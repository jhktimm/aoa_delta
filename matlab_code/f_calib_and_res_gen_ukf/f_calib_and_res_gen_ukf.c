/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_calib_and_res_gen_ukf.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "f_calib_and_res_gen_ukf_emxutil.h"
#include "sum.h"
#include "mldivide.h"
#include "combine_vector_elements.h"
#include "f_compute_ukf_residual.h"
#include "log.h"
#include "abs.h"
#include "exp.h"
#include "f_get_calCoeff_codegen.h"
#include "f_calib_and_res_gen_ukf_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *PA
 *                const emxArray_real_T *PP
 *                const emxArray_real_T *FA
 *                const emxArray_real_T *FP
 *                const emxArray_real_T *RA
 *                const emxArray_real_T *RP
 *                double FS
 *                double F0
 *                const double tau_m[4]
 *                const double K_m[4]
 *                const double X0[4]
 *                double DELAY
 *                double FILLING
 *                double FLATTOP
 *                double residual_ukf[6]
 *                double residual_ukf_mean[6]
 *                double residual_ukf_Variance[12]
 *                creal_T cal_Coeff[4]
 * Return Type  : void
 */
void f_calib_and_res_gen_ukf(const emxArray_real_T *PA, const emxArray_real_T
  *PP, const emxArray_real_T *FA, const emxArray_real_T *FP, const
  emxArray_real_T *RA, const emxArray_real_T *RP, double FS, double F0, const
  double tau_m[4], const double K_m[4], const double X0[4], double DELAY, double
  FILLING, double FLATTOP, double residual_ukf[6], double residual_ukf_mean[6],
  double residual_ukf_Variance[12], creal_T cal_Coeff[4])
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
  int loop_ub;
  int n;
  emxArray_creal_T *y_mC;
  int nm1d2;
  int k;
  emxArray_creal_T *u_mC;
  emxArray_creal_T *r_mC;
  emxArray_creal_T *b_y_mC;
  short t2;
  short i1;
  emxArray_creal_T *u_mCal;
  int i2;
  emxArray_real_T *lnA;
  emxArray_int32_T *r0;
  emxArray_creal_T *b_u_mC;
  double dv0[6];
  emxArray_real_T *c_y_mC;
  emxArray_real_T *b_u_mCal;
  emxArray_real_T *res_full_mean;
  emxArray_real_T *unusedU1;
  emxArray_real_T *res_full_xi;
  emxArray_real_T *res_full_Info;
  emxArray_real_T *c_x;
  emxArray_real_T *b_Rise;
  double A[2];
  emxArray_real_T *b_Flattop;
  double b_A[2];
  double c_A[2];
  emxArray_real_T *b_res_full_Info;
  emxArray_real_T *c_res_full_Info;
  double d_x[4];
  static const double dv1[4] = { 1.0, 0.0, 0.0, 1.0 };

  emxArray_real_T *d_res_full_Info;
  emxArray_real_T *e_res_full_Info;
  emxArray_real_T *b_res_full_xi;
  double a[4];
  emxArray_real_T *f_res_full_Info;
  emxArray_real_T *c_res_full_xi;
  double b_a[4];
  emxArray_real_T *g_res_full_Info;
  emxArray_real_T *d_res_full_xi;
  double c_a[4];
  double d_a[2];
  double e_a[2];
  double f_a[2];
  (void)F0;
  //~ f_get_calCoeff_codegen(PA, PP, FA, FP, RA, RP, DELAY, FILLING, FLATTOP, FS,
    //~ cal_Coeff);

  /*  inputs: */
  /*  Probe_Ampl: Amplitude of Probe measurement */
  /*  Probe_Phase: Phase of Probe measurement */
  /*  Forw_Ampl: Amplitude of Forward measurement */
  /*  Forw_Phase: Phase of Forward measurement */
  /*  Refl_Ampl: Amplitude of Reflected measurement */
  /*  Refl_Probe: Phase of Reflected measurement */
  /*  fs: Sampling frequency, for online Data 9MHz, DAQ data 1MHz - can be read */
  /*  from DOOCS property */
  /*  f0: Resonance frequency, should be 1.3GHz - should be read */
  /*  from DOOCS property */
  /*  cal_coeff: coefficients necessary for the calibration of the signals, */
  /*  obtained from the function f_get_calCoeff */
  /*  Rise: Sample numbers that belong to the rise (filling) of the Pulse - should be read */
  /*  from DOOCS property */
  /*  Flattop: Samople numbers that belong to the flattop of the pulse - should be read */
  /*  from DOOCS property */
  /*  Decay: Sample numbers that belong to the decay of the pulse  - should be read */
  /*  from DOOCS property */
  /* #cogegen */
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
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (b_x < x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
    } else if ((rtIsInf(x) || rtIsInf(b_x)) && (x == b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (x == x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - x) + 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      loop_ub = (int)(b_x - x);
      for (i0 = 0; i0 <= loop_ub; i0++) {
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
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      if (n > 0) {
        Rise->data[0] = x;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Rise->data[k] = x + (double)k;
            Rise->data[(n - k) - 1] = apnd - (double)k;
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
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (d < Rise->data[Rise->size[1] - 1] + 1.0) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(d)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      x = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(d - x) + 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      loop_ub = (int)floor(d - x);
      for (i0 = 0; i0 <= loop_ub; i0++) {
        Flattop->data[Flattop->size[0] * i0] = x + (double)i0;
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
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      if (n > 0) {
        Flattop->data[0] = Rise->data[Rise->size[1] - 1] + 1.0;
        if (n > 1) {
          Flattop->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Flattop->data[k] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)k;
            Flattop->data[(n - k) - 1] = apnd - (double)k;
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
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (1821.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 1821.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      x = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(1821.0 - x) + 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      loop_ub = (int)floor(1821.0 - x);
      for (i0 = 0; i0 <= loop_ub; i0++) {
        Decay->data[Decay->size[0] * i0] = x + (double)i0;
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
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      if (n > 0) {
        Decay->data[0] = Flattop->data[Flattop->size[1] - 1] + 1.0;
        if (n > 1) {
          Decay->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Decay->data[k] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)k;
            Decay->data[(n - k) - 1] = apnd - (double)k;
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
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (b_x < x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
    } else if ((rtIsInf(x) || rtIsInf(b_x)) && (x == b_x)) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (x == x) {
      i0 = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - x) + 1;
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      loop_ub = (int)(b_x - x);
      for (i0 = 0; i0 <= loop_ub; i0++) {
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
      emxEnsureCapacity((emxArray__common *)Rise, i0, sizeof(double));
      if (n > 0) {
        Rise->data[0] = x;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Rise->data[k] = x + (double)k;
            Rise->data[(n - k) - 1] = apnd - (double)k;
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
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (d < Rise->data[Rise->size[1] - 1] + 1.0) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(d)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == d)) {
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      x = Rise->data[Rise->size[1] - 1] + 1.0;
      i0 = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(d - x) + 1;
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      loop_ub = (int)floor(d - x);
      for (i0 = 0; i0 <= loop_ub; i0++) {
        Flattop->data[Flattop->size[0] * i0] = x + (double)i0;
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
      emxEnsureCapacity((emxArray__common *)Flattop, i0, sizeof(double));
      if (n > 0) {
        Flattop->data[0] = Rise->data[Rise->size[1] - 1] + 1.0;
        if (n > 1) {
          Flattop->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Flattop->data[k] = (Rise->data[Rise->size[1] - 1] + 1.0) + (double)k;
            Flattop->data[(n - k) - 1] = apnd - (double)k;
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
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (16384.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 16384.0)) {
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      x = Flattop->data[Flattop->size[1] - 1] + 1.0;
      i0 = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(16384.0 - x) + 1;
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      loop_ub = (int)floor(16384.0 - x);
      for (i0 = 0; i0 <= loop_ub; i0++) {
        Decay->data[Decay->size[0] * i0] = x + (double)i0;
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
      emxEnsureCapacity((emxArray__common *)Decay, i0, sizeof(double));
      if (n > 0) {
        Decay->data[0] = Flattop->data[Flattop->size[1] - 1] + 1.0;
        if (n > 1) {
          Decay->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Decay->data[k] = (Flattop->data[Flattop->size[1] - 1] + 1.0) +
              (double)k;
            Decay->data[(n - k) - 1] = apnd - (double)k;
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

  emxInit_creal_T(&y_mC, 1);
  i0 = y_mC->size[0];
  y_mC->size[0] = PP->size[0];
  emxEnsureCapacity((emxArray__common *)y_mC, i0, sizeof(creal_T));
  loop_ub = PP->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    x = 0.0 * PP->data[i0];
    d = PP->data[i0];
    if (d == 0.0) {
      b_x = x / 180.0;
      x = 0.0;
    } else if (x == 0.0) {
      b_x = 0.0;
      x = d / 180.0;
    } else {
      b_x = x / 180.0;
      x = d / 180.0;
    }

    y_mC->data[i0].re = 3.1415926535897931 * b_x;
    y_mC->data[i0].im = 3.1415926535897931 * x;
  }

  b_exp(y_mC);
  i0 = y_mC->size[0];
  y_mC->size[0] = PA->size[0];
  emxEnsureCapacity((emxArray__common *)y_mC, i0, sizeof(creal_T));
  loop_ub = PA->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    y_mC->data[i0].re *= PA->data[i0];
    y_mC->data[i0].im *= PA->data[i0];
  }

  emxInit_creal_T(&u_mC, 1);

  /*  Complex Probe measurement */
  i0 = u_mC->size[0];
  u_mC->size[0] = FP->size[0];
  emxEnsureCapacity((emxArray__common *)u_mC, i0, sizeof(creal_T));
  loop_ub = FP->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    x = 0.0 * FP->data[i0];
    d = FP->data[i0];
    if (d == 0.0) {
      b_x = x / 180.0;
      x = 0.0;
    } else if (x == 0.0) {
      b_x = 0.0;
      x = d / 180.0;
    } else {
      b_x = x / 180.0;
      x = d / 180.0;
    }

    u_mC->data[i0].re = 3.1415926535897931 * b_x;
    u_mC->data[i0].im = 3.1415926535897931 * x;
  }

  b_exp(u_mC);
  i0 = u_mC->size[0];
  u_mC->size[0] = FA->size[0];
  emxEnsureCapacity((emxArray__common *)u_mC, i0, sizeof(creal_T));
  loop_ub = FA->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    u_mC->data[i0].re *= FA->data[i0];
    u_mC->data[i0].im *= FA->data[i0];
  }

  emxInit_creal_T(&r_mC, 1);

  /*  Complex Forward measurement */
  i0 = r_mC->size[0];
  r_mC->size[0] = RP->size[0];
  emxEnsureCapacity((emxArray__common *)r_mC, i0, sizeof(creal_T));
  loop_ub = RP->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    x = 0.0 * RP->data[i0];
    d = RP->data[i0];
    if (d == 0.0) {
      b_x = x / 180.0;
      x = 0.0;
    } else if (x == 0.0) {
      b_x = 0.0;
      x = d / 180.0;
    } else {
      b_x = x / 180.0;
      x = d / 180.0;
    }

    r_mC->data[i0].re = 3.1415926535897931 * b_x;
    r_mC->data[i0].im = 3.1415926535897931 * x;
  }

  b_exp(r_mC);
  i0 = r_mC->size[0];
  r_mC->size[0] = RA->size[0];
  emxEnsureCapacity((emxArray__common *)r_mC, i0, sizeof(creal_T));
  loop_ub = RA->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r_mC->data[i0].re *= RA->data[i0];
    r_mC->data[i0].im *= RA->data[i0];
  }

  emxInit_creal_T(&b_y_mC, 1);

  /*  Reflected */
  /*  The quality factor of the cavity is determined by the decay time of the */
  /*  probes signal. */
  x = rt_roundd_snf(Decay->data[0] + ((double)Decay->size[1] - 1.0) / 2.0);
  if (x < 32768.0) {
    if (x >= -32768.0) {
      t2 = (short)x;
    } else {
      t2 = MIN_int16_T;
    }
  } else if (x >= 32768.0) {
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
  emxEnsureCapacity((emxArray__common *)b_y_mC, i0, sizeof(creal_T));
  loop_ub = i1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    i2 = t2 + i0;
    if (i2 > 32767) {
      i2 = 32767;
    } else {
      if (i2 < -32768) {
        i2 = -32768;
      }
    }

    b_y_mC->data[i0] = y_mC->data[i2 - 1];
  }

  emxInit_creal_T(&u_mCal, 1);
  emxInit_real_T2(&lnA, 1);
  b_abs(b_y_mC, lnA);
  b_log(lnA);

  /*      figure(55) */
  /*      plot(abs(y_mC),'k') */
  /*      hold on */
  /*      plot(t2 : t2 + offset_from_end_flattop1,... */
  /*          abs(y_mC(t2 : t2 + offset_from_end_flattop1,:)),'r--') */
  /*  Online residual generation */
  /* Initialize */
  i0 = u_mCal->size[0];
  u_mCal->size[0] = u_mC->size[0];
  emxEnsureCapacity((emxArray__common *)u_mCal, i0, sizeof(creal_T));
  loop_ub = u_mC->size[0];
  emxFree_creal_T(&b_y_mC);
  for (i0 = 0; i0 < loop_ub; i0++) {
    u_mCal->data[i0].re = 0.0;
    u_mCal->data[i0].im = 0.0;
  }

  emxInit_int32_T(&r0, 1);

  /*  compute calibrated FORW and REFL signal */
  loop_ub = u_mCal->size[0];
  i0 = r0->size[0];
  r0->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r0, i0, sizeof(int));
  for (i0 = 0; i0 < loop_ub; i0++) {
    r0->data[i0] = i0;
  }

  emxInit_creal_T1(&b_u_mC, 2);
  loop_ub = u_mC->size[0];
  i0 = b_u_mC->size[0] * b_u_mC->size[1];
  b_u_mC->size[0] = 1;
  b_u_mC->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_u_mC, i0, sizeof(creal_T));
  for (i0 = 0; i0 < loop_ub; i0++) {
    x = u_mC->data[i0].re * cal_Coeff[0].re - u_mC->data[i0].im * cal_Coeff[0].
      im;
    b_x = u_mC->data[i0].re * cal_Coeff[0].im + u_mC->data[i0].im * cal_Coeff[0]
      .re;
    d = r_mC->data[i0].re * cal_Coeff[1].re - r_mC->data[i0].im * cal_Coeff[1].
      im;
    ndbl = r_mC->data[i0].re * cal_Coeff[1].im + r_mC->data[i0].im * cal_Coeff[1]
      .re;
    b_u_mC->data[b_u_mC->size[0] * i0].re = x + d;
    b_u_mC->data[b_u_mC->size[0] * i0].im = b_x + ndbl;
  }

  emxFree_creal_T(&r_mC);
  emxFree_creal_T(&u_mC);
  nm1d2 = r0->size[0];
  for (i0 = 0; i0 < nm1d2; i0++) {
    u_mCal->data[r0->data[i0]] = b_u_mC->data[i0];
  }

  emxFree_creal_T(&b_u_mC);
  emxFree_int32_T(&r0);

  /* ------------Plot Before and After Calibration----------------------------- */
  /*  while(0) */
  /*  figure(22) */
  /*  subplot(2,1,1) */
  /*  plot(abs(Forw(:,1)+Refl(:,1)),'r--') */
  /*  hold on */
  /*  plot(abs(Probe(:,1)),'k--') */
  /*  plot(abs(Forw(:,1)),'g') */
  /*  plot(abs(Refl(:,1)), 'b') */
  /*  legend('Virtual Probe', 'Probe', 'Forward', 'Reflected') */
  /*  ylabel('After Calbiration') */
  /*   */
  /*  subplot(2,1,2) */
  /*  plot(abs(Forw_cal(:,1)+Refl_cal(:,1)),'r--') */
  /*  hold on */
  /*  plot(abs(Probe(:,1)),'k--') */
  /*  plot(abs(Forw_cal(:,1)),'g') */
  /*  plot(abs(Refl_cal(:,1)), 'b') */
  /*  legend('Virtual Probe', 'Probe', 'Forward', 'Reflected') */
  /*  ylabel('After Calbiration') */
  /*  end */
  memset(&residual_ukf_Variance[0], 0, 12U * sizeof(double));
  i0 = lnA->size[0];
  dv0[0] = 0.0;
  dv0[1] = 0.0;
  for (nm1d2 = 0; nm1d2 < 4; nm1d2++) {
    dv0[nm1d2 + 2] = X0[nm1d2];
  }

  emxInit_real_T(&c_y_mC, 2);
  i2 = c_y_mC->size[0] * c_y_mC->size[1];
  c_y_mC->size[0] = 2;
  c_y_mC->size[1] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)c_y_mC, i2, sizeof(double));
  loop_ub = y_mC->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    c_y_mC->data[c_y_mC->size[0] * i2] = y_mC->data[i2].re;
  }

  loop_ub = y_mC->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    c_y_mC->data[1 + c_y_mC->size[0] * i2] = y_mC->data[i2].im;
  }

  emxFree_creal_T(&y_mC);
  emxInit_real_T(&b_u_mCal, 2);
  i2 = b_u_mCal->size[0] * b_u_mCal->size[1];
  b_u_mCal->size[0] = 2;
  b_u_mCal->size[1] = u_mCal->size[0];
  emxEnsureCapacity((emxArray__common *)b_u_mCal, i2, sizeof(double));
  loop_ub = u_mCal->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_u_mCal->data[b_u_mCal->size[0] * i2] = u_mCal->data[i2].re;
  }

  loop_ub = u_mCal->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_u_mCal->data[1 + b_u_mCal->size[0] * i2] = u_mCal->data[i2].im;
  }

  emxFree_creal_T(&u_mCal);
  emxInit_real_T(&res_full_mean, 2);
  emxInit_real_T1(&unusedU1, 3);
  emxInit_real_T(&res_full_xi, 2);
  emxInit_real_T1(&res_full_Info, 3);
  f_compute_ukf_residual(dv0, c_y_mC, b_u_mCal, fs, 4.0840704496667309E+9 * fabs
    (1.0 / ((lnA->data[lnA->size[0] - 1] - lnA->data[0]) / ((double)i0 / fs))),
    tau_m, K_m, res_full_mean, unusedU1, res_full_xi, res_full_Info);

//~ printf("res_full_mean->size[0]: %i\n",res_full_mean->size[0]);
//~ printf("res_full_mean->data[0]: %f\n",res_full_mean->data[0]);
//~ printf("res_full_mean->data[1]: %f\n",res_full_mean->data[1]);
//~ printf("res_full_mean->data[2]: %f\n",res_full_mean->data[2]);
//~ printf("res_full_mean->data[3]: %f\n",res_full_mean->data[3]);
//~ printf("res_full_mean->data[4]: %f\n",res_full_mean->data[4]);
//~ printf("res_full_mean->data[5]: %f\n",res_full_mean->data[5]);
//~ printf("res_full_xi->size[0]: %i\n",res_full_xi->size[0]);
//~ printf("res_full_xi->data[0]: %f\n",res_full_xi->data[0]);
//~ printf("res_full_xi->data[1]: %f\n",res_full_xi->data[1]);
//~ printf("res_full_xi->data[2]: %f\n",res_full_xi->data[2]);
//~ printf("res_full_xi->data[3]: %f\n",res_full_xi->data[3]);
//~ printf("res_full_xi->data[4]: %f\n",res_full_xi->data[4]);
//~ printf("res_full_xi->data[5]: %f\n",res_full_xi->data[5]);

//~ printf("res_full_info->size[0]: %i\n",res_full_Info->size[0]);
//~ printf("res_full_info->data[0]: %f\n",res_full_Info->data[0]);
//~ printf("res_full_info->data[1]: %f\n",res_full_Info->data[1]);
//~ printf("res_full_info->data[2]: %f\n",res_full_Info->data[2]);
//~ printf("res_full_info->data[3]: %f\n",res_full_Info->data[3]);
//~ printf("res_full_info->data[4]: %f\n",res_full_Info->data[4]);
//~ printf("res_full_info->data[5]: %f\n",res_full_Info->data[5]);



  /*  figure(98) */
  /*  plot(res_full_mean(1,1:9:end),'k.', 'MarkerSize', 8) */
  /*  hold on */
  /*  plot(res_full_mean(2,1:9:end),'g.', 'MarkerSize', 8) */
  /*  xlabel('Samples') */
  /*  ylabel('Residual') */
  /*  legend('I', 'Q') */
  /*  axis tight */
  /*  ylim([-0.025,0.025]) */
  /*  ax= gca; */
  /*  ax.FontName = 'Calibri'; */
  /*  ax.FontSize = 20; */
  /*  set(gcf,'Color', 'w') */
  /*  Arithmetic mean of the mean */
  emxFree_real_T(&b_u_mCal);
  emxFree_real_T(&c_y_mC);
  emxFree_real_T(&lnA);
  emxFree_real_T(&unusedU1);
  if (1 > Decay->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = Decay->size[1] - 1;
  }

  emxInit_real_T(&c_x, 2);
  i0 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 2;
  c_x->size[1] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)c_x, i0, sizeof(double));
  n = Rise->size[1];
  for (i0 = 0; i0 < n; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      c_x->data[i2 + c_x->size[0] * i0] = res_full_mean->data[i2 +
        res_full_mean->size[0] * ((int)Rise->data[Rise->size[0] * i0] - 1)];
    }
  }

  emxInit_real_T2(&b_Rise, 1);
  combine_vector_elements(c_x, A);
  i0 = b_Rise->size[0];
  b_Rise->size[0] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)b_Rise, i0, sizeof(double));
  n = Rise->size[1];
  for (i0 = 0; i0 < n; i0++) {
    b_Rise->data[i0] = Rise->data[Rise->size[0] * i0];
  }

  k = b_Rise->size[0];
  i0 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 2;
  c_x->size[1] = Flattop->size[1];
  emxEnsureCapacity((emxArray__common *)c_x, i0, sizeof(double));
  n = Flattop->size[1];
  emxFree_real_T(&b_Rise);
  for (i0 = 0; i0 < n; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      c_x->data[i2 + c_x->size[0] * i0] = res_full_mean->data[i2 +
        res_full_mean->size[0] * ((int)Flattop->data[Flattop->size[0] * i0] - 1)];
    }
  }

  emxInit_real_T2(&b_Flattop, 1);
  combine_vector_elements(c_x, b_A);
  i0 = b_Flattop->size[0];
  b_Flattop->size[0] = Flattop->size[1];
  emxEnsureCapacity((emxArray__common *)b_Flattop, i0, sizeof(double));
  n = Flattop->size[1];
  for (i0 = 0; i0 < n; i0++) {
    b_Flattop->data[i0] = Flattop->data[Flattop->size[0] * i0];
  }

  nm1d2 = b_Flattop->size[0];
  i0 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 2;
  c_x->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)c_x, i0, sizeof(double));
  emxFree_real_T(&b_Flattop);
  for (i0 = 0; i0 < loop_ub; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      c_x->data[i2 + c_x->size[0] * i0] = res_full_mean->data[i2 +
        res_full_mean->size[0] * ((int)Decay->data[i0] - 1)];
    }
  }

  emxFree_real_T(&res_full_mean);
  combine_vector_elements(c_x, c_A);
  emxFree_real_T(&c_x);
  for (i0 = 0; i0 < 2; i0++) {
    residual_ukf[i0] = A[i0] / (double)k;
    residual_ukf[2 + i0] = b_A[i0] / (double)nm1d2;
    residual_ukf[4 + i0] = c_A[i0] / (double)loop_ub;
  }

  emxInit_real_T1(&b_res_full_Info, 3);

  /*  Equality Node: Taking the variance into consideration */
  i0 = b_res_full_Info->size[0] * b_res_full_Info->size[1] *
    b_res_full_Info->size[2];
  b_res_full_Info->size[0] = Rise->size[1];
  b_res_full_Info->size[1] = 2;
  b_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)b_res_full_Info, i0, sizeof(double));
  for (i0 = 0; i0 < 2; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      loop_ub = Rise->size[1];
      for (k = 0; k < loop_ub; k++) {
        b_res_full_Info->data[(k + b_res_full_Info->size[0] * i2) +
          b_res_full_Info->size[0] * b_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Rise->data[Rise->size[0] * k] +
          res_full_Info->size[0] * i2) + res_full_Info->size[0] *
          res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  emxInit_real_T1(&c_res_full_Info, 3);
  sum(b_res_full_Info, d_x);
  c_mldivide(d_x, dv1, *(double (*)[4])&residual_ukf_Variance[0]);
  i0 = c_res_full_Info->size[0] * c_res_full_Info->size[1] *
    c_res_full_Info->size[2];
  c_res_full_Info->size[0] = Flattop->size[1];
  c_res_full_Info->size[1] = 2;
  c_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)c_res_full_Info, i0, sizeof(double));
  emxFree_real_T(&b_res_full_Info);
  for (i0 = 0; i0 < 2; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      loop_ub = Flattop->size[1];
      for (k = 0; k < loop_ub; k++) {
        c_res_full_Info->data[(k + c_res_full_Info->size[0] * i2) +
          c_res_full_Info->size[0] * c_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Flattop->data[Flattop->size[0] * k] +
          res_full_Info->size[0] * i2) + res_full_Info->size[0] *
          res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  sum(c_res_full_Info, d_x);
  c_mldivide(d_x, dv1, *(double (*)[4])&residual_ukf_Variance[4]);
  emxFree_real_T(&c_res_full_Info);
  if (1 > Decay->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = Decay->size[1] - 1;
  }

  emxInit_real_T1(&d_res_full_Info, 3);
  i0 = d_res_full_Info->size[0] * d_res_full_Info->size[1] *
    d_res_full_Info->size[2];
  d_res_full_Info->size[0] = loop_ub;
  d_res_full_Info->size[1] = 2;
  d_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)d_res_full_Info, i0, sizeof(double));
  for (i0 = 0; i0 < 2; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      for (k = 0; k < loop_ub; k++) {
        d_res_full_Info->data[(k + d_res_full_Info->size[0] * i2) +
          d_res_full_Info->size[0] * d_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Decay->data[k] + res_full_Info->size[0] *
          i2) + res_full_Info->size[0] * res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  sum(d_res_full_Info, d_x);
  c_mldivide(d_x, dv1, *(double (*)[4])&residual_ukf_Variance[8]);
  emxFree_real_T(&d_res_full_Info);
  if (1 > Decay->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = Decay->size[1] - 1;
  }

  if (1 > Decay->size[1] - 1) {
    n = 0;
  } else {
    n = Decay->size[1] - 1;
  }

  emxInit_real_T1(&e_res_full_Info, 3);
  i0 = e_res_full_Info->size[0] * e_res_full_Info->size[1] *
    e_res_full_Info->size[2];
  e_res_full_Info->size[0] = Rise->size[1];
  e_res_full_Info->size[1] = 2;
  e_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)e_res_full_Info, i0, sizeof(double));
  for (i0 = 0; i0 < 2; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      nm1d2 = Rise->size[1];
      for (k = 0; k < nm1d2; k++) {
        e_res_full_Info->data[(k + e_res_full_Info->size[0] * i2) +
          e_res_full_Info->size[0] * e_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Rise->data[Rise->size[0] * k] +
          res_full_Info->size[0] * i2) + res_full_Info->size[0] *
          res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  emxInit_real_T(&b_res_full_xi, 2);
  sum(e_res_full_Info, d_x);
  c_mldivide(d_x, dv1, a);
  i0 = b_res_full_xi->size[0] * b_res_full_xi->size[1];
  b_res_full_xi->size[0] = 2;
  b_res_full_xi->size[1] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)b_res_full_xi, i0, sizeof(double));
  nm1d2 = Rise->size[1];
  emxFree_real_T(&e_res_full_Info);
  for (i0 = 0; i0 < nm1d2; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      b_res_full_xi->data[i2 + b_res_full_xi->size[0] * i0] = res_full_xi->
        data[i2 + res_full_xi->size[0] * ((int)Rise->data[Rise->size[0] * i0] -
        1)];
    }
  }

  emxFree_real_T(&Rise);
  emxInit_real_T1(&f_res_full_Info, 3);
  b_sum(b_res_full_xi, A);
  i0 = f_res_full_Info->size[0] * f_res_full_Info->size[1] *
    f_res_full_Info->size[2];
  f_res_full_Info->size[0] = Flattop->size[1];
  f_res_full_Info->size[1] = 2;
  f_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)f_res_full_Info, i0, sizeof(double));
  emxFree_real_T(&b_res_full_xi);
  for (i0 = 0; i0 < 2; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      nm1d2 = Flattop->size[1];
      for (k = 0; k < nm1d2; k++) {
        f_res_full_Info->data[(k + f_res_full_Info->size[0] * i2) +
          f_res_full_Info->size[0] * f_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Flattop->data[Flattop->size[0] * k] +
          res_full_Info->size[0] * i2) + res_full_Info->size[0] *
          res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  emxInit_real_T(&c_res_full_xi, 2);
  sum(f_res_full_Info, d_x);
  c_mldivide(d_x, dv1, b_a);
  i0 = c_res_full_xi->size[0] * c_res_full_xi->size[1];
  c_res_full_xi->size[0] = 2;
  c_res_full_xi->size[1] = Flattop->size[1];
  emxEnsureCapacity((emxArray__common *)c_res_full_xi, i0, sizeof(double));
  nm1d2 = Flattop->size[1];
  emxFree_real_T(&f_res_full_Info);
  for (i0 = 0; i0 < nm1d2; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      c_res_full_xi->data[i2 + c_res_full_xi->size[0] * i0] = res_full_xi->
        data[i2 + res_full_xi->size[0] * ((int)Flattop->data[Flattop->size[0] *
        i0] - 1)];
    }
  }

  emxFree_real_T(&Flattop);
  emxInit_real_T1(&g_res_full_Info, 3);
  b_sum(c_res_full_xi, b_A);
  i0 = g_res_full_Info->size[0] * g_res_full_Info->size[1] *
    g_res_full_Info->size[2];
  g_res_full_Info->size[0] = loop_ub;
  g_res_full_Info->size[1] = 2;
  g_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)g_res_full_Info, i0, sizeof(double));
  emxFree_real_T(&c_res_full_xi);
  for (i0 = 0; i0 < 2; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      for (k = 0; k < loop_ub; k++) {
        g_res_full_Info->data[(k + g_res_full_Info->size[0] * i2) +
          g_res_full_Info->size[0] * g_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Decay->data[k] + res_full_Info->size[0] *
          i2) + res_full_Info->size[0] * res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  emxFree_real_T(&res_full_Info);
  emxInit_real_T(&d_res_full_xi, 2);
  sum(g_res_full_Info, d_x);
  c_mldivide(d_x, dv1, c_a);
  i0 = d_res_full_xi->size[0] * d_res_full_xi->size[1];
  d_res_full_xi->size[0] = 2;
  d_res_full_xi->size[1] = n;
  emxEnsureCapacity((emxArray__common *)d_res_full_xi, i0, sizeof(double));
  emxFree_real_T(&g_res_full_Info);
  for (i0 = 0; i0 < n; i0++) {
    for (i2 = 0; i2 < 2; i2++) {
      d_res_full_xi->data[i2 + d_res_full_xi->size[0] * i0] = res_full_xi->
        data[i2 + res_full_xi->size[0] * ((int)Decay->data[i0] - 1)];
    }
  }

  emxFree_real_T(&res_full_xi);
  emxFree_real_T(&Decay);
  b_sum(d_res_full_xi, c_A);
  //~ printf("d_res_full_xi: %f\n",d_res_full_xi->data[0]);
  //~ printf("d_res_full_xi: %f\n",d_res_full_xi->data[1]);
  //~ printf("d_res_full_xi: %f\n",d_res_full_xi->data[2]);
  //~ printf("d_res_full_xi: %f\n",d_res_full_xi->data[3]);
  //~ printf("d_res_full_xi: %f\n",d_res_full_xi->data[4]);
  emxFree_real_T(&d_res_full_xi);
  for (i0 = 0; i0 < 2; i0++) {
    d_a[i0] = 0.0;
    e_a[i0] = 0.0;
    f_a[i0] = 0.0;
    for (i2 = 0; i2 < 2; i2++) {
      d_a[i0] += a[i0 + (i2 << 1)] * A[i2];
      e_a[i0] += b_a[i0 + (i2 << 1)] * b_A[i2];
      f_a[i0] += c_a[i0 + (i2 << 1)] * c_A[i2];
    }

    residual_ukf_mean[i0] = d_a[i0];
    residual_ukf_mean[2 + i0] = e_a[i0];
    residual_ukf_mean[4 + i0] = f_a[i0];
  }
}

/*
 * File trailer for f_calib_and_res_gen_ukf.c
 *
 * [EOF]
 */
