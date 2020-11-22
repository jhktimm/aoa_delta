/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * colon.c
 *
 * Code generation for function 'colon'
 *
 */

/* Include files */
#include "colon.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void b_eml_float_colon(double a, emxArray_real_T *y)
{
  double ndbl;
  double apnd;
  double u0;
  int n;
  int nm1d2;
  int k;
  int y_tmp;
  ndbl = floor((1821.0 - a) + 0.5);
  apnd = a + ndbl;
  u0 = fabs(a);
  if (!(u0 > 1821.0)) {
    u0 = 1821.0;
  }

  if (fabs(apnd - 1821.0) < 4.4408920985006262E-16 * u0) {
    ndbl++;
    apnd = 1821.0;
  } else if (apnd - 1821.0 > 0.0) {
    apnd = a + (ndbl - 1.0);
  } else {
    ndbl++;
  }

  if (ndbl >= 0.0) {
    n = (int)ndbl;
  } else {
    n = 0;
  }

  nm1d2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_real_T(y, nm1d2);
  if (n > 0) {
    y->data[0] = a;
    if (n > 1) {
      y->data[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (k = 0; k <= nm1d2 - 2; k++) {
        y_tmp = k + 1;
        y->data[k + 1] = a + (double)y_tmp;
        y->data[(n - k) - 2] = apnd - (double)y_tmp;
      }

      if (nm1d2 << 1 == n - 1) {
        y->data[nm1d2] = (a + apnd) / 2.0;
      } else {
        y->data[nm1d2] = a + (double)nm1d2;
        y->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }
}

void c_eml_float_colon(double a, emxArray_real_T *y)
{
  double ndbl;
  double apnd;
  double u0;
  int n;
  int nm1d2;
  int k;
  int y_tmp;
  ndbl = floor((16384.0 - a) + 0.5);
  apnd = a + ndbl;
  u0 = fabs(a);
  if (!(u0 > 16384.0)) {
    u0 = 16384.0;
  }

  if (fabs(apnd - 16384.0) < 4.4408920985006262E-16 * u0) {
    ndbl++;
    apnd = 16384.0;
  } else if (apnd - 16384.0 > 0.0) {
    apnd = a + (ndbl - 1.0);
  } else {
    ndbl++;
  }

  if (ndbl >= 0.0) {
    n = (int)ndbl;
  } else {
    n = 0;
  }

  nm1d2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_real_T(y, nm1d2);
  if (n > 0) {
    y->data[0] = a;
    if (n > 1) {
      y->data[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (k = 0; k <= nm1d2 - 2; k++) {
        y_tmp = k + 1;
        y->data[k + 1] = a + (double)y_tmp;
        y->data[(n - k) - 2] = apnd - (double)y_tmp;
      }

      if (nm1d2 << 1 == n - 1) {
        y->data[nm1d2] = (a + apnd) / 2.0;
      } else {
        y->data[nm1d2] = a + (double)nm1d2;
        y->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }
}

void eml_float_colon(double a, double b, emxArray_real_T *y)
{
  double ndbl;
  double apnd;
  double cdiff;
  double u0;
  double u1;
  int n;
  int nm1d2;
  int k;
  int y_tmp;
  ndbl = floor((b - a) + 0.5);
  apnd = a + ndbl;
  cdiff = apnd - b;
  u0 = fabs(a);
  u1 = fabs(b);
  if ((u0 > u1) || rtIsNaN(u1)) {
    u1 = u0;
  }

  if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
    ndbl++;
    apnd = b;
  } else if (cdiff > 0.0) {
    apnd = a + (ndbl - 1.0);
  } else {
    ndbl++;
  }

  if (ndbl >= 0.0) {
    n = (int)ndbl;
  } else {
    n = 0;
  }

  nm1d2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_real_T(y, nm1d2);
  if (n > 0) {
    y->data[0] = a;
    if (n > 1) {
      y->data[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (k = 0; k <= nm1d2 - 2; k++) {
        y_tmp = k + 1;
        y->data[k + 1] = a + (double)y_tmp;
        y->data[(n - k) - 2] = apnd - (double)y_tmp;
      }

      if (nm1d2 << 1 == n - 1) {
        y->data[nm1d2] = (a + apnd) / 2.0;
      } else {
        y->data[nm1d2] = a + (double)nm1d2;
        y->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }
}

/* End of code generation (colon.c) */
