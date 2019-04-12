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

int processEvent(ttf2_daq_getdata* data)
{
  ///to get pid and time
  u_int evid, tup, tlow;
  int status;
  int statusch;
  u_int len;
  int evtype, nsrvb;
  if(data->GetEventInfo(&evid, &evtype, &len, &tup, &tlow, &status, &nsrvb)) {
    printf("ttf2_user_loop(): failed to get event info\n");
    return -1;
  }
  std::cout << "   evid: " << evid;// PID
  //~ std::cout << "    tup: " << tup << " " << std::endl;//time [s]
  //~ std::cout << "   tlow: " << tlow << " " << std::endl;//time [mus]
  ///-----  
  /// to get channel name
  char *channml;
  int llenl;
  if(data->GetChanInfo(&channml, NULL, &statusch, &llenl)) {
    printf("ttf2_user_loop(): failed to get Server Block info\n");
    return -1;
  }
  std::cout << "   channml: " << channml << " " << std::endl;// channml
  ///-----
  ///main loop over numberOfSubchannels = # of subchennels: pp, ps, refl and forw ...
  int numberOfSubchannels;
  int ndata;
  int lndata;
  int groups;
  float start;
  float inc;
  float groups_inc;
  ttf2_spect_statistics_2010 *stat;  
  numberOfSubchannels = data->GetNmemb();
  std::cout << "   numberOfSubchannels: " << numberOfSubchannels << " " << std::endl;
  /// numberOfSubchannels = # of subchennels: pp, ps, refl and forw ...
  for (int ch = 0; ch < numberOfSubchannels; ch++) {
    //~ std::cout << "  GetMembName: " << data.GetMembName(ch) << std::endl;
    stat = NULL;
    if (!data->GetSpectPar(&start, &inc, NULL, &ndata, ch, &groups, &groups_inc, &stat)) {
      if (!ndata) {
        // Do nothing here for spectra with zero data but statistics arrays
      } else {
        lndata = ndata;
        if (groups > 1) lndata = groups*ndata;
      }
      // FIXME sample size to be a parameter?
      //~ int samples = 3;
      int samples = ndata;// FIXED            
      //~ printf("     [");
      /* Loop over spectrum elements for channel ch */
      //~ std::cout << "   lndata: " << lndata << " " << std::endl;
      /// lndata = #samples from the spectrum
      /// main loop over the samples
      for (int ii = 0; ii < lndata && ii < samples; ii++) {
        /* Get the spectrum value at bunch postion ii for channel ch */
        float di = data->GetSpectVal(ch, ii);
        if (std::isinf(di) || std::isnan((double)di)) {
          printf("Invalid"); 
        } else {
            //~ printf("%.6f ",data->GetSpectVal(ch, ii));
            //~ std::cout << di << " ";
        }
      }
      if (ch != (numberOfSubchannels-1)) {
        //~ printf("]\t");
      } else { 
        //~ printf("]");
      }
    } else {
      printf("No data\n"); 				
    }
    
  }	  
}


int main(int argc, char *argv[])
{
  std::cout << "usage: " << argv[0] << " <xml file with request>\n";
  char * xml = NULL;
	xml = argv[1];
  vector<char*> fls;
  fls.push_back(argv[1]);
  
    
  daq_server_request request;
	ttf2_daq_reader_2010 reader_2010;

  ttf2_daq_getdata data; 
  parse_daq_request_from_file(xml, &request); 
  //~ reader_2010.set_data_dir(request.ddir);///xml
  //~ reader_2010.set_catalog_dir(request.cdir);///xml
  //~ reader_2010.init(&request.file_list, &request.chan_list);///xml
  
  //~ reader_2010.set_catalog_dir("/daq/xfel/adm/");
  //~ reader_2010.set_data_dir("/daq_data/xfel/LLRF/");
  reader_2010.set_data_dir("/daq_data/xfel/USR1/LLRF/");///raw + list
  //~ reader_2010.add_file(argv[1],true);///raw
  
  
  /// check if we have to add all channels
  daq_server_request request_dummy;
	ttf2_daq_reader_2010 reader_dummy;
  reader_dummy.set_data_dir("/daq_data/xfel/USR1/LLRF/");  
  reader_dummy.init(&fls, &request_dummy.chan_list); 
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
      std::cout << "entry.name " << entry->name << "  ent->count " << ent->count << " dtype " << ent->dtype << std::endl;
      //~ reader_2010.add_channel(entry);///raw
      ch_list.push_back(entry);
    }
  }
  vc.clear();
  ///-----
  reader_2010.init(&fls, &ch_list);///list

  reader_2010.print_channels();
  reader_2010.print_files();
  
  /// main 'loop' over the events
  vector<ttf2_channel_entry_long*> res;
  reader_2010.start();
  int numberOfChannels;
  while((reader_2010.get_data(NULL, &res)) == TTF2_DAQ_READER_OK) {
    data.Clean();
    data.SetRes(&res);
    std::cout << "res.size() " << res.size() << "  reader_2010.get_number_of_channels() " << reader_2010.get_number_of_channels() << std::endl;
    if(res.size() == reader_2010.get_number_of_channels()) {
      data.Clean();
      data.SetRes(&res);
      numberOfChannels = reader_2010.get_number_of_channels();
      for (int i = 0; i < numberOfChannels; i++) {
        data.SetChan(i);
        processEvent(&data);
      }
    }      
  }
  return 0;	
}
