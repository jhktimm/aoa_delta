/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_online_UKF_residual_full.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 24-Sep-2019 18:29:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_generate_online_UKF_residual_full.h"
#include "f_generate_and_eval_residual_emxutil.h"
#include "f_compute_ukf_residual_not_pers.h"
#include "f_calibrateData.h"
#include "exp.h"

/* Function Definitions */

/*
 * inputs:
 *  Probe_Ampl: Amplitude of Probe measurement
 *  Probe_Phase: Phase of Probe measurement
 *  Forw_Ampl: Amplitude of Forward measurement
 *  Forw_Phase: Phase of Forward measurement
 *  Refl_Ampl: Amplitude of Reflected measurement
 *  Refl_Probe: Phase of Reflected measurement
 *  fs: Sampling frequency, for online Data 9MHz, DAQ data 1MHz - can be read
 *  from DOOCS property
 *  f0: Resonance frequency, should be 1.3GHz - should be read
 *  from DOOCS property
 *  cal_coeff: coefficients necessary for the calibration of the signals,
 *  obtained from the function f_get_calCoeff
 *  Rise: Sample numbers that belong to the rise (filling) of the Pulse - should be read
 *  from DOOCS property
 *  Flattop: Samople numbers that belong to the flattop of the pulse - should be read
 *  from DOOCS property
 *  Decay: Sample numbers that belong to the decay of the pulse  - should be read
 *  from DOOCS property
 *  #cogegen
 * Arguments    : const emxArray_real_T *Probe_Ampl
 *                const emxArray_real_T *Probe_Phase
 *                const emxArray_real_T *Forw_Ampl
 *                const emxArray_real_T *Forw_Phase
 *                const emxArray_real_T *Refl_Ampl
 *                const emxArray_real_T *Refl_Probe
 *                double FS
 *                const creal_T cal_coeff[4]
 *                const double tau_m[4]
 *                const double K_m[4]
 *                const double X0[4]
 *                double QL_nom
 *                const double MeasNoiseVar[4]
 *                const double ProcessVar[36]
 *                emxArray_real_T *res_full_mean
 *                emxArray_real_T *res_full_Variance
 * Return Type  : void
 */
void c_f_generate_online_UKF_residua(const emxArray_real_T *Probe_Ampl, const
  emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Ampl, const
  emxArray_real_T *Refl_Probe, double FS, const creal_T cal_coeff[4], const
  double tau_m[4], const double K_m[4], const double X0[4], double QL_nom, const
  double MeasNoiseVar[4], const double ProcessVar[36], emxArray_real_T
  *res_full_mean, emxArray_real_T *res_full_Variance)
{
  emxArray_creal_T *y_mC;
  int i;
  int loop_ub;
  double im;
  double ai;
  double re;
  emxArray_creal_T *u_mCal;
  emxArray_creal_T *unusedU0;
  emxArray_creal_T *b_Forw_Ampl;
  emxArray_creal_T *b_Refl_Ampl;
  double dv1[6];
  emxArray_real_T *b_y_mC;
  emxArray_real_T *b_u_mCal;
  emxArray_real_T *unusedU1;
  emxArray_real_T *unusedU2;
  emxInit_creal_T(&y_mC, 1);
  i = y_mC->size[0];
  y_mC->size[0] = Probe_Phase->size[0];
  emxEnsureCapacity_creal_T(y_mC, i);
  loop_ub = Probe_Phase->size[0];
  for (i = 0; i < loop_ub; i++) {
    im = 0.0 * Probe_Phase->data[i];
    ai = Probe_Phase->data[i];
    if (ai == 0.0) {
      re = im / 180.0;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 180.0;
    } else {
      re = rtNaN;
      im = ai / 180.0;
    }

    y_mC->data[i].re = 3.1415926535897931 * re;
    y_mC->data[i].im = 3.1415926535897931 * im;
  }

  b_exp(y_mC);
  i = y_mC->size[0];
  y_mC->size[0] = Probe_Ampl->size[0];
  emxEnsureCapacity_creal_T(y_mC, i);
  loop_ub = Probe_Ampl->size[0];
  for (i = 0; i < loop_ub; i++) {
    y_mC->data[i].re *= Probe_Ampl->data[i];
    y_mC->data[i].im *= Probe_Ampl->data[i];
  }

  emxInit_creal_T(&u_mCal, 1);

  /*  Complex Probe measurement */
  /*  Complex Forward measurement */
  /*  Reflected */
  /*  Online residual generation */
  i = u_mCal->size[0];
  u_mCal->size[0] = Forw_Phase->size[0];
  emxEnsureCapacity_creal_T(u_mCal, i);
  loop_ub = Forw_Phase->size[0];
  for (i = 0; i < loop_ub; i++) {
    im = 0.0 * Forw_Phase->data[i];
    ai = Forw_Phase->data[i];
    if (ai == 0.0) {
      re = im / 180.0;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 180.0;
    } else {
      re = rtNaN;
      im = ai / 180.0;
    }

    u_mCal->data[i].re = 3.1415926535897931 * re;
    u_mCal->data[i].im = 3.1415926535897931 * im;
  }

  emxInit_creal_T(&unusedU0, 1);
  b_exp(u_mCal);
  i = unusedU0->size[0];
  unusedU0->size[0] = Refl_Probe->size[0];
  emxEnsureCapacity_creal_T(unusedU0, i);
  loop_ub = Refl_Probe->size[0];
  for (i = 0; i < loop_ub; i++) {
    im = 0.0 * Refl_Probe->data[i];
    ai = Refl_Probe->data[i];
    if (ai == 0.0) {
      re = im / 180.0;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 180.0;
    } else {
      re = rtNaN;
      im = ai / 180.0;
    }

    unusedU0->data[i].re = 3.1415926535897931 * re;
    unusedU0->data[i].im = 3.1415926535897931 * im;
  }

  emxInit_creal_T(&b_Forw_Ampl, 1);
  b_exp(unusedU0);
  i = b_Forw_Ampl->size[0];
  b_Forw_Ampl->size[0] = Forw_Ampl->size[0];
  emxEnsureCapacity_creal_T(b_Forw_Ampl, i);
  loop_ub = Forw_Ampl->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_Forw_Ampl->data[i].re = Forw_Ampl->data[i] * u_mCal->data[i].re;
    b_Forw_Ampl->data[i].im = Forw_Ampl->data[i] * u_mCal->data[i].im;
  }

  emxInit_creal_T(&b_Refl_Ampl, 1);
  i = b_Refl_Ampl->size[0];
  b_Refl_Ampl->size[0] = Refl_Ampl->size[0];
  emxEnsureCapacity_creal_T(b_Refl_Ampl, i);
  loop_ub = Refl_Ampl->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_Refl_Ampl->data[i].re = Refl_Ampl->data[i] * unusedU0->data[i].re;
    b_Refl_Ampl->data[i].im = Refl_Ampl->data[i] * unusedU0->data[i].im;
  }

  f_calibrateData(b_Forw_Ampl, b_Refl_Ampl, cal_coeff, u_mCal, unusedU0);
  dv1[0] = 0.0;
  dv1[1] = 0.0;
  emxFree_creal_T(&b_Refl_Ampl);
  emxFree_creal_T(&b_Forw_Ampl);
  emxFree_creal_T(&unusedU0);
  for (i = 0; i < 4; i++) {
    dv1[i + 2] = X0[i];
  }

  emxInit_real_T(&b_y_mC, 2);
  i = b_y_mC->size[0] * b_y_mC->size[1];
  b_y_mC->size[0] = 2;
  b_y_mC->size[1] = y_mC->size[0];
  emxEnsureCapacity_real_T(b_y_mC, i);
  loop_ub = y_mC->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_y_mC->data[b_y_mC->size[0] * i] = y_mC->data[i].re;
  }

  loop_ub = y_mC->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_y_mC->data[1 + b_y_mC->size[0] * i] = y_mC->data[i].im;
  }

  emxFree_creal_T(&y_mC);
  emxInit_real_T(&b_u_mCal, 2);
  i = b_u_mCal->size[0] * b_u_mCal->size[1];
  b_u_mCal->size[0] = 2;
  b_u_mCal->size[1] = u_mCal->size[0];
  emxEnsureCapacity_real_T(b_u_mCal, i);
  loop_ub = u_mCal->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_u_mCal->data[b_u_mCal->size[0] * i] = u_mCal->data[i].re;
  }

  loop_ub = u_mCal->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_u_mCal->data[1 + b_u_mCal->size[0] * i] = u_mCal->data[i].im;
  }

  emxFree_creal_T(&u_mCal);
  emxInit_real_T(&unusedU1, 2);
  emxInit_real_T2(&unusedU2, 3);
  f_compute_ukf_residual_not_pers(dv1, MeasNoiseVar, ProcessVar, b_y_mC,
    b_u_mCal, FS * 1.0E+6, QL_nom, tau_m, K_m, res_full_mean, res_full_Variance,
    unusedU1, unusedU2);

  /* clear f_compute_ukf_residual_mex */
  /*  figure(98) */
  /*  plot(res_full_mean(1,1:9:end),'k.', 'MarkerSize', 8) */
  /*  hold on */
  /*  plot(res_full_mean(2,1:9:end),'g.', 'MarkerSize', 8) */
  /*  xlabel('Samples') */
  /*  ylabel('Residual') */
  /*  legend('I', 'Q') */
  /*  axis tight */
  /*  ylim([-0.025,0.025]) */
  /*  ax= gca; */
  /*  ax.FontName = 'Calibri'; */
  /*  ax.FontSize = 20; */
  /*  set(gcf,'Color', 'w') */
  /*  Arithmetic mean of the mean */
  /*  residual_ukf = [mean(res_full_mean(:,Rise),2),... */
  /*      mean(res_full_mean(:,Flattop),2),mean(res_full_mean(:,Decay(1:end-1)),2)]; */
  /*  */
  /*  % Equality Node: Taking the variance into consideration */
  /*  residual_ukf_Variance(:,:,1) = [reshape(sum(res_full_Info(Rise,:,:)),[2,2])]\eye(2,2); */
  /*  residual_ukf_Variance(:,:,2) = [reshape(sum(res_full_Info(Flattop,:,:)),[2,2])]\eye(2,2); */
  /*  */
  /*  */
  /*  residual_ukf_Variance(:,:,3) = ([reshape(sum(res_full_Info(Decay(1:end-1),:,:)),[2,2])])\eye(2,2); */
  /*  */
  /*  */
  /*  */
  /*  residual_ukf_mean = [ [reshape(sum(res_full_Info(Rise,:,:)),[2,2])]\eye(2,2) * sum(res_full_xi(:,Rise),2),... */
  /*      [reshape(sum(res_full_Info(Flattop,:,:)),[2,2])]\eye(2,2)*sum(res_full_xi(:,Flattop),2),... */
  /*      [reshape(sum(res_full_Info(Decay(1:end-1),:,:)),[2,2])]\eye(2,2)*sum(res_full_xi(:,Decay(1:end-1)),2)]; */
  emxFree_real_T(&b_u_mCal);
  emxFree_real_T(&b_y_mC);
  emxFree_real_T(&unusedU2);
  emxFree_real_T(&unusedU1);
}

/*
 * File trailer for f_generate_online_UKF_residual_full.c
 *
 * [EOF]
 */
