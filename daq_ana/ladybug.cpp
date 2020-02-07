#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>

#include "DAQAnalysis.h"
#include "DAQMyAna.h"
#include "ttf2Looper.h"

std::map<std::string,std::string> arguments(int argc, char* argv[], std::vector<char*> *rest) {
  std::map<std::string,std::string> resMap;
  std::cout << argv[0] << " ";
  for (int i = 1; i != argc; ++i) {
    std::cout << argv[i] << " ";
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
  std::cout << std::endl;
  return resMap;
}


int main(int argc, char *argv[])
{
  //just to show usage and options
  std::vector<std::pair<std::string,std::string>> options{
   {"r","result director, defualt /reslut/"},
   {"t","parameter director, default ../tau_k_x/"},
   {"p","prefix to name this run"},
  };
  std::cout << "usage: " << argv[0] << " <options> <listOfFiles>" << std::endl;
  std::cout << "options:" << std::endl;
  for (auto o : options) {
    std::cout << "  -" << o.first << "=<" << o.second << ">" << std::endl;
    std::cout << std::endl;
  }

  // parse options and fileList
  std::vector<char*> fileList;
//  std::vector<std::string> fileListStr;
  auto args = arguments(argc,argv,&fileList);

  //set options, defaults and tests
  auto resultDirectory = args["-r"];
  if (resultDirectory.empty()) resultDirectory="/reslut/";
  std::cout << "resultDirectory: " << resultDirectory << std::endl;

  auto parameterDirector = args["-t"];
  if (parameterDirector.empty()) parameterDirector="../tau_k_x/";
  std::cout << "parameterDirector: " << parameterDirector << std::endl;

  auto prefix = args["-p"];
  if (prefix.empty()) prefix="testRun";
  std::cout << "prefix: " << prefix << std::endl;

  std::cout << "files:";
  if (fileList.empty() == true) {
    std::cout << " File list is empty." << std::endl;
    return 1;
  }
  for ( auto file : fileList ) std::cout << " " << file;
  std::cout << std::endl;

  //new
//  TTF2Looper l;
//  l.setFileList(fileList);
    TTF2Looper l(fileList);

    /// main 'loop' over the events
    //~ double samples = 1821;
    double samples = 1820;
    double div = 9;
    DAQAnalysis * oa = new DAQAnalysis(samples,div);



  return 0;
}
