#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
//~ #include "doocs_snapdaq_llrf_datasclass.h"
#include "../include/aoa_daq_datasclass.h"

int main(int argc, char *argv[])
//~ int main()
{
	/*std::cout << " open file example_data.bit\n";
    std::ifstream ftestin("example_data.bit", std::ifstream::binary);    
    //~ std::vector<macro_pulse>* macro_pulses_in = new std::vector<macro_pulse>;  
    doocs_snapdaq_llrf_dataclass* mpd = new doocs_snapdaq_llrf_dataclass;

	ftestin >> *mpd;
	//~ ftestin >> *macro_pulses_in;
	//~ ftestin >> mpd->mps; 
    
    ftestin.close();
    
    std::cout << "size: " << mpd->mps.size() << "\n";    
    //~ std::cout << "size: " << macro_pulses_in->size() << "\n";    

	//~ macro_pulses_in->at(0).print();    

    int iiter =0;
    
    //~ for (auto &macro_test : *macro_pulses_in) {
    for (auto macro_test : mpd->mps) {
		//~ std::cout << "pid: " << macro_pulses_in->at(iiter).pid << "\n";
		std::cout << "pid: " << macro_test.pid << "\n";
		//~ std::cout << "type: " << macro_pulses_in->at(iiter).channel.at(0).type << "\n";
		//~ std::cout << "doocschannel: " << macro_pulses_in->at(iiter).channel.at(0).doocschannel << "\n";
		std::cout << "doocschannel: " << macro_test.channel.at(0).doocschannel << "\n";
		//~ std::cout << "doocschannel.size: " << macro_pulses_in->at(iiter).channel.size() << "\n";
		//~ for (auto mt_channel: macro_test.channel) {
			//~ std::cout << "doocschannel:" << mt_channel.doocschannel << "\n";
			//~ for (auto pa: mt_channel.forward_signal) {
				//~ std::cout << " " << pa;
			//~ }
			
		//~ }
		//~ doocs_snapdaq_data_channel dtest = macro_pulses_in->at(iiter).channel.at(0);
		//~ std::cout << "section: " << dtest.section << "\n";
		iiter++;
	}
	*/
	
	
	
	//~ doocs_snapdaq_llrf_dataclass* mpd2 = new doocs_snapdaq_llrf_dataclass("example_data.bit");
	std::cout << "open file " << argv[1] << "\n";
	//~ doocs_snapdaq_llrf_dataclass* mpd2 = new doocs_snapdaq_llrf_dataclass(argv[1]);
	aoa_daq_datasclass* mpd2 = new aoa_daq_datasclass(argv[1]);
	std::cout << "size of a sample: " << mpd2->mps.at(0).channel.at(0).forward_signal.size() << "\n";
	for (auto macro_test : mpd2->mps) {
		std::cout << "pid: " << macro_test.pid << "\n";
		for (auto mchannel: macro_test.channel){
			//~ if (mchannel.type=="C1.M1") { 
				std::cout << mchannel.doocschannel;
				std::cout << " " << mchannel.forward_signal.size() << ":\n";
				
				for (auto value:mchannel.forward_signal) {
					std::cout << " " << value;
				}
				std::cout << "\n";
			//~ }
		}
	}
	
    return 0;
}
