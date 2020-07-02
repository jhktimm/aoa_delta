/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xaxpy.c
 *
 * Code generation for function 'xaxpy'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "xaxpy.h"

/* Function Definitions */
void b_xaxpy(int n, double a, const double x[20], int ix0, double y[4], int iy0)
{
  int ix;
  int iy;
  int k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

void c_xaxpy(int n, double a, const double x[4], int ix0, double y[20], int iy0)
{
  int ix;
  int iy;
  int k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

void d_xaxpy(int n, double a, int ix0, double y[16], int iy0)
{
  int ix;
  int iy;
  int k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

void e_xaxpy(int n, double a, int ix0, double y[25], int iy0)
{
  int ix;
  int iy;
  int k;
  if ((n < 1) || (a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

void xaxpy(int n, double a, int ix0, double y[20], int iy0)
{
  int ix;
  int iy;
  int k;
  if (!(a == 0.0)) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* End of code generation (xaxpy.c) */
