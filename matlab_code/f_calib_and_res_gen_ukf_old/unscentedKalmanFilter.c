/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: unscentedKalmanFilter.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
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
  unscentedKalmanFilter *obj;
  int i;
  obj = *UKF;
  *UKF = obj;
  obj = *UKF;
  *UKF = obj;
  obj = *UKF;
  for (i = 0; i < 6; i++) {
    obj->pState[i] = varargin_3[i];
  }

  obj = *UKF;
  for (i = 0; i < 36; i++) {
    obj->pStateCovariance[i] = 0.0;
  }

  for (i = 0; i < 6; i++) {
    obj->pStateCovariance[i + 6 * i] = 1.0;
  }

  obj = *UKF;
  obj->pIsValidStateTransitionFcn = false;
  obj = *UKF;
  obj->pIsValidMeasurementFcn = false;
  (*UKF)->pIsValidMeasurementFcn = false;
  (*UKF)->pIsValidStateTransitionFcn = false;
  obj = *UKF;
  obj->Alpha = 0.001;
  obj = *UKF;
  obj->Beta = 2.0;
  obj = *UKF;
  obj->Kappa = 0.0;
  obj = *UKF;
  for (i = 0; i < 36; i++) {
    obj->pProcessNoise[i] = 0.0;
  }

  for (i = 0; i < 6; i++) {
    obj->pProcessNoise[i + 6 * i] = 1.0;
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
