/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_parity_Res1_full.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_compute_parity_Res1_full.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"

/* Function Definitions */

/*
 * f_computeR1 computes the residual- denoted by residual 1- as defined in
 *  the Safeprocess paper.
 * Arguments    : const emxArray_creal_T *u_mC
 *                const emxArray_creal_T *y_mC
 *                double fs
 *                double QL
 *                emxArray_real_T *r_1
 * Return Type  : void
 */
void f_compute_parity_Res1_full(const emxArray_creal_T *u_mC, const
  emxArray_creal_T *y_mC, double fs, double QL, emxArray_real_T *r_1)
{
  emxArray_real_T *u1;
  int i11;
  int loop_ub;
  emxArray_real_T *u2;
  emxArray_real_T *x1;
  emxArray_real_T *x2;
  double Ts;
  double w12;
  int i12;
  int i13;
  int i14;
  int i15;
  double a;
  int i16;
  int i17;
  int i18;
  int i19;
  double b_a;
  int i20;
  int i21;
  emxInit_real_T1(&u1, 1);

  /* -------------- input and states of the system--------------- */
  i11 = u1->size[0];
  u1->size[0] = u_mC->size[0];
  emxEnsureCapacity_real_T1(u1, i11);
  loop_ub = u_mC->size[0];
  for (i11 = 0; i11 < loop_ub; i11++) {
    u1->data[i11] = u_mC->data[i11].re;
  }

  emxInit_real_T1(&u2, 1);
  i11 = u2->size[0];
  u2->size[0] = u_mC->size[0];
  emxEnsureCapacity_real_T1(u2, i11);
  loop_ub = u_mC->size[0];
  for (i11 = 0; i11 < loop_ub; i11++) {
    u2->data[i11] = u_mC->data[i11].im;
  }

  emxInit_real_T1(&x1, 1);
  i11 = x1->size[0];
  x1->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(x1, i11);
  loop_ub = y_mC->size[0];
  for (i11 = 0; i11 < loop_ub; i11++) {
    x1->data[i11] = y_mC->data[i11].re;
  }

  emxInit_real_T1(&x2, 1);
  i11 = x2->size[0];
  x2->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(x2, i11);
  loop_ub = y_mC->size[0];
  for (i11 = 0; i11 < loop_ub; i11++) {
    x2->data[i11] = y_mC->data[i11].im;
  }

  Ts = 1.0 / fs;
  w12 = 4.0840704496667309E+9 / QL;

  /*  ------------------- first residual------------------------- */
  if (3 > x1->size[0]) {
    i11 = 0;
    i12 = 0;
  } else {
    i11 = 2;
    i12 = x1->size[0];
  }

  i13 = !(2 > x1->size[0] - 1);
  i14 = !(2 > x1->size[0] - 1);
  i15 = !(2 > u1->size[0] - 1);
  a = 2.0 * Ts;
  if (3 > x2->size[0]) {
    i16 = 0;
  } else {
    i16 = 2;
  }

  i17 = !(2 > x2->size[0] - 1);
  i18 = !(2 > x2->size[0] - 1);
  i19 = !(2 > u2->size[0] - 1);
  b_a = 2.0 * Ts;
  i20 = !(2 > x1->size[0] - 1);
  i21 = !(2 > x2->size[0] - 1);
  loop_ub = r_1->size[0];
  r_1->size[0] = i12 - i11;
  emxEnsureCapacity_real_T1(r_1, loop_ub);
  loop_ub = i12 - i11;
  for (i12 = 0; i12 < loop_ub; i12++) {
    r_1->data[i12] = ((-x1->data[i11 + i12] + x1->data[i13 + i12]) + (-Ts *
      x1->data[i14 + i12] + a * u1->data[i15 + i12] * w12)) * (Ts * x1->data[i20
      + i12]) - ((x2->data[i16 + i12] - x2->data[i17 + i12]) + (Ts * x2->
      data[i18 + i12] - b_a * u2->data[i19 + i12]) * w12) * (Ts * x2->data[i21 +
      i12]);
  }

  emxFree_real_T(&x2);
  emxFree_real_T(&x1);
  emxFree_real_T(&u2);
  emxFree_real_T(&u1);
}

/*
 * File trailer for f_compute_parity_Res1_full.c
 *
 * [EOF]
 */
