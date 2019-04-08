/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xscal.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "xscal.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T a
 *                emxArray_creal_T *x
 *                int ix0
 * Return Type  : void
 */
void b_xscal(const creal_T a, emxArray_creal_T *x, int ix0)
{
  int k;
  double x_re;
  double x_im;
  for (k = ix0; k < ix0; k++) {
    x_re = x->data[k - 1].re;
    x_im = x->data[k - 1].im;
    x->data[k - 1].re = a.re * x_re - a.im * x_im;
    x->data[k - 1].im = a.re * x_im + a.im * x_re;
  }
}

/*
 * Arguments    : int n
 *                const creal_T a
 *                emxArray_creal_T *x
 *                int ix0
 * Return Type  : void
 */
void c_xscal(int n, const creal_T a, emxArray_creal_T *x, int ix0)
{
  int i9;
  int k;
  double x_re;
  double x_im;
  i9 = (ix0 + n) - 1;
  for (k = ix0; k <= i9; k++) {
    x_re = x->data[k - 1].re;
    x_im = x->data[k - 1].im;
    x->data[k - 1].re = a.re * x_re - a.im * x_im;
    x->data[k - 1].im = a.re * x_im + a.im * x_re;
  }
}

/*
 * Arguments    : const creal_T a
 *                emxArray_creal_T *x
 *                int ix0
 * Return Type  : void
 */
void d_xscal(const creal_T a, emxArray_creal_T *x, int ix0)
{
  int k;
  double x_re;
  double x_im;
  for (k = ix0; k < ix0; k++) {
    x_re = x->data[k - 1].re;
    x_im = x->data[k - 1].im;
    x->data[k - 1].re = a.re * x_re - a.im * x_im;
    x->data[k - 1].im = a.re * x_im + a.im * x_re;
  }
}

/*
 * Arguments    : int n
 *                const creal_T a
 *                emxArray_creal_T *x
 *                int ix0
 * Return Type  : void
 */
void xscal(int n, const creal_T a, emxArray_creal_T *x, int ix0)
{
  int i8;
  int k;
  double x_re;
  double x_im;
  i8 = (ix0 + n) - 1;
  for (k = ix0; k <= i8; k++) {
    x_re = x->data[k - 1].re;
    x_im = x->data[k - 1].im;
    x->data[k - 1].re = a.re * x_re - a.im * x_im;
    x->data[k - 1].im = a.re * x_im + a.im * x_re;
  }
}

/*
 * File trailer for xscal.c
 *
 * [EOF]
 */
