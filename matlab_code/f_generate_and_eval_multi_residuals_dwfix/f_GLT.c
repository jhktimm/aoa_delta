/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_GLT.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "f_GLT.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"
#include "mldivide.h"

/* Function Definitions */

/*
 * The Generalized likelihood test adapted from S.Ding Model Based Fault Detection,
 *  Algorithm 10.4
 * Arguments    : double Sigma
 *                const emxArray_real_T *y
 *                emxArray_real_T *s_max
 * Return Type  : void
 */
void b_f_GLT(double Sigma, const emxArray_real_T *y, emxArray_real_T *s_max)
{
  int ii;
  int loop_ub;
  double y_bar;
  ii = s_max->size[0] * s_max->size[1];
  s_max->size[0] = 1;
  s_max->size[1] = y->size[1];
  emxEnsureCapacity((emxArray__common *)s_max, ii, sizeof(double));
  loop_ub = y->size[1];
  for (ii = 0; ii < loop_ub; ii++) {
    s_max->data[ii] = 0.0;
  }

  for (ii = 0; ii <= y->size[1] - 12; ii++) {
    y_bar = y->data[y->size[0] * ii];
    for (loop_ub = 0; loop_ub < 10; loop_ub++) {
      y_bar += y->data[y->size[0] * ((loop_ub + ii) + 1)];
    }

    y_bar *= 0.1;
    s_max->data[ii] = 5.0 * y_bar * (1.0 / Sigma) * y_bar;
  }

  /*  figure(103)  */
  /*  subplot(2,1,1) */
  /*  plot(y_bar(:,45:end).') */
  /*  subplot(2,1,2) */
  /*  plot(s_max(45:end)) */
}

/*
 * The Generalized likelihood test adapted from S.Ding Model Based Fault Detection,
 *  Algorithm 10.4
 * Arguments    : const double Sigma[4]
 *                const emxArray_real_T *y
 *                emxArray_real_T *s_max
 * Return Type  : void
 */
void f_GLT(const double Sigma[4], const emxArray_real_T *y, emxArray_real_T
           *s_max)
{
  int i8;
  int loop_ub;
  int n;
  int ii;
  double s;
  int k;
  static const double dv2[4] = { 1.0, 0.0, 0.0, 1.0 };

  double b[4];
  double y_bar[2];
  double dv3[2];
  i8 = s_max->size[0] * s_max->size[1];
  s_max->size[0] = 1;
  s_max->size[1] = y->size[1];
  emxEnsureCapacity((emxArray__common *)s_max, i8, sizeof(double));
  loop_ub = y->size[1];
  for (i8 = 0; i8 < loop_ub; i8++) {
    s_max->data[i8] = 0.0;
  }

  loop_ub = y->size[1];
  if (2 > loop_ub) {
    loop_ub = 2;
  }

  if (y->size[1] == 0) {
    n = 0;
  } else {
    n = loop_ub;
  }

  for (ii = 0; ii <= n - 12; ii++) {
    for (loop_ub = 0; loop_ub < 2; loop_ub++) {
      s = y->data[loop_ub % 2 + y->size[0] * (loop_ub / 2 + ii)];
      for (k = 0; k < 10; k++) {
        i8 = loop_ub + ((k + 1) << 1);
        s += y->data[i8 % 2 + y->size[0] * (i8 / 2 + ii)];
      }

      y_bar[loop_ub] = s;
    }

    for (i8 = 0; i8 < 2; i8++) {
      y_bar[i8] *= 0.1;
    }

    mldivide(Sigma, dv2, b);
    s = 0.0;
    for (i8 = 0; i8 < 2; i8++) {
      dv3[i8] = 0.0;
      for (loop_ub = 0; loop_ub < 2; loop_ub++) {
        dv3[i8] += 5.0 * y_bar[loop_ub] * b[loop_ub + (i8 << 1)];
      }

      s += dv3[i8] * y_bar[i8];
    }

    s_max->data[ii] = s;
  }

  /*  figure(103)  */
  /*  subplot(2,1,1) */
  /*  plot(y_bar(:,45:end).') */
  /*  subplot(2,1,2) */
  /*  plot(s_max(45:end)) */
}

/*
 * File trailer for f_GLT.c
 *
 * [EOF]
 */
