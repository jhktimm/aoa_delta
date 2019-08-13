/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_ukf_residual_not_pers.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Aug-2019 17:51:43
 */

#ifndef F_COMPUTE_UKF_RESIDUAL_NOT_PERS_H
#define F_COMPUTE_UKF_RESIDUAL_NOT_PERS_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_residual_types.h"

/* Function Declarations */
extern void f_compute_ukf_residual_not_pers(const double initialStateGuess[6],
  const double MeasNoiseVar[4], const double ProcessVar[36], const
  emxArray_real_T *y_Meas, const emxArray_real_T *u_Meas, double fs, double QL,
  const double tau_m[4], const double K_m[4], emxArray_real_T *residual_mean,
  emxArray_real_T *residual_Variance, emxArray_real_T *residual_xi,
  emxArray_real_T *residual_Info);

#endif

/*
 * File trailer for f_compute_ukf_residual_not_pers.h
 *
 * [EOF]
 */
