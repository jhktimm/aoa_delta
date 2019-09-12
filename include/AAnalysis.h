
#ifndef AANALYSIS_H
#define AANALYSIS_H


#include <jsoncpp/json/json.h>

//~ #include <ttf2_daq_reader_2010.h>
//~ #include <daq_server_util_def.h>
//~ #include <ttf2_daq_data.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <sstream>
// #include "../matlab_code/f_calib_and_res_gen_ukf.h"

//#include "../matlab_code/f_generate_and_eval_residual.h"
//#include "../matlab_code/f_generate_and_eval_residual2.h"
#include "../matlab_code/f_generate_and_eval_residual4.h"

//~ #include "f_generate_online_parityRes1.h"
//~ #include "f_generate_online_parityRes2.h"
//~ #include "f_generate_online_UKF_residual.h"

//~ #include "f_generate_online_UKF_residual.old2.h"
//~ #include "f_generate_online_UKF_residual.false.h"
//~ #include "f_get_calCoeff_codegen.h"

//~ #include "../doocs_snapdaq_llrf_datasclass.h"
#include "../include/aoa_daq_datasclass.h"



class AAnalysis
{
	public:
		AAnalysis();
		AAnalysis(int samples);
		AAnalysis(int samples, int div);
		virtual ~AAnalysis();
	
		//~ void getParameters(std::string jsonfilename, double tau_m[4], double K_m[4], double X0[4] );
		void getParameters(std::string jsonfilename);
		void getAutoParameters();/// Getting Parameters tau_m, K_m and X0 from jsonfile. json Filename is generated autamatic from live data. call readAll()( or cavity_name.read() or something like that) AND set_data first!
		void getAutoParameters(std::string tauKXdir);
    void print_Parameters();
    
		//~ void set_data(ttf2_daq_getdata* data);
		void set_data(std::string jsonfilename);
		void set_data(doocs_snapdaq_data_channel dc);
		void set_data(doocs_snapdaq_data_channel dc, uint pid, double time);/// use this, if you want to overwrite delay, flattop, filling, fs=1 !, f0 and pid
		//~ void set_data(aoa_daq_channel dc);
		//~ void set_data(CavitySignals *cs, MainTableParameters* mtp);
		void print_data();
		
		//~ void test_signal_consistence(CavitySignals *cs);
		
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
		
	//~ private:
	//~ protected:
		void init();
		void init(int samp, int div);
	
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
		bool   FLAG;
		//~ double FS;
		double F0;
		emxArray_real_T *Probe_Ampl;
		emxArray_real_T *Probe_Phase;
		emxArray_real_T *Forw_Ampl;
		emxArray_real_T *Forw_Phase;
		emxArray_real_T *Refl_Ampl;
		emxArray_real_T *Refl_Phase;
			
		
		creal_T calCoeff[4];
// 		creal_T j_calCoeff[4];
    
    double QL_nom;
    double Sigma_nom[4];
    double r_mean_nom[2];
    double MeasNoiseVar[4];
    double ProcessVar[36];
    
//    emxArray_creal_T *r_cmplx;
    emxArray_real_T *s_max;

    double *classis;
    double *strengthis;
    double *QL;
    double *dw_stat;
    double *SP_F;
    double *SP_P;
    double *strengtVar;
    double *maxis;
    double *minis;


		/* add your private declarations */
};


#endif /* AANALYSIS_H */ 
