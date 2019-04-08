/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_cavitySystem.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "f_cavitySystem.h"
#include "inv.h"

/* Function Definitions */

/*
 * Coupled simulink model
 * Arguments    : const double x[6]
 *                const double u_mC[2]
 *                double f0
 *                double fs
 *                const double tau_m[4]
 *                const double K_m[4]
 *                double QL
 *                double dx[6]
 * Return Type  : void
 */
void f_cavitySystem(const double x[6], const double u_mC[2], double f0, double
                    fs, const double tau_m[4], const double K_m[4], double QL,
                    double dx[6])
{
  double Ts;
  double w12;
  int i;
  double A[16];
  double z[4];
  double a0;
  signed char I[16];
  double b_I[16];
  double c_I[16];
  double y;
  int i3;
  int i4;
  Ts = 1.0 / fs;
  w12 = 3.1415926535897931 * f0 / QL;

  /* ---------- Define System from identified greybox model------------ */
  for (i = 0; i < 4; i++) {
    z[i] = -1.0 / tau_m[i];
  }

  memset(&A[0], 0, sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    A[i + (i << 2)] = z[i];
  }

  /*  ------------- Discrete State Space System ----------------------- */
  /*  ---------- Values--------- */
  a0 = -1.0 + w12 * Ts;
  w12 = 2.0 * w12 * Ts;
  for (i = 0; i < 16; i++) {
    I[i] = 0;
  }

  for (i = 0; i < 4; i++) {
    I[i + (i << 2)] = 1;
  }

  memset(&b_I[0], 0, sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    b_I[i + (i << 2)] = 1.0;
  }

  for (i = 0; i < 16; i++) {
    c_I[i] = b_I[i] - 0.5 * A[i] * Ts;
  }

  invNxN(c_I, b_I);
  y = x[2];
  for (i = 0; i < 3; i++) {
    y += x[i + 3];
  }

  dx[0] = (-a0 * x[0] - y * x[1] * Ts) + w12 * u_mC[0];
  y = x[2];
  for (i = 0; i < 3; i++) {
    y += x[i + 3];
  }

  dx[1] = (y * x[0] * Ts - a0 * x[1]) + w12 * u_mC[1];
  w12 = x[0] * x[0] + x[1] * x[1];
  for (i = 0; i < 4; i++) {
    for (i3 = 0; i3 < 4; i3++) {
      c_I[i3 + (i << 2)] = (double)I[i3 + (i << 2)] + 0.5 * A[i3 + (i << 2)] *
        Ts;
    }
  }

  for (i = 0; i < 4; i++) {
    y = 0.0;
    for (i3 = 0; i3 < 4; i3++) {
      A[i + (i3 << 2)] = 0.0;
      for (i4 = 0; i4 < 4; i4++) {
        A[i + (i3 << 2)] += c_I[i + (i4 << 2)] * b_I[i4 + (i3 << 2)];
      }

      y += A[i + (i3 << 2)] * x[2 + i3];
    }

    dx[2 + i] = y + Ts * (-6.2831853071795862 * K_m[i] / tau_m[i]) * w12;
  }
}

/*
 * File trailer for f_cavitySystem.c
 *
 * [EOF]
 */
