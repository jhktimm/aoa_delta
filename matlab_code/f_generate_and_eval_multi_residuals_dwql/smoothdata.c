/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * smoothdata.c
 *
 * Code generation for function 'smoothdata'
 *
 */

/* Include files */
#include "smoothdata.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void smoothdata(const emxArray_real_T *A, emxArray_real_T *B)
{
  emxArray_real_T *Bd;
  int nToCopy;
  int u1;
  int b_u1;
  int nx;
  int nw;
  int loop_ub;
  double buf_data[100];
  int k;
  int b_k;
  double y;
  double d;
  if (A->size[0] == 0) {
    B->size[0] = 0;
    B->size[1] = 1;
  } else if (A->size[0] < 2) {
    nToCopy = B->size[0] * B->size[1];
    B->size[0] = 1;
    B->size[1] = 1;
    emxEnsureCapacity_real_T(B, nToCopy);
    B->data[0] = A->data[0];
  } else {
    emxInit_real_T(&Bd, 1);
    u1 = A->size[0];
    if (50 < u1) {
      u1 = 50;
    }

    b_u1 = A->size[0];
    if (49 < b_u1) {
      b_u1 = 49;
    }

    nx = A->size[0];
    nw = u1 + b_u1;
    nToCopy = Bd->size[0];
    Bd->size[0] = A->size[0];
    emxEnsureCapacity_real_T(Bd, nToCopy);
    loop_ub = A->size[0];
    for (nToCopy = 0; nToCopy < loop_ub; nToCopy++) {
      Bd->data[nToCopy] = 0.0;
    }

    if (0 <= nw) {
      memset(&buf_data[0], 0, (nw + 1) * sizeof(double));
    }

    for (k = 0; k < nx; k++) {
      if (k + 1 <= u1) {
        loop_ub = 0;
      } else {
        loop_ub = k - u1;
      }

      nw = (k + b_u1) + 1;
      if (nw > A->size[0]) {
        nw = A->size[0];
      }

      nToCopy = nw - loop_ub;
      for (b_k = 0; b_k < nToCopy; b_k++) {
        buf_data[b_k] = A->data[loop_ub + b_k];
      }

      if (nToCopy == 0) {
        y = 0.0;
        nw = 0;
      } else {
        if (rtIsNaN(buf_data[0])) {
          y = 0.0;
          nw = 0;
        } else {
          y = buf_data[0];
          nw = 1;
        }

        for (b_k = 2; b_k <= nToCopy; b_k++) {
          d = buf_data[b_k - 1];
          if (!rtIsNaN(d)) {
            y += d;
            nw++;
          }
        }
      }

      Bd->data[k] = y / (double)nw;
    }

    nToCopy = B->size[0] * B->size[1];
    B->size[0] = A->size[0];
    B->size[1] = 1;
    emxEnsureCapacity_real_T(B, nToCopy);
    loop_ub = A->size[0];
    for (nToCopy = 0; nToCopy < loop_ub; nToCopy++) {
      B->data[nToCopy] = Bd->data[nToCopy];
    }

    emxFree_real_T(&Bd);
  }
}

/* End of code generation (smoothdata.c) */
