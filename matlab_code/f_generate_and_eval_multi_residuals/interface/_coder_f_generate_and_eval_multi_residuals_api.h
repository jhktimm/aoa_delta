/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_generate_and_eval_multi_residuals_api.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

#ifndef _CODER_F_GENERATE_AND_EVAL_MULTI_RESIDUALS_API_H
#define _CODER_F_GENERATE_AND_EVAL_MULTI_RESIDUALS_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_f_generate_and_eval_multi_residuals_api.h"

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
extern void f_generate_and_eval_multi_residuals(emxArray_real_T *PA,
  emxArray_real_T *PP, emxArray_real_T *FA, emxArray_real_T *FP, emxArray_real_T
  *RA, emxArray_real_T *RP, real_T FS, real_T F0, creal_T cal_coeff[4], real_T
  tau_m[4], real_T K_m[4], real_T X0[4], real_T QL_nom, emxArray_real_T
  *dw_trace_nom, real_T DELAY, real_T FILLING, real_T FLATTOP, real_T
  Sigma_nom_UKF[4], real_T r_mean_nom_UKF[2], real_T MeasNoiseVar[4], real_T
  ProcessVar[36], real_T Sigma_nom_dw, emxArray_real_T *r_PS1_nom, real_T
  Sigma_nom_PS1, emxArray_real_T *s_max_UKF, emxArray_real_T *s_max_dw,
  emxArray_real_T *s_max_PS1, emxArray_real_T *res_PS2, real_T *classis_UKF,
  real_T *classis_PS, real_T *classis_dw, real_T *strengthis_UKF, real_T
  *strengthis_PS, real_T *strengthis_dw, real_T *QL, real_T *dw_stat, real_T
  *SP_F, real_T *SP_P, real_T *PC, real_T *calib_check, real_T *dec_hq);
extern void f_generate_and_eval_multi_residuals_api(const mxArray *prhs[24],
  const mxArray *plhs[17]);
extern void f_generate_and_eval_multi_residuals_atexit(void);
extern void f_generate_and_eval_multi_residuals_initialize(void);
extern void f_generate_and_eval_multi_residuals_terminate(void);
extern void f_generate_and_eval_multi_residuals_xil_terminate(void);

#endif

/*
 * File trailer for _coder_f_generate_and_eval_multi_residuals_api.h
 *
 * [EOF]
 */