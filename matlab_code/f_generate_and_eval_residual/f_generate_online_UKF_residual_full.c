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
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_generate_online_UKF_residual_full.h"
#include "f_generate_and_eval_residual_emxutil.h"
#include "f_compute_ukf_residual_not_pers.h"
#include "exp.h"

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
  int i1;
  int i;
  double u_mC_re;
  double r_mC_re;
  double u_mC_im;
  emxArray_creal_T *u_mC;
  emxArray_creal_T *r_mC;
  emxArray_creal_T *u_mCal;
  emxArray_int32_T *r0;
  emxArray_creal_T *b_u_mC;
  double r_mC_im;
  double dv2[6];
  emxArray_real_T *b_y_mC;
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
  i1 = y_mC->size[0];
  y_mC->size[0] = Probe_Phase->size[0];
  emxEnsureCapacity((emxArray__common *)y_mC, i1, sizeof(creal_T));
  i = Probe_Phase->size[0];
  for (i1 = 0; i1 < i; i1++) {
    u_mC_re = 0.0 * Probe_Phase->data[i1];
    r_mC_re = Probe_Phase->data[i1];
    if (r_mC_re == 0.0) {
      u_mC_im = u_mC_re / 180.0;
      u_mC_re = 0.0;
    } else if (u_mC_re == 0.0) {
      u_mC_im = 0.0;
      u_mC_re = r_mC_re / 180.0;
    } else {
      u_mC_im = u_mC_re / 180.0;
      u_mC_re = r_mC_re / 180.0;
    }

    y_mC->data[i1].re = 3.1415926535897931 * u_mC_im;
    y_mC->data[i1].im = 3.1415926535897931 * u_mC_re;
  }

  b_exp(y_mC);
  i1 = y_mC->size[0];
  y_mC->size[0] = Probe_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)y_mC, i1, sizeof(creal_T));
  i = Probe_Ampl->size[0];
  for (i1 = 0; i1 < i; i1++) {
    y_mC->data[i1].re *= Probe_Ampl->data[i1];
    y_mC->data[i1].im *= Probe_Ampl->data[i1];
  }

  emxInit_creal_T(&u_mC, 1);

  /*  Complex Probe measurement */
  i1 = u_mC->size[0];
  u_mC->size[0] = Forw_Phase->size[0];
  emxEnsureCapacity((emxArray__common *)u_mC, i1, sizeof(creal_T));
  i = Forw_Phase->size[0];
  for (i1 = 0; i1 < i; i1++) {
    u_mC_re = 0.0 * Forw_Phase->data[i1];
    r_mC_re = Forw_Phase->data[i1];
    if (r_mC_re == 0.0) {
      u_mC_im = u_mC_re / 180.0;
      u_mC_re = 0.0;
    } else if (u_mC_re == 0.0) {
      u_mC_im = 0.0;
      u_mC_re = r_mC_re / 180.0;
    } else {
      u_mC_im = u_mC_re / 180.0;
      u_mC_re = r_mC_re / 180.0;
    }

    u_mC->data[i1].re = 3.1415926535897931 * u_mC_im;
    u_mC->data[i1].im = 3.1415926535897931 * u_mC_re;
  }

  b_exp(u_mC);
  i1 = u_mC->size[0];
  u_mC->size[0] = Forw_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)u_mC, i1, sizeof(creal_T));
  i = Forw_Ampl->size[0];
  for (i1 = 0; i1 < i; i1++) {
    u_mC->data[i1].re *= Forw_Ampl->data[i1];
    u_mC->data[i1].im *= Forw_Ampl->data[i1];
  }

  emxInit_creal_T(&r_mC, 1);

  /*  Complex Forward measurement */
  i1 = r_mC->size[0];
  r_mC->size[0] = Refl_Probe->size[0];
  emxEnsureCapacity((emxArray__common *)r_mC, i1, sizeof(creal_T));
  i = Refl_Probe->size[0];
  for (i1 = 0; i1 < i; i1++) {
    u_mC_re = 0.0 * Refl_Probe->data[i1];
    r_mC_re = Refl_Probe->data[i1];
    if (r_mC_re == 0.0) {
      u_mC_im = u_mC_re / 180.0;
      u_mC_re = 0.0;
    } else if (u_mC_re == 0.0) {
      u_mC_im = 0.0;
      u_mC_re = r_mC_re / 180.0;
    } else {
      u_mC_im = u_mC_re / 180.0;
      u_mC_re = r_mC_re / 180.0;
    }

    r_mC->data[i1].re = 3.1415926535897931 * u_mC_im;
    r_mC->data[i1].im = 3.1415926535897931 * u_mC_re;
  }

  b_exp(r_mC);
  i1 = r_mC->size[0];
  r_mC->size[0] = Refl_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)r_mC, i1, sizeof(creal_T));
  i = Refl_Ampl->size[0];
  for (i1 = 0; i1 < i; i1++) {
    r_mC->data[i1].re *= Refl_Ampl->data[i1];
    r_mC->data[i1].im *= Refl_Ampl->data[i1];
  }

  emxInit_creal_T(&u_mCal, 1);

  /*  Reflected */
  /*  Online residual generation */
  /* Initialize */
  i1 = u_mCal->size[0];
  u_mCal->size[0] = u_mC->size[0];
  emxEnsureCapacity((emxArray__common *)u_mCal, i1, sizeof(creal_T));
  i = u_mC->size[0];
  for (i1 = 0; i1 < i; i1++) {
    u_mCal->data[i1].re = 0.0;
    u_mCal->data[i1].im = 0.0;
  }

  emxInit_int32_T(&r0, 1);

  /*  compute calibrated FORW and REFL signal */
  i = u_mCal->size[0];
  i1 = r0->size[0];
  r0->size[0] = i;
  emxEnsureCapacity((emxArray__common *)r0, i1, sizeof(int));
  for (i1 = 0; i1 < i; i1++) {
    r0->data[i1] = i1;
  }

  emxInit_creal_T1(&b_u_mC, 2);
  i = u_mC->size[0];
  i1 = b_u_mC->size[0] * b_u_mC->size[1];
  b_u_mC->size[0] = 1;
  b_u_mC->size[1] = i;
  emxEnsureCapacity((emxArray__common *)b_u_mC, i1, sizeof(creal_T));
  for (i1 = 0; i1 < i; i1++) {
    u_mC_re = u_mC->data[i1].re * cal_coeff[0].re - u_mC->data[i1].im *
      cal_coeff[0].im;
    u_mC_im = u_mC->data[i1].re * cal_coeff[0].im + u_mC->data[i1].im *
      cal_coeff[0].re;
    r_mC_re = r_mC->data[i1].re * cal_coeff[1].re - r_mC->data[i1].im *
      cal_coeff[1].im;
    r_mC_im = r_mC->data[i1].re * cal_coeff[1].im + r_mC->data[i1].im *
      cal_coeff[1].re;
    b_u_mC->data[b_u_mC->size[0] * i1].re = u_mC_re + r_mC_re;
    b_u_mC->data[b_u_mC->size[0] * i1].im = u_mC_im + r_mC_im;
  }

  emxFree_creal_T(&r_mC);
  emxFree_creal_T(&u_mC);
  i = r0->size[0];
  for (i1 = 0; i1 < i; i1++) {
    u_mCal->data[r0->data[i1]] = b_u_mC->data[i1];
  }

  emxFree_creal_T(&b_u_mC);
  emxFree_int32_T(&r0);

  /* ------------Plot Before and After Calibration----------------------------- */
  dv2[0] = 0.0;
  dv2[1] = 0.0;
  for (i = 0; i < 4; i++) {
    dv2[i + 2] = X0[i];
  }

  emxInit_real_T(&b_y_mC, 2);
  i1 = b_y_mC->size[0] * b_y_mC->size[1];
  b_y_mC->size[0] = 2;
  b_y_mC->size[1] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)b_y_mC, i1, sizeof(double));
  i = y_mC->size[0];
  for (i1 = 0; i1 < i; i1++) {
    b_y_mC->data[b_y_mC->size[0] * i1] = y_mC->data[i1].re;
  }

  i = y_mC->size[0];
  for (i1 = 0; i1 < i; i1++) {
    b_y_mC->data[1 + b_y_mC->size[0] * i1] = y_mC->data[i1].im;
  }

  emxFree_creal_T(&y_mC);
  emxInit_real_T(&b_u_mCal, 2);
  i1 = b_u_mCal->size[0] * b_u_mCal->size[1];
  b_u_mCal->size[0] = 2;
  b_u_mCal->size[1] = u_mCal->size[0];
  emxEnsureCapacity((emxArray__common *)b_u_mCal, i1, sizeof(double));
  i = u_mCal->size[0];
  for (i1 = 0; i1 < i; i1++) {
    b_u_mCal->data[b_u_mCal->size[0] * i1] = u_mCal->data[i1].re;
  }

  i = u_mCal->size[0];
  for (i1 = 0; i1 < i; i1++) {
    b_u_mCal->data[1 + b_u_mCal->size[0] * i1] = u_mCal->data[i1].im;
  }

  emxFree_creal_T(&u_mCal);
  emxInit_real_T(&unusedU1, 2);
  emxInit_real_T1(&unusedU2, 3);
  f_compute_ukf_residual_not_pers(dv2, MeasNoiseVar, ProcessVar, b_y_mC,
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

/* End of code generation (f_generate_online_UKF_residual_full.c) */
