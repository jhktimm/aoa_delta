/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_ukf_residual_not_pers.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 24-Sep-2019 18:29:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_compute_ukf_residual_not_pers.h"
#include "f_cavitySystem.h"
#include "calcSigmaPoints.h"
#include "calcUTParameters.h"
#include "mldivide.h"
#include "f_generate_and_eval_residual_emxutil.h"
#include "isSymmetricPositiveSemiDefinite.h"
#include "UnscentedKalmanFilter1.h"
#include "unscentedKalmanFilter.h"
#include "f_generate_and_eval_residual_data.h"

/* Function Definitions */

/*
 * Arguments    : const double initialStateGuess[6]
 *                const double MeasNoiseVar[4]
 *                const double ProcessVar[36]
 *                const emxArray_real_T *y_Meas
 *                const emxArray_real_T *u_Meas
 *                double fs
 *                double QL
 *                const double tau_m[4]
 *                const double K_m[4]
 *                emxArray_real_T *residual_mean
 *                emxArray_real_T *residual_Variance
 *                emxArray_real_T *residual_xi
 *                emxArray_real_T *residual_Info
 * Return Type  : void
 */
void f_compute_ukf_residual_not_pers(const double initialStateGuess[6], const
  double MeasNoiseVar[4], const double ProcessVar[36], const emxArray_real_T
  *y_Meas, const emxArray_real_T *u_Meas, double fs, double QL, const double
  tau_m[4], const double K_m[4], emxArray_real_T *residual_mean, emxArray_real_T
  *residual_Variance, emxArray_real_T *residual_xi, emxArray_real_T
  *residual_Info)
{
  unscentedKalmanFilter ukf;
  int k;
  int i;
  int b_k;
  double value[6];
  double a21;
  int r2;
  double yk[2];
  static const signed char a[12] = { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

  double zcov[4];
  double P[36];
  double a22;
  double kappa;
  double c;
  double Wcov[2];
  double OOM;
  double X2[72];
  double Ymean[2];
  double Y2[24];
  double tempY[2];
  double b_X2[12];
  double Pyy[4];
  double Pxy[12];
  double b_tempY[4];
  double b_Y2[4];
  double gain[12];
  static const signed char b[12] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };

  double Q[36];
  double c_tempY[6];
  double c_Y2[72];
  double d_Y2[36];

  /*  Initialize the object. */
  /*  % State transition function */
  /*  % Measurement function */
  c_unscentedKalmanFilter_unscent(&ukf, initialStateGuess);

  /*  Construct the filter */
  c_UnscentedKalmanFilter_set_Mea(&ukf, MeasNoiseVar);
  b_isSymmetricPositiveSemiDefini(ProcessVar);
  memcpy(&ukf.pProcessNoise[0], &ProcessVar[0], 36U * sizeof(double));
  ukf.Alpha = 0.01;

  /*  end */
  k = residual_mean->size[0] * residual_mean->size[1];
  residual_mean->size[0] = 2;
  residual_mean->size[1] = y_Meas->size[1];
  emxEnsureCapacity_real_T(residual_mean, k);
  i = y_Meas->size[1] << 1;
  for (k = 0; k < i; k++) {
    residual_mean->data[k] = 0.0;
  }

  k = residual_Variance->size[0] * residual_Variance->size[1] *
    residual_Variance->size[2];
  residual_Variance->size[0] = y_Meas->size[1];
  residual_Variance->size[1] = 2;
  residual_Variance->size[2] = 2;
  emxEnsureCapacity_real_T2(residual_Variance, k);
  k = residual_Info->size[0] * residual_Info->size[1] * residual_Info->size[2];
  residual_Info->size[0] = y_Meas->size[1];
  residual_Info->size[1] = 2;
  residual_Info->size[2] = 2;
  emxEnsureCapacity_real_T2(residual_Info, k);
  k = residual_xi->size[0] * residual_xi->size[1];
  residual_xi->size[0] = 2;
  residual_xi->size[1] = y_Meas->size[1];
  emxEnsureCapacity_real_T(residual_xi, k);
  for (b_k = 0; b_k < y_Meas->size[1]; b_k++) {
    /*  Let k denote the current time. */
    /*  */
    /*  Residuals (or innovations): Measured output - Predicted output */
    for (i = 0; i < 6; i++) {
      value[i] = ukf.pState[i];
    }

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
    for (k = 0; k < 2; k++) {
      a21 = 0.0;
      for (r2 = 0; r2 < 6; r2++) {
        a21 += (double)a[k + (r2 << 1)] * value[r2];
      }

      yk[k] = a21;
    }

    for (k = 0; k < 2; k++) {
      residual_mean->data[k + residual_mean->size[0] * b_k] = y_Meas->data[k +
        y_Meas->size[0] * b_k] - yk[k];
    }

    /*  ukf.State is x[k|k-1] at this point */
    /*  Incorporate the measurements at time k into the state estimates by */
    /*  using the "correct" command. This updates the State and StateCovariance */
    /*  properties of the filter to contain x[k|k] and P[k|k]. These values */
    /*  are also produced as the output of the "correct" command. */
    if (!ukf.pIsValidMeasurementFcn) {
      ukf.pIsValidMeasurementFcn = true;
    }

    for (k = 0; k < 4; k++) {
      zcov[k] = ukf.pMeasurementNoise[k];
    }

    for (i = 0; i < 6; i++) {
      value[i] = ukf.pState[i];
    }

    memcpy(&P[0], &ukf.pStateCovariance[0], 36U * sizeof(double));
    a21 = ukf.Alpha;
    a22 = ukf.Beta;
    kappa = ukf.Kappa;
    calcUTParameters(a21, a22, kappa, &c, yk, Wcov, &OOM);
    calcSigmaPoints(P, value, c, X2);
    for (i = 0; i < 12; i++) {
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
      for (k = 0; k < 2; k++) {
        a21 = 0.0;
        for (r2 = 0; r2 < 6; r2++) {
          a21 += (double)a[k + (r2 << 1)] * X2[r2 + 6 * i];
        }

        Y2[k + (i << 1)] = a21;
        tempY[k] = a21;
      }
    }

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
    for (i = 0; i < 2; i++) {
      a21 = 0.0;
      for (k = 0; k < 6; k++) {
        a21 += (double)a[i + (k << 1)] * value[k];
      }

      Ymean[i] = a21 * yk[0];
      tempY[i] = a21;
    }

    for (i = 0; i < 12; i++) {
      for (k = 0; k < 2; k++) {
        Ymean[k] += Y2[k + (i << 1)] * yk[1];
      }
    }

    for (k = 0; k < 2; k++) {
      a21 = Ymean[k] * OOM;
      Ymean[k] = a21;
      tempY[k] -= a21;
    }

    for (i = 0; i < 12; i++) {
      for (k = 0; k < 2; k++) {
        Y2[k + (i << 1)] -= Ymean[k];
      }

      for (k = 0; k < 6; k++) {
        X2[k + 6 * i] -= value[k];
      }
    }

    a21 = Wcov[1] * OOM;
    for (k = 0; k < 6; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        b_X2[k + 6 * r2] = 0.0;
        for (i = 0; i < 12; i++) {
          b_X2[k + 6 * r2] += X2[k + 6 * i] * Y2[r2 + (i << 1)];
        }
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 6; r2++) {
        Pxy[r2 + 6 * k] = b_X2[r2 + 6 * k] * a21;
      }

      for (r2 = 0; r2 < 2; r2++) {
        b_tempY[k + (r2 << 1)] = tempY[k] * tempY[r2];
        b_Y2[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 12; i++) {
          b_Y2[k + (r2 << 1)] += Y2[k + (i << 1)] * Y2[r2 + (i << 1)];
        }
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        Pyy[r2 + (k << 1)] = OOM * (Wcov[0] * b_tempY[r2 + (k << 1)] + Wcov[1] *
          b_Y2[r2 + (k << 1)]) + zcov[r2 + (k << 1)];
      }
    }

    if (fabs(Pyy[1]) > fabs(Pyy[0])) {
      i = 1;
      r2 = 0;
    } else {
      i = 0;
      r2 = 1;
    }

    a21 = Pyy[r2] / Pyy[i];
    a22 = Pyy[2 + r2] - a21 * Pyy[2 + i];
    for (k = 0; k < 6; k++) {
      gain[k + 6 * i] = Pxy[k] / Pyy[i];
      gain[k + 6 * r2] = (Pxy[6 + k] - gain[k + 6 * i] * Pyy[2 + i]) / a22;
      gain[k + 6 * i] -= gain[k + 6 * r2] * a21;
    }

    for (k = 0; k < 2; k++) {
      yk[k] = y_Meas->data[k + y_Meas->size[0] * b_k] - Ymean[k];
    }

    for (k = 0; k < 6; k++) {
      a21 = 0.0;
      for (r2 = 0; r2 < 2; r2++) {
        a21 += gain[k + 6 * r2] * yk[r2];
        b_X2[k + 6 * r2] = 0.0;
        for (i = 0; i < 2; i++) {
          b_X2[k + 6 * r2] += gain[k + 6 * i] * Pyy[i + (r2 << 1)];
        }
      }

      for (r2 = 0; r2 < 6; r2++) {
        a22 = 0.0;
        for (i = 0; i < 2; i++) {
          a22 += b_X2[k + 6 * i] * gain[r2 + 6 * i];
        }

        P[k + 6 * r2] -= a22;
      }

      value[k] += a21;
    }

    for (i = 0; i < 6; i++) {
      ukf.pState[i] = value[i];
    }

    memcpy(&ukf.pStateCovariance[0], &P[0], 36U * sizeof(double));
    memcpy(&P[0], &ukf.pStateCovariance[0], 36U * sizeof(double));

    /*  Predict the states at next time step, k+1. This updates the State and */
    /*  StateCovariance properties of the filter to contain x[k+1|k] and */
    /*  P[k+1|k]. These will be utilized by the filter at the next time step. */
    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 6; r2++) {
        b_X2[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 6; i++) {
          b_X2[k + (r2 << 1)] += (double)a[k + (i << 1)] * P[i + 6 * r2];
        }
      }

      for (r2 = 0; r2 < 2; r2++) {
        a21 = 0.0;
        for (i = 0; i < 6; i++) {
          a21 += b_X2[k + (i << 1)] * (double)b[i + 6 * r2];
        }

        b_tempY[k + (r2 << 1)] = a21 + MeasNoiseVar[k + (r2 << 1)];
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        residual_Variance->data[(b_k + residual_Variance->size[0] * r2) +
          residual_Variance->size[0] * residual_Variance->size[1] * k] =
          b_tempY[r2 + (k << 1)];
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 6; r2++) {
        b_X2[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 6; i++) {
          b_X2[k + (r2 << 1)] += (double)a[k + (i << 1)] * P[i + 6 * r2];
        }
      }

      for (r2 = 0; r2 < 2; r2++) {
        a21 = 0.0;
        for (i = 0; i < 6; i++) {
          a21 += b_X2[k + (i << 1)] * (double)b[i + 6 * r2];
        }

        b_tempY[k + (r2 << 1)] = a21 + MeasNoiseVar[k + (r2 << 1)];
      }
    }

    mldivide(b_tempY, dv0, zcov);
    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        residual_Info->data[(b_k + residual_Info->size[0] * r2) +
          residual_Info->size[0] * residual_Info->size[1] * k] = zcov[r2 + (k <<
          1)];
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 6; r2++) {
        b_X2[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 6; i++) {
          b_X2[k + (r2 << 1)] += (double)a[k + (i << 1)] * P[i + 6 * r2];
        }
      }

      for (r2 = 0; r2 < 2; r2++) {
        a21 = 0.0;
        for (i = 0; i < 6; i++) {
          a21 += b_X2[k + (i << 1)] * (double)b[i + 6 * r2];
        }

        b_tempY[k + (r2 << 1)] = a21 + MeasNoiseVar[k + (r2 << 1)];
      }
    }

    mldivide(b_tempY, dv0, zcov);
    for (k = 0; k < 2; k++) {
      residual_xi->data[k + residual_xi->size[0] * b_k] = 0.0;
    }

    for (k = 0; k < 2; k++) {
      residual_xi->data[k + residual_xi->size[0] * b_k] = 0.0;
      for (r2 = 0; r2 < 2; r2++) {
        residual_xi->data[k + residual_xi->size[0] * b_k] += zcov[k + (r2 << 1)]
          * residual_mean->data[r2 + residual_mean->size[0] * b_k];
      }
    }

    if (!ukf.pIsValidStateTransitionFcn) {
      ukf.pIsValidStateTransitionFcn = true;
    }

    memcpy(&Q[0], &ukf.pProcessNoise[0], 36U * sizeof(double));
    for (i = 0; i < 6; i++) {
      value[i] = ukf.pState[i];
    }

    memcpy(&P[0], &ukf.pStateCovariance[0], 36U * sizeof(double));
    a21 = ukf.Alpha;
    a22 = ukf.Beta;
    kappa = ukf.Kappa;
    calcUTParameters(a21, a22, kappa, &c, yk, Wcov, &OOM);
    calcSigmaPoints(P, value, c, X2);
    for (i = 0; i < 12; i++) {
      f_cavitySystem(*(double (*)[6])&X2[6 * i], *(double (*)[2])&u_Meas->
                     data[u_Meas->size[0] * b_k], fs, tau_m, K_m, QL, c_tempY);
      for (k = 0; k < 6; k++) {
        c_Y2[k + 6 * i] = c_tempY[k];
      }
    }

    f_cavitySystem(value, *(double (*)[2])&u_Meas->data[u_Meas->size[0] * b_k],
                   fs, tau_m, K_m, QL, c_tempY);
    for (i = 0; i < 6; i++) {
      value[i] = c_tempY[i] * yk[0];
    }

    for (i = 0; i < 12; i++) {
      for (k = 0; k < 6; k++) {
        value[k] += c_Y2[k + 6 * i] * yk[1];
      }
    }

    for (k = 0; k < 6; k++) {
      a21 = value[k] * OOM;
      value[k] = a21;
      c_tempY[k] -= a21;
    }

    for (i = 0; i < 12; i++) {
      for (k = 0; k < 6; k++) {
        c_Y2[k + 6 * i] -= value[k];
      }
    }

    for (i = 0; i < 6; i++) {
      ukf.pState[i] = value[i];
    }

    for (k = 0; k < 6; k++) {
      for (r2 = 0; r2 < 6; r2++) {
        P[k + 6 * r2] = c_tempY[k] * c_tempY[r2];
        d_Y2[k + 6 * r2] = 0.0;
        for (i = 0; i < 12; i++) {
          d_Y2[k + 6 * r2] += c_Y2[k + 6 * i] * c_Y2[r2 + 6 * i];
        }
      }
    }

    for (k = 0; k < 6; k++) {
      for (r2 = 0; r2 < 6; r2++) {
        ukf.pStateCovariance[r2 + 6 * k] = OOM * (Wcov[0] * P[r2 + 6 * k] +
          Wcov[1] * d_Y2[r2 + 6 * k]) + Q[r2 + 6 * k];
      }
    }
  }

  /*  clear ukf */
  /*  C_full = repmat(C, [Nsamples, 1, Nstates]); */
  /*  MeasNoiseVar_full = repmat(MeasNoiseVar,[Nsamples, Noutput, Noutput]); */
  /* residual_Variance = PCorrected + MeasNoiseVar; */
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
  /*  plot(residual_mean.') */
}

/*
 * File trailer for f_compute_ukf_residual_not_pers.c
 *
 * [EOF]
 */
