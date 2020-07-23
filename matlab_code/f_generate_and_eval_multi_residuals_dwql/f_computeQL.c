/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_computeQL.c
 *
 * Code generation for function 'f_computeQL'
 *
 */

/* Include files */
#include "f_computeQL.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "f_generate_and_eval_multi_residuals_dwql_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double f_computeQL(const emxArray_real_T *Rise, const emxArray_creal_T *u_mCal,
                   const emxArray_creal_T *y_mC, double fs, double f0)
{
  double QL;
  emxArray_creal_T *x;
  int rampup_smpls;
  int ndbl;
  int i;
  emxArray_real_T *idx_u_mCal_off;
  int nx;
  int idx;
  emxArray_boolean_T *b_x;
  emxArray_int32_T *ii;
  boolean_T exitg1;
  emxArray_int32_T *r;
  double d;
  emxArray_real_T *r1;
  double apnd;
  emxArray_real_T *lnA;
  double cdiff;
  emxInit_creal_T(&x, 1);

  /*  The quality factor of the cavity is determined by the decay time of the */
  /*  probes signal. Pulse cuts are considered, as the decay time is deduced */
  /*  from the pulses. */
  if (fs > 1.0E+6) {
    rampup_smpls = 30;
  } else {
    rampup_smpls = 3;
  }

  ndbl = u_mCal->size[0];
  i = x->size[0];
  x->size[0] = u_mCal->size[0];
  emxEnsureCapacity_creal_T(x, i);
  for (i = 0; i < ndbl; i++) {
    x->data[i] = u_mCal->data[i];
  }

  emxInit_real_T(&idx_u_mCal_off, 1);
  nx = u_mCal->size[0];
  i = idx_u_mCal_off->size[0];
  idx_u_mCal_off->size[0] = u_mCal->size[0];
  emxEnsureCapacity_real_T(idx_u_mCal_off, i);
  for (idx = 0; idx < nx; idx++) {
    idx_u_mCal_off->data[idx] = rt_hypotd_snf(x->data[idx].re, x->data[idx].im);
  }

  emxInit_boolean_T(&b_x, 1);
  i = b_x->size[0];
  b_x->size[0] = idx_u_mCal_off->size[0];
  emxEnsureCapacity_boolean_T(b_x, i);
  ndbl = idx_u_mCal_off->size[0];
  for (i = 0; i < ndbl; i++) {
    b_x->data[i] = (idx_u_mCal_off->data[i] < 1.5);
  }

  emxInit_int32_T(&ii, 1);
  nx = b_x->size[0];
  idx = 0;
  i = ii->size[0];
  ii->size[0] = b_x->size[0];
  emxEnsureCapacity_int32_T(ii, i);
  ndbl = 0;
  exitg1 = false;
  while ((!exitg1) && (ndbl <= nx - 1)) {
    if (b_x->data[ndbl]) {
      idx++;
      ii->data[idx - 1] = ndbl + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ndbl++;
      }
    } else {
      ndbl++;
    }
  }

  if (b_x->size[0] == 1) {
    if (idx == 0) {
      ii->size[0] = 0;
    }
  } else {
    i = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity_int32_T(ii, i);
  }

  emxFree_boolean_T(&b_x);
  i = idx_u_mCal_off->size[0];
  idx_u_mCal_off->size[0] = ii->size[0];
  emxEnsureCapacity_real_T(idx_u_mCal_off, i);
  ndbl = ii->size[0];
  for (i = 0; i < ndbl; i++) {
    idx_u_mCal_off->data[i] = ii->data[i];
  }

  emxFree_int32_T(&ii);
  idx = idx_u_mCal_off->size[0] - 1;
  ndbl = 0;
  for (nx = 0; nx <= idx; nx++) {
    if (idx_u_mCal_off->data[nx] > Rise->data[0] + (double)rampup_smpls) {
      ndbl++;
    }
  }

  emxInit_int32_T(&r, 1);
  i = r->size[0];
  r->size[0] = ndbl;
  emxEnsureCapacity_int32_T(r, i);
  ndbl = 0;
  for (nx = 0; nx <= idx; nx++) {
    if (idx_u_mCal_off->data[nx] > Rise->data[0] + (double)rampup_smpls) {
      r->data[ndbl] = nx + 1;
      ndbl++;
    }
  }

  d = idx_u_mCal_off->data[r->data[0] - 1];
  nx = (int)d;
  emxInit_real_T(&r1, 2);
  if (u_mCal->size[0] < nx) {
    r1->size[1] = 0;
  } else if (d == d) {
    i = r1->size[0] * r1->size[1];
    r1->size[1] = (int)floor((double)u_mCal->size[0] - d) + 1;
    emxEnsureCapacity_real_T(r1, i);
  } else {
    ndbl = (int)floor(((double)u_mCal->size[0] - d) + 0.5);
    apnd = d + (double)ndbl;
    cdiff = apnd - (double)u_mCal->size[0];
    idx = u_mCal->size[0];
    if (nx > idx) {
      idx = nx;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * (double)idx) {
      ndbl++;
      apnd = u_mCal->size[0];
    } else if (cdiff > 0.0) {
      apnd = d + ((double)ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl < 0) {
      ndbl = 0;
    }

    i = r1->size[0] * r1->size[1];
    r1->size[0] = 1;
    r1->size[1] = ndbl;
    emxEnsureCapacity_real_T(r1, i);
    if ((ndbl > 0) && (ndbl > 1)) {
      r1->data[ndbl - 1] = apnd;
      nx = (ndbl - 1) / 2;
      for (idx = 0; idx <= nx - 2; idx++) {
        i = idx + 1;
        r1->data[idx + 1] = d + (double)i;
        r1->data[(ndbl - idx) - 2] = apnd - (double)i;
      }

      if (nx << 1 == ndbl - 1) {
        r1->data[nx] = (d + apnd) / 2.0;
      } else {
        r1->data[nx] = d + (double)nx;
        r1->data[nx + 1] = apnd - (double)nx;
      }
    }
  }

  emxInit_real_T(&lnA, 1);
  i = lnA->size[0];
  lnA->size[0] = r1->size[1];
  emxEnsureCapacity_real_T(lnA, i);
  ndbl = r1->size[1];
  for (i = 0; i < ndbl; i++) {
    lnA->data[i] = 0.0;
  }

  i = x->size[0];
  x->size[0] = r1->size[1];
  emxEnsureCapacity_creal_T(x, i);
  ndbl = r1->size[1] - 1;
  for (i = 0; i <= ndbl; i++) {
    x->data[i] = y_mC->data[(int)(i + (unsigned int)idx_u_mCal_off->data[r->
      data[0] - 1]) - 1];
  }

  emxFree_int32_T(&r);
  nx = r1->size[1] - 1;
  i = idx_u_mCal_off->size[0];
  idx_u_mCal_off->size[0] = r1->size[1];
  emxEnsureCapacity_real_T(idx_u_mCal_off, i);
  emxFree_real_T(&r1);
  for (idx = 0; idx <= nx; idx++) {
    idx_u_mCal_off->data[idx] = rt_hypotd_snf(x->data[idx].re, x->data[idx].im);
  }

  emxFree_creal_T(&x);
  nx = idx_u_mCal_off->size[0];
  for (idx = 0; idx < nx; idx++) {
    idx_u_mCal_off->data[idx] = log(idx_u_mCal_off->data[idx]);
  }

  ndbl = idx_u_mCal_off->size[0];
  for (i = 0; i < ndbl; i++) {
    lnA->data[i] = idx_u_mCal_off->data[i];
  }

  emxFree_real_T(&idx_u_mCal_off);
  QL = 3.1415926535897931 * f0 * fabs(1.0 / ((lnA->data[lnA->size[0] - 1] -
    lnA->data[0]) / ((double)lnA->size[0] / fs)));

  /*  for ii = 1:150: size(u_mCal,2) */
  /*  figure(55) */
  /*  plot(abs(y_mC(:,ii)),'k') */
  /*  hold on */
  /*  plot(idx_u_mCal_cut(1,ii) : idx_u_mCal_cut(1,ii) + decay_length,... */
  /*      abs(y_mC(idx_u_mCal_cut(1,ii) : idx_u_mCal_cut(1,ii) + decay_length,ii)),'r--') */
  /*       */
  /*  end */
  emxFree_real_T(&lnA);
  return QL;
}

/* End of code generation (f_computeQL.c) */
