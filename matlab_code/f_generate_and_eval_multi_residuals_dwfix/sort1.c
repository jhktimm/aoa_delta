/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sort1.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "sort1.h"
#include "sortIdx.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void sort(emxArray_real_T *x)
{
  int dim;
  int i33;
  emxArray_real_T *vwork;
  int j;
  int vstride;
  int k;
  emxArray_int32_T *b_vwork;
  dim = 2;
  if (x->size[0] != 1) {
    dim = 1;
  }

  if (dim <= 1) {
    i33 = x->size[0];
  } else {
    i33 = 1;
  }

  emxInit_real_T1(&vwork, 1);
  j = vwork->size[0];
  vwork->size[0] = i33;
  emxEnsureCapacity((emxArray__common *)vwork, j, sizeof(double));
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x->size[0];
    k = 2;
  }

  j = 0;
  emxInit_int32_T(&b_vwork, 1);
  while (j + 1 <= vstride) {
    for (k = 0; k + 1 <= i33; k++) {
      vwork->data[k] = x->data[j + k * vstride];
    }

    sortIdx(vwork, b_vwork);
    for (k = 0; k + 1 <= i33; k++) {
      x->data[j + k * vstride] = vwork->data[k];
    }

    j++;
  }

  emxFree_int32_T(&b_vwork);
  emxFree_real_T(&vwork);
}

/*
 * File trailer for sort1.c
 *
 * [EOF]
 */
