/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: inv.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "inv.h"

/* Function Definitions */

/*
 * Arguments    : const double x[16]
 *                double y[16]
 * Return Type  : void
 */
void invNxN(const double x[16], double y[16])
{
  int i7;
  double b_x[16];
  int j;
  signed char ipiv[4];
  int c;
  int jBcol;
  int k;
  signed char p[4];
  int ix;
  double smax;
  double s;
  int kAcol;
  int i;
  for (i7 = 0; i7 < 16; i7++) {
    y[i7] = 0.0;
    b_x[i7] = x[i7];
  }

  for (i7 = 0; i7 < 4; i7++) {
    ipiv[i7] = (signed char)(1 + i7);
  }

  for (j = 0; j < 3; j++) {
    c = j * 5;
    jBcol = 0;
    ix = c;
    smax = fabs(b_x[c]);
    for (k = 2; k <= 4 - j; k++) {
      ix++;
      s = fabs(b_x[ix]);
      if (s > smax) {
        jBcol = k - 1;
        smax = s;
      }
    }

    if (b_x[c + jBcol] != 0.0) {
      if (jBcol != 0) {
        ipiv[j] = (signed char)((j + jBcol) + 1);
        ix = j;
        jBcol += j;
        for (k = 0; k < 4; k++) {
          smax = b_x[ix];
          b_x[ix] = b_x[jBcol];
          b_x[jBcol] = smax;
          ix += 4;
          jBcol += 4;
        }
      }

      i7 = (c - j) + 4;
      for (i = c + 1; i + 1 <= i7; i++) {
        b_x[i] /= b_x[c];
      }
    }

    jBcol = c;
    kAcol = c + 4;
    for (i = 1; i <= 3 - j; i++) {
      smax = b_x[kAcol];
      if (b_x[kAcol] != 0.0) {
        ix = c + 1;
        i7 = (jBcol - j) + 8;
        for (k = 5 + jBcol; k + 1 <= i7; k++) {
          b_x[k] += b_x[ix] * -smax;
          ix++;
        }
      }

      kAcol += 4;
      jBcol += 4;
    }
  }

  for (i7 = 0; i7 < 4; i7++) {
    p[i7] = (signed char)(1 + i7);
  }

  for (k = 0; k < 3; k++) {
    if (ipiv[k] > 1 + k) {
      jBcol = p[ipiv[k] - 1];
      p[ipiv[k] - 1] = p[k];
      p[k] = (signed char)jBcol;
    }
  }

  for (k = 0; k < 4; k++) {
    c = p[k] - 1;
    y[k + ((p[k] - 1) << 2)] = 1.0;
    for (j = k; j + 1 < 5; j++) {
      if (y[j + (c << 2)] != 0.0) {
        for (i = j + 1; i + 1 < 5; i++) {
          y[i + (c << 2)] -= y[j + (c << 2)] * b_x[i + (j << 2)];
        }
      }
    }
  }

  for (j = 0; j < 4; j++) {
    jBcol = j << 2;
    for (k = 3; k >= 0; k += -1) {
      kAcol = k << 2;
      if (y[k + jBcol] != 0.0) {
        y[k + jBcol] /= b_x[k + kAcol];
        for (i = 0; i + 1 <= k; i++) {
          y[i + jBcol] -= y[k + jBcol] * b_x[i + kAcol];
        }
      }
    }
  }
}

/*
 * File trailer for inv.c
 *
 * [EOF]
 */
