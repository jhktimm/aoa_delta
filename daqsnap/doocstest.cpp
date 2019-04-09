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
  //~ print_daq_request(&request);
  
  reader_2010.set_data_dir(request.ddir);
  reader_2010.set_catalog_dir(request.cdir);
    
  reader_2010.init(&request.file_list, &request.chan_list);

  //~ reader_2010.print_channels();
  //~ reader_2010.print_files();
  
  vector<ttf2_channel_entry_long*> res;
  
  reader_2010.start();
  //~ reader_2010.get_data(NULL, &res);
  while((reader_2010.get_data(NULL, &res)) == TTF2_DAQ_READER_OK) {
    data.Clean();
    data.SetRes(&res);
    //~ data.PrintEvent();
    
   
        int nchan;
        int ndata;
				int lndata;
				int groups;
				float start;
				float inc;
				float groups_inc;
        char **chans = NULL;

				ttf2_spect_statistics_2010 *stat;
								
				nchan = data.GetNmemb();
        
        int nchans =  reader_2010.get_number_of_channels();
        chans = (char**) malloc(sizeof(char*)*nchans);
        
				for (int ch = 0; ch < nchan; ch++) {
					stat = NULL;
					if (!data.GetSpectPar(&start, &inc, NULL, &ndata, ch, &groups, &groups_inc, &stat)) {
						if (!ndata) {
							// Do nothing here for spectra with zero data but statistics arrays
						} else {
							lndata = ndata;
							if (groups > 1) lndata = groups*ndata;
						}
							
						printf("     [");
						// FIXME sample size to be a parameter?
						int samples = 3;

						/* Loop over spectrum elements for channel ch */
						for (int ii = 0; ii < lndata && ii < samples; ii++) {

							/* Get the spectrum value at bunch postion ii for channel ch */
							float di = data.GetSpectVal(ch, ii);
							if (std::isinf(di) || std::isnan((double)di)) {
								printf("Invalid"); 
							} else {
									printf("%.6f ",data.GetSpectVal(ch, ii));
							}
						}
						if (ch != (nchan-1)) {
							printf("]\t");
						} else { 
							printf("]");
						}
					} else {
						printf("No data\n"); 				
					}
					
				}	
    
  }
  return 0;	
}
