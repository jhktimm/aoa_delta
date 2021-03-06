/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calcUTParameters.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 06-Jun-2020 11:46:27
 */

#ifndef CALCUTPARAMETERS_H
#define CALCUTPARAMETERS_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern void calcUTParameters(double alpha, double beta, double kappa, double n,
  double *c, double Wmean[2], double Wcov[2], double *OOM);

#endif

/*
 * File trailer for calcUTParameters.h
 *
 * [EOF]
 */
