/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_generate_and_eval_multi_residuals_dwfix_api.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_f_generate_and_eval_multi_residuals_dwfix_api.h"
#include "_coder_f_generate_and_eval_multi_residuals_dwfix_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131450U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "f_generate_and_eval_multi_residuals_dwfix",/* fFunctionName */
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
static real_T (*k_emlrt_marshallIn(const mxArray *r_mean_nom_UKF_dwfix, const
  char_T *identifier))[2];
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

/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, emxArray_real_T *y)
{
  o_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m1;
  y = NULL;
  m1 = emlrtCreateDoubleScalar(u);
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
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T d_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId)
{
  real_T y;
  y = p_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const mxArray *cal_coeff
 *                const char_T *identifier
 *                creal_T y[4]
 * Return Type  : void
 */
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
 * Arguments    : const emxArray_real_T *u
 * Return Type  : const mxArray *
 */
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
 *                creal_T y[4]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, creal_T y[4])
{
  q_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const mxArray *tau_m
 *                const char_T *identifier
 * Return Type  : real_T (*)[4]
 */
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
/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[4]
 */
  static real_T (*h_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[4]
{
  real_T (*y)[4];
  y = r_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const mxArray *Sigma_nom_UKF
 *                const char_T *identifier
 * Return Type  : real_T (*)[4]
 */
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
/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[4]
 */
  static real_T (*j_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[4]
{
  real_T (*y)[4];
  y = s_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const mxArray *r_mean_nom_UKF_dwfix
 *                const char_T *identifier
 * Return Type  : real_T (*)[2]
 */
static real_T (*k_emlrt_marshallIn(const mxArray *r_mean_nom_UKF_dwfix, const
  char_T *identifier))[2]
{
  real_T (*y)[2];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = l_emlrt_marshallIn(emlrtAlias(r_mean_nom_UKF_dwfix), &thisId);
  emlrtDestroyArray(&r_mean_nom_UKF_dwfix);
  return y;
}
/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[2]
 */
  static real_T (*l_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[2]
{
  real_T (*y)[2];
  y = t_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const mxArray *ProcessVar
 *                const char_T *identifier
 * Return Type  : real_T (*)[36]
 */
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
/*
 * Arguments    : const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[36]
 */
  static real_T (*n_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier *
  parentId))[36]
{
  real_T (*y)[36];
  y = u_emlrt_marshallIn(emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
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

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
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

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                creal_T ret[4]
 * Return Type  : void
 */
static void q_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, creal_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", true, 1U,
    dims);
  emlrtImportArrayR2015b(emlrtRootTLSGlobal, src, ret, 8, true);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[4]
 */
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
/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[4]
 */
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

/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[2]
 */
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
/*
 * Arguments    : const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[36]
 */
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

/*
 * Arguments    : const mxArray *prhs[27]
 *                const mxArray *plhs[44]
 * Return Type  : void
 */
void f_generate_and_eval_multi_residuals_dwfix_api(const mxArray *prhs[27],
  const mxArray *plhs[44])
{
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  emxArray_real_T *dwfix;
  emxArray_real_T *r_PS1_nom;
  emxArray_real_T *s_max_UKF;
  emxArray_real_T *s_max_UKF_dwfix;
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
  real_T (*Sigma_nom_UKF_dwfix)[4];
  real_T (*r_mean_nom_UKF_dwfix)[2];
  real_T (*r_mean_nom_UKF)[2];
  real_T (*MeasNoiseVar)[4];
  real_T (*ProcessVar)[36];
  real_T alpha;
  real_T Sigma_nom_dw;
  real_T Sigma_nom_PS1;
  real_T classis_UKF;
  real_T classis_dwfix;
  real_T classis_PS;
  real_T classis_dw;
  real_T strengthis_UKF;
  real_T strengthis_dwfix;
  real_T strengthis_PS;
  real_T strengthis_dw;
  real_T max_UKF;
  real_T max_dwfix;
  real_T max_PS;
  real_T max_dw;
  real_T median_UKF;
  real_T median_dwfix;
  real_T median_PS;
  real_T median_dw;
  real_T mode_UKF;
  real_T mode_dwfix;
  real_T mode_PS;
  real_T mode_dw;
  real_T var_UKF;
  real_T var_dwfix;
  real_T var_PS;
  real_T var_dw;
  real_T rm_I;
  real_T rm_Q;
  real_T rm_I_dwfix;
  real_T rm_Q_dwfix;
  real_T rvar_1;
  real_T rvar_2;
  real_T rvar_3;
  real_T QL;
  real_T dw_stat;
  real_T SP_F;
  real_T SP_P;
  real_T PC;
  real_T calib_check;
  real_T dec_hq;
  real_T zpth;
  emlrtHeapReferenceStackEnterFcnR2012b(emlrtRootTLSGlobal);
  emxInit_real_T(&PA, 1, true);
  emxInit_real_T(&PP, 1, true);
  emxInit_real_T(&FA, 1, true);
  emxInit_real_T(&FP, 1, true);
  emxInit_real_T(&RA, 1, true);
  emxInit_real_T(&RP, 1, true);
  emxInit_real_T(&dwfix, 1, true);
  emxInit_real_T(&r_PS1_nom, 1, true);
  emxInit_real_T(&s_max_UKF, 1, true);
  emxInit_real_T(&s_max_UKF_dwfix, 1, true);
  emxInit_real_T(&s_max_dw, 1, true);
  emxInit_real_T(&s_max_PS1, 1, true);
  emxInit_real_T(&res_PS2, 1, true);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs[3] = emlrtProtectR2012b(prhs[3], 3, false, -1);
  prhs[5] = emlrtProtectR2012b(prhs[5], 5, false, -1);
  prhs[9] = emlrtProtectR2012b(prhs[9], 9, false, -1);

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
  emlrt_marshallIn(emlrtAlias(prhs[9]), "dwfix", dwfix);
  tau_m = g_emlrt_marshallIn(emlrtAlias(prhs[10]), "tau_m");
  K_m = g_emlrt_marshallIn(emlrtAlias(prhs[11]), "K_m");
  X0 = g_emlrt_marshallIn(emlrtAlias(prhs[12]), "X0");
  QL_nom = c_emlrt_marshallIn(emlrtAliasP(prhs[13]), "QL_nom");
  DELAY = c_emlrt_marshallIn(emlrtAliasP(prhs[14]), "DELAY");
  FILLING = c_emlrt_marshallIn(emlrtAliasP(prhs[15]), "FILLING");
  FLATTOP = c_emlrt_marshallIn(emlrtAliasP(prhs[16]), "FLATTOP");
  Sigma_nom_UKF = i_emlrt_marshallIn(emlrtAlias(prhs[17]), "Sigma_nom_UKF");
  Sigma_nom_UKF_dwfix = i_emlrt_marshallIn(emlrtAlias(prhs[18]),
    "Sigma_nom_UKF_dwfix");
  r_mean_nom_UKF_dwfix = k_emlrt_marshallIn(emlrtAlias(prhs[19]),
    "r_mean_nom_UKF_dwfix");
  r_mean_nom_UKF = k_emlrt_marshallIn(emlrtAlias(prhs[20]), "r_mean_nom_UKF");
  MeasNoiseVar = i_emlrt_marshallIn(emlrtAlias(prhs[21]), "MeasNoiseVar");
  ProcessVar = m_emlrt_marshallIn(emlrtAlias(prhs[22]), "ProcessVar");
  alpha = c_emlrt_marshallIn(emlrtAliasP(prhs[23]), "alpha");
  Sigma_nom_dw = c_emlrt_marshallIn(emlrtAliasP(prhs[24]), "Sigma_nom_dw");
  emlrt_marshallIn(emlrtAlias(prhs[25]), "r_PS1_nom", r_PS1_nom);
  Sigma_nom_PS1 = c_emlrt_marshallIn(emlrtAliasP(prhs[26]), "Sigma_nom_PS1");

  /* Invoke the target function */
  f_generate_and_eval_multi_residuals_dwfix(PA, PP, FA, FP, RA, RP, FS, F0,
    cal_coeff, dwfix, *tau_m, *K_m, *X0, QL_nom, DELAY, FILLING, FLATTOP,
    *Sigma_nom_UKF, *Sigma_nom_UKF_dwfix, *r_mean_nom_UKF_dwfix, *r_mean_nom_UKF,
    *MeasNoiseVar, *ProcessVar, alpha, Sigma_nom_dw, r_PS1_nom, Sigma_nom_PS1,
    s_max_UKF, s_max_UKF_dwfix, s_max_dw, s_max_PS1, res_PS2, &classis_UKF,
    &classis_dwfix, &classis_PS, &classis_dw, &strengthis_UKF, &strengthis_dwfix,
    &strengthis_PS, &strengthis_dw, &max_UKF, &max_dwfix, &max_PS, &max_dw,
    &median_UKF, &median_dwfix, &median_PS, &median_dw, &mode_UKF, &mode_dwfix,
    &mode_PS, &mode_dw, &var_UKF, &var_dwfix, &var_PS, &var_dw, &rm_I, &rm_Q,
    &rm_I_dwfix, &rm_Q_dwfix, &rvar_1, &rvar_2, &rvar_3, &QL, &dw_stat, &SP_F,
    &SP_P, &PC, &calib_check, &dec_hq, &zpth);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(s_max_UKF);
  plhs[1] = emlrt_marshallOut(s_max_UKF_dwfix);
  plhs[2] = emlrt_marshallOut(s_max_dw);
  plhs[3] = emlrt_marshallOut(s_max_PS1);
  plhs[4] = emlrt_marshallOut(res_PS2);
  plhs[5] = b_emlrt_marshallOut(classis_UKF);
  plhs[6] = b_emlrt_marshallOut(classis_dwfix);
  plhs[7] = b_emlrt_marshallOut(classis_PS);
  plhs[8] = b_emlrt_marshallOut(classis_dw);
  plhs[9] = b_emlrt_marshallOut(strengthis_UKF);
  plhs[10] = b_emlrt_marshallOut(strengthis_dwfix);
  plhs[11] = b_emlrt_marshallOut(strengthis_PS);
  plhs[12] = b_emlrt_marshallOut(strengthis_dw);
  plhs[13] = b_emlrt_marshallOut(max_UKF);
  plhs[14] = b_emlrt_marshallOut(max_dwfix);
  plhs[15] = b_emlrt_marshallOut(max_PS);
  plhs[16] = b_emlrt_marshallOut(max_dw);
  plhs[17] = b_emlrt_marshallOut(median_UKF);
  plhs[18] = b_emlrt_marshallOut(median_dwfix);
  plhs[19] = b_emlrt_marshallOut(median_PS);
  plhs[20] = b_emlrt_marshallOut(median_dw);
  plhs[21] = b_emlrt_marshallOut(mode_UKF);
  plhs[22] = b_emlrt_marshallOut(mode_dwfix);
  plhs[23] = b_emlrt_marshallOut(mode_PS);
  plhs[24] = b_emlrt_marshallOut(mode_dw);
  plhs[25] = b_emlrt_marshallOut(var_UKF);
  plhs[26] = b_emlrt_marshallOut(var_dwfix);
  plhs[27] = b_emlrt_marshallOut(var_PS);
  plhs[28] = b_emlrt_marshallOut(var_dw);
  plhs[29] = b_emlrt_marshallOut(rm_I);
  plhs[30] = b_emlrt_marshallOut(rm_Q);
  plhs[31] = b_emlrt_marshallOut(rm_I_dwfix);
  plhs[32] = b_emlrt_marshallOut(rm_Q_dwfix);
  plhs[33] = b_emlrt_marshallOut(rvar_1);
  plhs[34] = b_emlrt_marshallOut(rvar_2);
  plhs[35] = b_emlrt_marshallOut(rvar_3);
  plhs[36] = b_emlrt_marshallOut(QL);
  plhs[37] = b_emlrt_marshallOut(dw_stat);
  plhs[38] = b_emlrt_marshallOut(SP_F);
  plhs[39] = b_emlrt_marshallOut(SP_P);
  plhs[40] = b_emlrt_marshallOut(PC);
  plhs[41] = b_emlrt_marshallOut(calib_check);
  plhs[42] = b_emlrt_marshallOut(dec_hq);
  plhs[43] = b_emlrt_marshallOut(zpth);
  res_PS2->canFreeData = false;
  emxFree_real_T(&res_PS2);
  s_max_PS1->canFreeData = false;
  emxFree_real_T(&s_max_PS1);
  s_max_dw->canFreeData = false;
  emxFree_real_T(&s_max_dw);
  s_max_UKF_dwfix->canFreeData = false;
  emxFree_real_T(&s_max_UKF_dwfix);
  s_max_UKF->canFreeData = false;
  emxFree_real_T(&s_max_UKF);
  r_PS1_nom->canFreeData = false;
  emxFree_real_T(&r_PS1_nom);
  dwfix->canFreeData = false;
  emxFree_real_T(&dwfix);
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
void f_generate_and_eval_multi_residuals_dwfix_atexit(void)
{
  mexFunctionCreateRootTLS();
  emlrtEnterRtStackR2012b(emlrtRootTLSGlobal);
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  f_generate_and_eval_multi_residuals_dwfix_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void f_generate_and_eval_multi_residuals_dwfix_initialize(void)
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
void f_generate_and_eval_multi_residuals_dwfix_terminate(void)
{
  emlrtLeaveRtStackR2012b(emlrtRootTLSGlobal);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_f_generate_and_eval_multi_residuals_dwfix_api.c
 *
 * [EOF]
 */
