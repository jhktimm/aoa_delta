/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_f_generate_and_eval_multi_residuals_dwql_api.c
 *
 * Code generation for function '_coder_f_generate_and_eval_multi_residuals_dwql_api'
 *
 */

/* Include files */
#include "_coder_f_generate_and_eval_multi_residuals_dwql_api.h"
#include "_coder_f_generate_and_eval_multi_residuals_dwql_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131594U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "f_generate_and_eval_multi_residuals_dwql",/* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static const mxArray *b_emlrt_marshallOut(const real_T u);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *FS, const
  char_T *identifier);
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *cal_coeff,
  const char_T *identifier, creal_T y[4]);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *PA, const
  char_T *identifier, emxArray_real_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);
static void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel);
static void emxFree_real_T(emxArray_real_T **pEmxArray);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, creal_T y[4]);
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *tau_m,
  const char_T *identifier))[4];
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4];
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *Sigma_nom_UKF, const char_T *identifier))[4];
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4];
static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *r_mean_nom_UKF_dwfix, const char_T *identifier))[2];
static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[2];
static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *ProcessVar, const char_T *identifier))[36];
static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[36];
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static real_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, creal_T ret[4]);
static real_T (*r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4];
static real_T (*s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4];
static real_T (*t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[2];
static real_T (*u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36];

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  o_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m;
  y = NULL;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *FS, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(FS), &thisId);
  emlrtDestroyArray(&FS);
  return y;
}

static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = p_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *cal_coeff,
  const char_T *identifier, creal_T y[4])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(sp, emlrtAlias(cal_coeff), &thisId, y);
  emlrtDestroyArray(&cal_coeff);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *PA, const
  char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(PA), &thisId, y);
  emlrtDestroyArray(&PA);
}

static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[1] = { 0 };

  y = NULL;
  m = emlrtCreateNumericArray(1, &iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, &u->data[0]);
  emlrtSetDimensions((mxArray *)m, u->size, 1);
  emlrtAssign(&y, m);
  return y;
}

static void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int32_T oldNumel)
{
  int32_T newNumel;
  int32_T i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = emlrtCallocMex((uint32_T)i, sizeof(real_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(real_T) * oldNumel);
      if (emxArray->canFreeData) {
        emlrtFreeMex(emxArray->data);
      }
    }

    emxArray->data = (real_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((*pEmxArray)->data);
    }

    emlrtFreeMex((*pEmxArray)->size);
    emlrtFreeMex(*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void *)
      &emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, creal_T y[4])
{
  q_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *tau_m,
  const char_T *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(sp, emlrtAlias(tau_m), &thisId);
  emlrtDestroyArray(&tau_m);
  return y;
}
  static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4]
{
  real_T (*y)[4];
  y = r_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *Sigma_nom_UKF, const char_T *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(sp, emlrtAlias(Sigma_nom_UKF), &thisId);
  emlrtDestroyArray(&Sigma_nom_UKF);
  return y;
}
  static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4]
{
  real_T (*y)[4];
  y = s_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *r_mean_nom_UKF_dwfix, const char_T *identifier))[2]
{
  real_T (*y)[2];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = l_emlrt_marshallIn(sp, emlrtAlias(r_mean_nom_UKF_dwfix), &thisId);
  emlrtDestroyArray(&r_mean_nom_UKF_dwfix);
  return y;
}
  static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[2]
{
  real_T (*y)[2];
  y = t_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *ProcessVar, const char_T *identifier))[36]
{
  real_T (*y)[36];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = n_emlrt_marshallIn(sp, emlrtAlias(ProcessVar), &thisId);
  emlrtDestroyArray(&ProcessVar);
  return y;
}
  static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[36]
{
  real_T (*y)[36];
  y = u_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[1] = { -1 };

  const boolean_T bv[1] = { true };

  int32_T iv[1];
  int32_T i;
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims, &bv[0],
    iv);
  ret->allocatedSize = iv[0];
  i = ret->size[0];
  ret->size[0] = iv[0];
  emxEnsureCapacity_real_T(ret, i);
  ret->data = (real_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static real_T p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, creal_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", true, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 8, true);
  emlrtDestroyArray(&src);
}

static real_T (*r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4]
{
  real_T (*ret)[4];
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[4])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real_T (*s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4]
{
  real_T (*ret)[4];
  static const int32_T dims[2] = { 2, 2 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[4])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[2]
{
  real_T (*ret)[2];
  static const int32_T dims[1] = { 2 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[2])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real_T (*u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36]
{
  real_T (*ret)[36];
  static const int32_T dims[2] = { 6, 6 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[36])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void f_generate_and_eval_multi_residuals_dwql_api(const mxArray * const prhs[29],
  int32_T nlhs, const mxArray *plhs[43])
{
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  emxArray_real_T *dwfix;
  emxArray_real_T *w12fix;
  emxArray_real_T *r_PS1_nom;
  emxArray_real_T *s_max_UKF;
  emxArray_real_T *s_max_UKF_dwfix;
  emxArray_real_T *s_max_dwql;
  emxArray_real_T *s_max_PS1;
  const mxArray *prhs_copy_idx_0;
  const mxArray *prhs_copy_idx_1;
  const mxArray *prhs_copy_idx_2;
  const mxArray *prhs_copy_idx_3;
  const mxArray *prhs_copy_idx_4;
  const mxArray *prhs_copy_idx_5;
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
  real_T (*r_mean_nom_dwql)[2];
  real_T (*Sigma_nom_dwql)[4];
  real_T Sigma_nom_PS1;
  real_T classis_UKF;
  real_T classis_dwfix;
  real_T classis_PS;
  real_T classis_dwql;
  real_T strengthis_UKF;
  real_T strengthis_dwfix;
  real_T strengthis_PS;
  real_T strengthis_dwql;
  real_T max_UKF;
  real_T max_dwfix;
  real_T max_PS;
  real_T max_dwql;
  real_T median_UKF;
  real_T median_dwfix;
  real_T median_PS;
  real_T median_dwql;
  real_T mode_UKF;
  real_T mode_dwfix;
  real_T mode_PS;
  real_T mode_dwql;
  real_T var_UKF;
  real_T var_dwfix;
  real_T var_PS;
  real_T var_dwql;
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
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &PA, 1, true);
  emxInit_real_T(&st, &PP, 1, true);
  emxInit_real_T(&st, &FA, 1, true);
  emxInit_real_T(&st, &FP, 1, true);
  emxInit_real_T(&st, &RA, 1, true);
  emxInit_real_T(&st, &RP, 1, true);
  emxInit_real_T(&st, &dwfix, 1, true);
  emxInit_real_T(&st, &w12fix, 1, true);
  emxInit_real_T(&st, &r_PS1_nom, 1, true);
  emxInit_real_T(&st, &s_max_UKF, 1, true);
  emxInit_real_T(&st, &s_max_UKF_dwfix, 1, true);
  emxInit_real_T(&st, &s_max_dwql, 1, true);
  emxInit_real_T(&st, &s_max_PS1, 1, true);
  prhs_copy_idx_0 = prhs[0];
  prhs_copy_idx_1 = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs_copy_idx_2 = prhs[2];
  prhs_copy_idx_3 = emlrtProtectR2012b(prhs[3], 3, false, -1);
  prhs_copy_idx_4 = prhs[4];
  prhs_copy_idx_5 = emlrtProtectR2012b(prhs[5], 5, false, -1);

  /* Marshall function inputs */
  PA->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_0), "PA", PA);
  PP->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_1), "PP", PP);
  FA->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_2), "FA", FA);
  FP->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_3), "FP", FP);
  RA->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_4), "RA", RA);
  RP->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_5), "RP", RP);
  FS = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "FS");
  F0 = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "F0");
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "cal_coeff", cal_coeff);
  dwfix->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "dwfix", dwfix);
  w12fix->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[10]), "w12fix", w12fix);
  tau_m = g_emlrt_marshallIn(&st, emlrtAlias(prhs[11]), "tau_m");
  K_m = g_emlrt_marshallIn(&st, emlrtAlias(prhs[12]), "K_m");
  X0 = g_emlrt_marshallIn(&st, emlrtAlias(prhs[13]), "X0");
  QL_nom = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[14]), "QL_nom");
  DELAY = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[15]), "DELAY");
  FILLING = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[16]), "FILLING");
  FLATTOP = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[17]), "FLATTOP");
  Sigma_nom_UKF = i_emlrt_marshallIn(&st, emlrtAlias(prhs[18]), "Sigma_nom_UKF");
  Sigma_nom_UKF_dwfix = i_emlrt_marshallIn(&st, emlrtAlias(prhs[19]),
    "Sigma_nom_UKF_dwfix");
  r_mean_nom_UKF_dwfix = k_emlrt_marshallIn(&st, emlrtAlias(prhs[20]),
    "r_mean_nom_UKF_dwfix");
  r_mean_nom_UKF = k_emlrt_marshallIn(&st, emlrtAlias(prhs[21]),
    "r_mean_nom_UKF");
  MeasNoiseVar = i_emlrt_marshallIn(&st, emlrtAlias(prhs[22]), "MeasNoiseVar");
  ProcessVar = m_emlrt_marshallIn(&st, emlrtAlias(prhs[23]), "ProcessVar");
  alpha = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[24]), "alpha");
  r_mean_nom_dwql = k_emlrt_marshallIn(&st, emlrtAlias(prhs[25]),
    "r_mean_nom_dwql");
  Sigma_nom_dwql = i_emlrt_marshallIn(&st, emlrtAlias(prhs[26]),
    "Sigma_nom_dwql");
  r_PS1_nom->canFreeData = false;
  emlrt_marshallIn(&st, emlrtAlias(prhs[27]), "r_PS1_nom", r_PS1_nom);
  Sigma_nom_PS1 = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[28]), "Sigma_nom_PS1");

  /* Invoke the target function */
  f_generate_and_eval_multi_residuals_dwql(PA, PP, FA, FP, RA, RP, FS, F0,
    cal_coeff, dwfix, w12fix, *tau_m, *K_m, *X0, QL_nom, DELAY, FILLING, FLATTOP,
    *Sigma_nom_UKF, *Sigma_nom_UKF_dwfix, *r_mean_nom_UKF_dwfix, *r_mean_nom_UKF,
    *MeasNoiseVar, *ProcessVar, alpha, *r_mean_nom_dwql, *Sigma_nom_dwql,
    r_PS1_nom, Sigma_nom_PS1, s_max_UKF, s_max_UKF_dwfix, s_max_dwql, s_max_PS1,
    &classis_UKF, &classis_dwfix, &classis_PS, &classis_dwql, &strengthis_UKF,
    &strengthis_dwfix, &strengthis_PS, &strengthis_dwql, &max_UKF, &max_dwfix,
    &max_PS, &max_dwql, &median_UKF, &median_dwfix, &median_PS, &median_dwql,
    &mode_UKF, &mode_dwfix, &mode_PS, &mode_dwql, &var_UKF, &var_dwfix, &var_PS,
    &var_dwql, &rm_I, &rm_Q, &rm_I_dwfix, &rm_Q_dwfix, &rvar_1, &rvar_2, &rvar_3,
    &QL, &dw_stat, &SP_F, &SP_P, &PC, &calib_check, &dec_hq, &zpth);

  /* Marshall function outputs */
  s_max_UKF->canFreeData = false;
  plhs[0] = emlrt_marshallOut(s_max_UKF);
  emxFree_real_T(&s_max_UKF);
  emxFree_real_T(&r_PS1_nom);
  emxFree_real_T(&w12fix);
  emxFree_real_T(&dwfix);
  emxFree_real_T(&RP);
  emxFree_real_T(&RA);
  emxFree_real_T(&FP);
  emxFree_real_T(&FA);
  emxFree_real_T(&PP);
  emxFree_real_T(&PA);
  if (nlhs > 1) {
    s_max_UKF_dwfix->canFreeData = false;
    plhs[1] = emlrt_marshallOut(s_max_UKF_dwfix);
  }

  emxFree_real_T(&s_max_UKF_dwfix);
  if (nlhs > 2) {
    s_max_dwql->canFreeData = false;
    plhs[2] = emlrt_marshallOut(s_max_dwql);
  }

  emxFree_real_T(&s_max_dwql);
  if (nlhs > 3) {
    s_max_PS1->canFreeData = false;
    plhs[3] = emlrt_marshallOut(s_max_PS1);
  }

  emxFree_real_T(&s_max_PS1);
  if (nlhs > 4) {
    plhs[4] = b_emlrt_marshallOut(classis_UKF);
  }

  if (nlhs > 5) {
    plhs[5] = b_emlrt_marshallOut(classis_dwfix);
  }

  if (nlhs > 6) {
    plhs[6] = b_emlrt_marshallOut(classis_PS);
  }

  if (nlhs > 7) {
    plhs[7] = b_emlrt_marshallOut(classis_dwql);
  }

  if (nlhs > 8) {
    plhs[8] = b_emlrt_marshallOut(strengthis_UKF);
  }

  if (nlhs > 9) {
    plhs[9] = b_emlrt_marshallOut(strengthis_dwfix);
  }

  if (nlhs > 10) {
    plhs[10] = b_emlrt_marshallOut(strengthis_PS);
  }

  if (nlhs > 11) {
    plhs[11] = b_emlrt_marshallOut(strengthis_dwql);
  }

  if (nlhs > 12) {
    plhs[12] = b_emlrt_marshallOut(max_UKF);
  }

  if (nlhs > 13) {
    plhs[13] = b_emlrt_marshallOut(max_dwfix);
  }

  if (nlhs > 14) {
    plhs[14] = b_emlrt_marshallOut(max_PS);
  }

  if (nlhs > 15) {
    plhs[15] = b_emlrt_marshallOut(max_dwql);
  }

  if (nlhs > 16) {
    plhs[16] = b_emlrt_marshallOut(median_UKF);
  }

  if (nlhs > 17) {
    plhs[17] = b_emlrt_marshallOut(median_dwfix);
  }

  if (nlhs > 18) {
    plhs[18] = b_emlrt_marshallOut(median_PS);
  }

  if (nlhs > 19) {
    plhs[19] = b_emlrt_marshallOut(median_dwql);
  }

  if (nlhs > 20) {
    plhs[20] = b_emlrt_marshallOut(mode_UKF);
  }

  if (nlhs > 21) {
    plhs[21] = b_emlrt_marshallOut(mode_dwfix);
  }

  if (nlhs > 22) {
    plhs[22] = b_emlrt_marshallOut(mode_PS);
  }

  if (nlhs > 23) {
    plhs[23] = b_emlrt_marshallOut(mode_dwql);
  }

  if (nlhs > 24) {
    plhs[24] = b_emlrt_marshallOut(var_UKF);
  }

  if (nlhs > 25) {
    plhs[25] = b_emlrt_marshallOut(var_dwfix);
  }

  if (nlhs > 26) {
    plhs[26] = b_emlrt_marshallOut(var_PS);
  }

  if (nlhs > 27) {
    plhs[27] = b_emlrt_marshallOut(var_dwql);
  }

  if (nlhs > 28) {
    plhs[28] = b_emlrt_marshallOut(rm_I);
  }

  if (nlhs > 29) {
    plhs[29] = b_emlrt_marshallOut(rm_Q);
  }

  if (nlhs > 30) {
    plhs[30] = b_emlrt_marshallOut(rm_I_dwfix);
  }

  if (nlhs > 31) {
    plhs[31] = b_emlrt_marshallOut(rm_Q_dwfix);
  }

  if (nlhs > 32) {
    plhs[32] = b_emlrt_marshallOut(rvar_1);
  }

  if (nlhs > 33) {
    plhs[33] = b_emlrt_marshallOut(rvar_2);
  }

  if (nlhs > 34) {
    plhs[34] = b_emlrt_marshallOut(rvar_3);
  }

  if (nlhs > 35) {
    plhs[35] = b_emlrt_marshallOut(QL);
  }

  if (nlhs > 36) {
    plhs[36] = b_emlrt_marshallOut(dw_stat);
  }

  if (nlhs > 37) {
    plhs[37] = b_emlrt_marshallOut(SP_F);
  }

  if (nlhs > 38) {
    plhs[38] = b_emlrt_marshallOut(SP_P);
  }

  if (nlhs > 39) {
    plhs[39] = b_emlrt_marshallOut(PC);
  }

  if (nlhs > 40) {
    plhs[40] = b_emlrt_marshallOut(calib_check);
  }

  if (nlhs > 41) {
    plhs[41] = b_emlrt_marshallOut(dec_hq);
  }

  if (nlhs > 42) {
    plhs[42] = b_emlrt_marshallOut(zpth);
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

void f_generate_and_eval_multi_residuals_dwql_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  f_generate_and_eval_multi_residuals_dwql_xil_terminate();
  f_generate_and_eval_multi_residuals_dwql_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void f_generate_and_eval_multi_residuals_dwql_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void f_generate_and_eval_multi_residuals_dwql_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_f_generate_and_eval_multi_residuals_dwql_api.c) */
