/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: UnscentedKalmanFilter1.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 24-Sep-2019 18:29:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
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
  int i3;
  isSymmetricPositiveSemiDefinite(value);
  for (i3 = 0; i3 < 4; i3++) {
    obj->pMeasurementNoise[i3] = value[i3];
  }
}

/*
 * File trailer for UnscentedKalmanFilter1.c
 *
 * [EOF]
 */
