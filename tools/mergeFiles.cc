#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <ctime>
#include <iomanip>
#include <locale>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <dirent.h>
#include <cmath>

bool dummy = false;

std::map<std::string,std::string> arguments(int argc, char* argv[], std::vector<char*> *rest) {
 std::map<std::string,std::string> resMap;
 //  std::clog << argv[0] << " ";
 for (int i = 1; i != argc; ++i) {
  //    std::clog << argv[i] << " ";
  if (argv[i][0]=='-') {
   std::stringstream stream(argv[i]);
   std::string value,option;
   std::getline(stream, option,'=');
   std::getline(stream, value,'=');
   resMap.insert(std::make_pair(option,value));
  } else {
   rest->push_back(argv[i]);
  }
 }
 //  std::clog << std::endl;
 return resMap;
}

long date2unix(std::string str) {
 time_t tStart;
 int yy, month, dd, hh, mm, ss;
 struct tm whenStart;
 const char *zStart = str.c_str();
 sscanf(zStart, "%4d%2d%2dT%2d%2d%2d", &yy, &month, &dd, &hh, &mm, &ss);
 whenStart.tm_year = yy - 1900;
 whenStart.tm_mon = month - 1;
 whenStart.tm_mday = dd;
 whenStart.tm_hour = hh;
 whenStart.tm_min = mm;
 whenStart.tm_sec = ss;
 whenStart.tm_isdst = -1;
 tStart = mktime(&whenStart);
 long timeLong = tStart;
 //        std::stringstream tmp(str);
 //        struct std::tm dateTime;
 // tmp >> std::get_time(&dateTime, "%Y%m%dT%H%M%S.1.raw");
 return timeLong;
}

std::string unix2date(long time) {
 time_t t = time;
 struct tm tm = *localtime(&t);
 char buff[100];
 sprintf(buff,"%d%02d%02dT%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
 std::string str = buff;
 return str;
}


std::pair<std::string,std::pair<long,std::string>> parseFileName(std::string fullPath) {
 auto fileName = fullPath.substr( fullPath.rfind('/') + 1 );
 auto filePrefix = fileName.substr(0, fileName.rfind('_'));
 long timeLong = date2unix(fullPath.substr(fullPath.rfind('_')+1));
 auto inner = std::make_pair(timeLong,fullPath);
 auto outer = std::make_pair(filePrefix,inner);

 return outer;
}

void merge(std::string outFileName, std::vector<std::string> files) {
 std::cout << " merge  "<< files.size() << " fiels into file: "  << outFileName << std::endl;
 if(!dummy) {
  std::ofstream outFile(outFileName);
  std::string line;
  bool first = true;
  for (auto f : files) {
   std::ifstream inFile(f);
   if (!first) {
    getline(inFile,line);
   }
   while(getline(inFile, line)) {
    outFile << line << std::endl;
   }
   inFile.close();
   first = false;
  }
  outFile.close();
 }
}

void bundle(std::pair<std::string,std::map<long,std::string>> cav, int fileNumber, std::string outDir, bool verbose, int numOfTHreads){
 int i = 1;
 std::string mergedFileName;
 std::vector<std::string> fileList;
 std::vector<std::thread> threads;
 if (cav.second.size()<fileNumber) {
  std::cout << " number of files to be merged:" << fileNumber << " set to size of list: " << cav.second.size()  << std::endl;
  fileNumber=cav.second.size();
 }
 for (auto p : cav.second) {
  fileList.push_back(p.second);
  if (i==1) {
   mergedFileName = outDir + p.second.substr( p.second.rfind('/') + 1 );
  }
  if (verbose) std::cout << "  add file: "  << p.second << std::endl;
  if (i==fileNumber) {
   threads.push_back(std::thread(merge,mergedFileName,fileList));
   i = 1;
   fileList.clear();
  } else {
   i++;
  }
  if ( threads.size() == static_cast<ulong>(numOfTHreads) ) {
   for (size_t x = 0; x < threads.size(); ++x) threads[x].join();
   threads.clear();
  }
 }
 //very last thread
 if (!fileList.empty()) threads.push_back(std::thread(merge,mergedFileName,fileList));
 for (size_t x = 0; x < threads.size(); ++x) threads[x].join();
}



int main(int argc, char *argv[])
{
 //just to show usage and options
 std::vector<std::pair<std::string,std::string>> options{
  {"-help","show this"},
  {"-verbose","show debug infos"},
  {"-dummy","no merge"},
  {"-uid","only find UID"},
  {"o","optimal number of cores, overrides -j"},
  {"size","number of files to merge, default 100"},
  {"j","number of threads, default 1"},
  {"outDir","output directory, default pwd"},
  {"inputDir","input directory, required"},
  {"searchPattern","search pattern, required"}
 };

 // parse options and fileList
 std::vector<char*> fileList;
 //  std::vector<std::string> fileListStr;
 auto args = arguments(argc,argv,&fileList);

 //set flags, options, defaults and tests
 bool verbose = false;
 if (args.count("--verbose")) verbose=true;

 bool uid = false;
 if (args.count("--uid")) uid=true;

 if (args.count("--dummy")) dummy=true;

 auto sizeStr = args["-size"];
 if (sizeStr.empty()) sizeStr="100";
 auto size = std::stol(sizeStr);
 if (verbose) std::clog << "size: " << size << std::endl;

 bool optimal = false;
 if (args.count("-o")) optimal=true;

 auto numThreadsStr = args["-j"];
 if (numThreadsStr.empty()) numThreadsStr="1";
 auto numThreads = std::stoi(numThreadsStr);
 if (verbose) std::clog << "size: " << numThreads << std::endl;

 auto outDir = args["-outDir"];

 auto inputDir = args["-inputDir"];

 auto searchPattern = args["-searchPattern"];

 if ( args.count("--help") | argc==1  ) {
  std::clog << "This program merges files." << std::endl;
  std::clog << "/beegfs/desy/user/jhktimm/results/A17.L3.M1.C8_Mona_Noether_20190324T115450.dat" << std::endl;
  std::clog << "/beegfs/desy/user/jhktimm/results/A17.L3.M1.C8_Mona_Noether_20190324T125451.dat" << std::endl;
  std::clog << "/beegfs/desy/user/jhktimm/results/<unique file name>_20190324T115450.dat" << std::endl;
  std::clog << "/beegfs/desy/user/jhktimm/results/A17.L3.M1.C8_Mona_Noether_<date and time>.dat" << std::endl;
  std::clog << "new file name A17.L3.M1.C8_Mona_Noether_20190324T115450.dat" << std::endl;
  std::clog << "new file name <unique file name>_<date and time of the first file from each 'size' file list>.dat" << std::endl;
  std::clog << "usage: " << argv[0] << " <options> <listOfFiles>" << std::endl;
  std::clog << "options:" << std::endl;
  for (auto o : options) {
   std::clog << "  -" << o.first << "=<" << o.second << ">" << std::endl;
   //      std::clog << std::endl;
  }
  std::clog << "example: ./mergeFiles -size=10 --verbose /beegfs/*Mona_Lisa*" << std::endl;
  std::clog << std::endl;
  return 0;
 }

 //////////////////////////////////////////////////////////////////////////////////
 std::chrono::time_point<std::chrono::system_clock> start, end;
 /// map of cavity_unique_name of map of time and fullPath
 std::map<std::string,std::map<long,std::string>> cavityMap;

 if (fileList.empty()) {
  if ( inputDir.empty() && searchPattern.empty() ) {
   std::cerr << "you have to specify -inputDir=<> and -searchPattern=<>. See --help\n";
   return 1;
  }
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (inputDir.c_str())) != NULL) {
   while ((ent = readdir (dir)) != NULL) {
    std::string checkFileName(ent->d_name);
    if (checkFileName.find(searchPattern)!=std::string::npos) {
     //         printf ("%s\n", ent->d_name);
     auto ret = parseFileName(inputDir+checkFileName);
     cavityMap[ret.first][ret.second.first] = ret.second.second;
    }

   }
   closedir (dir);
  } else {
   /* could not open directory */
   perror ("");
   return EXIT_FAILURE;
  }
 } else {
  for (auto file: fileList) {
   auto ret = parseFileName(file);
   cavityMap[ret.first][ret.second.first] = ret.second.second;
  }
 }

 if (optimal) {
  numThreads = static_cast<int>(std::thread::hardware_concurrency());
  std::cout << "Optimal number of threads = "
            <<  numThreads << std::endl;
 }
 std::vector<std::thread> threads;
 int i = 0;
 start = std::chrono::system_clock::now();

 std::cout << "Total number of unique identifier data(UID) to be merged: " << cavityMap.size() << std::endl;
 if (cavityMap.size()==0) return 1;
 if (uid) {
  for (auto cav : cavityMap) {
   std::cout << "found unique identifier(UID): " << cav.first << " with: " << cav.second.size() <<  " files" <<  std::endl;
  }
  return 0;
 }
 int numThreadsMain=numThreads;
 int numThreadsBundle=1;
 if (numThreads > cavityMap.size()) {
  numThreadsBundle = std::ceil(numThreads/cavityMap.size());
  numThreadsMain = numThreads/numThreadsBundle;
 }
 std::cout << "numThreadsTotal: " << numThreads << std::endl;
 std::cout << "numThreadsBundle for files: " << numThreadsBundle << std::endl;
 std::cout << "numThreadsMain for UID: " << numThreadsMain << std::endl;

 for (auto cav : cavityMap) {
  std::cout << "found unique identifier(UID): " << cav.first << " with: " << cav.second.size() <<  " files, thread number: " << i <<  std::endl;
  threads.push_back(std::thread(bundle,cav,size,outDir, verbose, numThreadsBundle));
  if (i == numThreadsMain - 1 ) {
   for (size_t x = 0; x < threads.size(); ++x) threads[x].join();
   threads.clear();
   i=0;
  } else {
   ++i;
  }
 }
 //catch the last threads
 for (size_t x = 0; x < threads.size(); ++x) threads[x].join();
 end = std::chrono::system_clock::now();
 int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
   (end-start).count();
 std::cout << "elapsed time: " << elapsed_seconds << "s\n";
 return 0;
}
