#include "ttf2Looper.h"

TTF2Looper::TTF2Looper() {

}

/////////////////////////////////////////////////////////////////////////

TTF2Looper::TTF2Looper(std::vector<char*> list) {
  std::cout << "Init ttf2 looper." << std::endl;

  setFileList(list);
  auto ch_list = getChannelList();
  reader_2010.init(&fileList, &ch_list);

  reader_2010.print_channels();
  reader_2010.print_files();
  ulong numberOfAllEvents = reader_2010.get_number_of_files()*100;
  std::cout << "app. numberOfAllEvents = numberOfFiles*100: " << numberOfAllEvents << "\n" ;
  reader_2010.start();
  std::cout << "ttf2 looper ok." << std::endl;
}

/////////////////////////////////////////////////////////////////////////

TTF2Looper::~TTF2Looper() {

}

/////////////////////////////////////////////////////////////////////////

std::vector<daq_channel_entry*>  TTF2Looper::getChannelList() {
 /// check if we have to add all channels
 daq_server_request request_dummy;
 ttf2_daq_reader_2010 reader_dummy;
 reader_dummy.set_data_dir((char*) path().c_str());

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
     if(!dah.L_str.empty()) {
       ch_list.push_back(entry);
     }
   }
 }
 return ch_list;
}

/////////////////////////////////////////////////////////////////////////

std::string  TTF2Looper::path() {
  std::string path;
  if (!fileList.empty()) {
    std::string fullPath = fileList.at(0);
    path = fullPath.substr(0, fullPath.rfind('/'));
  } else {
    throw std::runtime_error("error: ttf2looper: list of files is empty.");
  }
  return path;
}
