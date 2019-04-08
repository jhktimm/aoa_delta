/*
 * OnlineAnalysis.h
 * 
 * Copyright 2019 jan.horst.karl.timm@desy.de <jhktimm@xfelvdev2>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef ONLINEANALYSIS_H
#define ONLINEANALYSIS_H

#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <sstream>
#include "../matlab_code/f_calib_and_res_gen_ukf.h"

//~ #include "f_generate_online_parityRes1.h"
//~ #include "f_generate_online_parityRes2.h"
//~ #include "f_generate_online_UKF_residual.h"

//~ #include "f_generate_online_UKF_residual.old2.h"
//~ #include "f_generate_online_UKF_residual.false.h"
//~ #include "f_get_calCoeff_codegen.h"

//~ #include "../doocs_snapdaq_llrf_datasclass.h"
#include "../include/aoa_daq_datasclass.h"



#include <ChimeraTK/ApplicationCore/ApplicationCore.h>
//#include <ApplicationCore.h>

bool operator==(std::vector<double> const& lhs, ChimeraTK::ArrayPushInput<double> & rhs){
    if(lhs.size() != rhs.getNElements()){
        return false;
    }
    for(std::size_t i = 0; i < lhs.size(); ++i){
        if(lhs.at(i) != rhs[i]){
            return false;
        }
    }
    return true;
}



  struct MainTableParameters : public ChimeraTK::VariableGroup {
	using ChimeraTK::VariableGroup::VariableGroup;
	  ChimeraTK::ScalarPollInput<float> fs{this, "FS", "", "...", {"MTC"}};
	  ChimeraTK::ScalarPollInput<float> f0{this, "F0", "", "...", {"MTC"}};  
	  ChimeraTK::ScalarPollInput<float> delay{this, "PULSE_DELAY", "", "...", {"MTC"}};
	  ChimeraTK::ScalarPollInput<float> filling{this, "PULSE_FILLING", "", "...", {"MTC"}};
	  ChimeraTK::ScalarPollInput<float> flattop{this, "PULSE_FLATTOP", "", "...", {"MTC"}};  
	  ChimeraTK::ScalarPollInput<long> pid{this, "MACRO_PULSE_NUMBER", "", "...", {"MTC"}};
	};

struct CavitySignals : public ChimeraTK::VariableGroup {
using ChimeraTK::VariableGroup::VariableGroup;
  ChimeraTK::ScalarPollInput<std::string> cavity_name{this, "NAME", "", "...", {"TC"} };
  ChimeraTK::ArrayPushInput<double> probe_ampl{this, "PROBE.AMPL" , "", 16384,"testcavity", {"TC"}};
  ChimeraTK::ArrayPushInput<double> probe_phase{this, "PROBE.PHASE" , "", 16384,"testcavity", {"TC"}};
  ChimeraTK::ArrayPushInput<double> vforw_ampl{this, "VFORW.AMPL" , "", 16384,"testcavity", {"TC"}};
  ChimeraTK::ArrayPushInput<double> vforw_phase{this, "VFORW.PHASE" , "", 16384,"testcavity", {"TC"}};
  ChimeraTK::ArrayPushInput<double> vrefl_ampl{this, "VREFL.AMPL" , "", 16384,"testcavity", {"TC"}};
  ChimeraTK::ArrayPushInput<double> vrefl_phase{this, "VREFL.PHASE" , "", 16384,"testcavity", {"TC"}};  
  
};

class OnlineAnalysis
{
	public:
		OnlineAnalysis();
		OnlineAnalysis(int samples);
		OnlineAnalysis(int samples, int div);
		virtual ~OnlineAnalysis();
	
		//~ void getParameters(std::string jsonfilename, double tau_m[4], double K_m[4], double X0[4] );
		void getParameters(std::string jsonfilename);
		void getAutoParameters();/// Getting Parameters tau_m, K_m and X0 from jsonfile. json Filename is generated autamatic from live data. call readAll()( or cavity_name.read() or something like that) AND set_data first!
		void print_Parameters();
    
		void set_data(std::string jsonfilename);
		void set_data(doocs_snapdaq_data_channel dc);
		void set_data(doocs_snapdaq_data_channel dc, uint pid, double time);/// use this, if you want to overwrite delay, flattop, filling, fs=1 !, f0 and pid
		//~ void set_data(aoa_daq_channel dc);
		void set_data(CavitySignals *cs, MainTableParameters* mtp);
		void print_data();
		
		void test_signal_consistence(CavitySignals *cs);
		
		void get_res();
		void print_res();
		
		void get_calCoeff();
		void print_calCoeff();
		
		void writejson();
		void writeappjson(std::string filename);
		void savejson(std::string filename);
		
		void write_res_dat(std::string filename);

		void save_daq_json(std::string filename);
		void jsondaq();
		
		void save_bit(std::string filename);
		//~ CavitySignals cs;
		
		double FS;
		
	private:
		void init();
	
		aoa_daq_datasclass* data = new aoa_daq_datasclass;
		
		doocs_snapdaq_data_channel channel;
		
		Json::Value jsonstream;
		Json::Value json_daq_stream;
	
		std::vector<double> tmp_probe_ampl;
		std::vector<double> tmp_probe_phase;
		std::vector<double> tmp_vforw_ampl;
		std::vector<double> tmp_vforw_phase;
		std::vector<double> tmp_vrefl_ampl;
		std::vector<double> tmp_vrefl_phase;
	
		double tau_m[4];
		double K_m[4];
		double X0[4];
	
		double residual_ukf[6];
		double residual_ukf_mean[6];
		double residual_ukf_Variance[12];
		
		uint samples;
		int div;
		
		std::string NAME;

		double DELAY;
		double FILLING;
		double FLATTOP;
		double PID;
		double TIME;
		//~ double FS;
		double F0;
		emxArray_real_T *Probe_Ampl;
		emxArray_real_T *Probe_Phase;
		emxArray_real_T *Forw_Ampl;
		emxArray_real_T *Forw_Phase;
		emxArray_real_T *Refl_Ampl;
		emxArray_real_T *Refl_Phase;
			
		
		creal_T calCoeff[4];
		creal_T j_calCoeff[4];
		/* add your private declarations */
};

#endif /* ONLINEANALYSIS_H */ 
