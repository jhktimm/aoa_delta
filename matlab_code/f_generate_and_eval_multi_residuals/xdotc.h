/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xdotc.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

#ifndef XDOTC_H
#define XDOTC_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern double b_xdotc(int n, const double x[16], int ix0, const double y[16],
                      int iy0);
extern double c_xdotc(int n, const double x[25], int ix0, const double y[25],
                      int iy0);
extern double xdotc(int n, const double x[20], int ix0, const double y[20], int
                    iy0);

#endif

/*
 * File trailer for xdotc.h
 *
 * [EOF]
 */
