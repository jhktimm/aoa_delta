/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_online_parityRes1_full.c
 *
 * Code generation for function 'f_generate_online_parityRes1_full'
 *
 */

/* Include files */
#include "f_generate_online_parityRes1_full.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void c_f_generate_online_parityRes1_(const emxArray_real_T *Probe_Ampl, const
  emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, double FS, double QL_nom, emxArray_real_T
  *residual1)
{
  emxArray_creal_T *y_mC;
  int i;
  int nx;
  double r;
  int k;
  double ai;
  double w12;
  emxArray_creal_T *u_mC;
  emxArray_real_T *u1;
  emxArray_real_T *u2;
  emxArray_real_T *x1;
  emxArray_real_T *x2;
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  double a;
  int i8;
  int i9;
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
  i = y_mC->size[0];
  y_mC->size[0] = Probe_Phase->size[0];
  emxEnsureCapacity_creal_T(y_mC, i);
  nx = Probe_Phase->size[0];
  for (i = 0; i < nx; i++) {
    r = 0.0 * Probe_Phase->data[i];
    ai = Probe_Phase->data[i];
    if (ai == 0.0) {
      w12 = r / 180.0;
      r = 0.0;
    } else if (r == 0.0) {
      w12 = 0.0;
      r = ai / 180.0;
    } else {
      w12 = rtNaN;
      r = ai / 180.0;
    }

    y_mC->data[i].re = 3.1415926535897931 * w12;
    y_mC->data[i].im = 3.1415926535897931 * r;
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

  i = y_mC->size[0];
  y_mC->size[0] = Probe_Ampl->size[0];
  emxEnsureCapacity_creal_T(y_mC, i);
  nx = Probe_Ampl->size[0];
  for (i = 0; i < nx; i++) {
    y_mC->data[i].re *= Probe_Ampl->data[i];
    y_mC->data[i].im *= Probe_Ampl->data[i];
  }

  emxInit_creal_T(&u_mC, 1);

  /*  Complex Probe measurement */
  i = u_mC->size[0];
  u_mC->size[0] = Forw_Phase->size[0];
  emxEnsureCapacity_creal_T(u_mC, i);
  nx = Forw_Phase->size[0];
  for (i = 0; i < nx; i++) {
    r = 0.0 * Forw_Phase->data[i];
    ai = Forw_Phase->data[i];
    if (ai == 0.0) {
      w12 = r / 180.0;
      r = 0.0;
    } else if (r == 0.0) {
      w12 = 0.0;
      r = ai / 180.0;
    } else {
      w12 = rtNaN;
      r = ai / 180.0;
    }

    u_mC->data[i].re = 3.1415926535897931 * w12;
    u_mC->data[i].im = 3.1415926535897931 * r;
  }

  nx = u_mC->size[0];
  for (k = 0; k < nx; k++) {
    if (u_mC->data[k].im == 0.0) {
      u_mC->data[k].re = exp(u_mC->data[k].re);
      u_mC->data[k].im = 0.0;
    } else if (rtIsInf(u_mC->data[k].im) && rtIsInf(u_mC->data[k].re) &&
               (u_mC->data[k].re < 0.0)) {
      u_mC->data[k].re = 0.0;
      u_mC->data[k].im = 0.0;
    } else {
      r = exp(u_mC->data[k].re / 2.0);
      u_mC->data[k].re = r * (r * cos(u_mC->data[k].im));
      u_mC->data[k].im = r * (r * sin(u_mC->data[k].im));
    }
  }

  /*  Complex Forward measurement */
  /*  Reflected */
  /*  Online residual generation */
  i = residual1->size[0];
  residual1->size[0] = y_mC->size[0] - 2;
  emxEnsureCapacity_real_T(residual1, i);
  nx = y_mC->size[0];
  for (i = 0; i <= nx - 3; i++) {
    residual1->data[i] = 0.0;
  }

  /*  [y_mC, u_mC, r_mC] = f_getData(facility, station, module, cavity); */
  i = u_mC->size[0];
  u_mC->size[0] = Forw_Ampl->size[0];
  emxEnsureCapacity_creal_T(u_mC, i);
  nx = Forw_Ampl->size[0];
  for (i = 0; i < nx; i++) {
    u_mC->data[i].re *= Forw_Ampl->data[i];
    u_mC->data[i].im *= Forw_Ampl->data[i];
  }

  emxInit_real_T(&u1, 1);

  /*  f_computeR1 computes the residual- denoted by residual 1- as defined in */
  /*  the Safeprocess paper. */
  /* -------------- input and states of the system--------------- */
  i = u1->size[0];
  u1->size[0] = u_mC->size[0];
  emxEnsureCapacity_real_T(u1, i);
  nx = u_mC->size[0];
  for (i = 0; i < nx; i++) {
    u1->data[i] = u_mC->data[i].re;
  }

  emxInit_real_T(&u2, 1);
  i = u2->size[0];
  u2->size[0] = u_mC->size[0];
  emxEnsureCapacity_real_T(u2, i);
  nx = u_mC->size[0];
  for (i = 0; i < nx; i++) {
    u2->data[i] = u_mC->data[i].im;
  }

  emxFree_creal_T(&u_mC);
  emxInit_real_T(&x1, 1);
  i = x1->size[0];
  x1->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T(x1, i);
  nx = y_mC->size[0];
  for (i = 0; i < nx; i++) {
    x1->data[i] = y_mC->data[i].re;
  }

  emxInit_real_T(&x2, 1);
  i = x2->size[0];
  x2->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T(x2, i);
  nx = y_mC->size[0];
  for (i = 0; i < nx; i++) {
    x2->data[i] = y_mC->data[i].im;
  }

  emxFree_creal_T(&y_mC);
  r = 1.0 / (FS * 1.0E+6);
  w12 = 4.0840704496667309E+9 / QL_nom;

  /*  ------------------- first residual------------------------- */
  if (3 > x1->size[0]) {
    i = 0;
    i1 = 0;
  } else {
    i = 2;
    i1 = x1->size[0];
  }

  if (2 > x1->size[0] - 1) {
    k = 0;
    i2 = 0;
  } else {
    k = 1;
    i2 = 1;
  }

  i3 = (2 <= u1->size[0] - 1);
  ai = 2.0 * r;
  if (3 > x2->size[0]) {
    i4 = 0;
  } else {
    i4 = 2;
  }

  if (2 > x2->size[0] - 1) {
    i5 = 0;
    i6 = 0;
  } else {
    i5 = 1;
    i6 = 1;
  }

  i7 = (2 <= u2->size[0] - 1);
  a = 2.0 * r;

  /*  r_1  = (x_d1.* (Ts.*x1(2:end-1,:)) - x_d2.*(Ts .* x2(2:end-1,:))); */
  i8 = (2 <= x1->size[0] - 1);
  i9 = (2 <= x2->size[0] - 1);
  nx = i1 - i;
  for (i1 = 0; i1 < nx; i1++) {
    residual1->data[i1] = ((-x1->data[i + i1] + x1->data[k + i1]) + (-r *
      x1->data[i2 + i1] + ai * u1->data[i3 + i1]) * w12) * x1->data[i8 + i1] -
      ((x2->data[i4 + i1] - x2->data[i5 + i1]) + (r * x2->data[i6 + i1] - a *
        u2->data[i7 + i1]) * w12) * x2->data[i9 + i1];
  }

  emxFree_real_T(&x2);
  emxFree_real_T(&x1);
  emxFree_real_T(&u2);
  emxFree_real_T(&u1);
}

/* End of code generation (f_generate_online_parityRes1_full.c) */
