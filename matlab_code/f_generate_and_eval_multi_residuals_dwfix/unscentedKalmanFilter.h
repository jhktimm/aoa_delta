/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: unscentedKalmanFilter.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

#ifndef UNSCENTEDKALMANFILTER_H
#define UNSCENTEDKALMANFILTER_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern unscentedKalmanFilter *c_unscentedKalmanFilter_unscent
  (unscentedKalmanFilter *UKF, const double varargin_3[6]);
extern unscentedKalmanFilter_1 *d_unscentedKalmanFilter_unscent
  (unscentedKalmanFilter_1 *UKF);

#endif

/*
 * File trailer for unscentedKalmanFilter.h
 *
 * [EOF]
 */
