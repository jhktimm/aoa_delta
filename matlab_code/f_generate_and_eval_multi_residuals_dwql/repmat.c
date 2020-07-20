/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * repmat.c
 *
 * Code generation for function 'repmat'
 *
 */

/* Include files */
#include "repmat.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void repmat(const double a[2], double varargin_2, emxArray_real_T *b)
{
  int ibtile;
  int i;
  int jtilecol;
  ibtile = b->size[0] * b->size[1];
  b->size[0] = 2;
  i = (int)varargin_2;
  b->size[1] = i;
  emxEnsureCapacity_real_T(b, ibtile);
  for (jtilecol = 0; jtilecol < i; jtilecol++) {
    ibtile = jtilecol << 1;
    b->data[ibtile] = a[0];
    b->data[ibtile + 1] = a[1];
  }
}

/* End of code generation (repmat.c) */
