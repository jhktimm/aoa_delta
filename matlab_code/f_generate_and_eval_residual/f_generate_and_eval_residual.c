/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_and_eval_residual.c
 *
 * Code generation for function 'f_generate_and_eval_residual'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "mldivide.h"
#include "f_generate_and_eval_residual_emxutil.h"
#include "f_generate_online_UKF_residual_full.h"

/* Function Definitions */
void f_generate_and_eval_residual(const emxArray_real_T *PA, const
  emxArray_real_T *PP, const emxArray_real_T *FA, const emxArray_real_T *FP,
  const emxArray_real_T *RA, const emxArray_real_T *RP, double FS, double F0,
  const creal_T cal_coeff[4], const double tau_m[4], const double K_m[4], const
  double X0[4], double QL_nom, double DELAY, double FILLING, double FLATTOP,
  const double Sigma_nom[4], const double r_mean_nom[2], const double
  MeasNoiseVar[4], const double ProcessVar[36], emxArray_creal_T *r_cmplx,
  emxArray_real_T *s_max)
{
  int ixstart;
  int n;
  double s;
  emxArray_real_T *res_full_mean;
  int ix;
  emxArray_real_T *y;
  boolean_T exitg1;
  emxArray_real_T *res_full_variance;
  int i0;
  int ii;
  double y_bar[2];
  emxArray_real_T *b_s_max;
  static const double dv0[4] = { 1.0, 0.0, 0.0, 1.0 };

  double b[4];
  double dv1[2];
  (void)F0;
  (void)DELAY;
  (void)FILLING;
  (void)FLATTOP;

  /*  This function evaluates the residual */
  ixstart = 1;
  n = PA->size[0];
  s = PA->data[0];
  if (PA->size[0] > 1) {
    if (rtIsNaN(PA->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(PA->data[ix - 1])) {
          s = PA->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < PA->size[0]) {
      while (ixstart + 1 <= n) {
        if (PA->data[ixstart] > s) {
          s = PA->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  emxInit_real_T(&res_full_mean, 2);
  emxInit_real_T(&y, 2);
  if (s < 10.0) {
    i0 = res_full_mean->size[0] * res_full_mean->size[1];
    res_full_mean->size[0] = 1;
    res_full_mean->size[1] = 1;
    emxEnsureCapacity((emxArray__common *)res_full_mean, i0, sizeof(double));
    res_full_mean->data[0] = rtNaN;
  } else {
    emxInit_real_T1(&res_full_variance, 3);
    c_f_generate_online_UKF_residua(PA, PP, FA, FP, RA, RP, FS, cal_coeff, tau_m,
      K_m, X0, QL_nom, MeasNoiseVar, ProcessVar, y, res_full_variance);
    i0 = res_full_mean->size[0] * res_full_mean->size[1];
    res_full_mean->size[0] = 2;
    res_full_mean->size[1] = y->size[1];
    emxEnsureCapacity((emxArray__common *)res_full_mean, i0, sizeof(double));
    ixstart = y->size[0] * y->size[1];
    emxFree_real_T(&res_full_variance);
    for (i0 = 0; i0 < ixstart; i0++) {
      res_full_mean->data[i0] = y->data[i0];
    }
  }

  ixstart = res_full_mean->size[1];
  i0 = r_cmplx->size[0];
  r_cmplx->size[0] = ixstart;
  emxEnsureCapacity((emxArray__common *)r_cmplx, i0, sizeof(creal_T));
  for (i0 = 0; i0 < ixstart; i0++) {
    r_cmplx->data[i0].re = res_full_mean->data[res_full_mean->size[0] * i0] +
      0.0 * res_full_mean->data[1 + res_full_mean->size[0] * i0];
    r_cmplx->data[i0].im = res_full_mean->data[1 + res_full_mean->size[0] * i0];
  }

  if (res_full_mean->size[1] == 0) {
    n = 0;
  } else if (res_full_mean->size[0] > res_full_mean->size[1]) {
    n = 2;
  } else {
    n = res_full_mean->size[1];
  }

  i0 = y->size[0] * y->size[1];
  y->size[0] = 2;
  y->size[1] = n;
  emxEnsureCapacity((emxArray__common *)y, i0, sizeof(double));
  ixstart = n << 1;
  for (i0 = 0; i0 < ixstart; i0++) {
    y->data[i0] = 0.0;
  }

  if (res_full_mean->size[1] == 0) {
    n = 0;
  } else if (res_full_mean->size[0] > res_full_mean->size[1]) {
    n = 2;
  } else {
    n = res_full_mean->size[1];
  }

  for (ii = 0; ii < n; ii++) {
    ixstart = res_full_mean->size[0];
    for (i0 = 0; i0 < ixstart; i0++) {
      y_bar[i0] = res_full_mean->data[i0 + res_full_mean->size[0] * ii];
    }

    for (i0 = 0; i0 < 2; i0++) {
      y->data[i0 + y->size[0] * ii] = y_bar[i0] - r_mean_nom[i0];
    }
  }

  emxFree_real_T(&res_full_mean);

  /*  The Generalized likelihood test adapted from S.Ding Model Based Fault Detection, */
  /*  Algorithm 10.4  */
  ixstart = y->size[1];
  if (2 > ixstart) {
    ixstart = 2;
  }

  if (y->size[1] == 0) {
    n = 0;
  } else {
    n = ixstart;
  }

  emxInit_real_T(&b_s_max, 2);
  i0 = b_s_max->size[0] * b_s_max->size[1];
  b_s_max->size[0] = 1;
  b_s_max->size[1] = n;
  emxEnsureCapacity((emxArray__common *)b_s_max, i0, sizeof(double));
  for (i0 = 0; i0 < n; i0++) {
    b_s_max->data[i0] = 0.0;
  }

  ixstart = y->size[1];
  if (2 > ixstart) {
    ixstart = 2;
  }

  if (y->size[1] == 0) {
    n = 0;
  } else {
    n = ixstart;
  }

  for (ii = 0; ii <= n - 12; ii++) {
    for (ixstart = 0; ixstart < 2; ixstart++) {
      s = y->data[ixstart % 2 + y->size[0] * (ixstart / 2 + ii)];
      for (ix = 0; ix < 10; ix++) {
        i0 = ixstart + ((ix + 1) << 1);
        s += y->data[i0 % 2 + y->size[0] * (i0 / 2 + ii)];
      }

      y_bar[ixstart] = 0.1 * s;
    }

    mldivide(Sigma_nom, dv0, b);
    s = 0.0;
    for (i0 = 0; i0 < 2; i0++) {
      dv1[i0] = 0.0;
      for (ixstart = 0; ixstart < 2; ixstart++) {
        dv1[i0] += 5.0 * y_bar[ixstart] * b[ixstart + (i0 << 1)];
      }

      s += dv1[i0] * y_bar[i0];
    }

    b_s_max->data[ii] = s;
  }

  emxFree_real_T(&y);
  i0 = s_max->size[0];
  s_max->size[0] = b_s_max->size[1];
  emxEnsureCapacity((emxArray__common *)s_max, i0, sizeof(double));
  ixstart = b_s_max->size[1];
  for (i0 = 0; i0 < ixstart; i0++) {
    s_max->data[i0] = b_s_max->data[b_s_max->size[0] * i0];
  }

  emxFree_real_T(&b_s_max);
}

/* End of code generation (f_generate_and_eval_residual.c) */
