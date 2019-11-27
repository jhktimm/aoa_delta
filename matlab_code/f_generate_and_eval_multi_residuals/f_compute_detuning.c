/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_detuning.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_compute_detuning.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"
#include "rdivide.h"
#include "power.h"
#include "abs.h"
#include "diff.h"

/* Function Definitions */

/*
 * -------- Calculate w12 with the decay time--------------
 * Arguments    : const emxArray_creal_T *y_mC
 *                const emxArray_creal_T *u_mC
 *                double fs
 *                double QL
 *                emxArray_real_T *dw
 * Return Type  : void
 */
void f_compute_detuning(const emxArray_creal_T *y_mC, const emxArray_creal_T
  *u_mC, double fs, double QL, emxArray_real_T *dw)
{
  emxArray_real_T *dVI;
  double w12;
  unsigned int varargin_1_idx_0;
  double dt;
  int i2;
  int loop_ub;
  emxArray_real_T *dVQ;
  emxArray_real_T *b_y_mC;
  emxArray_real_T *dw2;
  emxArray_real_T *r4;
  emxArray_real_T *r5;
  emxInit_real_T1(&dVI, 1);
  w12 = 4.0840704496667309E+9 / QL;
  varargin_1_idx_0 = (unsigned int)y_mC->size[0];
  dt = 1.0 / fs;
  i2 = dVI->size[0];
  dVI->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(dVI, i2);
  loop_ub = y_mC->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    dVI->data[i2] = 0.0;
  }

  emxInit_real_T1(&dVQ, 1);
  i2 = dVQ->size[0];
  dVQ->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(dVQ, i2);
  loop_ub = y_mC->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    dVQ->data[i2] = 0.0;
  }

  emxInit_real_T1(&b_y_mC, 1);
  loop_ub = y_mC->size[0];
  i2 = b_y_mC->size[0];
  b_y_mC->size[0] = loop_ub;
  emxEnsureCapacity_real_T1(b_y_mC, i2);
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_y_mC->data[i2] = y_mC->data[i2].re;
  }

  emxInit_real_T1(&dw2, 1);
  diff(b_y_mC, dw2);
  dVI->data[0] = 0.0;
  loop_ub = dw2->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    dVI->data[i2 + 1] = dw2->data[i2] / dt;
  }

  loop_ub = y_mC->size[0];
  i2 = b_y_mC->size[0];
  b_y_mC->size[0] = loop_ub;
  emxEnsureCapacity_real_T1(b_y_mC, i2);
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_y_mC->data[i2] = y_mC->data[i2].im;
  }

  diff(b_y_mC, dw2);
  dVQ->data[0] = 0.0;
  loop_ub = dw2->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    dVQ->data[i2 + 1] = dw2->data[i2] / dt;
  }

  emxInit_real_T(&r4, 2);

  /* if sum(sum(isnan(dVI)))> 0 || sum(sum(isnan(dVQ)))>0 */
  /*     warning('the values of dw could not be calculated correctly!') */
  /* end */
  i2 = r4->size[0] * r4->size[1];
  r4->size[0] = (int)varargin_1_idx_0;
  r4->size[1] = 1;
  emxEnsureCapacity_real_T(r4, i2);
  loop_ub = (int)varargin_1_idx_0;
  for (i2 = 0; i2 < loop_ub; i2++) {
    r4->data[i2] = 2.0 * w12;
  }

  emxInit_real_T1(&r5, 1);
  b_abs(y_mC, dw2);
  power(dw2, r5);
  i2 = b_y_mC->size[0];
  b_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(b_y_mC, i2);
  loop_ub = y_mC->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_y_mC->data[i2] = y_mC->data[i2].re * (dVQ->data[i2] - r4->data[i2] *
      u_mC->data[i2].im);
  }

  rdivide(b_y_mC, r5, dVQ);
  i2 = r4->size[0] * r4->size[1];
  r4->size[0] = (int)varargin_1_idx_0;
  r4->size[1] = 1;
  emxEnsureCapacity_real_T(r4, i2);
  loop_ub = (int)varargin_1_idx_0;
  for (i2 = 0; i2 < loop_ub; i2++) {
    r4->data[i2] = 2.0 * w12;
  }

  b_abs(y_mC, dw2);
  power(dw2, r5);
  i2 = b_y_mC->size[0];
  b_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(b_y_mC, i2);
  loop_ub = y_mC->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_y_mC->data[i2] = y_mC->data[i2].im * (r4->data[i2] * u_mC->data[i2].re -
      dVI->data[i2]);
  }

  emxFree_real_T(&r4);
  emxFree_real_T(&dVI);
  rdivide(b_y_mC, r5, dw2);
  i2 = dw->size[0];
  dw->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(dw, i2);
  loop_ub = y_mC->size[0];
  emxFree_real_T(&b_y_mC);
  emxFree_real_T(&r5);
  for (i2 = 0; i2 < loop_ub; i2++) {
    dw->data[i2] = 0.0;
  }

  loop_ub = dVQ->size[0] - 1;
  for (i2 = 0; i2 <= loop_ub; i2++) {
    dw->data[i2] = dVQ->data[i2] + dw2->data[i2];
  }

  emxFree_real_T(&dw2);
  emxFree_real_T(&dVQ);

  /* -----------Plot-------------- */
  /*      figure(555) */
  /*      hold on */
  /*      plot([1:1:length(dw)-1]*1e-6,dw(1:end-1)) */
  /*      xlabel('Time') */
  /*      ylabel('\Delta\omega') */
  /*       */
}

/*
 * File trailer for f_compute_detuning.c
 *
 * [EOF]
 */
