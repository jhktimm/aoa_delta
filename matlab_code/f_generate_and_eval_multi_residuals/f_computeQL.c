/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_computeQL.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_computeQL.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"
#include "abs.h"

/* Function Definitions */

/*
 * The quality factor of the cavity is determined by the decay time of the
 *  probes signal. Pulse cuts are considered, as the decay time is deduced
 *  from the pulses.
 * Arguments    : const emxArray_real_T *Rise
 *                const emxArray_creal_T *u_mCal
 *                const emxArray_creal_T *y_mC
 *                double fs
 *                double f0
 * Return Type  : double
 */
double f_computeQL(const emxArray_real_T *Rise, const emxArray_creal_T *u_mCal,
                   const emxArray_creal_T *y_mC, double fs, double f0)
{
  double QL;
  int rampup_smpls;
  emxArray_creal_T *b_u_mCal;
  int absb;
  int i;
  emxArray_real_T *idx_u_mCal_off;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int nx;
  int idx;
  boolean_T exitg1;
  emxArray_int32_T *r9;
  emxArray_real_T *r10;
  double ndbl;
  double apnd;
  double cdiff;
  unsigned int absa;
  emxArray_real_T *lnA;
  unsigned int u1;
  if (fs > 1.0E+6) {
    rampup_smpls = 30;
  } else {
    rampup_smpls = 3;
  }

  emxInit_creal_T(&b_u_mCal, 1);
  absb = u_mCal->size[0];
  i = b_u_mCal->size[0];
  b_u_mCal->size[0] = absb;
  emxEnsureCapacity_creal_T(b_u_mCal, i);
  for (i = 0; i < absb; i++) {
    b_u_mCal->data[i] = u_mCal->data[i];
  }

  emxInit_real_T1(&idx_u_mCal_off, 1);
  emxInit_boolean_T(&x, 1);
  b_abs(b_u_mCal, idx_u_mCal_off);
  i = x->size[0];
  x->size[0] = idx_u_mCal_off->size[0];
  emxEnsureCapacity_boolean_T(x, i);
  absb = idx_u_mCal_off->size[0];
  for (i = 0; i < absb; i++) {
    x->data[i] = (idx_u_mCal_off->data[i] < 1.5);
  }

  emxInit_int32_T(&ii, 1);
  nx = x->size[0];
  idx = 0;
  i = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity_int32_T(ii, i);
  absb = 1;
  exitg1 = false;
  while ((!exitg1) && (absb <= nx)) {
    if (x->data[absb - 1]) {
      idx++;
      ii->data[idx - 1] = absb;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        absb++;
      }
    } else {
      absb++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity_int32_T(ii, i);
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

  emxFree_boolean_T(&x);
  i = idx_u_mCal_off->size[0];
  idx_u_mCal_off->size[0] = ii->size[0];
  emxEnsureCapacity_real_T1(idx_u_mCal_off, i);
  absb = ii->size[0];
  for (i = 0; i < absb; i++) {
    idx_u_mCal_off->data[i] = ii->data[i];
  }

  emxFree_int32_T(&ii);
  idx = idx_u_mCal_off->size[0] - 1;
  absb = 0;
  for (i = 0; i <= idx; i++) {
    if (idx_u_mCal_off->data[i] > Rise->data[0] + (double)rampup_smpls) {
      absb++;
    }
  }

  emxInit_int32_T(&r9, 1);
  i = r9->size[0];
  r9->size[0] = absb;
  emxEnsureCapacity_int32_T(r9, i);
  absb = 0;
  for (i = 0; i <= idx; i++) {
    if (idx_u_mCal_off->data[i] > Rise->data[0] + (double)rampup_smpls) {
      r9->data[absb] = i + 1;
      absb++;
    }
  }

  emxInit_real_T(&r10, 2);
  if (u_mCal->size[0] < (int)idx_u_mCal_off->data[r9->data[0] - 1]) {
    i = r10->size[0] * r10->size[1];
    r10->size[1] = 0;
    emxEnsureCapacity_real_T(r10, i);
  } else if (idx_u_mCal_off->data[r9->data[0] - 1] == idx_u_mCal_off->data
             [r9->data[0] - 1]) {
    ndbl = idx_u_mCal_off->data[r9->data[0] - 1];
    i = u_mCal->size[0];
    absb = r10->size[0] * r10->size[1];
    r10->size[0] = 1;
    r10->size[1] = (int)floor((double)i - ndbl) + 1;
    emxEnsureCapacity_real_T(r10, absb);
    absb = (int)floor((double)i - ndbl);
    for (i = 0; i <= absb; i++) {
      r10->data[r10->size[0] * i] = ndbl + (double)i;
    }
  } else {
    ndbl = floor(((double)u_mCal->size[0] - idx_u_mCal_off->data[r9->data[0] - 1])
                 + 0.5);
    apnd = idx_u_mCal_off->data[r9->data[0] - 1] + ndbl;
    cdiff = apnd - (double)u_mCal->size[0];
    absa = (unsigned int)fabs(idx_u_mCal_off->data[r9->data[0] - 1]);
    absb = u_mCal->size[0];
    u1 = (unsigned int)absb;
    if (absa > u1) {
      u1 = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * (double)u1) {
      ndbl++;
      apnd = u_mCal->size[0];
    } else if (cdiff > 0.0) {
      apnd = idx_u_mCal_off->data[r9->data[0] - 1] + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      idx = (int)ndbl;
    } else {
      idx = 0;
    }

    i = r10->size[0] * r10->size[1];
    r10->size[0] = 1;
    r10->size[1] = idx;
    emxEnsureCapacity_real_T(r10, i);
    if (idx > 0) {
      r10->data[0] = idx_u_mCal_off->data[r9->data[0] - 1];
      if (idx > 1) {
        r10->data[idx - 1] = apnd;
        absb = (idx - 1) / 2;
        for (i = 1; i < absb; i++) {
          r10->data[i] = idx_u_mCal_off->data[r9->data[0] - 1] + (double)i;
          r10->data[(idx - i) - 1] = apnd - (double)i;
        }

        if (absb << 1 == idx - 1) {
          r10->data[absb] = (idx_u_mCal_off->data[r9->data[0] - 1] + apnd) / 2.0;
        } else {
          r10->data[absb] = idx_u_mCal_off->data[r9->data[0] - 1] + (double)absb;
          r10->data[absb + 1] = apnd - (double)absb;
        }
      }
    }
  }

  emxInit_real_T1(&lnA, 1);
  i = lnA->size[0];
  lnA->size[0] = r10->size[1];
  emxEnsureCapacity_real_T1(lnA, i);
  absb = r10->size[1];
  for (i = 0; i < absb; i++) {
    lnA->data[i] = 0.0;
  }

  apnd = idx_u_mCal_off->data[r9->data[0] - 1];
  ndbl = (double)r10->size[1] - 1.0;
  i = b_u_mCal->size[0];
  b_u_mCal->size[0] = (int)ndbl + 1;
  emxEnsureCapacity_creal_T(b_u_mCal, i);
  absb = (int)ndbl;
  emxFree_int32_T(&r9);
  for (i = 0; i <= absb; i++) {
    b_u_mCal->data[i] = y_mC->data[(int)(apnd + (double)i) - 1];
  }

  b_abs(b_u_mCal, idx_u_mCal_off);
  nx = idx_u_mCal_off->size[0];
  i = 0;
  emxFree_creal_T(&b_u_mCal);
  while (i + 1 <= nx) {
    idx_u_mCal_off->data[i] = log(idx_u_mCal_off->data[i]);
    i++;
  }

  absb = idx_u_mCal_off->size[0];
  emxFree_real_T(&r10);
  for (i = 0; i < absb; i++) {
    lnA->data[i] = idx_u_mCal_off->data[i];
  }

  emxFree_real_T(&idx_u_mCal_off);
  i = lnA->size[0];
  QL = 3.1415926535897931 * f0 * fabs(1.0 / ((lnA->data[lnA->size[0] - 1] -
    lnA->data[0]) / ((double)i / fs)));

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

/*
 * File trailer for f_computeQL.c
 *
 * [EOF]
 */
