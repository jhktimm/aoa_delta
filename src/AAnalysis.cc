/*
 * AAnalysis.cpp
 * 
 * jan.horst.karl.timm@desy.de <jhktimm@xfelvdev2>
 * 
 */

#include "../include/AAnalysis.h"

AAnalysis::AAnalysis()
{
	this->samples = 16384;
	this->div = 1;
	this->init();
}

AAnalysis::AAnalysis(int samp, int div)
{
	this->samples = samp;//adresse
	this->div = div;
	
	this->init(samp,div);
}

AAnalysis::AAnalysis(int samp)
{
	this->samples = samp;//adresse
	std::cout << "samples set to: " << this->samples << "\n";
	std::cout << "DO NOT USE THIS FUNCTION! IT WILL BE ...\n";
	this->init();
}


AAnalysis::~AAnalysis()
{
  delete data;
}

void AAnalysis::init(int samp, int div)
{
	this->samples = samp;//adresse
	this->div = div;
	std::cout << "samples set to: " << this->samples << "\n";
	std::cout << "div set to: " << this->div << "\n";
	this->init();
}

void AAnalysis::init()
{
  
//  emxInitArray_creal_T(&r_cmplx, 1);
  emxInitArray_real_T(&s_max, 1);
  
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

//~ void AAnalysis::getParameters(std::string jsonfilename, double tau_m[4], double K_m[4], double X0[4])
void AAnalysis::getParameters(std::string jsonfilename)
{
		std::ifstream jsonfile(jsonfilename);
		if (jsonfile.is_open()) {		
			Json::Reader reader;
			Json::Value obj;
			reader.parse(jsonfile, obj);
			const Json::Value j_tau_m = obj["tau_m"];
			const Json::Value j_K_m = obj["K_m"];
			const Json::Value j_X0 = obj["X0"];
			const Json::Value j_QL_nom = obj["QL_nom"];
      this->QL_nom = j_QL_nom.asDouble();
			const Json::Value j_cal_coeff_real = obj["cal_coeff_real"];
			const Json::Value j_cal_coeff_imag = obj["cal_coeff_imag"];
      for (int idx0 = 0; idx0 < 4; idx0++) {
        calCoeff[idx0].re = j_cal_coeff_real[idx0].asDouble();
        calCoeff[idx0].im = j_cal_coeff_imag[idx0].asDouble();
      }
      
			const Json::Value j_Sigma_nom = obj["Sigma_nom"];
      this->Sigma_nom[0]=j_Sigma_nom[0][0].asDouble();
      this->Sigma_nom[1]=j_Sigma_nom[0][1].asDouble();
      this->Sigma_nom[2]=j_Sigma_nom[1][0].asDouble();
      this->Sigma_nom[3]=j_Sigma_nom[1][1].asDouble();
			const Json::Value j_MeasNoiseVar = obj["MeasNoiseVar"];
      this->MeasNoiseVar[0]=j_MeasNoiseVar[0][0].asDouble();
      this->MeasNoiseVar[1]=j_MeasNoiseVar[0][1].asDouble();
      this->MeasNoiseVar[2]=j_MeasNoiseVar[1][0].asDouble();
      this->MeasNoiseVar[3]=j_MeasNoiseVar[1][1].asDouble();
			const Json::Value j_r_mean_nom = obj["r_mean_nom"];
      this->r_mean_nom[0]=j_r_mean_nom[0].asDouble();
      this->r_mean_nom[1]=j_r_mean_nom[1].asDouble();
			const Json::Value j_ProcessVar = obj["ProcessVar"];
			for ( uint x = 0; x < 6; ++x ) {
        for ( uint y = 0; y < 6; ++y ) {
          this->ProcessVar[6*x+y]=j_ProcessVar[x][y].asDouble();     
        }
      }
      
			for ( uint index = 0; index < j_tau_m.size(); ++index ) {
				this->tau_m[index] = j_tau_m[index].asDouble();
				this->K_m[index] = j_K_m[index].asDouble();
				this->X0[index] = j_X0[index].asDouble();
			}
		} else {
			std::cout << "!!!!!     Error opening file:" << jsonfilename << "\n";
// 			std::cout << "!!!!!     tau_m, K_m and X0 set to:\n";
      this->QL_nom = 4.5452426058970168E+6;
      double s[4]= {2.7555539567360955E-5,-7.1685130309531256E-6,-7.1685130309531256E-6,2.8752891448382514E-5};
      double m[4]= {0.0001,0,0,0.0001};
			double t[4] = {0.0001540832871932599,0.00021662815104381899,0.00020796093478067394,0.00018335802017938494};
			double k[4] = { 27.0017421067048,-6.7881026325577114,-19.883832901443135,53.344675600530827 };
			double x[4] = { 359919.45138667425,-3.7594839458641172E+6,5.4300091097390065E+6,-2.0331664354777546E+6 };
			for (int i=0;i<4;i++){
				this->tau_m[i] = t[i];
				this->K_m[i] = k[i];
				this->X0[i] = x[i];
        this->Sigma_nom[i] = s[i];
        this->MeasNoiseVar[i] = m[i];
			}
			this->r_mean_nom[0]=0.0027705769790225682;
			this->r_mean_nom[1]= -1 * 0.0020281930252110526;
      for ( uint x = 0; x < 6; ++x ) {
        for ( uint y = 0; y < 6; ++y ) {
          if (x==y) {
            this->ProcessVar[6*x+y]=0.0001;
          } else {
            this->ProcessVar[6*x+y]=0;     
          }
        }
      }      
//       this->print_Parameters();
		}
		//~ std::cout << "tau: " << this->tau_m[0] << " " << this->tau_m[1]<< " " << this->tau_m[2]<< " " << this->tau_m[3]<< "\n";
		//~ std::cout << "K_m: " << this->K_m[0]   << " " << this->K_m[1]  << " " << this->K_m[2]  << " " << this->K_m[3]  << "\n";
		//~ std::cout << "X0: "  << this->X0[0]    << " " << this->X0[1]   << " " << this->X0[2]   << " " << this->X0[3]   << "\n";
}

void AAnalysis::print_Parameters()
{
  print_calCoeff();
  std::cout << "tau: " << this->tau_m[0] << " " << this->tau_m[1]<< " " << this->tau_m[2]<< " " << this->tau_m[3]<< "\n";
  std::cout << "K_m: " << this->K_m[0]   << " " << this->K_m[1]  << " " << this->K_m[2]  << " " << this->K_m[3]  << "\n";
  std::cout << "X0: "  << this->X0[0]    << " " << this->X0[1]   << " " << this->X0[2]   << " " << this->X0[3]   << "\n";
  std::cout << "r_mean_nom: "  << this->r_mean_nom[0]    << " " << this->r_mean_nom[1] << "\n";
  for ( uint i = 0; i < 4; ++i ) {
    std::cout << " Sigma_nom[" << i << "]: " << Sigma_nom[i] << "\n";
    std::cout << " MeasNoiseVar[" << i << "]: " << MeasNoiseVar[i] << "\n";
  }
  std::cout << "ProcessVar: ";
  for ( uint x = 0; x < 6; ++x ) {
    for ( uint y = 0; y < 6; ++y ) {
      std::cout <<  " "<< 6*x+y <<": " << this->ProcessVar[6*x+y] << " ";          
    }
    std::cout << "\n          ";
  }
  std::cout << "\n";

}

void AAnalysis::getAutoParameters(std::string tauKXdir){
  std::stringstream strstream_name(this->NAME);//C1.M1.A20.L3
	std::string C_str, M_str, A_str, L_str;
	getline(strstream_name, C_str, '.');
	getline(strstream_name, M_str, '.');
	getline(strstream_name, A_str, '.');	
	getline(strstream_name, L_str, '.');	
	
	std::string jsonfilename = tauKXdir + "XFEL.RF." + A_str + '.' + L_str + '.' + M_str + '.' + C_str + "_nomPara" + ".json";//XFEL.RF.A20.L3.M1.C1.json
	//~ std::cout << "AAnalysis::getAutoParameters: " << jsonfilename << "\n";
	this->getParameters(jsonfilename);
}

void AAnalysis::getAutoParameters(){
  this->getAutoParameters("../tau_k_x/");
	//~ std::stringstream strstream_name(this->NAME);//C1.M1.A20.L3
	//~ std::string C_str, M_str, A_str, L_str;
	//~ getline(strstream_name, C_str, '.');
	//~ getline(strstream_name, M_str, '.');
	//~ getline(strstream_name, A_str, '.');	
	//~ getline(strstream_name, L_str, '.');	
	
	//~ std::string jsonfilename = "../tau_k_x/XFEL.RF." + A_str + '.' + L_str + '.' + M_str + '.' + C_str + ".json";//XFEL.RF.A20.L3.M1.C1.json
	//~ std::cout << "AAnalysis::getAutoParameters: " << jsonfilename << "\n";
	//~ this->getParameters(jsonfilename);
}

void AAnalysis::set_data(std::string jsonfilename)
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

void AAnalysis::get_calCoeff()
{
  std::cout << "DO NOT USE!!!!!\n";
// 	f_get_calCoeff_codegen(
// 		this->Probe_Ampl, 
// 		this->Probe_Phase, 
// 		this->Forw_Ampl, 
// 		this->Forw_Phase, 
// 		this->Refl_Ampl, 
// 		this->Refl_Phase, 
// 		this->DELAY,
// 		this->FILLING,
// 		this->FLATTOP, 
// 		this->FS,
// 		this->calCoeff);
	//~ this->print_calCoeff();
	
}

void AAnalysis::print_calCoeff()
{
	std::cout << "calCoeff: "
		<< this->calCoeff[0].re << ": " << this->calCoeff[0].im << "\n"
		<< this->calCoeff[1].re << ": " << this->calCoeff[1].im << "\n"
		<< this->calCoeff[2].re << ": " << this->calCoeff[2].im << "\n"
		<< this->calCoeff[3].re << ": " << this->calCoeff[3].im << "\n";
}

void AAnalysis::get_res()
{

	//~ this->print_data();
  if (this->Forw_Ampl->data[1000] < 5) {
    this->FLAG=true;
    std::cout << "FLAG! cavity "<< this->NAME <<" at pid " << this->PID << " could be off.";
  } else {
    this->FLAG=false;
    f_generate_and_eval_residual(
      this->Probe_Ampl,
      this->Probe_Phase,
      this->Forw_Ampl,
      this->Forw_Phase,
      this->Refl_Ampl,
      this->Refl_Phase,
      this->FS,
      this->F0,
      this->calCoeff,
      this->tau_m,
      this->K_m,
      this->X0,
      this->QL_nom,
      this->DELAY,
      this->FILLING,
      this->FLATTOP,
      this->Sigma_nom,
      this->r_mean_nom,
      this->MeasNoiseVar,
      this->ProcessVar,
      this->s_max,
      this->classis,
      this->strengthis,
      this->QL,
      this->dw_stat
      );
  }
  
  

// 		this->residual_ukf, 
// 		this->residual_ukf_mean, 
// 		this->residual_ukf_Variance,
// 		this->calCoeff);

	//~ this->print_res();
}

void AAnalysis::print_res()
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
    
//    std::cout << " r_cmplx[" << r_cmplx->size[0U] << "].re: ";
//    for (int idx0 = 0; idx0 < r_cmplx->size[0U]; idx0++) {
//      std::cout << r_cmplx->data[idx0].re << " ";
//    }
//    std::cout << "\n";
//    std::cout << " r_cmplx[" << r_cmplx->size[0U] << "].im: ";
//    for (int idx0 = 0; idx0 < r_cmplx->size[0U]; idx0++) {
//      std::cout << r_cmplx->data[idx0].im << " ";
//    }
    std::cout << "\n";
    std::cout << " smax[" << s_max->size[0U] << "]: ";
    for (int idx0 = 0; idx0 < s_max->size[0U]; idx0++) {
      std::cout << s_max->data[idx0] << " ";      
    }
    std::cout << "\n";

}

void AAnalysis::set_data(doocs_snapdaq_data_channel dc, uint pid, double time)
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

void AAnalysis::set_data(doocs_snapdaq_data_channel dc ) 
//~ void AAnalysis::set_data(aoa_daq_channel dc ) 
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

void AAnalysis::print_data()
{
	std::cout << std::setprecision(12) << "Data:"
		<< " pid: " << this->PID     
		<< " time: " << this->TIME
		<< " name: " << this->NAME    
    << " delay: " << this->DELAY   
		<< " filling: " << this->FILLING 
		<< " flattop: " << this->FLATTOP 
		<< " fs: " << this->FS      
		<< " f0: " << this->F0           
		//~ << "\n";
    //~ std::cout 
    << " Sizes: "
		<< this->Probe_Ampl->size[0U] << " "
		<< this->Probe_Phase->size[0U] << " "
		<< this->Forw_Ampl->size[0U] << " "
		<< this->Forw_Phase->size[0U] << " "
		<< this->Refl_Ampl->size[0U] << " "
		<< this->Refl_Phase->size[0U] << "\n";
		
}

void AAnalysis::jsondaq()
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

void AAnalysis::writejson()
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

void AAnalysis::writeappjson(std::string filename)
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

void AAnalysis::write_res_dat(std::string filename)
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
		<< "FLAG"  << " " 
  << "classis"  << " "
  << "strengthis"  << " "
  << "QL"  << " "
  << "dw_stat"  << " "
//		<< "r_cmplx.re[]"  << " "
//		<< "r_cmplx.im[]"  << " "
//		<< "smax[]"  << " "
    << std::endl;
	}
	
	file_out << std::setprecision(16)
		<< this->PID                        << " " 
		<< this->NAME                       << " " 
		<< this->TIME                       << " "
		<< this->FLAG                       << " "

  << this->classis                   << " "
  << this->strengthis                << " "
  << this->QL                        << " "
  << this->dw_stat                    << " "
    ;
// << "[ ";
//    for (int idx0 = 0; idx0 < r_cmplx->size[0U]; idx0++) {
//      file_out << r_cmplx->data[idx0].re << " ";
//    }
//    file_out << " ] [ ";
//    for (int idx0 = 0; idx0 < r_cmplx->size[0U]; idx0++) {
//      file_out << r_cmplx->data[idx0].im << " ";
//    }
//    file_out << " ] [ ";
//    file_out << " [ ";
//    for (int idx0 = 0; idx0 < s_max->size[0U]; idx0++) {
//      file_out << s_max->data[idx0] << " ";
//    }
//		file_out << " ]" << std::endl;
    
	file_out.close();
	
}

void AAnalysis::save_daq_json(std::string filename)
{
	//~ std::cout << jsonstream << std::endl;	
	std::ofstream file_out(filename);
	file_out << json_daq_stream;
	file_out.close();
	json_daq_stream.clear();

}

void AAnalysis::savejson(std::string filename)
{
	//~ std::cout << jsonstream << std::endl;	
	std::ofstream file_out(filename);
	file_out << jsonstream;
	file_out.close();
	jsonstream.clear();

}

void AAnalysis::save_bit(std::string filename) 
{
	this->data->appwrite(filename);
	this->data->mps.clear();
}
