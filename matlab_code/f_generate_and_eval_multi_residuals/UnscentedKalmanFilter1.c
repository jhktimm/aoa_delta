/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * UnscentedKalmanFilter1.c
 *
 * Code generation for function 'UnscentedKalmanFilter1'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "UnscentedKalmanFilter1.h"
#include "isSymmetricPositiveSemiDefinite.h"

/* Function Definitions */
void c_UnscentedKalmanFilter_set_Mea(unscentedKalmanFilter *obj, const double
  value[4])
{
  int i4;
  isSymmetricPositiveSemiDefinite(value);
  for (i4 = 0; i4 < 4; i4++) {
    obj->pMeasurementNoise[i4] = value[i4];
  }
}

void c_UnscentedKalmanFilter_set_Pro(unscentedKalmanFilter *obj, const double
  value[36])
{
  int i5;
  b_isSymmetricPositiveSemiDefini(value);
  for (i5 = 0; i5 < 36; i5++) {
    obj->pProcessNoise[i5] = value[i5];
  }
}

/* End of code generation (UnscentedKalmanFilter1.c) */
