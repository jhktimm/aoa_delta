/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: unscentedKalmanFilter.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 15-Oct-2019 14:56:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "unscentedKalmanFilter.h"

/* Function Declarations */
static void d_unscentedKalmanFilter_unscent(unscentedKalmanFilter **UKF, const
  double varargin_3[6]);

/* Function Definitions */

/*
 * Arguments    : unscentedKalmanFilter **UKF
 *                const double varargin_3[6]
 * Return Type  : void
 */
static void d_unscentedKalmanFilter_unscent(unscentedKalmanFilter **UKF, const
  double varargin_3[6])
{
  int i;
  for (i = 0; i < 6; i++) {
    (*UKF)->pState[i] = varargin_3[i];
  }

  for (i = 0; i < 36; i++) {
    (*UKF)->pStateCovariance[i] = 0.0;
  }

  for (i = 0; i < 6; i++) {
    (*UKF)->pStateCovariance[i + 6 * i] = 1.0;
  }

  (*UKF)->pIsValidStateTransitionFcn = false;
  (*UKF)->pIsValidMeasurementFcn = false;
  (*UKF)->pIsValidMeasurementFcn = false;
  (*UKF)->pIsValidStateTransitionFcn = false;
  (*UKF)->Alpha = 0.001;
  (*UKF)->Beta = 2.0;
  (*UKF)->Kappa = 0.0;
  for (i = 0; i < 36; i++) {
    (*UKF)->pProcessNoise[i] = 0.0;
  }

  for (i = 0; i < 6; i++) {
    (*UKF)->pProcessNoise[i + 6 * i] = 1.0;
  }
}

/*
 * Arguments    : unscentedKalmanFilter *UKF
 *                const double varargin_3[6]
 * Return Type  : unscentedKalmanFilter *
 */
unscentedKalmanFilter *c_unscentedKalmanFilter_unscent(unscentedKalmanFilter
  *UKF, const double varargin_3[6])
{
  unscentedKalmanFilter *b_UKF;
  b_UKF = UKF;
  d_unscentedKalmanFilter_unscent(&b_UKF, varargin_3);
  return b_UKF;
}

/*
 * File trailer for unscentedKalmanFilter.c
 *
 * [EOF]
 */
