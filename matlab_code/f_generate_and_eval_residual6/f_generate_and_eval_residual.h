/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_and_eval_residual.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Sep-2019 16:47:25
 */

#ifndef F_GENERATE_AND_EVAL_RESIDUAL_H
#define F_GENERATE_AND_EVAL_RESIDUAL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_residual_types.h"

/* Function Declarations */
extern void f_generate_and_eval_residual(const emxArray_real_T *PA,
  emxArray_real_T *PP, const emxArray_real_T *FA, const emxArray_real_T *FP,
  const emxArray_real_T *RA, const emxArray_real_T *RP, double FS, double F0,
  const creal_T cal_coeff[4], const double tau_m[4], const double K_m[4], const
  double X0[4], double QL_nom, double DELAY, double FILLING, double FLATTOP,
  const double Sigma_nom[4], const double r_mean_nom[2], const double
  MeasNoiseVar[4], const double ProcessVar[36], emxArray_real_T *s_max, double
  *classis, double *strengthis, double *strengtVar, double *maxis, double *minis,
  double *QL, double *dw_stat, double *SP_F, double *SP_P, double *PC, double
  *calib_check, double *dec_hq);

#endif

/*
 * File trailer for f_generate_and_eval_residual.h
 *
 * [EOF]
 */
