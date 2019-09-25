/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calcUTParameters.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 24-Sep-2019 18:29:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
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
  int i4;
  *c = alpha * alpha * (6.0 + kappa);
  Wmean[0] = 1.0 - 6.0 / *c;
  Wmean[1] = 1.0 / (2.0 * *c);
  Wcov[0] = Wmean[0] + ((1.0 - alpha * alpha) + beta);
  Wcov[1] = Wmean[1];
  if (Wmean[0] != 0.0) {
    *OOM = Wmean[0];
    b_Wmean = Wmean[0];
    for (i4 = 0; i4 < 2; i4++) {
      Wmean[i4] /= b_Wmean;
      Wcov[i4] /= *OOM;
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
