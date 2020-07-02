/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cov.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "cov.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double xy_data[]
 *                int xy_size[2]
 * Return Type  : void
 */
void cov(const emxArray_real_T *x, double xy_data[], int xy_size[2])
{
  boolean_T p;
  emxArray_real_T *b_x;
  int br;
  double alpha;
  double c_x[2];
  int loop_ub;
  double temp;
  int m;
  double a;
  double c[4];
  int LDA;
  int ic;
  int ar;
  int w;
  double b;
  p = (x->size[0] == 1);
  if (p) {
    for (br = 0; br < 2; br++) {
      c_x[br] = x->data[x->size[0] * br];
    }

    alpha = 0.0;
    for (br = 0; br < 2; br++) {
      alpha += x->data[x->size[0] * br];
    }

    alpha /= 2.0;
    temp = 0.0;
    for (br = 0; br < 2; br++) {
      a = c_x[br] - alpha;
      temp += a * a;
    }

    xy_size[0] = 1;
    xy_size[1] = 1;
    xy_data[0] = temp;
  } else {
    emxInit_real_T(&b_x, 2);
    br = b_x->size[0] * b_x->size[1];
    b_x->size[0] = x->size[0];
    b_x->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)b_x, br, sizeof(double));
    loop_ub = x->size[0] * x->size[1];
    for (br = 0; br < loop_ub; br++) {
      b_x->data[br] = x->data[br];
    }

    m = x->size[0];
    for (br = 0; br < 4; br++) {
      c[br] = 0.0;
    }

    if (x->size[0] == 0) {
      for (br = 0; br < 4; br++) {
        c[br] = rtNaN;
      }
    } else {
      LDA = x->size[0];
      if (x->size[0] >= 2) {
        for (loop_ub = 0; loop_ub < 2; loop_ub++) {
          alpha = 0.0;
          for (br = 1; br <= m; br++) {
            alpha += b_x->data[(br + b_x->size[0] * loop_ub) - 1];
          }

          alpha /= (double)m;
          for (br = 0; br + 1 <= m; br++) {
            b_x->data[br + b_x->size[0] * loop_ub] -= alpha;
          }
        }

        alpha = 1.0 / ((double)x->size[0] - 1.0);
        for (br = 0; br < 4; br++) {
          c[br] = 0.0;
        }

        for (loop_ub = 0; loop_ub <= 3; loop_ub += 2) {
          for (ic = loop_ub; ic + 1 <= loop_ub + 2; ic++) {
            c[ic] = 0.0;
          }
        }

        br = -1;
        for (loop_ub = 0; loop_ub <= 3; loop_ub += 2) {
          ar = -1;
          for (ic = loop_ub; ic + 1 <= loop_ub + 2; ic++) {
            temp = 0.0;
            for (w = 1; w <= m; w++) {
              a = b_x->data[w + ar];
              b = b_x->data[w + br];
              temp += a * b;
            }

            c[ic] += alpha * temp;
            ar += LDA;
          }

          br += LDA;
        }
      }
    }

    emxFree_real_T(&b_x);
    xy_size[0] = 2;
    xy_size[1] = 2;
    for (br = 0; br < 4; br++) {
      xy_data[br] = c[br];
    }
  }
}

/*
 * File trailer for cov.c
 *
 * [EOF]
 */
