/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_calib_and_res_gen_ukf_api.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_f_calib_and_res_gen_ukf_api.h"
#include "_coder_f_calib_and_res_gen_ukf_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131450U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "f_calib_and_res_gen_ukf",           /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y);
static const mxArray *b_emlrt_marshallOut(const real_T u[12]);
static real_T c_emlrt_marshallIn(const mxArray *FS, const char_T *identifier);
static const mxArray *c_emlrt_marshallOut(const creal_T u[4]);
static real_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static real_T (*e_emlrt_marshallIn(const mxArray *tau_m, const char_T
  *identifier))[4];
static void emlrt_marshallIn(const mxArray *PA, const char_T *identifier,
  emxArray_real_T *y);
static const mxArray *emlrt_marshallOut(const real_T u[6]);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
static real_T (*f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[4];
static void g_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret);
static real_T h_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static real_T (*i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[4];

/* Function Definitions */

/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y)
{
  g_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const real_T u[12]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u[12])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv2[3] = { 0, 0, 0 };

  static const int32_T iv3[3] = { 2, 2, 3 };

  y = NULL;
  m1 = emlrtCreateNumericArray(3, iv2, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m1, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m1, iv3, 3);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const mxArray *FS
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T c_emlrt_marshallIn(const mxArray *FS, const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(emlrtAlias(FS), &thisId);
  emlrtDestroyArray(&FS);
  return y;
}

/*
 * Arguments    : const creal_T u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const creal_T u[4])
{
  const mxArray *y;
  const mxArray *m2;
  static const int32_T iv4[1] = { 4 };

  y = NULL;
  m2 = emlrtCreateNumericArray(1, iv4, mxDOUBLE_CLASS, mxCOMPLEX);
  emlrtExportNumericArrayR2013b(emlrtRootTLSGlobal, m2, (void *)&u[0], 8);
  emlrtAssign(&y, m2);
  return y;
}

/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real_T y;
  y = h_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const mxArray *tau_m
 *                const char_T *identifier
 * Return Type  : real_T (*)[4]
 */
static real_T (*e_emlrt_marshallIn(const mxArray *tau_m, const char_T
  *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(emlrtAlias(tau_m), &thisId);
  emlrtDestroyArray(&tau_m);
  return y;
}
/*
 * Arguments    : const mxArray *PA
 *                const char_T *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
  static void emlrt_marshallIn(const mxArray *PA, const char_T *identifier,
  emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(emlrtAlias(PA), &thisId, y);
  emlrtDestroyArray(&PA);
}

/*
 * Arguments    : const real_T u[6]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u[6])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 0, 0 };

  static const int32_T iv1[2] = { 2, 3 };

  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m0, iv1, 2);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 * Return Type  : void
 */
static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int32_T numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(emlrtRootTLSGlobal, (void *)pEmxArray,
      (void (*)(void *))emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[4]
 */
static real_T (*f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[4]
{
  real_T (*y)[4];
  y = i_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
  static void g_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[1] = { -1 };

  const boolean_T bv0[1] = { true };

  int32_T iv5[1];
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
    dims, &bv0[0], iv5);
  ret->size[0] = iv5[0];
  ret->allocatedSize = ret->size[0];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T h_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 0U,
    &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[4]
 */
static real_T (*i_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[4]
{
  real_T (*ret)[4];
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
    dims);
  ret = (real_T (*)[4])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const mxArray * const prhs[14]
 *                const mxArray *plhs[4]
 * Return Type  : void
 */
  void f_calib_and_res_gen_ukf_api(const mxArray * const prhs[14], const mxArray
  *plhs[4])
{
  real_T (*residual_ukf)[6];
  real_T (*residual_ukf_mean)[6];
  real_T (*residual_ukf_Variance)[12];
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  real_T FS;
  real_T F0;
  real_T (*tau_m)[4];
  real_T (*K_m)[4];
  real_T (*X0)[4];
  real_T DELAY;
  real_T FILLING;
  real_T FLATTOP;
  creal_T cal_Coeff[4];
  residual_ukf = (real_T (*)[6])mxMalloc(sizeof(real_T [6]));
  residual_ukf_mean = (real_T (*)[6])mxMalloc(sizeof(real_T [6]));
  residual_ukf_Variance = (real_T (*)[12])mxMalloc(sizeof(real_T [12]));
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_real_T(&PA, 1, true);
  emxInit_real_T(&PP, 1, true);
  emxInit_real_T(&FA, 1, true);
  emxInit_real_T(&FP, 1, true);
  emxInit_real_T(&RA, 1, true);
  emxInit_real_T(&RP, 1, true);

  /* Marshall function inputs */
  emlrt_marshallIn(emlrtAlias(prhs[0]), "PA", PA);
  emlrt_marshallIn(emlrtAlias(prhs[1]), "PP", PP);
  emlrt_marshallIn(emlrtAlias(prhs[2]), "FA", FA);
  emlrt_marshallIn(emlrtAlias(prhs[3]), "FP", FP);
  emlrt_marshallIn(emlrtAlias(prhs[4]), "RA", RA);
  emlrt_marshallIn(emlrtAlias(prhs[5]), "RP", RP);
  FS = c_emlrt_marshallIn(emlrtAliasP(prhs[6]), "FS");
  F0 = c_emlrt_marshallIn(emlrtAliasP(prhs[7]), "F0");
  tau_m = e_emlrt_marshallIn(emlrtAlias(prhs[8]), "tau_m");
  K_m = e_emlrt_marshallIn(emlrtAlias(prhs[9]), "K_m");
  X0 = e_emlrt_marshallIn(emlrtAlias(prhs[10]), "X0");
  DELAY = c_emlrt_marshallIn(emlrtAliasP(prhs[11]), "DELAY");
  FILLING = c_emlrt_marshallIn(emlrtAliasP(prhs[12]), "FILLING");
  FLATTOP = c_emlrt_marshallIn(emlrtAliasP(prhs[13]), "FLATTOP");

  /* Invoke the target function */
  f_calib_and_res_gen_ukf(PA, PP, FA, FP, RA, RP, FS, F0, *tau_m, *K_m, *X0,
    DELAY, FILLING, FLATTOP, *residual_ukf, *residual_ukf_mean,
    *residual_ukf_Variance, cal_Coeff);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*residual_ukf);
  plhs[1] = emlrt_marshallOut(*residual_ukf_mean);
  plhs[2] = b_emlrt_marshallOut(*residual_ukf_Variance);
  plhs[3] = c_emlrt_marshallOut(cal_Coeff);
  RP->canFreeData = false;
  emxFree_real_T(&RP);
  RA->canFreeData = false;
  emxFree_real_T(&RA);
  FP->canFreeData = false;
  emxFree_real_T(&FP);
  FA->canFreeData = false;
  emxFree_real_T(&FA);
  PP->canFreeData = false;
  emxFree_real_T(&PP);
  PA->canFreeData = false;
  emxFree_real_T(&PA);
  emlrtHeapReferenceStackLeaveFcnR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void f_calib_and_res_gen_ukf_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  f_calib_and_res_gen_ukf_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void f_calib_and_res_gen_ukf_initialize(void)
{
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void f_calib_and_res_gen_ukf_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_f_calib_and_res_gen_ukf_api.c
 *
 * [EOF]
 */
