/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_calib_and_res_gen_ukf.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
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
  double f0;
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
  int k;
  int n;
  emxArray_creal_T *y_mC;
  int nm1d2;
  emxArray_creal_T *u_mC;
  emxArray_creal_T *r_mC;
  emxArray_creal_T *b_y_mC;
  short t2;
  short i1;
  emxArray_creal_T *u_mCal;
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
  int unnamed_idx_1;
  emxArray_real_T *b_Flattop;
  double b_A[2];
  int b_unnamed_idx_1;
  emxArray_real_T *b_Decay;
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
  //~ f_get_calCoeff_codegen(PA, PP, FA, FP, RA, RP, DELAY, FILLING, FLATTOP, FS, cal_Coeff);

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
  /*  %% Facility */
  /*  clear */
  /*  warning('On') */
  /*  facility = 'XFEL.RF'; */
  /*  station = 'A19.L3'; */
  /*  module = 'M1'; */
  /*  cavity_all = {'C2'}; */
  /*  */
  /*  FS = doocsread([facility,'/LLRF.CONTROLLER/MAIN.M12.',station,'/FS']); */
  /*  F0 = doocsread([facility,'/LLRF.CONTROLLER/MAIN.M12.',station,'/F0']); */
  /*  % Static Values */
  /*  fs = FS.data*1e6; */
  /*  f0 = F0.data *1e6; */
  /*  Ts = 1/fs; */
  /*  %----------------- Time of Rise, Flattop and Decay ---------------------- */
  /*  DELAY = doocsread([facility,'/LLRF.CONTROLLER/MAIN.M12.',station,'/PULSE_DELAY']); */
  /*  FILLING = doocsread([facility,'/LLRF.CONTROLLER/MAIN.M12.',station,'/PULSE_FILLING']); */
  /*  FLATTOP = doocsread([facility,'/LLRF.CONTROLLER/MAIN.M12.',station,'/PULSE_FLATTOP']); */
  /*  Rise = round(DELAY.data * fs *1e-6):round(DELAY.data * fs*1e-6+ FILLING.data*fs*1e-6); */
  /*  Flattop = Rise(end)+1 : Rise(end)+1+round(FLATTOP.data*fs*1e-6); */
  /*  Decay = Flattop(end)+1 : 2^(14); */
  /*  */
  /*  %% Get Data */
  /*  % The Data used for all following algorithms are the complex signal */
  /*  % representations of the forward, reflected and probe measurements of the */
  /*  % electromagnetic fields during each pulse. */
  /*  % y_mC is the complex representation of the probe signal. */
  /*  % u_mC is the complex represenation of the forward signal. */
  /*  % r_mC is the complex represnentation of the refelxted signal. */
  /*  */
  /*  for k = 1:length(cavity_all) */
  /*      cavity = cavity_all{k}; */
  /*      [y_mC(:,k), u_mC(:,k), r_mC(:,k)] = f_getData(facility, station, module, cavity); */
  /*  end */
  /*  Calibrate Data */
  /*  Each pulse has to be calibrated such, that the sum of forwad and */
  /*  refelcted is equal to the probe signal. abs(u_mC)+abs(r_mC) = abs(y_mC). */
  /*  In general, the measurements of these signals are not calibrated. In */
  /*  order to calibrate the forwad signal with respect to the probe, the */
  /*  reflected signal is needed. */
  /*  %--------------- Calibrated Forward and Probe------------------------------ */
  /*  cal_coeff = zeros(4,1); */
  /*  coeff = [u_mC r_mC]\y_mC; */
  /*  if(max(abs(1-abs(coeff))>0.05) || max(abs(180/pi*angle(coeff)) > 5)) */
  /*      warning('Calibration required') */
  /*      cal_coeff(:,k) = f_get_calCoeff(y_mC, u_mC, r_mC, Decay(1)+3000:Decay(end),1); */
  /*  end */
  /*  [u_mCal, r_mCal] = f_calibrateData(u_mC, r_mC, y_mC, cal_coeff); */
  /*  */
  /*  %------------Plot Before and After Calibration----------------------------- */
  /*  */
  /*  figure(22) */
  /*  subplot(2,1,1) */
  /*  plot(abs(u_mC(:,1)+r_mC(:,1)),'r--') */
  /*  hold on */
  /*  plot(abs(y_mC(:,1)),'k--') */
  /*  plot(abs(u_mC(:,1)),'g') */
  /*  plot(abs(r_mC(:,1)), 'b') */
  /*  legend('Virtual Probe', 'Probe', 'Forward', 'Reflected') */
  /*  ylabel('After Calbiration') */
  /*  */
  /*  subplot(2,1,2) */
  /*  plot(abs(u_mCal(:,1)+r_mCal(:,1)),'r--') */
  /*  hold on */
  /*  plot(abs(y_mC(:,1)),'k--') */
  /*  plot(abs(u_mCal(:,1)),'g') */
  /*  plot(abs(r_mCal(:,1)), 'b') */
  /*  legend('Virtual Probe', 'Probe', 'Forward', 'Reflected') */
  /*  ylabel('After Calbiration') */
  fs = FS * 1.0E+6;
  f0 = F0 * 1.0E+6;
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
      k = (int)(b_x - x);
      for (i0 = 0; i0 <= k; i0++) {
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
      k = (int)floor(d - x);
      for (i0 = 0; i0 <= k; i0++) {
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
      k = (int)floor(1821.0 - x);
      for (i0 = 0; i0 <= k; i0++) {
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
      k = (int)(b_x - x);
      for (i0 = 0; i0 <= k; i0++) {
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
      k = (int)floor(d - x);
      for (i0 = 0; i0 <= k; i0++) {
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
      k = (int)floor(16384.0 - x);
      for (i0 = 0; i0 <= k; i0++) {
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
  k = PP->size[0];
  for (i0 = 0; i0 < k; i0++) {
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
  k = PA->size[0];
  for (i0 = 0; i0 < k; i0++) {
    y_mC->data[i0].re *= PA->data[i0];
    y_mC->data[i0].im *= PA->data[i0];
  }

  emxInit_creal_T(&u_mC, 1);

  /*  Complex Probe measurement */
  i0 = u_mC->size[0];
  u_mC->size[0] = FP->size[0];
  emxEnsureCapacity((emxArray__common *)u_mC, i0, sizeof(creal_T));
  k = FP->size[0];
  for (i0 = 0; i0 < k; i0++) {
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
  k = FA->size[0];
  for (i0 = 0; i0 < k; i0++) {
    u_mC->data[i0].re *= FA->data[i0];
    u_mC->data[i0].im *= FA->data[i0];
  }

  emxInit_creal_T(&r_mC, 1);

  /*  Complex Forward measurement */
  i0 = r_mC->size[0];
  r_mC->size[0] = RP->size[0];
  emxEnsureCapacity((emxArray__common *)r_mC, i0, sizeof(creal_T));
  k = RP->size[0];
  for (i0 = 0; i0 < k; i0++) {
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
  k = RA->size[0];
  for (i0 = 0; i0 < k; i0++) {
    r_mC->data[i0].re *= RA->data[i0];
    r_mC->data[i0].im *= RA->data[i0];
  }

  emxInit_creal_T(&b_y_mC, 1);

  /*  Reflected */
  /*  The quality factor of the cavity is determined by the decay time of the */
  /*  probes signal. */
  x = rt_roundd_snf(Decay->data[0] + (double)Decay->size[1] / 2.0);
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

  i0 = (int)rt_roundd_snf((double)Decay->size[1] * 15.0 / 32.0);
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
  k = i1;
  for (i0 = 0; i0 <= k; i0++) {
    n = t2 + i0;
    if (n > 32767) {
      n = 32767;
    } else {
      if (n < -32768) {
        n = -32768;
      }
    }

    b_y_mC->data[i0] = y_mC->data[n - 1];
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
  /*  tic */
  /*  Y_MC = zeros(length(u_mC), 20); */
  /*  U_MC = zeros(length(u_mC), 20); */
  /*  R_MC = zeros(length(u_mC), 20); */
  /*  iterSwitch = 0; */
  /*  iter = 0; */
  /*  state_of_sys = cell(10,1); */
  /*  pNum = 1; */
  /*  while(1) */
  /*      cavity = cavity_all{1}; */
  /*  u_mCal = zeros(length(u_mC),1); */
  /*  r_mCal = zeros(length(u_mC),1); */
  /*  [y_mC, u_mC, r_mC] = f_getData(facility, station, module, cavity); */
  /* Initialize */
  i0 = u_mCal->size[0];
  u_mCal->size[0] = u_mC->size[0];
  emxEnsureCapacity((emxArray__common *)u_mCal, i0, sizeof(creal_T));
  k = u_mC->size[0];
  emxFree_creal_T(&b_y_mC);
  for (i0 = 0; i0 < k; i0++) {
    u_mCal->data[i0].re = 0.0;
    u_mCal->data[i0].im = 0.0;
  }

  emxInit_int32_T(&r0, 1);

  /*  compute calibrated FORW and REFL signal */
  k = u_mCal->size[0];
  i0 = r0->size[0];
  r0->size[0] = k;
  emxEnsureCapacity((emxArray__common *)r0, i0, sizeof(int));
  for (i0 = 0; i0 < k; i0++) {
    r0->data[i0] = i0;
  }

  emxInit_creal_T1(&b_u_mC, 2);
  k = u_mC->size[0];
  i0 = b_u_mC->size[0] * b_u_mC->size[1];
  b_u_mC->size[0] = 1;
  b_u_mC->size[1] = k;
  emxEnsureCapacity((emxArray__common *)b_u_mC, i0, sizeof(creal_T));
  for (i0 = 0; i0 < k; i0++) {
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
  n = c_y_mC->size[0] * c_y_mC->size[1];
  c_y_mC->size[0] = 2;
  c_y_mC->size[1] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)c_y_mC, n, sizeof(double));
  k = y_mC->size[0];
  for (n = 0; n < k; n++) {
    c_y_mC->data[c_y_mC->size[0] * n] = y_mC->data[n].re;
  }

  k = y_mC->size[0];
  for (n = 0; n < k; n++) {
    c_y_mC->data[1 + c_y_mC->size[0] * n] = y_mC->data[n].im;
  }

  emxFree_creal_T(&y_mC);
  emxInit_real_T(&b_u_mCal, 2);
  n = b_u_mCal->size[0] * b_u_mCal->size[1];
  b_u_mCal->size[0] = 2;
  b_u_mCal->size[1] = u_mCal->size[0];
  emxEnsureCapacity((emxArray__common *)b_u_mCal, n, sizeof(double));
  k = u_mCal->size[0];
  for (n = 0; n < k; n++) {
    b_u_mCal->data[b_u_mCal->size[0] * n] = u_mCal->data[n].re;
  }

  k = u_mCal->size[0];
  for (n = 0; n < k; n++) {
    b_u_mCal->data[1 + b_u_mCal->size[0] * n] = u_mCal->data[n].im;
  }

  emxFree_creal_T(&u_mCal);
  emxInit_real_T(&res_full_mean, 2);
  emxInit_real_T1(&unusedU1, 3);
  emxInit_real_T(&res_full_xi, 2);
  emxInit_real_T1(&res_full_Info, 3);
  emxInit_real_T(&c_x, 2);
  f_compute_ukf_residual(dv0, c_y_mC, b_u_mCal, f0, fs, 3.1415926535897931 * f0 *
    fabs(1.0 / ((lnA->data[lnA->size[0] - 1] - lnA->data[0]) / ((double)i0 / fs))),
    tau_m, K_m, res_full_mean, unusedU1, res_full_xi, res_full_Info);
    
  printf("lnA[%i]: %f\n",lnA->size[0],lnA->data[lnA->size[0] - 1] );
for(int i = 0; i<5; i++) printf("lnA[%i]: %f\n",i,lnA->data[i]);

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
  /*  Arithmetic mean of the mean  */
  i0 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 2;
  c_x->size[1] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)c_x, i0, sizeof(double));
  k = Rise->size[1];
  emxFree_real_T(&b_u_mCal);
  emxFree_real_T(&c_y_mC);
  emxFree_real_T(&lnA);
  emxFree_real_T(&unusedU1);
  for (i0 = 0; i0 < k; i0++) {
    for (n = 0; n < 2; n++) {
      c_x->data[n + c_x->size[0] * i0] = res_full_mean->data[n +
        res_full_mean->size[0] * ((int)Rise->data[Rise->size[0] * i0] - 1)];
    }
  }

  emxInit_real_T2(&b_Rise, 1);
  combine_vector_elements(c_x, A);
  i0 = b_Rise->size[0];
  b_Rise->size[0] = Rise->size[1];
  emxEnsureCapacity((emxArray__common *)b_Rise, i0, sizeof(double));
  k = Rise->size[1];
  for (i0 = 0; i0 < k; i0++) {
    b_Rise->data[i0] = Rise->data[Rise->size[0] * i0];
  }

  unnamed_idx_1 = b_Rise->size[0];
  i0 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 2;
  c_x->size[1] = Flattop->size[1];
  emxEnsureCapacity((emxArray__common *)c_x, i0, sizeof(double));
  k = Flattop->size[1];
  emxFree_real_T(&b_Rise);
  for (i0 = 0; i0 < k; i0++) {
    for (n = 0; n < 2; n++) {
      c_x->data[n + c_x->size[0] * i0] = res_full_mean->data[n +
        res_full_mean->size[0] * ((int)Flattop->data[Flattop->size[0] * i0] - 1)];
    }
  }

  emxInit_real_T2(&b_Flattop, 1);
  combine_vector_elements(c_x, b_A);
  i0 = b_Flattop->size[0];
  b_Flattop->size[0] = Flattop->size[1];
  emxEnsureCapacity((emxArray__common *)b_Flattop, i0, sizeof(double));
  k = Flattop->size[1];
  for (i0 = 0; i0 < k; i0++) {
    b_Flattop->data[i0] = Flattop->data[Flattop->size[0] * i0];
  }

  b_unnamed_idx_1 = b_Flattop->size[0];
  i0 = c_x->size[0] * c_x->size[1];
  c_x->size[0] = 2;
  c_x->size[1] = Decay->size[1];
  emxEnsureCapacity((emxArray__common *)c_x, i0, sizeof(double));
  k = Decay->size[1];
  emxFree_real_T(&b_Flattop);
  for (i0 = 0; i0 < k; i0++) {
    for (n = 0; n < 2; n++) {
      c_x->data[n + c_x->size[0] * i0] = res_full_mean->data[n +
        res_full_mean->size[0] * ((int)Decay->data[Decay->size[0] * i0] - 1)];
    }
  }

  emxFree_real_T(&res_full_mean);
  emxInit_real_T2(&b_Decay, 1);
  combine_vector_elements(c_x, c_A);
  i0 = b_Decay->size[0];
  b_Decay->size[0] = Decay->size[1];
  emxEnsureCapacity((emxArray__common *)b_Decay, i0, sizeof(double));
  k = Decay->size[1];
  emxFree_real_T(&c_x);
  for (i0 = 0; i0 < k; i0++) {
    b_Decay->data[i0] = Decay->data[Decay->size[0] * i0];
  }

  nm1d2 = b_Decay->size[0];
  emxFree_real_T(&b_Decay);
  for (i0 = 0; i0 < 2; i0++) {
    residual_ukf[i0] = A[i0] / (double)unnamed_idx_1;
    residual_ukf[2 + i0] = b_A[i0] / (double)b_unnamed_idx_1;
    residual_ukf[4 + i0] = c_A[i0] / (double)nm1d2;
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
    for (n = 0; n < 2; n++) {
      k = Rise->size[1];
      for (nm1d2 = 0; nm1d2 < k; nm1d2++) {
        b_res_full_Info->data[(nm1d2 + b_res_full_Info->size[0] * n) +
          b_res_full_Info->size[0] * b_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Rise->data[Rise->size[0] * nm1d2] +
          res_full_Info->size[0] * n) + res_full_Info->size[0] *
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
    for (n = 0; n < 2; n++) {
      k = Flattop->size[1];
      for (nm1d2 = 0; nm1d2 < k; nm1d2++) {
        c_res_full_Info->data[(nm1d2 + c_res_full_Info->size[0] * n) +
          c_res_full_Info->size[0] * c_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Flattop->data[Flattop->size[0] * nm1d2] +
          res_full_Info->size[0] * n) + res_full_Info->size[0] *
          res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  emxInit_real_T1(&d_res_full_Info, 3);
  sum(c_res_full_Info, d_x);
  c_mldivide(d_x, dv1, *(double (*)[4])&residual_ukf_Variance[4]);
  i0 = d_res_full_Info->size[0] * d_res_full_Info->size[1] *
    d_res_full_Info->size[2];
  d_res_full_Info->size[0] = Decay->size[1];
  d_res_full_Info->size[1] = 2;
  d_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)d_res_full_Info, i0, sizeof(double));
  emxFree_real_T(&c_res_full_Info);
  for (i0 = 0; i0 < 2; i0++) {
    for (n = 0; n < 2; n++) {
      k = Decay->size[1];
      for (nm1d2 = 0; nm1d2 < k; nm1d2++) {
        d_res_full_Info->data[(nm1d2 + d_res_full_Info->size[0] * n) +
          d_res_full_Info->size[0] * d_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Decay->data[Decay->size[0] * nm1d2] +
          res_full_Info->size[0] * n) + res_full_Info->size[0] *
          res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  emxInit_real_T1(&e_res_full_Info, 3);
  sum(d_res_full_Info, d_x);
  c_mldivide(d_x, dv1, *(double (*)[4])&residual_ukf_Variance[8]);
  i0 = e_res_full_Info->size[0] * e_res_full_Info->size[1] *
    e_res_full_Info->size[2];
  e_res_full_Info->size[0] = Rise->size[1];
  e_res_full_Info->size[1] = 2;
  e_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)e_res_full_Info, i0, sizeof(double));
  emxFree_real_T(&d_res_full_Info);
  for (i0 = 0; i0 < 2; i0++) {
    for (n = 0; n < 2; n++) {
      k = Rise->size[1];
      for (nm1d2 = 0; nm1d2 < k; nm1d2++) {
        e_res_full_Info->data[(nm1d2 + e_res_full_Info->size[0] * n) +
          e_res_full_Info->size[0] * e_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Rise->data[Rise->size[0] * nm1d2] +
          res_full_Info->size[0] * n) + res_full_Info->size[0] *
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
  k = Rise->size[1];
  emxFree_real_T(&e_res_full_Info);
  for (i0 = 0; i0 < k; i0++) {
    for (n = 0; n < 2; n++) {
      b_res_full_xi->data[n + b_res_full_xi->size[0] * i0] = res_full_xi->data[n
        + res_full_xi->size[0] * ((int)Rise->data[Rise->size[0] * i0] - 1)];
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
    for (n = 0; n < 2; n++) {
      k = Flattop->size[1];
      for (nm1d2 = 0; nm1d2 < k; nm1d2++) {
        f_res_full_Info->data[(nm1d2 + f_res_full_Info->size[0] * n) +
          f_res_full_Info->size[0] * f_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Flattop->data[Flattop->size[0] * nm1d2] +
          res_full_Info->size[0] * n) + res_full_Info->size[0] *
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
  k = Flattop->size[1];
  emxFree_real_T(&f_res_full_Info);
  for (i0 = 0; i0 < k; i0++) {
    for (n = 0; n < 2; n++) {
      c_res_full_xi->data[n + c_res_full_xi->size[0] * i0] = res_full_xi->data[n
        + res_full_xi->size[0] * ((int)Flattop->data[Flattop->size[0] * i0] - 1)];
    }
  }

  emxFree_real_T(&Flattop);
  emxInit_real_T1(&g_res_full_Info, 3);
  b_sum(c_res_full_xi, b_A);
  i0 = g_res_full_Info->size[0] * g_res_full_Info->size[1] *
    g_res_full_Info->size[2];
  g_res_full_Info->size[0] = Decay->size[1];
  g_res_full_Info->size[1] = 2;
  g_res_full_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)g_res_full_Info, i0, sizeof(double));
  emxFree_real_T(&c_res_full_xi);
  for (i0 = 0; i0 < 2; i0++) {
    for (n = 0; n < 2; n++) {
      k = Decay->size[1];
      for (nm1d2 = 0; nm1d2 < k; nm1d2++) {
        g_res_full_Info->data[(nm1d2 + g_res_full_Info->size[0] * n) +
          g_res_full_Info->size[0] * g_res_full_Info->size[1] * i0] =
          res_full_Info->data[(((int)Decay->data[Decay->size[0] * nm1d2] +
          res_full_Info->size[0] * n) + res_full_Info->size[0] *
          res_full_Info->size[1] * i0) - 1];
      }
    }
  }

  emxFree_real_T(&res_full_Info);
  emxInit_real_T(&d_res_full_xi, 2);
  sum(g_res_full_Info, d_x);
  c_mldivide(d_x, dv1, c_a);
  i0 = d_res_full_xi->size[0] * d_res_full_xi->size[1];
  d_res_full_xi->size[0] = 2;
  d_res_full_xi->size[1] = Decay->size[1];
  emxEnsureCapacity((emxArray__common *)d_res_full_xi, i0, sizeof(double));
  k = Decay->size[1];
  emxFree_real_T(&g_res_full_Info);
  for (i0 = 0; i0 < k; i0++) {
    for (n = 0; n < 2; n++) {
      d_res_full_xi->data[n + d_res_full_xi->size[0] * i0] = res_full_xi->data[n
        + res_full_xi->size[0] * ((int)Decay->data[Decay->size[0] * i0] - 1)];
    }
  }

  emxFree_real_T(&res_full_xi);
  emxFree_real_T(&Decay);
  b_sum(d_res_full_xi, c_A);
  emxFree_real_T(&d_res_full_xi);
  for (i0 = 0; i0 < 2; i0++) {
    d_a[i0] = 0.0;
    e_a[i0] = 0.0;
    f_a[i0] = 0.0;
    for (n = 0; n < 2; n++) {
      d_a[i0] += a[i0 + (n << 1)] * A[n];
      e_a[i0] += b_a[i0 + (n << 1)] * b_A[n];
      f_a[i0] += c_a[i0 + (n << 1)] * c_A[n];
    }

    residual_ukf_mean[i0] = d_a[i0];
    residual_ukf_mean[2 + i0] = e_a[i0];
    residual_ukf_mean[4 + i0] = f_a[i0];
  }

  /*      Y_MC(:, 2:end) = Y_MC(:, 1:end-1); */
  /*      Y_MC(:, 1) = y_mC; */
  /*      U_MC(:, 2:end) = U_MC(:, 1:end-1); */
  /*      U_MC(:, 1) = u_mCal; */
  /*      R_MC(:, 2:end) = R_MC(:, 1:end-1); */
  /*      R_MC(:, 1) = r_mCal; */
  /*  */
  /*      if abs(residual1(pNum,1)) > 3e-6 || abs(residual1(pNum,2)) > 3e-6 || abs(residual1(pNum,3)) > 4e-6 */
  /*          state_of_sys(2:end) = state_of_sys(1:end-1); */
  /*          state_of_sys(1) = {'fault'}; */
  /*          if iterSwitch == 0 */
  /*          iterSwitch = 1; */
  /*          iter = 0; */
  /*          pNum */
  /*          end */
  /*      else */
  /*          state_of_sys(2:end) = state_of_sys(1:end-1); */
  /*          state_of_sys(1) = {'nominal'}; */
  /*      end */
  /*  */
  /*      if iterSwitch == 1 */
  /*          iter = iter +1; */
  /*      end */
  /*      if iter == 5 */
  /*          save('fault_data.mat','U_MC','Y_MC','R_MC') */
  /*          iterSwitch = 0; */
  /*          iter = 0; */
  /*      end */
  /*      pNum = pNum +1; */
  /*  */
}

/*
 * File trailer for f_calib_and_res_gen_ukf.c
 *
 * [EOF]
 */
