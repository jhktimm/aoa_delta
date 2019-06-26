/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzgeev.h
 *
 * Code generation for function 'xzgeev'
 *
 */

#ifndef XZGEEV_H
#define XZGEEV_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_residual_types.h"

/* Function Declarations */
extern void b_xzgeev(const double A[36], int *info, creal_T alpha1[6], creal_T
                     beta1[6]);
extern void xzgeev(const double A[4], int *info, creal_T alpha1[2], creal_T
                   beta1[2]);

#endif

/* End of code generation (xzgeev.h) */
