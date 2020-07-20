/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * filter.c
 *
 * Code generation for function 'filter'
 *
 */

/* Include files */
#include "filter.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void filter(const emxArray_real_T *x, emxArray_real_T *y)
{
  int nx;
  int nx_m_nb;
  int i;
  int k;
  int j;
  int naxpy;
  nx = x->size[0];
  nx_m_nb = x->size[0];
  i = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity_real_T(y, i);
  for (i = 0; i < nx_m_nb; i++) {
    y->data[i] = 0.0;
  }

  if (x->size[0] >= 6) {
    for (k = 0; k < 3; k++) {
      nx_m_nb = k + 1;
      for (j = nx_m_nb; j <= nx; j++) {
        y->data[j - 1] += (-0.5 * (double)k + 0.5) * x->data[(j - k) - 1];
      }
    }
  } else {
    if (x->size[0] > 3) {
      nx_m_nb = x->size[0] - 4;
    } else {
      nx_m_nb = -1;
    }

    for (k = 0; k <= nx_m_nb; k++) {
      y->data[k] += x->data[k] * 0.5;
      y->data[k + 1] += x->data[k] * 0.0;
      y->data[k + 2] += x->data[k] * -0.5;
    }

    naxpy = x->size[0] - nx_m_nb;
    i = nx_m_nb + 2;
    for (k = i; k <= nx; k++) {
      for (j = 0; j <= naxpy - 2; j++) {
        nx_m_nb = (k + j) - 1;
        y->data[nx_m_nb] += x->data[k - 1] * (-0.5 * (double)j + 0.5);
      }

      naxpy--;
    }
  }
}

/* End of code generation (filter.c) */
