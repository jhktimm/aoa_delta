/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_f_generate_and_eval_multi_residuals_api.c
 *
 * Code generation for function '_coder_f_generate_and_eval_multi_residuals_api'
 *
 */

/* Include files */
#include "tmwtypes.h"
#include "_coder_f_generate_and_eval_multi_residuals_api.h"
#include "_coder_f_generate_and_eval_multi_residuals_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131450U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "f_generate_and_eval_multi_residuals",/* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y);
static const mxArray *b_emlrt_marshallOut(const real_T u);
static real_T c_emlrt_marshallIn(const mxArray *FS, const char_T *identifier);
static real_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId);
static void e_emlrt_marshallIn(const mxArray *cal_coeff, const char_T
  *identifier, creal_T y[4]);
static void emlrt_marshallIn(const mxArray *PA, const char_T *identifier,
  emxArray_real_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions,
  boolean_T doPush);
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, creal_T y[4]);
static real_T (*g_emlrt_marshallIn(const mxArray *tau_m, const char_T
  *identifier))[4];
static real_T (*h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[4];
static real_T (*i_emlrt_marshallIn(const mxArray *Sigma_nom_UKF, const char_T
  *identifier))[4];
static real_T (*j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[4];
static real_T (*k_emlrt_marshallIn(const mxArray *r_mean_nom_UKF, const char_T
  *identifier))[2];
static real_T (*l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[2];
static real_T (*m_emlrt_marshallIn(const mxArray *ProcessVar, const char_T
  *identifier))[36];
static real_T (*n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId))[36];
static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret);
static real_T p_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId);
static void q_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, creal_T ret[4]);
static real_T (*r_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[4];
static real_T (*s_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[4];
static real_T (*t_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[2];
static real_T (*u_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[36];

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y)
{
  o_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m1;
  y = NULL;
  m1 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m1);
  return y;
}

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

static real_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real_T y;
  y = p_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void e_emlrt_marshallIn(const mxArray *cal_coeff, const char_T
  *identifier, creal_T y[4])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(emlrtAlias(cal_coeff), &thisId, y);
  emlrtDestroyArray(&cal_coeff);
}

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

static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[1] = { 0 };

  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m0, (void *)&u->data[0]);
  emlrtSetDimensions((mxArray *)m0, u->size, 1);
  emlrtAssign(&y, m0);
  return y;
}

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

static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, creal_T y[4])
{
  q_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T (*g_emlrt_marshallIn(const mxArray *tau_m, const char_T
  *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(emlrtAlias(tau_m), &thisId);
  emlrtDestroyArray(&tau_m);
  return y;
}
  static real_T (*h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[4]
{
  real_T (*y)[4];
  y = r_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*i_emlrt_marshallIn(const mxArray *Sigma_nom_UKF, const char_T
  *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(emlrtAlias(Sigma_nom_UKF), &thisId);
  emlrtDestroyArray(&Sigma_nom_UKF);
  return y;
}
  static real_T (*j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[4]
{
  real_T (*y)[4];
  y = s_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*k_emlrt_marshallIn(const mxArray *r_mean_nom_UKF, const char_T
  *identifier))[2]
{
  real_T (*y)[2];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = l_emlrt_marshallIn(emlrtAlias(r_mean_nom_UKF), &thisId);
  emlrtDestroyArray(&r_mean_nom_UKF);
  return y;
}
  static real_T (*l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[2]
{
  real_T (*y)[2];
  y = t_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*m_emlrt_marshallIn(const mxArray *ProcessVar, const char_T
  *identifier))[36]
{
  real_T (*y)[36];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = n_emlrt_marshallIn(emlrtAlias(ProcessVar), &thisId);
  emlrtDestroyArray(&ProcessVar);
  return y;
}
  static real_T (*n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[36]
{
  real_T (*y)[36];
  y = u_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void o_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[1] = { -1 };

  const boolean_T bv0[1] = { true };

  int32_T iv1[1];
  emlrtCheckVsBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
    dims, &bv0[0], iv1);
  ret->size[0] = iv1[0];
  ret->allocatedSize = ret->size[0];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static real_T p_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
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

static void q_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, creal_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", true, 1U,
    dims);
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, ret, 8, true);
  emlrtDestroyArray(&src);
}

static real_T (*r_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
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
  static real_T (*s_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId))[4]
{
  real_T (*ret)[4];
  static const int32_T dims[2] = { 2, 2 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 2U,
    dims);
  ret = (real_T (*)[4])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*t_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier *
  msgId))[2]
{
  real_T (*ret)[2];
  static const int32_T dims[1] = { 2 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 1U,
    dims);
  ret = (real_T (*)[2])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real_T (*u_emlrt_marshallIn(const mxArray *src, const
  emlrtMsgIdentifier *msgId))[36]
{
  real_T (*ret)[36];
  static const int32_T dims[2] = { 6, 6 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", false, 2U,
    dims);
  ret = (real_T (*)[36])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void f_generate_and_eval_multi_residuals_api(const mxArray *prhs[24], const
  mxArray *plhs[17])
{
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  emxArray_real_T *dw_trace_nom;
  emxArray_real_T *r_PS1_nom;
  emxArray_real_T *s_max_UKF;
  emxArray_real_T *s_max_dw;
  emxArray_real_T *s_max_PS1;
  emxArray_real_T *res_PS2;
  real_T FS;
  real_T F0;
  creal_T cal_coeff[4];
  real_T (*tau_m)[4];
  real_T (*K_m)[4];
  real_T (*X0)[4];
  real_T QL_nom;
  real_T DELAY;
  real_T FILLING;
  real_T FLATTOP;
  real_T (*Sigma_nom_UKF)[4];
  real_T (*r_mean_nom_UKF)[2];
  real_T (*MeasNoiseVar)[4];
  real_T (*ProcessVar)[36];
  real_T Sigma_nom_dw;
  real_T Sigma_nom_PS1;
  real_T classis_UKF;
  real_T classis_PS;
  real_T classis_dw;
  real_T strengthis_UKF;
  real_T strengthis_PS;
  real_T strengthis_dw;
  real_T QL;
  real_T dw_stat;
  real_T SP_F;
  real_T SP_P;
  real_T PC;
  real_T calib_check;
  real_T dec_hq;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_real_T(&PA, 1, true);
  emxInit_real_T(&PP, 1, true);
  emxInit_real_T(&FA, 1, true);
  emxInit_real_T(&FP, 1, true);
  emxInit_real_T(&RA, 1, true);
  emxInit_real_T(&RP, 1, true);
  emxInit_real_T(&dw_trace_nom, 1, true);
  emxInit_real_T(&r_PS1_nom, 1, true);
  emxInit_real_T(&s_max_UKF, 1, true);
  emxInit_real_T(&s_max_dw, 1, true);
  emxInit_real_T(&s_max_PS1, 1, true);
  emxInit_real_T(&res_PS2, 1, true);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);

  /* Marshall function inputs */
  emlrt_marshallIn(emlrtAlias(prhs[0]), "PA", PA);
  emlrt_marshallIn(emlrtAlias(prhs[1]), "PP", PP);
  emlrt_marshallIn(emlrtAlias(prhs[2]), "FA", FA);
  emlrt_marshallIn(emlrtAlias(prhs[3]), "FP", FP);
  emlrt_marshallIn(emlrtAlias(prhs[4]), "RA", RA);
  emlrt_marshallIn(emlrtAlias(prhs[5]), "RP", RP);
  FS = c_emlrt_marshallIn(emlrtAliasP(prhs[6]), "FS");
  F0 = c_emlrt_marshallIn(emlrtAliasP(prhs[7]), "F0");
  e_emlrt_marshallIn(emlrtAliasP(prhs[8]), "cal_coeff", cal_coeff);
  tau_m = g_emlrt_marshallIn(emlrtAlias(prhs[9]), "tau_m");
  K_m = g_emlrt_marshallIn(emlrtAlias(prhs[10]), "K_m");
  X0 = g_emlrt_marshallIn(emlrtAlias(prhs[11]), "X0");
  QL_nom = c_emlrt_marshallIn(emlrtAliasP(prhs[12]), "QL_nom");
  emlrt_marshallIn(emlrtAlias(prhs[13]), "dw_trace_nom", dw_trace_nom);
  DELAY = c_emlrt_marshallIn(emlrtAliasP(prhs[14]), "DELAY");
  FILLING = c_emlrt_marshallIn(emlrtAliasP(prhs[15]), "FILLING");
  FLATTOP = c_emlrt_marshallIn(emlrtAliasP(prhs[16]), "FLATTOP");
  Sigma_nom_UKF = i_emlrt_marshallIn(emlrtAlias(prhs[17]), "Sigma_nom_UKF");
  r_mean_nom_UKF = k_emlrt_marshallIn(emlrtAlias(prhs[18]), "r_mean_nom_UKF");
  MeasNoiseVar = i_emlrt_marshallIn(emlrtAlias(prhs[19]), "MeasNoiseVar");
  ProcessVar = m_emlrt_marshallIn(emlrtAlias(prhs[20]), "ProcessVar");
  Sigma_nom_dw = c_emlrt_marshallIn(emlrtAliasP(prhs[21]), "Sigma_nom_dw");
  emlrt_marshallIn(emlrtAlias(prhs[22]), "r_PS1_nom", r_PS1_nom);
  Sigma_nom_PS1 = c_emlrt_marshallIn(emlrtAliasP(prhs[23]), "Sigma_nom_PS1");

  /* Invoke the target function */
  f_generate_and_eval_multi_residuals(PA, PP, FA, FP, RA, RP, FS, F0, cal_coeff,
    *tau_m, *K_m, *X0, QL_nom, dw_trace_nom, DELAY, FILLING, FLATTOP,
    *Sigma_nom_UKF, *r_mean_nom_UKF, *MeasNoiseVar, *ProcessVar, Sigma_nom_dw,
    r_PS1_nom, Sigma_nom_PS1, s_max_UKF, s_max_dw, s_max_PS1, res_PS2,
    &classis_UKF, &classis_PS, &classis_dw, &strengthis_UKF, &strengthis_PS,
    &strengthis_dw, &QL, &dw_stat, &SP_F, &SP_P, &PC, &calib_check, &dec_hq);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(s_max_UKF);
  plhs[1] = emlrt_marshallOut(s_max_dw);
  plhs[2] = emlrt_marshallOut(s_max_PS1);
  plhs[3] = emlrt_marshallOut(res_PS2);
  plhs[4] = b_emlrt_marshallOut(classis_UKF);
  plhs[5] = b_emlrt_marshallOut(classis_PS);
  plhs[6] = b_emlrt_marshallOut(classis_dw);
  plhs[7] = b_emlrt_marshallOut(strengthis_UKF);
  plhs[8] = b_emlrt_marshallOut(strengthis_PS);
  plhs[9] = b_emlrt_marshallOut(strengthis_dw);
  plhs[10] = b_emlrt_marshallOut(QL);
  plhs[11] = b_emlrt_marshallOut(dw_stat);
  plhs[12] = b_emlrt_marshallOut(SP_F);
  plhs[13] = b_emlrt_marshallOut(SP_P);
  plhs[14] = b_emlrt_marshallOut(PC);
  plhs[15] = b_emlrt_marshallOut(calib_check);
  plhs[16] = b_emlrt_marshallOut(dec_hq);
  res_PS2->canFreeData = false;
  emxFree_real_T(&res_PS2);
  s_max_PS1->canFreeData = false;
  emxFree_real_T(&s_max_PS1);
  s_max_dw->canFreeData = false;
  emxFree_real_T(&s_max_dw);
  s_max_UKF->canFreeData = false;
  emxFree_real_T(&s_max_UKF);
  r_PS1_nom->canFreeData = false;
  emxFree_real_T(&r_PS1_nom);
  dw_trace_nom->canFreeData = false;
  emxFree_real_T(&dw_trace_nom);
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

void f_generate_and_eval_multi_residuals_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  f_generate_and_eval_multi_residuals_xil_terminate();
}

void f_generate_and_eval_multi_residuals_initialize(void)
{
  mexFunctionCreateRootTLS();
  emlrtClearAllocCountR2012b(emlrtRootTLSGlobal, false, 0U, 0);
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void f_generate_and_eval_multi_residuals_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_f_generate_and_eval_multi_residuals_api.c) */
