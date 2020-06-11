/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calcSigmaPoints.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

#ifndef CALCSIGMAPOINTS_H
#define CALCSIGMAPOINTS_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern void b_calcSigmaPoints(const double covariance[4], const double X1[2],
  double c, double X2[8]);
extern void calcSigmaPoints(const double covariance[36], const double X1[6],
  double c, double X2[72]);

#endif

/*
 * File trailer for calcSigmaPoints.h
 *
 * [EOF]
 */
