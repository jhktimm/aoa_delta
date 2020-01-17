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

std::map<long,std::string> fileMap;

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


int parseFileName(std::string str) {
 auto fileName = str;
 std::stringstream stream(str);
 long run, fileNumber, time;
 while(getline(stream,str,'_')) {
   std::size_t found;
   found = str.find("run");
   if (found != std::string::npos ) {
     try { run = std::stol(str.substr(found+3)); } catch (...) {break;};
   }
   found = str.find("file");
   if (found != std::string::npos ) {
     try { fileNumber = std::stol(str.substr(found+4)); } catch (...) {break;};
   }
 }
 long timeLong = date2unix(str);
 fileMap.insert(std::make_pair(timeLong,fileName));

 return 0;
}

int main(int argc, char *argv[])
{
  //just to show usage and options
  std::vector<std::pair<std::string,std::string>> options{
   {"-help","show this"},
   {"-verbose","show debug infos"},
   {"cores","define number of cores on every node, defualt 40"},
   {"size","nukmber of files per job, default 100"},
   {"indexFile","path to .index file with list of files. default 'index'"},
   {"outputFile","name for the output file, default 'fileList.txt'"},
   {"arrayNumber","show file list for this array number"},
   {"coreNumber","show file list for this core number"},
  };

  // parse options and fileList
  std::vector<char*> fileList;
//  std::vector<std::string> fileListStr;
  auto args = arguments(argc,argv,&fileList);

  bool verbose = false;
  if (args.count("--verbose")) verbose=true;

  //set options, defaults and tests
  auto numberOfCoresStr = args["-cores"];
  if (numberOfCoresStr.empty()) numberOfCoresStr="40";
  auto numberOfCores = std::stol(numberOfCoresStr);
  if (verbose) std::clog << "numberOfCores: " << numberOfCores << std::endl;

  auto sizeStr = args["-size"];
  if (sizeStr.empty()) sizeStr="100";
  auto size = std::stol(sizeStr);
  if (verbose) std::clog << "size: " << size << std::endl;

  auto indexFile = args["-indexFile"];
  if (indexFile.empty()) indexFile="index";
  if (verbose) std::clog << "indexFile: " << indexFile << std::endl;

  auto outputFile = args["-outputFile"];
  if (outputFile.empty()) outputFile="fileList.txt";
  if (verbose) std::clog << "outputFile: " << outputFile << std::endl;

  auto coreNumberStr = args["-coreNumber"];
  if (coreNumberStr.empty()) coreNumberStr="0";
  auto coreNumber = std::stol(coreNumberStr);
  if (verbose) std::clog << "coreNumber: " << coreNumber << std::endl;

  auto arrayNumberStr = args["-arrayNumber"];
  if (arrayNumberStr.empty()) arrayNumberStr="0";
  auto arrayNumber = std::stol(arrayNumberStr);
  if (verbose) std::clog << "arrayNumber: " << arrayNumber << std::endl;

  if (args.count("--help")) {
      std::clog << "This program cout to start dateTime and make a list of Files." << std::endl;
    std::clog << "usage: " << argv[0] << " <options> <listOfFiles>" << std::endl;
    std::clog << "options:" << std::endl;
    for (auto o : options) {
      std::clog << "  -" << o.first << "=<" << o.second << ">" << std::endl;
//      std::clog << std::endl;
    }
    std::clog << "example: ./getFileList -coreNumber=0 -arrayNumber=1 --verbose" << std::endl;
    std::clog << std::endl;
    return 0;
  }

  //////////////////////////////////////////////////////////////////////////////////

  std::ifstream myfile (indexFile);
  if (myfile.is_open())
  {
    std::string line;
    while ( getline (myfile,line) )
    {
      std::stringstream stream(line);
      parseFileName(line);
//      std::cout << line << " ";
    }


    myfile.close();
  }

  int i = 0;
  int iMin=coreNumber*size+arrayNumber*numberOfCores*size;
  int iMax=iMin+size;
  if (verbose) std::clog << "Min: " << iMin << " Max: " << iMax << std::endl;

  std::ofstream outFile(outputFile);
  for (auto p : fileMap) {
    if (i == iMin) std::cout << unix2date(p.first) << std::endl;
    if (  (i < iMax ) & (i >= iMin)) {
        outFile << p.second << " ";
//        outFile << p.second << std::endl;
//        std::cout << p.first << " " <<  unix2date(p.first) << std::endl;
    }
    ++i;
  }
  outFile.close();
}
