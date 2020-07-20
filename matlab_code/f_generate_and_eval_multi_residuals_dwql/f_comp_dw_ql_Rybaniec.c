/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_comp_dw_ql_Rybaniec.c
 *
 * Code generation for function 'f_comp_dw_ql_Rybaniec'
 *
 */

/* Include files */
#include "f_comp_dw_ql_Rybaniec.h"
#include "diff.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "filter.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void f_comp_dw_ql_Rybaniec(const emxArray_creal_T *y_mC, const emxArray_creal_T *
  u_mC, double fs, double K, emxArray_real_T *dw, emxArray_real_T *w12)
{
  emxArray_real_T *P_I;
  int k;
  int nx;
  emxArray_real_T *P_Q;
  emxArray_real_T *r;
  double dt;
  double a;
  emxArray_real_T *r1;
  emxArray_real_T *r2;
  emxArray_real_T *y;
  emxArray_real_T *b_y;
  emxArray_real_T *r3;
  emxArray_real_T *b_y_mC;
  emxArray_real_T *r4;
  emxInit_real_T(&P_I, 1);
  k = P_I->size[0];
  P_I->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T(P_I, k);
  nx = y_mC->size[0];
  for (k = 0; k < nx; k++) {
    P_I->data[k] = y_mC->data[k].re;
  }

  emxInit_real_T(&P_Q, 1);
  k = P_Q->size[0];
  P_Q->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T(P_Q, k);
  nx = y_mC->size[0];
  for (k = 0; k < nx; k++) {
    P_Q->data[k] = y_mC->data[k].im;
  }

  emxInit_real_T(&r, 1);
  dt = 1.0 / fs;
  a = 2.0 * K;
  k = r->size[0];
  r->size[0] = u_mC->size[0];
  emxEnsureCapacity_real_T(r, k);
  nx = u_mC->size[0];
  for (k = 0; k < nx; k++) {
    r->data[k] = a * u_mC->data[k].im;
  }

  emxInit_real_T(&r1, 1);
  k = r1->size[0];
  r1->size[0] = P_Q->size[0];
  emxEnsureCapacity_real_T(r1, k);
  nx = P_Q->size[0];
  for (k = 0; k < nx; k++) {
    r1->data[k] = P_Q->data[k] * P_Q->data[k];
  }

  emxInit_real_T(&r2, 1);
  a = 2.0 * K;
  k = r2->size[0];
  r2->size[0] = u_mC->size[0];
  emxEnsureCapacity_real_T(r2, k);
  nx = u_mC->size[0];
  for (k = 0; k < nx; k++) {
    r2->data[k] = a * u_mC->data[k].re;
  }

  emxInit_real_T(&y, 1);
  k = y->size[0];
  y->size[0] = P_I->size[0];
  emxEnsureCapacity_real_T(y, k);
  nx = P_I->size[0];
  for (k = 0; k < nx; k++) {
    y->data[k] = P_I->data[k] * P_I->data[k];
  }

  emxInit_real_T(&b_y, 1);
  k = b_y->size[0];
  b_y->size[0] = P_I->size[0];
  emxEnsureCapacity_real_T(b_y, k);
  nx = P_I->size[0];
  for (k = 0; k < nx; k++) {
    b_y->data[k] = P_I->data[k] * P_I->data[k];
  }

  emxInit_real_T(&r3, 1);
  filter(P_Q, dw);
  filter(P_I, r3);
  k = dw->size[0];
  dw->size[0] = P_I->size[0];
  emxEnsureCapacity_real_T(dw, k);
  nx = P_I->size[0];
  for (k = 0; k < nx; k++) {
    dw->data[k] = P_I->data[k] * (dw->data[k] / dt - r->data[k]) / (y->data[k] +
      r1->data[k]) + P_Q->data[k] * (r2->data[k] - r3->data[k] / dt) /
      (b_y->data[k] + r1->data[k]);
  }

  emxInit_real_T(&b_y_mC, 1);
  k = b_y_mC->size[0];
  b_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T(b_y_mC, k);
  nx = y_mC->size[0];
  for (k = 0; k < nx; k++) {
    b_y_mC->data[k] = y_mC->data[k].re;
  }

  diff(b_y_mC, r3);
  k = b_y_mC->size[0];
  b_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity_real_T(b_y_mC, k);
  nx = y_mC->size[0];
  for (k = 0; k < nx; k++) {
    b_y_mC->data[k] = y_mC->data[k].im;
  }

  emxInit_real_T(&r4, 1);
  diff(b_y_mC, r4);
  k = y->size[0];
  y->size[0] = P_I->size[0];
  emxEnsureCapacity_real_T(y, k);
  nx = P_I->size[0];
  for (k = 0; k < nx; k++) {
    y->data[k] = P_I->data[k] * P_I->data[k];
  }

  k = b_y->size[0];
  b_y->size[0] = P_I->size[0];
  emxEnsureCapacity_real_T(b_y, k);
  nx = P_I->size[0];
  for (k = 0; k < nx; k++) {
    b_y->data[k] = P_I->data[k] * P_I->data[k];
  }

  nx = r3->size[0] - 1;
  k = w12->size[0];
  w12->size[0] = r3->size[0] + 1;
  emxEnsureCapacity_real_T(w12, k);
  w12->data[0] = P_I->data[0] * r2->data[0];
  for (k = 0; k <= nx; k++) {
    w12->data[k + 1] = P_I->data[k + 1] * (r2->data[k + 1] - r3->data[k] / dt);
  }

  emxFree_real_T(&r3);
  emxFree_real_T(&r2);
  emxFree_real_T(&P_I);
  nx = r4->size[0] - 1;
  k = b_y_mC->size[0];
  b_y_mC->size[0] = r4->size[0] + 1;
  emxEnsureCapacity_real_T(b_y_mC, k);
  b_y_mC->data[0] = P_Q->data[0] * r->data[0];
  for (k = 0; k <= nx; k++) {
    b_y_mC->data[k + 1] = P_Q->data[k + 1] * (r->data[k + 1] - r4->data[k] / dt);
  }

  emxFree_real_T(&r4);
  emxFree_real_T(&r);
  emxFree_real_T(&P_Q);
  nx = w12->size[0];
  for (k = 0; k < nx; k++) {
    w12->data[k] = w12->data[k] / (y->data[k] + r1->data[k]) + b_y_mC->data[k] /
      (b_y->data[k] + r1->data[k]);
  }

  emxFree_real_T(&b_y_mC);
  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  emxFree_real_T(&r1);

  /*  dw = smoothdata(dw,'movmean', smooth_dw); */
  /*  w12 = smoothdata(w12, 'movmean',  smooth_w12); */
  /*  ql = 2*pi*f0./(2*w12); */
  /*  w12_1 =... */
  /*      real(CAV_complex).*(2*K*real(FOR_complex_cal)-dVI)./abs(CAV_complex).^2; */
  /*  w12_2 =... */
  /*      imag(CAV_complex).*(2*K*imag(FOR_complex_cal)-dVQ)./abs(CAV_complex).^2; */
  /*   */
  /*  w12 = w12_1 + w12_2; */
}

/* End of code generation (f_comp_dw_ql_Rybaniec.c) */
