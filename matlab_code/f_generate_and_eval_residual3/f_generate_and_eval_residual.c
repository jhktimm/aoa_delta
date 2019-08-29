/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_and_eval_residual.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 23-Aug-2019 08:22:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_generate_and_eval_residual_emxutil.h"
#include "combineVectorElements.h"
#include "abs.h"
#include "f_compute_detuning.h"
#include "log.h"
#include "f_calibrateData.h"
#include "exp.h"
#include "sum.h"
#include "f_GLT.h"
#include "f_generate_online_UKF_residual_full.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
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

/*
 * This function evaluates the residual
 * Arguments    : const emxArray_real_T *PA
 *                emxArray_real_T *PP
 *                const emxArray_real_T *FA
 *                const emxArray_real_T *FP
 *                const emxArray_real_T *RA
 *                const emxArray_real_T *RP
 *                double FS
 *                double F0
 *                const creal_T cal_coeff[4]
 *                const double tau_m[4]
 *                const double K_m[4]
 *                const double X0[4]
 *                double QL_nom
 *                double DELAY
 *                double FILLING
 *                double FLATTOP
 *                const double Sigma_nom[4]
 *                const double r_mean_nom[2]
 *                const double MeasNoiseVar[4]
 *                const double ProcessVar[36]
 *                emxArray_real_T *s_max
 *                double *classis
 *                double *strengthis
 *                double *QL
 *                double *dw_stat
 *                double *SP_F
 *                double *SP_P
 * Return Type  : void
 */
void f_generate_and_eval_residual(const emxArray_real_T *PA, emxArray_real_T *PP,
  const emxArray_real_T *FA, const emxArray_real_T *FP, const emxArray_real_T
  *RA, const emxArray_real_T *RP, double FS, double F0, const creal_T cal_coeff
  [4], const double tau_m[4], const double K_m[4], const double X0[4], double
  QL_nom, double DELAY, double FILLING, double FLATTOP, const double Sigma_nom[4],
  const double r_mean_nom[2], const double MeasNoiseVar[4], const double
  ProcessVar[36], emxArray_real_T *s_max, double *classis, double *strengthis,
  double *QL, double *dw_stat, double *SP_F, double *SP_P)
{
  emxArray_real_T *dw;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  emxArray_real_T *b_s_max;
  emxArray_boolean_T *b_PP;
  int exitg1;
  int i0;
  int idx;
  int ixstart;
  int n;
  double mtmp;
  emxArray_real_T *res_full_mean;
  emxArray_real_T *y;
  boolean_T exitg2;
  emxArray_real_T *res_full_variance;
  int b_ii;
  emxArray_real_T *Rise;
  double res_full_mean_data[2];
  double b_classis;
  double b_strengthis;
  double fs;
  emxArray_real_T *Flattop;
  emxArray_real_T *Decay;
  double b_x;
  double ndbl;
  double apnd;
  double cdiff;
  double absa;
  double d;
  double absb;
  emxArray_creal_T *y_mC;
  emxArray_creal_T *u_mCal;
  emxArray_creal_T *unusedU0;
  emxArray_creal_T *b_FA;
  emxArray_creal_T *b_RA;
  emxArray_creal_T *b_y_mC;
  short t2;
  short i1;
  emxArray_real_T *lnA;
  emxInit_real_T1(&dw, 1);
  emxInit_boolean_T(&x, 1);
  emxInit_int32_T(&ii, 1);
  emxInit_real_T1(&b_s_max, 1);
  emxInit_boolean_T(&b_PP, 1);
  do {
    exitg1 = 0;
    if (40 > PP->size[0]) {
      i0 = 0;
      idx = 0;
    } else {
      i0 = 39;
      idx = PP->size[0];
    }

    ixstart = b_PP->size[0];
    b_PP->size[0] = idx - i0;
    emxEnsureCapacity_boolean_T(b_PP, ixstart);
    ixstart = idx - i0;
    for (idx = 0; idx < ixstart; idx++) {
      b_PP->data[idx] = (PP->data[i0 + idx] == 0.0);
    }

    if (sum(b_PP) > 0.0) {
      if (40 > PP->size[0]) {
        i0 = 0;
        idx = 0;
      } else {
        i0 = 39;
        idx = PP->size[0];
      }

      ixstart = x->size[0];
      x->size[0] = idx - i0;
      emxEnsureCapacity_boolean_T(x, ixstart);
      ixstart = idx - i0;
      for (idx = 0; idx < ixstart; idx++) {
        x->data[idx] = (PP->data[i0 + idx] == 0.0);
      }

      ixstart = x->size[0];
      idx = 0;
      i0 = ii->size[0];
      ii->size[0] = x->size[0];
      emxEnsureCapacity_int32_T(ii, i0);
      b_ii = 1;
      exitg2 = false;
      while ((!exitg2) && (b_ii <= ixstart)) {
        if (x->data[b_ii - 1]) {
          idx++;
          ii->data[idx - 1] = b_ii;
          if (idx >= ixstart) {
            exitg2 = true;
          } else {
            b_ii++;
          }
        } else {
          b_ii++;
        }
      }

      if (x->size[0] == 1) {
        if (idx == 0) {
          i0 = ii->size[0];
          ii->size[0] = 0;
          emxEnsureCapacity_int32_T(ii, i0);
        }
      } else {
        i0 = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }

        emxEnsureCapacity_int32_T(ii, i0);
      }

      i0 = dw->size[0];
      dw->size[0] = ii->size[0];
      emxEnsureCapacity_real_T1(dw, i0);
      ixstart = ii->size[0];
      for (i0 = 0; i0 < ixstart; i0++) {
        dw->data[i0] = ii->data[i0];
      }

      i0 = ii->size[0];
      ii->size[0] = dw->size[0];
      emxEnsureCapacity_int32_T(ii, i0);
      ixstart = dw->size[0];
      for (i0 = 0; i0 < ixstart; i0++) {
        ii->data[i0] = (int)((40.0 + dw->data[i0]) - 1.0);
      }

      i0 = b_s_max->size[0];
      b_s_max->size[0] = dw->size[0];
      emxEnsureCapacity_real_T1(b_s_max, i0);
      ixstart = dw->size[0];
      for (i0 = 0; i0 < ixstart; i0++) {
        b_s_max->data[i0] = PP->data[(int)((40.0 + dw->data[i0]) - 2.0) - 1];
      }

      ixstart = b_s_max->size[0];
      for (i0 = 0; i0 < ixstart; i0++) {
        PP->data[ii->data[i0] - 1] = b_s_max->data[i0];
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_boolean_T(&x);
  ixstart = 1;
  n = PA->size[0];
  mtmp = PA->data[0];
  if (PA->size[0] > 1) {
    if (rtIsNaN(PA->data[0])) {
      idx = 2;
      exitg2 = false;
      while ((!exitg2) && (idx <= n)) {
        ixstart = idx;
        if (!rtIsNaN(PA->data[idx - 1])) {
          mtmp = PA->data[idx - 1];
          exitg2 = true;
        } else {
          idx++;
        }
      }
    }

    if (ixstart < PA->size[0]) {
      while (ixstart + 1 <= n) {
        if (PA->data[ixstart] > mtmp) {
          mtmp = PA->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  emxInit_real_T(&res_full_mean, 2);
  emxInit_real_T(&y, 2);
  if (mtmp < 10.0) {
    i0 = res_full_mean->size[0] * res_full_mean->size[1];
    res_full_mean->size[0] = 1;
    res_full_mean->size[1] = 1;
    emxEnsureCapacity_real_T(res_full_mean, i0);
    res_full_mean->data[0] = rtNaN;
  } else {
    emxInit_real_T2(&res_full_variance, 3);
    c_f_generate_online_UKF_residua(PA, PP, FA, FP, RA, RP, FS, cal_coeff, tau_m,
      K_m, X0, QL_nom, MeasNoiseVar, ProcessVar, y, res_full_variance);
    i0 = res_full_mean->size[0] * res_full_mean->size[1];
    res_full_mean->size[0] = 2;
    res_full_mean->size[1] = y->size[1];
    emxEnsureCapacity_real_T(res_full_mean, i0);
    ixstart = y->size[0] * y->size[1];
    emxFree_real_T(&res_full_variance);
    for (i0 = 0; i0 < ixstart; i0++) {
      res_full_mean->data[i0] = y->data[i0];
    }
  }

  /*  r_cmplx = res_full_mean(1,:).'+1i*res_full_mean(2,:).'; */
  if (res_full_mean->size[1] == 0) {
    n = 0;
  } else if (res_full_mean->size[0] > res_full_mean->size[1]) {
    n = 2;
  } else {
    n = res_full_mean->size[1];
  }

  i0 = y->size[0] * y->size[1];
  y->size[0] = 2;
  y->size[1] = n;
  emxEnsureCapacity_real_T(y, i0);
  ixstart = n << 1;
  for (i0 = 0; i0 < ixstart; i0++) {
    y->data[i0] = 0.0;
  }

  if (res_full_mean->size[1] == 0) {
    n = 0;
  } else if (res_full_mean->size[0] > res_full_mean->size[1]) {
    n = 2;
  } else {
    n = res_full_mean->size[1];
  }

  for (b_ii = 0; b_ii < n; b_ii++) {
    ixstart = res_full_mean->size[0];
    for (i0 = 0; i0 < ixstart; i0++) {
      res_full_mean_data[i0] = res_full_mean->data[i0 + res_full_mean->size[0] *
        b_ii];
    }

    for (i0 = 0; i0 < 2; i0++) {
      y->data[i0 + y->size[0] * b_ii] = res_full_mean_data[i0] - r_mean_nom[i0];
    }
  }

  emxFree_real_T(&res_full_mean);
  emxInit_real_T(&Rise, 2);
  f_GLT(Sigma_nom, y, Rise);
  i0 = s_max->size[0];
  s_max->size[0] = Rise->size[1];
  emxEnsureCapacity_real_T1(s_max, i0);
  ixstart = Rise->size[1];
  emxFree_real_T(&y);
  for (i0 = 0; i0 < ixstart; i0++) {
    s_max->data[i0] = Rise->data[Rise->size[0] * i0];
  }

  /*  Check if GLT is above a threshold. */
  if (40 > s_max->size[0]) {
    i0 = 0;
    idx = 0;
  } else {
    i0 = 39;
    idx = s_max->size[0];
  }

  ixstart = b_PP->size[0];
  b_PP->size[0] = idx - i0;
  emxEnsureCapacity_boolean_T(b_PP, ixstart);
  ixstart = idx - i0;
  for (idx = 0; idx < ixstart; idx++) {
    b_PP->data[idx] = (s_max->data[i0 + idx] > 13.8);
  }

  b_classis = sum(b_PP);
  emxFree_boolean_T(&b_PP);
  if (40 > s_max->size[0]) {
    i0 = 0;
    idx = 0;
  } else {
    i0 = 39;
    idx = s_max->size[0];
  }

  ixstart = b_s_max->size[0];
  b_s_max->size[0] = idx - i0;
  emxEnsureCapacity_real_T1(b_s_max, ixstart);
  ixstart = idx - i0;
  for (idx = 0; idx < ixstart; idx++) {
    b_s_max->data[idx] = s_max->data[i0 + idx];
  }

  b_strengthis = b_sum(b_s_max);

  /*  Get QL value and static detuning value */
  fs = FS * 1.0E+6;
  emxInit_real_T(&Flattop, 2);
  emxInit_real_T(&Decay, 2);
  if (fs == 1.0E+6) {
    mtmp = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6);
    b_x = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6 + FILLING * 1.0E+6 * 1.0E-6);
    if (rtIsNaN(mtmp) || rtIsNaN(b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (b_x < mtmp) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity_real_T(Rise, i0);
    } else if ((rtIsInf(mtmp) || rtIsInf(b_x)) && (mtmp == b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (mtmp == mtmp) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - mtmp) + 1;
      emxEnsureCapacity_real_T(Rise, i0);
      ixstart = (int)(b_x - mtmp);
      for (i0 = 0; i0 <= ixstart; i0++) {
        Rise->data[Rise->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((b_x - mtmp) + 0.5);
      apnd = mtmp + ndbl;
      cdiff = apnd - b_x;
      absa = fabs(mtmp);
      absb = fabs(b_x);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = b_x;
      } else if (cdiff > 0.0) {
        apnd = mtmp + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = n;
      emxEnsureCapacity_real_T(Rise, i0);
      if (n > 0) {
        Rise->data[0] = mtmp;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          ixstart = (n - 1) / 2;
          for (idx = 1; idx < ixstart; idx++) {
            Rise->data[idx] = mtmp + (double)idx;
            Rise->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (ixstart << 1 == n - 1) {
            Rise->data[ixstart] = (mtmp + apnd) / 2.0;
          } else {
            Rise->data[ixstart] = mtmp + (double)ixstart;
            Rise->data[ixstart + 1] = apnd - (double)ixstart;
          }
        }
      }
    }

    d = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * 1.0E+6 *
      1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      Flattop->data[0] = rtNaN;
    } else if (d < Rise->data[Rise->size[1] - 1] + 1.0) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity_real_T(Flattop, i0);
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(d)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      mtmp = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(d - mtmp) + 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      ixstart = (int)floor(d - mtmp);
      for (i0 = 0; i0 <= ixstart; i0++) {
        Flattop->data[Flattop->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((d - (Rise->data[Rise->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + ndbl;
      cdiff = apnd - d;
      absa = fabs(Rise->data[Rise->size[1] - 1] + 1.0);
      absb = fabs(d);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = d;
      } else if (cdiff > 0.0) {
        apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = n;
      emxEnsureCapacity_real_T(Flattop, i0);
      if (n > 0) {
        Flattop->data[0] = Rise->data[Rise->size[1] - 1] + 1.0;
        if (n > 1) {
          Flattop->data[n - 1] = apnd;
          ixstart = (n - 1) / 2;
          for (idx = 1; idx < ixstart; idx++) {
            Flattop->data[idx] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)
              idx;
            Flattop->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (ixstart << 1 == n - 1) {
            Flattop->data[ixstart] = ((Rise->data[Rise->size[1] - 1] + 1.0) +
              apnd) / 2.0;
          } else {
            Flattop->data[ixstart] = (Rise->data[Rise->size[1] - 1] + 1.0) +
              (double)ixstart;
            Flattop->data[ixstart + 1] = apnd - (double)ixstart;
          }
        }
      }
    }

    if (rtIsNaN(Flattop->data[Flattop->size[1] - 1] + 1.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity_real_T(Decay, i0);
      Decay->data[0] = rtNaN;
    } else if (1821.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 0;
      emxEnsureCapacity_real_T(Decay, i0);
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 1821.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity_real_T(Decay, i0);
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      mtmp = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(1821.0 - mtmp) + 1;
      emxEnsureCapacity_real_T(Decay, i0);
      ixstart = (int)floor(1821.0 - mtmp);
      for (i0 = 0; i0 <= ixstart; i0++) {
        Decay->data[Decay->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((1821.0 - (Flattop->data[Flattop->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Flattop->data[Flattop->size[1] - 1] + 1.0) + ndbl;
      absa = fabs(Flattop->data[Flattop->size[1] - 1] + 1.0);
      if (!(absa > 1821.0)) {
        absa = 1821.0;
      }

      if (fabs(apnd - 1821.0) < 4.4408920985006262E-16 * absa) {
        ndbl++;
        apnd = 1821.0;
      } else if (apnd - 1821.0 > 0.0) {
        apnd = (Flattop->data[Flattop->size[1] - 1] + 1.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = n;
      emxEnsureCapacity_real_T(Decay, i0);
      if (n > 0) {
        Decay->data[0] = Flattop->data[Flattop->size[1] - 1] + 1.0;
        if (n > 1) {
          Decay->data[n - 1] = apnd;
          ixstart = (n - 1) / 2;
          for (idx = 1; idx < ixstart; idx++) {
            Decay->data[idx] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)idx;
            Decay->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (ixstart << 1 == n - 1) {
            Decay->data[ixstart] = ((Flattop->data[Flattop->size[1] - 1] + 1.0)
              + apnd) / 2.0;
          } else {
            Decay->data[ixstart] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)ixstart;
            Decay->data[ixstart + 1] = apnd - (double)ixstart;
          }
        }
      }
    }
  } else {
    mtmp = rt_roundd_snf(DELAY * fs * 1.0E-6);
    b_x = rt_roundd_snf(DELAY * fs * 1.0E-6 + FILLING * fs * 1.0E-6);
    if (rtIsNaN(mtmp) || rtIsNaN(b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (b_x < mtmp) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity_real_T(Rise, i0);
    } else if ((rtIsInf(mtmp) || rtIsInf(b_x)) && (mtmp == b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (mtmp == mtmp) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - mtmp) + 1;
      emxEnsureCapacity_real_T(Rise, i0);
      ixstart = (int)(b_x - mtmp);
      for (i0 = 0; i0 <= ixstart; i0++) {
        Rise->data[Rise->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((b_x - mtmp) + 0.5);
      apnd = mtmp + ndbl;
      cdiff = apnd - b_x;
      absa = fabs(mtmp);
      absb = fabs(b_x);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = b_x;
      } else if (cdiff > 0.0) {
        apnd = mtmp + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = n;
      emxEnsureCapacity_real_T(Rise, i0);
      if (n > 0) {
        Rise->data[0] = mtmp;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          ixstart = (n - 1) / 2;
          for (idx = 1; idx < ixstart; idx++) {
            Rise->data[idx] = mtmp + (double)idx;
            Rise->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (ixstart << 1 == n - 1) {
            Rise->data[ixstart] = (mtmp + apnd) / 2.0;
          } else {
            Rise->data[ixstart] = mtmp + (double)ixstart;
            Rise->data[ixstart + 1] = apnd - (double)ixstart;
          }
        }
      }
    }

    d = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * fs *
      1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      Flattop->data[0] = rtNaN;
    } else if (d < Rise->data[Rise->size[1] - 1] + 1.0) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity_real_T(Flattop, i0);
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(d)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      mtmp = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(d - mtmp) + 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      ixstart = (int)floor(d - mtmp);
      for (i0 = 0; i0 <= ixstart; i0++) {
        Flattop->data[Flattop->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((d - (Rise->data[Rise->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + ndbl;
      cdiff = apnd - d;
      absa = fabs(Rise->data[Rise->size[1] - 1] + 1.0);
      absb = fabs(d);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = d;
      } else if (cdiff > 0.0) {
        apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = n;
      emxEnsureCapacity_real_T(Flattop, i0);
      if (n > 0) {
        Flattop->data[0] = Rise->data[Rise->size[1] - 1] + 1.0;
        if (n > 1) {
          Flattop->data[n - 1] = apnd;
          ixstart = (n - 1) / 2;
          for (idx = 1; idx < ixstart; idx++) {
            Flattop->data[idx] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)
              idx;
            Flattop->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (ixstart << 1 == n - 1) {
            Flattop->data[ixstart] = ((Rise->data[Rise->size[1] - 1] + 1.0) +
              apnd) / 2.0;
          } else {
            Flattop->data[ixstart] = (Rise->data[Rise->size[1] - 1] + 1.0) +
              (double)ixstart;
            Flattop->data[ixstart + 1] = apnd - (double)ixstart;
          }
        }
      }
    }

    if (rtIsNaN(Flattop->data[Flattop->size[1] - 1] + 1.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity_real_T(Decay, i0);
      Decay->data[0] = rtNaN;
    } else if (16384.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 0;
      emxEnsureCapacity_real_T(Decay, i0);
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 16384.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity_real_T(Decay, i0);
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      mtmp = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(16384.0 - mtmp) + 1;
      emxEnsureCapacity_real_T(Decay, i0);
      ixstart = (int)floor(16384.0 - mtmp);
      for (i0 = 0; i0 <= ixstart; i0++) {
        Decay->data[Decay->size[0] * i0] = mtmp + (double)i0;
      }
    } else {
      ndbl = floor((16384.0 - (Flattop->data[Flattop->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Flattop->data[Flattop->size[1] - 1] + 1.0) + ndbl;
      absa = fabs(Flattop->data[Flattop->size[1] - 1] + 1.0);
      if (!(absa > 16384.0)) {
        absa = 16384.0;
      }

      if (fabs(apnd - 16384.0) < 4.4408920985006262E-16 * absa) {
        ndbl++;
        apnd = 16384.0;
      } else if (apnd - 16384.0 > 0.0) {
        apnd = (Flattop->data[Flattop->size[1] - 1] + 1.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = n;
      emxEnsureCapacity_real_T(Decay, i0);
      if (n > 0) {
        Decay->data[0] = Flattop->data[Flattop->size[1] - 1] + 1.0;
        if (n > 1) {
          Decay->data[n - 1] = apnd;
          ixstart = (n - 1) / 2;
          for (idx = 1; idx < ixstart; idx++) {
            Decay->data[idx] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)idx;
            Decay->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (ixstart << 1 == n - 1) {
            Decay->data[ixstart] = ((Flattop->data[Flattop->size[1] - 1] + 1.0)
              + apnd) / 2.0;
          } else {
            Decay->data[ixstart] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)ixstart;
            Decay->data[ixstart + 1] = apnd - (double)ixstart;
          }
        }
      }
    }
  }

  emxInit_creal_T(&y_mC, 1);
  i0 = y_mC->size[0];
  y_mC->size[0] = PP->size[0];
  emxEnsureCapacity_creal_T(y_mC, i0);
  ixstart = PP->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    mtmp = 0.0 * PP->data[i0];
    d = PP->data[i0];
    if (d == 0.0) {
      b_x = mtmp / 180.0;
      mtmp = 0.0;
    } else if (mtmp == 0.0) {
      b_x = 0.0;
      mtmp = d / 180.0;
    } else {
      b_x = rtNaN;
      mtmp = d / 180.0;
    }

    y_mC->data[i0].re = 3.1415926535897931 * b_x;
    y_mC->data[i0].im = 3.1415926535897931 * mtmp;
  }

  b_exp(y_mC);
  i0 = y_mC->size[0];
  y_mC->size[0] = PA->size[0];
  emxEnsureCapacity_creal_T(y_mC, i0);
  ixstart = PA->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    y_mC->data[i0].re *= PA->data[i0];
    y_mC->data[i0].im *= PA->data[i0];
  }

  emxInit_creal_T(&u_mCal, 1);

  /*  Complex Probe measurement */
  /*  Complex Forward measurement */
  /*  Reflected */
  i0 = u_mCal->size[0];
  u_mCal->size[0] = FP->size[0];
  emxEnsureCapacity_creal_T(u_mCal, i0);
  ixstart = FP->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    mtmp = 0.0 * FP->data[i0];
    d = FP->data[i0];
    if (d == 0.0) {
      b_x = mtmp / 180.0;
      mtmp = 0.0;
    } else if (mtmp == 0.0) {
      b_x = 0.0;
      mtmp = d / 180.0;
    } else {
      b_x = rtNaN;
      mtmp = d / 180.0;
    }

    u_mCal->data[i0].re = 3.1415926535897931 * b_x;
    u_mCal->data[i0].im = 3.1415926535897931 * mtmp;
  }

  emxInit_creal_T(&unusedU0, 1);
  b_exp(u_mCal);
  i0 = unusedU0->size[0];
  unusedU0->size[0] = RP->size[0];
  emxEnsureCapacity_creal_T(unusedU0, i0);
  ixstart = RP->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    mtmp = 0.0 * RP->data[i0];
    d = RP->data[i0];
    if (d == 0.0) {
      b_x = mtmp / 180.0;
      mtmp = 0.0;
    } else if (mtmp == 0.0) {
      b_x = 0.0;
      mtmp = d / 180.0;
    } else {
      b_x = rtNaN;
      mtmp = d / 180.0;
    }

    unusedU0->data[i0].re = 3.1415926535897931 * b_x;
    unusedU0->data[i0].im = 3.1415926535897931 * mtmp;
  }

  emxInit_creal_T(&b_FA, 1);
  b_exp(unusedU0);
  i0 = b_FA->size[0];
  b_FA->size[0] = FA->size[0];
  emxEnsureCapacity_creal_T(b_FA, i0);
  ixstart = FA->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    b_FA->data[i0].re = FA->data[i0] * u_mCal->data[i0].re;
    b_FA->data[i0].im = FA->data[i0] * u_mCal->data[i0].im;
  }

  emxInit_creal_T(&b_RA, 1);
  i0 = b_RA->size[0];
  b_RA->size[0] = RA->size[0];
  emxEnsureCapacity_creal_T(b_RA, i0);
  ixstart = RA->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    b_RA->data[i0].re = RA->data[i0] * unusedU0->data[i0].re;
    b_RA->data[i0].im = RA->data[i0] * unusedU0->data[i0].im;
  }

  emxInit_creal_T(&b_y_mC, 1);
  f_calibrateData(b_FA, b_RA, cal_coeff, u_mCal, unusedU0);

  /*  The quality factor of the cavity is determined by the decay time of the */
  /*  probes signal. */
  mtmp = rt_roundd_snf(Decay->data[0] + ((double)Decay->size[1] - 1.0) / 2.0);
  if (mtmp < 32768.0) {
    if (mtmp >= -32768.0) {
      t2 = (short)mtmp;
    } else {
      t2 = MIN_int16_T;
    }
  } else if (mtmp >= 32768.0) {
    t2 = MAX_int16_T;
  } else {
    t2 = 0;
  }

  i0 = (int)rt_roundd_snf(((double)Decay->size[1] - 1.0) * 15.0 / 32.0);
  if (i0 < 32768) {
    if (i0 >= -32768) {
      i1 = (short)i0;
    } else {
      i1 = MIN_int16_T;
    }
  } else {
    i1 = MAX_int16_T;
  }

  i0 = b_y_mC->size[0];
  b_y_mC->size[0] = i1 + 1;
  emxEnsureCapacity_creal_T(b_y_mC, i0);
  ixstart = i1;
  emxFree_creal_T(&b_RA);
  emxFree_creal_T(&b_FA);
  emxFree_creal_T(&unusedU0);
  emxFree_real_T(&Decay);
  for (i0 = 0; i0 <= ixstart; i0++) {
    idx = t2 + i0;
    if (idx > 32767) {
      idx = 32767;
    } else {
      if (idx < -32768) {
        idx = -32768;
      }
    }

    b_y_mC->data[i0] = y_mC->data[idx - 1];
  }

  emxInit_real_T1(&lnA, 1);
  b_abs(b_y_mC, b_s_max);
  i0 = lnA->size[0];
  lnA->size[0] = b_s_max->size[0];
  emxEnsureCapacity_real_T1(lnA, i0);
  ixstart = b_s_max->size[0];
  emxFree_creal_T(&b_y_mC);
  for (i0 = 0; i0 < ixstart; i0++) {
    lnA->data[i0] = b_s_max->data[i0];
  }

  b_log(lnA);
  i0 = lnA->size[0];
  ndbl = 3.1415926535897931 * (F0 * 1.0E+6) * fabs(1.0 / ((lnA->data[lnA->size[0]
    - 1] - lnA->data[0]) / ((double)i0 / fs)));

  /*      figure(55) */
  /*      plot(abs(y_mC),'k') */
  /*      hold on */
  /*      plot(t2 : t2 + offset_from_end_flattop1,... */
  /*          abs(y_mC(t2 : t2 + offset_from_end_flattop1,:)),'r--') */
  f_compute_detuning(y_mC, u_mCal, fs, ndbl, dw);
  i0 = b_s_max->size[0];
  b_s_max->size[0] = Flattop->size[1];
  emxEnsureCapacity_real_T1(b_s_max, i0);
  ixstart = Flattop->size[1];
  emxFree_real_T(&lnA);
  for (i0 = 0; i0 < ixstart; i0++) {
    b_s_max->data[i0] = dw->data[(int)Flattop->data[Flattop->size[0] * i0] - 1];
  }

  i0 = ii->size[0];
  ii->size[0] = Flattop->size[1];
  emxEnsureCapacity_int32_T(ii, i0);
  ixstart = Flattop->size[1];
  for (i0 = 0; i0 < ixstart; i0++) {
    ii->data[i0] = (int)Flattop->data[Flattop->size[0] * i0];
  }

  mtmp = combineVectorElements(b_s_max) / (double)ii->size[0];
  i0 = b_s_max->size[0];
  b_s_max->size[0] = Flattop->size[1];
  emxEnsureCapacity_real_T1(b_s_max, i0);
  ixstart = Flattop->size[1];
  for (i0 = 0; i0 < ixstart; i0++) {
    b_s_max->data[i0] = PA->data[(int)Flattop->data[Flattop->size[0] * i0] - 1];
  }

  i0 = ii->size[0];
  ii->size[0] = Flattop->size[1];
  emxEnsureCapacity_int32_T(ii, i0);
  ixstart = Flattop->size[1];
  for (i0 = 0; i0 < ixstart; i0++) {
    ii->data[i0] = (int)Flattop->data[Flattop->size[0] * i0];
  }

  emxFree_real_T(&Flattop);
  b_x = combineVectorElements(b_s_max) / (double)ii->size[0];
  i0 = y_mC->size[0];
  y_mC->size[0] = Rise->size[1];
  emxEnsureCapacity_creal_T(y_mC, i0);
  ixstart = Rise->size[1];
  emxFree_real_T(&b_s_max);
  emxFree_int32_T(&ii);
  for (i0 = 0; i0 < ixstart; i0++) {
    y_mC->data[i0] = u_mCal->data[(int)Rise->data[Rise->size[0] * i0] - 1];
  }

  emxFree_creal_T(&u_mCal);
  emxFree_real_T(&Rise);
  b_abs(y_mC, dw);
  d = combineVectorElements(dw) / (double)dw->size[0];

  /* [FIT, y_mC_hat]=f_cavitySystemSimulatior(y_mC, u_mC, f0, fs, sys_hat, QL, plt, u3) */
  *classis = b_classis;
  *strengthis = b_strengthis;
  *QL = ndbl;
  *dw_stat = mtmp;
  *SP_F = d;
  *SP_P = b_x;
  emxFree_real_T(&dw);
  emxFree_creal_T(&y_mC);
}

/*
 * File trailer for f_generate_and_eval_residual.c
 *
 * [EOF]
 */
