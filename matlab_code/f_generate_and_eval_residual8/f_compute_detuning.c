/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_detuning.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 16-Oct-2019 16:31:43
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_compute_detuning.h"
#include "f_generate_and_eval_residual_emxutil.h"
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
  int i9;
  int loop_ub;
  emxArray_real_T *dVQ;
  emxArray_real_T *b_y_mC;
  emxArray_real_T *dw2;
  emxArray_real_T *r6;
  emxArray_real_T *r7;
  emxInit_real_T1(&dVI, 1);
  w12 = 4.0840704496667309E+9 / QL;
  varargin_1_idx_0 = (unsigned int)y_mC->size[0];
  dt = 1.0 / fs;
  i9 = dVI->size[0];
  dVI->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(dVI, i9);
  loop_ub = y_mC->size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    dVI->data[i9] = 0.0;
  }

  emxInit_real_T1(&dVQ, 1);
  i9 = dVQ->size[0];
  dVQ->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(dVQ, i9);
  loop_ub = y_mC->size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    dVQ->data[i9] = 0.0;
  }

  emxInit_real_T1(&b_y_mC, 1);
  loop_ub = y_mC->size[0];
  i9 = b_y_mC->size[0];
  b_y_mC->size[0] = loop_ub;
  emxEnsureCapacity_real_T1(b_y_mC, i9);
  for (i9 = 0; i9 < loop_ub; i9++) {
    b_y_mC->data[i9] = y_mC->data[i9].re;
  }

  emxInit_real_T1(&dw2, 1);
  diff(b_y_mC, dw2);
  dVI->data[0] = 0.0;
  loop_ub = dw2->size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    dVI->data[i9 + 1] = dw2->data[i9] / dt;
  }

  loop_ub = y_mC->size[0];
  i9 = b_y_mC->size[0];
  b_y_mC->size[0] = loop_ub;
  emxEnsureCapacity_real_T1(b_y_mC, i9);
  for (i9 = 0; i9 < loop_ub; i9++) {
    b_y_mC->data[i9] = y_mC->data[i9].im;
  }

  diff(b_y_mC, dw2);
  dVQ->data[0] = 0.0;
  loop_ub = dw2->size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    dVQ->data[i9 + 1] = dw2->data[i9] / dt;
  }

  emxInit_real_T(&r6, 2);

  /* if sum(sum(isnan(dVI)))> 0 || sum(sum(isnan(dVQ)))>0 */
  /*     warning('the values of dw could not be calculated correctly!') */
  /* end */
  i9 = r6->size[0] * r6->size[1];
  r6->size[0] = (int)varargin_1_idx_0;
  r6->size[1] = 1;
  emxEnsureCapacity_real_T(r6, i9);
  loop_ub = (int)varargin_1_idx_0;
  for (i9 = 0; i9 < loop_ub; i9++) {
    r6->data[i9] = 2.0 * w12;
  }

  emxInit_real_T1(&r7, 1);
  b_abs(y_mC, dw2);
  power(dw2, r7);
  i9 = b_y_mC->size[0];
  b_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(b_y_mC, i9);
  loop_ub = y_mC->size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    b_y_mC->data[i9] = y_mC->data[i9].re * (dVQ->data[i9] - r6->data[i9] *
      u_mC->data[i9].im);
  }

  rdivide(b_y_mC, r7, dVQ);
  i9 = r6->size[0] * r6->size[1];
  r6->size[0] = (int)varargin_1_idx_0;
  r6->size[1] = 1;
  emxEnsureCapacity_real_T(r6, i9);
  loop_ub = (int)varargin_1_idx_0;
  for (i9 = 0; i9 < loop_ub; i9++) {
    r6->data[i9] = 2.0 * w12;
  }

  b_abs(y_mC, dw2);
  power(dw2, r7);
  i9 = b_y_mC->size[0];
  b_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(b_y_mC, i9);
  loop_ub = y_mC->size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    b_y_mC->data[i9] = y_mC->data[i9].im * (r6->data[i9] * u_mC->data[i9].re -
      dVI->data[i9]);
  }

  emxFree_real_T(&r6);
  emxFree_real_T(&dVI);
  rdivide(b_y_mC, r7, dw2);
  i9 = dw->size[0];
  dw->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(dw, i9);
  loop_ub = y_mC->size[0];
  emxFree_real_T(&b_y_mC);
  emxFree_real_T(&r7);
  for (i9 = 0; i9 < loop_ub; i9++) {
    dw->data[i9] = 0.0;
  }

  loop_ub = dVQ->size[0] - 1;
  for (i9 = 0; i9 <= loop_ub; i9++) {
    dw->data[i9] = dVQ->data[i9] + dw2->data[i9];
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
