/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_computeQL.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Sep-2019 16:47:25
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_computeQL.h"
#include "f_generate_and_eval_residual_emxutil.h"
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
  emxArray_creal_T *b_u_mCal;
  int absb;
  int i8;
  emxArray_real_T *idx_u_mCal_off;
  emxArray_boolean_T *x;
  emxArray_int32_T *ii;
  int nx;
  int idx;
  boolean_T exitg1;
  int end;
  emxArray_int32_T *r3;
  emxArray_real_T *r4;
  double ndbl;
  double apnd;
  double cdiff;
  unsigned int absa;
  emxArray_real_T *lnA;
  unsigned int u1;
  emxInit_creal_T(&b_u_mCal, 1);
  absb = u_mCal->size[0];
  i8 = b_u_mCal->size[0];
  b_u_mCal->size[0] = absb;
  emxEnsureCapacity_creal_T(b_u_mCal, i8);
  for (i8 = 0; i8 < absb; i8++) {
    b_u_mCal->data[i8] = u_mCal->data[i8];
  }

  emxInit_real_T1(&idx_u_mCal_off, 1);
  emxInit_boolean_T(&x, 1);
  b_abs(b_u_mCal, idx_u_mCal_off);
  i8 = x->size[0];
  x->size[0] = idx_u_mCal_off->size[0];
  emxEnsureCapacity_boolean_T(x, i8);
  absb = idx_u_mCal_off->size[0];
  for (i8 = 0; i8 < absb; i8++) {
    x->data[i8] = (idx_u_mCal_off->data[i8] < 1.5);
  }

  emxInit_int32_T(&ii, 1);
  nx = x->size[0];
  idx = 0;
  i8 = ii->size[0];
  ii->size[0] = x->size[0];
  emxEnsureCapacity_int32_T(ii, i8);
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
      i8 = ii->size[0];
      ii->size[0] = 0;
      emxEnsureCapacity_int32_T(ii, i8);
    }
  } else {
    i8 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity_int32_T(ii, i8);
  }

  emxFree_boolean_T(&x);
  i8 = idx_u_mCal_off->size[0];
  idx_u_mCal_off->size[0] = ii->size[0];
  emxEnsureCapacity_real_T1(idx_u_mCal_off, i8);
  absb = ii->size[0];
  for (i8 = 0; i8 < absb; i8++) {
    idx_u_mCal_off->data[i8] = ii->data[i8];
  }

  emxFree_int32_T(&ii);
  end = idx_u_mCal_off->size[0] - 1;
  absb = 0;
  for (idx = 0; idx <= end; idx++) {
    if (idx_u_mCal_off->data[idx] > Rise->data[0] + 3.0) {
      absb++;
    }
  }

  emxInit_int32_T(&r3, 1);
  i8 = r3->size[0];
  r3->size[0] = absb;
  emxEnsureCapacity_int32_T(r3, i8);
  absb = 0;
  for (idx = 0; idx <= end; idx++) {
    if (idx_u_mCal_off->data[idx] > Rise->data[0] + 3.0) {
      r3->data[absb] = idx + 1;
      absb++;
    }
  }

  emxInit_real_T(&r4, 2);
  if (u_mCal->size[0] < (int)idx_u_mCal_off->data[r3->data[0] - 1]) {
    i8 = r4->size[0] * r4->size[1];
    r4->size[1] = 0;
    emxEnsureCapacity_real_T(r4, i8);
  } else if (idx_u_mCal_off->data[r3->data[0] - 1] == idx_u_mCal_off->data
             [r3->data[0] - 1]) {
    ndbl = idx_u_mCal_off->data[r3->data[0] - 1];
    i8 = u_mCal->size[0];
    absb = r4->size[0] * r4->size[1];
    r4->size[0] = 1;
    r4->size[1] = (int)floor((double)i8 - ndbl) + 1;
    emxEnsureCapacity_real_T(r4, absb);
    absb = (int)floor((double)i8 - ndbl);
    for (i8 = 0; i8 <= absb; i8++) {
      r4->data[r4->size[0] * i8] = ndbl + (double)i8;
    }
  } else {
    ndbl = floor(((double)u_mCal->size[0] - idx_u_mCal_off->data[r3->data[0] - 1])
                 + 0.5);
    apnd = idx_u_mCal_off->data[r3->data[0] - 1] + ndbl;
    cdiff = apnd - (double)u_mCal->size[0];
    absa = (unsigned int)fabs(idx_u_mCal_off->data[r3->data[0] - 1]);
    absb = u_mCal->size[0];
    u1 = (unsigned int)absb;
    if (absa > u1) {
      u1 = absa;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * (double)u1) {
      ndbl++;
      apnd = u_mCal->size[0];
    } else if (cdiff > 0.0) {
      apnd = idx_u_mCal_off->data[r3->data[0] - 1] + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      idx = (int)ndbl;
    } else {
      idx = 0;
    }

    i8 = r4->size[0] * r4->size[1];
    r4->size[0] = 1;
    r4->size[1] = idx;
    emxEnsureCapacity_real_T(r4, i8);
    if (idx > 0) {
      r4->data[0] = idx_u_mCal_off->data[r3->data[0] - 1];
      if (idx > 1) {
        r4->data[idx - 1] = apnd;
        absb = (idx - 1) / 2;
        for (end = 1; end < absb; end++) {
          r4->data[end] = idx_u_mCal_off->data[r3->data[0] - 1] + (double)end;
          r4->data[(idx - end) - 1] = apnd - (double)end;
        }

        if (absb << 1 == idx - 1) {
          r4->data[absb] = (idx_u_mCal_off->data[r3->data[0] - 1] + apnd) / 2.0;
        } else {
          r4->data[absb] = idx_u_mCal_off->data[r3->data[0] - 1] + (double)absb;
          r4->data[absb + 1] = apnd - (double)absb;
        }
      }
    }
  }

  emxInit_real_T1(&lnA, 1);
  i8 = lnA->size[0];
  lnA->size[0] = r4->size[1];
  emxEnsureCapacity_real_T1(lnA, i8);
  absb = r4->size[1];
  for (i8 = 0; i8 < absb; i8++) {
    lnA->data[i8] = 0.0;
  }

  apnd = idx_u_mCal_off->data[r3->data[0] - 1];
  ndbl = (double)r4->size[1] - 1.0;
  i8 = b_u_mCal->size[0];
  b_u_mCal->size[0] = (int)ndbl + 1;
  emxEnsureCapacity_creal_T(b_u_mCal, i8);
  absb = (int)ndbl;
  emxFree_int32_T(&r3);
  for (i8 = 0; i8 <= absb; i8++) {
    b_u_mCal->data[i8] = y_mC->data[(int)(apnd + (double)i8) - 1];
  }

  b_abs(b_u_mCal, idx_u_mCal_off);
  nx = idx_u_mCal_off->size[0];
  end = 0;
  emxFree_creal_T(&b_u_mCal);
  while (end + 1 <= nx) {
    idx_u_mCal_off->data[end] = log(idx_u_mCal_off->data[end]);
    end++;
  }

  absb = idx_u_mCal_off->size[0];
  emxFree_real_T(&r4);
  for (i8 = 0; i8 < absb; i8++) {
    lnA->data[i8] = idx_u_mCal_off->data[i8];
  }

  emxFree_real_T(&idx_u_mCal_off);
  i8 = lnA->size[0];
  QL = 3.1415926535897931 * f0 * fabs(1.0 / ((lnA->data[lnA->size[0] - 1] -
    lnA->data[0]) / ((double)i8 / fs)));

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
