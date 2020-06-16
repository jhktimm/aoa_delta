/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_ukf_residual_fixdw.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "f_compute_ukf_residual_fixdw.h"
#include "calcSigmaPoints.h"
#include "mldivide.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"
#include "UnscentedKalmanFilter1.h"
#include "isSymmetricPositiveSemiDefinite.h"
#include "unscentedKalmanFilter.h"

/* Function Definitions */

/*
 * Arguments    : const double MeasNoiseVar[4]
 *                const double ProcessVar[4]
 *                const emxArray_real_T *y_Meas
 *                const emxArray_real_T *u_Meas
 *                double fs
 *                double QL
 *                const emxArray_real_T *dw
 *                emxArray_real_T *residual_mean
 *                emxArray_real_T *residual_Variance
 *                emxArray_real_T *residual_xi
 *                emxArray_real_T *residual_Info
 * Return Type  : void
 */
void f_compute_ukf_residual_fixdw(const double MeasNoiseVar[4], const double
  ProcessVar[4], const emxArray_real_T *y_Meas, const emxArray_real_T *u_Meas,
  double fs, double QL, const emxArray_real_T *dw, emxArray_real_T
  *residual_mean, emxArray_real_T *residual_Variance, emxArray_real_T
  *residual_xi, emxArray_real_T *residual_Info)
{
  unscentedKalmanFilter_1 ukf;
  int k;
  int i;
  int b_k;
  double tempY[2];
  double a21;
  int r2;
  double yk[2];
  static const double a[4] = { 1.0, 0.0, 0.0, 1.0 };

  double zcov[4];
  double X1[2];
  double a22;
  double P[4];
  double a0;
  double c;
  double Wcov[2];
  double OOM;
  double X2[8];
  double Ymean[2];
  double Y2[8];
  double b_X2[4];
  double Pyy[4];
  double Pxy[4];
  double b_tempY[4];
  double gain[4];
  double params_f4;
  double c_tempY[2];

  /*  Initialize the object. */
  /*  % State transition function */
  /*  % Measurement function */
  d_unscentedKalmanFilter_unscent(&ukf);

  /*  Construct the filter */
  isSymmetricPositiveSemiDefinite(MeasNoiseVar);
  for (k = 0; k < 4; k++) {
    ukf.pMeasurementNoise[k] = MeasNoiseVar[k];
  }

  c_UnscentedKalmanFilter_set_Pro(&ukf, ProcessVar);
  ukf.Alpha = 0.1;

  /*  end */
  k = residual_mean->size[0] * residual_mean->size[1];
  residual_mean->size[0] = 2;
  residual_mean->size[1] = y_Meas->size[1];
  emxEnsureCapacity((emxArray__common *)residual_mean, k, sizeof(double));
  i = y_Meas->size[1] << 1;
  for (k = 0; k < i; k++) {
    residual_mean->data[k] = 0.0;
  }

  k = residual_Variance->size[0] * residual_Variance->size[1] *
    residual_Variance->size[2];
  residual_Variance->size[0] = y_Meas->size[1];
  residual_Variance->size[1] = 2;
  residual_Variance->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)residual_Variance, k, sizeof(double));
  k = residual_Info->size[0] * residual_Info->size[1] * residual_Info->size[2];
  residual_Info->size[0] = y_Meas->size[1];
  residual_Info->size[1] = 2;
  residual_Info->size[2] = 2;
  emxEnsureCapacity((emxArray__common *)residual_Info, k, sizeof(double));
  k = residual_xi->size[0] * residual_xi->size[1];
  residual_xi->size[0] = 2;
  residual_xi->size[1] = y_Meas->size[1];
  emxEnsureCapacity((emxArray__common *)residual_xi, k, sizeof(double));
  for (b_k = 0; b_k < y_Meas->size[1]; b_k++) {
    /*  Let k denote the current time. */
    /*  */
    /*  Residuals (or innovations): Measured output - Predicted output */
    for (i = 0; i < 2; i++) {
      tempY[i] = ukf.pState[i];
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
      for (r2 = 0; r2 < 2; r2++) {
        a21 += a[k + (r2 << 1)] * tempY[r2];
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

    for (i = 0; i < 2; i++) {
      X1[i] = ukf.pState[i];
    }

    for (k = 0; k < 4; k++) {
      P[k] = ukf.pStateCovariance[k];
    }

    a22 = ukf.Alpha;
    a0 = ukf.Beta;
    a21 = ukf.Kappa;
    c = a22 * a22 * (2.0 + a21);
    yk[0] = 1.0 - 2.0 / c;
    yk[1] = 1.0 / (2.0 * c);
    Wcov[0] = yk[0] + ((1.0 - a22 * a22) + a0);
    Wcov[1] = yk[1];
    if (yk[0] != 0.0) {
      OOM = yk[0];
      a21 = yk[0];
      for (k = 0; k < 2; k++) {
        yk[k] /= a21;
        Wcov[k] /= OOM;
      }
    } else {
      OOM = 1.0;
    }

    b_calcSigmaPoints(P, X1, c, X2);
    for (i = 0; i < 4; i++) {
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
        for (r2 = 0; r2 < 2; r2++) {
          a21 += a[k + (r2 << 1)] * X2[r2 + (i << 1)];
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
      for (k = 0; k < 2; k++) {
        a21 += a[i + (k << 1)] * X1[k];
      }

      Ymean[i] = a21 * yk[0];
      tempY[i] = a21;
    }

    for (i = 0; i < 4; i++) {
      for (k = 0; k < 2; k++) {
        Ymean[k] += Y2[k + (i << 1)] * yk[1];
      }
    }

    for (k = 0; k < 2; k++) {
      a21 = Ymean[k] * OOM;
      Ymean[k] = a21;
      tempY[k] -= a21;
    }

    for (i = 0; i < 4; i++) {
      for (k = 0; k < 2; k++) {
        Y2[k + (i << 1)] -= Ymean[k];
        X2[k + (i << 1)] -= X1[k];
      }
    }

    a21 = Wcov[1] * OOM;
    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        b_X2[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 4; i++) {
          b_X2[k + (r2 << 1)] += X2[k + (i << 1)] * Y2[r2 + (i << 1)];
        }
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        Pxy[r2 + (k << 1)] = b_X2[r2 + (k << 1)] * a21;
        b_tempY[k + (r2 << 1)] = tempY[k] * tempY[r2];
        gain[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 4; i++) {
          gain[k + (r2 << 1)] += Y2[k + (i << 1)] * Y2[r2 + (i << 1)];
        }
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        Pyy[r2 + (k << 1)] = OOM * (Wcov[0] * b_tempY[r2 + (k << 1)] + Wcov[1] *
          gain[r2 + (k << 1)]) + zcov[r2 + (k << 1)];
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
    for (k = 0; k < 2; k++) {
      gain[k + (i << 1)] = Pxy[k] / Pyy[i];
      gain[k + (r2 << 1)] = (Pxy[2 + k] - gain[k + (i << 1)] * Pyy[2 + i]) / a22;
      gain[k + (i << 1)] -= gain[k + (r2 << 1)] * a21;
    }

    for (k = 0; k < 2; k++) {
      tempY[k] = y_Meas->data[k + y_Meas->size[0] * b_k] - Ymean[k];
    }

    for (k = 0; k < 2; k++) {
      a21 = 0.0;
      for (r2 = 0; r2 < 2; r2++) {
        a21 += gain[k + (r2 << 1)] * tempY[r2];
        b_X2[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 2; i++) {
          b_X2[k + (r2 << 1)] += gain[k + (i << 1)] * Pyy[i + (r2 << 1)];
        }
      }

      for (r2 = 0; r2 < 2; r2++) {
        a22 = 0.0;
        for (i = 0; i < 2; i++) {
          a22 += b_X2[k + (i << 1)] * gain[r2 + (i << 1)];
        }

        P[k + (r2 << 1)] -= a22;
      }

      X1[k] += a21;
    }

    for (i = 0; i < 2; i++) {
      ukf.pState[i] = X1[i];
    }

    for (k = 0; k < 4; k++) {
      ukf.pStateCovariance[k] = P[k];
    }

    for (k = 0; k < 4; k++) {
      zcov[k] = ukf.pStateCovariance[k];
    }

    /*  Predict the states at next time step, k+1. This updates the State and */
    /*  StateCovariance properties of the filter to contain x[k+1|k] and */
    /*  P[k+1|k]. These will be utilized by the filter at the next time step. */
    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        b_tempY[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 2; i++) {
          b_tempY[k + (r2 << 1)] += a[k + (i << 1)] * zcov[i + (r2 << 1)];
        }
      }

      for (r2 = 0; r2 < 2; r2++) {
        a21 = 0.0;
        for (i = 0; i < 2; i++) {
          a21 += b_tempY[k + (i << 1)] * a[i + (r2 << 1)];
        }

        b_X2[k + (r2 << 1)] = a21 + MeasNoiseVar[k + (r2 << 1)];
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        residual_Variance->data[(b_k + residual_Variance->size[0] * r2) +
          residual_Variance->size[0] * residual_Variance->size[1] * k] = b_X2[r2
          + (k << 1)];
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        b_X2[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 2; i++) {
          b_X2[k + (r2 << 1)] += a[k + (i << 1)] * zcov[i + (r2 << 1)];
        }
      }

      for (r2 = 0; r2 < 2; r2++) {
        a21 = 0.0;
        for (i = 0; i < 2; i++) {
          a21 += b_X2[k + (i << 1)] * a[i + (r2 << 1)];
        }

        b_tempY[k + (r2 << 1)] = a21 + MeasNoiseVar[k + (r2 << 1)];
      }
    }

    mldivide(b_tempY, a, gain);
    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        residual_Info->data[(b_k + residual_Info->size[0] * r2) +
          residual_Info->size[0] * residual_Info->size[1] * k] = gain[r2 + (k <<
          1)];
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        b_X2[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 2; i++) {
          b_X2[k + (r2 << 1)] += a[k + (i << 1)] * zcov[i + (r2 << 1)];
        }
      }

      for (r2 = 0; r2 < 2; r2++) {
        a21 = 0.0;
        for (i = 0; i < 2; i++) {
          a21 += b_X2[k + (i << 1)] * a[i + (r2 << 1)];
        }

        b_tempY[k + (r2 << 1)] = a21 + MeasNoiseVar[k + (r2 << 1)];
      }
    }

    mldivide(b_tempY, a, zcov);
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

    params_f4 = dw->data[b_k];
    for (k = 0; k < 4; k++) {
      zcov[k] = ukf.pProcessNoise[k];
    }

    for (i = 0; i < 2; i++) {
      X1[i] = ukf.pState[i];
    }

    for (k = 0; k < 4; k++) {
      P[k] = ukf.pStateCovariance[k];
    }

    a22 = ukf.Alpha;
    a0 = ukf.Beta;
    a21 = ukf.Kappa;
    c = a22 * a22 * (2.0 + a21);
    yk[0] = 1.0 - 2.0 / c;
    yk[1] = 1.0 / (2.0 * c);
    Wcov[0] = yk[0] + ((1.0 - a22 * a22) + a0);
    Wcov[1] = yk[1];
    if (yk[0] != 0.0) {
      OOM = yk[0];
      a21 = yk[0];
      for (k = 0; k < 2; k++) {
        yk[k] /= a21;
        Wcov[k] /= OOM;
      }
    } else {
      OOM = 1.0;
    }

    b_calcSigmaPoints(P, X1, c, X2);
    a22 = 1.0 / fs;
    a21 = 4.0840704496667309E+9 / QL;
    a0 = -1.0 + a21 * a22;
    a21 = 2.0 * a21 * a22;
    for (i = 0; i < 4; i++) {
      /*  Coupled simulink model */
      /*  ------------- Discrete State Space System ----------------------- */
      /*  ---------- Values--------- */
      c_tempY[0] = (-a0 * X2[i << 1] - params_f4 * X2[1 + (i << 1)] * a22) + a21
        * u_Meas->data[u_Meas->size[0] * b_k];
      c_tempY[1] = (params_f4 * X2[i << 1] * a22 - a0 * X2[1 + (i << 1)]) + a21 *
        u_Meas->data[1 + u_Meas->size[0] * b_k];
      for (k = 0; k < 2; k++) {
        Y2[k + (i << 1)] = c_tempY[k];
      }
    }

    /*  Coupled simulink model */
    a22 = 1.0 / fs;
    a21 = 4.0840704496667309E+9 / QL;

    /*  ------------- Discrete State Space System ----------------------- */
    /*  ---------- Values--------- */
    a0 = -1.0 + a21 * a22;
    a21 = 2.0 * a21 * a22;
    c_tempY[0] = (-a0 * X1[0] - dw->data[b_k] * X1[1] * a22) + a21 *
      u_Meas->data[u_Meas->size[0] * b_k];
    c_tempY[1] = (dw->data[b_k] * X1[0] * a22 - a0 * X1[1]) + a21 * u_Meas->
      data[1 + u_Meas->size[0] * b_k];
    for (i = 0; i < 2; i++) {
      X1[i] = c_tempY[i] * yk[0];
    }

    for (i = 0; i < 4; i++) {
      for (k = 0; k < 2; k++) {
        X1[k] += Y2[k + (i << 1)] * yk[1];
      }
    }

    for (i = 0; i < 2; i++) {
      a21 = X1[i] * OOM;
      tempY[i] = c_tempY[i] - a21;
      X1[i] = a21;
    }

    for (i = 0; i < 4; i++) {
      for (k = 0; k < 2; k++) {
        Y2[k + (i << 1)] -= X1[k];
      }
    }

    for (i = 0; i < 2; i++) {
      ukf.pState[i] = X1[i];
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        b_tempY[k + (r2 << 1)] = tempY[k] * tempY[r2];
        gain[k + (r2 << 1)] = 0.0;
        for (i = 0; i < 4; i++) {
          gain[k + (r2 << 1)] += Y2[k + (i << 1)] * Y2[r2 + (i << 1)];
        }
      }
    }

    for (k = 0; k < 2; k++) {
      for (r2 = 0; r2 < 2; r2++) {
        ukf.pStateCovariance[r2 + (k << 1)] = OOM * (Wcov[0] * b_tempY[r2 + (k <<
          1)] + Wcov[1] * gain[r2 + (k << 1)]) + zcov[r2 + (k << 1)];
      }
    }
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

/*
 * File trailer for f_compute_ukf_residual_fixdw.c
 *
 * [EOF]
 */
