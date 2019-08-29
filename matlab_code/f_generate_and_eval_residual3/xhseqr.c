/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xhseqr.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 23-Aug-2019 08:22:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "xhseqr.h"
#include "xdlanv2.h"

/* Function Definitions */

/*
 * Arguments    : double h[4]
 * Return Type  : int
 */
int xhseqr(double h[4])
{
  int info;
  int i;
  int k;
  boolean_T exitg1;
  double htmp1;
  double htmp2;
  double ab;
  double aa;
  double ba;
  double s;
  double unusedU3;
  double cs;
  double sn;
  double d0;
  info = -1;
  for (i = 1; i + 1 >= 1; i = k - 2) {
    k = i + 1;
    exitg1 = false;
    while ((!exitg1) && ((k > 1) && (!(fabs(h[1]) <= 2.0041683600089728E-292))))
    {
      if (fabs(h[1]) <= 2.2204460492503131E-16 * (fabs(h[0]) + fabs(h[3]))) {
        htmp1 = fabs(h[1]);
        htmp2 = fabs(h[2]);
        if (htmp1 > htmp2) {
          ab = htmp1;
          ba = htmp2;
        } else {
          ab = htmp2;
          ba = htmp1;
        }

        htmp1 = fabs(h[3]);
        htmp2 = fabs(h[0] - h[3]);
        if (htmp1 > htmp2) {
          aa = htmp1;
          htmp1 = htmp2;
        } else {
          aa = htmp2;
        }

        s = aa + ab;
        htmp2 = 2.2204460492503131E-16 * (htmp1 * (aa / s));
        if ((2.0041683600089728E-292 > htmp2) || rtIsNaN(htmp2)) {
          d0 = 2.0041683600089728E-292;
        } else {
          d0 = htmp2;
        }

        if (ba * (ab / s) <= d0) {
          exitg1 = true;
        } else {
          k = 1;
        }
      } else {
        k = 1;
      }
    }

    if (k > 1) {
      h[1] = 0.0;
    }

    if ((k != i + 1) && (k == i)) {
      htmp2 = h[(i + (i << 1)) - 1];
      htmp1 = h[i + ((i - 1) << 1)];
      aa = h[i + (i << 1)];
      xdlanv2(&h[(i + ((i - 1) << 1)) - 1], &htmp2, &htmp1, &aa, &s, &ab, &ba,
              &unusedU3, &cs, &sn);
      h[(i + (i << 1)) - 1] = htmp2;
      h[i + ((i - 1) << 1)] = htmp1;
      h[i + (i << 1)] = aa;
      if (2 > i + 1) {
        htmp2 = cs * h[1] + sn * h[2];
        h[2] = cs * h[2] - sn * h[1];
        h[1] = htmp2;
      }
    }
  }

  info++;
  return info;
}

/*
 * File trailer for xhseqr.c
 *
 * [EOF]
 */
