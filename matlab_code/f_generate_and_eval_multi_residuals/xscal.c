/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xscal.c
 *
 * Code generation for function 'xscal'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "xscal.h"

/* Function Definitions */
void b_xscal(double a, double x[25], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 4; k++) {
    x[k - 1] *= a;
  }
}

void xscal(double a, double x[16], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 3; k++) {
    x[k - 1] *= a;
  }
}

/* End of code generation (xscal.c) */
