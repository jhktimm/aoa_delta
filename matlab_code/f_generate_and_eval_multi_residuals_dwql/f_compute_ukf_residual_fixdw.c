/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_compute_ukf_residual_fixdw.c
 *
 * Code generation for function 'f_compute_ukf_residual_fixdw'
 *
 */

/* Include files */
#include "f_compute_ukf_residual_fixdw.h"
#include "calcSigmaPoints.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "isSymmetricPositiveSemiDefinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void f_compute_ukf_residual_fixdw(const double MeasNoiseVar[4], const double
  ProcessVar[4], const emxArray_real_T *y_Meas, const emxArray_real_T *u_Meas,
  double fs, double QL, const emxArray_real_T *dw, emxArray_real_T
  *residual_mean, emxArray_real_T *residual_Variance, emxArray_real_T
  *residual_xi, emxArray_real_T *residual_Info)
{
  double ukf_pState[2];
  double d[4];
  double tempY[2];
  double w12;
  int r2;
  int i;
  double Ts;
  int k;
  double a0;
  double b0;
  double b_Ts;
  double b_a0;
  double b_b0;
  double b_d;
  double X1[2];
  int i1;
  double d1;
  double X2[8];
  double Ymean_idx_0;
  int r1;
  double Ymean_idx_1;
  int i2;
  double Y2[8];
  double y_tmp[8];
  int X2_tmp;
  double b_X2[4];
  double d2;
  double d3;
  double b_tempY[4];
  double b_Y2[4];
  double a22;
  int i3;
  double a22_tmp;
  double Y2_idx_0;
  double d4;
  double gain[4];
  static const signed char value[4] = { 1, 0, 0, 1 };

  /*  */
  /*  Initialize the object. */
  /*  % State transition function */
  /*  % Measurement function */
  ukf_pState[0] = 0.0;
  ukf_pState[1] = 0.0;
  d[0] = 1.0;
  d[1] = 0.0;
  d[2] = 0.0;
  d[3] = 1.0;

  /*  Construct the filter */
  isSymmetricPositiveSemiDefinite(MeasNoiseVar);
  tempY[0] = fabs(ProcessVar[0]);
  tempY[1] = fabs(ProcessVar[3]);
  if ((tempY[0] < tempY[1]) || (rtIsNaN(tempY[0]) && (!rtIsNaN(tempY[1])))) {
    w12 = tempY[1];
  } else {
    w12 = tempY[0];
  }

  if ((!rtIsInf(w12)) && (!rtIsNaN(w12)) && (!(w12 <= 2.2250738585072014E-308)))
  {
    frexp(w12, &r2);
  }

  /*  end */
  i = residual_mean->size[0] * residual_mean->size[1];
  residual_mean->size[0] = 2;
  residual_mean->size[1] = y_Meas->size[1];
  emxEnsureCapacity_real_T(residual_mean, i);
  r2 = y_Meas->size[1] << 1;
  for (i = 0; i < r2; i++) {
    residual_mean->data[i] = 0.0;
  }

  i = residual_Variance->size[0] * residual_Variance->size[1] *
    residual_Variance->size[2];
  residual_Variance->size[0] = y_Meas->size[1];
  residual_Variance->size[1] = 2;
  residual_Variance->size[2] = 2;
  emxEnsureCapacity_real_T(residual_Variance, i);
  i = residual_Info->size[0] * residual_Info->size[1] * residual_Info->size[2];
  residual_Info->size[0] = y_Meas->size[1];
  residual_Info->size[1] = 2;
  residual_Info->size[2] = 2;
  emxEnsureCapacity_real_T(residual_Info, i);
  i = residual_xi->size[0] * residual_xi->size[1];
  residual_xi->size[0] = 2;
  residual_xi->size[1] = y_Meas->size[1];
  emxEnsureCapacity_real_T(residual_xi, i);
  i = y_Meas->size[1];
  if (0 <= y_Meas->size[1] - 1) {
    Ts = 1.0 / fs;
    w12 = 4.0840704496667309E+9 / QL;
    a0 = w12 * Ts + -1.0;
    b0 = 2.0 * w12 * Ts;
    b_Ts = 1.0 / fs;
    w12 = 4.0840704496667309E+9 / QL;
    b_a0 = w12 * b_Ts + -1.0;
    b_b0 = 2.0 * w12 * b_Ts;
  }

  for (k = 0; k < i; k++) {
    /*  Let k denote the current time. */
    /*  */
    /*  Residuals (or innovations): Measured output - Predicted output */
    /*  vdpMeasurementNonAdditiveNoiseFcn Example measurement function for discrete */
    /*  time nonlinear state estimators with non-additive measurement noise. */
    /*  */
    /*  yk = vdpNonAdditiveMeasurementFcn(xk,vk) */
    /*  */
    /*  Inputs: */
    /*     xk - x[k], states at time k */
    /*     vk - v[k], measurement noise at time k */
    /*  */
    /*  Outputs: */
    /*     yk - y[k], measurements at time k */
    /*  */
    /*  The measurement is the first state with multiplicative noise */
    /*  */
    /*  See also extendedKalmanFilter, unscentedKalmanFilter */
    /*    Copyright 2016 The MathWorks, Inc. */
    /*  The tag %#codegen must be included if you wish to generate code with  */
    /*  MATLAB Coder. */
    /*  ukf.State is x[k|k-1] at this point */
    /*  Incorporate the measurements at time k into the state estimates by */
    /*  using the "correct" command. This updates the State and StateCovariance */
    /*  properties of the filter to contain x[k|k] and P[k|k]. These values */
    /*  are also produced as the output of the "correct" command. */
    b_d = ukf_pState[0] + 0.0 * ukf_pState[1];
    residual_mean->data[2 * k] = y_Meas->data[2 * k] - b_d;
    X1[0] = ukf_pState[0];
    i1 = 2 * k + 1;
    d1 = 0.0 * ukf_pState[0] + ukf_pState[1];
    residual_mean->data[i1] = y_Meas->data[i1] - d1;
    X1[1] = ukf_pState[1];
    b_calcSigmaPoints(d, X1, 0.020000000000000004, X2);

    /*  vdpMeasurementNonAdditiveNoiseFcn Example measurement function for discrete */
    /*  time nonlinear state estimators with non-additive measurement noise. */
    /*  */
    /*  yk = vdpNonAdditiveMeasurementFcn(xk,vk) */
    /*  */
    /*  Inputs: */
    /*     xk - x[k], states at time k */
    /*     vk - v[k], measurement noise at time k */
    /*  */
    /*  Outputs: */
    /*     yk - y[k], measurements at time k */
    /*  */
    /*  The measurement is the first state with multiplicative noise */
    /*  */
    /*  See also extendedKalmanFilter, unscentedKalmanFilter */
    /*    Copyright 2016 The MathWorks, Inc. */
    /*  The tag %#codegen must be included if you wish to generate code with  */
    /*  MATLAB Coder. */
    Ymean_idx_0 = b_d;
    w12 = d1;
    for (r1 = 0; r1 < 4; r1++) {
      /*  vdpMeasurementNonAdditiveNoiseFcn Example measurement function for discrete */
      /*  time nonlinear state estimators with non-additive measurement noise. */
      /*  */
      /*  yk = vdpNonAdditiveMeasurementFcn(xk,vk) */
      /*  */
      /*  Inputs: */
      /*     xk - x[k], states at time k */
      /*     vk - v[k], measurement noise at time k */
      /*  */
      /*  Outputs: */
      /*     yk - y[k], measurements at time k */
      /*  */
      /*  The measurement is the first state with multiplicative noise */
      /*  */
      /*  See also extendedKalmanFilter, unscentedKalmanFilter */
      /*    Copyright 2016 The MathWorks, Inc. */
      /*  The tag %#codegen must be included if you wish to generate code with  */
      /*  MATLAB Coder. */
      i2 = r1 << 1;
      i3 = i2 + 1;
      d2 = X2[i2] + 0.0 * X2[i3];
      Y2[i2] = d2;
      d3 = 0.0 * X2[i2] + X2[i3];
      Y2[i3] = d3;
      Ymean_idx_0 += d2 * -0.25252525252525254;
      w12 += d3 * -0.25252525252525254;
    }

    Ymean_idx_1 = Ymean_idx_0 * -98.999999999999986;
    Ymean_idx_0 = Ymean_idx_1;
    tempY[0] = b_d - Ymean_idx_1;
    Ymean_idx_1 = w12 * -98.999999999999986;
    tempY[1] = d1 - Ymean_idx_1;
    for (r1 = 0; r1 < 4; r1++) {
      r2 = r1 << 1;
      Y2[r2] -= Ymean_idx_0;
      r2++;
      Y2[r2] -= Ymean_idx_1;
    }

    for (i2 = 0; i2 < 2; i2++) {
      r2 = i2 << 2;
      y_tmp[r2] = Y2[i2];
      y_tmp[r2 + 1] = Y2[i2 + 2];
      y_tmp[r2 + 2] = Y2[i2 + 4];
      y_tmp[r2 + 3] = Y2[i2 + 6];
    }

    for (r1 = 0; r1 < 4; r1++) {
      X2_tmp = r1 << 1;
      X2[X2_tmp] -= X1[0];
      X2_tmp++;
      X2[X2_tmp] -= X1[1];
    }

    for (i2 = 0; i2 < 2; i2++) {
      b_d = X2[i2 + 2];
      d1 = X2[i2 + 4];
      d2 = X2[i2 + 6];
      d3 = Y2[i2 + 2];
      w12 = Y2[i2 + 4];
      a22 = Y2[i2 + 6];
      for (i3 = 0; i3 < 2; i3++) {
        r2 = i3 << 2;
        a22_tmp = y_tmp[r2 + 1];
        Y2_idx_0 = y_tmp[r2 + 2];
        d4 = y_tmp[r2 + 3];
        X2_tmp = i2 + (i3 << 1);
        b_X2[X2_tmp] = ((X2[i2] * y_tmp[r2] + b_d * a22_tmp) + d1 * Y2_idx_0) +
          d2 * d4;
        b_tempY[i3 + (i2 << 1)] = tempY[i3] * tempY[i2];
        b_Y2[X2_tmp] = ((Y2[i2] * y_tmp[r2] + d3 * a22_tmp) + w12 * Y2_idx_0) +
          a22 * d4;
      }
    }

    b_X2[0] *= 24.999999999999996;
    b_X2[1] *= 24.999999999999996;
    b_X2[2] *= 24.999999999999996;
    b_X2[3] *= 24.999999999999996;
    b_tempY[0] = -98.999999999999986 * (0.96979797979797988 * b_tempY[0] +
      -0.25252525252525254 * b_Y2[0]) + MeasNoiseVar[0];
    b_tempY[1] = -98.999999999999986 * (0.96979797979797988 * b_tempY[1] +
      -0.25252525252525254 * b_Y2[1]) + MeasNoiseVar[1];
    b_tempY[2] = -98.999999999999986 * (0.96979797979797988 * b_tempY[2] +
      -0.25252525252525254 * b_Y2[2]) + MeasNoiseVar[2];
    b_tempY[3] = -98.999999999999986 * (0.96979797979797988 * b_tempY[3] +
      -0.25252525252525254 * b_Y2[3]) + MeasNoiseVar[3];
    if (fabs(b_tempY[1]) > fabs(b_tempY[0])) {
      r1 = 1;
      r2 = 0;
    } else {
      r1 = 0;
      r2 = 1;
    }

    w12 = b_tempY[r2] / b_tempY[r1];
    a22_tmp = b_tempY[r1 + 2];
    a22 = b_tempY[r2 + 2] - w12 * a22_tmp;
    X2_tmp = r1 << 1;
    gain[X2_tmp] = b_X2[0] / b_tempY[r1];
    r2 <<= 1;
    gain[r2] = (b_X2[2] - gain[X2_tmp] * a22_tmp) / a22;
    gain[X2_tmp] -= gain[r2] * w12;
    Y2_idx_0 = y_Meas->data[2 * k] - Ymean_idx_0;
    X2_tmp++;
    gain[X2_tmp] = b_X2[1] / b_tempY[r1];
    r2++;
    gain[r2] = (b_X2[3] - gain[X2_tmp] * a22_tmp) / a22;
    gain[X2_tmp] -= gain[r2] * w12;
    w12 = y_Meas->data[i1] - Ymean_idx_1;
    for (i2 = 0; i2 < 2; i2++) {
      b_d = gain[i2 + 2];
      d1 = gain[i2] * b_tempY[0] + b_d * b_tempY[1];
      d2 = gain[i2] * b_tempY[2] + b_d * b_tempY[3];
      X1[i2] = ukf_pState[i2] + (gain[i2] * Y2_idx_0 + b_d * w12);
      d[i2] -= d1 * gain[0] + d2 * gain[2];
      d[i2 + 2] -= d1 * gain[1] + d2 * gain[3];
    }

    /*  Predict the states at next time step, k+1. This updates the State and */
    /*  StateCovariance properties of the filter to contain x[k+1|k] and */
    /*  P[k+1|k]. These will be utilized by the filter at the next time step. */
    for (i2 = 0; i2 < 2; i2++) {
      i3 = value[i2 + 2];
      b_d = (double)value[i2] * d[0] + (double)i3 * d[1];
      b_X2[i2] = b_d;
      d1 = (double)value[i2] * d[2] + (double)i3 * d[3];
      b_X2[i2 + 2] = d1;
      b_Y2[i2] = (b_d + d1 * 0.0) + MeasNoiseVar[i2];
      d2 = MeasNoiseVar[i2 + 2];
      b_Y2[i2 + 2] = (b_d * 0.0 + d1) + d2;
      gain[i2] = (b_d + d1 * 0.0) + MeasNoiseVar[i2];
      gain[i2 + 2] = (b_d * 0.0 + d1) + d2;
    }

    residual_Variance->data[k] = b_Y2[0];
    residual_Variance->data[k + residual_Variance->size[0]] = b_Y2[1];
    residual_Variance->data[k + residual_Variance->size[0] * 2] = b_Y2[2];
    residual_Variance->data[(k + residual_Variance->size[0]) +
      residual_Variance->size[0] * 2] = b_Y2[3];
    if (fabs(gain[1]) > fabs(gain[0])) {
      r1 = 1;
      r2 = 0;
    } else {
      r1 = 0;
      r2 = 1;
    }

    w12 = gain[r2] / gain[r1];
    a22_tmp = gain[r1 + 2];
    a22 = gain[r2 + 2] - w12 * a22_tmp;
    b_d = ((double)value[r2] - (double)value[r1] * w12) / a22;
    residual_Info->data[k] = ((double)value[r1] - b_d * a22_tmp) / gain[r1];
    residual_Info->data[k + residual_Info->size[0]] = b_d;
    i2 = value[r1 + 2];
    b_d = ((double)value[r2 + 2] - (double)i2 * w12) / a22;
    residual_Info->data[k + residual_Info->size[0] * 2] = ((double)i2 - b_d *
      a22_tmp) / gain[r1];
    residual_Info->data[(k + residual_Info->size[0]) + residual_Info->size[0] *
      2] = b_d;
    for (i2 = 0; i2 < 2; i2++) {
      b_d = b_X2[i2 + 2];
      gain[i2] = (b_X2[i2] + b_d * 0.0) + MeasNoiseVar[i2];
      gain[i2 + 2] = (b_X2[i2] * 0.0 + b_d) + MeasNoiseVar[i2 + 2];
    }

    if (fabs(gain[1]) > fabs(gain[0])) {
      r1 = 1;
      r2 = 0;
    } else {
      r1 = 0;
      r2 = 1;
    }

    w12 = gain[r2] / gain[r1];
    a22_tmp = gain[r1 + 2];
    a22 = gain[r2 + 2] - w12 * a22_tmp;
    b_d = ((double)value[r2] - (double)value[r1] * w12) / a22;
    b_tempY[1] = b_d;
    b_tempY[0] = ((double)value[r1] - b_d * a22_tmp) / gain[r1];
    i2 = value[r1 + 2];
    b_d = ((double)value[r2 + 2] - (double)i2 * w12) / a22;
    Y2_idx_0 = dw->data[k];
    residual_xi->data[2 * k] = b_tempY[0] * residual_mean->data[2 * k] +
      ((double)i2 - b_d * a22_tmp) / gain[r1] * residual_mean->data[i1];
    residual_xi->data[i1] = b_tempY[1] * residual_mean->data[2 * k] + b_d *
      residual_mean->data[i1];
    b_calcSigmaPoints(d, X1, 0.020000000000000004, X2);

    /*  Coupled simulink model */
    /*  ------------- Discrete State Space System ----------------------- */
    /*  ---------- Values--------- */
    w12 = (-b_a0 * X1[0] - dw->data[k] * X1[1] * b_Ts) + b_b0 * u_Meas->data[2 *
      k];
    a22 = (dw->data[k] * X1[0] * b_Ts - b_a0 * X1[1]) + b_b0 * u_Meas->data[i1];
    b_d = w12;
    d1 = a22;
    for (r1 = 0; r1 < 4; r1++) {
      /*  Coupled simulink model */
      /*  ------------- Discrete State Space System ----------------------- */
      /*  ---------- Values--------- */
      i2 = r1 << 1;
      i3 = i2 + 1;
      d2 = (-a0 * X2[i2] - Y2_idx_0 * X2[i3] * Ts) + b0 * u_Meas->data[2 * k];
      Y2[i2] = d2;
      d3 = (Y2_idx_0 * X2[i2] * Ts - a0 * X2[i3]) + b0 * u_Meas->data[i1];
      Y2[i3] = d3;
      b_d += d2 * -0.25252525252525254;
      d1 += d3 * -0.25252525252525254;
    }

    b_d *= -98.999999999999986;
    X1[0] = b_d;
    tempY[0] = w12 - b_d;
    b_d = d1 * -98.999999999999986;
    X1[1] = b_d;
    tempY[1] = a22 - b_d;
    for (r1 = 0; r1 < 4; r1++) {
      r2 = r1 << 1;
      Y2[r2] -= X1[0];
      r2++;
      Y2[r2] -= b_d;
    }

    for (r2 = 0; r2 < 2; r2++) {
      ukf_pState[r2] = X1[r2];
      for (i1 = 0; i1 < 2; i1++) {
        d[i1 + (r2 << 1)] = tempY[i1] * tempY[r2];
        b_Y2[r2 + (i1 << 1)] = ((Y2[r2] * Y2[i1] + Y2[r2 + 2] * Y2[i1 + 2]) +
          Y2[r2 + 4] * Y2[i1 + 4]) + Y2[r2 + 6] * Y2[i1 + 6];
      }
    }

    d[0] = -98.999999999999986 * (0.96979797979797988 * d[0] +
      -0.25252525252525254 * b_Y2[0]) + ProcessVar[0];
    d[1] = -98.999999999999986 * (0.96979797979797988 * d[1] +
      -0.25252525252525254 * b_Y2[1]) + ProcessVar[1];
    d[2] = -98.999999999999986 * (0.96979797979797988 * d[2] +
      -0.25252525252525254 * b_Y2[2]) + ProcessVar[2];
    d[3] = -98.999999999999986 * (0.96979797979797988 * d[3] +
      -0.25252525252525254 * b_Y2[3]) + ProcessVar[3];
  }

  /*  clear ukf */
  /*  C_full = repmat(C, [Nsamples, 1, Nstates]); */
  /*  MeasNoiseVar_full = repmat(MeasNoiseVar,[Nsamples, Noutput, Noutput]); */
  /*  figure(2323) */
  /*  plot(sum(xCorrectedUKF(:,3:end),2)) */
  /*   */
  /*  %residual_Variance = PCorrected + MeasNoiseVar; */
  /*  figure(23) */
  /*  subplot(3,1,1) */
  /*  plot(xCorrectedUKF(:,1), 'g--', 'linewidth', 2.2) */
  /*  hold on */
  /*  plot(y_Meas(1,:), 'k') */
  /*  subplot(3,1,2) */
  /*  plot(xCorrectedUKF(:,2), 'g--', 'linewidth', 2.2) */
  /*  hold on */
  /*  plot(y_Meas(2,:), 'k') */
  /*  subplot(3,1,3) */
  /*  hold on */
  /*  plot(residual_mean(100:end).') */
}

/* End of code generation (f_compute_ukf_residual_fixdw.c) */
