/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_f_generate_and_eval_residual_api.h
 *
 * Code generation for function '_coder_f_generate_and_eval_residual_api'
 *
 */

#ifndef _CODER_F_GENERATE_AND_EVAL_RESIDUAL_API_H
#define _CODER_F_GENERATE_AND_EVAL_RESIDUAL_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_f_generate_and_eval_residual_api.h"

/* Type Definitions */
#ifndef struct_emxArray_creal_T
#define struct_emxArray_creal_T

struct emxArray_creal_T
{
  creal_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_creal_T*/

#ifndef typedef_emxArray_creal_T
#define typedef_emxArray_creal_T

typedef struct emxArray_creal_T emxArray_creal_T;

#endif                                 /*typedef_emxArray_creal_T*/

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
  MeasNoiseVar[4], real_T ProcessVar[36], emxArray_creal_T *r_cmplx,
  emxArray_real_T *s_max);
extern void f_generate_and_eval_residual_api(const mxArray * const prhs[20],
  const mxArray *plhs[2]);
extern void f_generate_and_eval_residual_atexit(void);
extern void f_generate_and_eval_residual_initialize(void);
extern void f_generate_and_eval_residual_terminate(void);
extern void f_generate_and_eval_residual_xil_terminate(void);

#endif

/* End of code generation (_coder_f_generate_and_eval_residual_api.h) */