/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_generate_and_eval_residual_api.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 24-Sep-2019 18:29:39
 */

#ifndef _CODER_F_GENERATE_AND_EVAL_RESIDUAL_API_H
#define _CODER_F_GENERATE_AND_EVAL_RESIDUAL_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_f_generate_and_eval_residual_api.h"

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
extern void f_generate_and_eval_residual(emxArray_real_T *PA, emxArray_real_T
  *PP, emxArray_real_T *FA, emxArray_real_T *FP, emxArray_real_T *RA,
  emxArray_real_T *RP, real_T FS, real_T F0, creal_T cal_coeff[4], real_T tau_m
  [4], real_T K_m[4], real_T X0[4], real_T QL_nom, real_T DELAY, real_T FILLING,
  real_T FLATTOP, real_T Sigma_nom[4], real_T r_mean_nom[2], real_T
  MeasNoiseVar[4], real_T ProcessVar[36], emxArray_real_T *s_max, real_T
  *classis, real_T *strengthis, real_T *strengtVar, real_T *maxis, real_T *minis,
  real_T *QL, real_T *dw_stat, real_T *SP_F, real_T *SP_P, boolean_T *PC, real_T
  *calib_check);
extern void f_generate_and_eval_residual_api(const mxArray *prhs[20], const
  mxArray *plhs[12]);
extern void f_generate_and_eval_residual_atexit(void);
extern void f_generate_and_eval_residual_initialize(void);
extern void f_generate_and_eval_residual_terminate(void);
extern void f_generate_and_eval_residual_xil_terminate(void);

#endif

/*
 * File trailer for _coder_f_generate_and_eval_residual_api.h
 *
 * [EOF]
 */
