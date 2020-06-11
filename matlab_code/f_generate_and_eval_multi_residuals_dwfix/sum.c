/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sum.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T x[1361]
 * Return Type  : double
 */
double b_sum(const boolean_T x[1361])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 1360; k++) {
    y += (double)x[k + 1];
  }

  return y;
}

/*
 * Arguments    : const emxArray_boolean_T *x
 * Return Type  : double
 */
double sum(const emxArray_boolean_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += (double)x->data[k - 1];
    }
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
