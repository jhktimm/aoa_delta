/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: UnscentedKalmanFilter1.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "UnscentedKalmanFilter1.h"
#include "isSymmetricPositiveSemiDefinite.h"

/* Function Definitions */

/*
 * Arguments    : unscentedKalmanFilter *obj
 *                const double value[4]
 * Return Type  : void
 */
void c_UnscentedKalmanFilter_set_Mea(unscentedKalmanFilter *obj, const double
  value[4])
{
  int i4;
  isSymmetricPositiveSemiDefinite(value);
  for (i4 = 0; i4 < 4; i4++) {
    obj->pMeasurementNoise[i4] = value[i4];
  }
}

/*
 * File trailer for UnscentedKalmanFilter1.c
 *
 * [EOF]
 */
