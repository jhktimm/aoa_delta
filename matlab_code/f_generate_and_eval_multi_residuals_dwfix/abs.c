/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: abs.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "abs.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"
#include "f_generate_and_eval_multi_residuals_dwfix_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_abs(const emxArray_creal_T *x, emxArray_real_T *y)
{
  unsigned int x_idx_0;
  int k;
  x_idx_0 = (unsigned int)x->size[0];
  k = y->size[0];
  y->size[0] = (int)x_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, sizeof(double));
  for (k = 0; k + 1 <= x->size[0]; k++) {
    y->data[k] = rt_hypotd_snf(x->data[k].re, x->data[k].im);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
