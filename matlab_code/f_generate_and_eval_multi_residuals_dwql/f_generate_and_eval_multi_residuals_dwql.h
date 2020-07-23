/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_and_eval_multi_residuals_dwql.h
 *
 * Code generation for function 'f_generate_and_eval_multi_residuals_dwql'
 *
 */

#ifndef F_GENERATE_AND_EVAL_MULTI_RESIDUALS_DWQL_H
#define F_GENERATE_AND_EVAL_MULTI_RESIDUALS_DWQL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void f_generate_and_eval_multi_residuals_dwql(const emxArray_real_T *PA,
  emxArray_real_T *PP, const emxArray_real_T *FA, emxArray_real_T *FP, const
  emxArray_real_T *RA, emxArray_real_T *RP, double FS, double F0, const creal_T
  cal_coeff[4], const emxArray_real_T *dwfix, const emxArray_real_T *w12fix,
  const double tau_m[4], const double K_m[4], const double X0[4], double QL_nom,
  double DELAY, double FILLING, double FLATTOP, const double Sigma_nom_UKF[4],
  const double Sigma_nom_UKF_dwfix[4], const double r_mean_nom_UKF_dwfix[2],
  const double r_mean_nom_UKF[2], const double MeasNoiseVar[4], const double
  ProcessVar[36], double alpha, const double r_mean_nom_dwql[2], const double
  Sigma_nom_dwql[4], const emxArray_real_T *r_PS1_nom, double Sigma_nom_PS1,
  emxArray_real_T *s_max_UKF, emxArray_real_T *s_max_UKF_dwfix, emxArray_real_T *
  s_max_dwql, emxArray_real_T *s_max_PS1, double *classis_UKF, double
  *classis_dwfix, double *classis_PS, double *classis_dwql, double
  *strengthis_UKF, double *strengthis_dwfix, double *strengthis_PS, double
  *strengthis_dwql, double *max_UKF, double *max_dwfix, double *max_PS, double
  *max_dwql, double *median_UKF, double *median_dwfix, double *median_PS, double
  *median_dwql, double *mode_UKF, double *mode_dwfix, double *mode_PS, double
  *mode_dwql, double *var_UKF, double *var_dwfix, double *var_PS, double
  *var_dwql, double *rm_I, double *rm_Q, double *rm_I_dwfix, double *rm_Q_dwfix,
  double *rvar_1, double *rvar_2, double *rvar_3, double *QL, double *dw_stat,
  double *SP_F, double *SP_P, double *PC, double *calib_check, double *dec_hq,
  double *zpth);

#endif

/* End of code generation (f_generate_and_eval_multi_residuals_dwql.h) */
