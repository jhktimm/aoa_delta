/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_compute_parity_Res2_full.c
 *
 * Code generation for function 'f_compute_parity_Res2_full'
 *
 */

/* Include files */
#include "f_compute_parity_Res2_full.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "inv.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

void f_compute_parity_Res2_full(const emxArray_creal_T *u_mC, const
  emxArray_creal_T *y_mC, const double tau_m[4], const double K_m[4], double QL,
  double fs, emxArray_real_T *r_2)
{
  double Ts;
  double w12;
  double A_c[16];
  double b_I[16];
  double c_I[16];
  int i;
  double A_d[16];
  double absx;
  double Hu_tmp;
  int b_i;
  int k;
  double d;
  double d1;
  double d2;
  double z1[16];
  boolean_T p;
  int i1;
  double z1_tmp;
  int i2;
  double b_z1[16];
  int i3;
  double c_z1[16];
  double B_d[4];
  double A[20];
  double s[4];
  double V[25];
  int Z_size_idx_1;
  double Z_data[25];
  int r;
  emxArray_real_T *u1;
  double v_data[25];
  emxArray_real_T *x1;
  emxArray_real_T *x2;
  emxArray_real_T *u_dw_stacked1;
  emxArray_real_T *y;
  double B[5];

  /* UNTITLED8 Summary of this function goes here */
  /*    Detailed explanation goes here */
  /*  Define System Matrix of linear detuning model */
  Ts = 1.0 / fs;
  w12 = 4.0840704496667309E+9 / QL;
  memset(&A_c[0], 0, 16U * sizeof(double));
  A_c[0] = -1.0 / tau_m[0];
  A_c[5] = -1.0 / tau_m[1];
  A_c[10] = -1.0 / tau_m[2];
  A_c[15] = -1.0 / tau_m[3];

  /* --------------- Sample the System Matrix (Euler Forward)------------------ */
  memset(&b_I[0], 0, 16U * sizeof(double));
  b_I[0] = 1.0;
  b_I[5] = 1.0;
  b_I[10] = 1.0;
  b_I[15] = 1.0;
  memset(&c_I[0], 0, 16U * sizeof(double));
  c_I[0] = 1.0;
  c_I[5] = 1.0;
  c_I[10] = 1.0;
  c_I[15] = 1.0;
  for (i = 0; i < 16; i++) {
    absx = 0.5 * A_c[i] * Ts;
    A_d[i] = c_I[i] - absx;
    b_I[i] += absx;
  }

  inv(A_d, c_I);

  /* ------------Compute Parity Space Vector needed for 2nd Residual----------- */
  Hu_tmp = 0.0;
  for (b_i = 0; b_i < 4; b_i++) {
    d = b_I[b_i + 4];
    d1 = b_I[b_i + 8];
    d2 = b_I[b_i + 12];
    for (i = 0; i < 4; i++) {
      i1 = i << 2;
      A_d[b_i + i1] = ((b_I[b_i] * c_I[i1] + d * c_I[i1 + 1]) + d1 * c_I[i1 + 2])
        + d2 * c_I[i1 + 3];
    }

    d = Ts * (-6.2831853071795862 * K_m[b_i] / tau_m[b_i]);
    B_d[b_i] = d;
    Hu_tmp += d;
  }

  for (k = 0; k < 16; k++) {
    absx = A_d[k] * A_d[k];
    z1[k] = absx;
    z1_tmp = rt_powd_snf(A_d[k], 3.0);
    b_z1[k] = z1_tmp;
    c_z1[k] = absx;
    c_I[k] = absx;
    A_c[k] = z1_tmp;
    b_I[k] = rt_powd_snf(A_d[k], 4.0);
  }

  for (i = 0; i < 4; i++) {
    i1 = i << 2;
    i2 = i1 + 1;
    i3 = i1 + 2;
    k = i1 + 3;
    A[i] = 1.0;
    A[i + 4] = ((A_d[i1] + A_d[i2]) + A_d[i3]) + A_d[k];
    A[i + 8] = ((c_I[i1] + c_I[i2]) + c_I[i3]) + c_I[k];
    A[i + 12] = ((A_c[i1] + A_c[i2]) + A_c[i3]) + A_c[k];
    A[i + 16] = ((b_I[i1] + b_I[i2]) + b_I[i3]) + b_I[k];
  }

  p = true;
  for (k = 0; k < 20; k++) {
    if ((!p) || (rtIsInf(A[k]) || rtIsNaN(A[k]))) {
      p = false;
    }
  }

  if (!p) {
    Z_size_idx_1 = 5;
    for (i = 0; i < 25; i++) {
      Z_data[i] = rtNaN;
    }
  } else {
    svd(A, c_I, s, V);
    absx = fabs(s[0]);
    if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
      if (absx <= 2.2250738585072014E-308) {
        absx = 4.94065645841247E-324;
      } else {
        frexp(absx, &r);
        absx = ldexp(1.0, r - 53);
      }
    } else {
      absx = rtNaN;
    }

    absx *= 5.0;
    r = ((((s[0] > absx) + (s[1] > absx)) + (s[2] > absx)) + (s[3] > absx)) - 5;
    Z_size_idx_1 = -r;
    b_i = -r;
    for (i = 0; i < b_i; i++) {
      for (i1 = 0; i1 < 5; i1++) {
        Z_data[i1 + 5 * i] = V[i1 + 5 * ((r + i) + 5)];
      }
    }
  }

  for (i = 0; i < 5; i++) {
    for (i1 = 0; i1 < Z_size_idx_1; i1++) {
      v_data[i1 + Z_size_idx_1 * i] = Z_data[i + 5 * i1];
    }
  }

  emxInit_real_T(&u1, 1);

  /* -------------- input and states of the system--------------- */
  i = u1->size[0];
  u1->size[0] = u_mC->size[0];
  emxEnsureCapacity_real_T(u1, i);
  b_i = u_mC->size[0];
  for (i = 0; i < b_i; i++) {
    u1->data[i] = u_mC->data[i].re;
  }

  emxInit_real_T(&x1, 1);
  i = x1->size[0];
  x1->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T(x1, i);
  b_i = y_mC->size[0];
  for (i = 0; i < b_i; i++) {
    x1->data[i] = y_mC->data[i].re;
  }

  emxInit_real_T(&x2, 1);
  i = x2->size[0];
  x2->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T(x2, i);
  b_i = y_mC->size[0];
  for (i = 0; i < b_i; i++) {
    x2->data[i] = y_mC->data[i].im;
  }

  /* r_2 = zeros(length(u1),1); */
  if (2 > x1->size[0]) {
    i = 0;
    i1 = 0;
  } else {
    i = 1;
    i1 = x1->size[0];
  }

  emxInit_real_T(&u_dw_stacked1, 1);
  absx = 2.0 * Ts;

  /*  -------------------second residual----------------------- */
  i2 = u_dw_stacked1->size[0];
  u_dw_stacked1->size[0] = x1->size[0];
  emxEnsureCapacity_real_T(u_dw_stacked1, i2);
  r = x1->size[0];
  for (k = 0; k < r; k++) {
    u_dw_stacked1->data[k] = x1->data[k] * x1->data[k];
  }

  emxInit_real_T(&y, 1);
  i2 = y->size[0];
  y->size[0] = x2->size[0];
  emxEnsureCapacity_real_T(y, i2);
  r = x2->size[0];
  for (k = 0; k < r; k++) {
    y->data[k] = x2->data[k] * x2->data[k];
  }

  b_i = u_dw_stacked1->size[0];
  for (i2 = 0; i2 < b_i; i2++) {
    u_dw_stacked1->data[i2] = (u_dw_stacked1->data[i2] + y->data[i2]) * (Ts *
      x2->data[i2]);
  }

  emxFree_real_T(&y);
  if (2 > u_dw_stacked1->size[0]) {
    i2 = -1;
    i3 = -1;
  } else {
    i2 = 0;
    i3 = u_dw_stacked1->size[0] - 1;
  }

  b_i = i1 - i;
  i1 = x2->size[0];
  x2->size[0] = b_i;
  emxEnsureCapacity_real_T(x2, i1);
  for (i1 = 0; i1 < b_i; i1++) {
    x2->data[i1] = (-x1->data[i + i1] + x1->data[i1]) + (-Ts * x1->data[i1] +
      absx * u1->data[i1] * w12);
  }

  emxFree_real_T(&x1);
  i = u1->size[0];
  u1->size[0] = x2->size[0];
  emxEnsureCapacity_real_T(u1, i);
  b_i = x2->size[0];
  for (i = 0; i < b_i; i++) {
    u1->data[i] = x2->data[i];
  }

  emxFree_real_T(&x2);
  if (u1->size[0] >= 5) {
    r = u1->size[0] - 5;
  } else {
    r = -1;
  }

  i = r_2->size[0];
  r_2->size[0] = r + 1;
  emxEnsureCapacity_real_T(r_2, i);
  for (i = 0; i <= r; i++) {
    r_2->data[i] = 0.0;
  }

  if (u1->size[0] > 0) {
    i = u1->size[0] - 5;
    for (k = 0; k < 5; k++) {
      for (r = 0; r <= i; r++) {
        r_2->data[r] += v_data[Z_size_idx_1 * k] * u1->data[(r - k) + 4];
      }
    }
  }

  d = 0.0;
  d1 = 0.0;
  d2 = 0.0;
  absx = 0.0;
  z1_tmp = 0.0;
  Ts = 0.0;
  for (i = 0; i < 4; i++) {
    i1 = i << 2;
    k = i1 + 1;
    r = i1 + 2;
    b_i = i1 + 3;
    w12 = (((A_d[i1] + A_d[k]) + A_d[r]) + A_d[b_i]) * B_d[i];
    d += w12;
    d1 += (((z1[i1] + z1[k]) + z1[r]) + z1[b_i]) * B_d[i];
    d2 += w12;
    absx += (((b_z1[i1] + b_z1[k]) + b_z1[r]) + b_z1[b_i]) * B_d[i];
    z1_tmp += (((c_z1[i1] + c_z1[k]) + c_z1[r]) + c_z1[b_i]) * B_d[i];
    Ts += w12;
  }

  V[1] = Hu_tmp;
  V[6] = 0.0;
  V[11] = 0.0;
  V[16] = 0.0;
  V[21] = 0.0;
  V[2] = d;
  V[7] = Hu_tmp;
  V[12] = 0.0;
  V[17] = 0.0;
  V[22] = 0.0;
  V[3] = d1;
  V[8] = d2;
  V[13] = Hu_tmp;
  V[18] = 0.0;
  V[23] = 0.0;
  V[4] = absx;
  V[9] = z1_tmp;
  V[14] = Ts;
  V[19] = Hu_tmp;
  V[24] = 0.0;
  for (i = 0; i < 5; i++) {
    V[5 * i] = 0.0;
    d = 0.0;
    for (i1 = 0; i1 < 5; i1++) {
      d += v_data[Z_size_idx_1 * i1] * V[i1 + 5 * i];
    }

    B[i] = d;
  }

  i = i3 - i2;
  if (i >= 5) {
    r = i - 5;
  } else {
    r = -1;
  }

  i1 = u1->size[0];
  u1->size[0] = r + 1;
  emxEnsureCapacity_real_T(u1, i1);
  for (i1 = 0; i1 <= r; i1++) {
    u1->data[i1] = 0.0;
  }

  if (i > 0) {
    i = (i3 - i2) - 5;
    for (k = 0; k < 5; k++) {
      for (r = 0; r <= i; r++) {
        u1->data[r] += B[k] * u_dw_stacked1->data[((i2 + r) - k) + 5];
      }
    }
  }

  emxFree_real_T(&u_dw_stacked1);
  b_i = r_2->size[0];
  for (i = 0; i < b_i; i++) {
    r_2->data[i] -= u1->data[i];
  }

  emxFree_real_T(&u1);
}

/* End of code generation (f_compute_parity_Res2_full.c) */
