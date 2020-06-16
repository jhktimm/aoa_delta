/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mldivide.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "mldivide.h"

/* Function Definitions */

/*
 * Arguments    : const double A[4]
 *                const double B[4]
 *                double Y[4]
 * Return Type  : void
 */
void mldivide(const double A[4], const double B[4], double Y[4])
{
  int r1;
  int r2;
  double a21;
  double a22;
  int k;
  if (fabs(A[1]) > fabs(A[0])) {
    r1 = 1;
    r2 = 0;
  } else {
    r1 = 0;
    r2 = 1;
  }

  a21 = A[r2] / A[r1];
  a22 = A[2 + r2] - a21 * A[2 + r1];
  for (k = 0; k < 2; k++) {
    Y[1 + (k << 1)] = (B[r2 + (k << 1)] - B[r1 + (k << 1)] * a21) / a22;
    Y[k << 1] = (B[r1 + (k << 1)] - Y[1 + (k << 1)] * A[2 + r1]) / A[r1];
  }
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */
