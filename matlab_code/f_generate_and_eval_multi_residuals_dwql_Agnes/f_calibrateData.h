/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_calibrateData.h
 *
 * Code generation for function 'f_calibrateData'
 *
 */

#ifndef F_CALIBRATEDATA_H
#define F_CALIBRATEDATA_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void f_calibrateData(const emxArray_creal_T *Forw, const emxArray_creal_T
  *Refl, const creal_T cof22[4], emxArray_creal_T *Forw_cal, emxArray_creal_T
  *Refl_cal);

#endif

/* End of code generation (f_calibrateData.h) */
