/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_calibrateData.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

#ifndef F_CALIBRATEDATA_H
#define F_CALIBRATEDATA_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern void f_calibrateData(const emxArray_creal_T *Forw, const emxArray_creal_T
  *Refl, const creal_T cof22[4], emxArray_creal_T *Forw_cal, emxArray_creal_T
  *Refl_cal);

#endif

/*
 * File trailer for f_calibrateData.h
 *
 * [EOF]
 */