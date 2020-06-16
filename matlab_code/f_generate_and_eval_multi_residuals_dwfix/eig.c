/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: eig.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "eig.h"
#include "abs.h"
#include "xdlanv2.h"
#include "xhseqr.h"
#include "xgehrd.h"
#include "xzgeev.h"
#include "f_generate_and_eval_multi_residuals_dwfix_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const double A[4]
 *                creal_T V[2]
 * Return Type  : void
 */
void eig(const double A[4], creal_T V[2])
{
  boolean_T p;
  int info;
  int i;
  boolean_T exitg2;
  creal_T beta1[2];
  int exitg1;
  double mu1_im;
  double t1_im;
  double b_A[4];
  creal_T T[4];
  double r;
  double s;
  double d;
  double sgnbi;
  double rt1i;
  double mu1_re;
  double cs;
  double sn;
  p = false;
  for (info = 0; info < 4; info++) {
    if (p || rtIsInf(A[info]) || rtIsNaN(A[info])) {
      p = true;
    } else {
      p = false;
    }
  }

  if (p) {
    for (i = 0; i < 2; i++) {
      V[i].re = rtNaN;
      V[i].im = 0.0;
    }
  } else {
    p = true;
    info = 0;
    exitg2 = false;
    while ((!exitg2) && (info < 2)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= info) {
          if (!(A[i + (info << 1)] == A[info + (i << 1)])) {
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
        if (p || rtIsInf(A[info]) || rtIsNaN(A[info])) {
          p = true;
        } else {
          p = false;
        }
      }

      if (p) {
        for (info = 0; info < 4; info++) {
          T[info].re = rtNaN;
          T[info].im = 0.0;
        }
      } else {
        for (info = 0; info < 4; info++) {
          b_A[info] = A[info];
        }

        xgehrd(b_A);
        xhseqr(b_A);
        for (info = 0; info < 4; info++) {
          T[info].re = b_A[info];
          T[info].im = 0.0;
        }

        if (b_A[1] != 0.0) {
          sgnbi = b_A[0];
          r = b_A[2];
          t1_im = b_A[1];
          d = b_A[3];
          xdlanv2(&sgnbi, &r, &t1_im, &d, &mu1_im, &rt1i, &s, &mu1_re, &cs, &sn);
          mu1_re = mu1_im - b_A[3];
          r = rt_hypotd_snf(rt_hypotd_snf(mu1_re, rt1i), b_A[1]);
          if (rt1i == 0.0) {
            mu1_re /= r;
            mu1_im = 0.0;
          } else if (mu1_re == 0.0) {
            mu1_re = 0.0;
            mu1_im = rt1i / r;
          } else {
            mu1_re /= r;
            mu1_im = rt1i / r;
          }

          s = b_A[1] / r;
          for (info = 0; info < 2; info++) {
            r = T[info << 1].re;
            t1_im = T[info << 1].im;
            sgnbi = T[info << 1].re;
            T[info << 1].re = (mu1_re * T[info << 1].re + mu1_im * T[info << 1].
                               im) + s * T[1 + (info << 1)].re;
            T[info << 1].im = (mu1_re * T[info << 1].im - mu1_im * sgnbi) + s *
              T[1 + (info << 1)].im;
            sgnbi = mu1_re * T[1 + (info << 1)].im + mu1_im * T[1 + (info << 1)]
              .re;
            T[1 + (info << 1)].re = (mu1_re * T[1 + (info << 1)].re - mu1_im *
              T[1 + (info << 1)].im) - s * r;
            T[1 + (info << 1)].im = sgnbi - s * t1_im;
          }

          for (i = 0; i < 2; i++) {
            r = T[i].re;
            t1_im = T[i].im;
            sgnbi = mu1_re * T[i].im + mu1_im * T[i].re;
            T[i].re = (mu1_re * T[i].re - mu1_im * T[i].im) + s * T[2 + i].re;
            T[i].im = sgnbi + s * T[2 + i].im;
            sgnbi = T[2 + i].re;
            T[2 + i].re = (mu1_re * T[2 + i].re + mu1_im * T[2 + i].im) - s * r;
            T[2 + i].im = (mu1_re * T[2 + i].im - mu1_im * sgnbi) - s * t1_im;
          }

          T[1].re = 0.0;
          T[1].im = 0.0;
        }
      }

      for (info = 0; info < 2; info++) {
        V[info] = T[info + (info << 1)];
      }
    } else {
      xzgeev(A, &info, V, beta1);
      for (info = 0; info < 2; info++) {
        mu1_im = V[info].re;
        if (beta1[info].im == 0.0) {
          if (V[info].im == 0.0) {
            V[info].re /= beta1[info].re;
            V[info].im = 0.0;
          } else if (V[info].re == 0.0) {
            V[info].re = 0.0;
            V[info].im /= beta1[info].re;
          } else {
            V[info].re /= beta1[info].re;
            V[info].im /= beta1[info].re;
          }
        } else if (beta1[info].re == 0.0) {
          if (V[info].re == 0.0) {
            V[info].re = V[info].im / beta1[info].im;
            V[info].im = 0.0;
          } else if (V[info].im == 0.0) {
            V[info].re = 0.0;
            V[info].im = -(mu1_im / beta1[info].im);
          } else {
            V[info].re = V[info].im / beta1[info].im;
            V[info].im = -(mu1_im / beta1[info].im);
          }
        } else {
          t1_im = fabs(beta1[info].re);
          r = fabs(beta1[info].im);
          if (t1_im > r) {
            s = beta1[info].im / beta1[info].re;
            d = beta1[info].re + s * beta1[info].im;
            V[info].re = (V[info].re + s * V[info].im) / d;
            V[info].im = (V[info].im - s * mu1_im) / d;
          } else if (r == t1_im) {
            if (beta1[info].re > 0.0) {
              r = 0.5;
            } else {
              r = -0.5;
            }

            if (beta1[info].im > 0.0) {
              sgnbi = 0.5;
            } else {
              sgnbi = -0.5;
            }

            V[info].re = (V[info].re * r + V[info].im * sgnbi) / t1_im;
            V[info].im = (V[info].im * r - mu1_im * sgnbi) / t1_im;
          } else {
            s = beta1[info].re / beta1[info].im;
            d = beta1[info].im + s * beta1[info].re;
            V[info].re = (s * V[info].re + V[info].im) / d;
            V[info].im = (s * V[info].im - mu1_im) / d;
          }
        }
      }
    }
  }
}

/*
 * File trailer for eig.c
 *
 * [EOF]
 */
