/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calcSigmaPoints.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Aug-2019 17:51:43
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
#include "f_generate_and_eval_residual_types.h"

/* Function Declarations */
extern void calcSigmaPoints(const double covariance[36], const double X1[6],
  double c, double X2[72]);

#endif

/*
 * File trailer for calcSigmaPoints.h
 *
 * [EOF]
 */
