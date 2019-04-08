/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_calib_and_res_gen_ukf_api.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

#ifndef _CODER_F_CALIB_AND_RES_GEN_UKF_API_H
#define _CODER_F_CALIB_AND_RES_GEN_UKF_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_f_calib_and_res_gen_ukf_api.h"

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
extern void f_calib_and_res_gen_ukf(emxArray_real_T *PA, emxArray_real_T *PP,
  emxArray_real_T *FA, emxArray_real_T *FP, emxArray_real_T *RA, emxArray_real_T
  *RP, real_T FS, real_T F0, real_T tau_m[4], real_T K_m[4], real_T X0[4],
  real_T DELAY, real_T FILLING, real_T FLATTOP, real_T residual_ukf[6], real_T
  residual_ukf_mean[6], real_T residual_ukf_Variance[12], creal_T cal_Coeff[4]);
extern void f_calib_and_res_gen_ukf_api(const mxArray * const prhs[14], const
  mxArray *plhs[4]);
extern void f_calib_and_res_gen_ukf_atexit(void);
extern void f_calib_and_res_gen_ukf_initialize(void);
extern void f_calib_and_res_gen_ukf_terminate(void);
extern void f_calib_and_res_gen_ukf_xil_terminate(void);

#endif

/*
 * File trailer for _coder_f_calib_and_res_gen_ukf_api.h
 *
 * [EOF]
 */
