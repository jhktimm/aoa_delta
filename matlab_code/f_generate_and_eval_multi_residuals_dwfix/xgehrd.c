/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgehrd.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "xgehrd.h"
#include "abs.h"
#include "xnrm2.h"
#include "f_generate_and_eval_multi_residuals_dwfix_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : double a[36]
 * Return Type  : void
 */
void b_xgehrd(double a[36])
{
  int i;
  double work[6];
  int im1n;
  int in;
  int ia0;
  double alpha1;
  double d10;
  double xnorm;
  double tau[5];
  int jy;
  int knt;
  int lastv;
  int i30;
  int lastc;
  int k;
  boolean_T exitg2;
  int ix;
  int ia;
  int exitg1;
  int i31;
  for (i = 0; i < 6; i++) {
    work[i] = 0.0;
  }

  for (i = 0; i < 5; i++) {
    im1n = i * 6 + 2;
    in = (i + 1) * 6;
    ia0 = i + 3;
    if (!(ia0 < 6)) {
      ia0 = 6;
    }

    ia0 += i * 6;
    alpha1 = a[(i + 6 * i) + 1];
    d10 = 0.0;
    xnorm = b_xnrm2(4 - i, a, ia0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(a[(i + 6 * i) + 1], xnorm);
      if (a[(i + 6 * i) + 1] >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        i30 = (ia0 - i) + 3;
        do {
          knt++;
          for (k = ia0; k <= i30; k++) {
            a[k - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          alpha1 *= 9.9792015476736E+291;
        } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

        xnorm = rt_hypotd_snf(alpha1, b_xnrm2(4 - i, a, ia0));
        if (alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        d10 = (xnorm - alpha1) / xnorm;
        alpha1 = 1.0 / (alpha1 - xnorm);
        i30 = (ia0 - i) + 3;
        while (ia0 <= i30) {
          a[ia0 - 1] *= alpha1;
          ia0++;
        }

        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        alpha1 = xnorm;
      } else {
        d10 = (xnorm - a[(i + 6 * i) + 1]) / xnorm;
        alpha1 = 1.0 / (a[(i + 6 * i) + 1] - xnorm);
        i30 = (ia0 - i) + 3;
        while (ia0 <= i30) {
          a[ia0 - 1] *= alpha1;
          ia0++;
        }

        alpha1 = xnorm;
      }
    }

    tau[i] = d10;
    a[(i + 6 * i) + 1] = 1.0;
    jy = (i + im1n) - 1;
    if (tau[i] != 0.0) {
      lastv = 5 - i;
      ia0 = (jy - i) + 4;
      while ((lastv > 0) && (a[ia0] == 0.0)) {
        lastv--;
        ia0--;
      }

      lastc = 6;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        ia0 = in + lastc;
        ia = ia0;
        do {
          exitg1 = 0;
          if (ia <= ia0 + (lastv - 1) * 6) {
            if (a[ia - 1] != 0.0) {
              exitg1 = 1;
            } else {
              ia += 6;
            }
          } else {
            lastc--;
            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    } else {
      lastv = 0;
      lastc = 0;
    }

    if (lastv > 0) {
      if (lastc != 0) {
        for (ia0 = 1; ia0 <= lastc; ia0++) {
          work[ia0 - 1] = 0.0;
        }

        ix = jy;
        i30 = (in + 6 * (lastv - 1)) + 1;
        for (k = in + 1; k <= i30; k += 6) {
          ia0 = 0;
          i31 = (k + lastc) - 1;
          for (ia = k; ia <= i31; ia++) {
            work[ia0] += a[ia - 1] * a[ix];
            ia0++;
          }

          ix++;
        }
      }

      if (!(-tau[i] == 0.0)) {
        ia0 = in;
        for (knt = 1; knt <= lastv; knt++) {
          if (a[jy] != 0.0) {
            xnorm = a[jy] * -tau[i];
            ix = 0;
            i30 = lastc + ia0;
            for (k = ia0; k + 1 <= i30; k++) {
              a[k] += work[ix] * xnorm;
              ix++;
            }
          }

          jy++;
          ia0 += 6;
        }
      }
    }

    im1n += i;
    knt = (i + in) + 2;
    if (tau[i] != 0.0) {
      lastv = 5 - i;
      ia0 = (im1n - i) + 3;
      while ((lastv > 0) && (a[ia0] == 0.0)) {
        lastv--;
        ia0--;
      }

      lastc = 5 - i;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        ia0 = knt + (lastc - 1) * 6;
        ia = ia0;
        do {
          exitg1 = 0;
          if (ia <= (ia0 + lastv) - 1) {
            if (a[ia - 1] != 0.0) {
              exitg1 = 1;
            } else {
              ia++;
            }
          } else {
            lastc--;
            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    } else {
      lastv = 0;
      lastc = 0;
    }

    if (lastv > 0) {
      if (lastc != 0) {
        for (ia0 = 1; ia0 <= lastc; ia0++) {
          work[ia0 - 1] = 0.0;
        }

        ia0 = 0;
        i30 = knt + 6 * (lastc - 1);
        for (k = knt; k <= i30; k += 6) {
          ix = im1n;
          xnorm = 0.0;
          i31 = (k + lastv) - 1;
          for (ia = k; ia <= i31; ia++) {
            xnorm += a[ia - 1] * a[ix - 1];
            ix++;
          }

          work[ia0] += xnorm;
          ia0++;
        }
      }

      if (!(-tau[i] == 0.0)) {
        ia0 = knt - 1;
        jy = 0;
        for (knt = 1; knt <= lastc; knt++) {
          if (work[jy] != 0.0) {
            xnorm = work[jy] * -tau[i];
            ix = im1n;
            i30 = lastv + ia0;
            for (k = ia0; k + 1 <= i30; k++) {
              a[k] += a[ix - 1] * xnorm;
              ix++;
            }
          }

          jy++;
          ia0 += 6;
        }
      }
    }

    a[(i + 6 * i) + 1] = alpha1;
  }
}

/*
 * Arguments    : double a[4]
 * Return Type  : void
 */
void xgehrd(double a[4])
{
  double alpha1;
  alpha1 = a[1];
  a[1] = 1.0;
  a[1] = alpha1;
}

/*
 * File trailer for xgehrd.c
 *
 * [EOF]
 */
