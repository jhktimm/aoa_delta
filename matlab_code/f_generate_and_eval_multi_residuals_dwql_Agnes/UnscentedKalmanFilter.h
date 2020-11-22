/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * UnscentedKalmanFilter.h
 *
 * Code generation for function 'UnscentedKalmanFilter'
 *
 */

#ifndef UNSCENTEDKALMANFILTER_H
#define UNSCENTEDKALMANFILTER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void UnscentedKalmanFilter_correct(unscentedKalmanFilter *obj, const
  double z[2], double x_corr[6], double P_corr[36]);

#endif

/* End of code generation (UnscentedKalmanFilter.h) */
