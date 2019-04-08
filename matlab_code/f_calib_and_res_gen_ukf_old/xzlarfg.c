/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzlarfg.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "xzlarfg.h"
#include "xscal.h"
#include "recip.h"
#include "xdlapy3.h"
#include "xnrm2.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                creal_T *alpha1
 *                emxArray_creal_T *x
 *                int ix0
 * Return Type  : creal_T
 */
creal_T xzlarfg(int n, creal_T *alpha1, emxArray_creal_T *x, int ix0)
{
  creal_T tau;
  double xnorm;
  double beta1;
  int knt;
  double ai;
  int i7;
  int k;
  creal_T b_alpha1;
  tau.re = 0.0;
  tau.im = 0.0;
  if (!(n <= 0)) {
    xnorm = b_xnrm2(n - 1, x, ix0);
    if ((xnorm != 0.0) || (alpha1->im != 0.0)) {
      beta1 = xdlapy3(alpha1->re, alpha1->im, xnorm);
      if (alpha1->re >= 0.0) {
        beta1 = -beta1;
      }

      if (fabs(beta1) < 1.0020841800044864E-292) {
        knt = 0;
        i7 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i7; k++) {
            xnorm = x->data[k - 1].re;
            ai = x->data[k - 1].im;
            x->data[k - 1].re = 9.9792015476736E+291 * xnorm - 0.0 * ai;
            x->data[k - 1].im = 9.9792015476736E+291 * ai + 0.0 * xnorm;
          }

          beta1 *= 9.9792015476736E+291;
          alpha1->re *= 9.9792015476736E+291;
          alpha1->im *= 9.9792015476736E+291;
        } while (!(fabs(beta1) >= 1.0020841800044864E-292));

        xnorm = b_xnrm2(n - 1, x, ix0);
        beta1 = xdlapy3(alpha1->re, alpha1->im, xnorm);
        if (alpha1->re >= 0.0) {
          beta1 = -beta1;
        }

        xnorm = beta1 - alpha1->re;
        ai = 0.0 - alpha1->im;
        if (ai == 0.0) {
          tau.re = xnorm / beta1;
          tau.im = 0.0;
        } else if (xnorm == 0.0) {
          tau.re = 0.0;
          tau.im = ai / beta1;
        } else {
          tau.re = xnorm / beta1;
          tau.im = ai / beta1;
        }

        b_alpha1.re = alpha1->re - beta1;
        b_alpha1.im = alpha1->im;
        *alpha1 = recip(b_alpha1);
        xscal(n - 1, *alpha1, x, ix0);
        for (k = 1; k <= knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }

        alpha1->re = beta1;
        alpha1->im = 0.0;
      } else {
        xnorm = beta1 - alpha1->re;
        ai = 0.0 - alpha1->im;
        if (ai == 0.0) {
          tau.re = xnorm / beta1;
          tau.im = 0.0;
        } else if (xnorm == 0.0) {
          tau.re = 0.0;
          tau.im = ai / beta1;
        } else {
          tau.re = xnorm / beta1;
          tau.im = ai / beta1;
        }

        b_alpha1.re = alpha1->re - beta1;
        b_alpha1.im = alpha1->im;
        *alpha1 = recip(b_alpha1);
        xscal(n - 1, *alpha1, x, ix0);
        alpha1->re = beta1;
        alpha1->im = 0.0;
      }
    }
  }

  return tau;
}

/*
 * File trailer for xzlarfg.c
 *
 * [EOF]
 */
