/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * isSymmetricPositiveSemiDefinite.c
 *
 * Code generation for function 'isSymmetricPositiveSemiDefinite'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "isSymmetricPositiveSemiDefinite.h"
#include "xdhseqr.h"
#include "xgehrd.h"
#include "xzgeev.h"
#include "xhseqr.h"

/* Function Definitions */
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

void isSymmetricPositiveSemiDefinite(const double value[4])
{
  int info;
  boolean_T p;
  int i;
  double y[4];
  boolean_T exitg2;
  creal_T alpha1[2];
  creal_T beta1[2];
  int exitg1;
  for (info = 0; info < 2; info++) {
    for (i = 0; i < 2; i++) {
      y[i + (info << 1)] = (value[i + (info << 1)] + value[info + (i << 1)]) /
        2.0;
    }
  }

  p = false;
  for (info = 0; info < 4; info++) {
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
    while ((!exitg2) && (info < 2)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= info) {
          if (!(y[i + (info << 1)] == y[info + (i << 1)])) {
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
      for (info = 0; info < 4; info++) {
        if (p || rtIsInf(y[info]) || rtIsNaN(y[info])) {
          p = true;
        } else {
          p = false;
        }
      }

      if (!p) {
        xgehrd(y);
        xhseqr(y);
      }
    } else {
      xzgeev(y, &info, alpha1, beta1);
    }
  }
}

/* End of code generation (isSymmetricPositiveSemiDefinite.c) */
