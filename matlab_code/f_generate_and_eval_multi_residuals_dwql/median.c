/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * median.c
 *
 * Code generation for function 'median'
 *
 */

/* Include files */
#include "median.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "quickselect.h"
#include "rt_nonfinite.h"

/* Function Definitions */
double median(const emxArray_real_T *x)
{
  double y;
  int vlen;
  int k;
  emxArray_real_T *unusedU3;
  int exitg1;
  int midm1;
  int unusedU5;
  double b;
  vlen = x->size[0];
  if (x->size[0] == 0) {
    y = rtNaN;
  } else {
    k = 0;
    emxInit_real_T(&unusedU3, 1);
    do {
      exitg1 = 0;
      if (k <= vlen - 1) {
        if (rtIsNaN(x->data[k])) {
          y = rtNaN;
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (vlen <= 4) {
          if (vlen == 0) {
            y = rtNaN;
          } else if (vlen == 1) {
            y = x->data[0];
          } else if (vlen == 2) {
            if (((x->data[0] < 0.0) != (x->data[1] < 0.0)) || rtIsInf(x->data[0]))
            {
              y = (x->data[0] + x->data[1]) / 2.0;
            } else {
              y = x->data[0] + (x->data[1] - x->data[0]) / 2.0;
            }
          } else if (vlen == 3) {
            if (x->data[0] < x->data[1]) {
              if (x->data[1] < x->data[2]) {
                unusedU5 = 1;
              } else if (x->data[0] < x->data[2]) {
                unusedU5 = 2;
              } else {
                unusedU5 = 0;
              }
            } else if (x->data[0] < x->data[2]) {
              unusedU5 = 0;
            } else if (x->data[1] < x->data[2]) {
              unusedU5 = 2;
            } else {
              unusedU5 = 1;
            }

            y = x->data[unusedU5];
          } else {
            if (x->data[0] < x->data[1]) {
              if (x->data[1] < x->data[2]) {
                k = 0;
                unusedU5 = 1;
                vlen = 2;
              } else if (x->data[0] < x->data[2]) {
                k = 0;
                unusedU5 = 2;
                vlen = 1;
              } else {
                k = 2;
                unusedU5 = 0;
                vlen = 1;
              }
            } else if (x->data[0] < x->data[2]) {
              k = 1;
              unusedU5 = 0;
              vlen = 2;
            } else if (x->data[1] < x->data[2]) {
              k = 1;
              unusedU5 = 2;
              vlen = 0;
            } else {
              k = 2;
              unusedU5 = 1;
              vlen = 0;
            }

            if (x->data[k] < x->data[3]) {
              if (x->data[3] < x->data[vlen]) {
                if (((x->data[unusedU5] < 0.0) != (x->data[3] < 0.0)) || rtIsInf
                    (x->data[unusedU5])) {
                  y = (x->data[unusedU5] + x->data[3]) / 2.0;
                } else {
                  y = x->data[unusedU5] + (x->data[3] - x->data[unusedU5]) / 2.0;
                }
              } else if (((x->data[unusedU5] < 0.0) != (x->data[vlen] < 0.0)) ||
                         rtIsInf(x->data[unusedU5])) {
                y = (x->data[unusedU5] + x->data[vlen]) / 2.0;
              } else {
                y = x->data[unusedU5] + (x->data[vlen] - x->data[unusedU5]) /
                  2.0;
              }
            } else if (((x->data[k] < 0.0) != (x->data[unusedU5] < 0.0)) ||
                       rtIsInf(x->data[k])) {
              y = (x->data[k] + x->data[unusedU5]) / 2.0;
            } else {
              y = x->data[k] + (x->data[unusedU5] - x->data[k]) / 2.0;
            }
          }
        } else {
          midm1 = vlen >> 1;
          if ((vlen & 1) == 0) {
            unusedU5 = unusedU3->size[0];
            unusedU3->size[0] = x->size[0];
            emxEnsureCapacity_real_T(unusedU3, unusedU5);
            k = x->size[0];
            for (unusedU5 = 0; unusedU5 < k; unusedU5++) {
              unusedU3->data[unusedU5] = x->data[unusedU5];
            }

            quickselect(unusedU3, midm1 + 1, vlen, &y, &k, &unusedU5);
            if (midm1 < k) {
              quickselect(unusedU3, midm1, unusedU5 - 1, &b, &k, &vlen);
              if (((y < 0.0) != (b < 0.0)) || rtIsInf(y)) {
                y = (y + b) / 2.0;
              } else {
                y += (b - y) / 2.0;
              }
            }
          } else {
            unusedU5 = unusedU3->size[0];
            unusedU3->size[0] = x->size[0];
            emxEnsureCapacity_real_T(unusedU3, unusedU5);
            k = x->size[0];
            for (unusedU5 = 0; unusedU5 < k; unusedU5++) {
              unusedU3->data[unusedU5] = x->data[unusedU5];
            }

            quickselect(unusedU3, midm1 + 1, vlen, &y, &k, &unusedU5);
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);

    emxFree_real_T(&unusedU3);
  }

  return y;
}

/* End of code generation (median.c) */
