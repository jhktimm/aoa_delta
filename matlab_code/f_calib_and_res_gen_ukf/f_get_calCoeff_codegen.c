/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_get_calCoeff_codegen.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "f_get_calCoeff_codegen.h"
#include "f_calib_and_res_gen_ukf_emxutil.h"
#include "mldivide.h"
#include "exp.h"
#include "f_calib_and_res_gen_ukf_rtwutil.h"

/* Function Definitions */

/*
 * claCoeff = f_get_calCoeff returns a 4 dimensional vector containing the
 *  coefficients needed for the calibration of the forward and reflected
 *  signals with respect to the probe. To calibrate a new set of data from
 *  the same cavity use f_calibrate().
 *  Input Parameters:
 *  Probe_Ampl: Amplitude of Probe measurement
 *  Probe_Phase: Phase of Probe measurement
 *  Forw_Ampl: Amplitude of Forward measurement
 *  Forw_Phase: Phase of Forward measurement
 *  Refl_Ampl: Amplitude of Reflected measurement
 *  Refl_Probe: Phase of Reflected measurement
 *  DECAY_TIM: Array containing the sample numbers that correspond to the
 *  duration of the decay time.
 *  free parameters...
 *  #codegen
 * Arguments    : const emxArray_real_T *Probe_Ampl
 *                const emxArray_real_T *Probe_Phase
 *                const emxArray_real_T *Forw_Ampl
 *                const emxArray_real_T *Forw_Phase
 *                const emxArray_real_T *Refl_Ampl
 *                const emxArray_real_T *Refl_Probe
 *                double DELAY
 *                double FILLING
 *                double FLATTOP
 *                double FS
 *                creal_T calCoeff[4]
 * Return Type  : void
 */
void f_get_calCoeff_codegen(const emxArray_real_T *Probe_Ampl, const
  emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Ampl, const
  emxArray_real_T *Refl_Probe, double DELAY, double FILLING, double FLATTOP,
  double FS, creal_T calCoeff[4])
{
  double fs;
  emxArray_real_T *Rise;
  emxArray_real_T *Flattop;
  emxArray_real_T *Decay;
  double x;
  double b_x;
  int k;
  double ndbl;
  double apnd;
  double cdiff;
  double absa;
  double absb;
  int nm1d2;
  int n;
  emxArray_creal_T *y_mC;
  emxArray_creal_T *u_mC;
  emxArray_creal_T *r_mC;
  emxArray_creal_T *a3;
  emxArray_creal_T *a4;
  emxArray_int32_T *b_Rise;
  emxArray_int32_T *c_Rise;
  unsigned int unnamed_idx_0;
  emxArray_creal_T *b_u_mC;
  unsigned int b_unnamed_idx_0;
  emxArray_creal_T *b_a3;
  creal_T xystar[2];
  static const double dv2[4] = { 1.0, 0.0, 0.1, 0.0 };

  static const double dv3[4] = { 0.0, 0.1, 0.0, 1.0 };

  static const double dv4[4] = { 0.1, 0.0, 0.0, 1.0 };

  emxArray_creal_T *r1;
  fs = FS * 1.0E+6;
  emxInit_real_T(&Rise, 2);
  emxInit_real_T(&Flattop, 2);
  emxInit_real_T(&Decay, 2);
  if (fs == 1.0E+6) {
    x = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6);
    b_x = rt_roundd_snf(DELAY * 1.0E+6 * 1.0E-6 + FILLING * 1.0E+6 * 1.0E-6);
    if (rtIsNaN(x) || rtIsNaN(b_x)) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (b_x < x) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
    } else if ((rtIsInf(x) || rtIsInf(b_x)) && (x == b_x)) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (x == x) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - x) + 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      nm1d2 = (int)(b_x - x);
      for (k = 0; k <= nm1d2; k++) {
        Rise->data[Rise->size[0] * k] = x + (double)k;
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

      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = n;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
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

    b_x = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * 1.0E+6
      * 1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(b_x)) {
      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (b_x < Rise->data[Rise->size[1] - 1] + 1.0) {
      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(b_x)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == b_x)) {
      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      fs = Rise->data[Rise->size[1] - 1] + 1.0;
      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(b_x - fs) + 1;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
      nm1d2 = (int)floor(b_x - fs);
      for (k = 0; k <= nm1d2; k++) {
        Flattop->data[Flattop->size[0] * k] = fs + (double)k;
      }
    } else {
      ndbl = floor((b_x - (Rise->data[Rise->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + ndbl;
      cdiff = apnd - b_x;
      absa = fabs(Rise->data[Rise->size[1] - 1] + 1.0);
      absb = fabs(b_x);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = b_x;
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

      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = n;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
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
      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (1821.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 1821.0)) {
      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      fs = Flattop->data[Flattop->size[1] - 1] + 1.0;
      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(1821.0 - fs) + 1;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
      nm1d2 = (int)floor(1821.0 - fs);
      for (k = 0; k <= nm1d2; k++) {
        Decay->data[Decay->size[0] * k] = fs + (double)k;
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

      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = n;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
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

    if (rtIsNaN(Decay->data[0] + 333.0) || rtIsNaN(Decay->data[Decay->size[1] -
         2])) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (Decay->data[Decay->size[1] - 2] < Decay->data[0] + 333.0) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
    } else if ((rtIsInf(Decay->data[0] + 333.0) || rtIsInf(Decay->data
                 [Decay->size[1] - 2])) && (Decay->data[0] + 333.0 ==
                Decay->data[Decay->size[1] - 2])) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (floor(Decay->data[0] + 333.0) == Decay->data[0] + 333.0) {
      fs = Decay->data[0] + 333.0;
      b_x = Decay->data[Decay->size[1] - 2];
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)floor(b_x - fs) + 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      nm1d2 = (int)floor(b_x - fs);
      for (k = 0; k <= nm1d2; k++) {
        Rise->data[Rise->size[0] * k] = fs + (double)k;
      }
    } else {
      ndbl = floor((Decay->data[Decay->size[1] - 2] - (Decay->data[0] + 333.0))
                   + 0.5);
      apnd = (Decay->data[0] + 333.0) + ndbl;
      cdiff = apnd - Decay->data[Decay->size[1] - 2];
      absa = fabs(Decay->data[0] + 333.0);
      absb = fabs(Decay->data[Decay->size[1] - 2]);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = Decay->data[Decay->size[1] - 2];
      } else if (cdiff > 0.0) {
        apnd = (Decay->data[0] + 333.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = n;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      if (n > 0) {
        Rise->data[0] = Decay->data[0] + 333.0;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Rise->data[k] = (Decay->data[0] + 333.0) + (double)k;
            Rise->data[(n - k) - 1] = apnd - (double)k;
          }

          if (nm1d2 << 1 == n - 1) {
            Rise->data[nm1d2] = ((Decay->data[0] + 333.0) + apnd) / 2.0;
          } else {
            Rise->data[nm1d2] = (Decay->data[0] + 333.0) + (double)nm1d2;
            Rise->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }
  } else {
    x = rt_roundd_snf(DELAY * fs * 1.0E-6);
    b_x = rt_roundd_snf(DELAY * fs * 1.0E-6 + FILLING * fs * 1.0E-6);
    if (rtIsNaN(x) || rtIsNaN(b_x)) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (b_x < x) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
    } else if ((rtIsInf(x) || rtIsInf(b_x)) && (x == b_x)) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (x == x) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)(b_x - x) + 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      nm1d2 = (int)(b_x - x);
      for (k = 0; k <= nm1d2; k++) {
        Rise->data[Rise->size[0] * k] = x + (double)k;
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

      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = n;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
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

    b_x = (Rise->data[Rise->size[1] - 1] + 1.0) + rt_roundd_snf(FLATTOP * fs *
      1.0E-6);
    if (rtIsNaN(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsNaN(b_x)) {
      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (b_x < Rise->data[Rise->size[1] - 1] + 1.0) {
      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
    } else if ((rtIsInf(Rise->data[Rise->size[1] - 1] + 1.0) || rtIsInf(b_x)) &&
               (Rise->data[Rise->size[1] - 1] + 1.0 == b_x)) {
      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
      Flattop->data[0] = rtNaN;
    } else if (floor(Rise->data[Rise->size[1] - 1] + 1.0) == Rise->data
               [Rise->size[1] - 1] + 1.0) {
      fs = Rise->data[Rise->size[1] - 1] + 1.0;
      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = (int)floor(b_x - fs) + 1;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
      nm1d2 = (int)floor(b_x - fs);
      for (k = 0; k <= nm1d2; k++) {
        Flattop->data[Flattop->size[0] * k] = fs + (double)k;
      }
    } else {
      ndbl = floor((b_x - (Rise->data[Rise->size[1] - 1] + 1.0)) + 0.5);
      apnd = (Rise->data[Rise->size[1] - 1] + 1.0) + ndbl;
      cdiff = apnd - b_x;
      absa = fabs(Rise->data[Rise->size[1] - 1] + 1.0);
      absb = fabs(b_x);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = b_x;
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

      k = Flattop->size[0] * Flattop->size[1];
      Flattop->size[0] = 1;
      Flattop->size[1] = n;
      emxEnsureCapacity((emxArray__common *)Flattop, k, sizeof(double));
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
      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (16384.0 < Flattop->data[Flattop->size[1] - 1] + 1.0) {
      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
    } else if (rtIsInf(Flattop->data[Flattop->size[1] - 1] + 1.0) &&
               (Flattop->data[Flattop->size[1] - 1] + 1.0 == 16384.0)) {
      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
      Decay->data[0] = rtNaN;
    } else if (floor(Flattop->data[Flattop->size[1] - 1] + 1.0) == Flattop->
               data[Flattop->size[1] - 1] + 1.0) {
      fs = Flattop->data[Flattop->size[1] - 1] + 1.0;
      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = (int)floor(16384.0 - fs) + 1;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
      nm1d2 = (int)floor(16384.0 - fs);
      for (k = 0; k <= nm1d2; k++) {
        Decay->data[Decay->size[0] * k] = fs + (double)k;
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

      k = Decay->size[0] * Decay->size[1];
      Decay->size[0] = 1;
      Decay->size[1] = n;
      emxEnsureCapacity((emxArray__common *)Decay, k, sizeof(double));
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

    if (rtIsNaN(Decay->data[0] + 3000.0) || rtIsNaN(Decay->data[Decay->size[1] -
         1])) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (Decay->data[Decay->size[1] - 1] < Decay->data[0] + 3000.0) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
    } else if ((rtIsInf(Decay->data[0] + 3000.0) || rtIsInf(Decay->data
                 [Decay->size[1] - 1])) && (Decay->data[0] + 3000.0 ==
                Decay->data[Decay->size[1] - 1])) {
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      Rise->data[0] = rtNaN;
    } else if (floor(Decay->data[0] + 3000.0) == Decay->data[0] + 3000.0) {
      fs = Decay->data[0] + 3000.0;
      b_x = Decay->data[Decay->size[1] - 1];
      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = (int)floor(b_x - fs) + 1;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      nm1d2 = (int)floor(b_x - fs);
      for (k = 0; k <= nm1d2; k++) {
        Rise->data[Rise->size[0] * k] = fs + (double)k;
      }
    } else {
      ndbl = floor((Decay->data[Decay->size[1] - 1] - (Decay->data[0] + 3000.0))
                   + 0.5);
      apnd = (Decay->data[0] + 3000.0) + ndbl;
      cdiff = apnd - Decay->data[Decay->size[1] - 1];
      absa = fabs(Decay->data[0] + 3000.0);
      absb = fabs(Decay->data[Decay->size[1] - 1]);
      if ((absa > absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = Decay->data[Decay->size[1] - 1];
      } else if (cdiff > 0.0) {
        apnd = (Decay->data[0] + 3000.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      k = Rise->size[0] * Rise->size[1];
      Rise->size[0] = 1;
      Rise->size[1] = n;
      emxEnsureCapacity((emxArray__common *)Rise, k, sizeof(double));
      if (n > 0) {
        Rise->data[0] = Decay->data[0] + 3000.0;
        if (n > 1) {
          Rise->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 1; k < nm1d2; k++) {
            Rise->data[k] = (Decay->data[0] + 3000.0) + (double)k;
            Rise->data[(n - k) - 1] = apnd - (double)k;
          }

          if (nm1d2 << 1 == n - 1) {
            Rise->data[nm1d2] = ((Decay->data[0] + 3000.0) + apnd) / 2.0;
          } else {
            Rise->data[nm1d2] = (Decay->data[0] + 3000.0) + (double)nm1d2;
            Rise->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }
  }

  emxFree_real_T(&Decay);
  emxFree_real_T(&Flattop);
  emxInit_creal_T(&y_mC, 1);
  k = y_mC->size[0];
  y_mC->size[0] = Probe_Phase->size[0];
  emxEnsureCapacity((emxArray__common *)y_mC, k, sizeof(creal_T));
  nm1d2 = Probe_Phase->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_x = 0.0 * Probe_Phase->data[k];
    x = Probe_Phase->data[k];
    if (x == 0.0) {
      fs = b_x / 180.0;
      b_x = 0.0;
    } else if (b_x == 0.0) {
      fs = 0.0;
      b_x = x / 180.0;
    } else {
      fs = b_x / 180.0;
      b_x = x / 180.0;
    }

    y_mC->data[k].re = 3.1415926535897931 * fs;
    y_mC->data[k].im = 3.1415926535897931 * b_x;
  }

  b_exp(y_mC);
  k = y_mC->size[0];
  y_mC->size[0] = Probe_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)y_mC, k, sizeof(creal_T));
  nm1d2 = Probe_Ampl->size[0];
  for (k = 0; k < nm1d2; k++) {
    y_mC->data[k].re *= Probe_Ampl->data[k];
    y_mC->data[k].im *= Probe_Ampl->data[k];
  }

  emxInit_creal_T(&u_mC, 1);

  /*  Complex Probe measurement */
  k = u_mC->size[0];
  u_mC->size[0] = Forw_Phase->size[0];
  emxEnsureCapacity((emxArray__common *)u_mC, k, sizeof(creal_T));
  nm1d2 = Forw_Phase->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_x = 0.0 * Forw_Phase->data[k];
    x = Forw_Phase->data[k];
    if (x == 0.0) {
      fs = b_x / 180.0;
      b_x = 0.0;
    } else if (b_x == 0.0) {
      fs = 0.0;
      b_x = x / 180.0;
    } else {
      fs = b_x / 180.0;
      b_x = x / 180.0;
    }

    u_mC->data[k].re = 3.1415926535897931 * fs;
    u_mC->data[k].im = 3.1415926535897931 * b_x;
  }

  b_exp(u_mC);
  k = u_mC->size[0];
  u_mC->size[0] = Forw_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)u_mC, k, sizeof(creal_T));
  nm1d2 = Forw_Ampl->size[0];
  for (k = 0; k < nm1d2; k++) {
    u_mC->data[k].re *= Forw_Ampl->data[k];
    u_mC->data[k].im *= Forw_Ampl->data[k];
  }

  emxInit_creal_T(&r_mC, 1);

  /*  Complex Forward measurement */
  k = r_mC->size[0];
  r_mC->size[0] = Refl_Probe->size[0];
  emxEnsureCapacity((emxArray__common *)r_mC, k, sizeof(creal_T));
  nm1d2 = Refl_Probe->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_x = 0.0 * Refl_Probe->data[k];
    x = Refl_Probe->data[k];
    if (x == 0.0) {
      fs = b_x / 180.0;
      b_x = 0.0;
    } else if (b_x == 0.0) {
      fs = 0.0;
      b_x = x / 180.0;
    } else {
      fs = b_x / 180.0;
      b_x = x / 180.0;
    }

    r_mC->data[k].re = 3.1415926535897931 * fs;
    r_mC->data[k].im = 3.1415926535897931 * b_x;
  }

  b_exp(r_mC);
  k = r_mC->size[0];
  r_mC->size[0] = Refl_Ampl->size[0];
  emxEnsureCapacity((emxArray__common *)r_mC, k, sizeof(creal_T));
  nm1d2 = Refl_Ampl->size[0];
  for (k = 0; k < nm1d2; k++) {
    r_mC->data[k].re *= Refl_Ampl->data[k];
    r_mC->data[k].im *= Refl_Ampl->data[k];
  }

  emxInit_creal_T(&a3, 1);

  /*  Reflected */
  k = a3->size[0];
  a3->size[0] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)a3, k, sizeof(creal_T));
  nm1d2 = Rise->size[1];
  for (k = 0; k < nm1d2; k++) {
    a3->data[k] = u_mC->data[(int)Rise->data[Rise->size[0] * k] - 1];
  }

  emxInit_creal_T(&a4, 1);
  k = a4->size[0];
  a4->size[0] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)a4, k, sizeof(creal_T));
  nm1d2 = Rise->size[1];
  for (k = 0; k < nm1d2; k++) {
    a4->data[k] = r_mC->data[(int)Rise->data[Rise->size[0] * k] - 1];
  }

  emxInit_int32_T(&b_Rise, 1);
  k = b_Rise->size[0];
  b_Rise->size[0] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)b_Rise, k, sizeof(int));
  nm1d2 = Rise->size[1];
  for (k = 0; k < nm1d2; k++) {
    b_Rise->data[k] = (int)Rise->data[Rise->size[0] * k];
  }

  emxInit_int32_T(&c_Rise, 1);
  unnamed_idx_0 = (unsigned int)b_Rise->size[0];
  k = c_Rise->size[0];
  c_Rise->size[0] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)c_Rise, k, sizeof(int));
  nm1d2 = Rise->size[1];
  emxFree_int32_T(&b_Rise);
  for (k = 0; k < nm1d2; k++) {
    c_Rise->data[k] = (int)Rise->data[Rise->size[0] * k];
  }

  emxInit_creal_T1(&b_u_mC, 2);
  b_unnamed_idx_0 = (unsigned int)c_Rise->size[0];

  /* za1= zeros(size(a1)); */
  k = b_u_mC->size[0] * b_u_mC->size[1];
  b_u_mC->size[0] = u_mC->size[0];
  b_u_mC->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_u_mC, k, sizeof(creal_T));
  nm1d2 = u_mC->size[0];
  emxFree_int32_T(&c_Rise);
  for (k = 0; k < nm1d2; k++) {
    b_u_mC->data[k] = u_mC->data[k];
  }

  nm1d2 = r_mC->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_u_mC->data[k + b_u_mC->size[0]] = r_mC->data[k];
  }

  emxInit_creal_T1(&b_a3, 2);
  mldivide(b_u_mC, y_mC, xystar);

  /*  estimate cross couplings next.... */
  /*  uses method of least squares... */
  /*  tunig factor to adjust f1/2 within pulse and during decay (Fig 21, red == yellow line) */
  /*  calCoeff0(:,1) = (Aold.'*Aold)^-1*Aold.'*Bold;%mldivide(Aold,Bold);  */
  /*  calCoeff1(:,1) = inv(Aold.'*Aold)*Aold.'*Bold;%mldivide(Aold,Bold);  */
  k = b_a3->size[0] * b_a3->size[1];
  b_a3->size[0] = ((a3->size[0] + u_mC->size[0]) + (int)b_unnamed_idx_0) + 3;
  b_a3->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)b_a3, k, sizeof(creal_T));
  nm1d2 = a3->size[0];
  emxFree_creal_T(&b_u_mC);
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[k] = a3->data[k];
  }

  nm1d2 = a4->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[k + b_a3->size[0]] = a4->data[k];
  }

  nm1d2 = (int)b_unnamed_idx_0;
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[k + (b_a3->size[0] << 1)].re = 0.0;
    b_a3->data[k + (b_a3->size[0] << 1)].im = 0.0;
  }

  nm1d2 = (int)b_unnamed_idx_0;
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[k + b_a3->size[0] * 3].re = 0.0;
    b_a3->data[k + b_a3->size[0] * 3].im = 0.0;
  }

  nm1d2 = u_mC->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[k + a3->size[0]] = u_mC->data[k];
  }

  nm1d2 = r_mC->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[(k + a3->size[0]) + b_a3->size[0]] = r_mC->data[k];
  }

  nm1d2 = u_mC->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[(k + a3->size[0]) + (b_a3->size[0] << 1)] = u_mC->data[k];
  }

  nm1d2 = r_mC->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[(k + a3->size[0]) + b_a3->size[0] * 3] = r_mC->data[k];
  }

  emxFree_creal_T(&r_mC);
  nm1d2 = (int)b_unnamed_idx_0;
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[(k + a3->size[0]) + u_mC->size[0]].re = 0.0;
    b_a3->data[(k + a3->size[0]) + u_mC->size[0]].im = 0.0;
  }

  nm1d2 = (int)b_unnamed_idx_0;
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[((k + a3->size[0]) + u_mC->size[0]) + b_a3->size[0]].re = 0.0;
    b_a3->data[((k + a3->size[0]) + u_mC->size[0]) + b_a3->size[0]].im = 0.0;
  }

  nm1d2 = a3->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[((k + a3->size[0]) + u_mC->size[0]) + (b_a3->size[0] << 1)] =
      a3->data[k];
  }

  nm1d2 = a4->size[0];
  for (k = 0; k < nm1d2; k++) {
    b_a3->data[((k + a3->size[0]) + u_mC->size[0]) + b_a3->size[0] * 3] =
      a4->data[k];
  }

  emxFree_creal_T(&a4);
  for (k = 0; k < 4; k++) {
    b_a3->data[((a3->size[0] + u_mC->size[0]) + (int)b_unnamed_idx_0) +
      b_a3->size[0] * k].re = dv2[k];
    b_a3->data[((a3->size[0] + u_mC->size[0]) + (int)b_unnamed_idx_0) +
      b_a3->size[0] * k].im = 0.0;
  }

  for (k = 0; k < 4; k++) {
    b_a3->data[(((a3->size[0] + u_mC->size[0]) + (int)b_unnamed_idx_0) +
                b_a3->size[0] * k) + 1].re = dv3[k];
    b_a3->data[(((a3->size[0] + u_mC->size[0]) + (int)b_unnamed_idx_0) +
                b_a3->size[0] * k) + 1].im = 0.0;
  }

  for (k = 0; k < 4; k++) {
    b_a3->data[(((a3->size[0] + u_mC->size[0]) + (int)b_unnamed_idx_0) +
                b_a3->size[0] * k) + 2].re = dv4[k];
    b_a3->data[(((a3->size[0] + u_mC->size[0]) + (int)b_unnamed_idx_0) +
                b_a3->size[0] * k) + 2].im = 0.0;
  }

  emxFree_creal_T(&a3);
  emxFree_creal_T(&u_mC);
  emxInit_creal_T(&r1, 1);
  k = r1->size[0];
  r1->size[0] = (((int)unnamed_idx_0 + y_mC->size[0]) + Rise->size[1]) + 3;
  emxEnsureCapacity((emxArray__common *)r1, k, sizeof(creal_T));
  nm1d2 = (int)unnamed_idx_0;
  for (k = 0; k < nm1d2; k++) {
    r1->data[k].re = 0.0;
    r1->data[k].im = 0.0;
  }

  nm1d2 = y_mC->size[0];
  for (k = 0; k < nm1d2; k++) {
    r1->data[k + (int)unnamed_idx_0] = y_mC->data[k];
  }

  nm1d2 = Rise->size[1];
  for (k = 0; k < nm1d2; k++) {
    r1->data[(k + (int)unnamed_idx_0) + y_mC->size[0]] = y_mC->data[(int)
      Rise->data[Rise->size[0] * k] - 1];
  }

  r1->data[((int)unnamed_idx_0 + y_mC->size[0]) + Rise->size[1]] = xystar[0];
  r1->data[(((int)unnamed_idx_0 + y_mC->size[0]) + Rise->size[1]) + 1] = xystar
    [1];
  r1->data[(((int)unnamed_idx_0 + y_mC->size[0]) + Rise->size[1]) + 2] = xystar
    [1];
  b_mldivide(b_a3, r1, calCoeff);

  /*  calCoeff3(:,1) = mldivide(Aold,Bold); */
  emxFree_creal_T(&r1);
  emxFree_creal_T(&b_a3);
  emxFree_creal_T(&y_mC);
  emxFree_real_T(&Rise);
}

/*
 * File trailer for f_get_calCoeff_codegen.c
 *
 * [EOF]
 */
