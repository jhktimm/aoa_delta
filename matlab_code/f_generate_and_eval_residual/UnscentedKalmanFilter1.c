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
#include "f_generate_and_eval_residual.h"
#include "UnscentedKalmanFilter1.h"
#include "isSymmetricPositiveSemiDefinite.h"

/* Function Definitions */
void c_UnscentedKalmanFilter_set_Mea(unscentedKalmanFilter *obj, const double
  value[4])
{
  int i2;
  isSymmetricPositiveSemiDefinite(value);
  for (i2 = 0; i2 < 4; i2++) {
    obj->pMeasurementNoise[i2] = value[i2];
  }
}

void c_UnscentedKalmanFilter_set_Pro(unscentedKalmanFilter *obj, const double
  value[36])
{
  int i3;
  b_isSymmetricPositiveSemiDefini(value);
  for (i3 = 0; i3 < 36; i3++) {
    obj->pProcessNoise[i3] = value[i3];
  }
}

/* End of code generation (UnscentedKalmanFilter1.c) */
