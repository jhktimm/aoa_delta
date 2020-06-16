/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xnrm2.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

#ifndef XNRM2_H
#define XNRM2_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern double b_xnrm2(int n, const double x[36], int ix0);
extern double c_xnrm2(int n, const double x[20], int ix0);
extern double d_xnrm2(int n, const double x[5], int ix0);
extern double xnrm2(int n, const double x[3]);

#endif

/*
 * File trailer for xnrm2.h
 *
 * [EOF]
 */
