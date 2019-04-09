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
#include <time.h>

int main(int argc, char *argv[])
{
  std::cout << "usage: " << argv[0] << " <json file with test data>\n";
  char * xml = NULL;
	xml = argv[1];
    
  daq_server_request request;
	ttf2_daq_reader_2010 reader_2010;
  ttf2_daq_getdata data;

  parse_daq_request_from_file(xml, &request);
  print_daq_request(&request);
  
  reader_2010.set_data_dir(request.ddir);
  reader_2010.set_catalog_dir(request.cdir);
    
  reader_2010.init(&request.file_list, &request.chan_list);

  reader_2010.print_channels();
  reader_2010.print_files();
  
  vector<ttf2_channel_entry_long*> res;
  
  reader_2010.start();
  //~ reader_2010.get_data(NULL, &res);
  while((reader_2010.get_data(NULL, &res)) == TTF2_DAQ_READER_OK) {
    data.Clean();
    data.SetRes(&res);
    data.PrintEvent();
    
    u_int evid, tup, tlow;
    int status;
    int statusch;
    u_int len;
    int evtype, nsrvb;


    if(data.GetEventInfo(&evid, &evtype, &len, &tup, &tlow, &status, &nsrvb)) {
      printf("ttf2_user_loop(): failed to get event info\n");
      return -1;
    }
    for(int ii=st; ii<lndata && ii<samples+st; ii++){
      float dt = data.GetSpectVal(ch, ii);
    }
    
    
    
  }
  return 0;	
}
