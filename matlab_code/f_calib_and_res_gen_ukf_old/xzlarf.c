/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzlarf.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "xzlarf.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                const creal_T tau
 *                emxArray_creal_T *C
 *                int ic0
 *                int ldc
 *                creal_T work[4]
 * Return Type  : void
 */
void xzlarf(int m, int n, int iv0, const creal_T tau, emxArray_creal_T *C, int
            ic0, int ldc, creal_T work[4])
{
  int lastv;
  int lastc;
  int i;
  boolean_T exitg1;
  boolean_T b_C;
  double c_re;
  double c_im;
  int i10;
  int jy;
  int ia;
  int j;
  int exitg2;
  int ix;
  double temp_re;
  double temp_im;
  double C_re;
  double C_im;
  if ((tau.re != 0.0) || (tau.im != 0.0)) {
    lastv = m;
    i = iv0 + m;
    exitg1 = false;
    while ((!exitg1) && (lastv > 0)) {
      b_C = ((C->data[i - 2].re == 0.0) && (C->data[i - 2].im == 0.0));
      if (b_C) {
        lastv--;
        i--;
      } else {
        exitg1 = true;
      }
    }

    lastc = n;
    exitg1 = false;
    while ((!exitg1) && (lastc > 0)) {
      i = ic0 + (lastc - 1) * ldc;
      ia = i;
      do {
        exitg2 = 0;
        if (ia <= (i + lastv) - 1) {
          b_C = ((C->data[ia - 1].re != 0.0) || (C->data[ia - 1].im != 0.0));
          if (b_C) {
            exitg2 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg2 = 2;
        }
      } while (exitg2 == 0);

      if (exitg2 == 1) {
        exitg1 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      for (i = 1; i <= lastc; i++) {
        work[i - 1].re = 0.0;
        work[i - 1].im = 0.0;
      }

      i = 0;
      i10 = ic0 + ldc * (lastc - 1);
      for (jy = ic0; jy <= i10; jy += ldc) {
        ix = iv0 - 1;
        c_re = 0.0;
        c_im = 0.0;
        j = (jy + lastv) - 1;
        for (ia = jy - 1; ia + 1 <= j; ia++) {
          c_re += C->data[ia].re * C->data[ix].re + C->data[ia].im * C->data[ix]
            .im;
          c_im += C->data[ia].re * C->data[ix].im - C->data[ia].im * C->data[ix]
            .re;
          ix++;
        }

        work[i].re += c_re - 0.0 * c_im;
        work[i].im += c_im + 0.0 * c_re;
        i++;
      }
    }

    c_re = -tau.re;
    c_im = -tau.im;
    if (!((-tau.re == 0.0) && (-tau.im == 0.0))) {
      i = ic0 - 1;
      jy = 0;
      for (j = 1; j <= lastc; j++) {
        if ((work[jy].re != 0.0) || (work[jy].im != 0.0)) {
          temp_re = work[jy].re * c_re + work[jy].im * c_im;
          temp_im = work[jy].re * c_im - work[jy].im * c_re;
          ix = iv0;
          i10 = lastv + i;
          for (ia = i; ia + 1 <= i10; ia++) {
            C_re = C->data[ix - 1].re * temp_re - C->data[ix - 1].im * temp_im;
            C_im = C->data[ix - 1].re * temp_im + C->data[ix - 1].im * temp_re;
            C->data[ia].re += C_re;
            C->data[ia].im += C_im;
            ix++;
          }
        }

        jy++;
        i += ldc;
      }
    }
  }
}

/*
 * File trailer for xzlarf.c
 *
 * [EOF]
 */
