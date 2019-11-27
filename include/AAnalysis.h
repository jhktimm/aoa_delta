
#ifndef AANALYSIS_H
#define AANALYSIS_H

#include <jsoncpp/json/json.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <sstream>

#include "../matlab_code/f_generate_and_eval_multi_residuals.h"
//#include "../matlab_code/f_generate_and_eval_residual6.h"

#include "../include/aoa_daq_datasclass.h"


class AAnalysis
{
public:
 AAnalysis();
 AAnalysis(int samples);
 AAnalysis(int samples, int div);
 virtual ~AAnalysis();

 void getParameters(std::string jsonfilename);
 void getAutoParameters();/// Getting Parameters tau_m, K_m and X0 from jsonfile. json Filename is generated autamatic from live data. call readAll()( or cavity_name.read() or something like that) AND set_data first!
 void getAutoParameters(std::string tauKXdir);
 void print_Parameters();

 void set_data(std::string jsonfilename);
 void set_data(doocs_snapdaq_data_channel dc);
 void set_data(doocs_snapdaq_data_channel dc, uint pid, double time);/// use this, if you want to overwrite delay, flattop, filling, fs=1 !, f0 and pid
 void print_data();


 void get_res();
 void print_res();

 void get_calCoeff();
 void print_calCoeff();

 void write_res_dat(std::string filename);

 void save_bit(std::string filename);

 double FS;

 void init();
 void init(int samp, int div);

 aoa_daq_datasclass* data = new aoa_daq_datasclass;

 doocs_snapdaq_data_channel channel;

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
 double F0;
 emxArray_real_T *Probe_Ampl;
 emxArray_real_T *Probe_Phase;
 emxArray_real_T *Forw_Ampl;
 emxArray_real_T *Forw_Phase;
 emxArray_real_T *Refl_Ampl;
 emxArray_real_T *Refl_Phase;

 //inputs
 emxArray_real_T *dw_trace_nom; //new
 emxArray_real_T *r_PS1_nom; //new

 double Sigma_nom_PS1;//new
 double Sigma_nom_dw;//new

 creal_T calCoeff[4];

 double QL_nom;
 double Sigma_nom[4];
 double r_mean_nom[2];
 double MeasNoiseVar[4];
 double ProcessVar[36];

 //    emxArray_creal_T *r_cmplx;
 //outputs not to be saved
 emxArray_real_T *s_max;//ukf
 emxArray_real_T *s_max_dw; //new
 emxArray_real_T *s_max_PS1; //new
 emxArray_real_T *res_PS2; //new

 double *classis;
 double *classis_ps;//new
 double *classis_dw;//new
 double *strengthis;
 double *strengthis_ps;//new
 double *strengthis_dw;//new
 double *QL;
 double *dw_stat;
 double *SP_F;
 double *SP_P;
// double *strengtVar;//old
// double *maxis;//old
// double *minis;//old
 double *PC;
 double *calib_check;
 double *dec_hq;

};


#endif /* AANALYSIS_H */ 
