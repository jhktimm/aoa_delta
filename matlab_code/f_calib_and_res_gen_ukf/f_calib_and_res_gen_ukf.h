/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_calib_and_res_gen_ukf.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

#ifndef F_CALIB_AND_RES_GEN_UKF_H
#define F_CALIB_AND_RES_GEN_UKF_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_calib_and_res_gen_ukf_types.h"

/* Function Declarations */
extern void f_calib_and_res_gen_ukf(const emxArray_real_T *PA, const
  emxArray_real_T *PP, const emxArray_real_T *FA, const emxArray_real_T *FP,
  const emxArray_real_T *RA, const emxArray_real_T *RP, double FS, double F0,
  const double tau_m[4], const double K_m[4], const double X0[4], double DELAY,
  double FILLING, double FLATTOP, double residual_ukf[6], double
  residual_ukf_mean[6], double residual_ukf_Variance[12], creal_T cal_Coeff[4]);

#endif

/*
 * File trailer for f_calib_and_res_gen_ukf.h
 *
 * [EOF]
 */
