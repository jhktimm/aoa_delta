/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_generate_and_eval_residual_api.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 16-Oct-2019 16:31:43
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_f_generate_and_eval_residual_api.h"
#include "_coder_f_generate_and_eval_residual_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131451U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "f_generate_and_eval_residual",      /* fFunctionName */
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
  *Sigma_nom, const char_T *identifier))[4];
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4];
static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *r_mean_nom, const char_T *identifier))[2];
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

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  o_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
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
 * Arguments    : const emlrtStack *sp
 *                const mxArray *FS
 *                const char_T *identifier
 * Return Type  : real_T
 */
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

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = p_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *cal_coeff
 *                const char_T *identifier
 *                creal_T y[4]
 * Return Type  : void
 */
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

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *PA
 *                const char_T *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
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
  emlrtMxSetData((mxArray *)m0, (void *)&u->data[0]);
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
 * Arguments    : const emlrtStack *sp
 *                emxArray_real_T **pEmxArray
 *                int32_T numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
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
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                creal_T y[4]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, creal_T y[4])
{
  q_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *tau_m
 *                const char_T *identifier
 * Return Type  : real_T (*)[4]
 */
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
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[4]
 */
  static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4]
{
  real_T (*y)[4];
  y = r_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *Sigma_nom
 *                const char_T *identifier
 * Return Type  : real_T (*)[4]
 */
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *Sigma_nom, const char_T *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(sp, emlrtAlias(Sigma_nom), &thisId);
  emlrtDestroyArray(&Sigma_nom);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[4]
 */
  static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4]
{
  real_T (*y)[4];
  y = s_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *r_mean_nom
 *                const char_T *identifier
 * Return Type  : real_T (*)[2]
 */
static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *r_mean_nom, const char_T *identifier))[2]
{
  real_T (*y)[2];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = l_emlrt_marshallIn(sp, emlrtAlias(r_mean_nom), &thisId);
  emlrtDestroyArray(&r_mean_nom);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[2]
 */
  static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[2]
{
  real_T (*y)[2];
  y = t_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *ProcessVar
 *                const char_T *identifier
 * Return Type  : real_T (*)[36]
 */
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
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[36]
 */
  static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[36]
{
  real_T (*y)[36];
  y = u_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[1] = { -1 };

  const boolean_T bv0[1] = { true };

  int32_T iv1[1];
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims, &bv0[0],
    iv1);
  ret->size[0] = iv1[0];
  ret->allocatedSize = ret->size[0];
  ret->data = (real_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
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

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                creal_T ret[4]
 * Return Type  : void
 */
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, creal_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", true, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 8, true);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[4]
 */
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
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[4]
 */
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

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[2]
 */
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
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[36]
 */
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

/*
 * Arguments    : const mxArray *prhs[20]
 *                const mxArray *plhs[13]
 * Return Type  : void
 */
void f_generate_and_eval_residual_api(const mxArray *prhs[20], const mxArray
  *plhs[13])
{
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  emxArray_real_T *s_max;
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
  real_T (*Sigma_nom)[4];
  real_T (*r_mean_nom)[2];
  real_T (*MeasNoiseVar)[4];
  real_T (*ProcessVar)[36];
  real_T classis;
  real_T strengthis;
  real_T strengtVar;
  real_T maxis;
  real_T minis;
  real_T QL;
  real_T dw_stat;
  real_T SP_F;
  real_T SP_P;
  real_T PC;
  real_T calib_check;
  real_T dec_hq;
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
  emxInit_real_T(&st, &s_max, 1, true);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "PA", PA);
  emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "PP", PP);
  emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "FA", FA);
  emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "FP", FP);
  emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "RA", RA);
  emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "RP", RP);
  FS = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "FS");
  F0 = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "F0");
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "cal_coeff", cal_coeff);
  tau_m = g_emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "tau_m");
  K_m = g_emlrt_marshallIn(&st, emlrtAlias(prhs[10]), "K_m");
  X0 = g_emlrt_marshallIn(&st, emlrtAlias(prhs[11]), "X0");
  QL_nom = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "QL_nom");
  DELAY = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "DELAY");
  FILLING = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[14]), "FILLING");
  FLATTOP = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[15]), "FLATTOP");
  Sigma_nom = i_emlrt_marshallIn(&st, emlrtAlias(prhs[16]), "Sigma_nom");
  r_mean_nom = k_emlrt_marshallIn(&st, emlrtAlias(prhs[17]), "r_mean_nom");
  MeasNoiseVar = i_emlrt_marshallIn(&st, emlrtAlias(prhs[18]), "MeasNoiseVar");
  ProcessVar = m_emlrt_marshallIn(&st, emlrtAlias(prhs[19]), "ProcessVar");

  /* Invoke the target function */
  f_generate_and_eval_residual(PA, PP, FA, FP, RA, RP, FS, F0, cal_coeff, *tau_m,
    *K_m, *X0, QL_nom, DELAY, FILLING, FLATTOP, *Sigma_nom, *r_mean_nom,
    *MeasNoiseVar, *ProcessVar, s_max, &classis, &strengthis, &strengtVar,
    &maxis, &minis, &QL, &dw_stat, &SP_F, &SP_P, &PC, &calib_check, &dec_hq);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(s_max);
  plhs[1] = b_emlrt_marshallOut(classis);
  plhs[2] = b_emlrt_marshallOut(strengthis);
  plhs[3] = b_emlrt_marshallOut(strengtVar);
  plhs[4] = b_emlrt_marshallOut(maxis);
  plhs[5] = b_emlrt_marshallOut(minis);
  plhs[6] = b_emlrt_marshallOut(QL);
  plhs[7] = b_emlrt_marshallOut(dw_stat);
  plhs[8] = b_emlrt_marshallOut(SP_F);
  plhs[9] = b_emlrt_marshallOut(SP_P);
  plhs[10] = b_emlrt_marshallOut(PC);
  plhs[11] = b_emlrt_marshallOut(calib_check);
  plhs[12] = b_emlrt_marshallOut(dec_hq);
  s_max->canFreeData = false;
  emxFree_real_T(&s_max);
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
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void f_generate_and_eval_residual_atexit(void)
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
  f_generate_and_eval_residual_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void f_generate_and_eval_residual_initialize(void)
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

/*
 * Arguments    : void
 * Return Type  : void
 */
void f_generate_and_eval_residual_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_f_generate_and_eval_residual_api.c
 *
 * [EOF]
 */
