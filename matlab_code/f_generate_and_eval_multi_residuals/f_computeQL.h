/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_computeQL.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

#ifndef F_COMPUTEQL_H
#define F_COMPUTEQL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern double f_computeQL(const emxArray_real_T *Rise, const emxArray_creal_T
  *u_mCal, const emxArray_creal_T *y_mC, double fs, double f0);

#endif

/*
 * File trailer for f_computeQL.h
 *
 * [EOF]
 */
