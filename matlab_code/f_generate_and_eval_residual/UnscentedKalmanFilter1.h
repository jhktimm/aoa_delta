/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * UnscentedKalmanFilter1.h
 *
 * Code generation for function 'UnscentedKalmanFilter1'
 *
 */

#ifndef UNSCENTEDKALMANFILTER1_H
#define UNSCENTEDKALMANFILTER1_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_residual_types.h"

/* Function Declarations */
extern void c_UnscentedKalmanFilter_set_Mea(unscentedKalmanFilter *obj, const
  double value[4]);
extern void c_UnscentedKalmanFilter_set_Pro(unscentedKalmanFilter *obj, const
  double value[36]);

#endif

/* End of code generation (UnscentedKalmanFilter1.h) */
