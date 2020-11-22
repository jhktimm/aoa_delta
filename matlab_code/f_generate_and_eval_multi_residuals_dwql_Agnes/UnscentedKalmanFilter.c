/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * UnscentedKalmanFilter.c
 *
 * Code generation for function 'UnscentedKalmanFilter'
 *
 */

/* Include files */
#include "UnscentedKalmanFilter.h"
#include "calcSigmaPoints.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_data.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void UnscentedKalmanFilter_correct(unscentedKalmanFilter *obj, const double z[2],
  double x_corr[6], double P_corr[36])
{
  double a21;
  int gain_tmp;
  int i;
  double P[36];
  double X1[6];
  double c;
  double a22;
  double Wmean_idx_1;
  double Wcov_idx_0;
  double Wcov_idx_1;
  double OOM;
  double d;
  double X2[72];
  int kk;
  double Ymean[2];
  int r2;
  double tempY[2];
  double Y2[24];
  double y_tmp[24];
  double b_X2[12];
  double b_tempY[4];
  double b_Y2[4];
  int k;
  double gain[12];
  if ((!obj->pIsSetStateCovariance) || (obj->pStateCovarianceScalar != -1.0)) {
    a21 = obj->pStateCovarianceScalar;
    for (gain_tmp = 0; gain_tmp < 36; gain_tmp++) {
      obj->pStateCovariance[gain_tmp] = a21 * (double)iv[gain_tmp];
    }

    obj->pIsSetStateCovariance = true;
    obj->pStateCovarianceScalar = -1.0;
  }

  if (obj->pIsFirstCallCorrect) {
    if (!obj->pIsValidMeasurementFcn) {
      obj->pIsValidMeasurementFcn = true;
    }

    obj->pIsFirstCallCorrect = false;
  }

  if ((!obj->pIsSetMeasurementNoise) || (obj->pMeasurementNoiseScalar != -1.0))
  {
    a21 = obj->pMeasurementNoiseScalar;
    obj->pMeasurementNoise[0] = a21;
    obj->pMeasurementNoise[1] = a21 * 0.0;
    obj->pMeasurementNoise[2] = a21 * 0.0;
    obj->pMeasurementNoise[3] = a21;
    obj->pIsSetMeasurementNoise = true;
    obj->pMeasurementNoiseScalar = -1.0;
  }

  for (i = 0; i < 6; i++) {
    X1[i] = obj->pState[i];
  }

  memcpy(&P[0], &obj->pStateCovariance[0], 36U * sizeof(double));
  a21 = obj->Alpha;
  a21 *= a21;
  c = a21 * (obj->Kappa + 6.0);
  a22 = 1.0 - 6.0 / c;
  Wmean_idx_1 = 1.0 / (2.0 * c);
  Wcov_idx_0 = a22 + ((1.0 - a21) + obj->Beta);
  Wcov_idx_1 = Wmean_idx_1;
  if (a22 != 0.0) {
    OOM = a22;
    d = a22;
    a22 /= a22;
    Wcov_idx_0 /= OOM;
    Wmean_idx_1 /= d;
    Wcov_idx_1 /= OOM;
  } else {
    OOM = 1.0;
  }

  calcSigmaPoints(P, X1, c, X2);
  for (kk = 0; kk < 12; kk++) {
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
    for (gain_tmp = 0; gain_tmp < 2; gain_tmp++) {
      d = 0.0;
      for (r2 = 0; r2 < 6; r2++) {
        d += (double)iv1[gain_tmp + (r2 << 1)] * X2[r2 + 6 * kk];
      }

      Y2[gain_tmp + (kk << 1)] = d;
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
    d = 0.0;
    for (gain_tmp = 0; gain_tmp < 6; gain_tmp++) {
      d += (double)iv1[i + (gain_tmp << 1)] * X1[gain_tmp];
    }

    tempY[i] = d;
    Ymean[i] = d * a22;
  }

  d = Ymean[0];
  a22 = Ymean[1];
  for (kk = 0; kk < 12; kk++) {
    i = kk << 1;
    d += Y2[i] * Wmean_idx_1;
    a22 += Y2[i + 1] * Wmean_idx_1;
  }

  d *= OOM;
  Ymean[0] = d;
  tempY[0] -= d;
  d = a22 * OOM;
  tempY[1] -= d;
  for (kk = 0; kk < 12; kk++) {
    i = kk << 1;
    Y2[i] -= Ymean[0];
    i++;
    Y2[i] -= d;
  }

  for (gain_tmp = 0; gain_tmp < 2; gain_tmp++) {
    for (r2 = 0; r2 < 12; r2++) {
      y_tmp[r2 + 12 * gain_tmp] = Y2[gain_tmp + (r2 << 1)];
    }
  }

  for (kk = 0; kk < 12; kk++) {
    for (gain_tmp = 0; gain_tmp < 6; gain_tmp++) {
      i = gain_tmp + 6 * kk;
      X2[i] -= X1[gain_tmp];
    }
  }

  a21 = Wcov_idx_1 * OOM;
  for (gain_tmp = 0; gain_tmp < 6; gain_tmp++) {
    for (r2 = 0; r2 < 2; r2++) {
      a22 = 0.0;
      for (i = 0; i < 12; i++) {
        a22 += X2[gain_tmp + 6 * i] * y_tmp[i + 12 * r2];
      }

      b_X2[gain_tmp + 6 * r2] = a22;
    }
  }

  for (gain_tmp = 0; gain_tmp < 12; gain_tmp++) {
    b_X2[gain_tmp] *= a21;
  }

  for (gain_tmp = 0; gain_tmp < 2; gain_tmp++) {
    for (r2 = 0; r2 < 2; r2++) {
      b_tempY[r2 + (gain_tmp << 1)] = tempY[r2] * tempY[gain_tmp];
      a22 = 0.0;
      for (i = 0; i < 12; i++) {
        a22 += Y2[gain_tmp + (i << 1)] * y_tmp[i + 12 * r2];
      }

      b_Y2[gain_tmp + (r2 << 1)] = a22;
    }
  }

  b_tempY[0] = OOM * (Wcov_idx_0 * b_tempY[0] + Wcov_idx_1 * b_Y2[0]) +
    obj->pMeasurementNoise[0];
  b_tempY[1] = OOM * (Wcov_idx_0 * b_tempY[1] + Wcov_idx_1 * b_Y2[1]) +
    obj->pMeasurementNoise[1];
  b_tempY[2] = OOM * (Wcov_idx_0 * b_tempY[2] + Wcov_idx_1 * b_Y2[2]) +
    obj->pMeasurementNoise[2];
  b_tempY[3] = OOM * (Wcov_idx_0 * b_tempY[3] + Wcov_idx_1 * b_Y2[3]) +
    obj->pMeasurementNoise[3];
  if (fabs(b_tempY[1]) > fabs(b_tempY[0])) {
    i = 1;
    r2 = 0;
  } else {
    i = 0;
    r2 = 1;
  }

  a21 = b_tempY[r2] / b_tempY[i];
  c = b_tempY[i + 2];
  a22 = b_tempY[r2 + 2] - a21 * c;
  for (k = 0; k < 6; k++) {
    gain_tmp = k + 6 * i;
    gain[gain_tmp] = b_X2[k] / b_tempY[i];
    kk = k + 6 * r2;
    gain[kk] = (b_X2[k + 6] - gain[gain_tmp] * c) / a22;
    gain[gain_tmp] -= gain[kk] * a21;
  }

  Ymean[0] = z[0] - Ymean[0];
  Ymean[1] = z[1] - d;
  obj->pIsSetStateCovariance = true;
  obj->pStateCovarianceScalar = -1.0;
  for (i = 0; i < 6; i++) {
    d = gain[i + 6];
    a22 = gain[i] * b_tempY[0] + d * b_tempY[1];
    a21 = gain[i] * b_tempY[2] + d * b_tempY[3];
    obj->pState[i] = X1[i] + (gain[i] * Ymean[0] + d * Ymean[1]);
    for (gain_tmp = 0; gain_tmp < 6; gain_tmp++) {
      r2 = i + 6 * gain_tmp;
      obj->pStateCovariance[r2] = P[r2] - (a22 * gain[gain_tmp] + a21 *
        gain[gain_tmp + 6]);
    }

    x_corr[i] = obj->pState[i];
  }

  if ((!obj->pIsSetStateCovariance) || (obj->pStateCovarianceScalar != -1.0)) {
    a21 = obj->pStateCovarianceScalar;
    for (gain_tmp = 0; gain_tmp < 36; gain_tmp++) {
      obj->pStateCovariance[gain_tmp] = a21 * (double)iv[gain_tmp];
    }

    obj->pIsSetStateCovariance = true;
    obj->pStateCovarianceScalar = -1.0;
  }

  memcpy(&P_corr[0], &obj->pStateCovariance[0], 36U * sizeof(double));
}

/* End of code generation (UnscentedKalmanFilter.c) */
