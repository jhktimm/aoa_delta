/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * conv.c
 *
 * Code generation for function 'conv'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "conv.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"

/* Function Definitions */
void conv(const emxArray_real_T *A, const double B[5], emxArray_real_T *C)
{
  int nC;
  int k;
  if (A->size[0] >= 5) {
    nC = A->size[0] - 5;
  } else {
    nC = -1;
  }

  k = C->size[0];
  C->size[0] = nC + 1;
  emxEnsureCapacity((emxArray__common *)C, k, sizeof(double));
  for (k = 0; k <= nC; k++) {
    C->data[k] = 0.0;
  }

  if (A->size[0] > 0) {
    for (nC = 0; nC < 5; nC++) {
      for (k = 0; k <= A->size[0] - 5; k++) {
        C->data[k] += B[nC] * A->data[(k - nC) + 4];
      }
    }
  }
}

/* End of code generation (conv.c) */
