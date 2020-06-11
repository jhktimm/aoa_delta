/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_parity_Res1_full.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "f_compute_parity_Res1_full.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"

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
  int i13;
  int loop_ub;
  emxArray_real_T *u2;
  emxArray_real_T *x1;
  emxArray_real_T *x2;
  double Ts;
  double w12;
  int i14;
  int i15;
  int i16;
  int i17;
  double a;
  int i18;
  int i19;
  int i20;
  int i21;
  double b_a;
  int i22;
  int i23;
  emxInit_real_T1(&u1, 1);

  /* -------------- input and states of the system--------------- */
  i13 = u1->size[0];
  u1->size[0] = u_mC->size[0];
  emxEnsureCapacity((emxArray__common *)u1, i13, sizeof(double));
  loop_ub = u_mC->size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    u1->data[i13] = u_mC->data[i13].re;
  }

  emxInit_real_T1(&u2, 1);
  i13 = u2->size[0];
  u2->size[0] = u_mC->size[0];
  emxEnsureCapacity((emxArray__common *)u2, i13, sizeof(double));
  loop_ub = u_mC->size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    u2->data[i13] = u_mC->data[i13].im;
  }

  emxInit_real_T1(&x1, 1);
  i13 = x1->size[0];
  x1->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)x1, i13, sizeof(double));
  loop_ub = y_mC->size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    x1->data[i13] = y_mC->data[i13].re;
  }

  emxInit_real_T1(&x2, 1);
  i13 = x2->size[0];
  x2->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)x2, i13, sizeof(double));
  loop_ub = y_mC->size[0];
  for (i13 = 0; i13 < loop_ub; i13++) {
    x2->data[i13] = y_mC->data[i13].im;
  }

  Ts = 1.0 / fs;
  w12 = 4.0840704496667309E+9 / QL;

  /*  ------------------- first residual------------------------- */
  if (3 > x1->size[0]) {
    i13 = 0;
    i14 = 0;
  } else {
    i13 = 2;
    i14 = x1->size[0];
  }

  i15 = !(2 > x1->size[0] - 1);
  i16 = !(2 > x1->size[0] - 1);
  i17 = !(2 > u1->size[0] - 1);
  a = 2.0 * Ts;
  if (3 > x2->size[0]) {
    i18 = 0;
  } else {
    i18 = 2;
  }

  i19 = !(2 > x2->size[0] - 1);
  i20 = !(2 > x2->size[0] - 1);
  i21 = !(2 > u2->size[0] - 1);
  b_a = 2.0 * Ts;
  i22 = !(2 > x1->size[0] - 1);
  i23 = !(2 > x2->size[0] - 1);
  loop_ub = r_1->size[0];
  r_1->size[0] = i14 - i13;
  emxEnsureCapacity((emxArray__common *)r_1, loop_ub, sizeof(double));
  loop_ub = i14 - i13;
  for (i14 = 0; i14 < loop_ub; i14++) {
    r_1->data[i14] = ((-x1->data[i13 + i14] + x1->data[i15 + i14]) + (-Ts *
      x1->data[i16 + i14] + a * u1->data[i17 + i14] * w12)) * (Ts * x1->data[i22
      + i14]) - ((x2->data[i18 + i14] - x2->data[i19 + i14]) + (Ts * x2->
      data[i20 + i14] - b_a * u2->data[i21 + i14]) * w12) * (Ts * x2->data[i23 +
      i14]);
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
