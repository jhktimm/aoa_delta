/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_and_eval_residual.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Aug-2019 17:51:43
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_generate_and_eval_residual_emxutil.h"
#include "combineVectorElements.h"
#include "rdivide.h"
#include "power.h"
#include "abs.h"
#include "diff.h"
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
 * Return Type  : void
 */
void f_generate_and_eval_residual(const emxArray_real_T *PA, emxArray_real_T *PP,
  const emxArray_real_T *FA, const emxArray_real_T *FP, const emxArray_real_T
  *RA, const emxArray_real_T *RP, double FS, double F0, const creal_T cal_coeff
  [4], const double tau_m[4], const double K_m[4], const double X0[4], double
  QL_nom, double DELAY, double FILLING, double FLATTOP, const double Sigma_nom[4],
  const double r_mean_nom[2], const double MeasNoiseVar[4], const double
  ProcessVar[36], emxArray_real_T *s_max, double *classis, double *strengthis,
  double *QL, double *dw_stat)
{
  int i0;
  int idx;
  emxArray_boolean_T *b_PP;
  int nx;
  emxArray_real_T *b_idx;
  emxArray_int32_T *ii;
  emxArray_real_T *b_s_max;
  int n;
  double dt;
  emxArray_boolean_T *x;
  emxArray_real_T *res_full_mean;
  emxArray_real_T *y;
  boolean_T exitg1;
  emxArray_real_T *res_full_variance;
  int b_ii;
  emxArray_real_T *Rise;
  double res_full_mean_data[2];
  double b_classis;
  double b_strengthis;
  double fs;
  emxArray_real_T *Flattop;
  double b_x;
  double ndbl;
  double apnd;
  double cdiff;
  double absa;
  double w12;
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
  emxArray_real_T *dVI;
  unsigned int varargin_1_idx_0;
  emxArray_real_T *dVQ;
  emxArray_real_T *r0;
  emxArray_real_T *dw1;
  if (40 > PP->size[0]) {
    i0 = 0;
    idx = 0;
  } else {
    i0 = 39;
    idx = PP->size[0];
  }

  emxInit_boolean_T(&b_PP, 1);
  nx = b_PP->size[0];
  b_PP->size[0] = idx - i0;
  emxEnsureCapacity_boolean_T(b_PP, nx);
  nx = idx - i0;
  for (idx = 0; idx < nx; idx++) {
    b_PP->data[idx] = (PP->data[i0 + idx] == 0.0);
  }

  emxInit_real_T(&b_idx, 1);
  emxInit_int32_T(&ii, 1);
  emxInit_real_T(&b_s_max, 1);
  if (sum(b_PP) > 0.0) {
    if (40 > PP->size[0]) {
      i0 = 0;
      idx = 0;
    } else {
      i0 = 39;
      idx = PP->size[0];
    }

    emxInit_boolean_T(&x, 1);
    nx = x->size[0];
    x->size[0] = idx - i0;
    emxEnsureCapacity_boolean_T(x, nx);
    nx = idx - i0;
    for (idx = 0; idx < nx; idx++) {
      x->data[idx] = (PP->data[i0 + idx] == 0.0);
    }

    nx = x->size[0];
    idx = 0;
    i0 = ii->size[0];
    ii->size[0] = x->size[0];
    emxEnsureCapacity_int32_T(ii, i0);
    b_ii = 1;
    exitg1 = false;
    while ((!exitg1) && (b_ii <= nx)) {
      if (x->data[b_ii - 1]) {
        idx++;
        ii->data[idx - 1] = b_ii;
        if (idx >= nx) {
          exitg1 = true;
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

    emxFree_boolean_T(&x);
    i0 = b_idx->size[0];
    b_idx->size[0] = ii->size[0];
    emxEnsureCapacity_real_T1(b_idx, i0);
    nx = ii->size[0];
    for (i0 = 0; i0 < nx; i0++) {
      b_idx->data[i0] = ii->data[i0];
    }

    i0 = ii->size[0];
    ii->size[0] = b_idx->size[0];
    emxEnsureCapacity_int32_T(ii, i0);
    nx = b_idx->size[0];
    for (i0 = 0; i0 < nx; i0++) {
      ii->data[i0] = (int)((40.0 + b_idx->data[i0]) - 1.0);
    }

    i0 = b_s_max->size[0];
    b_s_max->size[0] = b_idx->size[0];
    emxEnsureCapacity_real_T1(b_s_max, i0);
    nx = b_idx->size[0];
    for (i0 = 0; i0 < nx; i0++) {
      b_s_max->data[i0] = PP->data[(int)((40.0 + b_idx->data[i0]) - 2.0) - 1];
    }

    nx = b_s_max->size[0];
    for (i0 = 0; i0 < nx; i0++) {
      PP->data[ii->data[i0] - 1] = b_s_max->data[i0];
    }
  }

  nx = 1;
  n = PA->size[0];
  dt = PA->data[0];
  if (PA->size[0] > 1) {
    if (rtIsNaN(PA->data[0])) {
      idx = 2;
      exitg1 = false;
      while ((!exitg1) && (idx <= n)) {
        nx = idx;
        if (!rtIsNaN(PA->data[idx - 1])) {
          dt = PA->data[idx - 1];
          exitg1 = true;
        } else {
          idx++;
        }
      }
    }

    if (nx < PA->size[0]) {
      while (nx + 1 <= n) {
        if (PA->data[nx] > dt) {
          dt = PA->data[nx];
        }

        nx++;
      }
    }
  }

  emxInit_real_T1(&res_full_mean, 2);
  emxInit_real_T1(&y, 2);
  if (dt < 10.0) {
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
    nx = y->size[0] * y->size[1];
    emxFree_real_T(&res_full_variance);
    for (i0 = 0; i0 < nx; i0++) {
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
  nx = n << 1;
  for (i0 = 0; i0 < nx; i0++) {
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
    nx = res_full_mean->size[0];
    for (i0 = 0; i0 < nx; i0++) {
      res_full_mean_data[i0] = res_full_mean->data[i0 + res_full_mean->size[0] *
        b_ii];
    }

    for (i0 = 0; i0 < 2; i0++) {
      y->data[i0 + y->size[0] * b_ii] = res_full_mean_data[i0] - r_mean_nom[i0];
    }
  }

  emxFree_real_T(&res_full_mean);
  emxInit_real_T1(&Rise, 2);
  f_GLT(Sigma_nom, y, Rise);
  i0 = s_max->size[0];
  s_max->size[0] = Rise->size[1];
  emxEnsureCapacity_real_T1(s_max, i0);
  nx = Rise->size[1];
  emxFree_real_T(&y);
  for (i0 = 0; i0 < nx; i0++) {
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

  nx = b_PP->size[0];
  b_PP->size[0] = idx - i0;
  emxEnsureCapacity_boolean_T(b_PP, nx);
  nx = idx - i0;
  for (idx = 0; idx < nx; idx++) {
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

  nx = b_s_max->size[0];
  b_s_max->size[0] = idx - i0;
  emxEnsureCapacity_real_T1(b_s_max, nx);
  nx = idx - i0;
  for (idx = 0; idx < nx; idx++) {
    b_s_max->data[idx] = s_max->data[i0 + idx];
  }

  b_strengthis = b_sum(b_s_max);

  /*  Get QL value and static detuning value */
  fs = FS * 1.0E+6;
  emxInit_real_T1(&Flattop, 2);
  if (fs == 1.0E+6) {
    dt = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6);
    b_x = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6 + FILLING * 1.0E+6 * 1.0E-6);
    if (rtIsNaN(dt) || rtIsNaN(b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (b_x < dt) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity_real_T(Rise, i0);
    } else if ((rtIsInf(dt) || rtIsInf(b_x)) && (dt == b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (dt == dt) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - dt) + 1;
      emxEnsureCapacity_real_T(Rise, i0);
      nx = (int)(b_x - dt);
      for (i0 = 0; i0 <= nx; i0++) {
        Rise->data[Rise->size[0] * i0] = dt + (double)i0;
      }
    } else {
      ndbl = floor((b_x - dt) + 0.5);
      apnd = dt + ndbl;
      cdiff = apnd - b_x;
      absa = fabs(dt);
      absb = fabs(b_x);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = b_x;
      } else if (cdiff > 0.0) {
        apnd = dt + (ndbl - 1.0);
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
        Rise->data[0] = dt;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nx = (n - 1) / 2;
          for (idx = 1; idx < nx; idx++) {
            Rise->data[idx] = dt + (double)idx;
            Rise->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nx << 1 == n - 1) {
            Rise->data[nx] = (dt + apnd) / 2.0;
          } else {
            Rise->data[nx] = dt + (double)nx;
            Rise->data[nx + 1] = apnd - (double)nx;
          }
        }
      }
    }

    w12 = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * 1.0E+6
      * 1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(w12)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      Flattop->data[0] = rtNaN;
    } else if (w12 < Rise->data[Rise->size[1] - 1] + 1.0) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity_real_T(Flattop, i0);
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(w12)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == w12)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      dt = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(w12 - dt) + 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      nx = (int)floor(w12 - dt);
      for (i0 = 0; i0 <= nx; i0++) {
        Flattop->data[Flattop->size[0] * i0] = dt + (double)i0;
      }
    } else {
      ndbl = floor((w12 - (Rise->data[Rise->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + ndbl;
      cdiff = apnd - w12;
      absa = fabs(Rise->data[Rise->size[1] - 1] + 1.0);
      absb = fabs(w12);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = w12;
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
          nx = (n - 1) / 2;
          for (idx = 1; idx < nx; idx++) {
            Flattop->data[idx] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)
              idx;
            Flattop->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nx << 1 == n - 1) {
            Flattop->data[nx] = ((Rise->data[Rise->size[1] - 1] + 1.0) + apnd) /
              2.0;
          } else {
            Flattop->data[nx] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)
              nx;
            Flattop->data[nx + 1] = apnd - (double)nx;
          }
        }
      }
    }

    if (rtIsNaN(Flattop->data[Flattop->size[1] - 1] + 1.0)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (1821.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity_real_T(Rise, i0);
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 1821.0)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      dt = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)floor(1821.0 - dt) + 1;
      emxEnsureCapacity_real_T(Rise, i0);
      nx = (int)floor(1821.0 - dt);
      for (i0 = 0; i0 <= nx; i0++) {
        Rise->data[Rise->size[0] * i0] = dt + (double)i0;
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

      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = n;
      emxEnsureCapacity_real_T(Rise, i0);
      if (n > 0) {
        Rise->data[0] = Flattop->data[Flattop->size[1] - 1] + 1.0;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nx = (n - 1) / 2;
          for (idx = 1; idx < nx; idx++) {
            Rise->data[idx] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)idx;
            Rise->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nx << 1 == n - 1) {
            Rise->data[nx] = ((Flattop->data[Flattop->size[1] - 1] + 1.0) + apnd)
              / 2.0;
          } else {
            Rise->data[nx] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)nx;
            Rise->data[nx + 1] = apnd - (double)nx;
          }
        }
      }
    }
  } else {
    dt = rt_roundd_snf(DELAY * fs * 1.0E-6);
    b_x = rt_roundd_snf(DELAY * fs * 1.0E-6 + FILLING * fs * 1.0E-6);
    if (rtIsNaN(dt) || rtIsNaN(b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (b_x < dt) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity_real_T(Rise, i0);
    } else if ((rtIsInf(dt) || rtIsInf(b_x)) && (dt == b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (dt == dt) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - dt) + 1;
      emxEnsureCapacity_real_T(Rise, i0);
      nx = (int)(b_x - dt);
      for (i0 = 0; i0 <= nx; i0++) {
        Rise->data[Rise->size[0] * i0] = dt + (double)i0;
      }
    } else {
      ndbl = floor((b_x - dt) + 0.5);
      apnd = dt + ndbl;
      cdiff = apnd - b_x;
      absa = fabs(dt);
      absb = fabs(b_x);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = b_x;
      } else if (cdiff > 0.0) {
        apnd = dt + (ndbl - 1.0);
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
        Rise->data[0] = dt;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nx = (n - 1) / 2;
          for (idx = 1; idx < nx; idx++) {
            Rise->data[idx] = dt + (double)idx;
            Rise->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nx << 1 == n - 1) {
            Rise->data[nx] = (dt + apnd) / 2.0;
          } else {
            Rise->data[nx] = dt + (double)nx;
            Rise->data[nx + 1] = apnd - (double)nx;
          }
        }
      }
    }

    w12 = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * fs *
      1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(w12)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      Flattop->data[0] = rtNaN;
    } else if (w12 < Rise->data[Rise->size[1] - 1] + 1.0) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity_real_T(Flattop, i0);
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(w12)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == w12)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      dt = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(w12 - dt) + 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      nx = (int)floor(w12 - dt);
      for (i0 = 0; i0 <= nx; i0++) {
        Flattop->data[Flattop->size[0] * i0] = dt + (double)i0;
      }
    } else {
      ndbl = floor((w12 - (Rise->data[Rise->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + ndbl;
      cdiff = apnd - w12;
      absa = fabs(Rise->data[Rise->size[1] - 1] + 1.0);
      absb = fabs(w12);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = w12;
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
          nx = (n - 1) / 2;
          for (idx = 1; idx < nx; idx++) {
            Flattop->data[idx] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)
              idx;
            Flattop->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nx << 1 == n - 1) {
            Flattop->data[nx] = ((Rise->data[Rise->size[1] - 1] + 1.0) + apnd) /
              2.0;
          } else {
            Flattop->data[nx] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)
              nx;
            Flattop->data[nx + 1] = apnd - (double)nx;
          }
        }
      }
    }

    if (rtIsNaN(Flattop->data[Flattop->size[1] - 1] + 1.0)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (16384.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity_real_T(Rise, i0);
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 16384.0)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      dt = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)floor(16384.0 - dt) + 1;
      emxEnsureCapacity_real_T(Rise, i0);
      nx = (int)floor(16384.0 - dt);
      for (i0 = 0; i0 <= nx; i0++) {
        Rise->data[Rise->size[0] * i0] = dt + (double)i0;
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

      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = n;
      emxEnsureCapacity_real_T(Rise, i0);
      if (n > 0) {
        Rise->data[0] = Flattop->data[Flattop->size[1] - 1] + 1.0;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nx = (n - 1) / 2;
          for (idx = 1; idx < nx; idx++) {
            Rise->data[idx] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)idx;
            Rise->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nx << 1 == n - 1) {
            Rise->data[nx] = ((Flattop->data[Flattop->size[1] - 1] + 1.0) + apnd)
              / 2.0;
          } else {
            Rise->data[nx] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)nx;
            Rise->data[nx + 1] = apnd - (double)nx;
          }
        }
      }
    }
  }

  emxInit_creal_T(&y_mC, 1);
  i0 = y_mC->size[0];
  y_mC->size[0] = PP->size[0];
  emxEnsureCapacity_creal_T(y_mC, i0);
  nx = PP->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    dt = 0.0 * PP->data[i0];
    b_x = PP->data[i0];
    if (b_x == 0.0) {
      w12 = dt / 180.0;
      dt = 0.0;
    } else if (dt == 0.0) {
      w12 = 0.0;
      dt = b_x / 180.0;
    } else {
      w12 = rtNaN;
      dt = b_x / 180.0;
    }

    y_mC->data[i0].re = 3.1415926535897931 * w12;
    y_mC->data[i0].im = 3.1415926535897931 * dt;
  }

  b_exp(y_mC);
  i0 = y_mC->size[0];
  y_mC->size[0] = PA->size[0];
  emxEnsureCapacity_creal_T(y_mC, i0);
  nx = PA->size[0];
  for (i0 = 0; i0 < nx; i0++) {
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
  nx = FP->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    dt = 0.0 * FP->data[i0];
    b_x = FP->data[i0];
    if (b_x == 0.0) {
      w12 = dt / 180.0;
      dt = 0.0;
    } else if (dt == 0.0) {
      w12 = 0.0;
      dt = b_x / 180.0;
    } else {
      w12 = rtNaN;
      dt = b_x / 180.0;
    }

    u_mCal->data[i0].re = 3.1415926535897931 * w12;
    u_mCal->data[i0].im = 3.1415926535897931 * dt;
  }

  emxInit_creal_T(&unusedU0, 1);
  b_exp(u_mCal);
  i0 = unusedU0->size[0];
  unusedU0->size[0] = RP->size[0];
  emxEnsureCapacity_creal_T(unusedU0, i0);
  nx = RP->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    dt = 0.0 * RP->data[i0];
    b_x = RP->data[i0];
    if (b_x == 0.0) {
      w12 = dt / 180.0;
      dt = 0.0;
    } else if (dt == 0.0) {
      w12 = 0.0;
      dt = b_x / 180.0;
    } else {
      w12 = rtNaN;
      dt = b_x / 180.0;
    }

    unusedU0->data[i0].re = 3.1415926535897931 * w12;
    unusedU0->data[i0].im = 3.1415926535897931 * dt;
  }

  emxInit_creal_T(&b_FA, 1);
  b_exp(unusedU0);
  i0 = b_FA->size[0];
  b_FA->size[0] = FA->size[0];
  emxEnsureCapacity_creal_T(b_FA, i0);
  nx = FA->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    b_FA->data[i0].re = FA->data[i0] * u_mCal->data[i0].re;
    b_FA->data[i0].im = FA->data[i0] * u_mCal->data[i0].im;
  }

  emxInit_creal_T(&b_RA, 1);
  i0 = b_RA->size[0];
  b_RA->size[0] = RA->size[0];
  emxEnsureCapacity_creal_T(b_RA, i0);
  nx = RA->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    b_RA->data[i0].re = RA->data[i0] * unusedU0->data[i0].re;
    b_RA->data[i0].im = RA->data[i0] * unusedU0->data[i0].im;
  }

  emxInit_creal_T(&b_y_mC, 1);
  f_calibrateData(b_FA, b_RA, cal_coeff, u_mCal, unusedU0);

  /*  The quality factor of the cavity is determined by the decay time of the */
  /*  probes signal. */
  dt = rt_roundd_snf(Rise->data[0] + ((double)Rise->size[1] - 1.0) / 2.0);
  if (dt < 32768.0) {
    if (dt >= -32768.0) {
      t2 = (short)dt;
    } else {
      t2 = MIN_int16_T;
    }
  } else if (dt >= 32768.0) {
    t2 = MAX_int16_T;
  } else {
    t2 = 0;
  }

  i0 = (int)rt_roundd_snf(((double)Rise->size[1] - 1.0) * 15.0 / 32.0);
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
  nx = i1;
  emxFree_creal_T(&b_RA);
  emxFree_creal_T(&b_FA);
  emxFree_creal_T(&unusedU0);
  emxFree_real_T(&Rise);
  for (i0 = 0; i0 <= nx; i0++) {
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

  emxInit_real_T(&lnA, 1);
  b_abs(b_y_mC, b_s_max);
  i0 = lnA->size[0];
  lnA->size[0] = b_s_max->size[0];
  emxEnsureCapacity_real_T1(lnA, i0);
  nx = b_s_max->size[0];
  emxFree_creal_T(&b_y_mC);
  for (i0 = 0; i0 < nx; i0++) {
    lnA->data[i0] = b_s_max->data[i0];
  }

  emxInit_real_T(&dVI, 1);
  b_log(lnA);
  i0 = lnA->size[0];
  b_x = 3.1415926535897931 * (F0 * 1.0E+6) * fabs(1.0 / ((lnA->data[lnA->size[0]
    - 1] - lnA->data[0]) / ((double)i0 / fs)));

  /*      figure(55) */
  /*      plot(abs(y_mC),'k') */
  /*      hold on */
  /*      plot(t2 : t2 + offset_from_end_flattop1,... */
  /*          abs(y_mC(t2 : t2 + offset_from_end_flattop1,:)),'r--') */
  /* -------- Calculate w12 with the decay time-------------- */
  w12 = 4.0840704496667309E+9 / b_x;
  varargin_1_idx_0 = (unsigned int)y_mC->size[0];
  dt = 1.0 / fs;
  i0 = dVI->size[0];
  dVI->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(dVI, i0);
  nx = y_mC->size[0];
  emxFree_real_T(&lnA);
  for (i0 = 0; i0 < nx; i0++) {
    dVI->data[i0] = 0.0;
  }

  emxInit_real_T(&dVQ, 1);
  i0 = dVQ->size[0];
  dVQ->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(dVQ, i0);
  nx = y_mC->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    dVQ->data[i0] = 0.0;
  }

  nx = y_mC->size[0];
  i0 = b_s_max->size[0];
  b_s_max->size[0] = nx;
  emxEnsureCapacity_real_T1(b_s_max, i0);
  for (i0 = 0; i0 < nx; i0++) {
    b_s_max->data[i0] = y_mC->data[i0].re;
  }

  diff(b_s_max, b_idx);
  dVI->data[0] = 0.0;
  nx = b_idx->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    dVI->data[i0 + 1] = b_idx->data[i0] / dt;
  }

  nx = y_mC->size[0];
  i0 = b_s_max->size[0];
  b_s_max->size[0] = nx;
  emxEnsureCapacity_real_T1(b_s_max, i0);
  for (i0 = 0; i0 < nx; i0++) {
    b_s_max->data[i0] = y_mC->data[i0].im;
  }

  diff(b_s_max, b_idx);
  dVQ->data[0] = 0.0;
  nx = b_idx->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    dVQ->data[i0 + 1] = b_idx->data[i0] / dt;
  }

  emxInit_real_T1(&r0, 2);

  /* if sum(sum(isnan(dVI)))> 0 || sum(sum(isnan(dVQ)))>0 */
  /*     warning('the values of dw could not be calculated correctly!') */
  /* end */
  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = (int)varargin_1_idx_0;
  r0->size[1] = 1;
  emxEnsureCapacity_real_T(r0, i0);
  nx = (int)varargin_1_idx_0;
  for (i0 = 0; i0 < nx; i0++) {
    r0->data[i0] = 2.0 * w12;
  }

  b_abs(y_mC, b_s_max);
  power(b_s_max, b_idx);
  i0 = b_s_max->size[0];
  b_s_max->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(b_s_max, i0);
  nx = y_mC->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    b_s_max->data[i0] = y_mC->data[i0].re * (dVQ->data[i0] - r0->data[i0] *
      u_mCal->data[i0].im);
  }

  emxInit_real_T(&dw1, 1);
  rdivide(b_s_max, b_idx, dw1);
  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = (int)varargin_1_idx_0;
  r0->size[1] = 1;
  emxEnsureCapacity_real_T(r0, i0);
  nx = (int)varargin_1_idx_0;
  for (i0 = 0; i0 < nx; i0++) {
    r0->data[i0] = 2.0 * w12;
  }

  b_abs(y_mC, b_s_max);
  power(b_s_max, b_idx);
  i0 = b_s_max->size[0];
  b_s_max->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(b_s_max, i0);
  nx = y_mC->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    b_s_max->data[i0] = y_mC->data[i0].im * (r0->data[i0] * u_mCal->data[i0].re
      - dVI->data[i0]);
  }

  emxFree_real_T(&r0);
  emxFree_real_T(&dVI);
  emxFree_creal_T(&u_mCal);
  rdivide(b_s_max, b_idx, dVQ);
  i0 = b_idx->size[0];
  b_idx->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T1(b_idx, i0);
  nx = y_mC->size[0];
  for (i0 = 0; i0 < nx; i0++) {
    b_idx->data[i0] = 0.0;
  }

  nx = dw1->size[0] - 1;
  emxFree_creal_T(&y_mC);
  for (i0 = 0; i0 <= nx; i0++) {
    b_idx->data[i0] = dw1->data[i0] + dVQ->data[i0];
  }

  emxFree_real_T(&dw1);
  emxFree_real_T(&dVQ);

  /* -----------Plot-------------- */
  /*      figure(555) */
  /*      hold on */
  /*      plot([1:1:length(dw)-1]*1e-6,dw(1:end-1)) */
  /*      xlabel('Time') */
  /*      ylabel('\Delta\omega') */
  /*       */
  i0 = b_s_max->size[0];
  b_s_max->size[0] = Flattop->size[1];
  emxEnsureCapacity_real_T1(b_s_max, i0);
  nx = Flattop->size[1];
  for (i0 = 0; i0 < nx; i0++) {
    b_s_max->data[i0] = b_idx->data[(int)Flattop->data[Flattop->size[0] * i0] -
      1];
  }

  emxFree_real_T(&b_idx);
  i0 = ii->size[0];
  ii->size[0] = Flattop->size[1];
  emxEnsureCapacity_int32_T(ii, i0);
  nx = Flattop->size[1];
  for (i0 = 0; i0 < nx; i0++) {
    ii->data[i0] = (int)Flattop->data[Flattop->size[0] * i0];
  }

  emxFree_real_T(&Flattop);
  dt = combineVectorElements(b_s_max) / (double)ii->size[0];
  *classis = b_classis;
  *strengthis = b_strengthis;
  *QL = b_x;
  *dw_stat = dt;
  emxFree_real_T(&b_s_max);
  emxFree_int32_T(&ii);
}

/*
 * File trailer for f_generate_and_eval_residual.c
 *
 * [EOF]
 */
