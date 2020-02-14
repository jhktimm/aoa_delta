#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>

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

void justDoIt(DAQAnalysis *oa,ttf2_daq_getdata* data, std::string parameterDirector,std::string fileNameToSave, std::string fullName) {
//  double samples = 1820, div = 9;
//  DAQAnalysis oa(samples,div);
//  DAQAnalysis * oa = new DAQAnalysis(samples,div);
 /// set data to the
 oa->set_data(data);
 /// prepair for calculations
 oa->getAutoParameters(parameterDirector);
 /// skiping same channels
 std::vector<std::string> channelsToSkip;
 channelsToSkip.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C7.M3.A17.L3");//this cavity was off for run 1138,1143,1146
 channelsToSkip.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C2.M2.A12.L3");// get res does not work with this for run 1262
 channelsToSkip.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C8.M3.A12.L3");//   "
 channelsToSkip.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C1.M4.A12.L3");//   "
 bool calculateThisChannel = true;
 for  (auto channelToSkip: channelsToSkip) {
   if( channelToSkip.compare(fullName) == 0) calculateThisChannel = false ;
 }
 /// do calculations
 if (calculateThisChannel) oa->get_res();
 /// write results
 oa->write_res_dat( fileNameToSave );
// delete(oa);
}


int main(int argc, char *argv[])
{
 //just to show usage and options
 std::vector<std::pair<std::string,std::string>> options{
  {"r","result director, defualt /reslut/"},
  {"t","parameter director, default ../tau_k_x/"},
  {"j","number of cores, default 1"},
  {"-o","best number of cores, overwrites -j"},
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

 auto numberOfCOresStr = args["-j"];
 if (numberOfCOresStr.empty()) numberOfCOresStr="1";
 auto numberOfCores = std::stoi(numberOfCOresStr);
 std::cout << "numberOfCores: " << numberOfCores << std::endl;

 bool bestCores = false;
 if (args.count("--o")) bestCores=true;

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


 if (bestCores) {
//   numberOfCores = static_cast<int>(std::thread::hardware_concurrency());
//   std::cout << "Optimal number of threads = "
//             <<  numThreads << std::endl;

      std::cout << "Optimal number of threads = NOT IMPLEMENTED JET " << std::endl;
 }
 std::vector<std::thread> threads;

 double samples = 1820, div = 9;

 std::vector<DAQAnalysis*> oaVec;
 for (int i=0; i<numberOfCores; ++i) {
  DAQAnalysis oa(samples,div);
//   DAQAnalysis * oa = new DAQAnalysis(samples,div);
   oaVec.push_back(&oa);
 }
 /// main 'loop' over the events
 TTF2Looper looper(fileList);
 int nuumberOfRunningThreads = 0;
 while(looper.getData()) {
  if(looper.numberOfChannels == looper.res.size()) {
    std::cout << "  numberOfChannels: " << looper.numberOfChannels << " " << std::endl;
    for (int i = 0; i < looper.numberOfChannels; i++) {
     ///this also set set this channel to the data, not only getting the name
     auto channelName = looper.getChannel(i);
     std::cout << "   channel name: " << channelName.shortName << " " << std::endl;
     auto fileNameToSave = resultDirectory + channelName.shortName + '_' + prefix + ".dat" ;
     threads.push_back(std::thread(justDoIt,oaVec[nuumberOfRunningThreads],&looper.data,parameterDirector,fileNameToSave,channelName.fullName));
//     justDoIt(&looper.data,parameterDirector,fileNameToSave,channelName.fullName);
         if (nuumberOfRunningThreads == numberOfCores - 1 ) {
          for (size_t x = 0; x < threads.size(); ++x) {
            threads[x].join();
          }
          threads.clear();
          nuumberOfRunningThreads=0;
         } else {
          ++nuumberOfRunningThreads;
         }
    }
    //catch the last threads
    for (size_t x = 0; x < threads.size(); ++x) threads[x].join();
  } else {
    std::cerr << "Number of channels not ok. res != get" << std::endl;
  }
 }
 std::cout << "ladybug: fino" << std::endl;
 return 0;
}
