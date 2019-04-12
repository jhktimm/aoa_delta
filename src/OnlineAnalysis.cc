/*
 * OnlineAnalysis.cpp
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include "../include/OnlineAnalysis.h"


OnlineAnalysis::OnlineAnalysis()
{
	this->samples = 16384;
	this->div = 1;
	this->init();
}

OnlineAnalysis::OnlineAnalysis(int samp, int div)
{
	this->samples = samp;//adresse
	this->div = div;
	std::cout << "samples set to: " << this->samples << "\n";
	std::cout << "div set to: " << this->div << "\n";
	this->init();
}

OnlineAnalysis::OnlineAnalysis(int samp)
{
	this->samples = samp;//adresse
	std::cout << "samples set to: " << this->samples << "\n";
	std::cout << "DO NOT USE THIS FUNCTION! IT WILL BE ...\n";
	this->init();
}


OnlineAnalysis::~OnlineAnalysis()
{
  delete data;
}

void OnlineAnalysis::init()
{
	static int iv0[1] = { (int) this->samples };
	
	this->Probe_Ampl = emxCreateND_real_T(1, iv0);
	this->Probe_Phase = emxCreateND_real_T(1, iv0);
	this->Forw_Ampl = emxCreateND_real_T(1, iv0);
	this->Forw_Phase = emxCreateND_real_T(1, iv0);
	this->Refl_Ampl = emxCreateND_real_T(1, iv0);
	this->Refl_Phase = emxCreateND_real_T(1, iv0);
	
	for (int idx0 = 0; idx0 < Probe_Ampl->size[0U]; idx0++) {
		this->Probe_Ampl->data[idx0] = 0;
		this->Probe_Phase->data[idx0] = 0;
		this->Forw_Ampl->data[idx0] = 0;
		this->Forw_Phase->data[idx0] = 0;
		this->Refl_Ampl->data[idx0] = 0;
		this->Refl_Phase->data[idx0] = 0;
	}
	
	for (int i = 0; i < 4; i++ ) {
		this->calCoeff[i].im  = 0;
		this->calCoeff[i].re  = 0;
	}
	//~ this->tmp_probe_ampl->reserve(samp);
	//~ this->tmp_probe_phase->reserve(samp);
	//~ this->tmp_vforw_ampl->reserve(samp);
	//~ this->tmp_vforw_phase->reserve(samp);
	//~ this->tmp_vrefl_ampl->reserve(samp);
	//~ this->tmp_vrefl_phase->reserve(samp);
}

//~ void OnlineAnalysis::getParameters(std::string jsonfilename, double tau_m[4], double K_m[4], double X0[4])
void OnlineAnalysis::getParameters(std::string jsonfilename)
{
		std::ifstream jsonfile(jsonfilename);
		if (jsonfile.is_open()) {		
			Json::Reader reader;
			Json::Value obj;
			reader.parse(jsonfile, obj);
			const Json::Value j_tau_m = obj["tau_m"];
			const Json::Value j_K_m = obj["K_m"];
			const Json::Value j_X0 = obj["X0"];
	  
			for ( uint index = 0; index < j_tau_m.size(); ++index ) {
				this->tau_m[index] = j_tau_m[index].asDouble();
				this->K_m[index] = j_K_m[index].asDouble();
				this->X0[index] = j_X0[index].asDouble();
			}
		} else {
			std::cout << "!!!!!     Error opening file:" << jsonfilename << "\n";
			std::cout << "!!!!!     tau_m, K_m and X0 set to:/n";
			double t[4] = {0.0001540832871932599,0.00021662815104381899,0.00020796093478067394,0.00018335802017938494};
			double k[4] = { 27.0017421067048,-6.7881026325577114,-19.883832901443135,53.344675600530827 };
			double x[4] = { 359919.45138667425,-3.7594839458641172E+6,5.4300091097390065E+6,-2.0331664354777546E+6 };
			for (int i=0;i<4;i++){
				this->tau_m[i] = t[i];
				this->K_m[i] = k[i];
				this->X0[i] = x[i];
			}
			
		}
		//~ std::cout << "tau: " << this->tau_m[0] << " " << this->tau_m[1]<< " " << this->tau_m[2]<< " " << this->tau_m[3]<< "\n";
		//~ std::cout << "K_m: " << this->K_m[0]   << " " << this->K_m[1]  << " " << this->K_m[2]  << " " << this->K_m[3]  << "\n";
		//~ std::cout << "X0: "  << this->X0[0]    << " " << this->X0[1]   << " " << this->X0[2]   << " " << this->X0[3]   << "\n";
}

void OnlineAnalysis::print_Parameters()
{
  std::cout << "tau: " << this->tau_m[0] << " " << this->tau_m[1]<< " " << this->tau_m[2]<< " " << this->tau_m[3]<< "\n";
  std::cout << "K_m: " << this->K_m[0]   << " " << this->K_m[1]  << " " << this->K_m[2]  << " " << this->K_m[3]  << "\n";
  std::cout << "X0: "  << this->X0[0]    << " " << this->X0[1]   << " " << this->X0[2]   << " " << this->X0[3]   << "\n";

}

void OnlineAnalysis::getAutoParameters(){
	std::stringstream strstream_name(this->NAME);//C1.M1.A20.L3
	std::string C_str, M_str, A_str, L_str;
	getline(strstream_name, C_str, '.');
	getline(strstream_name, M_str, '.');
	getline(strstream_name, A_str, '.');	
	getline(strstream_name, L_str, '.');	
	
	std::string jsonfilename = "../tau_k_x/XFEL.RF." + A_str + '.' + L_str + '.' + M_str + '.' + C_str + ".json";//XFEL.RF.A20.L3.M1.C1.json
	//~ std::cout << "OnlineAnalysis::getAutoParameters: " << jsonfilename << "\n";
	this->getParameters(jsonfilename);
}

void OnlineAnalysis::set_data(std::string jsonfilename)
{
	int div = this->div;
	std::ifstream ifs_data(jsonfilename);
	Json::Value obj_data;
	Json::Reader reader;
	reader.parse(ifs_data, obj_data);
	const Json::Value j_FA = obj_data["ForwAmpl"];
	const Json::Value j_FP = obj_data["ForwPhase"];
	const Json::Value j_RP = obj_data["ReflPhase"];
	const Json::Value j_RA = obj_data["ReflAmpl"];
	const Json::Value j_PP = obj_data["ProbePhase"];
	const Json::Value j_PA = obj_data["ProbeAmpl"];
	const Json::Value j_FS = obj_data["FS"];
	const Json::Value j_F0 = obj_data["F0"];
	const Json::Value j_DELAY= obj_data["DELAY"];
	const Json::Value j_FILLING = obj_data["FILLING"];
	const Json::Value j_FLATTOP = obj_data["FLATTOP"];
	const Json::Value j_NAME = obj_data["Name"];
	//~ double j_fs, j_f0, j_delay, j_filling, j_flattop;
	//for less samples
	this->FS      = j_FS.asDouble();
	this->F0      = j_F0.asDouble();
	this->DELAY   = j_DELAY.asDouble();
	this->FILLING = j_FILLING.asDouble();
	this->FLATTOP = j_FLATTOP.asDouble();
  this->NAME = j_NAME.asString();
	std::cout << "size of json data: " << j_FA.size() << std::endl;
	
	
	for (uint idx0 = 0; idx0 < this->samples; idx0 = idx0 + div) {
		this->Probe_Ampl->data[idx0/div] = j_PA[idx0].asDouble();					
		this->Probe_Phase->data[idx0/div] = j_PP[idx0].asDouble();
		this->Forw_Ampl->data[idx0/div] = j_FA[idx0].asDouble();
		this->Forw_Phase->data[idx0/div] = j_FP[idx0].asDouble();
		this->Refl_Ampl->data[idx0/div] = j_RA[idx0].asDouble();
		this->Refl_Phase->data[idx0/div] = j_RP[idx0].asDouble();
		//~ if( (idx0 < 340) && (idx0 > 300)) {
			//~ std::cout << "PA[" << idx0 << "]: " << Probe_Ampl->data[idx0/div] << "\n";
			//~ std::cout << "PP[" << idx0 << "]: " << Probe_Phase->data[idx0/div] << "\n";
			//~ std::cout << "FA[" << idx0 << "]: " << Forw_Ampl->data[idx0/div] << "\n";
			//~ std::cout << "FP[" << idx0 << "]: " << Forw_Phase->data[idx0/div] << "\n";
			//~ std::cout << "RA[" << idx0 << "]: " << Refl_Ampl->data[idx0/div] << "\n";
			//~ std::cout << "RP[" << idx0 << "]: " << Refl_Phase->data[idx0/div] << "\n";
		//~ }
	}
		//~ this->DELAY       =  20;
	//~ this->FILLING     =  750;
	//~ this->FLATTOP     =  650;
	//~ this->FS          =  9.027999878;
	//~ this->FS          =  1;
	//~ this->F0          =  1300;
	//~ this->PID         =  0;

}

void OnlineAnalysis::get_calCoeff()
{
	f_get_calCoeff_codegen(
		this->Probe_Ampl, 
		this->Probe_Phase, 
		this->Forw_Ampl, 
		this->Forw_Phase, 
		this->Refl_Ampl, 
		this->Refl_Phase, 
		this->DELAY,
		this->FILLING,
		this->FLATTOP, 
		this->FS,
		this->calCoeff);
	//~ this->print_calCoeff();
	
}

void OnlineAnalysis::print_calCoeff()
{
	std::cout << "calCoeff: "
		<< this->calCoeff[0].re << ": " << this->calCoeff[0].im << "\n"
		<< this->calCoeff[1].re << ": " << this->calCoeff[1].im << "\n"
		<< this->calCoeff[2].re << ": " << this->calCoeff[2].im << "\n"
		<< this->calCoeff[3].re << ": " << this->calCoeff[3].im << "\n";
}

void OnlineAnalysis::get_res()
{
	//~ this->print_data();
	
	f_calib_and_res_gen_ukf(
	//~ f_generate_online_UKF_residual(
		this->Probe_Ampl, 
		this->Probe_Phase, 
		this->Forw_Ampl, 
		this->Forw_Phase, 
		this->Refl_Ampl, 
		this->Refl_Phase, 
		this->FS, 
		this->F0, 
		this->tau_m, 
		this->K_m, 
		this->X0, 
		this->DELAY,
		this->FILLING, 
		this->FLATTOP, 
		this->residual_ukf, 
		this->residual_ukf_mean, 
		this->residual_ukf_Variance,
		this->calCoeff);

	//~ this->print_res();
}

void OnlineAnalysis::print_res()
{
	std::cout << "NAME: " << this->NAME << ", "
		<< std::setprecision(10) <<"PID: " 
		<< this->PID << " TIME: " 
		<< this->TIME << "\n"
		<< "residual_ukf: " 
		<< this->residual_ukf[0] << ", " 
		<< this->residual_ukf[1] << ", " 
		<< this->residual_ukf[2] << ", " 
		<< this->residual_ukf[3] << ", " 
		<< this->residual_ukf[4] << ", " 
		<< this->residual_ukf[5] << "   " 
		<< "residual_ukf_mean: " 
		<< this->residual_ukf_mean[0] << ", " 
		<< this->residual_ukf_mean[1] << ", " 
		<< this->residual_ukf_mean[2] << ", " 
		<< this->residual_ukf_mean[3] << ", " 
		<< this->residual_ukf_mean[4] << ", " 
		<< this->residual_ukf_mean[5] << "\n" 
		<< "residual_ukf_Variance: " 
		<< this->residual_ukf_Variance[0] << ", "
		<< this->residual_ukf_Variance[1] << ", "
		<< this->residual_ukf_Variance[2] << ", "
		<< this->residual_ukf_Variance[3] << ", "
		<< this->residual_ukf_Variance[4] << ", "
		<< this->residual_ukf_Variance[5] << ", "
		<< this->residual_ukf_Variance[6] << ", "
		<< this->residual_ukf_Variance[7] << ", "
		<< this->residual_ukf_Variance[8] << ", "
		<< this->residual_ukf_Variance[9] << ", "
		<< this->residual_ukf_Variance[10] <<", " 
		<< this->residual_ukf_Variance[11] << " "
		<< "\n";
}

void OnlineAnalysis::set_data(ttf2_daq_getdata* data)
{
    ///to get pid and time
  u_int evid, tup, tlow;
  int status;
  int statusch;
  u_int len;
  int evtype, nsrvb;
  if(data->GetEventInfo(&evid, &evtype, &len, &tup, &tlow, &status, &nsrvb)) {
    printf("ttf2_user_loop(): failed to get event info\n");
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
  for (uint i = 0; i < this->samples; i++) {
    this->Probe_Ampl->data[i]  = data->GetSpectVal(0, i);
    this->Probe_Phase->data[i] = data->GetSpectVal(1, i);
    this->Forw_Ampl->data[i]   = data->GetSpectVal(2, i);
    this->Forw_Phase->data[i]  = data->GetSpectVal(3, i);
    this->Refl_Ampl->data[i]   = data->GetSpectVal(4, i);
    this->Refl_Phase->data[i]  = data->GetSpectVal(5, i);
  }

	this->PID = evid;
	this->TIME = tup;
	this->DELAY       =  20;
	this->FILLING     =  750;
	this->FLATTOP     =  650;
	//~ this->FS          =  9.027999878;
	this->FS          =  1;
	this->F0          =  1300;
}

void OnlineAnalysis::set_data(CavitySignals *cs, MainTableParameters* mtp)
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

void OnlineAnalysis::set_data(doocs_snapdaq_data_channel dc, uint pid, double time)
{
	this->set_data(dc);
	
	this->PID = pid;
	this->TIME = time;
	this->DELAY       =  20;
	this->FILLING     =  750;
	this->FLATTOP     =  650;
	//~ this->FS          =  9.027999878;
	this->FS          =  1;
	this->F0          =  1300;
}

void OnlineAnalysis::set_data(doocs_snapdaq_data_channel dc ) 
//~ void OnlineAnalysis::set_data(aoa_daq_channel dc ) 
{

	if ( (this->samples==dc.probe_signal.size()) &
		(this->samples==dc.probe_phase.size()) &
		(this->samples==dc.forward_signal.size()) &
		(this->samples==dc.forward_phase.size()) &
		(this->samples==dc.reflected_signal.size()) &
		(this->samples==dc.reflected_phase.size()) 
	 ) {
	
		for (uint i = 0; i < this->samples; i++) {
			
			this->Probe_Ampl->data[i]  = dc.probe_signal.at(i);
			this->Probe_Phase->data[i] = dc.probe_phase.at(i);
			this->Forw_Ampl->data[i]   = dc.forward_signal.at(i);
			this->Forw_Phase->data[i]  = dc.forward_phase.at(i);
			this->Refl_Ampl->data[i]   = dc.reflected_signal.at(i);
			this->Refl_Phase->data[i]  = dc.reflected_phase.at(i);
		}	
	} else {
		std::cout << "data is not useable!!!!!! \n";
    
		std::cout << "name: " << dc.type + '.' + dc.station + '.' + dc.section << "\n";
		std::cout << "size for this->samples: " << this->samples << "\n";
		std::cout << "size for probe_signal: " << dc.probe_signal.size() << "\n";
		std::cout << "size for probe_phase: " << dc.probe_phase.size() << "\n";
		std::cout << "size for forward_signal: " << dc.forward_signal.size() << "\n";
		std::cout << "size for forward_phase: " << dc.forward_phase.size() << "\n";
		std::cout << "size for reflected_signal: " << dc.reflected_signal.size() << "\n";
		std::cout << "size for reflected_phase: " << dc.reflected_phase.size() << "\n";
	}
	this->DELAY   = dc.delay;
	this->FILLING = dc.filling;
	this->FLATTOP = dc.flattop;
	this->FS      = dc.fs;
	this->F0      = dc.f0;
	this->NAME    = dc.type + '.' + dc.station + '.' + dc.section;// z.B. C4.M2. A17. L3

//~ .M1.L3 section
//~ A17 station
//~ C1 type

	
}

void OnlineAnalysis::print_data()
{
	std::cout << "Data:"
		<< " delay: " << this->DELAY   
		<< " filling: " << this->FILLING 
		<< " flattop: " << this->FLATTOP 
		<< " fs: " << this->FS      
		<< " f0: " << this->F0      
		<< " pid: " << this->PID     
		<< " time: " << this->TIME     
		<< "\n";
    std::cout << "Sizes: "
		<< this->Probe_Ampl->size[0U] << " "
		<< this->Probe_Phase->size[0U] << " "
		<< this->Forw_Ampl->size[0U] << " "
		<< this->Forw_Phase->size[0U] << " "
		<< this->Refl_Ampl->size[0U] << " "
		<< this->Refl_Phase->size[0U] << "\n";
		
}

void OnlineAnalysis::test_signal_consistence(CavitySignals *cs)
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
	//~ if(this->tmp_probe_ampl == cs->probe_ampl) std::cout   << "po\n";
	//~ if(this->tmp_probe_phase == cs->probe_phase) std::cout << "po\n";
	//~ if(this->tmp_vforw_ampl == cs->vforw_ampl) std::cout   << "po\n";
	//~ if(this->tmp_vforw_phase == cs->vforw_phase) std::cout << "po\n";
	//~ if(this->tmp_vrefl_ampl == cs->vrefl_ampl) std::cout   << "po\n";
	//~ if(this->tmp_vrefl_phase == cs->vrefl_phase) std::cout << "po\n";
}

void OnlineAnalysis::jsondaq()
{
	Json::Value root;
	root["PID"]     = this->PID;
	root["TIME"]    = this->TIME;
	root["NAME"]    = this->NAME;
	root["DELAY"]   = this->DELAY  ;
	root["FILLING"] = this->FILLING;
	root["FLATTOP"] = this->FLATTOP;
	root["FS"]      = this->FS     ;
	root["F0"]      = this->F0     ;
	
	Json::Value jpa;
	Json::Value jpp;
	Json::Value jfp;
	Json::Value jfa;
	Json::Value jrp;
	Json::Value jra;
	for (uint i = 0; i < this->samples; i++) {		
		jpa.append(this->Probe_Ampl->data[i] );
		jpp.append(this->Probe_Phase->data[i]);
		jfp.append(this->Forw_Ampl->data[i]  );
		jfa.append(this->Forw_Phase->data[i] );
		jrp.append(this->Refl_Ampl->data[i]  );
		jra.append(this->Refl_Phase->data[i] );
	}
	root["PROBE.AMPL"]  = jpa;
	root["PROBE.PHASE"] = jpp;
	root["VFORW.AMPL"]  = jfa;
	root["VFORW.PHASE"] = jfp;
	root["VREFL.AMPL"]  = jra;
	root["VREFL.PHASE"] = jrp;
	json_daq_stream.append(root);
	
}

void OnlineAnalysis::writejson()
{
	Json::Value root;
	root["PID"] = this->PID;
	root["NAME"] = this->NAME;
	root["TIME"] = this->TIME;
	
	Json::Value res_array;
	res_array.append(this->residual_ukf[0]);
	res_array.append(this->residual_ukf[1]);
	res_array.append(this->residual_ukf[2]);
	res_array.append(this->residual_ukf[3]);
	res_array.append(this->residual_ukf[3]);
	res_array.append(this->residual_ukf[4]);
	res_array.append(this->residual_ukf[5]);
	root["residual_ukf"] = res_array;
	
	Json::Value mean_array;
	mean_array.append(this->residual_ukf_mean[0]);
	mean_array.append(this->residual_ukf_mean[1]);
	mean_array.append(this->residual_ukf_mean[2]);
	mean_array.append(this->residual_ukf_mean[3]);
	mean_array.append(this->residual_ukf_mean[4]);
	mean_array.append(this->residual_ukf_mean[5]);
	root["residual_ukf_mean"] = mean_array;
	
	Json::Value var_array;
	var_array.append(this->residual_ukf_Variance[0]);
	var_array.append(this->residual_ukf_Variance[1]);
	var_array.append(this->residual_ukf_Variance[2]);
	var_array.append(this->residual_ukf_Variance[3]);
	var_array.append(this->residual_ukf_Variance[4]);
	var_array.append(this->residual_ukf_Variance[5]);
	var_array.append(this->residual_ukf_Variance[6]);
	var_array.append(this->residual_ukf_Variance[7]);
	var_array.append(this->residual_ukf_Variance[8]);
	var_array.append(this->residual_ukf_Variance[9]);
	var_array.append(this->residual_ukf_Variance[10]);
	var_array.append(this->residual_ukf_Variance[11]);
	root["residual_ukf_Variance"] = var_array;


	jsonstream.append(root);
	
	//~ Json::StyledWriter style_root;
	//~ Json::FastWriter fast_root;
	//~ std::cout << root << std::endl;
	//~ std::cout << style_root.write( root ) << std::endl;
	//~ std::cout << fast_root.write( root ) << std::endl;
}

void OnlineAnalysis::writeappjson(std::string filename)
{
	Json::Value root;
	root["PID"] = this->PID;
	root["NAME"] = this->NAME;
	root["TIME"] = this->TIME;
	
	Json::Value res_array;
	res_array.append(this->residual_ukf[0]);
	res_array.append(this->residual_ukf[1]);
	res_array.append(this->residual_ukf[2]);
	res_array.append(this->residual_ukf[3]);
	res_array.append(this->residual_ukf[3]);
	res_array.append(this->residual_ukf[4]);
	res_array.append(this->residual_ukf[5]);
	root["residual_ukf"] = res_array;
	
	Json::Value mean_array;
	mean_array.append(this->residual_ukf_mean[0]);
	mean_array.append(this->residual_ukf_mean[1]);
	mean_array.append(this->residual_ukf_mean[2]);
	mean_array.append(this->residual_ukf_mean[3]);
	mean_array.append(this->residual_ukf_mean[4]);
	mean_array.append(this->residual_ukf_mean[5]);
	root["residual_ukf_mean"] = mean_array;
	
	Json::Value var_array;
	var_array.append(this->residual_ukf_Variance[0]);
	var_array.append(this->residual_ukf_Variance[1]);
	var_array.append(this->residual_ukf_Variance[2]);
	var_array.append(this->residual_ukf_Variance[3]);
	var_array.append(this->residual_ukf_Variance[4]);
	var_array.append(this->residual_ukf_Variance[5]);
	var_array.append(this->residual_ukf_Variance[6]);
	var_array.append(this->residual_ukf_Variance[7]);
	var_array.append(this->residual_ukf_Variance[8]);
	var_array.append(this->residual_ukf_Variance[9]);
	var_array.append(this->residual_ukf_Variance[10]);
	var_array.append(this->residual_ukf_Variance[11]);
	root["residual_ukf_Variance"] = var_array;

	std::fstream file_out(filename, std::fstream::in | std::fstream::out );
	if(!file_out.eof()){
		std::cout << " append \n";
		Json::Value json_file_stream;
		
		//~ Json::Reader reader;
		//~ reader.parse(file_out, json_file_stream);

		file_out >> json_file_stream;
		
		json_file_stream.append(root);
		file_out << json_file_stream;
		
    } else {		
		std::cout << " first time open\n"; 
		file_out << root;
	}
	file_out.close();
}

void OnlineAnalysis::write_res_dat(std::string filename)
{
	//~ std::cout << "write data to file: " << filename << "\n";
	std::fstream checkfileStream;
	checkfileStream.open(filename);
	bool is_first_time_open = checkfileStream.fail();
	checkfileStream.close();
	std::fstream file_out(filename, std::fstream::in | std::fstream::out | std::ofstream::app );
	if (is_first_time_open) {
		file_out 
		<< "PID"  << " " 
		<< "NAME"  << " " 
		<< "TIME"  << " " 
		<< "residual_ukf[0]"  << " " 
		<< "residual_ukf[1]"  << " " 
		<< "residual_ukf[2]"  << " " 
		<< "residual_ukf[3]"  << " " 
		<< "residual_ukf[3]"  << " " 
		<< "residual_ukf[4]"  << " " 
		<< "residual_ukf[5]"  << " " 
		<< "residual_ukf_mean[0]"  << " " 
		<< "residual_ukf_mean[1]"  << " " 
		<< "residual_ukf_mean[2]"  << " " 
		<< "residual_ukf_mean[3]"  << " " 
		<< "residual_ukf_mean[4]"  << " " 
		<< "residual_ukf_mean[5]"  << " " 
		<< "residual_ukf_Variance[0]" << " " 
		<< "residual_ukf_Variance[1]" << " " 
		<< "residual_ukf_Variance[2]" << " " 
		<< "residual_ukf_Variance[3]" << " " 
		<< "residual_ukf_Variance[4]" << " " 
		<< "residual_ukf_Variance[5]" << " " 
		<< "residual_ukf_Variance[6]" << " " 
		<< "residual_ukf_Variance[7]" << " " 
		<< "residual_ukf_Variance[8]" << " " 
		<< "residual_ukf_Variance[9]" << " " 
		<< "residual_ukf_Variance[10]" << " " 
		<< "residual_ukf_Variance[11]" << std::endl;
	}
	file_out << std::setprecision(16)
		<< this->PID                        << " " 
		<< this->NAME                       << " " 
		<< this->TIME                       << " " 
		<< this->residual_ukf[0]            << " " 
		<< this->residual_ukf[1]            << " " 
		<< this->residual_ukf[2]            << " " 
		<< this->residual_ukf[3]            << " " 
		//~ << this->residual_ukf[3]            << " " 
		<< this->residual_ukf[4]            << " " 
		<< this->residual_ukf[5]            << " " 
		<< this->residual_ukf_mean[0]       << " " 
		<< this->residual_ukf_mean[1]       << " " 
		<< this->residual_ukf_mean[2]       << " " 
		<< this->residual_ukf_mean[3]       << " " 
		<< this->residual_ukf_mean[4]       << " " 
		<< this->residual_ukf_mean[5]       << " " 
		<< this->residual_ukf_Variance[0]  << " " 
		<< this->residual_ukf_Variance[1]  << " " 
		<< this->residual_ukf_Variance[2]  << " " 
		<< this->residual_ukf_Variance[3]  << " " 
		<< this->residual_ukf_Variance[4]  << " " 
		<< this->residual_ukf_Variance[5]  << " " 
		<< this->residual_ukf_Variance[6]  << " " 
		<< this->residual_ukf_Variance[7]  << " " 
		<< this->residual_ukf_Variance[8]  << " " 
		<< this->residual_ukf_Variance[9]  << " " 
		<< this->residual_ukf_Variance[10] << " " 
		<< this->residual_ukf_Variance[11] << std::endl;
	file_out.close();
	
}

void OnlineAnalysis::save_daq_json(std::string filename)
{
	//~ std::cout << jsonstream << std::endl;	
	std::ofstream file_out(filename);
	file_out << json_daq_stream;
	file_out.close();
	json_daq_stream.clear();

}

void OnlineAnalysis::savejson(std::string filename)
{
	//~ std::cout << jsonstream << std::endl;	
	std::ofstream file_out(filename);
	file_out << jsonstream;
	file_out.close();
	jsonstream.clear();

}

void OnlineAnalysis::save_bit(std::string filename) 
{
	this->data->appwrite(filename);
	this->data->mps.clear();
}
