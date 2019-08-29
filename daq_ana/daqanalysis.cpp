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

int main(int argc, char *argv[])
{
  std::cout << "usage: " << argv[0] << " <prefix> <list with .raw files>\n";
  std::cout << "usage: " << argv[0] << " <resultDirectory> <prefix> <list with .raw files>\n";
  std::vector<char*> fileList;
  for (int a = 2; a < argc; a++) {
    fileList.push_back(argv[a]);
  }
  std::string resultDirectory;
  resultDirectory = argv[1];
  std::string prefix;
  prefix = argv[2];
  
  daq_server_request request;
	ttf2_daq_reader_2010 reader_2010;

  ttf2_daq_getdata data; 
  std::string path = argv[3];
  FileSystemPath fsp(path);  
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
  DAQMyAna ma;
  ulong numberOfAllEvents = reader_2010.get_number_of_files()*100;
  std::cout << "app. numberOfAllEvents = numberOfFiles*100: " << numberOfAllEvents << "\n" ;
  vector<ttf2_channel_entry_long*> res;
  reader_2010.start();
  int numberOfChannels;
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
        
        oa->set_data(&data);
        ma.setData(&data,samples);
//        oa->print_data();
        
        //~ oa->getAutoParameters("../../tau_k_x/");
        oa->getAutoParameters("../tau_k_x/");
//         oa->print_Parameters();
        
//         oa->get_calCoeff();
//        oa->print_calCoeff();
        
        oa->get_res();
        ma.mach();
//         oa->print_res();
        /// to get channel name
        char *channml;
        int llenl, statusch;
        if(data.GetChanInfo(&channml, NULL, &statusch, &llenl)) {
          printf("ttf2_user_loop(): failed to get Server Block info\n");
          return -1;
        }
        std::cout << "   channml: " << channml << " " << std::endl;// channml
        ///-----
        DoocsAddressHelper dah(channml);
        //~ dah.print();
        oa->write_res_dat( resultDirectory + dah.A_str + '.' + dah.L_str + '.' + dah.M_str + '.' + dah.C_str + '_' + prefix + ".dat" );
        ma.write( resultDirectory + "MyAna_" + dah.A_str + '.' + dah.L_str + '.' + dah.M_str + '.' + dah.C_str + '_' + prefix + ".dat" );
//         oa->write_res_dat( dah.A_str + '.' + dah.L_str + '.' + dah.M_str + '.' + dah.C_str + '_' + prefix + ".dat" );
//        oa->print_data();
      }
//      oa->print_data();
    }      
  }
  std::cout << "fino" << std::endl;
  return 0;
}
