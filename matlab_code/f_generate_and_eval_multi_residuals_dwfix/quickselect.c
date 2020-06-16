/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: quickselect.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "quickselect.h"
#include "sort3.h"

/* Function Declarations */
static int thirdOfFive(const emxArray_real_T *v, int ia, int ib);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *v
 *                int ia
 *                int ib
 * Return Type  : int
 */
static int thirdOfFive(const emxArray_real_T *v, int ia, int ib)
{
  int im;
  int b_j1;
  int j3;
  int j4;
  int j5;
  double v4;
  double v5;
  boolean_T p;
  if ((ia == ib) || (ia + 1 == ib)) {
    im = ia;
  } else if ((ia + 2 == ib) || (ia + 3 == ib)) {
    sort3(ia, v->data[ia - 1], ia + 1, v->data[ia], ia + 2, v->data[ia + 1],
          &b_j1, &im, &j3);
  } else {
    sort3(ia, v->data[ia - 1], ia + 1, v->data[ia], ia + 2, v->data[ia + 1],
          &b_j1, &im, &j3);
    j4 = ia;
    j5 = ia + 1;
    v4 = v->data[ia + 2];
    v5 = v->data[ia + 3];
    p = (v->data[ia + 3] < v->data[ia + 2]);
    if (p) {
      j4 = ia + 1;
      j5 = ia;
      v5 = v->data[ia + 2];
      v4 = v->data[ia + 3];
    }

    p = (v5 < v->data[b_j1 - 1]);
    if (p) {
      im = b_j1;
    } else {
      p = (v5 < v->data[im - 1]);
      if (p) {
        im = j5 + 3;
      } else {
        p = (v4 < v->data[im - 1]);
        if (!p) {
          p = (v4 < v->data[j3 - 1]);
          if (p) {
            im = j4 + 3;
          } else {
            im = j3;
          }
        }
      }
    }
  }

  return im;
}

/*
 * Arguments    : emxArray_real_T *v
 *                int n
 *                int vlen
 *                double *vn
 *                int *nfirst
 *                int *nlast
 * Return Type  : void
 */
void quickselect(emxArray_real_T *v, int n, int vlen, double *vn, int *nfirst,
                 int *nlast)
{
  int ipiv;
  int ia;
  int ib;
  int oldnv;
  boolean_T checkspeed;
  boolean_T isslow;
  boolean_T exitg1;
  double vref;
  int ngroupsof5;
  int k;
  double vk;
  boolean_T p;
  boolean_T guard1 = false;
  int a;
  int destidx;
  if (n > vlen) {
    *vn = rtNaN;
    *nfirst = 0;
    *nlast = 0;
  } else {
    ipiv = n;
    ia = 1;
    ib = vlen - 1;
    *nfirst = 1;
    *nlast = vlen;
    oldnv = vlen;
    checkspeed = false;
    isslow = false;
    exitg1 = false;
    while ((!exitg1) && (ia < ib + 1)) {
      vref = v->data[ipiv - 1];
      v->data[ipiv - 1] = v->data[ib];
      v->data[ib] = vref;
      ngroupsof5 = ia - 1;
      ipiv = -1;
      for (k = ia - 1; k + 1 <= ib; k++) {
        vk = v->data[k];
        if (v->data[k] == vref) {
          v->data[k] = v->data[ngroupsof5];
          v->data[ngroupsof5] = vk;
          ipiv++;
          ngroupsof5++;
        } else {
          p = (v->data[k] < vref);
          if (p) {
            v->data[k] = v->data[ngroupsof5];
            v->data[ngroupsof5] = vk;
            ngroupsof5++;
          }
        }
      }

      v->data[ib] = v->data[ngroupsof5];
      v->data[ngroupsof5] = vref;
      *nlast = ngroupsof5 + 1;
      guard1 = false;
      if (n <= ngroupsof5 + 1) {
        *nfirst = ngroupsof5 - ipiv;
        if (n >= *nfirst) {
          exitg1 = true;
        } else {
          ib = ngroupsof5 - 1;
          guard1 = true;
        }
      } else {
        ia = ngroupsof5 + 2;
        guard1 = true;
      }

      if (guard1) {
        a = (ib - ia) + 2;
        if (checkspeed) {
          isslow = (a > oldnv / 2);
          oldnv = a;
        }

        checkspeed = !checkspeed;
        if (isslow) {
          while (a > 1) {
            ngroupsof5 = a / 5;
            *nlast = a - ngroupsof5 * 5;
            a = ngroupsof5;
            for (k = 0; k + 1 <= ngroupsof5; k++) {
              ipiv = ia + k * 5;
              ipiv = thirdOfFive(v, ipiv, ipiv + 4) - 1;
              destidx = (ia + k) - 1;
              vref = v->data[destidx];
              v->data[destidx] = v->data[ipiv];
              v->data[ipiv] = vref;
            }

            if (*nlast > 0) {
              ipiv = ia + ngroupsof5 * 5;
              ipiv = thirdOfFive(v, ipiv, (ipiv + *nlast) - 1) - 1;
              destidx = (ia + ngroupsof5) - 1;
              vref = v->data[destidx];
              v->data[destidx] = v->data[ipiv];
              v->data[ipiv] = vref;
              a = ngroupsof5 + 1;
            }
          }
        } else {
          if (a >= 3) {
            ipiv = ia + (a - 1) / 2;
            sort3(ia, v->data[ia - 1], ipiv, v->data[ipiv - 1], ib + 1, v->
                  data[ib], &ngroupsof5, &destidx, &a);
            if (destidx > ia) {
              vref = v->data[ia - 1];
              v->data[ia - 1] = v->data[destidx - 1];
              v->data[destidx - 1] = vref;
            }
          }
        }

        ipiv = ia;
        *nfirst = ia;
        *nlast = ib + 1;
      }
    }

    *vn = v->data[*nlast - 1];
  }
}

/*
 * File trailer for quickselect.c
 *
 * [EOF]
 */
