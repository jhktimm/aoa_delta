/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_cavitySystem.c
 *
 * Code generation for function 'f_cavitySystem'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_cavitySystem.h"
#include "inv.h"

/* Function Definitions */
void f_cavitySystem(const double x[6], const double u_mC[2], double fs, const
                    double tau_m[4], const double K_m[4], double QL, double dx[6])
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
  int i6;
  int i7;

  /*  Coupled simulink model */
  Ts = 1.0 / fs;
  w12 = 4.0840704496667309E+9 / QL;

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
    for (i6 = 0; i6 < 4; i6++) {
      c_I[i6 + (i << 2)] = (double)I[i6 + (i << 2)] + 0.5 * A[i6 + (i << 2)] *
        Ts;
    }
  }

  for (i = 0; i < 4; i++) {
    y = 0.0;
    for (i6 = 0; i6 < 4; i6++) {
      A[i + (i6 << 2)] = 0.0;
      for (i7 = 0; i7 < 4; i7++) {
        A[i + (i6 << 2)] += c_I[i + (i7 << 2)] * b_I[i7 + (i6 << 2)];
      }

      y += A[i + (i6 << 2)] * x[2 + i6];
    }

    dx[2 + i] = y + Ts * (-6.2831853071795862 * K_m[i] / tau_m[i]) * w12;
  }
}

/* End of code generation (f_cavitySystem.c) */
