/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: UnscentedKalmanFilter1.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "UnscentedKalmanFilter1.h"
#include "eig.h"

/* Function Definitions */

/*
 * Arguments    : unscentedKalmanFilter_1 *obj
 *                const double value[4]
 * Return Type  : void
 */
void c_UnscentedKalmanFilter_set_Pro(unscentedKalmanFilter_1 *obj, const double
  value[4])
{
  int i10;
  double b_value[4];
  creal_T unusedExpr[2];
  int i11;
  for (i10 = 0; i10 < 2; i10++) {
    for (i11 = 0; i11 < 2; i11++) {
      b_value[i11 + (i10 << 1)] = (value[i11 + (i10 << 1)] + value[i10 + (i11 <<
        1)]) / 2.0;
    }
  }

  eig(b_value, unusedExpr);
  for (i10 = 0; i10 < 4; i10++) {
    obj->pProcessNoise[i10] = value[i10];
  }
}

/*
 * File trailer for UnscentedKalmanFilter1.c
 *
 * [EOF]
 */
