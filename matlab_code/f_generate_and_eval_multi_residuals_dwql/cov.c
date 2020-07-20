/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * cov.c
 *
 * Code generation for function 'cov'
 *
 */

/* Include files */
#include "cov.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void cov(const emxArray_real_T *x, double xy_data[], int xy_size[2])
{
  emxArray_real_T *b_x;
  double x_idx_1;
  int br;
  double alpha1;
  double muj;
  int ar;
  double temp;
  int m;
  double C[4];
  int LDA;
  int ic;
  int w;
  if (x->size[0] == 1) {
    x_idx_1 = x->data[0];
    alpha1 = x_idx_1;
    muj = x_idx_1;
    x_idx_1 = x->data[x->size[0]];
    muj += x_idx_1;
    muj /= 2.0;
    alpha1 -= muj;
    temp = alpha1 * alpha1;
    alpha1 = x_idx_1 - muj;
    temp += alpha1 * alpha1;
    xy_size[0] = 1;
    xy_size[1] = 1;
    xy_data[0] = temp;
  } else {
    emxInit_real_T(&b_x, 2);
    br = b_x->size[0] * b_x->size[1];
    b_x->size[0] = x->size[0];
    b_x->size[1] = 2;
    emxEnsureCapacity_real_T(b_x, br);
    ar = x->size[0] * x->size[1];
    for (br = 0; br < ar; br++) {
      b_x->data[br] = x->data[br];
    }

    m = x->size[0] - 1;
    C[0] = 0.0;
    C[1] = 0.0;
    C[2] = 0.0;
    C[3] = 0.0;
    if (x->size[0] == 0) {
      C[0] = rtNaN;
      C[1] = rtNaN;
      C[2] = rtNaN;
      C[3] = rtNaN;
    } else {
      LDA = x->size[0];
      if (x->size[0] >= 2) {
        muj = 0.0;
        for (br = 0; br <= m; br++) {
          muj += b_x->data[br];
        }

        ar = m + 1;
        muj /= (double)ar;
        for (br = 0; br <= m; br++) {
          b_x->data[br] -= muj;
        }

        muj = 0.0;
        for (br = 0; br <= m; br++) {
          muj += b_x->data[br + b_x->size[0]];
        }

        muj /= (double)ar;
        for (br = 0; br <= m; br++) {
          b_x->data[br + b_x->size[0]] -= muj;
        }

        alpha1 = 1.0 / ((double)x->size[0] - 1.0);
        for (ic = 1; ic < 3; ic++) {
          C[ic - 1] = 0.0;
        }

        for (ic = 3; ic < 5; ic++) {
          C[ic - 1] = 0.0;
        }

        ar = -1;
        for (ic = 1; ic < 3; ic++) {
          temp = 0.0;
          for (w = 0; w <= m; w++) {
            temp += b_x->data[(w + ar) + 1] * b_x->data[w];
          }

          C[ic - 1] += alpha1 * temp;
          ar += LDA;
        }

        br = x->size[0] + -1;
        ar = -1;
        for (ic = 3; ic < 5; ic++) {
          temp = 0.0;
          for (w = 0; w <= m; w++) {
            temp += b_x->data[(w + ar) + 1] * b_x->data[(w + br) + 1];
          }

          C[ic - 1] += alpha1 * temp;
          ar += LDA;
        }
      }
    }

    emxFree_real_T(&b_x);
    xy_size[0] = 2;
    xy_size[1] = 2;
    xy_data[0] = C[0];
    xy_data[1] = C[1];
    xy_data[2] = C[2];
    xy_data[3] = C[3];
  }
}

/* End of code generation (cov.c) */
