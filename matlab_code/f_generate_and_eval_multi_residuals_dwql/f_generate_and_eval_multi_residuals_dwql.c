/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_and_eval_multi_residuals_dwql.c
 *
 * Code generation for function 'f_generate_and_eval_multi_residuals_dwql'
 *
 */

/* Include files */
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "colon.h"
#include "cov.h"
#include "exp.h"
#include "f_GLT.h"
#include "f_calibrateData.h"
#include "f_comp_dw_ql_Rybaniec.h"
#include "f_computeQL.h"
#include "f_generate_and_eval_multi_residuals_dwql_data.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "f_generate_and_eval_multi_residuals_dwql_initialize.h"
#include "f_generate_and_eval_multi_residuals_dwql_rtwutil.h"
#include "f_generate_online_UKF_residual_full.h"
#include "f_generate_online_UKF_residual_full_dwfix.h"
#include "f_generate_online_parityRes1_full.h"
#include "f_generate_online_parityRes2_full.h"
#include "find.h"
#include "mean.h"
#include "median.h"
#include "minOrMax.h"
#include "mode.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "smoothdata.h"
#include "var.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

void f_generate_and_eval_multi_residuals_dwql(const emxArray_real_T *PA,
  emxArray_real_T *PP, const emxArray_real_T *FA, emxArray_real_T *FP, const
  emxArray_real_T *RA, emxArray_real_T *RP, double FS, double F0, const creal_T
  cal_coeff[4], const emxArray_real_T *dwfix, const emxArray_real_T *w12fix,
  const double tau_m[4], const double K_m[4], const double X0[4], double QL_nom,
  double DELAY, double FILLING, double FLATTOP, const double Sigma_nom_UKF[4],
  const double Sigma_nom_UKF_dwfix[4], const double r_mean_nom_UKF_dwfix[2],
  const double r_mean_nom_UKF[2], const double MeasNoiseVar[4], const double
  ProcessVar[36], double alpha, const double r_mean_nom_dwql[2], const double
  Sigma_nom_dwql[4], const emxArray_real_T *r_PS1_nom, double Sigma_nom_PS1,
  emxArray_real_T *s_max_UKF, emxArray_real_T *s_max_UKF_dwfix, emxArray_real_T *
  s_max_dwql, emxArray_real_T *s_max_PS1, double *classis_UKF, double
  *classis_dwfix, double *classis_PS, double *classis_dwql, double
  *strengthis_UKF, double *strengthis_dwfix, double *strengthis_PS, double
  *strengthis_dwql, double *max_UKF, double *max_dwfix, double *max_PS, double
  *max_dwql, double *median_UKF, double *median_dwfix, double *median_PS, double
  *median_dwql, double *mode_UKF, double *mode_dwfix, double *mode_PS, double
  *mode_dwql, double *var_UKF, double *var_dwfix, double *var_PS, double
  *var_dwql, double *rm_I, double *rm_Q, double *rm_I_dwfix, double *rm_Q_dwfix,
  double *rvar_1, double *rvar_2, double *rvar_3, double *QL, double *dw_stat,
  double *SP_F, double *SP_P, double *PC, double *calib_check, double *dec_hq,
  double *zpth)
{
  double fs;
  double f0;
  emxArray_real_T *Rise;
  emxArray_real_T *Flattop;
  emxArray_real_T *Decay;
  double a_tmp;
  double a;
  double b;
  int i;
  int loop_ub;
  int s;
  emxArray_real_T *idxP;
  emxArray_real_T *dw_res;
  emxArray_boolean_T *x;
  emxArray_int32_T *r;
  int exitg1;
  int k;
  int vlen;
  boolean_T guard1 = false;
  boolean_T b_x[1361];
  emxArray_real_T *y;
  emxArray_creal_T *y_mC;
  emxArray_real_T *res_full_mean;
  emxArray_real_T *res_full_variance;
  emxArray_creal_T *u_mCal;
  emxArray_creal_T *r_mCal;
  emxArray_real_T *dw;
  emxArray_real_T *r1;
  emxArray_int32_T *r2;
  emxArray_real_T *b_res_full_mean;
  emxArray_real_T *c_res_full_mean;
  emxArray_real_T *b_idxP;
  emxArray_creal_T *b_FA;
  emxArray_creal_T *b_RA;
  emxArray_real_T *b_PA;
  boolean_T b_guard1 = false;
  int tmp_data[1361];
  int tmp_size[1];
  int idxF_data[1361];
  double FP_data[1361];
  double res_var_data[4];
  int res_var_size[2];
  if (!isInitialized_f_generate_and_eval_multi_residuals_dwql) {
    f_generate_and_eval_multi_residuals_dwql_initialize();
  }

  /*  This function evaluates the residual */
  /*  #codegen */
  fs = FS * 1.0E+6;
  f0 = F0 * 1.0E+6;
  emxInit_real_T(&Rise, 2);
  emxInit_real_T(&Flattop, 2);
  emxInit_real_T(&Decay, 2);
  if (fs == 1.0E+6) {
    a_tmp = DELAY * 1.0E+6 * 1.0E-6;
    a = rt_roundd_snf(a_tmp);
    b = rt_roundd_snf(a_tmp + FILLING * 1.0E+6 * 1.0E-6);
    if (rtIsNaN(a) || rtIsNaN(b)) {
      i = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i);
      Rise->data[0] = rtNaN;
    } else if (b < a) {
      Rise->size[0] = 1;
      Rise->size[1] = 0;
    } else if ((rtIsInf(a) || rtIsInf(b)) && (a == b)) {
      i = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i);
      Rise->data[0] = rtNaN;
    } else if (a == a) {
      i = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      loop_ub = (int)(b - a);
      Rise->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(Rise, i);
      for (i = 0; i <= loop_ub; i++) {
        Rise->data[i] = a + (double)i;
      }
    } else {
      eml_float_colon(a, b, Rise);
    }

    b = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * 1.0E+6 *
      1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(b)) {
      i = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i);
      Flattop->data[0] = rtNaN;
    } else if (b < Rise->data[Rise->size[1] - 1] + 1.0) {
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(b)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == b)) {
      i = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i);
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      a_tmp = Rise->data[Rise->size[1] - 1] + 1.0;
      i = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      loop_ub = (int)floor(b - a_tmp);
      Flattop->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(Flattop, i);
      for (i = 0; i <= loop_ub; i++) {
        Flattop->data[i] = a_tmp + (double)i;
      }
    } else {
      eml_float_colon(Rise->data[Rise->size[1] - 1] + 1.0, b, Flattop);
    }

    if (rtIsNaN(Flattop->data[Flattop->size[1] - 1] + 1.0)) {
      i = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity_real_T(Decay, i);
      Decay->data[0] = rtNaN;
    } else if (1821.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      Decay->size[0] = 1;
      Decay->size[1] = 0;
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 1821.0)) {
      i = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity_real_T(Decay, i);
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      a_tmp = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      loop_ub = (int)floor(1821.0 - a_tmp);
      Decay->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(Decay, i);
      for (i = 0; i <= loop_ub; i++) {
        Decay->data[i] = a_tmp + (double)i;
      }
    } else {
      b_eml_float_colon(Flattop->data[Flattop->size[1] - 1] + 1.0, Decay);
    }
  } else {
    a_tmp = DELAY * fs * 1.0E-6;
    a = rt_roundd_snf(a_tmp);
    b = rt_roundd_snf(a_tmp + FILLING * fs * 1.0E-6);
    if (rtIsNaN(a) || rtIsNaN(b)) {
      i = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i);
      Rise->data[0] = rtNaN;
    } else if (b < a) {
      Rise->size[0] = 1;
      Rise->size[1] = 0;
    } else if ((rtIsInf(a) || rtIsInf(b)) && (a == b)) {
      i = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i);
      Rise->data[0] = rtNaN;
    } else if (a == a) {
      i = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      loop_ub = (int)(b - a);
      Rise->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(Rise, i);
      for (i = 0; i <= loop_ub; i++) {
        Rise->data[i] = a + (double)i;
      }
    } else {
      eml_float_colon(a, b, Rise);
    }

    b = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * fs *
      1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(b)) {
      i = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i);
      Flattop->data[0] = rtNaN;
    } else if (b < Rise->data[Rise->size[1] - 1] + 1.0) {
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(b)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == b)) {
      i = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i);
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      a_tmp = Rise->data[Rise->size[1] - 1] + 1.0;
      i = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      loop_ub = (int)floor(b - a_tmp);
      Flattop->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(Flattop, i);
      for (i = 0; i <= loop_ub; i++) {
        Flattop->data[i] = a_tmp + (double)i;
      }
    } else {
      eml_float_colon(Rise->data[Rise->size[1] - 1] + 1.0, b, Flattop);
    }

    if (rtIsNaN(Flattop->data[Flattop->size[1] - 1] + 1.0)) {
      i = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity_real_T(Decay, i);
      Decay->data[0] = rtNaN;
    } else if (16384.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      Decay->size[0] = 1;
      Decay->size[1] = 0;
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 16384.0)) {
      i = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity_real_T(Decay, i);
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      a_tmp = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      loop_ub = (int)floor(16384.0 - a_tmp);
      Decay->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(Decay, i);
      for (i = 0; i <= loop_ub; i++) {
        Decay->data[i] = a_tmp + (double)i;
      }
    } else {
      c_eml_float_colon(Flattop->data[Flattop->size[1] - 1] + 1.0, Decay);
    }
  }

  s = 0;
  emxInit_real_T(&idxP, 1);
  emxInit_real_T(&dw_res, 1);
  emxInit_boolean_T(&x, 1);
  emxInit_int32_T(&r, 1);
  do {
    exitg1 = 0;
    if (60 > PP->size[0]) {
      i = 0;
      k = 0;
    } else {
      i = 59;
      k = PP->size[0];
    }

    loop_ub = k - i;
    k = x->size[0];
    x->size[0] = loop_ub;
    emxEnsureCapacity_boolean_T(x, k);
    for (k = 0; k < loop_ub; k++) {
      x->data[k] = (PP->data[i + k] == 0.0);
    }

    vlen = x->size[0];
    if (x->size[0] == 0) {
      loop_ub = 0;
    } else {
      loop_ub = x->data[0];
      for (k = 2; k <= vlen; k++) {
        loop_ub += x->data[k - 1];
      }
    }

    guard1 = false;
    if (loop_ub > 0) {
      guard1 = true;
    } else {
      for (i = 0; i < 1361; i++) {
        b_x[i] = (FP->data[i + 59] == 0.0);
      }

      loop_ub = b_x[0];
      for (k = 0; k < 1360; k++) {
        loop_ub += b_x[k + 1];
      }

      if (loop_ub > 0) {
        guard1 = true;
      } else {
        if (60 > RP->size[0]) {
          i = 0;
          k = 0;
        } else {
          i = 59;
          k = RP->size[0];
        }

        loop_ub = k - i;
        k = x->size[0];
        x->size[0] = loop_ub;
        emxEnsureCapacity_boolean_T(x, k);
        for (k = 0; k < loop_ub; k++) {
          x->data[k] = (RP->data[i + k] == 0.0);
        }

        vlen = x->size[0];
        if (x->size[0] == 0) {
          loop_ub = 0;
        } else {
          loop_ub = x->data[0];
          for (k = 2; k <= vlen; k++) {
            loop_ub += x->data[k - 1];
          }
        }

        if (loop_ub > 0) {
          guard1 = true;
        } else {
          exitg1 = 1;
        }
      }
    }

    if (guard1) {
      if (60 > PP->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = PP->size[0];
      }

      loop_ub = k - i;
      k = x->size[0];
      x->size[0] = loop_ub;
      emxEnsureCapacity_boolean_T(x, k);
      for (k = 0; k < loop_ub; k++) {
        x->data[k] = (PP->data[i + k] == 0.0);
      }

      eml_find(x, r);
      i = idxP->size[0];
      idxP->size[0] = r->size[0];
      emxEnsureCapacity_real_T(idxP, i);
      loop_ub = r->size[0];
      for (i = 0; i < loop_ub; i++) {
        idxP->data[i] = r->data[i];
      }

      i = r->size[0];
      r->size[0] = idxP->size[0];
      emxEnsureCapacity_int32_T(r, i);
      loop_ub = idxP->size[0];
      for (i = 0; i < loop_ub; i++) {
        r->data[i] = (int)((idxP->data[i] + 60.0) - 1.0);
      }

      i = dw_res->size[0];
      dw_res->size[0] = idxP->size[0];
      emxEnsureCapacity_real_T(dw_res, i);
      loop_ub = idxP->size[0];
      for (i = 0; i < loop_ub; i++) {
        dw_res->data[i] = PP->data[(int)((idxP->data[i] + 60.0) - 2.0) - 1];
      }

      loop_ub = dw_res->size[0];
      for (i = 0; i < loop_ub; i++) {
        PP->data[r->data[i] - 1] = dw_res->data[i];
      }

      for (i = 0; i < 1361; i++) {
        b_x[i] = (FP->data[i + 59] == 0.0);
      }

      b_eml_find(b_x, tmp_data, tmp_size);
      vlen = tmp_size[0];
      loop_ub = tmp_size[0];
      if (0 <= loop_ub - 1) {
        memcpy(&idxF_data[0], &tmp_data[0], loop_ub * sizeof(int));
      }

      for (i = 0; i < vlen; i++) {
        tmp_data[i] = (int)(((double)idxF_data[i] + 60.0) - 1.0);
      }

      for (i = 0; i < vlen; i++) {
        FP_data[i] = FP->data[(int)(((double)idxF_data[i] + 60.0) - 2.0) - 1];
      }

      for (i = 0; i < vlen; i++) {
        FP->data[tmp_data[i] - 1] = FP_data[i];
      }

      if (60 > RP->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = RP->size[0];
      }

      loop_ub = k - i;
      k = x->size[0];
      x->size[0] = loop_ub;
      emxEnsureCapacity_boolean_T(x, k);
      for (k = 0; k < loop_ub; k++) {
        x->data[k] = (RP->data[i + k] == 0.0);
      }

      eml_find(x, r);
      i = idxP->size[0];
      idxP->size[0] = r->size[0];
      emxEnsureCapacity_real_T(idxP, i);
      loop_ub = r->size[0];
      for (i = 0; i < loop_ub; i++) {
        idxP->data[i] = r->data[i];
      }

      i = r->size[0];
      r->size[0] = idxP->size[0];
      emxEnsureCapacity_int32_T(r, i);
      loop_ub = idxP->size[0];
      for (i = 0; i < loop_ub; i++) {
        r->data[i] = (int)((idxP->data[i] + 60.0) - 1.0);
      }

      i = dw_res->size[0];
      dw_res->size[0] = idxP->size[0];
      emxEnsureCapacity_real_T(dw_res, i);
      loop_ub = idxP->size[0];
      for (i = 0; i < loop_ub; i++) {
        dw_res->data[i] = RP->data[(int)((idxP->data[i] + 60.0) - 2.0) - 1];
      }

      loop_ub = dw_res->size[0];
      for (i = 0; i < loop_ub; i++) {
        RP->data[r->data[i] - 1] = dw_res->data[i];
      }

      s++;
      if (s > 500) {
        exitg1 = 1;
      }
    }
  } while (exitg1 == 0);

  i = dw_res->size[0];
  dw_res->size[0] = Rise->size[1];
  emxEnsureCapacity_real_T(dw_res, i);
  loop_ub = Rise->size[1];
  for (i = 0; i < loop_ub; i++) {
    dw_res->data[i] = FA->data[(int)Rise->data[i] - 1];
  }

  emxInit_real_T(&y, 2);
  emxInit_creal_T(&y_mC, 1);
  emxInit_real_T(&res_full_mean, 2);
  emxInit_real_T(&res_full_variance, 3);
  emxInit_creal_T(&u_mCal, 1);
  emxInit_creal_T(&r_mCal, 1);
  emxInit_real_T(&dw, 1);
  emxInit_real_T(&r1, 2);
  emxInit_int32_T(&r2, 1);
  emxInit_real_T(&b_res_full_mean, 2);
  emxInit_real_T(&c_res_full_mean, 2);
  emxInit_real_T(&b_idxP, 2);
  emxInit_creal_T(&b_FA, 1);
  emxInit_creal_T(&b_RA, 1);
  emxInit_real_T(&b_PA, 1);
  b_guard1 = false;
  if (mean(dw_res) > 3.0) {
    i = dw_res->size[0];
    dw_res->size[0] = Flattop->size[1];
    emxEnsureCapacity_real_T(dw_res, i);
    loop_ub = Flattop->size[1];
    for (i = 0; i < loop_ub; i++) {
      dw_res->data[i] = PA->data[(int)Flattop->data[i] - 1];
    }

    if (mean(dw_res) > 3.0) {
      /*     %% Unscented Kalman Filter Residual Generation + GLRT Evaluation */
      c_f_generate_online_UKF_residua(PA, PP, FA, FP, RA, RP, FS, cal_coeff,
        tau_m, K_m, X0, QL_nom, MeasNoiseVar, ProcessVar, res_full_mean,
        res_full_variance);
      vlen = res_full_mean->size[1];
      if (2 > vlen) {
        vlen = 2;
      }

      if (res_full_mean->size[1] == 0) {
        vlen = 0;
      }

      i = y->size[0] * y->size[1];
      y->size[0] = 2;
      y->size[1] = vlen;
      emxEnsureCapacity_real_T(y, i);
      loop_ub = vlen << 1;
      for (i = 0; i < loop_ub; i++) {
        y->data[i] = 0.0;
      }

      vlen = res_full_mean->size[1];
      if (2 > vlen) {
        vlen = 2;
      }

      if (res_full_mean->size[1] == 0) {
        vlen = 0;
      }

      for (loop_ub = 0; loop_ub < vlen; loop_ub++) {
        y->data[2 * loop_ub] = res_full_mean->data[2 * loop_ub] -
          r_mean_nom_UKF[0];
        i = 2 * loop_ub + 1;
        y->data[i] = res_full_mean->data[i] - r_mean_nom_UKF[1];
      }

      /*      figure(9) */
      /*      plot(res_full_mean(1,45:end), res_full_mean(2,45:end), '.') */
      /*      hold on */
      f_GLT(Sigma_nom_UKF, y, b_res_full_mean);
      i = s_max_UKF->size[0];
      s_max_UKF->size[0] = b_res_full_mean->size[1];
      emxEnsureCapacity_real_T(s_max_UKF, i);
      loop_ub = b_res_full_mean->size[1];
      for (i = 0; i < loop_ub; i++) {
        s_max_UKF->data[i] = b_res_full_mean->data[i];
      }

      if (60 > res_full_mean->size[1]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = res_full_mean->size[1];
      }

      vlen = b_res_full_mean->size[0] * b_res_full_mean->size[1];
      b_res_full_mean->size[0] = 1;
      loop_ub = k - i;
      b_res_full_mean->size[1] = loop_ub;
      emxEnsureCapacity_real_T(b_res_full_mean, vlen);
      for (k = 0; k < loop_ub; k++) {
        b_res_full_mean->data[k] = res_full_mean->data[2 * (i + k)];
      }

      *rm_I = b_mean(b_res_full_mean);
      if (60 > res_full_mean->size[1]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = res_full_mean->size[1];
      }

      vlen = b_res_full_mean->size[0] * b_res_full_mean->size[1];
      b_res_full_mean->size[0] = 1;
      loop_ub = k - i;
      b_res_full_mean->size[1] = loop_ub;
      emxEnsureCapacity_real_T(b_res_full_mean, vlen);
      for (k = 0; k < loop_ub; k++) {
        b_res_full_mean->data[k] = res_full_mean->data[2 * (i + k) + 1];
      }

      *rm_Q = b_mean(b_res_full_mean);
      if (60 > res_full_mean->size[1]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = res_full_mean->size[1];
      }

      loop_ub = k - i;
      k = c_res_full_mean->size[0] * c_res_full_mean->size[1];
      c_res_full_mean->size[0] = loop_ub;
      c_res_full_mean->size[1] = 2;
      emxEnsureCapacity_real_T(c_res_full_mean, k);
      for (k = 0; k < loop_ub; k++) {
        c_res_full_mean->data[k] = res_full_mean->data[2 * (i + k)];
      }

      for (k = 0; k < loop_ub; k++) {
        c_res_full_mean->data[k + c_res_full_mean->size[0]] =
          res_full_mean->data[2 * (i + k) + 1];
      }

      cov(c_res_full_mean, res_var_data, res_var_size);
      *rvar_1 = res_var_data[0];
      *rvar_2 = res_var_data[1];
      *rvar_3 = res_var_data[2];

      /*     %% */
      res_var_data[0] = ProcessVar[0] * alpha;
      res_var_data[1] = ProcessVar[1] * alpha;
      res_var_data[2] = ProcessVar[6] * alpha;
      res_var_data[3] = ProcessVar[7] * alpha;
      d_f_generate_online_UKF_residua(PA, PP, FA, FP, RA, RP, FS, cal_coeff,
        dwfix, QL_nom, MeasNoiseVar, res_var_data, res_full_mean,
        res_full_variance);
      vlen = res_full_mean->size[1];
      if (2 > vlen) {
        vlen = 2;
      }

      if (res_full_mean->size[1] == 0) {
        vlen = 0;
      }

      i = y->size[0] * y->size[1];
      y->size[0] = 2;
      y->size[1] = vlen;
      emxEnsureCapacity_real_T(y, i);
      loop_ub = vlen << 1;
      for (i = 0; i < loop_ub; i++) {
        y->data[i] = 0.0;
      }

      vlen = res_full_mean->size[1];
      if (2 > vlen) {
        vlen = 2;
      }

      if (res_full_mean->size[1] == 0) {
        vlen = 0;
      }

      for (loop_ub = 0; loop_ub < vlen; loop_ub++) {
        y->data[2 * loop_ub] = res_full_mean->data[2 * loop_ub] -
          r_mean_nom_UKF_dwfix[0];
        i = 2 * loop_ub + 1;
        y->data[i] = res_full_mean->data[i] - r_mean_nom_UKF_dwfix[1];
      }

      /*      figure(9) */
      /*      plot(res_full_mean_dwfix(1,45:end), res_full_mean_dwfix(2,45:end), '.') */
      /*      hold on */
      f_GLT(Sigma_nom_UKF_dwfix, y, b_res_full_mean);
      i = s_max_UKF_dwfix->size[0];
      s_max_UKF_dwfix->size[0] = b_res_full_mean->size[1];
      emxEnsureCapacity_real_T(s_max_UKF_dwfix, i);
      loop_ub = b_res_full_mean->size[1];
      for (i = 0; i < loop_ub; i++) {
        s_max_UKF_dwfix->data[i] = b_res_full_mean->data[i];
      }

      if (60 > res_full_mean->size[1]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = res_full_mean->size[1];
      }

      vlen = b_res_full_mean->size[0] * b_res_full_mean->size[1];
      b_res_full_mean->size[0] = 1;
      loop_ub = k - i;
      b_res_full_mean->size[1] = loop_ub;
      emxEnsureCapacity_real_T(b_res_full_mean, vlen);
      for (k = 0; k < loop_ub; k++) {
        b_res_full_mean->data[k] = res_full_mean->data[2 * (i + k)];
      }

      *rm_I_dwfix = b_mean(b_res_full_mean);
      if (60 > res_full_mean->size[1]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = res_full_mean->size[1];
      }

      vlen = b_res_full_mean->size[0] * b_res_full_mean->size[1];
      b_res_full_mean->size[0] = 1;
      loop_ub = k - i;
      b_res_full_mean->size[1] = loop_ub;
      emxEnsureCapacity_real_T(b_res_full_mean, vlen);
      for (k = 0; k < loop_ub; k++) {
        b_res_full_mean->data[k] = res_full_mean->data[2 * (i + k) + 1];
      }

      *rm_Q_dwfix = b_mean(b_res_full_mean);

      /*     %% Parity Space Residual Genertation + GLRT Evaluation */
      c_f_generate_online_parityRes1_(PA, PP, FA, FP, FS, QL_nom, idxP);
      c_f_generate_online_parityRes2_(PA, PP, FA, FP, RA, RP, FS, cal_coeff,
        tau_m, K_m, QL_nom, b_PA);
      i = b_idxP->size[0] * b_idxP->size[1];
      b_idxP->size[0] = 1;
      b_idxP->size[1] = idxP->size[0];
      emxEnsureCapacity_real_T(b_idxP, i);
      loop_ub = idxP->size[0];
      for (i = 0; i < loop_ub; i++) {
        b_idxP->data[i] = idxP->data[i] - r_PS1_nom->data[i];
      }

      b_f_GLT(Sigma_nom_PS1, b_idxP, b_res_full_mean);
      i = s_max_PS1->size[0];
      s_max_PS1->size[0] = b_res_full_mean->size[1];
      emxEnsureCapacity_real_T(s_max_PS1, i);
      loop_ub = b_res_full_mean->size[1];
      for (i = 0; i < loop_ub; i++) {
        s_max_PS1->data[i] = b_res_full_mean->data[i];
      }

      if (60 > s_max_PS1->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_PS1->size[0];
      }

      loop_ub = k - i;
      k = x->size[0];
      x->size[0] = loop_ub;
      emxEnsureCapacity_boolean_T(x, k);
      for (k = 0; k < loop_ub; k++) {
        x->data[k] = (s_max_PS1->data[i + k] > 10.8);
      }

      vlen = x->size[0];
      if (x->size[0] == 0) {
        loop_ub = 0;
      } else {
        loop_ub = x->data[0];
        for (k = 2; k <= vlen; k++) {
          loop_ub += x->data[k - 1];
        }
      }

      *classis_PS = loop_ub;
      if (60 > s_max_PS1->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_PS1->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_PS1->data[i + k];
      }

      *strengthis_PS = mean(dw_res);
      if (60 > s_max_PS1->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_PS1->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_PS1->data[i + k];
      }

      *max_PS = maximum(dw_res);
      if (60 > s_max_PS1->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_PS1->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_PS1->data[i + k];
      }

      *median_PS = median(dw_res);
      if (60 > s_max_PS1->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_PS1->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_PS1->data[i + k];
      }

      *mode_PS = arraymode(dw_res);
      if (60 > s_max_PS1->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_PS1->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_PS1->data[i + k];
      }

      *var_PS = var(dw_res);

      /*     %% Check if GLT is above a threshold. */
      if (60 > s_max_UKF->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF->size[0];
      }

      loop_ub = k - i;
      k = x->size[0];
      x->size[0] = loop_ub;
      emxEnsureCapacity_boolean_T(x, k);
      for (k = 0; k < loop_ub; k++) {
        x->data[k] = (s_max_UKF->data[i + k] > 13.8);
      }

      vlen = x->size[0];
      if (x->size[0] == 0) {
        loop_ub = 0;
      } else {
        loop_ub = x->data[0];
        for (k = 2; k <= vlen; k++) {
          loop_ub += x->data[k - 1];
        }
      }

      *classis_UKF = loop_ub;
      if (60 > s_max_UKF->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF->data[i + k];
      }

      *strengthis_UKF = mean(dw_res);
      if (60 > s_max_UKF->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF->data[i + k];
      }

      *max_UKF = maximum(dw_res);
      if (60 > s_max_UKF->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF->data[i + k];
      }

      *median_UKF = median(dw_res);
      if (60 > s_max_UKF->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF->data[i + k];
      }

      *mode_UKF = arraymode(dw_res);
      if (60 > s_max_UKF->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF->data[i + k];
      }

      *var_UKF = var(dw_res);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF_dwfix->size[0];
      }

      loop_ub = k - i;
      k = x->size[0];
      x->size[0] = loop_ub;
      emxEnsureCapacity_boolean_T(x, k);
      for (k = 0; k < loop_ub; k++) {
        x->data[k] = (s_max_UKF_dwfix->data[i + k] > 13.8);
      }

      vlen = x->size[0];
      if (x->size[0] == 0) {
        loop_ub = 0;
      } else {
        loop_ub = x->data[0];
        for (k = 2; k <= vlen; k++) {
          loop_ub += x->data[k - 1];
        }
      }

      *classis_dwfix = loop_ub;
      if (60 > s_max_UKF_dwfix->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF_dwfix->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF_dwfix->data[i + k];
      }

      *strengthis_dwfix = mean(dw_res);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF_dwfix->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF_dwfix->data[i + k];
      }

      *max_dwfix = maximum(dw_res);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF_dwfix->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF_dwfix->data[i + k];
      }

      *median_dwfix = median(dw_res);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF_dwfix->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF_dwfix->data[i + k];
      }

      *mode_dwfix = arraymode(dw_res);
      if (60 > s_max_UKF_dwfix->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 59;
        k = s_max_UKF_dwfix->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_UKF_dwfix->data[i + k];
      }

      *var_dwfix = var(dw_res);

      /*     %% Get QL value and static detuning value */
      i = y_mC->size[0];
      y_mC->size[0] = PP->size[0];
      emxEnsureCapacity_creal_T(y_mC, i);
      loop_ub = PP->size[0];
      for (i = 0; i < loop_ub; i++) {
        a_tmp = 0.0 * PP->data[i];
        b = PP->data[i];
        if (b == 0.0) {
          a = a_tmp / 180.0;
          a_tmp = 0.0;
        } else if (a_tmp == 0.0) {
          a = 0.0;
          a_tmp = b / 180.0;
        } else {
          a = rtNaN;
          a_tmp = b / 180.0;
        }

        y_mC->data[i].re = 3.1415926535897931 * a;
        y_mC->data[i].im = 3.1415926535897931 * a_tmp;
      }

      b_exp(y_mC);
      i = y_mC->size[0];
      y_mC->size[0] = PA->size[0];
      emxEnsureCapacity_creal_T(y_mC, i);
      loop_ub = PA->size[0];
      for (i = 0; i < loop_ub; i++) {
        y_mC->data[i].re *= PA->data[i];
        y_mC->data[i].im *= PA->data[i];
      }

      /*  Complex Probe measurement */
      /*  Complex Forward measurement */
      /*  Reflected */
      i = u_mCal->size[0];
      u_mCal->size[0] = FP->size[0];
      emxEnsureCapacity_creal_T(u_mCal, i);
      loop_ub = FP->size[0];
      for (i = 0; i < loop_ub; i++) {
        a_tmp = 0.0 * FP->data[i];
        b = FP->data[i];
        if (b == 0.0) {
          a = a_tmp / 180.0;
          a_tmp = 0.0;
        } else if (a_tmp == 0.0) {
          a = 0.0;
          a_tmp = b / 180.0;
        } else {
          a = rtNaN;
          a_tmp = b / 180.0;
        }

        u_mCal->data[i].re = 3.1415926535897931 * a;
        u_mCal->data[i].im = 3.1415926535897931 * a_tmp;
      }

      b_exp(u_mCal);
      i = r_mCal->size[0];
      r_mCal->size[0] = RP->size[0];
      emxEnsureCapacity_creal_T(r_mCal, i);
      loop_ub = RP->size[0];
      for (i = 0; i < loop_ub; i++) {
        a_tmp = 0.0 * RP->data[i];
        b = RP->data[i];
        if (b == 0.0) {
          a = a_tmp / 180.0;
          a_tmp = 0.0;
        } else if (a_tmp == 0.0) {
          a = 0.0;
          a_tmp = b / 180.0;
        } else {
          a = rtNaN;
          a_tmp = b / 180.0;
        }

        r_mCal->data[i].re = 3.1415926535897931 * a;
        r_mCal->data[i].im = 3.1415926535897931 * a_tmp;
      }

      b_exp(r_mCal);
      i = b_FA->size[0];
      b_FA->size[0] = FA->size[0];
      emxEnsureCapacity_creal_T(b_FA, i);
      loop_ub = FA->size[0];
      for (i = 0; i < loop_ub; i++) {
        b_FA->data[i].re = FA->data[i] * u_mCal->data[i].re;
        b_FA->data[i].im = FA->data[i] * u_mCal->data[i].im;
      }

      i = b_RA->size[0];
      b_RA->size[0] = RA->size[0];
      emxEnsureCapacity_creal_T(b_RA, i);
      loop_ub = RA->size[0];
      for (i = 0; i < loop_ub; i++) {
        b_RA->data[i].re = RA->data[i] * r_mCal->data[i].re;
        b_RA->data[i].im = RA->data[i] * r_mCal->data[i].im;
      }

      f_calibrateData(b_FA, b_RA, cal_coeff, u_mCal, r_mCal);
      i = b_FA->size[0];
      b_FA->size[0] = Flattop->size[1];
      emxEnsureCapacity_creal_T(b_FA, i);
      loop_ub = Flattop->size[1];
      for (i = 0; i < loop_ub; i++) {
        k = (int)Flattop->data[i] - 1;
        b_FA->data[i].re = y_mC->data[k].re - (u_mCal->data[k].re + r_mCal->
          data[k].re);
        b_FA->data[i].im = y_mC->data[k].im - (u_mCal->data[k].im + r_mCal->
          data[k].im);
      }

      vlen = b_FA->size[0];
      i = idxP->size[0];
      idxP->size[0] = b_FA->size[0];
      emxEnsureCapacity_real_T(idxP, i);
      for (k = 0; k < vlen; k++) {
        idxP->data[k] = rt_hypotd_snf(b_FA->data[k].re, b_FA->data[k].im);
      }

      if (mean(idxP) < 0.05) {
        if (25 > Decay->size[1] - 1) {
          i = 0;
          k = 0;
        } else {
          i = 24;
          k = Decay->size[1] - 1;
        }

        loop_ub = k - i;
        k = b_FA->size[0];
        b_FA->size[0] = loop_ub;
        emxEnsureCapacity_creal_T(b_FA, k);
        for (k = 0; k < loop_ub; k++) {
          b_FA->data[k] = u_mCal->data[(int)Decay->data[i + k] - 1];
        }

        i = idxP->size[0];
        idxP->size[0] = loop_ub;
        emxEnsureCapacity_real_T(idxP, i);
        for (k = 0; k < loop_ub; k++) {
          idxP->data[k] = rt_hypotd_snf(b_FA->data[k].re, b_FA->data[k].im);
        }

        if (mean(idxP) < 0.8) {
          *calib_check = 1.0;
        } else {
          *calib_check = 0.0;
        }
      } else {
        *calib_check = 0.0;
      }

      *QL = f_computeQL(Rise, u_mCal, y_mC, fs, f0);

      /*  dwfix = f_compute_detuning(y_mC, u_mCal, fs, QL_nom); */
      /*     %% Detuning/Bandwidth Heuristic + GLRT Evaluation */
      f_comp_dw_ql_Rybaniec(y_mC, u_mCal, fs, 6.2831853071795862 * f0 / (2.0 *
        QL_nom), dw, idxP);
      smoothdata(dw, r1);
      i = dw_res->size[0];
      dw_res->size[0] = r1->size[0];
      emxEnsureCapacity_real_T(dw_res, i);
      loop_ub = r1->size[0];
      for (i = 0; i < loop_ub; i++) {
        dw_res->data[i] = r1->data[i] - dwfix->data[i];
      }

      smoothdata(idxP, r1);

      /* [s_max_UKF_dwfix] = f_GLT(Sigma_nom_UKF_dwfix, y, N).'; */
      repmat(r_mean_nom_dwql, dw_res->size[0], res_full_mean);
      i = y->size[0] * y->size[1];
      y->size[0] = 2;
      y->size[1] = dw_res->size[0];
      emxEnsureCapacity_real_T(y, i);
      loop_ub = dw_res->size[0];
      for (i = 0; i < loop_ub; i++) {
        y->data[2 * i] = dw_res->data[i] - res_full_mean->data[2 * i];
      }

      loop_ub = r1->size[0];
      for (i = 0; i < loop_ub; i++) {
        k = 2 * i + 1;
        y->data[k] = (r1->data[i] - w12fix->data[i]) - res_full_mean->data[k];
      }

      f_GLT(Sigma_nom_dwql, y, b_res_full_mean);
      i = s_max_dwql->size[0];
      s_max_dwql->size[0] = b_res_full_mean->size[1];
      emxEnsureCapacity_real_T(s_max_dwql, i);
      loop_ub = b_res_full_mean->size[1];
      for (i = 0; i < loop_ub; i++) {
        s_max_dwql->data[i] = b_res_full_mean->data[i];
      }

      if (170 > s_max_dwql->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 169;
        k = s_max_dwql->size[0];
      }

      loop_ub = k - i;
      k = x->size[0];
      x->size[0] = loop_ub;
      emxEnsureCapacity_boolean_T(x, k);
      for (k = 0; k < loop_ub; k++) {
        x->data[k] = (s_max_dwql->data[i + k] > 13.8);
      }

      vlen = x->size[0];
      if (x->size[0] == 0) {
        loop_ub = 0;
      } else {
        loop_ub = x->data[0];
        for (k = 2; k <= vlen; k++) {
          loop_ub += x->data[k - 1];
        }
      }

      *classis_dwql = loop_ub;
      if (170 > s_max_dwql->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 169;
        k = s_max_dwql->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_dwql->data[i + k];
      }

      *strengthis_dwql = mean(dw_res);
      if (170 > s_max_dwql->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 169;
        k = s_max_dwql->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_dwql->data[i + k];
      }

      *max_dwql = maximum(dw_res);
      if (170 > s_max_dwql->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 169;
        k = s_max_dwql->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_dwql->data[i + k];
      }

      *median_dwql = median(dw_res);
      if (170 > s_max_dwql->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 169;
        k = s_max_dwql->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_dwql->data[i + k];
      }

      *mode_dwql = arraymode(dw_res);
      if (170 > s_max_dwql->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 169;
        k = s_max_dwql->size[0];
      }

      loop_ub = k - i;
      k = dw_res->size[0];
      dw_res->size[0] = loop_ub;
      emxEnsureCapacity_real_T(dw_res, k);
      for (k = 0; k < loop_ub; k++) {
        dw_res->data[k] = s_max_dwql->data[i + k];
      }

      *var_dwql = var(dw_res);

      /*     %% */
      i = dw_res->size[0];
      dw_res->size[0] = Flattop->size[1];
      emxEnsureCapacity_real_T(dw_res, i);
      loop_ub = Flattop->size[1];
      for (i = 0; i < loop_ub; i++) {
        dw_res->data[i] = dw->data[(int)Flattop->data[i] - 1];
      }

      *dw_stat = mean(dw_res);
      i = dw_res->size[0];
      dw_res->size[0] = Flattop->size[1];
      emxEnsureCapacity_real_T(dw_res, i);
      loop_ub = Flattop->size[1];
      for (i = 0; i < loop_ub; i++) {
        dw_res->data[i] = PA->data[(int)Flattop->data[i] - 1];
      }

      *SP_P = mean(dw_res);
      i = b_FA->size[0];
      b_FA->size[0] = Rise->size[1];
      emxEnsureCapacity_creal_T(b_FA, i);
      loop_ub = Rise->size[1];
      for (i = 0; i < loop_ub; i++) {
        b_FA->data[i] = u_mCal->data[(int)Rise->data[i] - 1];
      }

      vlen = Rise->size[1];
      i = idxP->size[0];
      idxP->size[0] = Rise->size[1];
      emxEnsureCapacity_real_T(idxP, i);
      for (k = 0; k < vlen; k++) {
        idxP->data[k] = rt_hypotd_snf(b_FA->data[k].re, b_FA->data[k].im);
      }

      *SP_F = mean(idxP);
      loop_ub = u_mCal->size[0];
      i = b_FA->size[0];
      b_FA->size[0] = u_mCal->size[0];
      emxEnsureCapacity_creal_T(b_FA, i);
      for (i = 0; i < loop_ub; i++) {
        b_FA->data[i] = u_mCal->data[i];
      }

      i = u_mCal->size[0] - 1;
      k = idxP->size[0];
      idxP->size[0] = u_mCal->size[0];
      emxEnsureCapacity_real_T(idxP, k);
      for (k = 0; k <= i; k++) {
        idxP->data[k] = rt_hypotd_snf(b_FA->data[k].re, b_FA->data[k].im);
      }

      i = x->size[0];
      x->size[0] = idxP->size[0];
      emxEnsureCapacity_boolean_T(x, i);
      loop_ub = idxP->size[0];
      for (i = 0; i < loop_ub; i++) {
        x->data[i] = (idxP->data[i] < 1.5);
      }

      eml_find(x, r);
      i = idxP->size[0];
      idxP->size[0] = r->size[0];
      emxEnsureCapacity_real_T(idxP, i);
      loop_ub = r->size[0];
      for (i = 0; i < loop_ub; i++) {
        idxP->data[i] = r->data[i];
      }

      loop_ub = idxP->size[0] - 1;
      vlen = 0;
      for (s = 0; s <= loop_ub; s++) {
        if (idxP->data[s] > (double)(unsigned int)Rise->data[0] + 3.0) {
          vlen++;
        }
      }

      i = r2->size[0];
      r2->size[0] = vlen;
      emxEnsureCapacity_int32_T(r2, i);
      vlen = 0;
      for (s = 0; s <= loop_ub; s++) {
        if (idxP->data[s] > (double)(unsigned int)Rise->data[0] + 3.0) {
          r2->data[vlen] = s + 1;
          vlen++;
        }
      }

      *PC = idxP->data[r2->data[0] - 1];

      /* double(abs(u_mCal(Flattop(end-1))) < 1); */
      *dec_hq = fabs(*QL - QL_nom);
      if (1420 > FP->size[0]) {
        i = 0;
        k = 0;
      } else {
        i = 1419;
        k = FP->size[0];
      }

      loop_ub = k - i;
      k = x->size[0];
      x->size[0] = loop_ub;
      emxEnsureCapacity_boolean_T(x, k);
      for (k = 0; k < loop_ub; k++) {
        x->data[k] = (FP->data[i + k] == 0.0);
      }

      vlen = x->size[0];
      if (x->size[0] == 0) {
        loop_ub = 0;
      } else {
        loop_ub = x->data[0];
        for (k = 2; k <= vlen; k++) {
          loop_ub += x->data[k - 1];
        }
      }

      *zpth = loop_ub;
    } else {
      b_guard1 = true;
    }
  } else {
    b_guard1 = true;
  }

  if (b_guard1) {
    i = s_max_UKF->size[0];
    s_max_UKF->size[0] = PA->size[0];
    emxEnsureCapacity_real_T(s_max_UKF, i);
    loop_ub = PA->size[0];
    for (i = 0; i < loop_ub; i++) {
      s_max_UKF->data[i] = rtNaN;
    }

    i = s_max_UKF_dwfix->size[0];
    s_max_UKF_dwfix->size[0] = PA->size[0];
    emxEnsureCapacity_real_T(s_max_UKF_dwfix, i);
    loop_ub = PA->size[0];
    for (i = 0; i < loop_ub; i++) {
      s_max_UKF_dwfix->data[i] = rtNaN;
    }

    i = s_max_PS1->size[0];
    s_max_PS1->size[0] = r_PS1_nom->size[0];
    emxEnsureCapacity_real_T(s_max_PS1, i);
    loop_ub = r_PS1_nom->size[0];
    for (i = 0; i < loop_ub; i++) {
      s_max_PS1->data[i] = rtNaN;
    }

    i = s_max_dwql->size[0];
    s_max_dwql->size[0] = PA->size[0];
    emxEnsureCapacity_real_T(s_max_dwql, i);
    loop_ub = PA->size[0];
    for (i = 0; i < loop_ub; i++) {
      s_max_dwql->data[i] = rtNaN;
    }

    *classis_UKF = rtNaN;
    *classis_PS = rtNaN;
    *classis_dwql = rtNaN;
    *classis_dwfix = rtNaN;
    *strengthis_UKF = rtNaN;
    *strengthis_PS = rtNaN;
    *strengthis_dwql = rtNaN;
    *strengthis_dwfix = rtNaN;
    *max_UKF = rtNaN;
    *max_PS = rtNaN;
    *max_dwql = rtNaN;
    *max_dwfix = rtNaN;
    *median_UKF = rtNaN;
    *median_PS = rtNaN;
    *median_dwql = rtNaN;
    *median_dwfix = rtNaN;
    *mode_UKF = rtNaN;
    *mode_dwfix = rtNaN;
    *mode_PS = rtNaN;
    *mode_dwql = rtNaN;
    *var_UKF = rtNaN;
    *var_dwfix = rtNaN;
    *var_PS = rtNaN;
    *var_dwql = rtNaN;
    *rm_I = rtNaN;
    *rm_Q = rtNaN;
    *rm_I_dwfix = rtNaN;
    *rm_Q_dwfix = rtNaN;
    *rvar_1 = rtNaN;
    *rvar_2 = rtNaN;
    *rvar_3 = rtNaN;
    *QL = rtNaN;
    *dw_stat = rtNaN;
    *SP_F = rtNaN;
    *SP_P = rtNaN;
    *PC = rtNaN;
    *calib_check = rtNaN;
    *dec_hq = rtNaN;
    *zpth = rtNaN;
  }

  emxFree_real_T(&b_PA);
  emxFree_creal_T(&b_RA);
  emxFree_creal_T(&b_FA);
  emxFree_real_T(&b_idxP);
  emxFree_real_T(&c_res_full_mean);
  emxFree_real_T(&b_res_full_mean);
  emxFree_int32_T(&r);
  emxFree_boolean_T(&x);
  emxFree_int32_T(&r2);
  emxFree_real_T(&r1);
  emxFree_real_T(&dw);
  emxFree_creal_T(&r_mCal);
  emxFree_creal_T(&u_mCal);
  emxFree_real_T(&res_full_variance);
  emxFree_real_T(&res_full_mean);
  emxFree_real_T(&dw_res);
  emxFree_creal_T(&y_mC);
  emxFree_real_T(&y);
  emxFree_real_T(&idxP);
  emxFree_real_T(&Decay);
  emxFree_real_T(&Flattop);
  emxFree_real_T(&Rise);

  /*  figure(14), */
  /*  hold on */
  /*  plot(dw,'') */
  /*  figure(21) */
  /*  hold on */
  /*  plot(res_full_mean(1,:),'k') */
  /*  plot(res_full_mean(2,:),'k') */
  /*  xlabel('Samples') */
  /*  ylabel('Residual') */
  /*  ylim([-0.05,0.05]) */
  /* [FIT, y_mC_hat]=f_cavitySystemSimulatior(y_mC, u_mC, f0, fs, sys_hat, QL, plt, u3) */
}

/* End of code generation (f_generate_and_eval_multi_residuals_dwql.c) */
