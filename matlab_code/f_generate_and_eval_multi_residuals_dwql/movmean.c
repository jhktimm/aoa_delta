/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * movmean.c
 *
 * Code generation for function 'movmean'
 *
 */

/* Include files */
#include "movmean.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void movmean(const emxArray_real_T *x, emxArray_real_T *y)
{
  int len;
  unsigned int szy[2];
  int i;
  int nToCopy;
  int stride;
  int k;
  int outsize_idx_0;
  emxArray_real_T *xv;
  emxArray_real_T *yv;
  int nx;
  int j;
  int tunableEnvironment_idx_0;
  double buf[100];
  int b_k;
  double b_y;
  len = 2;
  if (x->size[0] != 1) {
    len = 1;
  }

  szy[0] = (unsigned int)x->size[0];
  szy[1] = 1U;
  if (len <= 1) {
    szy[len - 1] = (unsigned int)x->size[0];
  } else {
    szy[len - 1] = 1U;
  }

  i = y->size[0] * y->size[1];
  y->size[0] = (int)szy[0];
  y->size[1] = (int)szy[1];
  emxEnsureCapacity_real_T(y, i);
  nToCopy = (int)szy[0] * (int)szy[1];
  for (i = 0; i < nToCopy; i++) {
    y->data[i] = 0.0;
  }

  if (len <= 1) {
    i = x->size[0];
  } else {
    i = 1;
  }

  stride = 1;
  for (k = 0; k <= len - 2; k++) {
    stride *= x->size[0];
  }

  if (0 <= stride - 1) {
    outsize_idx_0 = i;
    if (len <= 1) {
      nx = x->size[0] - 1;
    } else {
      nx = 0;
    }
  }

  emxInit_real_T(&xv, 1);
  emxInit_real_T(&yv, 1);
  for (j = 0; j < stride; j++) {
    tunableEnvironment_idx_0 = j + 1;
    len = xv->size[0];
    xv->size[0] = outsize_idx_0;
    emxEnsureCapacity_real_T(xv, len);
    for (len = 0; len < outsize_idx_0; len++) {
      xv->data[len] = 0.0;
    }

    for (k = 0; k < i; k++) {
      xv->data[k] = x->data[(tunableEnvironment_idx_0 + k * stride) - 1];
    }

    len = yv->size[0];
    yv->size[0] = xv->size[0];
    emxEnsureCapacity_real_T(yv, len);
    nToCopy = xv->size[0];
    for (len = 0; len < nToCopy; len++) {
      yv->data[len] = 0.0;
    }

    memset(&buf[0], 0, 100U * sizeof(double));
    for (k = 0; k <= nx; k++) {
      if (k + 1 <= 50) {
        len = -50;
      } else {
        len = k - 100;
      }

      if (k + 50 > xv->size[0]) {
        b_k = xv->size[0] - 50;
      } else {
        b_k = k;
      }

      nToCopy = b_k - len;
      for (b_k = 0; b_k < nToCopy; b_k++) {
        buf[b_k] = xv->data[(len + b_k) + 50];
      }

      if (nToCopy == 0) {
        b_y = 0.0;
      } else {
        b_y = buf[0];
        for (b_k = 2; b_k <= nToCopy; b_k++) {
          b_y += buf[b_k - 1];
        }
      }

      yv->data[k] = b_y / (double)nToCopy;
    }

    len = yv->size[0];
    for (k = 0; k < len; k++) {
      y->data[(tunableEnvironment_idx_0 + k * stride) - 1] = yv->data[k];
    }
  }

  emxFree_real_T(&yv);
  emxFree_real_T(&xv);
}

/* End of code generation (movmean.c) */
