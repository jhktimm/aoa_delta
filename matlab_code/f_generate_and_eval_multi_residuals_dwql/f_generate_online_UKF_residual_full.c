/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_online_UKF_residual_full.c
 *
 * Code generation for function 'f_generate_online_UKF_residual_full'
 *
 */

/* Include files */
#include "f_generate_online_UKF_residual_full.h"
#include "f_compute_ukf_residual_not_pers.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void c_f_generate_online_UKF_residua(const emxArray_real_T *Probe_Ampl, const
  emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Ampl, const
  emxArray_real_T *Refl_Probe, double FS, const creal_T cal_coeff[4], const
  double tau_m[4], const double K_m[4], const double X0[4], double QL_nom, const
  double MeasNoiseVar[4], const double ProcessVar[36], emxArray_real_T
  *res_full_mean, emxArray_real_T *res_full_Variance)
{
  emxArray_creal_T *y_mC;
  int k;
  int nx;
  double r;
  double ai;
  double re;
  emxArray_creal_T *Forw;
  emxArray_creal_T *Refl;
  emxArray_creal_T *u_mCal;
  emxArray_real_T *b_y_mC;
  double dv[6];
  emxArray_real_T *b_u_mCal;
  emxArray_real_T *unusedU1;
  emxArray_real_T *unusedU2;
  emxInit_creal_T(&y_mC, 1);

  /*  inputs: */
  /*  Probe_Ampl: Amplitude of Probe measurement */
  /*  Probe_Phase: Phase of Probe measurement */
  /*  Forw_Ampl: Amplitude of Forward measurement */
  /*  Forw_Phase: Phase of Forward measurement */
  /*  Refl_Ampl: Amplitude of Reflected measurement */
  /*  Refl_Probe: Phase of Reflected measurement */
  /*  fs: Sampling frequency, for online Data 9MHz, DAQ data 1MHz - can be read */
  /*  from DOOCS property */
  /*  f0: Resonance frequency, should be 1.3GHz - should be read */
  /*  from DOOCS property */
  /*  cal_coeff: coefficients necessary for the calibration of the signals, */
  /*  obtained from the function f_get_calCoeff */
  /*  Rise: Sample numbers that belong to the rise (filling) of the Pulse - should be read */
  /*  from DOOCS property */
  /*  Flattop: Samople numbers that belong to the flattop of the pulse - should be read */
  /*  from DOOCS property */
  /*  Decay: Sample numbers that belong to the decay of the pulse  - should be read */
  /*  from DOOCS property */
  /*  #cogegen */
  k = y_mC->size[0];
  y_mC->size[0] = Probe_Phase->size[0];
  emxEnsureCapacity_creal_T(y_mC, k);
  nx = Probe_Phase->size[0];
  for (k = 0; k < nx; k++) {
    r = 0.0 * Probe_Phase->data[k];
    ai = Probe_Phase->data[k];
    if (ai == 0.0) {
      re = r / 180.0;
      r = 0.0;
    } else if (r == 0.0) {
      re = 0.0;
      r = ai / 180.0;
    } else {
      re = rtNaN;
      r = ai / 180.0;
    }

    y_mC->data[k].re = 3.1415926535897931 * re;
    y_mC->data[k].im = 3.1415926535897931 * r;
  }

  nx = y_mC->size[0];
  for (k = 0; k < nx; k++) {
    if (y_mC->data[k].im == 0.0) {
      y_mC->data[k].re = exp(y_mC->data[k].re);
      y_mC->data[k].im = 0.0;
    } else if (rtIsInf(y_mC->data[k].im) && rtIsInf(y_mC->data[k].re) &&
               (y_mC->data[k].re < 0.0)) {
      y_mC->data[k].re = 0.0;
      y_mC->data[k].im = 0.0;
    } else {
      r = exp(y_mC->data[k].re / 2.0);
      y_mC->data[k].re = r * (r * cos(y_mC->data[k].im));
      y_mC->data[k].im = r * (r * sin(y_mC->data[k].im));
    }
  }

  k = y_mC->size[0];
  y_mC->size[0] = Probe_Ampl->size[0];
  emxEnsureCapacity_creal_T(y_mC, k);
  nx = Probe_Ampl->size[0];
  for (k = 0; k < nx; k++) {
    y_mC->data[k].re *= Probe_Ampl->data[k];
    y_mC->data[k].im *= Probe_Ampl->data[k];
  }

  emxInit_creal_T(&Forw, 1);

  /*  Complex Probe measurement */
  k = Forw->size[0];
  Forw->size[0] = Forw_Phase->size[0];
  emxEnsureCapacity_creal_T(Forw, k);
  nx = Forw_Phase->size[0];
  for (k = 0; k < nx; k++) {
    r = 0.0 * Forw_Phase->data[k];
    ai = Forw_Phase->data[k];
    if (ai == 0.0) {
      re = r / 180.0;
      r = 0.0;
    } else if (r == 0.0) {
      re = 0.0;
      r = ai / 180.0;
    } else {
      re = rtNaN;
      r = ai / 180.0;
    }

    Forw->data[k].re = 3.1415926535897931 * re;
    Forw->data[k].im = 3.1415926535897931 * r;
  }

  nx = Forw->size[0];
  for (k = 0; k < nx; k++) {
    if (Forw->data[k].im == 0.0) {
      Forw->data[k].re = exp(Forw->data[k].re);
      Forw->data[k].im = 0.0;
    } else if (rtIsInf(Forw->data[k].im) && rtIsInf(Forw->data[k].re) &&
               (Forw->data[k].re < 0.0)) {
      Forw->data[k].re = 0.0;
      Forw->data[k].im = 0.0;
    } else {
      r = exp(Forw->data[k].re / 2.0);
      Forw->data[k].re = r * (r * cos(Forw->data[k].im));
      Forw->data[k].im = r * (r * sin(Forw->data[k].im));
    }
  }

  emxInit_creal_T(&Refl, 1);

  /*  Complex Forward measurement */
  k = Refl->size[0];
  Refl->size[0] = Refl_Probe->size[0];
  emxEnsureCapacity_creal_T(Refl, k);
  nx = Refl_Probe->size[0];
  for (k = 0; k < nx; k++) {
    r = 0.0 * Refl_Probe->data[k];
    ai = Refl_Probe->data[k];
    if (ai == 0.0) {
      re = r / 180.0;
      r = 0.0;
    } else if (r == 0.0) {
      re = 0.0;
      r = ai / 180.0;
    } else {
      re = rtNaN;
      r = ai / 180.0;
    }

    Refl->data[k].re = 3.1415926535897931 * re;
    Refl->data[k].im = 3.1415926535897931 * r;
  }

  nx = Refl->size[0];
  for (k = 0; k < nx; k++) {
    if (Refl->data[k].im == 0.0) {
      Refl->data[k].re = exp(Refl->data[k].re);
      Refl->data[k].im = 0.0;
    } else if (rtIsInf(Refl->data[k].im) && rtIsInf(Refl->data[k].re) &&
               (Refl->data[k].re < 0.0)) {
      Refl->data[k].re = 0.0;
      Refl->data[k].im = 0.0;
    } else {
      r = exp(Refl->data[k].re / 2.0);
      Refl->data[k].re = r * (r * cos(Refl->data[k].im));
      Refl->data[k].im = r * (r * sin(Refl->data[k].im));
    }
  }

  /*  Reflected */
  /*  Online residual generation */
  k = Forw->size[0];
  Forw->size[0] = Forw_Ampl->size[0];
  emxEnsureCapacity_creal_T(Forw, k);
  nx = Forw_Ampl->size[0];
  for (k = 0; k < nx; k++) {
    Forw->data[k].re *= Forw_Ampl->data[k];
    Forw->data[k].im *= Forw_Ampl->data[k];
  }

  k = Refl->size[0];
  Refl->size[0] = Refl_Ampl->size[0];
  emxEnsureCapacity_creal_T(Refl, k);
  nx = Refl_Ampl->size[0];
  for (k = 0; k < nx; k++) {
    Refl->data[k].re *= Refl_Ampl->data[k];
    Refl->data[k].im *= Refl_Ampl->data[k];
  }

  emxInit_creal_T(&u_mCal, 1);

  /* Initialize */
  k = u_mCal->size[0];
  u_mCal->size[0] = Forw->size[0];
  emxEnsureCapacity_creal_T(u_mCal, k);
  nx = Forw->size[0];
  for (k = 0; k < nx; k++) {
    u_mCal->data[k].re = 0.0;
    u_mCal->data[k].im = 0.0;
  }

  /*  compute calibrated FORW and REFL signal */
  nx = u_mCal->size[0];
  for (k = 0; k < nx; k++) {
    u_mCal->data[k].re = (Forw->data[k].re * cal_coeff[0].re - Forw->data[k].im *
                          cal_coeff[0].im) + (Refl->data[k].re * cal_coeff[1].re
      - Refl->data[k].im * cal_coeff[1].im);
    u_mCal->data[k].im = (Forw->data[k].re * cal_coeff[0].im + Forw->data[k].im *
                          cal_coeff[0].re) + (Refl->data[k].re * cal_coeff[1].im
      + Refl->data[k].im * cal_coeff[1].re);
  }

  emxFree_creal_T(&Refl);
  emxFree_creal_T(&Forw);
  emxInit_real_T(&b_y_mC, 2);

  /*      Forw_cal = Forw*cof22(1) +... */
  /*          Refl*cof22(2); */
  /*      Refl_cal = Forw*cof22(3) +... */
  /*          Refl*cof22(4); */
  /*  ------------Plot Before and After Calibration----------------------------- */
  /*  if plt == 1 */
  /*  */
  /*  figsize = f_fig_sizes(); */
  /*  figure('Renderer', 'painters', 'Position', [1500 100 2*figsize.wLong 2*figsize.hBig], 'Name', 'Calibration Basic Plot') */
  /*  subplot(2,1,1); set(gca, 'ColorOrder',  cbrewer('qual', 'Set1', 5)) */
  /*  hold on */
  /*  plot(abs(Forw(:,1))) */
  /*  plot(abs(Refl(:,1))) */
  /*  plot(abs(Probe(:,1))) */
  /*  plot(abs(Forw(:,1)+Refl(:,1)),'--') */
  /*  ylabel('Amplitude MV/m') */
  /*  axis tight; box on */
  /*  title('Before Calibration') */
  /*  legend({ 'Forward $\hat{V}_F$', 'Reflected $\hat{V}_R$', 'Probe $\hat{V}_P$','Virtual Probe $\hat{V}_F + \hat{V}_R$ '}, 'Orientation', 'vertical',... */
  /*      'Location', 'eastoutside') */
  /*  ylim([min(ylim), 1.05*max(ylim)]) */
  /*   */
  /*  subplot(2,1,2);set(gca, 'ColorOrder',  cbrewer('qual', 'Set1', 5)) */
  /*  hold on */
  /*  plot(abs(Forw_cal(:,1))) */
  /*  plot(abs(Refl_cal(:,1))) */
  /*  plot(abs(Probe(:,1))) */
  /*  plot(abs(Forw_cal(:,1)+Refl_cal(:,1)),'--') */
  /*  xlabel('Samples');ylabel('Amplitude MV/m') */
  /*  title('After Calibration') */
  /*  legend({ 'Forward $\hat{V}_F$', 'Reflected $\hat{V}_R$', 'Probe $\hat{V}_P$','Virtual Probe $\hat{V}_F + \hat{V}_R$ '}, 'Orientation', 'vertical',... */
  /*      'Location', 'eastoutside') */
  /*  axis tight; box on */
  /*  ylim([min(ylim), 1.05*max(ylim)]) */
  /*  end */
  /*  print -dpng -r600 /home/anawaz/ThesisFigs/Basisc_Calibration_plot.png */
  /*  This is a calibration plot for the real and imag parts of the signals */
  /*      figure('Renderer', 'painters', 'Position', [100 100 1*600 2/3*700], 'Name', 'I values') */
  /*      subplot(2,1,1) */
  /*      set(gca, 'ColorOrder',  cbrewer('qual', 'Dark2', 4)) */
  /*      hold on */
  /*      plot(real(Probe(:,1))) */
  /*      plot(real(Forw(:,1))) */
  /*      plot(real(Refl(:,1))) */
  /*      plot(real(Forw(:,1)+Refl(:,1)),'r--') */
  /*      ylabel('Amplitude MV/m') */
  /*      axis tight */
  /*      title('Before Calibration') */
  /*  */
  /*      legend({ 'Probe', 'Forward', 'Reflected','Virtual Probe'}, 'Orientation', 'vertical',... */
  /*          'Location', 'eastoutside') */
  /*  */
  /*      subplot(2,1,2) */
  /*      set(gca, 'ColorOrder',  cbrewer('qual', 'Dark2', 4)) */
  /*  */
  /*      hold on */
  /*      plot(real(Probe(:,1))) */
  /*      plot(real(Forw_cal(:,1))) */
  /*      plot(real(Refl_cal(:,1))) */
  /*      plot(real(Forw_cal(:,1)+Refl_cal(:,1)),'r--') */
  /*  */
  /*      %legend('Virtual Probe', 'Probe', 'Forward', 'Reflected') */
  /*      ylabel('Amplitude MV/m') */
  /*      xlabel('Samples') */
  /*      title('After Calibration') */
  /*      legend({ 'Probe', 'Forward', 'Reflected','Virtual Probe'}, 'Orientation', 'vertical',... */
  /*          'Location', 'eastoutside') */
  /*      axis tight */
  /* end */
  /* sys_hat.tau */
  /* sys_FIT = f_cavitySystemSimulatior(mean(y_mC,2), mean(u_mCal,2),f0, fs, sys_hat, QL, 1); */
  dv[0] = 0.0;
  dv[1] = 0.0;
  dv[2] = X0[0];
  dv[3] = X0[1];
  dv[4] = X0[2];
  dv[5] = X0[3];
  k = b_y_mC->size[0] * b_y_mC->size[1];
  b_y_mC->size[0] = 2;
  b_y_mC->size[1] = y_mC->size[0];
  emxEnsureCapacity_real_T(b_y_mC, k);
  nx = y_mC->size[0];
  for (k = 0; k < nx; k++) {
    b_y_mC->data[2 * k] = y_mC->data[k].re;
  }

  nx = y_mC->size[0];
  for (k = 0; k < nx; k++) {
    b_y_mC->data[2 * k + 1] = y_mC->data[k].im;
  }

  emxFree_creal_T(&y_mC);
  emxInit_real_T(&b_u_mCal, 2);
  k = b_u_mCal->size[0] * b_u_mCal->size[1];
  b_u_mCal->size[0] = 2;
  b_u_mCal->size[1] = u_mCal->size[0];
  emxEnsureCapacity_real_T(b_u_mCal, k);
  nx = u_mCal->size[0];
  for (k = 0; k < nx; k++) {
    b_u_mCal->data[2 * k] = u_mCal->data[k].re;
  }

  nx = u_mCal->size[0];
  for (k = 0; k < nx; k++) {
    b_u_mCal->data[2 * k + 1] = u_mCal->data[k].im;
  }

  emxFree_creal_T(&u_mCal);
  emxInit_real_T(&unusedU1, 2);
  emxInit_real_T(&unusedU2, 3);
  f_compute_ukf_residual_not_pers(dv, MeasNoiseVar, ProcessVar, b_y_mC, b_u_mCal,
    FS * 1.0E+6, QL_nom, tau_m, K_m, res_full_mean, res_full_Variance, unusedU1,
    unusedU2);
  emxFree_real_T(&b_u_mCal);
  emxFree_real_T(&b_y_mC);
  emxFree_real_T(&unusedU2);
  emxFree_real_T(&unusedU1);
}

/* End of code generation (f_generate_online_UKF_residual_full.c) */
