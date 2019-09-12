/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rdivide.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 09-Sep-2019 14:44:25
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
  int i10;
  int loop_ub;
  i10 = z->size[0];
  z->size[0] = x->size[0];
  emxEnsureCapacity_real_T1(z, i10);
  loop_ub = x->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    z->data[i10] = x->data[i10] / y->data[i10];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
