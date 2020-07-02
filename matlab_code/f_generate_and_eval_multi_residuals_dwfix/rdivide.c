/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: rdivide.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "rdivide.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"

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
  int i29;
  int loop_ub;
  i29 = z->size[0];
  z->size[0] = x->size[0];
  emxEnsureCapacity((emxArray__common *)z, i29, sizeof(double));
  loop_ub = x->size[0];
  for (i29 = 0; i29 < loop_ub; i29++) {
    z->data[i29] = x->data[i29] / y->data[i29];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
