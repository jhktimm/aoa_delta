/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mldivide.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

#ifndef MLDIVIDE_H
#define MLDIVIDE_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_calib_and_res_gen_ukf_types.h"

/* Function Declarations */
extern void b_mldivide(const emxArray_creal_T *A, const emxArray_creal_T *B,
  creal_T Y[4]);
extern void c_mldivide(const double A[4], const double B[4], double Y[4]);
extern void mldivide(const emxArray_creal_T *A, const emxArray_creal_T *B,
                     creal_T Y[2]);

#endif

/*
 * File trailer for mldivide.h
 *
 * [EOF]
 */
