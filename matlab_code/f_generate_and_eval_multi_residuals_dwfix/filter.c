/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filter.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "filter.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void filter(const emxArray_real_T *x, emxArray_real_T *y)
{
  unsigned int x_idx_0;
  int nx_m_nb;
  int nx;
  int jp;
  int k;
  int j;
  int naxpy;
  x_idx_0 = (unsigned int)x->size[0];
  nx_m_nb = y->size[0];
  y->size[0] = (int)x_idx_0;
  emxEnsureCapacity((emxArray__common *)y, nx_m_nb, sizeof(double));
  nx = x->size[0];
  jp = y->size[0];
  nx_m_nb = y->size[0];
  y->size[0] = jp;
  emxEnsureCapacity((emxArray__common *)y, nx_m_nb, sizeof(double));
  for (nx_m_nb = 0; nx_m_nb < jp; nx_m_nb++) {
    y->data[nx_m_nb] = 0.0;
  }

  if (x->size[0] >= 6) {
    for (k = 0; k < 3; k++) {
      for (j = k; j + 1 <= nx; j++) {
        y->data[j] += (0.5 + -0.5 * (double)k) * x->data[j - k];
      }
    }
  } else {
    if (x->size[0] > 3) {
      nx_m_nb = x->size[0] - 3;
    } else {
      nx_m_nb = 0;
    }

    jp = -1;
    for (k = 1; k <= nx_m_nb; k++) {
      jp++;
      for (j = 0; j < 3; j++) {
        y->data[jp + j] += x->data[jp] * (0.5 + -0.5 * (double)j);
      }
    }

    naxpy = x->size[0] - nx_m_nb;
    for (k = nx_m_nb + 1; k <= nx; k++) {
      jp++;
      for (j = 0; j + 1 <= naxpy; j++) {
        y->data[jp + j] += x->data[jp] * (0.5 + -0.5 * (double)j);
      }

      naxpy--;
    }
  }
}

/*
 * File trailer for filter.c
 *
 * [EOF]
 */
