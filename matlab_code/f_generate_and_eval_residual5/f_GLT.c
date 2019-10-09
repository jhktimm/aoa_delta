/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_GLT.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 24-Sep-2019 18:29:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_GLT.h"
#include "mldivide.h"
#include "f_generate_and_eval_residual_emxutil.h"
#include "f_generate_and_eval_residual_data.h"

/* Function Definitions */

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
  int u1;
  int n;
  int i8;
  double b[4];
  int ii;
  int k;
  double y_bar[2];
  int xoffset;
  double b_y_bar;
  double dv2[2];
  u1 = y->size[1];
  if (2 > u1) {
    u1 = 2;
  }

  if (y->size[1] == 0) {
    n = 0;
  } else {
    n = u1;
  }

  i8 = s_max->size[0] * s_max->size[1];
  s_max->size[0] = 1;
  s_max->size[1] = n;
  emxEnsureCapacity_real_T(s_max, i8);
  for (i8 = 0; i8 < n; i8++) {
    s_max->data[i8] = 0.0;
  }

  u1 = y->size[1];
  if (2 > u1) {
    u1 = 2;
  }

  if (y->size[1] == 0) {
    n = 0;
  } else {
    n = u1;
  }

  if (0 <= n - 12) {
    mldivide(Sigma, dv0, b);
  }

  for (ii = 0; ii <= n - 12; ii++) {
    for (u1 = 0; u1 < 2; u1++) {
      y_bar[u1] = y->data[u1 % 2 + y->size[0] * (u1 / 2 + ii)];
    }

    for (k = 0; k < 10; k++) {
      xoffset = (k + 1) << 1;
      for (u1 = 0; u1 < 2; u1++) {
        i8 = xoffset + u1;
        b_y_bar = y_bar[u1] + y->data[i8 % 2 + y->size[0] * (i8 / 2 + ii)];
        y_bar[u1] = b_y_bar;
      }
    }

    for (i8 = 0; i8 < 2; i8++) {
      y_bar[i8] *= 0.1;
    }

    b_y_bar = 0.0;
    for (i8 = 0; i8 < 2; i8++) {
      dv2[i8] = 0.0;
      for (u1 = 0; u1 < 2; u1++) {
        dv2[i8] += 5.0 * y_bar[u1] * b[u1 + (i8 << 1)];
      }

      b_y_bar += dv2[i8] * y_bar[i8];
    }

    s_max->data[ii] = b_y_bar;
  }
}

/*
 * File trailer for f_GLT.c
 *
 * [EOF]
 */