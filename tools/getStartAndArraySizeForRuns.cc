#include<stdio.h>
#include<dirent.h>
#include<sstream>
#include<iostream>
#include<limits>
#include<map>
#include <math.h>
#include <fstream>

std::map<long,long> mapMin,mapMax;

void getMinMax(std::stringstream* stream) {

      std::string str, runNumber,fileNumber;
      long run{-1}, fileMin{std::numeric_limits<long>::max()}, fileMax{0};
      long file;
      while(getline(*stream,str,'_')) {
        std::stringstream tmp(str);
        std::size_t found;
        found = str.find("run");
        if (found != std::string::npos ) {
          runNumber = str.substr(found+3);
          try { run = std::stol(runNumber); } catch (...) {break;};
        }
        found = str.find("file");
        if (found != std::string::npos ) {
          fileNumber = str.substr(found+4);
          try { file = std::stol(fileNumber); } catch (...) {};
          if ( file > fileMax ) fileMax = file;
          if (file < fileMin ) fileMin = file;
        }
      }
      if ( (run > 0) & ( fileMax == fileMin) ) {
        auto itMax = mapMax.find(run);
        auto itMin = mapMin.find(run);
        if ( itMax == mapMax.end() ) mapMax.insert(std::make_pair(run,0 ));
        if ( itMin == mapMin.end() ) mapMin.insert(std::make_pair(run,std::numeric_limits<long>::max() ));
      }
      if ( (run > 0) & ( fileMax != 0) ) {
        auto itMax = mapMax.find(run);
        auto itMin = mapMin.find(run);
        if ( file > itMax->second ) mapMax[run] = file;
        if (file < itMin->second ) mapMin[run] = file;
  // 			std::cout << stream.str()
  // 				<< " run: " << run
  // 				<< " file: " << file
  // 				<< std::endl;
      } 
  
}


int main(int argc, char* argv[]) {
  if(argc!=2) {  
    std::cout << "Usage: " << argv[0] << " <directory>" << std::endl;
    std::cout << "Lists all runs with min and max file number," << std::endl;
    std::cout << "for files with <*run222_file11_*> run number is 222, min and max 11." << std::endl;
    std::cout << "Or usage: " << argv[0] << " <indexFile>" << std::endl;
    std::cout << "Create <indexFile> with:" << std::endl;
    std::cout << "ls <directory> > <indexFile>" << std::endl;
    
    return -1;
  }
  
  std::ifstream myfile (argv[1]);
  if (myfile.is_open())
  {
    std::string line;
    while ( getline (myfile,line) )
    {
      std::stringstream stream(line);
      getMinMax(&stream);
    }
    myfile.close();
  } else {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (argv[1])) != NULL) {
    std::cout << "Open directory: " << argv[1] << std::endl;
    std::cout << "This could take same time..." << std::flush;    
    while ((ent = readdir (dir)) != NULL) {
      std::stringstream stream(ent->d_name);
      getMinMax(&stream);
    }
    std::cout << std::endl;
    closedir (dir);
  } else {
    std::cout << "Could not open directory." << std::endl;
    return -1;
  }
 }
	for (auto p : mapMin) {
		std::cout << "run: " << p.first
		<< " min: " << p.second
		<< " max: " << mapMax[p.first]
		<< " numberOfFiles: " << (mapMax[p.first] - p.second + 1)
		<< " numberOfArrays: " << ceil( (mapMax[p.first] - p.second + 1.)/4000. )
		<< " numberOfArrays: " <<  (mapMax[p.first] - p.second + 1.)/4000. 
		<< std::endl;
	}
 std::cout << std::endl;

 std::ofstream outfile;
 outfile.open("setStartAndLengthFromRuns.sh");
 outfile
  << "#!/bin/bash\n"
  << "\n"
  << "case \"$1\" in\n";
	for (auto p : mapMin) {
//		std::cout
  outfile
		<< "    "
		<< p.first 
		<< ") runnumber=$1; START="
    << p.second/100
		<< "; arrayRange=0-"
    << ceil( (mapMax[p.first] - p.second + 1.)/4000. ) -1
		<< ";;"
		<< std::endl;
	}
 outfile
   << "    *) runnumber=\"\"; START=\"\"; arrayRange=\"\";echo \"Runnumber $1 is not defined in setStartAndLengthFromRuns\";return 1;;\n"
   << "esac\n"
   << "\n"
   << "echo \"Set parameter for run to runnumber=${runnumber} START=${START} arrayRange=${arrayRange}\"\n"
   << "return 0\n";

 outfile.close();
	return 0;
}
