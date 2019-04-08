/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xscal.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

#ifndef XSCAL_H
#define XSCAL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_calib_and_res_gen_ukf_types.h"

/* Function Declarations */
extern void b_xscal(const creal_T a, emxArray_creal_T *x, int ix0);
extern void c_xscal(int n, const creal_T a, emxArray_creal_T *x, int ix0);
extern void d_xscal(const creal_T a, emxArray_creal_T *x, int ix0);
extern void xscal(int n, const creal_T a, emxArray_creal_T *x, int ix0);

#endif

/*
 * File trailer for xscal.h
 *
 * [EOF]
 */
