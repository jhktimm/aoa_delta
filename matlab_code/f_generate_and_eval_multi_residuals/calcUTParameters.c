/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calcUTParameters.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "calcUTParameters.h"

/* Function Definitions */

/*
 * Arguments    : double alpha
 *                double beta
 *                double kappa
 *                double *c
 *                double Wmean[2]
 *                double Wcov[2]
 *                double *OOM
 * Return Type  : void
 */
void calcUTParameters(double alpha, double beta, double kappa, double *c, double
                      Wmean[2], double Wcov[2], double *OOM)
{
  double b_Wmean;
  int i5;
  *c = alpha * alpha * (6.0 + kappa);
  Wmean[0] = 1.0 - 6.0 / *c;
  Wmean[1] = 1.0 / (2.0 * *c);
  Wcov[0] = Wmean[0] + ((1.0 - alpha * alpha) + beta);
  Wcov[1] = Wmean[1];
  if (Wmean[0] != 0.0) {
    *OOM = Wmean[0];
    b_Wmean = Wmean[0];
    for (i5 = 0; i5 < 2; i5++) {
      Wmean[i5] /= b_Wmean;
      Wcov[i5] /= *OOM;
    }
  } else {
    *OOM = 1.0;
  }
}

/*
 * File trailer for calcUTParameters.c
 *
 * [EOF]
 */
