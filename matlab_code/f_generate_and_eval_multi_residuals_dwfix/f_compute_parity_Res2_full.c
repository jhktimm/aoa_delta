/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_parity_Res2_full.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "f_compute_parity_Res2_full.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"
#include "conv.h"
#include "power.h"
#include "eps.h"
#include "svd.h"
#include "inv.h"

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d7;
  double d8;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d7 = fabs(u0);
    d8 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d7 == 1.0) {
        y = 1.0;
      } else if (d7 > 1.0) {
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
    } else if (d8 == 0.0) {
      y = 1.0;
    } else if (d8 == 1.0) {
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

/*
 * UNTITLED8 Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : const emxArray_creal_T *u_mC
 *                const emxArray_creal_T *y_mC
 *                const double tau_m[4]
 *                const double K_m[4]
 *                double QL
 *                double fs
 *                emxArray_real_T *r_2
 * Return Type  : void
 */
void f_compute_parity_Res2_full(const emxArray_creal_T *u_mC, const
  emxArray_creal_T *y_mC, const double tau_m[4], const double K_m[4], double QL,
  double fs, emxArray_real_T *r_2)
{
  double Ts;
  double w12;
  int i;
  double A_c[16];
  double B_d[4];
  double I[16];
  double b_I[16];
  int i25;
  double c_I[16];
  double y[16];
  int i26;
  double A_d[16];
  boolean_T p;
  double s[4];
  double b_y[16];
  double dv4[4];
  double dv5[4];
  double A[20];
  double dv6[4];
  double V[25];
  int Z_size_idx_1;
  int r;
  double tol;
  double Z_data[25];
  int loop_ub;
  emxArray_real_T *u1;
  double v_data[25];
  emxArray_real_T *x1;
  emxArray_real_T *x2;
  emxArray_real_T *u_dw_stacked1;
  emxArray_real_T *r5;
  emxArray_real_T *b_x1;
  double v[5];
  emxArray_real_T *b_u_dw_stacked1;
  double d0;
  double d1;
  double d2;
  double d3;
  double d4;
  double d5;
  double d6;
  double dv7[4];
  double b_v[5];
  double dv8[4];

  /*  Define System Matrix of linear detuning model */
  Ts = 1.0 / fs;
  w12 = 4.0840704496667309E+9 / QL;
  for (i = 0; i < 4; i++) {
    B_d[i] = -1.0 / tau_m[i];
  }

  memset(&A_c[0], 0, sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    A_c[i + (i << 2)] = B_d[i];
  }

  /* --------------- Sample the System Matrix (Euler Forward)------------------ */
  memset(&I[0], 0, sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    I[i + (i << 2)] = 1.0;
  }

  memset(&b_I[0], 0, sizeof(double) << 4);
  for (i = 0; i < 4; i++) {
    b_I[i + (i << 2)] = 1.0;
  }

  for (i25 = 0; i25 < 16; i25++) {
    c_I[i25] = b_I[i25] - 0.5 * A_c[i25] * Ts;
  }

  invNxN(c_I, y);
  for (i25 = 0; i25 < 4; i25++) {
    for (i26 = 0; i26 < 4; i26++) {
      b_I[i26 + (i25 << 2)] = I[i26 + (i25 << 2)] + 0.5 * A_c[i26 + (i25 << 2)] *
        Ts;
    }
  }

  for (i = 0; i < 4; i++) {
    for (i25 = 0; i25 < 4; i25++) {
      A_d[i + (i25 << 2)] = 0.0;
      for (i26 = 0; i26 < 4; i26++) {
        A_d[i + (i25 << 2)] += b_I[i + (i26 << 2)] * y[i26 + (i25 << 2)];
      }
    }

    B_d[i] = Ts * (-6.2831853071795862 * K_m[i] / tau_m[i]);
  }

  /* ------------Compute Parity Space Vector needed for 2nd Residual----------- */
  for (i = 0; i < 16; i++) {
    y[i] = A_d[i] * A_d[i];
    c_I[i] = rt_powd_snf(A_d[i], 3.0);
    b_y[i] = A_d[i] * A_d[i];
    b_I[i] = A_d[i] * A_d[i];
    A_c[i] = rt_powd_snf(A_d[i], 3.0);
    I[i] = rt_powd_snf(A_d[i], 4.0);
  }

  for (i25 = 0; i25 < 4; i25++) {
    s[i25] = 0.0;
    dv4[i25] = 0.0;
    dv5[i25] = 0.0;
    dv6[i25] = 0.0;
    for (i26 = 0; i26 < 4; i26++) {
      s[i25] += A_d[i26 + (i25 << 2)];
      dv4[i25] += b_I[i26 + (i25 << 2)];
      dv5[i25] += A_c[i26 + (i25 << 2)];
      dv6[i25] += I[i26 + (i25 << 2)];
    }

    A[i25] = 1.0;
    A[4 + i25] = s[i25];
    A[8 + i25] = dv4[i25];
    A[12 + i25] = dv5[i25];
    A[16 + i25] = dv6[i25];
  }

  p = false;
  for (i = 0; i < 20; i++) {
    if (p || rtIsInf(A[i]) || rtIsNaN(A[i])) {
      p = true;
    } else {
      p = false;
    }
  }

  if (p) {
    Z_size_idx_1 = 5;
    for (i25 = 0; i25 < 25; i25++) {
      Z_data[i25] = rtNaN;
    }
  } else {
    svd(A, b_I, s, V);
    r = -5;
    tol = 5.0 * eps(s[0]);
    for (i = 0; i < 4; i++) {
      r += (s[i] > tol);
    }

    Z_size_idx_1 = -r;
    loop_ub = -r;
    for (i25 = 0; i25 < loop_ub; i25++) {
      for (i26 = 0; i26 < 5; i26++) {
        Z_data[i26 + 5 * i25] = V[i26 + 5 * ((r + i25) + 5)];
      }
    }
  }

  for (i25 = 0; i25 < 5; i25++) {
    for (i26 = 0; i26 < Z_size_idx_1; i26++) {
      v_data[i26 + Z_size_idx_1 * i25] = Z_data[i25 + 5 * i26];
    }
  }

  emxInit_real_T1(&u1, 1);

  /* -------------- input and states of the system--------------- */
  i25 = u1->size[0];
  u1->size[0] = u_mC->size[0];
  emxEnsureCapacity((emxArray__common *)u1, i25, sizeof(double));
  loop_ub = u_mC->size[0];
  for (i25 = 0; i25 < loop_ub; i25++) {
    u1->data[i25] = u_mC->data[i25].re;
  }

  emxInit_real_T1(&x1, 1);
  i25 = x1->size[0];
  x1->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)x1, i25, sizeof(double));
  loop_ub = y_mC->size[0];
  for (i25 = 0; i25 < loop_ub; i25++) {
    x1->data[i25] = y_mC->data[i25].re;
  }

  emxInit_real_T1(&x2, 1);
  i25 = x2->size[0];
  x2->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)x2, i25, sizeof(double));
  loop_ub = y_mC->size[0];
  for (i25 = 0; i25 < loop_ub; i25++) {
    x2->data[i25] = y_mC->data[i25].im;
  }

  /* r_2 = zeros(length(u1),1); */
  if (2 > x1->size[0]) {
    i25 = 0;
    i26 = 0;
  } else {
    i25 = 1;
    i26 = x1->size[0];
  }

  emxInit_real_T1(&u_dw_stacked1, 1);
  emxInit_real_T1(&r5, 1);
  tol = 2.0 * Ts;

  /*  -------------------second residual----------------------- */
  power(x1, u_dw_stacked1);
  power(x2, r5);
  i = u_dw_stacked1->size[0];
  emxEnsureCapacity((emxArray__common *)u_dw_stacked1, i, sizeof(double));
  loop_ub = u_dw_stacked1->size[0];
  for (i = 0; i < loop_ub; i++) {
    u_dw_stacked1->data[i] = (u_dw_stacked1->data[i] + r5->data[i]) * (Ts *
      x2->data[i]);
  }

  emxFree_real_T(&r5);
  emxFree_real_T(&x2);
  emxInit_real_T1(&b_x1, 1);
  i = b_x1->size[0];
  b_x1->size[0] = i26 - i25;
  emxEnsureCapacity((emxArray__common *)b_x1, i, sizeof(double));
  loop_ub = i26 - i25;
  for (i26 = 0; i26 < loop_ub; i26++) {
    b_x1->data[i26] = (-x1->data[i25 + i26] + x1->data[i26]) + (-Ts * x1->
      data[i26] + tol * u1->data[i26] * w12);
  }

  emxFree_real_T(&x1);
  for (i25 = 0; i25 < 5; i25++) {
    v[i25] = v_data[Z_size_idx_1 * i25];
  }

  conv(b_x1, v, r_2);
  emxFree_real_T(&b_x1);
  if (2 > u_dw_stacked1->size[0]) {
    i25 = 0;
    i26 = 0;
  } else {
    i25 = 1;
    i26 = u_dw_stacked1->size[0];
  }

  emxInit_real_T1(&b_u_dw_stacked1, 1);
  i = b_u_dw_stacked1->size[0];
  b_u_dw_stacked1->size[0] = i26 - i25;
  emxEnsureCapacity((emxArray__common *)b_u_dw_stacked1, i, sizeof(double));
  loop_ub = i26 - i25;
  for (i26 = 0; i26 < loop_ub; i26++) {
    b_u_dw_stacked1->data[i26] = u_dw_stacked1->data[i25 + i26];
  }

  emxFree_real_T(&u_dw_stacked1);
  tol = 0.0;
  Ts = 0.0;
  w12 = 0.0;
  d0 = 0.0;
  d1 = 0.0;
  d2 = 0.0;
  d3 = 0.0;
  d4 = 0.0;
  d5 = 0.0;
  d6 = 0.0;
  for (i25 = 0; i25 < 4; i25++) {
    tol += B_d[i25];
    s[i25] = 0.0;
    for (i26 = 0; i26 < 4; i26++) {
      s[i25] += A_d[i26 + (i25 << 2)];
    }

    Ts += s[i25] * B_d[i25];
    w12 += B_d[i25];
    dv4[i25] = 0.0;
    for (i26 = 0; i26 < 4; i26++) {
      dv4[i25] += y[i26 + (i25 << 2)];
    }

    d0 += dv4[i25] * B_d[i25];
    dv5[i25] = 0.0;
    for (i26 = 0; i26 < 4; i26++) {
      dv5[i25] += A_d[i26 + (i25 << 2)];
    }

    d1 += dv5[i25] * B_d[i25];
    d2 += B_d[i25];
    dv6[i25] = 0.0;
    for (i26 = 0; i26 < 4; i26++) {
      dv6[i25] += c_I[i26 + (i25 << 2)];
    }

    d3 += dv6[i25] * B_d[i25];
    dv7[i25] = 0.0;
    for (i26 = 0; i26 < 4; i26++) {
      dv7[i25] += b_y[i26 + (i25 << 2)];
    }

    d4 += dv7[i25] * B_d[i25];
    dv8[i25] = 0.0;
    for (i26 = 0; i26 < 4; i26++) {
      dv8[i25] += A_d[i26 + (i25 << 2)];
    }

    d5 += dv8[i25] * B_d[i25];
    d6 += B_d[i25];
  }

  Z_data[1] = tol;
  Z_data[6] = 0.0;
  Z_data[11] = 0.0;
  Z_data[16] = 0.0;
  Z_data[21] = 0.0;
  Z_data[2] = Ts;
  Z_data[7] = w12;
  Z_data[12] = 0.0;
  Z_data[17] = 0.0;
  Z_data[22] = 0.0;
  Z_data[3] = d0;
  Z_data[8] = d1;
  Z_data[13] = d2;
  Z_data[18] = 0.0;
  Z_data[23] = 0.0;
  Z_data[4] = d3;
  Z_data[9] = d4;
  Z_data[14] = d5;
  Z_data[19] = d6;
  Z_data[24] = 0.0;
  for (i25 = 0; i25 < 5; i25++) {
    Z_data[5 * i25] = 0.0;
    b_v[i25] = 0.0;
    for (i26 = 0; i26 < 5; i26++) {
      b_v[i25] += v_data[Z_size_idx_1 * i26] * Z_data[i26 + 5 * i25];
    }

    v[i25] = b_v[i25];
  }

  conv(b_u_dw_stacked1, v, u1);
  i25 = r_2->size[0];
  emxEnsureCapacity((emxArray__common *)r_2, i25, sizeof(double));
  loop_ub = r_2->size[0];
  emxFree_real_T(&b_u_dw_stacked1);
  for (i25 = 0; i25 < loop_ub; i25++) {
    r_2->data[i25] -= u1->data[i25];
  }

  emxFree_real_T(&u1);
}

/*
 * File trailer for f_compute_parity_Res2_full.c
 *
 * [EOF]
 */