/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_online_parityRes2_full.c
 *
 * Code generation for function 'f_generate_online_parityRes2_full'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_generate_online_parityRes2_full.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"
#include "f_compute_parity_Res2_full.h"
#include "f_calibrateData.h"
#include "exp.h"

/* Function Definitions */
void c_f_generate_online_parityRes2_(const emxArray_real_T *Probe_Ampl, const
  emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Ampl, const
  emxArray_real_T *Refl_Probe, double FS, const creal_T cal_coeff[4], const
  double tau_m[4], const double K_m[4], double QL_nom, emxArray_real_T
  *residual2)
{
  emxArray_creal_T *r7;
  int i22;
  int loop_ub;
  emxArray_creal_T *u_mCal;
  double im;
  double ai;
  double re;
  emxArray_creal_T *unusedU0;
  emxArray_creal_T *b_Forw_Ampl;
  emxArray_creal_T *b_Refl_Ampl;
  emxArray_creal_T *b_Probe_Ampl;
  emxInit_creal_T(&r7, 1);

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
  i22 = r7->size[0];
  r7->size[0] = Probe_Phase->size[0];
  emxEnsureCapacity((emxArray__common *)r7, i22, sizeof(creal_T));
  loop_ub = Probe_Phase->size[0];
  for (i22 = 0; i22 < loop_ub; i22++) {
    im = 0.0 * Probe_Phase->data[i22];
    ai = Probe_Phase->data[i22];
    if (ai == 0.0) {
      re = im / 180.0;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 180.0;
    } else {
      re = im / 180.0;
      im = ai / 180.0;
    }

    r7->data[i22].re = 3.1415926535897931 * re;
    r7->data[i22].im = 3.1415926535897931 * im;
  }

  emxInit_creal_T(&u_mCal, 1);
  b_exp(r7);

  /*  Complex Probe measurement */
  i22 = u_mCal->size[0];
  u_mCal->size[0] = Forw_Phase->size[0];
  emxEnsureCapacity((emxArray__common *)u_mCal, i22, sizeof(creal_T));
  loop_ub = Forw_Phase->size[0];
  for (i22 = 0; i22 < loop_ub; i22++) {
    im = 0.0 * Forw_Phase->data[i22];
    ai = Forw_Phase->data[i22];
    if (ai == 0.0) {
      re = im / 180.0;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 180.0;
    } else {
      re = im / 180.0;
      im = ai / 180.0;
    }

    u_mCal->data[i22].re = 3.1415926535897931 * re;
    u_mCal->data[i22].im = 3.1415926535897931 * im;
  }

  emxInit_creal_T(&unusedU0, 1);
  b_exp(u_mCal);

  /*  Complex Forward measurement */
  i22 = unusedU0->size[0];
  unusedU0->size[0] = Refl_Probe->size[0];
  emxEnsureCapacity((emxArray__common *)unusedU0, i22, sizeof(creal_T));
  loop_ub = Refl_Probe->size[0];
  for (i22 = 0; i22 < loop_ub; i22++) {
    im = 0.0 * Refl_Probe->data[i22];
    ai = Refl_Probe->data[i22];
    if (ai == 0.0) {
      re = im / 180.0;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 180.0;
    } else {
      re = im / 180.0;
      im = ai / 180.0;
    }

    unusedU0->data[i22].re = 3.1415926535897931 * re;
    unusedU0->data[i22].im = 3.1415926535897931 * im;
  }

  emxInit_creal_T(&b_Forw_Ampl, 1);
  b_exp(unusedU0);

  /*  Reflected */
  /*  Online residual generation */
  i22 = b_Forw_Ampl->size[0];
  b_Forw_Ampl->size[0] = Forw_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)b_Forw_Ampl, i22, sizeof(creal_T));
  loop_ub = Forw_Ampl->size[0];
  for (i22 = 0; i22 < loop_ub; i22++) {
    b_Forw_Ampl->data[i22].re = Forw_Ampl->data[i22] * u_mCal->data[i22].re;
    b_Forw_Ampl->data[i22].im = Forw_Ampl->data[i22] * u_mCal->data[i22].im;
  }

  emxInit_creal_T(&b_Refl_Ampl, 1);
  i22 = b_Refl_Ampl->size[0];
  b_Refl_Ampl->size[0] = Refl_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)b_Refl_Ampl, i22, sizeof(creal_T));
  loop_ub = Refl_Ampl->size[0];
  for (i22 = 0; i22 < loop_ub; i22++) {
    b_Refl_Ampl->data[i22].re = Refl_Ampl->data[i22] * unusedU0->data[i22].re;
    b_Refl_Ampl->data[i22].im = Refl_Ampl->data[i22] * unusedU0->data[i22].im;
  }

  emxInit_creal_T(&b_Probe_Ampl, 1);
  f_calibrateData(b_Forw_Ampl, b_Refl_Ampl, cal_coeff, u_mCal, unusedU0);
  i22 = b_Probe_Ampl->size[0];
  b_Probe_Ampl->size[0] = Probe_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)b_Probe_Ampl, i22, sizeof(creal_T));
  loop_ub = Probe_Ampl->size[0];
  emxFree_creal_T(&b_Refl_Ampl);
  emxFree_creal_T(&b_Forw_Ampl);
  emxFree_creal_T(&unusedU0);
  for (i22 = 0; i22 < loop_ub; i22++) {
    b_Probe_Ampl->data[i22].re = Probe_Ampl->data[i22] * r7->data[i22].re;
    b_Probe_Ampl->data[i22].im = Probe_Ampl->data[i22] * r7->data[i22].im;
  }

  emxFree_creal_T(&r7);
  f_compute_parity_Res2_full(u_mCal, b_Probe_Ampl, tau_m, K_m, QL_nom, FS *
    1.0E+6, residual2);
  emxFree_creal_T(&b_Probe_Ampl);
  emxFree_creal_T(&u_mCal);
}

/* End of code generation (f_generate_online_parityRes2_full.c) */
