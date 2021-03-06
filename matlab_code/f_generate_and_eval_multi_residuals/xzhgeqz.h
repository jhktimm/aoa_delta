/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzhgeqz.h
 *
 * Code generation for function 'xzhgeqz'
 *
 */

#ifndef XZHGEQZ_H
#define XZHGEQZ_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern void b_xzhgeqz(const creal_T A[36], int ilo, int ihi, int *info, creal_T
                      alpha1[6], creal_T beta1[6]);
extern void xzhgeqz(const creal_T A[4], int ilo, int ihi, int *info, creal_T
                    alpha1[2], creal_T beta1[2]);

#endif

/* End of code generation (xzhgeqz.h) */
