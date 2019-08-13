/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rdivide.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 12-Aug-2019 17:51:43
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "rdivide.h"
#include "f_generate_and_eval_residual_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                emxArray_real_T *z
 * Return Type  : void
 */
void rdivide(const emxArray_real_T *x, const emxArray_real_T *y, emxArray_real_T
             *z)
{
  int i9;
  int loop_ub;
  i9 = z->size[0];
  z->size[0] = x->size[0];
  emxEnsureCapacity_real_T1(z, i9);
  loop_ub = x->size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    z->data[i9] = x->data[i9] / y->data[i9];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
