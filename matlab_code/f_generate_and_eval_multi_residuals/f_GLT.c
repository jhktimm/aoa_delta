/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_GLT.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_GLT.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"
#include "mldivide.h"
#include "f_generate_and_eval_multi_residuals_data.h"

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
  emxEnsureCapacity_real_T(s_max, ii);
  loop_ub = y->size[1];
  for (ii = 0; ii < loop_ub; ii++) {
    s_max->data[ii] = 0.0;
  }

  for (ii = 0; ii <= y->size[1] - 22; ii++) {
    y_bar = y->data[y->size[0] * ii];
    for (loop_ub = 0; loop_ub < 20; loop_ub++) {
      y_bar += y->data[y->size[0] * ((loop_ub + ii) + 1)];
    }

    y_bar *= 0.05;
    s_max->data[ii] = 10.0 * y_bar * (1.0 / Sigma) * y_bar;
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
  int i9;
  int loop_ub;
  int n;
  double b[4];
  int ii;
  int k;
  double y_bar[2];
  int xoffset;
  double b_y_bar;
  double dv2[2];
  i9 = s_max->size[0] * s_max->size[1];
  s_max->size[0] = 1;
  s_max->size[1] = y->size[1];
  emxEnsureCapacity_real_T(s_max, i9);
  loop_ub = y->size[1];
  for (i9 = 0; i9 < loop_ub; i9++) {
    s_max->data[i9] = 0.0;
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

  if (0 <= n - 12) {
    mldivide(Sigma, dv0, b);
  }

  for (ii = 0; ii <= n - 12; ii++) {
    for (loop_ub = 0; loop_ub < 2; loop_ub++) {
      y_bar[loop_ub] = y->data[loop_ub % 2 + y->size[0] * (loop_ub / 2 + ii)];
    }

    for (k = 0; k < 10; k++) {
      xoffset = (k + 1) << 1;
      for (loop_ub = 0; loop_ub < 2; loop_ub++) {
        i9 = xoffset + loop_ub;
        b_y_bar = y_bar[loop_ub] + y->data[i9 % 2 + y->size[0] * (i9 / 2 + ii)];
        y_bar[loop_ub] = b_y_bar;
      }
    }

    for (i9 = 0; i9 < 2; i9++) {
      y_bar[i9] *= 0.1;
    }

    b_y_bar = 0.0;
    for (i9 = 0; i9 < 2; i9++) {
      dv2[i9] = 0.0;
      for (loop_ub = 0; loop_ub < 2; loop_ub++) {
        dv2[i9] += 5.0 * y_bar[loop_ub] * b[loop_ub + (i9 << 1)];
      }

      b_y_bar += dv2[i9] * y_bar[i9];
    }

    s_max->data[ii] = b_y_bar;
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
