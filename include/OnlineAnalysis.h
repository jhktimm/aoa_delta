/*
 * OnlineAnalysis.h
 * 
 * 2019 jan.horst.karl.timm@desy.de <jhktimm@xfelvdev2>
 * 
 * 
 */


#ifndef ONLINEANALYSIS_H
#define ONLINEANALYSIS_H

#include "AAnalysis.h"

#include <jsoncpp/json/json.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <sstream>

#include <ChimeraTK/ApplicationCore/ApplicationCore.h>

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

class OnlineAnalysis : public AAnalysis
{ 
	public:
	OnlineAnalysis(int samples, int div) : AAnalysis(samples, div) {}
	OnlineAnalysis() : AAnalysis() {}
	using AAnalysis::set_data;
	void set_data(CavitySignals *cs, MainTableParameters* mtp)
	{
		this->channel.probe_signal.clear();
		this->channel.probe_phase.clear();
		this->channel.forward_signal.clear();
		this->channel.forward_phase.clear();
		this->channel.reflected_signal.clear();
		this->channel.reflected_phase.clear();
		for (uint i = 0; i < this->samples; i = i + 1) {
			
			this->Probe_Ampl->data[i]  = cs->probe_ampl[i];
			this->Probe_Phase->data[i] = cs->probe_phase[i];
			this->Forw_Ampl->data[i]   = cs->vforw_ampl[i];
			this->Forw_Phase->data[i]  = cs->vforw_phase[i];
			this->Refl_Ampl->data[i]   = cs->vrefl_ampl[i];
			this->Refl_Phase->data[i]  = cs->vrefl_phase[i];
				this->channel.probe_signal.push_back(cs->probe_ampl[i]);
				this->channel.probe_phase.push_back(cs->probe_phase[i]);
				this->channel.forward_signal.push_back(cs->vforw_ampl[i]);
				this->channel.forward_phase.push_back(cs->vforw_phase[i]);
				this->channel.reflected_signal.push_back(cs->vrefl_ampl[i]);
				this->channel.reflected_phase.push_back(cs->vrefl_phase[i]);
		}	
		this->NAME			= cs->cavity_name;	
		this->DELAY       =  mtp->delay;
		this->FILLING     =  mtp->filling;
		this->FLATTOP     =  mtp->flattop;
		this->FS          =  mtp->fs;
		this->F0          =  mtp->f0;
		this->PID         =  mtp->pid;
		this->TIME         =  0;//mtp->time nned to be implemented!!!!!!!!!!!!!!!!!!!!!
		this->channel.doocschannel= cs->cavity_name;//ist eigentlich nicht der voller doocschannel
		std::stringstream strstream_name(this->NAME);//C1.M1.A20.L3
		std::string C_str, M_str, A_str, L_str;
		getline(strstream_name, C_str, '.');
		getline(strstream_name, M_str, '.');
		getline(strstream_name, A_str, '.');	
		getline(strstream_name, L_str, '.');	
		this->channel.section = M_str + '.' + L_str;
		this->channel.station = A_str;
		this->channel.type = C_str;
		//~ this->NAME    = dc.type + '.' + dc.station + '.' + dc.section;// z.B. C4.M2. A17. L3

	//~ .M1.L3 section
	//~ A17 station
	//~ C1 type
		
		this->channel.delay       =  mtp->delay;
		this->channel.filling     =  mtp->filling;
		this->channel.flattop     =  mtp->flattop;
		this->channel.fs          =  mtp->fs;
		this->channel.f0          =  mtp->f0;
		
		macro_pulse* mp = new macro_pulse();
		mp->channel.push_back(this->channel);
		mp->pid = mtp->pid;
		this->data->mps.push_back(*mp);
	}
	
	void test_signal_consistence(CavitySignals *cs)
	{
		if(this->tmp_probe_ampl == cs->probe_ampl) std::cout << "arsch\n";
		if(this->tmp_probe_phase == cs->probe_phase) std::cout << "arsch\n";
		if(this->tmp_vforw_ampl == cs->vforw_ampl) std::cout << "arsch\n";
		if(this->tmp_vforw_phase == cs->vforw_phase) std::cout << "arsch\n";
		if(this->tmp_vrefl_ampl == cs->vrefl_ampl) std::cout << "arsch\n";
		if(this->tmp_vrefl_phase == cs->vrefl_phase) std::cout << "arsch\n";

		this->tmp_probe_ampl.clear();
		this->tmp_probe_phase.clear();
		this->tmp_vforw_ampl.clear();
		this->tmp_vforw_phase.clear();
		this->tmp_vrefl_ampl.clear();
		this->tmp_vrefl_phase.clear();
		for (uint i = 0; i < this->samples; i++) {		
			this->tmp_probe_ampl.push_back( cs->probe_ampl[i]);
			this->tmp_probe_phase.push_back( cs->probe_phase[i]);
			this->tmp_vforw_ampl.push_back( cs->vforw_ampl[i]);
			this->tmp_vforw_phase.push_back( cs->vforw_phase[i]);
			this->tmp_vrefl_ampl.push_back( cs->vrefl_ampl[i]);
			this->tmp_vrefl_phase.push_back( cs->vrefl_phase[i]);
		}	
	}

};

#endif /* ONLINEANALYSIS_H */ 
