/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * unscentedKalmanFilter.c
 *
 * Code generation for function 'unscentedKalmanFilter'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "unscentedKalmanFilter.h"

/* Function Declarations */
static void d_unscentedKalmanFilter_unscent(unscentedKalmanFilter **UKF, const
  double varargin_3[6]);

/* Function Definitions */
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

unscentedKalmanFilter *c_unscentedKalmanFilter_unscent(unscentedKalmanFilter
  *UKF, const double varargin_3[6])
{
  unscentedKalmanFilter *b_UKF;
  b_UKF = UKF;
  d_unscentedKalmanFilter_unscent(&b_UKF, varargin_3);
  return b_UKF;
}

/* End of code generation (unscentedKalmanFilter.c) */
