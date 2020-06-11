/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: var.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "var.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double var(const emxArray_real_T *x)
{
  double y;
  int i27;
  int d;
  int ix;
  double xbar;
  int k;
  double r;
  i27 = x->size[0];
  if (x->size[0] > 1) {
    d = x->size[0] - 1;
  } else {
    d = x->size[0];
  }

  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    ix = 0;
    xbar = x->data[0];
    for (k = 2; k <= i27; k++) {
      ix++;
      xbar += x->data[ix];
    }

    xbar /= (double)x->size[0];
    ix = 0;
    r = x->data[0] - xbar;
    y = r * r;
    for (k = 2; k <= i27; k++) {
      ix++;
      r = x->data[ix] - xbar;
      y += r * r;
    }

    y /= (double)d;
  }

  return y;
}

/*
 * File trailer for var.c
 *
 * [EOF]
 */
