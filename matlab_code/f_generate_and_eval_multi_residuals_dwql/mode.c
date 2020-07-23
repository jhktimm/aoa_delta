/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mode.c
 *
 * Code generation for function 'mode'
 *
 */

/* Include files */
#include "mode.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"
#include "sort.h"

/* Function Definitions */
double arraymode(const emxArray_real_T *x)
{
  double M;
  emxArray_real_T *v;
  int i;
  int loop_ub;
  double mtmp;
  int ftmp;
  int k;
  double d;
  if (x->size[0] == 0) {
    M = rtNaN;
  } else {
    emxInit_real_T(&v, 1);
    i = v->size[0];
    v->size[0] = x->size[0];
    emxEnsureCapacity_real_T(v, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      v->data[i] = x->data[i];
    }

    sort(v);
    M = v->data[0];
    loop_ub = 1;
    mtmp = v->data[0];
    ftmp = 1;
    i = v->size[0];
    for (k = 0; k <= i - 2; k++) {
      d = v->data[k + 1];
      if (d == mtmp) {
        ftmp++;
      } else {
        if (ftmp > loop_ub) {
          M = mtmp;
          loop_ub = ftmp;
        }

        mtmp = d;
        ftmp = 1;
      }
    }

    emxFree_real_T(&v);
    if (ftmp > loop_ub) {
      M = mtmp;
    }
  }

  return M;
}

/* End of code generation (mode.c) */
