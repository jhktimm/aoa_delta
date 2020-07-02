
#ifndef AANALYSIS_H
#define AANALYSIS_H

#include <jsoncpp/json/json.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <sstream>

#include "../matlab_code/f_generate_and_eval_multi_residuals_dwfix.h"
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
 emxArray_real_T *dwfix; //dwfix


 double Sigma_nom_PS1;//new
 double Sigma_nom_dw;//new

 creal_T calCoeff[4];

 double QL_nom;
 double Sigma_nom_UKF[4];
 double r_mean_nom_UKF[2];  //dwfix
 double MeasNoiseVar[4];
 double ProcessVar[36];
 double alpha{1}; //dwfix 
 
 double Sigma_nom_UKF_dwfix[4]; //dwfix
 double r_mean_nom_UKF_dwfix[2]; //dwfix
 //    emxArray_creal_T *r_cmplx;
 //outputs not to be saved
 emxArray_real_T *s_max_UKF; //dwfix
 emxArray_real_T *s_max_UKF_dwfix; //dwfix
 emxArray_real_T *s_max_dw; //new
 emxArray_real_T *s_max_PS1; //new
 emxArray_real_T *res_PS2; //new

 double *classis_UKF; //dwfix
 double *classis_dwfix; //dwfix
 double *classis_ps;//new
 double *classis_dw;//new
 double *strengthis_UKF; //dwfix
 double *strengthis_dwfix; //dwfix
 double *strengthis_ps;//new
 double *strengthis_dw;//new
 
 double *max_UKF;//dwfix
 double *max_dwfix;//dwfix
 double *max_PS;//dwfix
 double *max_dw;//dwfix
 double *median_UKF;//dwfix
 double *median_dwfix;//dwfix
 double *median_PS;//dwfix
 double *median_dw;//dwfix
 double *mode_UKF;//dwfix
 double *mode_dwfix;//dwfix
 double *mode_PS;//dwfix
 double *mode_dw;//dwfix
 double *var_UKF;//dwfix
 double *var_dwfix;//dwfix
 double *var_PS;//dwfix
 double *var_dw;//dwfix
 double *rm_I;//dwfix
 double *rm_Q;//dwfix
 double *rm_I_dwfix;//dwfix
 double *rm_Q_dwfix;//dwfix
 double *rvar_1;//dwfix
 double *rvar_2;//dwfix
 double *rvar_3;//dwfix
 
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
 double *zpth;//dwfix 

};


#endif /* AANALYSIS_H */ 
