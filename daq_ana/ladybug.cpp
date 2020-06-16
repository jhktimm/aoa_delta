#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include <map>
#include <chrono>

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

void justDoIt(DAQAnalysis * oa, ttf2_daq_getdata* data, std::string parameterDirector,std::string fileNameToSave, std::string fullChannelName) {
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
   if( channelToSkip.compare(fullChannelName) == 0) calculateThisChannel = false ;
 }
 std::vector<std::string> channelsToSkipWithPIDCut;
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C1.M1.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C2.M1.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C3.M1.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C4.M1.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C5.M1.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C6.M1.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C7.M1.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C8.M1.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C1.M2.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C2.M2.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C3.M2.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C4.M2.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C5.M2.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C6.M2.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C7.M2.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C8.M2.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C1.M3.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C2.M3.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C3.M3.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C4.M3.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C5.M3.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C6.M3.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C7.M3.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C8.M3.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C1.M4.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C2.M4.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C3.M4.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C4.M4.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C5.M4.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C6.M4.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C7.M4.A17.L3");
 channelsToSkipWithPIDCut.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C8.M4.A17.L3");
 bool calculateThisChannelWithPIDCut = true;
 for  (auto channelToSkip: channelsToSkipWithPIDCut) {
   if( ( channelToSkip.compare(fullChannelName) == 0) and (oa->TIME >=  1569999397.912552 ) and (oa->TIME < 1572999397.0  ) ) calculateThisChannelWithPIDCut = false ;
 }

 /// do calculations
 if (calculateThisChannel and calculateThisChannelWithPIDCut) oa->get_res();
 /// write results
 oa->write_res_dat( fileNameToSave );
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

 std::chrono::time_point<std::chrono::system_clock> start, end;
 start = std::chrono::system_clock::now();
 double samples = 1820, div = 9;
 DAQAnalysis * oa = new DAQAnalysis(samples,div);

 /// main 'loop' over the events
 TTF2Looper looper(fileList);
 while(looper.getData()) {
  std::cout << "  numberOfChannels: " << looper.numberOfChannels << " " << std::endl;
  for (int i = 0; i < looper.numberOfChannels; i++) {
   ///this also set set this channel to the data, not only getting the name
   auto channelName = looper.getChannel(i);
   std::cout << "   channel name: " << channelName.shortName << " " << std::endl;
   auto fileNameToSave = resultDirectory + channelName.shortName + '_' + prefix + ".dat" ;
   justDoIt(oa,&looper.data,parameterDirector,fileNameToSave,channelName.fullName);
  }
 }
 end = std::chrono::system_clock::now();
 auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
   (end-start).count();
 std::cout << "totalNumber: " << looper.totalNumber << "\n";
 std::cout << "elapsed time: " << elapsed_seconds << "s\n";
 std::cout << "elapsed time per channel: " << static_cast<double>(1000.*elapsed_seconds/looper.totalNumber) << "ms\n";
 std::cout << "ladybug: fino" << std::endl;
 return 0;
}
