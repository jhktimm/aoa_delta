#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//~ #include "doocs_snapdaq_llrf_datasclass.h"
#include "../include/OnlineAnalysis.h"
#include <time.h>

//~ /*
int main(int argc, char *argv[])
{
	std::cout << argc << ": " << argv[0] << "\n";
	//~ doocs_snapdaq_llrf_dataclass* mpd2 = new doocs_snapdaq_llrf_dataclass(argv[1]);
	
	
	//~ double samples = 1821;
	//~ double samples = 101;
	//~ double samples = 16384;
	//~ double div = 1;
	double samples = 1821;
	double div = 9;
	OnlineAnalysis * oa = new OnlineAnalysis(samples,div);

	if (argc == 0) {
		std::cout << "usage: " << argv[0] << " <[A17.L3.M2.C1_]data_file_name.dat>   <lists of files to operate>"  ;
		return 1;
    }
	for (int a = 2; a < argc; a++) {
		std::cout << "open file " << a - 1 << "/" << argc - 2 << ": " << argv[a] << "\n";
		aoa_daq_datasclass* mpd2 = new aoa_daq_datasclass(argv[a]);
		//~ std::cout << "size of a sample: " << mpd2->mps.at(0).channel.at(0).forward_signal.size() << "\n";
		for (auto macro_test : mpd2->mps) {

			std::cout << "pid: " << macro_test.pid << " time: " << std::setprecision(12)<< macro_test.time << std::endl;
			//~ std::cout << "str: " << macro_test.str << "\n";
			for (auto mchannel: macro_test.channel){
				//~ std::cout << "doocschannel: " << mchannel.doocschannel << " type: " << mchannel.type << " station: " << mchannel.station << "\n";
				if ( 
					//~ (mchannel.doocschannel=="C1.M1.A17.L3") | 
					//~ (mchannel.doocschannel=="C2.M1.A17.L3") | 
					//~ (mchannel.doocschannel=="C3.M1.A17.L3") | 
					//~ (mchannel.doocschannel=="C4.M1.A17.L3") 
					(mchannel.type=="C1.M1") | (mchannel.type=="C2.M1") | (mchannel.type=="C3.M1") | (mchannel.type=="C4.M1") |
					(mchannel.type=="C5.M1") | (mchannel.type=="C6.M1") | (mchannel.type=="C7.M1") | (mchannel.type=="C8.M1") |
					(mchannel.type=="C1.M2") | (mchannel.type=="C2.M2") | (mchannel.type=="C3.M2") | (mchannel.type=="C4.M2") |
					(mchannel.type=="C5.M2") | (mchannel.type=="C6.M2") | (mchannel.type=="C7.M2") | (mchannel.type=="C8.M2") |
					(mchannel.type=="C1.M3") | (mchannel.type=="C2.M3") | (mchannel.type=="C3.M3") | (mchannel.type=="C4.M3") |
					(mchannel.type=="C5.M3") | (mchannel.type=="C6.M3") | (mchannel.type=="C7.M3") | (mchannel.type=="C8.M3") |
					(mchannel.type=="C1.M4") | (mchannel.type=="C2.M4") | (mchannel.type=="C3.M4") | (mchannel.type=="C4.M4") |
					(mchannel.type=="C5.M4") | (mchannel.type=="C6.M4") | (mchannel.type=="C7.M4") | (mchannel.type=="C8.M4")
						//~ ) &  (mchannel.station =="A17") 
						) { 
					//~ std::cout << "enter data loop\n";
          //~ std::cout << "type: " << mchannel.type << " station: " << mchannel.station << "\n";

					oa->set_data(mchannel, macro_test.pid, macro_test.time);
					oa->getAutoParameters();
					//~ std::cout << " " << mchannel.forward_signal.size() << "\n";
					oa->get_calCoeff();
					//~ oa->print_calCoeff();
					//~ oa->print_data();
					double time1=0.0, tstart;tstart = clock();//timing
					oa->get_res();
					//~ time1 += clock() - tstart;time1 = time1/CLOCKS_PER_SEC; printf(" *** get_res time = %2.4f sec.\n",time1);
					//~ oa->print_res();
					std::string prefix;
					prefix = argv[1];
					//~ oa->write_res_dat(prefix + '_' + mchannel.type + '.' + mchannel.station + '.' + mchannel.section + ".dat" );//_C8.M4.  A17.  .L3
						std::stringstream strstream_name(mchannel.type);//C1.M1.A20.L3
						std::string C_str, M_str;
						getline(strstream_name, C_str, '.');
						getline(strstream_name, M_str, '.');
					oa->write_res_dat( mchannel.station + '.' + mchannel.section + '.' + M_str + '.' + C_str + '_' + prefix + ".dat" );//A17.L3.M2.C1_l
					
					//~ oa->writejson();
					
					//~ for (auto value:mchannel.forward_signal) {
						//~ std::cout << " " << value;
					//~ }
					//~ std::cout << "\n";
				}
			}
		} 
    delete(mpd2);
	}
	std::cout << "finished all files" << std::endl;
	//~ std::string jsonfilename = argv[1];
	//~ jsonfilename = jsonfilename + ".json";
	//~ oa->savejson(jsonfilename);
    return 0;	
}
//*/


//~ int main(int argc, char *argv[])
//~ {
	//~ OnlineAnalysis * oa = new OnlineAnalysis;
	//~ oa->getParameters("XFEL.RF.A20.L3.M1.C1.json");
	//~ oa->set_data("../../data_set.json");
	//~ oa->get_calCoeff();
	//~ oa->print_calCoeff();
	//~ oa->get_res();
	
	//~ return 0;
//~ }
