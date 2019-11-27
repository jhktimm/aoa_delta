/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_online_parityRes1_full.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_generate_online_parityRes1_full.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"
#include "f_compute_parity_Res1_full.h"
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
 * Arguments    : const emxArray_real_T *Probe_Ampl
 *                const emxArray_real_T *Probe_Phase
 *                const emxArray_real_T *Forw_Ampl
 *                const emxArray_real_T *Forw_Phase
 *                const emxArray_real_T *Refl_Probe
 *                double FS
 *                double QL_nom
 *                emxArray_real_T *residual1
 * Return Type  : void
 */
void c_f_generate_online_parityRes1_(const emxArray_real_T *Probe_Ampl, const
  emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Probe, double FS,
  double QL_nom, emxArray_real_T *residual1)
{
  emxArray_creal_T *y_mC;
  int i10;
  int loop_ub;
  double im;
  double ai;
  double re;
  emxArray_creal_T *u_mC;
  emxArray_creal_T *u_mCal;
  emxArray_real_T *r6;
  emxInit_creal_T(&y_mC, 1);
  i10 = y_mC->size[0];
  y_mC->size[0] = Probe_Phase->size[0];
  emxEnsureCapacity_creal_T(y_mC, i10);
  loop_ub = Probe_Phase->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    im = 0.0 * Probe_Phase->data[i10];
    ai = Probe_Phase->data[i10];
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

    y_mC->data[i10].re = 3.1415926535897931 * re;
    y_mC->data[i10].im = 3.1415926535897931 * im;
  }

  b_exp(y_mC);
  i10 = y_mC->size[0];
  y_mC->size[0] = Probe_Ampl->size[0];
  emxEnsureCapacity_creal_T(y_mC, i10);
  loop_ub = Probe_Ampl->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    y_mC->data[i10].re *= Probe_Ampl->data[i10];
    y_mC->data[i10].im *= Probe_Ampl->data[i10];
  }

  emxInit_creal_T(&u_mC, 1);

  /*  Complex Probe measurement */
  i10 = u_mC->size[0];
  u_mC->size[0] = Forw_Phase->size[0];
  emxEnsureCapacity_creal_T(u_mC, i10);
  loop_ub = Forw_Phase->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    im = 0.0 * Forw_Phase->data[i10];
    ai = Forw_Phase->data[i10];
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

    u_mC->data[i10].re = 3.1415926535897931 * re;
    u_mC->data[i10].im = 3.1415926535897931 * im;
  }

  b_exp(u_mC);
  i10 = u_mC->size[0];
  u_mC->size[0] = Forw_Ampl->size[0];
  emxEnsureCapacity_creal_T(u_mC, i10);
  loop_ub = Forw_Ampl->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    u_mC->data[i10].re *= Forw_Ampl->data[i10];
    u_mC->data[i10].im *= Forw_Ampl->data[i10];
  }

  /*  Complex Forward measurement */
  /*  Reflected */
  /*  Online residual generation */
  i10 = residual1->size[0];
  residual1->size[0] = y_mC->size[0] - 2;
  emxEnsureCapacity_real_T1(residual1, i10);
  loop_ub = y_mC->size[0];
  for (i10 = 0; i10 <= loop_ub - 3; i10++) {
    residual1->data[i10] = 0.0;
  }

  emxInit_creal_T(&u_mCal, 1);

  /*  [y_mC, u_mC, r_mC] = f_getData(facility, station, module, cavity); */
  i10 = u_mCal->size[0];
  u_mCal->size[0] = Refl_Probe->size[0];
  emxEnsureCapacity_creal_T(u_mCal, i10);
  loop_ub = Refl_Probe->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    im = 0.0 * Refl_Probe->data[i10];
    ai = Refl_Probe->data[i10];
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

    u_mCal->data[i10].re = 3.1415926535897931 * re;
    u_mCal->data[i10].im = 3.1415926535897931 * im;
  }

  emxInit_real_T1(&r6, 1);
  b_exp(u_mCal);
  f_compute_parity_Res1_full(u_mC, y_mC, FS * 1.0E+6, QL_nom, r6);
  loop_ub = r6->size[0];
  emxFree_creal_T(&u_mCal);
  emxFree_creal_T(&u_mC);
  emxFree_creal_T(&y_mC);
  for (i10 = 0; i10 < loop_ub; i10++) {
    residual1->data[i10] = r6->data[i10];
  }

  emxFree_real_T(&r6);
}

/*
 * File trailer for f_generate_online_parityRes1_full.c
 *
 * [EOF]
 */
