/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_f_generate_and_eval_multi_residuals_dwql_api.h
 *
 * Code generation for function '_coder_f_generate_and_eval_multi_residuals_dwql_api'
 *
 */

#ifndef _CODER_F_GENERATE_AND_EVAL_MULTI_RESIDUALS_DWQL_API_H
#define _CODER_F_GENERATE_AND_EVAL_MULTI_RESIDUALS_DWQL_API_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void f_generate_and_eval_multi_residuals_dwql(emxArray_real_T *PA,
  emxArray_real_T *PP, emxArray_real_T *FA, emxArray_real_T *FP, emxArray_real_T
  *RA, emxArray_real_T *RP, real_T FS, real_T F0, creal_T cal_coeff[4],
  emxArray_real_T *dwfix, emxArray_real_T *w12fix, real_T tau_m[4], real_T K_m[4],
  real_T X0[4], real_T QL_nom, real_T DELAY, real_T FILLING, real_T FLATTOP,
  real_T Sigma_nom_UKF[4], real_T Sigma_nom_UKF_dwfix[4], real_T
  r_mean_nom_UKF_dwfix[2], real_T r_mean_nom_UKF[2], real_T MeasNoiseVar[4],
  real_T ProcessVar[36], real_T alpha, real_T r_mean_nom_dwql[2], real_T
  Sigma_nom_dwql[4], emxArray_real_T *r_PS1_nom, real_T Sigma_nom_PS1,
  emxArray_real_T *s_max_UKF, emxArray_real_T *s_max_UKF_dwfix, emxArray_real_T *
  s_max_dwql, emxArray_real_T *s_max_PS1, real_T *classis_UKF, real_T
  *classis_dwfix, real_T *classis_PS, real_T *classis_dwql, real_T
  *strengthis_UKF, real_T *strengthis_dwfix, real_T *strengthis_PS, real_T
  *strengthis_dwql, real_T *max_UKF, real_T *max_dwfix, real_T *max_PS, real_T
  *max_dwql, real_T *median_UKF, real_T *median_dwfix, real_T *median_PS, real_T
  *median_dwql, real_T *mode_UKF, real_T *mode_dwfix, real_T *mode_PS, real_T
  *mode_dwql, real_T *var_UKF, real_T *var_dwfix, real_T *var_PS, real_T
  *var_dwql, real_T *rm_I, real_T *rm_Q, real_T *rm_I_dwfix, real_T *rm_Q_dwfix,
  real_T *rvar_1, real_T *rvar_2, real_T *rvar_3, real_T *QL, real_T *dw_stat,
  real_T *SP_F, real_T *SP_P, real_T *PC, real_T *calib_check, real_T *dec_hq,
  real_T *zpth);
extern void f_generate_and_eval_multi_residuals_dwql_api(const mxArray * const
  prhs[29], int32_T nlhs, const mxArray *plhs[43]);
extern void f_generate_and_eval_multi_residuals_dwql_atexit(void);
extern void f_generate_and_eval_multi_residuals_dwql_initialize(void);
extern void f_generate_and_eval_multi_residuals_dwql_terminate(void);
extern void f_generate_and_eval_multi_residuals_dwql_xil_shutdown(void);
extern void f_generate_and_eval_multi_residuals_dwql_xil_terminate(void);

#endif

/* End of code generation (_coder_f_generate_and_eval_multi_residuals_dwql_api.h) */
