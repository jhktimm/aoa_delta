/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_compute_ukf_residual_not_pers.c
 *
 * Code generation for function 'f_compute_ukf_residual_not_pers'
 *
 */

/* Include files */
#include "f_compute_ukf_residual_not_pers.h"
#include "UnscentedKalmanFilter.h"
#include "calcSigmaPoints.h"
#include "f_cavitySystem.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_data.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "isSymmetricPositiveSemiDefinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void f_compute_ukf_residual_not_pers(const double initialStateGuess[6], const
  double MeasNoiseVar[4], const double ProcessVar[36], const emxArray_real_T
  *y_Meas, const emxArray_real_T *u_Meas, double fs, double QL, const double
  tau_m[4], const double K_m[4], emxArray_real_T *residual_mean, emxArray_real_T
  *residual_Variance, emxArray_real_T *residual_xi, emxArray_real_T
  *residual_Info)
{
  unscentedKalmanFilter ukf;
  int i;
  int b_i;
  int k;
  double tempY[6];
  boolean_T exitg1;
  double a21;
  int r1;
  double d;
  int i1;
  int i2;
  double b_d[6];
  double PCorrected[36];
  double y_tmp[4];
  double b_y_tmp[12];
  double A[4];
  static const signed char b_iv[12] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };

  double a22_tmp;
  double a22;
  static const signed char B[4] = { 1, 0, 0, 1 };

  double c;
  double a_idx_0;
  double a_idx_1;
  double X2state[72];
  double Y2[72];
  double b_Y2[36];

  /*  */
  /*  Initialize the object. */
  /*  % State transition function */
  /*  % Measurement function */
  ukf.pIsFirstCallPredict = true;
  ukf.pIsFirstCallCorrect = true;
  for (i = 0; i < 6; i++) {
    ukf.pState[i] = initialStateGuess[i];
  }

  for (b_i = 0; b_i < 36; b_i++) {
    ukf.pStateCovariance[b_i] = iv[b_i];
  }

  ukf.pIsSetStateCovariance = true;
  ukf.pStateCovarianceScalar = -1.0;
  ukf.pIsValidMeasurementFcn = false;
  ukf.pIsValidStateTransitionFcn = false;
  ukf.Beta = 2.0;
  ukf.Kappa = 0.0;

  /*  Construct the filter */
  isSymmetricPositiveSemiDefinite(MeasNoiseVar);
  ukf.pMeasurementNoise[0] = MeasNoiseVar[0];
  ukf.pMeasurementNoise[1] = MeasNoiseVar[1];
  ukf.pMeasurementNoise[2] = MeasNoiseVar[2];
  ukf.pMeasurementNoise[3] = MeasNoiseVar[3];
  ukf.pIsSetMeasurementNoise = true;
  ukf.pMeasurementNoiseScalar = -1.0;
  for (k = 0; k < 6; k++) {
    tempY[k] = fabs(ProcessVar[k + 6 * k]);
  }

  if (!rtIsNaN(tempY[0])) {
    i = 1;
  } else {
    i = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 6)) {
      if (!rtIsNaN(tempY[k - 1])) {
        i = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (i == 0) {
    a21 = tempY[0];
  } else {
    a21 = tempY[i - 1];
    b_i = i + 1;
    for (k = b_i; k < 7; k++) {
      d = tempY[k - 1];
      if (a21 < d) {
        a21 = d;
      }
    }
  }

  if ((!rtIsInf(a21)) && (!rtIsNaN(a21)) && (!(a21 <= 2.2250738585072014E-308)))
  {
    frexp(a21, &r1);
  }

  memcpy(&ukf.pProcessNoise[0], &ProcessVar[0], 36U * sizeof(double));
  ukf.pIsSetProcessNoise = true;
  ukf.pProcessNoiseScalar = -1.0;
  ukf.Alpha = 0.01;

  /*  end */
  b_i = residual_mean->size[0] * residual_mean->size[1];
  residual_mean->size[0] = 2;
  residual_mean->size[1] = y_Meas->size[1];
  emxEnsureCapacity_real_T(residual_mean, b_i);
  i = y_Meas->size[1] << 1;
  for (b_i = 0; b_i < i; b_i++) {
    residual_mean->data[b_i] = 0.0;
  }

  b_i = residual_Variance->size[0] * residual_Variance->size[1] *
    residual_Variance->size[2];
  residual_Variance->size[0] = y_Meas->size[1];
  residual_Variance->size[1] = 2;
  residual_Variance->size[2] = 2;
  emxEnsureCapacity_real_T(residual_Variance, b_i);
  b_i = residual_Info->size[0] * residual_Info->size[1] * residual_Info->size[2];
  residual_Info->size[0] = y_Meas->size[1];
  residual_Info->size[1] = 2;
  residual_Info->size[2] = 2;
  emxEnsureCapacity_real_T(residual_Info, b_i);
  b_i = residual_xi->size[0] * residual_xi->size[1];
  residual_xi->size[0] = 2;
  residual_xi->size[1] = y_Meas->size[1];
  emxEnsureCapacity_real_T(residual_xi, b_i);
  b_i = y_Meas->size[1];
  for (k = 0; k < b_i; k++) {
    /*  Let k denote the current time. */
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
    for (i1 = 0; i1 < 2; i1++) {
      d = 0.0;
      for (i2 = 0; i2 < 6; i2++) {
        d += (double)iv1[i1 + (i2 << 1)] * ukf.pState[i2];
      }

      i2 = i1 + 2 * k;
      residual_mean->data[i2] = y_Meas->data[i2] - d;
    }

    /*  ukf.State is x[k|k-1] at this point */
    /*  Incorporate the measurements at time k into the state estimates by */
    /*  using the "correct" command. This updates the State and StateCovariance */
    /*  properties of the filter to contain x[k|k] and P[k|k]. These values */
    /*  are also produced as the output of the "correct" command. */
    UnscentedKalmanFilter_correct(&ukf, *(double (*)[2])&y_Meas->data[2 * k],
      b_d, PCorrected);

    /*  Predict the states at next time step, k+1. This updates the State and */
    /*  StateCovariance properties of the filter to contain x[k+1|k] and */
    /*  P[k+1|k]. These will be utilized by the filter at the next time step. */
    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 6; i2++) {
        d = 0.0;
        for (i = 0; i < 6; i++) {
          d += (double)iv1[i1 + (i << 1)] * PCorrected[i + 6 * i2];
        }

        b_y_tmp[i1 + (i2 << 1)] = d;
      }

      for (i2 = 0; i2 < 2; i2++) {
        d = 0.0;
        for (i = 0; i < 6; i++) {
          d += b_y_tmp[i1 + (i << 1)] * (double)b_iv[i + 6 * i2];
        }

        i = i1 + (i2 << 1);
        y_tmp[i] = d + MeasNoiseVar[i];
      }
    }

    residual_Variance->data[k] = y_tmp[0];
    residual_Variance->data[k + residual_Variance->size[0]] = y_tmp[1];
    residual_Variance->data[k + residual_Variance->size[0] * 2] = y_tmp[2];
    residual_Variance->data[(k + residual_Variance->size[0]) +
      residual_Variance->size[0] * 2] = y_tmp[3];
    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        d = 0.0;
        for (i = 0; i < 6; i++) {
          d += b_y_tmp[i1 + (i << 1)] * (double)b_iv[i + 6 * i2];
        }

        i = i1 + (i2 << 1);
        A[i] = d + MeasNoiseVar[i];
      }
    }

    if (fabs(A[1]) > fabs(A[0])) {
      r1 = 1;
      i = 0;
    } else {
      r1 = 0;
      i = 1;
    }

    a21 = A[i] / A[r1];
    a22_tmp = A[r1 + 2];
    a22 = A[i + 2] - a21 * a22_tmp;
    d = ((double)B[i] - (double)B[r1] * a21) / a22;
    residual_Info->data[k] = ((double)B[r1] - d * a22_tmp) / A[r1];
    residual_Info->data[k + residual_Info->size[0]] = d;
    i1 = B[r1 + 2];
    d = ((double)B[i + 2] - (double)i1 * a21) / a22;
    residual_Info->data[k + residual_Info->size[0] * 2] = ((double)i1 - d *
      a22_tmp) / A[r1];
    residual_Info->data[(k + residual_Info->size[0]) + residual_Info->size[0] *
      2] = d;
    for (i1 = 0; i1 < 2; i1++) {
      for (i2 = 0; i2 < 2; i2++) {
        d = 0.0;
        for (i = 0; i < 6; i++) {
          d += b_y_tmp[i1 + (i << 1)] * (double)b_iv[i + 6 * i2];
        }

        i = i1 + (i2 << 1);
        A[i] = d + MeasNoiseVar[i];
      }
    }

    if (fabs(A[1]) > fabs(A[0])) {
      r1 = 1;
      i = 0;
    } else {
      r1 = 0;
      i = 1;
    }

    a21 = A[i] / A[r1];
    a22_tmp = A[r1 + 2];
    a22 = A[i + 2] - a21 * a22_tmp;
    d = ((double)B[i] - (double)B[r1] * a21) / a22;
    y_tmp[1] = d;
    y_tmp[0] = ((double)B[r1] - d * a22_tmp) / A[r1];
    i1 = B[r1 + 2];
    d = ((double)B[i + 2] - (double)i1 * a21) / a22;
    i2 = 2 * k + 1;
    residual_xi->data[2 * k] = y_tmp[0] * residual_mean->data[2 * k] + ((double)
      i1 - d * a22_tmp) / A[r1] * residual_mean->data[i2];
    residual_xi->data[i2] = y_tmp[1] * residual_mean->data[2 * k] + d *
      residual_mean->data[i2];
    if ((!ukf.pIsSetStateCovariance) || (ukf.pStateCovarianceScalar != -1.0)) {
      for (i1 = 0; i1 < 36; i1++) {
        ukf.pStateCovariance[i1] = ukf.pStateCovarianceScalar * (double)iv[i1];
      }
    }

    if ((!ukf.pIsSetProcessNoise) || (ukf.pProcessNoiseScalar != -1.0)) {
      for (i1 = 0; i1 < 36; i1++) {
        ukf.pProcessNoise[i1] = ukf.pProcessNoiseScalar * (double)iv[i1];
      }

      ukf.pIsSetProcessNoise = true;
      ukf.pProcessNoiseScalar = -1.0;
    }

    if (ukf.pIsFirstCallPredict) {
      if (!ukf.pIsValidStateTransitionFcn) {
        ukf.pIsValidStateTransitionFcn = true;
      }

      ukf.pIsFirstCallPredict = false;
    }

    a21 = ukf.Alpha * ukf.Alpha;
    c = a21 * (ukf.Kappa + 6.0);
    a_idx_0 = 1.0 - 6.0 / c;
    a_idx_1 = 1.0 / (2.0 * c);
    a21 = a_idx_0 + ((1.0 - a21) + ukf.Beta);
    a22_tmp = a_idx_1;
    if (a_idx_0 != 0.0) {
      a22 = a_idx_0;
      d = a_idx_0;
      a_idx_0 /= a_idx_0;
      a21 /= a22;
      a_idx_1 /= d;
      a22_tmp /= a22;
    } else {
      a22 = 1.0;
    }

    for (i = 0; i < 6; i++) {
      b_d[i] = ukf.pState[i];
    }

    calcSigmaPoints(ukf.pStateCovariance, b_d, c, X2state);
    for (r1 = 0; r1 < 12; r1++) {
      f_cavitySystem(*(double (*)[6])&X2state[6 * r1], *(double (*)[2])&
                     u_Meas->data[2 * k], fs, tau_m, K_m, QL, *(double (*)[6])&
                     Y2[6 * r1]);
    }

    f_cavitySystem(b_d, *(double (*)[2])&u_Meas->data[2 * k], fs, tau_m, K_m, QL,
                   tempY);
    for (i = 0; i < 6; i++) {
      b_d[i] = tempY[i] * a_idx_0;
    }

    for (r1 = 0; r1 < 12; r1++) {
      for (i1 = 0; i1 < 6; i1++) {
        b_d[i1] += Y2[i1 + 6 * r1] * a_idx_1;
      }
    }

    for (i1 = 0; i1 < 6; i1++) {
      d = b_d[i1] * a22;
      b_d[i1] = d;
      tempY[i1] -= d;
    }

    for (r1 = 0; r1 < 12; r1++) {
      for (i1 = 0; i1 < 6; i1++) {
        i = i1 + 6 * r1;
        Y2[i] -= b_d[i1];
      }
    }

    for (i = 0; i < 6; i++) {
      ukf.pState[i] = b_d[i];
      for (i1 = 0; i1 < 6; i1++) {
        PCorrected[i1 + 6 * i] = tempY[i1] * tempY[i];
        d = 0.0;
        for (i2 = 0; i2 < 12; i2++) {
          d += Y2[i + 6 * i2] * Y2[i1 + 6 * i2];
        }

        b_Y2[i + 6 * i1] = d;
      }
    }

    for (i1 = 0; i1 < 36; i1++) {
      ukf.pStateCovariance[i1] = a22 * (a21 * PCorrected[i1] + a22_tmp * b_Y2[i1])
        + ukf.pProcessNoise[i1];
    }

    ukf.pIsSetStateCovariance = true;
    ukf.pStateCovarianceScalar = -1.0;
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
  /*   */
  /*   */
}

/* End of code generation (f_compute_ukf_residual_not_pers.c) */
