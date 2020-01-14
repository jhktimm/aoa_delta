/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xscal.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "xscal.h"

/* Function Definitions */

/*
 * Arguments    : double a
 *                double x[25]
 *                int ix0
 * Return Type  : void
 */
void b_xscal(double a, double x[25], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 4; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : double a
 *                double x[16]
 *                int ix0
 * Return Type  : void
 */
void xscal(double a, double x[16], int ix0)
{
  int k;
  for (k = ix0; k <= ix0 + 3; k++) {
    x[k - 1] *= a;
  }
}

/*
 * File trailer for xscal.c
 *
 * [EOF]
 */