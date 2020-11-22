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
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void b_calcSigmaPoints(const double covariance[4], const double X1[2],
  double c, double X2[8]);
extern void calcSigmaPoints(const double covariance[36], const double X1[6],
  double c, double X2[72]);

#endif

/* End of code generation (calcSigmaPoints.h) */
