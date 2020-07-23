/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sort.c
 *
 * Code generation for function 'sort'
 *
 */

/* Include files */
#include "sort.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"

/* Function Definitions */
void sort(emxArray_real_T *x)
{
  int dim;
  emxArray_real_T *vwork;
  int vstride;
  int vlen;
  int j;
  int k;
  emxArray_int32_T *b_vwork;
  dim = 0;
  if (x->size[0] != 1) {
    dim = -1;
  }

  emxInit_real_T(&vwork, 1);
  if (dim + 2 <= 1) {
    vstride = x->size[0];
  } else {
    vstride = 1;
  }

  vlen = vstride - 1;
  j = vwork->size[0];
  vwork->size[0] = vstride;
  emxEnsureCapacity_real_T(vwork, j);
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x->size[0];
  }

  emxInit_int32_T(&b_vwork, 1);
  for (j = 0; j < vstride; j++) {
    for (k = 0; k <= vlen; k++) {
      vwork->data[k] = x->data[j + k * vstride];
    }

    sortIdx(vwork, b_vwork);
    for (k = 0; k <= vlen; k++) {
      x->data[j + k * vstride] = vwork->data[k];
    }
  }

  emxFree_int32_T(&b_vwork);
  emxFree_real_T(&vwork);
}

/* End of code generation (sort.c) */
