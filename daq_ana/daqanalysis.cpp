#include <daq_server_util_def.h>
#include <ttf2_daq_data.h>
#include <ttf2_daq_reader_2010.h>

#include <parse_chan_descr.h>
#include <ttf2_daq_slicer.h>


#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>

#include "DAQAnalysis.h"
#include "DAQMyAna.h"

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

  std::string path = fileList.at(0);
  FileSystemPath fsp(path);


  daq_server_request request;
  ttf2_daq_reader_2010 reader_2010;

  ttf2_daq_getdata data;
  //~ reader_2010.set_data_dir((char*) "/daq_data/xfel/USR1/LLRF/");///raw + list
  reader_2010.set_data_dir((char*) fsp.dir.c_str());///raw + list

  /// check if we have to add all channels
  daq_server_request request_dummy;
  ttf2_daq_reader_2010 reader_dummy;
  //~ reader_dummy.set_data_dir((char*) "/daq_data/xfel/USR1/LLRF/");
  reader_dummy.set_data_dir((char*) fsp.dir.c_str());
  
  reader_dummy.init(&fileList, &request_dummy.chan_list);
  vector<chan_descr_2010*> vc;
  vc.clear();
  reader_dummy.fill_chan_descr(reader_dummy.get_file_name(0), &vc);
  std::vector<daq_channel_entry*> ch_list;
  for(u_int i=0; i<vc.size(); i++) {
    chan_descr_2010* ent = vc[i];
    if(ent &&  ent->count && ent->dtype == 2148532224 ) {
      //~ if(ent &&  ent->count) {
      daq_channel_entry *entry = (daq_channel_entry *)malloc(sizeof(daq_channel_entry));
      entry->name = ent->daq_name;
      entry->prms.start = -1;
      entry->prms.length = -1;
      entry->prms.func = -1;
      entry->prms.inc = -1;
      DoocsAddressHelper dah(entry->name);
      //~ dah.print();
      if(!dah.L_str.empty()) {
        //~ std::cout << "entry.name " << entry->name << "  ent->count " << ent->count << " dtype " << ent->dtype << std::endl;
        ch_list.push_back(entry);
      }
    }
  }
  vc.clear();
  ///-----
  reader_2010.init(&fileList, &ch_list);///list

  reader_2010.print_channels();
  reader_2010.print_files();

  
  /// main 'loop' over the events
  //~ double samples = 1821;
  double samples = 1820;
  double div = 9;
  DAQAnalysis * oa = new DAQAnalysis(samples,div);
  //  DAQMyAna ma;
  ulong numberOfAllEvents = reader_2010.get_number_of_files()*100;
  std::cout << "app. numberOfAllEvents = numberOfFiles*100: " << numberOfAllEvents << "\n" ;
  vector<ttf2_channel_entry_long*> res;
  reader_2010.start();
  int numberOfChannels;
  /////////////////////////////////////////////////////////////////////////////////////
  /// main loop over daq data
  while((reader_2010.get_data(NULL, &res)) == TTF2_DAQ_READER_OK) {
    std::cout << "operating " << reader_2010.get_number_of_events() << " of approx " << numberOfAllEvents <<" events\n" ;
    data.Clean();
    data.SetRes(&res);
    //~ std::cout << "res.size() " << res.size() << "  reader_2010.get_number_of_channels() " << reader_2010.get_number_of_channels() << std::endl;
    if(res.size() == (uint) reader_2010.get_number_of_channels()) {
      data.Clean();
      data.SetRes(&res);
      numberOfChannels = reader_2010.get_number_of_channels();
      for (int i = 0; i < numberOfChannels; i++) {
        data.SetChan(i);
        //~ processEvent(&data);
        
        //~ std::cout << "\n-----------------------------------\n";
        
        /////////////////////////////////////////////////////////////////////////////////////
        /// set data to the
        oa->set_data(&data);
        //        ma.setData(&data,samples);
        //        oa->print_data();
        
        /////////////////////////////////////////////////////////////////////////////////////
        /// prepair for calculations
        oa->getAutoParameters(parameterDirector);//normal
//        oa->getAutoParameters("../tau_k_x/");//normal
        //oa->print_Parameters();
        
        /////////////////////////////////////////////////////////////////////////////////////
        /// to get channel name
        char *channml;
        int llenl, statusch;
        if(data.GetChanInfo(&channml, NULL, &statusch, &llenl)) {
          printf("ttf2_user_loop(): failed to get Server Block info\n");
          return -1;
        }
        std::cout << "   channml: " << channml << " " << std::endl;// channml

        /////////////////////////////////////////////////////////////////////////////////////
        /// do calculations
//        std::string wasOFF("XFEL.RF/LLRF.CONTROLLER.DAQ/C7.M3.A17.L3");

        /// skiping same channels
        std::vector<std::string> channelsToSkip;
        channelsToSkip.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C7.M3.A17.L3");//this cavity was off for run 1138,1143,1146
        channelsToSkip.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C2.M2.A12.L3");// get res does not work with this for run 1262
        channelsToSkip.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C8.M3.A12.L3");//   "
        channelsToSkip.push_back("XFEL.RF/LLRF.CONTROLLER.DAQ/C1.M4.A12.L3");//   "
        bool calculateThisChannel = true;
        for  (auto channelToSkip: channelsToSkip) {
          if( channelToSkip.compare(channml) == 0) calculateThisChannel = false ;
        }
        if (calculateThisChannel) oa->get_res();
//        if ( wasOFF.compare(channml) != 0) oa->get_res();// !!!!!!!!!!!
        //        ma.mach();
        //         oa->print_res();

        /////////////////////////////////////////////////////////////////////////////////////
        /// write results
        DoocsAddressHelper dah(channml);
        //~ dah.print();
        oa->write_res_dat( resultDirectory + dah.A_str + '.' + dah.L_str + '.' + dah.M_str + '.' + dah.C_str + '_' + prefix + ".dat" );// !!!!!!!!!!!
        //        ma.write( resultDirectory + "MyAna_" + dah.A_str + '.' + dah.L_str + '.' + dah.M_str + '.' + dah.C_str + '_' + prefix + ".dat" );
        //        oa->print_data();
      }

      //      oa->print_data();
    } else {
      std::cout << "res.size(): "<< res.size() <<" != (uint) reader_2010.get_number_of_channels(): "<< (uint) reader_2010.get_number_of_channels() << std::endl;
    }
  }
  std::cout << "fino" << std::endl;
  return 0;
}
