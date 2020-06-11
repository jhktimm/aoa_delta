/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzhgeqz.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

#ifndef XZHGEQZ_H
#define XZHGEQZ_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern void b_xzhgeqz(const creal_T A[36], int ilo, int ihi, int *info, creal_T
                      alpha1[6], creal_T beta1[6]);
extern void xzhgeqz(const creal_T A[4], int ilo, int ihi, int *info, creal_T
                    alpha1[2], creal_T beta1[2]);

#endif

/*
 * File trailer for xzhgeqz.h
 *
 * [EOF]
 */
