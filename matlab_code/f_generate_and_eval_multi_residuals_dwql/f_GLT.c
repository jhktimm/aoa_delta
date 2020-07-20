/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_GLT.c
 *
 * Code generation for function 'f_GLT'
 *
 */

/* Include files */
#include "f_GLT.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void b_f_GLT(double Sigma, const emxArray_real_T *y, emxArray_real_T *s_max)
{
  int i;
  int loop_ub;
  double y_bar;
  int k;

  /*  The Generalized likelihood test adapted from S.Ding Model Based Fault Detection, */
  /*  Algorithm 10.4 */
  /*  */
  i = s_max->size[0] * s_max->size[1];
  s_max->size[0] = 1;
  s_max->size[1] = y->size[1];
  emxEnsureCapacity_real_T(s_max, i);
  loop_ub = y->size[1];
  for (i = 0; i < loop_ub; i++) {
    s_max->data[i] = 0.0;
  }

  i = y->size[1];
  for (loop_ub = 0; loop_ub <= i - 12; loop_ub++) {
    y_bar = y->data[loop_ub];
    for (k = 0; k < 10; k++) {
      y_bar += y->data[(k + loop_ub) + 1];
    }

    y_bar *= 0.1;
    s_max->data[loop_ub] = 5.0 * y_bar * (1.0 / Sigma) * y_bar;
  }

  /*  figure(103)  */
  /*  subplot(2,1,1) */
  /*  plot(y_bar(:,45:end).') */
  /*  subplot(2,1,2) */
  /*  plot(s_max(45:end)) */
}

void f_GLT(const double Sigma[4], const emxArray_real_T *y, emxArray_real_T
           *s_max)
{
  int i;
  int xoffset;
  int n;
  int ii;
  int r1;
  int r2;
  double y_bar_idx_0;
  double y_bar_idx_1;
  double a21;
  int k;
  double a22;
  double d;
  static const signed char B[4] = { 1, 0, 0, 1 };

  double Y_tmp;
  double d1;

  /*  The Generalized likelihood test adapted from S.Ding Model Based Fault Detection, */
  /*  Algorithm 10.4 */
  /*  */
  i = s_max->size[0] * s_max->size[1];
  s_max->size[0] = 1;
  s_max->size[1] = y->size[1];
  emxEnsureCapacity_real_T(s_max, i);
  xoffset = y->size[1];
  for (i = 0; i < xoffset; i++) {
    s_max->data[i] = 0.0;
  }

  if (y->size[1] == 0) {
    n = -12;
  } else if (2 > y->size[1]) {
    n = -10;
  } else {
    n = y->size[1] - 12;
  }

  if (0 <= n) {
    if (fabs(Sigma[1]) > fabs(Sigma[0])) {
      r1 = 1;
      r2 = 0;
    } else {
      r1 = 0;
      r2 = 1;
    }

    a21 = Sigma[r2] / Sigma[r1];
    a22 = Sigma[r2 + 2] - a21 * Sigma[r1 + 2];
  }

  for (ii = 0; ii <= n; ii++) {
    y_bar_idx_0 = y->data[2 * ii];
    y_bar_idx_1 = y->data[2 * ii + 1];
    for (k = 0; k < 10; k++) {
      xoffset = (k + 1) << 1;
      y_bar_idx_0 += y->data[xoffset % 2 + 2 * (xoffset / 2 + ii)];
      i = xoffset + 1;
      y_bar_idx_1 += y->data[i % 2 + 2 * (i / 2 + ii)];
    }

    y_bar_idx_0 *= 0.1;
    y_bar_idx_1 *= 0.1;
    d = ((double)B[r2] - (double)B[r1] * a21) / a22;
    Y_tmp = Sigma[r1 + 2];
    d1 = (5.0 * y_bar_idx_0 * (((double)B[r1] - d * Y_tmp) / Sigma[r1]) + 5.0 *
          y_bar_idx_1 * d) * y_bar_idx_0;
    i = B[r1 + 2];
    d = ((double)B[r2 + 2] - (double)i * a21) / a22;
    d1 += (5.0 * y_bar_idx_0 * (((double)i - d * Y_tmp) / Sigma[r1]) + 5.0 *
           y_bar_idx_1 * d) * y_bar_idx_1;
    s_max->data[ii] = d1;
  }

  /*  figure(103)  */
  /*  subplot(2,1,1) */
  /*  plot(y_bar(:,45:end).') */
  /*  subplot(2,1,2) */
  /*  plot(s_max(45:end)) */
}

/* End of code generation (f_GLT.c) */
