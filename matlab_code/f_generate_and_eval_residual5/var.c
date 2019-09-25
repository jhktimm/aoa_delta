/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: var.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 24-Sep-2019 18:29:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "var.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double var(const emxArray_real_T *x)
{
  double y;
  int n;
  double xbar;
  int k;
  double t;
  n = x->size[0];
  if (x->size[0] == 0) {
    y = rtNaN;
  } else if (x->size[0] == 1) {
    if ((!rtIsInf(x->data[0])) && (!rtIsNaN(x->data[0]))) {
      y = 0.0;
    } else {
      y = rtNaN;
    }
  } else {
    xbar = x->data[0];
    for (k = 2; k <= n; k++) {
      xbar += x->data[k - 1];
    }

    xbar /= (double)x->size[0];
    y = 0.0;
    for (k = 1; k <= n; k++) {
      t = x->data[k - 1] - xbar;
      y += t * t;
    }

    y /= (double)x->size[0] - 1.0;
  }

  return y;
}

/*
 * File trailer for var.c
 *
 * [EOF]
 */
