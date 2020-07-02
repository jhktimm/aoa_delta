/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_computeQL.h
 *
 * Code generation for function 'f_computeQL'
 *
 */

#ifndef F_COMPUTEQL_H
#define F_COMPUTEQL_H

/* Include files */
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

/* End of code generation (f_computeQL.h) */
