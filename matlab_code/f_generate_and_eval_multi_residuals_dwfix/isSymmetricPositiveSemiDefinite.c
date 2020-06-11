/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: isSymmetricPositiveSemiDefinite.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "isSymmetricPositiveSemiDefinite.h"
#include "eig.h"
#include "xdhseqr.h"
#include "xgehrd.h"
#include "xzgeev.h"

/* Function Definitions */

/*
 * Arguments    : const double value[36]
 * Return Type  : void
 */
void b_isSymmetricPositiveSemiDefini(const double value[36])
{
  int info;
  boolean_T p;
  int i;
  double y[36];
  boolean_T exitg2;
  creal_T alpha1[6];
  creal_T beta1[6];
  int exitg1;
  for (info = 0; info < 6; info++) {
    for (i = 0; i < 6; i++) {
      y[i + 6 * info] = (value[i + 6 * info] + value[info + 6 * i]) / 2.0;
    }
  }

  p = false;
  for (info = 0; info < 36; info++) {
    if (p || rtIsInf(y[info]) || rtIsNaN(y[info])) {
      p = true;
    } else {
      p = false;
    }
  }

  if (!p) {
    p = true;
    info = 0;
    exitg2 = false;
    while ((!exitg2) && (info < 6)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= info) {
          if (!(y[i + 6 * info] == y[info + 6 * i])) {
            p = false;
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          info++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    if (p) {
      p = false;
      for (info = 0; info < 36; info++) {
        if (p || rtIsInf(y[info]) || rtIsNaN(y[info])) {
          p = true;
        } else {
          p = false;
        }
      }

      if (!p) {
        b_xgehrd(y);
        eml_dlahqr(y);
      }
    } else {
      b_xzgeev(y, &info, alpha1, beta1);
    }
  }
}

/*
 * Arguments    : const double value[4]
 * Return Type  : void
 */
void isSymmetricPositiveSemiDefinite(const double value[4])
{
  int i3;
  double b_value[4];
  creal_T unusedExpr[2];
  int i4;
  for (i3 = 0; i3 < 2; i3++) {
    for (i4 = 0; i4 < 2; i4++) {
      b_value[i4 + (i3 << 1)] = (value[i4 + (i3 << 1)] + value[i3 + (i4 << 1)]) /
        2.0;
    }
  }

  eig(b_value, unusedExpr);
}

/*
 * File trailer for isSymmetricPositiveSemiDefinite.c
 *
 * [EOF]
 */
