/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_detuning.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 16-Oct-2019 16:31:43
 */

#ifndef F_COMPUTE_DETUNING_H
#define F_COMPUTE_DETUNING_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_residual_types.h"

/* Function Declarations */
extern void f_compute_detuning(const emxArray_creal_T *y_mC, const
  emxArray_creal_T *u_mC, double fs, double QL, emxArray_real_T *dw);

#endif

/*
 * File trailer for f_compute_detuning.h
 *
 * [EOF]
 */
