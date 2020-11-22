/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * isSymmetricPositiveSemiDefinite.c
 *
 * Code generation for function 'isSymmetricPositiveSemiDefinite'
 *
 */

/* Include files */
#include "isSymmetricPositiveSemiDefinite.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void isSymmetricPositiveSemiDefinite(const double value[4])
{
  double varargin_1_idx_0;
  double varargin_1_idx_1;
  int exponent;
  varargin_1_idx_0 = fabs(value[0]);
  varargin_1_idx_1 = fabs(value[3]);
  if ((varargin_1_idx_0 < varargin_1_idx_1) || (rtIsNaN(varargin_1_idx_0) &&
       (!rtIsNaN(varargin_1_idx_1)))) {
    varargin_1_idx_0 = varargin_1_idx_1;
  }

  if ((!rtIsInf(varargin_1_idx_0)) && (!rtIsNaN(varargin_1_idx_0)) &&
      (!(varargin_1_idx_0 <= 2.2250738585072014E-308))) {
    frexp(varargin_1_idx_0, &exponent);
  }
}

/* End of code generation (isSymmetricPositiveSemiDefinite.c) */
