/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: inv.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

#ifndef INV_H
#define INV_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_calib_and_res_gen_ukf_types.h"

/* Function Declarations */
extern void invNxN(const double x[16], double y[16]);

#endif

/*
 * File trailer for inv.h
 *
 * [EOF]
 */
