/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_and_eval_multi_residuals.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"
#include "abs.h"
#include "mean.h"
#include "sum.h"
#include "f_GLT.h"
#include "f_compute_detuning.h"
#include "f_computeQL.h"
#include "f_calibrateData.h"
#include "exp.h"
#include "f_generate_online_parityRes2_full.h"
#include "f_generate_online_parityRes1_full.h"
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
 *                const emxArray_real_T *dw_trace_nom
 *                double DELAY
 *                double FILLING
 *                double FLATTOP
 *                const double Sigma_nom_UKF[4]
 *                const double r_mean_nom_UKF[2]
 *                const double MeasNoiseVar[4]
 *                const double ProcessVar[36]
 *                double Sigma_nom_dw
 *                const emxArray_real_T *r_PS1_nom
 *                double Sigma_nom_PS1
 *                emxArray_real_T *s_max_UKF
 *                emxArray_real_T *s_max_dw
 *                emxArray_real_T *s_max_PS1
 *                emxArray_real_T *res_PS2
 *                double *classis_UKF
 *                double *classis_PS
 *                double *classis_dw
 *                double *strengthis_UKF
 *                double *strengthis_PS
 *                double *strengthis_dw
 *                double *QL
 *                double *dw_stat
 *                double *SP_F
 *                double *SP_P
 *                double *PC
 *                double *calib_check
 *                double *dec_hq
 * Return Type  : void
 */
void f_generate_and_eval_multi_residuals(const emxArray_real_T *PA,
  emxArray_real_T *PP, const emxArray_real_T *FA, const emxArray_real_T *FP,
  const emxArray_real_T *RA, const emxArray_real_T *RP, double FS, double F0,
  const creal_T cal_coeff[4], const double tau_m[4], const double K_m[4], const
  double X0[4], double QL_nom, const emxArray_real_T *dw_trace_nom, double DELAY,
  double FILLING, double FLATTOP, const double Sigma_nom_UKF[4], const double
  r_mean_nom_UKF[2], const double MeasNoiseVar[4], const double ProcessVar[36],
  double Sigma_nom_dw, const emxArray_real_T *r_PS1_nom, double Sigma_nom_PS1,
  emxArray_real_T *s_max_UKF, emxArray_real_T *s_max_dw, emxArray_real_T
  *s_max_PS1, emxArray_real_T *res_PS2, double *classis_UKF, double *classis_PS,
  double *classis_dw, double *strengthis_UKF, double *strengthis_PS, double
  *strengthis_dw, double *QL, double *dw_stat, double *SP_F, double *SP_P,
  double *PC, double *calib_check, double *dec_hq)
{
  double fs;
  emxArray_real_T *Rise;
  emxArray_real_T *Flattop;
  emxArray_real_T *Decay;
  double x;
  double b_x;
  int i0;
  double ndbl;
  double apnd;
  double cdiff;
  double absa;
  double d;
  double absb;
  int nm1d2;
  int n;
  emxArray_real_T *b_FA;
  int idx;
  emxArray_real_T *y;
  emxArray_real_T *res_PS1;
  emxArray_creal_T *y_mC;
  emxArray_real_T *res_full_mean;
  emxArray_real_T *res_full_variance;
  emxArray_creal_T *u_mCal;
  emxArray_creal_T *r_mCal;
  emxArray_int32_T *r0;
  emxArray_boolean_T *c_x;
  emxArray_int32_T *ii;
  emxArray_real_T *r1;
  emxArray_real_T *r2;
  emxArray_creal_T *c_FA;
  emxArray_creal_T *b_RA;
  emxArray_real_T *b_res_PS1;
  emxArray_boolean_T *b_PP;
  boolean_T guard1 = false;
  int exitg1;
  double b_classis_UKF;
  double b_classis_PS;
  double b_strengthis_UKF;
  double b_strengthis_PS;
  int b_ii;
  boolean_T exitg2;
  double b_calib_check;

  /* .. */
  fs = FS * 1.0E+6;
  emxInit_real_T(&Rise, 2);
  emxInit_real_T(&Flattop, 2);
  emxInit_real_T(&Decay, 2);
  if (fs == 1.0E+6) {
    x = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6);
    b_x = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6 + FILLING * 1.0E+6 * 1.0E-6);
    if (rtIsNaN(x) || rtIsNaN(b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (b_x < x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity_real_T(Rise, i0);
    } else if ((rtIsInf(x) || rtIsInf(b_x)) && (x == b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (x == x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - x) + 1;
      emxEnsureCapacity_real_T(Rise, i0);
      nm1d2 = (int)(b_x - x);
      for (i0 = 0; i0 <= nm1d2; i0++) {
        Rise->data[Rise->size[0] * i0] = x + (double)i0;
      }
    } else {
      ndbl = floor((b_x - x) + 0.5);
      apnd = x + ndbl;
      cdiff = apnd - b_x;
      absa = fabs(x);
      absb = fabs(b_x);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = b_x;
      } else if (cdiff > 0.0) {
        apnd = x + (ndbl - 1.0);
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
        Rise->data[0] = x;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (idx = 1; idx < nm1d2; idx++) {
            Rise->data[idx] = x + (double)idx;
            Rise->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nm1d2 << 1 == n - 1) {
            Rise->data[nm1d2] = (x + apnd) / 2.0;
          } else {
            Rise->data[nm1d2] = x + (double)nm1d2;
            Rise->data[nm1d2 + 1] = apnd - (double)nm1d2;
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
      b_x = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(d - b_x) + 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      nm1d2 = (int)floor(d - b_x);
      for (i0 = 0; i0 <= nm1d2; i0++) {
        Flattop->data[Flattop->size[0] * i0] = b_x + (double)i0;
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
          nm1d2 = (n - 1) / 2;
          for (idx = 1; idx < nm1d2; idx++) {
            Flattop->data[idx] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)
              idx;
            Flattop->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nm1d2 << 1 == n - 1) {
            Flattop->data[nm1d2] = ((Rise->data[Rise->size[1] - 1] + 1.0) + apnd)
              / 2.0;
          } else {
            Flattop->data[nm1d2] = (Rise->data[Rise->size[1] - 1] + 1.0) +
              (double)nm1d2;
            Flattop->data[nm1d2 + 1] = apnd - (double)nm1d2;
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
      b_x = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(1821.0 - b_x) + 1;
      emxEnsureCapacity_real_T(Decay, i0);
      nm1d2 = (int)floor(1821.0 - b_x);
      for (i0 = 0; i0 <= nm1d2; i0++) {
        Decay->data[Decay->size[0] * i0] = b_x + (double)i0;
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
          nm1d2 = (n - 1) / 2;
          for (idx = 1; idx < nm1d2; idx++) {
            Decay->data[idx] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)idx;
            Decay->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nm1d2 << 1 == n - 1) {
            Decay->data[nm1d2] = ((Flattop->data[Flattop->size[1] - 1] + 1.0) +
                                  apnd) / 2.0;
          } else {
            Decay->data[nm1d2] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)nm1d2;
            Decay->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }
  } else {
    x = rt_roundd_snf(DELAY * fs * 1.0E-6);
    b_x = rt_roundd_snf(DELAY * fs * 1.0E-6 + FILLING * fs * 1.0E-6);
    if (rtIsNaN(x) || rtIsNaN(b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (b_x < x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity_real_T(Rise, i0);
    } else if ((rtIsInf(x) || rtIsInf(b_x)) && (x == b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity_real_T(Rise, i0);
      Rise->data[0] = rtNaN;
    } else if (x == x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - x) + 1;
      emxEnsureCapacity_real_T(Rise, i0);
      nm1d2 = (int)(b_x - x);
      for (i0 = 0; i0 <= nm1d2; i0++) {
        Rise->data[Rise->size[0] * i0] = x + (double)i0;
      }
    } else {
      ndbl = floor((b_x - x) + 0.5);
      apnd = x + ndbl;
      cdiff = apnd - b_x;
      absa = fabs(x);
      absb = fabs(b_x);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = b_x;
      } else if (cdiff > 0.0) {
        apnd = x + (ndbl - 1.0);
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
        Rise->data[0] = x;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (idx = 1; idx < nm1d2; idx++) {
            Rise->data[idx] = x + (double)idx;
            Rise->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nm1d2 << 1 == n - 1) {
            Rise->data[nm1d2] = (x + apnd) / 2.0;
          } else {
            Rise->data[nm1d2] = x + (double)nm1d2;
            Rise->data[nm1d2 + 1] = apnd - (double)nm1d2;
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
      b_x = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(d - b_x) + 1;
      emxEnsureCapacity_real_T(Flattop, i0);
      nm1d2 = (int)floor(d - b_x);
      for (i0 = 0; i0 <= nm1d2; i0++) {
        Flattop->data[Flattop->size[0] * i0] = b_x + (double)i0;
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
          nm1d2 = (n - 1) / 2;
          for (idx = 1; idx < nm1d2; idx++) {
            Flattop->data[idx] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)
              idx;
            Flattop->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nm1d2 << 1 == n - 1) {
            Flattop->data[nm1d2] = ((Rise->data[Rise->size[1] - 1] + 1.0) + apnd)
              / 2.0;
          } else {
            Flattop->data[nm1d2] = (Rise->data[Rise->size[1] - 1] + 1.0) +
              (double)nm1d2;
            Flattop->data[nm1d2 + 1] = apnd - (double)nm1d2;
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
      b_x = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(16384.0 - b_x) + 1;
      emxEnsureCapacity_real_T(Decay, i0);
      nm1d2 = (int)floor(16384.0 - b_x);
      for (i0 = 0; i0 <= nm1d2; i0++) {
        Decay->data[Decay->size[0] * i0] = b_x + (double)i0;
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
          nm1d2 = (n - 1) / 2;
          for (idx = 1; idx < nm1d2; idx++) {
            Decay->data[idx] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)idx;
            Decay->data[(n - idx) - 1] = apnd - (double)idx;
          }

          if (nm1d2 << 1 == n - 1) {
            Decay->data[nm1d2] = ((Flattop->data[Flattop->size[1] - 1] + 1.0) +
                                  apnd) / 2.0;
          } else {
            Decay->data[nm1d2] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)nm1d2;
            Decay->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }
  }

  emxInit_real_T1(&b_FA, 1);
  i0 = b_FA->size[0];
  b_FA->size[0] = Rise->size[1];
  emxEnsureCapacity_real_T1(b_FA, i0);
  nm1d2 = Rise->size[1];
  for (i0 = 0; i0 < nm1d2; i0++) {
    b_FA->data[i0] = FA->data[(int)Rise->data[Rise->size[0] * i0] - 1];
  }

  emxInit_real_T(&y, 2);
  emxInit_real_T1(&res_PS1, 1);
  emxInit_creal_T(&y_mC, 1);
  emxInit_real_T(&res_full_mean, 2);
  emxInit_real_T2(&res_full_variance, 3);
  emxInit_creal_T(&u_mCal, 1);
  emxInit_creal_T(&r_mCal, 1);
  emxInit_int32_T(&r0, 1);
  emxInit_boolean_T(&c_x, 1);
  emxInit_int32_T(&ii, 1);
  emxInit_real_T(&r1, 2);
  emxInit_real_T1(&r2, 1);
  emxInit_creal_T(&c_FA, 1);
  emxInit_creal_T(&b_RA, 1);
  emxInit_real_T(&b_res_PS1, 2);
  emxInit_boolean_T(&b_PP, 1);
  guard1 = false;
  if (mean(b_FA) > 3.0) {
    i0 = b_FA->size[0];
    b_FA->size[0] = Flattop->size[1];
    emxEnsureCapacity_real_T1(b_FA, i0);
    nm1d2 = Flattop->size[1];
    for (i0 = 0; i0 < nm1d2; i0++) {
      b_FA->data[i0] = PA->data[(int)Flattop->data[Flattop->size[0] * i0] - 1];
    }

    if (mean(b_FA) > 3.0) {
      do {
        exitg1 = 0;
        if (70 > PP->size[0]) {
          i0 = 0;
          idx = 0;
        } else {
          i0 = 69;
          idx = PP->size[0];
        }

        n = b_PP->size[0];
        b_PP->size[0] = idx - i0;
        emxEnsureCapacity_boolean_T(b_PP, n);
        nm1d2 = idx - i0;
        for (idx = 0; idx < nm1d2; idx++) {
          b_PP->data[idx] = (PP->data[i0 + idx] == 0.0);
        }

        if (sum(b_PP) > 0.0) {
          if (70 > PP->size[0]) {
            i0 = 0;
            idx = 0;
          } else {
            i0 = 69;
            idx = PP->size[0];
          }

          n = c_x->size[0];
          c_x->size[0] = idx - i0;
          emxEnsureCapacity_boolean_T(c_x, n);
          nm1d2 = idx - i0;
          for (idx = 0; idx < nm1d2; idx++) {
            c_x->data[idx] = (PP->data[i0 + idx] == 0.0);
          }

          nm1d2 = c_x->size[0];
          idx = 0;
          i0 = ii->size[0];
          ii->size[0] = c_x->size[0];
          emxEnsureCapacity_int32_T(ii, i0);
          b_ii = 1;
          exitg2 = false;
          while ((!exitg2) && (b_ii <= nm1d2)) {
            if (c_x->data[b_ii - 1]) {
              idx++;
              ii->data[idx - 1] = b_ii;
              if (idx >= nm1d2) {
                exitg2 = true;
              } else {
                b_ii++;
              }
            } else {
              b_ii++;
            }
          }

          if (c_x->size[0] == 1) {
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

          i0 = res_PS1->size[0];
          res_PS1->size[0] = ii->size[0];
          emxEnsureCapacity_real_T1(res_PS1, i0);
          nm1d2 = ii->size[0];
          for (i0 = 0; i0 < nm1d2; i0++) {
            res_PS1->data[i0] = ii->data[i0];
          }

          i0 = ii->size[0];
          ii->size[0] = res_PS1->size[0];
          emxEnsureCapacity_int32_T(ii, i0);
          nm1d2 = res_PS1->size[0];
          for (i0 = 0; i0 < nm1d2; i0++) {
            ii->data[i0] = (int)((70.0 + res_PS1->data[i0]) - 1.0);
          }

          i0 = r2->size[0];
          r2->size[0] = res_PS1->size[0];
          emxEnsureCapacity_real_T1(r2, i0);
          nm1d2 = res_PS1->size[0];
          for (i0 = 0; i0 < nm1d2; i0++) {
            r2->data[i0] = PP->data[(int)((70.0 + res_PS1->data[i0]) - 2.0) - 1];
          }

          nm1d2 = r2->size[0];
          for (i0 = 0; i0 < nm1d2; i0++) {
            PP->data[ii->data[i0] - 1] = r2->data[i0];
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      /*     %% Unscented Kalman Filter Residual Generation + GLRT Evaluation */
      c_f_generate_online_UKF_residua(PA, PP, FA, FP, RA, RP, FS, cal_coeff,
        tau_m, K_m, X0, QL_nom, MeasNoiseVar, ProcessVar, res_full_mean,
        res_full_variance);
      nm1d2 = res_full_mean->size[1];
      if (2 > nm1d2) {
        nm1d2 = 2;
      }

      if (res_full_mean->size[1] == 0) {
        n = 0;
      } else {
        n = nm1d2;
      }

      i0 = y->size[0] * y->size[1];
      y->size[0] = 2;
      y->size[1] = n;
      emxEnsureCapacity_real_T(y, i0);
      nm1d2 = n << 1;
      for (i0 = 0; i0 < nm1d2; i0++) {
        y->data[i0] = 0.0;
      }

      nm1d2 = res_full_mean->size[1];
      if (2 > nm1d2) {
        nm1d2 = 2;
      }

      if (res_full_mean->size[1] == 0) {
        n = 0;
      } else {
        n = nm1d2;
      }

      for (b_ii = 0; b_ii < n; b_ii++) {
        for (i0 = 0; i0 < 2; i0++) {
          y->data[i0 + y->size[0] * b_ii] = res_full_mean->data[i0 +
            res_full_mean->size[0] * b_ii] - r_mean_nom_UKF[i0];
        }
      }

      f_GLT(Sigma_nom_UKF, y, r1);
      i0 = s_max_UKF->size[0];
      s_max_UKF->size[0] = r1->size[1];
      emxEnsureCapacity_real_T1(s_max_UKF, i0);
      nm1d2 = r1->size[1];
      for (i0 = 0; i0 < nm1d2; i0++) {
        s_max_UKF->data[i0] = r1->data[r1->size[0] * i0];
      }

      /*     %% Parity Space Residual Genertation + GLRT Evaluation */
      c_f_generate_online_parityRes1_(PA, PP, FA, FP, RP, FS, QL_nom, res_PS1);
      c_f_generate_online_parityRes2_(PA, PP, FA, FP, RA, RP, FS, cal_coeff,
        tau_m, K_m, QL_nom, res_PS2);
      i0 = b_res_PS1->size[0] * b_res_PS1->size[1];
      b_res_PS1->size[0] = 1;
      b_res_PS1->size[1] = res_PS1->size[0];
      emxEnsureCapacity_real_T(b_res_PS1, i0);
      nm1d2 = res_PS1->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        b_res_PS1->data[b_res_PS1->size[0] * i0] = res_PS1->data[i0] -
          r_PS1_nom->data[i0];
      }

      b_f_GLT(Sigma_nom_PS1, b_res_PS1, r1);
      i0 = s_max_PS1->size[0];
      s_max_PS1->size[0] = r1->size[1];
      emxEnsureCapacity_real_T1(s_max_PS1, i0);
      nm1d2 = r1->size[1];
      for (i0 = 0; i0 < nm1d2; i0++) {
        s_max_PS1->data[i0] = r1->data[r1->size[0] * i0];
      }

      if (40 > s_max_PS1->size[0]) {
        i0 = 0;
        idx = 0;
      } else {
        i0 = 39;
        idx = s_max_PS1->size[0];
      }

      n = b_PP->size[0];
      b_PP->size[0] = idx - i0;
      emxEnsureCapacity_boolean_T(b_PP, n);
      nm1d2 = idx - i0;
      for (idx = 0; idx < nm1d2; idx++) {
        b_PP->data[idx] = (s_max_PS1->data[i0 + idx] > 10.8);
      }

      b_classis_PS = sum(b_PP);
      if (40 > s_max_PS1->size[0]) {
        i0 = 0;
        idx = 0;
      } else {
        i0 = 39;
        idx = s_max_PS1->size[0];
      }

      n = b_FA->size[0];
      b_FA->size[0] = idx - i0;
      emxEnsureCapacity_real_T1(b_FA, n);
      nm1d2 = idx - i0;
      for (idx = 0; idx < nm1d2; idx++) {
        b_FA->data[idx] = s_max_PS1->data[i0 + idx];
      }

      b_strengthis_PS = mean(b_FA);

      /*     %% Check if GLT is above a threshold. */
      if (40 > s_max_UKF->size[0]) {
        i0 = 0;
        idx = 0;
      } else {
        i0 = 39;
        idx = s_max_UKF->size[0];
      }

      n = b_PP->size[0];
      b_PP->size[0] = idx - i0;
      emxEnsureCapacity_boolean_T(b_PP, n);
      nm1d2 = idx - i0;
      for (idx = 0; idx < nm1d2; idx++) {
        b_PP->data[idx] = (s_max_UKF->data[i0 + idx] > 13.8);
      }

      b_classis_UKF = sum(b_PP);
      if (40 > s_max_UKF->size[0]) {
        i0 = 0;
        idx = 0;
      } else {
        i0 = 39;
        idx = s_max_UKF->size[0];
      }

      n = b_FA->size[0];
      b_FA->size[0] = idx - i0;
      emxEnsureCapacity_real_T1(b_FA, n);
      nm1d2 = idx - i0;
      for (idx = 0; idx < nm1d2; idx++) {
        b_FA->data[idx] = s_max_UKF->data[i0 + idx];
      }

      b_strengthis_UKF = mean(b_FA);

      /*     %% Get QL value and static detuning value */
      i0 = y_mC->size[0];
      y_mC->size[0] = PP->size[0];
      emxEnsureCapacity_creal_T(y_mC, i0);
      nm1d2 = PP->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        b_x = 0.0 * PP->data[i0];
        ndbl = PP->data[i0];
        if (ndbl == 0.0) {
          d = b_x / 180.0;
          b_x = 0.0;
        } else if (b_x == 0.0) {
          d = 0.0;
          b_x = ndbl / 180.0;
        } else {
          d = rtNaN;
          b_x = ndbl / 180.0;
        }

        y_mC->data[i0].re = 3.1415926535897931 * d;
        y_mC->data[i0].im = 3.1415926535897931 * b_x;
      }

      b_exp(y_mC);
      i0 = y_mC->size[0];
      y_mC->size[0] = PA->size[0];
      emxEnsureCapacity_creal_T(y_mC, i0);
      nm1d2 = PA->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        y_mC->data[i0].re *= PA->data[i0];
        y_mC->data[i0].im *= PA->data[i0];
      }

      /*  Complex Probe measurement */
      /*  Complex Forward measurement */
      /*  Reflected */
      i0 = u_mCal->size[0];
      u_mCal->size[0] = FP->size[0];
      emxEnsureCapacity_creal_T(u_mCal, i0);
      nm1d2 = FP->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        b_x = 0.0 * FP->data[i0];
        ndbl = FP->data[i0];
        if (ndbl == 0.0) {
          d = b_x / 180.0;
          b_x = 0.0;
        } else if (b_x == 0.0) {
          d = 0.0;
          b_x = ndbl / 180.0;
        } else {
          d = rtNaN;
          b_x = ndbl / 180.0;
        }

        u_mCal->data[i0].re = 3.1415926535897931 * d;
        u_mCal->data[i0].im = 3.1415926535897931 * b_x;
      }

      b_exp(u_mCal);
      i0 = r_mCal->size[0];
      r_mCal->size[0] = RP->size[0];
      emxEnsureCapacity_creal_T(r_mCal, i0);
      nm1d2 = RP->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        b_x = 0.0 * RP->data[i0];
        ndbl = RP->data[i0];
        if (ndbl == 0.0) {
          d = b_x / 180.0;
          b_x = 0.0;
        } else if (b_x == 0.0) {
          d = 0.0;
          b_x = ndbl / 180.0;
        } else {
          d = rtNaN;
          b_x = ndbl / 180.0;
        }

        r_mCal->data[i0].re = 3.1415926535897931 * d;
        r_mCal->data[i0].im = 3.1415926535897931 * b_x;
      }

      b_exp(r_mCal);
      i0 = c_FA->size[0];
      c_FA->size[0] = FA->size[0];
      emxEnsureCapacity_creal_T(c_FA, i0);
      nm1d2 = FA->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        c_FA->data[i0].re = FA->data[i0] * u_mCal->data[i0].re;
        c_FA->data[i0].im = FA->data[i0] * u_mCal->data[i0].im;
      }

      i0 = b_RA->size[0];
      b_RA->size[0] = RA->size[0];
      emxEnsureCapacity_creal_T(b_RA, i0);
      nm1d2 = RA->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        b_RA->data[i0].re = RA->data[i0] * r_mCal->data[i0].re;
        b_RA->data[i0].im = RA->data[i0] * r_mCal->data[i0].im;
      }

      f_calibrateData(c_FA, b_RA, cal_coeff, u_mCal, r_mCal);
      i0 = c_FA->size[0];
      c_FA->size[0] = Flattop->size[1];
      emxEnsureCapacity_creal_T(c_FA, i0);
      nm1d2 = Flattop->size[1];
      for (i0 = 0; i0 < nm1d2; i0++) {
        c_FA->data[i0].re = y_mC->data[(int)Flattop->data[Flattop->size[0] * i0]
          - 1].re - (u_mCal->data[(int)Flattop->data[Flattop->size[0] * i0] - 1]
                     .re + r_mCal->data[(int)Flattop->data[Flattop->size[0] * i0]
                     - 1].re);
        c_FA->data[i0].im = y_mC->data[(int)Flattop->data[Flattop->size[0] * i0]
          - 1].im - (u_mCal->data[(int)Flattop->data[Flattop->size[0] * i0] - 1]
                     .im + r_mCal->data[(int)Flattop->data[Flattop->size[0] * i0]
                     - 1].im);
      }

      b_abs(c_FA, r2);
      if (mean(r2) < 0.05) {
        if (25 > Decay->size[1] - 1) {
          i0 = 0;
          idx = 0;
        } else {
          i0 = 24;
          idx = Decay->size[1] - 1;
        }

        n = c_FA->size[0];
        c_FA->size[0] = idx - i0;
        emxEnsureCapacity_creal_T(c_FA, n);
        nm1d2 = idx - i0;
        for (idx = 0; idx < nm1d2; idx++) {
          c_FA->data[idx] = u_mCal->data[(int)Decay->data[i0 + idx] - 1];
        }

        b_abs(c_FA, r2);
        if (mean(r2) < 0.8) {
          b_calib_check = 1.0;
        } else {
          b_calib_check = 0.0;
        }
      } else {
        b_calib_check = 0.0;
      }

      x = f_computeQL(Rise, u_mCal, y_mC, fs, F0 * 1.0E+6);
      f_compute_detuning(y_mC, u_mCal, fs, x, res_PS1);

      /*     %% Detuning Trace Residual Generation + GLRT Evaluation */
      if (45 > res_PS1->size[0]) {
        i0 = 0;
        idx = 0;
      } else {
        i0 = 44;
        idx = res_PS1->size[0];
      }

      if (45 > dw_trace_nom->size[0]) {
        n = 0;
      } else {
        n = 44;
      }

      nm1d2 = b_res_PS1->size[0] * b_res_PS1->size[1];
      b_res_PS1->size[0] = 1;
      b_res_PS1->size[1] = idx - i0;
      emxEnsureCapacity_real_T(b_res_PS1, nm1d2);
      nm1d2 = idx - i0;
      for (idx = 0; idx < nm1d2; idx++) {
        b_res_PS1->data[b_res_PS1->size[0] * idx] = res_PS1->data[i0 + idx] -
          dw_trace_nom->data[n + idx];
      }

      b_f_GLT(Sigma_nom_dw, b_res_PS1, r1);
      i0 = s_max_dw->size[0];
      s_max_dw->size[0] = r1->size[1];
      emxEnsureCapacity_real_T1(s_max_dw, i0);
      nm1d2 = r1->size[1];
      for (i0 = 0; i0 < nm1d2; i0++) {
        s_max_dw->data[i0] = r1->data[r1->size[0] * i0];
      }

      if (40 > s_max_dw->size[0]) {
        i0 = 0;
        idx = 0;
      } else {
        i0 = 39;
        idx = s_max_dw->size[0];
      }

      n = b_PP->size[0];
      b_PP->size[0] = idx - i0;
      emxEnsureCapacity_boolean_T(b_PP, n);
      nm1d2 = idx - i0;
      for (idx = 0; idx < nm1d2; idx++) {
        b_PP->data[idx] = (s_max_dw->data[i0 + idx] > 10.8);
      }

      b_x = sum(b_PP);
      if (40 > s_max_dw->size[0]) {
        i0 = 0;
        idx = 0;
      } else {
        i0 = 39;
        idx = s_max_dw->size[0];
      }

      n = b_FA->size[0];
      b_FA->size[0] = idx - i0;
      emxEnsureCapacity_real_T1(b_FA, n);
      nm1d2 = idx - i0;
      for (idx = 0; idx < nm1d2; idx++) {
        b_FA->data[idx] = s_max_dw->data[i0 + idx];
      }

      d = mean(b_FA);

      /*     %% */
      i0 = b_FA->size[0];
      b_FA->size[0] = Flattop->size[1];
      emxEnsureCapacity_real_T1(b_FA, i0);
      nm1d2 = Flattop->size[1];
      for (i0 = 0; i0 < nm1d2; i0++) {
        b_FA->data[i0] = res_PS1->data[(int)Flattop->data[Flattop->size[0] * i0]
          - 1];
      }

      ndbl = mean(b_FA);
      i0 = b_FA->size[0];
      b_FA->size[0] = Flattop->size[1];
      emxEnsureCapacity_real_T1(b_FA, i0);
      nm1d2 = Flattop->size[1];
      for (i0 = 0; i0 < nm1d2; i0++) {
        b_FA->data[i0] = PA->data[(int)Flattop->data[Flattop->size[0] * i0] - 1];
      }

      cdiff = mean(b_FA);
      i0 = c_FA->size[0];
      c_FA->size[0] = Rise->size[1];
      emxEnsureCapacity_creal_T(c_FA, i0);
      nm1d2 = Rise->size[1];
      for (i0 = 0; i0 < nm1d2; i0++) {
        c_FA->data[i0] = u_mCal->data[(int)Rise->data[Rise->size[0] * i0] - 1];
      }

      b_abs(c_FA, r2);
      apnd = mean(r2);
      nm1d2 = u_mCal->size[0];
      i0 = c_FA->size[0];
      c_FA->size[0] = nm1d2;
      emxEnsureCapacity_creal_T(c_FA, i0);
      for (i0 = 0; i0 < nm1d2; i0++) {
        c_FA->data[i0] = u_mCal->data[i0];
      }

      b_abs(c_FA, r2);
      i0 = c_x->size[0];
      c_x->size[0] = r2->size[0];
      emxEnsureCapacity_boolean_T(c_x, i0);
      nm1d2 = r2->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        c_x->data[i0] = (r2->data[i0] < 1.5);
      }

      nm1d2 = c_x->size[0];
      idx = 0;
      i0 = ii->size[0];
      ii->size[0] = c_x->size[0];
      emxEnsureCapacity_int32_T(ii, i0);
      b_ii = 1;
      exitg2 = false;
      while ((!exitg2) && (b_ii <= nm1d2)) {
        if (c_x->data[b_ii - 1]) {
          idx++;
          ii->data[idx - 1] = b_ii;
          if (idx >= nm1d2) {
            exitg2 = true;
          } else {
            b_ii++;
          }
        } else {
          b_ii++;
        }
      }

      if (c_x->size[0] == 1) {
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

      i0 = res_PS1->size[0];
      res_PS1->size[0] = ii->size[0];
      emxEnsureCapacity_real_T1(res_PS1, i0);
      nm1d2 = ii->size[0];
      for (i0 = 0; i0 < nm1d2; i0++) {
        res_PS1->data[i0] = ii->data[i0];
      }

      n = res_PS1->size[0] - 1;
      nm1d2 = 0;
      for (idx = 0; idx <= n; idx++) {
        if (res_PS1->data[idx] > (double)(unsigned int)Rise->data[0] + 3.0) {
          nm1d2++;
        }
      }

      i0 = r0->size[0];
      r0->size[0] = nm1d2;
      emxEnsureCapacity_int32_T(r0, i0);
      nm1d2 = 0;
      for (idx = 0; idx <= n; idx++) {
        if (res_PS1->data[idx] > (double)(unsigned int)Rise->data[0] + 3.0) {
          r0->data[nm1d2] = idx + 1;
          nm1d2++;
        }
      }

      absa = res_PS1->data[r0->data[0] - 1];

      /* double(abs(u_mCal(Flattop(end-1))) < 1); */
      absb = fabs(x - QL_nom);
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    i0 = s_max_UKF->size[0];
    s_max_UKF->size[0] = PA->size[0];
    emxEnsureCapacity_real_T1(s_max_UKF, i0);
    nm1d2 = PA->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      s_max_UKF->data[i0] = rtNaN;
    }

    if (45 > dw_trace_nom->size[0]) {
      i0 = 1;
      idx = 1;
    } else {
      i0 = 45;
      idx = dw_trace_nom->size[0] + 1;
    }

    nm1d2 = idx - i0;
    i0 = s_max_dw->size[0];
    s_max_dw->size[0] = nm1d2;
    emxEnsureCapacity_real_T1(s_max_dw, i0);
    for (i0 = 0; i0 < nm1d2; i0++) {
      s_max_dw->data[i0] = rtNaN;
    }

    i0 = s_max_PS1->size[0];
    s_max_PS1->size[0] = r_PS1_nom->size[0];
    emxEnsureCapacity_real_T1(s_max_PS1, i0);
    nm1d2 = r_PS1_nom->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      s_max_PS1->data[i0] = rtNaN;
    }

    i0 = res_PS2->size[0];
    res_PS2->size[0] = PA->size[0];
    emxEnsureCapacity_real_T1(res_PS2, i0);
    nm1d2 = PA->size[0];
    for (i0 = 0; i0 < nm1d2; i0++) {
      res_PS2->data[i0] = rtNaN;
    }

    b_classis_UKF = rtNaN;
    b_classis_PS = rtNaN;
    b_x = rtNaN;
    b_strengthis_UKF = rtNaN;
    b_strengthis_PS = rtNaN;
    d = rtNaN;
    x = rtNaN;
    ndbl = rtNaN;
    apnd = rtNaN;
    cdiff = rtNaN;
    absa = rtNaN;
    b_calib_check = rtNaN;
    absb = rtNaN;
  }

  emxFree_real_T(&b_FA);
  emxFree_boolean_T(&b_PP);
  emxFree_real_T(&b_res_PS1);
  emxFree_creal_T(&b_RA);
  emxFree_creal_T(&c_FA);
  emxFree_real_T(&r2);
  emxFree_real_T(&r1);
  emxFree_int32_T(&ii);
  emxFree_boolean_T(&c_x);
  emxFree_int32_T(&r0);
  emxFree_creal_T(&r_mCal);
  emxFree_creal_T(&u_mCal);
  emxFree_real_T(&res_full_variance);
  emxFree_real_T(&res_full_mean);
  emxFree_creal_T(&y_mC);
  emxFree_real_T(&res_PS1);
  emxFree_real_T(&y);
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
  *classis_UKF = b_classis_UKF;
  *classis_PS = b_classis_PS;
  *classis_dw = b_x;
  *strengthis_UKF = b_strengthis_UKF;
  *strengthis_PS = b_strengthis_PS;
  *strengthis_dw = d;
  *QL = x;
  *dw_stat = ndbl;
  *SP_F = apnd;
  *SP_P = cdiff;
  *PC = absa;
  *calib_check = b_calib_check;
  *dec_hq = absb;
}

/*
 * File trailer for f_generate_and_eval_multi_residuals.c
 *
 * [EOF]
 */
