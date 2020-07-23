/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * var.c
 *
 * Code generation for function 'var'
 *
 */

/* Include files */
#include "var.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "rt_nonfinite.h"

/* Function Definitions */
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
    for (k = 0; k < n; k++) {
      t = x->data[k] - xbar;
      y += t * t;
    }

    y /= (double)x->size[0] - 1.0;
  }

  return y;
}

/* End of code generation (var.c) */
