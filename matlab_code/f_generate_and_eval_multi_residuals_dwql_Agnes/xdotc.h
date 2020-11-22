/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdotc.h
 *
 * Code generation for function 'xdotc'
 *
 */

#ifndef XDOTC_H
#define XDOTC_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern double b_xdotc(int n, const double x[16], int ix0, const double y[16],
                      int iy0);
extern double c_xdotc(int n, const double x[25], int ix0, const double y[25],
                      int iy0);
extern double xdotc(int n, const double x[20], int ix0, const double y[20], int
                    iy0);

#endif

/* End of code generation (xdotc.h) */
