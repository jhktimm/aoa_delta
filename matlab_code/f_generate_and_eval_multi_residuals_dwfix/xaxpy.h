/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xaxpy.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

#ifndef XAXPY_H
#define XAXPY_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern void b_xaxpy(int n, double a, const double x[20], int ix0, double y[4],
                    int iy0);
extern void c_xaxpy(int n, double a, const double x[4], int ix0, double y[20],
                    int iy0);
extern void d_xaxpy(int n, double a, int ix0, double y[16], int iy0);
extern void e_xaxpy(int n, double a, int ix0, double y[25], int iy0);
extern void xaxpy(int n, double a, int ix0, double y[20], int iy0);

#endif

/*
 * File trailer for xaxpy.h
 *
 * [EOF]
 */
