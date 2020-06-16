/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xscal.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

#ifndef XSCAL_H
#define XSCAL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern void b_xscal(double a, double x[25], int ix0);
extern void xscal(double a, double x[16], int ix0);

#endif

/*
 * File trailer for xscal.h
 *
 * [EOF]
 */
