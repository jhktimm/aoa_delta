#include <ChimeraTK/ApplicationCore/ApplicationCore.h>
#include <ChimeraTK/ApplicationCore/PeriodicTrigger.h>

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "../include/OnlineAnalysis.h"

#include <time.h>

//~ #include <time.h>
//~ #include <jsoncpp/json/json.h>
//~ #include <unistd.h>//for sleep

namespace ctk = ChimeraTK;

bool run_flag=true;
bool daq = true;

struct Controller : public ctk::ApplicationModule {
    using ctk::ApplicationModule::ApplicationModule;

  CavitySignals casi{this, "tableParameters", "..."};
  MainTableParameters mtp{this, "maintableParameters", "..."};

	void mainLoop() {
		int samples = 16384;int div = 1;//samples divider		
		
		//~ int samples = 1820;		int div = 9;//samples divider		
		//~ int samples = 101;		int div = 9;//samples divider		

		uint refresh = 4;
		uint save_residual_every =	10*60-1;//saves residual to json every x events
		time_t rawtime;
		time(&rawtime);
		std::string st = ctime(&rawtime);
		std::string json_filename_prefix = "residual_" + std::to_string(rawtime) + '_';
	
		//~ OnlineAnalysis * oa = new OnlineAnalysis(samples);
		//~ OnlineAnalysis * oa = new OnlineAnalysis(samples, div);
		OnlineAnalysis * oa = new OnlineAnalysis();
		oa->init(samples, div);
// 		oa->getParameters("../dmap_files/XFEL.RF.A20.L3.M1.C1.json");
                oa->getAutoParameters("../tau_k_x/");
		oa->print_Parameters();
		//~ oa->set_data("../data/data_set.json");// !!!!!!!!!!!!!!!!!!!!!!!!!!!
		//~ oa->FS = 1;
// 		oa->get_calCoeff();
// 		oa->print_calCoeff();		
		std::cout << "bevor" << std::endl; 
// 		oa->get_res();	
// 		oa->print_res();
		std::cout << "after" << std::endl; 
		

		casi.readAll();
		mtp.readAll();
		oa->set_data(&casi, &mtp);
// 		oa->getAutoParameters();
				
		oa->get_calCoeff();		
		oa->print_calCoeff();
                oa->print_calCoeff();
		uint file_iterator = 0;
		uint event_iterator = 0;
		while (run_flag)
		{
			std::cout << "     ***** Event " << event_iterator << " from " << save_residual_every << " to analys. *****\n";
			casi.readAll();			
			oa->test_signal_consistence(&casi);
			mtp.readAll();
			oa->set_data(&casi, &mtp);
			
			//~ oa->jsondaq();
			
			oa->print_data();
			
			double time1=0.0, tstart;tstart = clock();//timing
			oa->get_res();std::cout << "after" << std::endl;
			time1 += clock() - tstart;time1 = time1/CLOCKS_PER_SEC; printf(" *** get_res time = %2.4f sec.\n",time1);
			oa->print_res();
// 			oa->writejson();			
			event_iterator++;
			if (event_iterator > save_residual_every) {
				event_iterator=0;
				file_iterator++;
// 				oa->savejson(json_filename_prefix + std::to_string(file_iterator) + ".json");
// 				oa->save_bit("daq_" + json_filename_prefix + std::to_string(file_iterator) + ".bit");
				//~ oa->save_daq_json( "daq_" + json_filename_prefix + std::to_string(file_iterator) + ".json");				
			} else if (event_iterator > refresh) {
// 				oa->save_bit("daq_" + json_filename_prefix + std::to_string(file_iterator) + ".bit");				
			}
		}
// 		oa->save_bit("daq_" + json_filename_prefix + std::to_string(file_iterator) + ".bit");
		file_iterator++;
// 		oa->savejson(json_filename_prefix + std::to_string(file_iterator) + ".json");
		//~ oa->save_daq_json("daq_" + json_filename_prefix + std::to_string(file_iterator) + ".json");
            delete(oa);
	}
};


 struct ExampleApp : public ctk::Application {
     ExampleApp() : Application("exampleApp") {}
     ~ExampleApp() { 
			run_flag=false; 
			usleep(500000);
			shutdown(); 
		}
     Controller controller{this, "Controller", "The Controller"};

	ctk::DeviceModule cavity_device{this, "cavity"};
// 	ctk::DeviceModule cavity_device{"cavity"};
// 	ctk::DeviceModule mainmodule {"mainmodule"};
	ctk::DeviceModule mainmodule {this, "mainmodule"};
	
     void defineConnections();
 };
 static ExampleApp theExampleApp;


 void ExampleApp::defineConnections() {
     ChimeraTK::setDMapFilePath("aoa.dmap");

     controller.mtp.findTag("MTC").connectTo(mainmodule);

     cavity_device("NAME") >> controller.casi.cavity_name;
     cavity_device("PROBE.AMPL",ChimeraTK::UpdateMode::push) >> controller.casi.probe_ampl;
     cavity_device("PROBE.PHASE",ChimeraTK::UpdateMode::push) >> controller.casi.probe_phase;
     cavity_device("VFORW.AMPL",ChimeraTK::UpdateMode::push) >> controller.casi.vforw_ampl;
     cavity_device("VFORW.PHASE",ChimeraTK::UpdateMode::push) >> controller.casi.vforw_phase;
     cavity_device("VREFL.AMPL",ChimeraTK::UpdateMode::push) >> controller.casi.vrefl_ampl;
     cavity_device("VREFL.PHASE",ChimeraTK::UpdateMode::push) >> controller.casi.vrefl_phase;

 }
