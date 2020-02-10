/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * calcSigmaPoints.h
 *
 * Code generation for function 'calcSigmaPoints'
 *
 */

#ifndef CALCSIGMAPOINTS_H
#define CALCSIGMAPOINTS_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern void calcSigmaPoints(const double covariance[36], const double X1[6],
  double c, double X2[72]);

#endif

/* End of code generation (calcSigmaPoints.h) */
