/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzlarf.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:09:16
 */

#ifndef XZLARF_H
#define XZLARF_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_calib_and_res_gen_ukf_types.h"

/* Function Declarations */
extern void xzlarf(int m, int n, int iv0, const creal_T tau, emxArray_creal_T *C,
                   int ic0, int ldc, creal_T work[4]);

#endif

/*
 * File trailer for xzlarf.h
 *
 * [EOF]
 */
