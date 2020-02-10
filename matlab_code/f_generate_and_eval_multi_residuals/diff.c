/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * diff.c
 *
 * Code generation for function 'diff'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "diff.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"

/* Function Definitions */
void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int orderForDim;
  int iyLead;
  double work_data_idx_0;
  int m;
  double tmp1;
  double tmp2;
  if (x->size[0] == 0) {
    iyLead = y->size[0];
    y->size[0] = 0;
    emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
  } else {
    orderForDim = x->size[0] - 1;
    if (!(orderForDim < 1)) {
      orderForDim = 1;
    }

    if (orderForDim < 1) {
      iyLead = y->size[0];
      y->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
    } else {
      orderForDim = x->size[0] - 1;
      iyLead = y->size[0];
      y->size[0] = orderForDim;
      emxEnsureCapacity((emxArray__common *)y, iyLead, sizeof(double));
      if (!(y->size[0] == 0)) {
        orderForDim = 1;
        iyLead = 0;
        work_data_idx_0 = x->data[0];
        for (m = 2; m <= x->size[0]; m++) {
          tmp1 = x->data[orderForDim];
          tmp2 = work_data_idx_0;
          work_data_idx_0 = tmp1;
          tmp1 -= tmp2;
          orderForDim++;
          y->data[iyLead] = tmp1;
          iyLead++;
        }
      }
    }
  }
}

/* End of code generation (diff.c) */
