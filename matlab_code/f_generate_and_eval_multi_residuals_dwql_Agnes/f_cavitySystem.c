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
#include "f_cavitySystem.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "inv.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void f_cavitySystem(const double x[6], const double u_mC[2], double fs, const
                    double tau_m[4], const double K_m[4], double QL, double dx[6])
{
  double Ts;
  double w12;
  double A[16];
  double a0;
  int i;
  signed char b_I[16];
  double c_I[16];
  double dx_tmp;
  double b;
  double d_I[16];
  double d;
  int i1;
  int i2;

  /*  Coupled simulink model */
  Ts = 1.0 / fs;
  w12 = 4.0840704496667309E+9 / QL;

  /* ---------- Define System from identified greybox model------------ */
  memset(&A[0], 0, 16U * sizeof(double));
  A[0] = -1.0 / tau_m[0];
  A[5] = -1.0 / tau_m[1];
  A[10] = -1.0 / tau_m[2];
  A[15] = -1.0 / tau_m[3];

  /*  ------------- Discrete State Space System ----------------------- */
  /*  ---------- Values--------- */
  a0 = w12 * Ts + -1.0;
  w12 = 2.0 * w12 * Ts;
  for (i = 0; i < 16; i++) {
    b_I[i] = 0;
  }

  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  memset(&c_I[0], 0, 16U * sizeof(double));
  c_I[0] = 1.0;
  c_I[5] = 1.0;
  c_I[10] = 1.0;
  c_I[15] = 1.0;
  dx_tmp = ((x[2] + x[3]) + x[4]) + x[5];
  dx[0] = (-a0 * x[0] - dx_tmp * x[1] * Ts) + w12 * u_mC[0];
  dx[1] = (dx_tmp * x[0] * Ts - a0 * x[1]) + w12 * u_mC[1];
  b = x[0] * x[0] + x[1] * x[1];
  for (i = 0; i < 16; i++) {
    w12 = 0.5 * A[i] * Ts;
    d_I[i] = c_I[i] - w12;
    A[i] = (double)b_I[i] + w12;
  }

  inv(d_I, c_I);
  for (i = 0; i < 4; i++) {
    w12 = 0.0;
    dx_tmp = A[i + 4];
    a0 = A[i + 8];
    d = A[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      i2 = i1 << 2;
      w12 += (((A[i] * c_I[i2] + dx_tmp * c_I[i2 + 1]) + a0 * c_I[i2 + 2]) + d *
              c_I[i2 + 3]) * x[i1 + 2];
    }

    dx[i + 2] = w12 + Ts * (-6.2831853071795862 * K_m[i] / tau_m[i]) * b;
  }
}

/* End of code generation (f_cavitySystem.c) */
