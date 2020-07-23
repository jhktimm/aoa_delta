/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * exp.c
 *
 * Code generation for function 'exp'
 *
 */

/* Include files */
#include "exp.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void b_exp(emxArray_creal_T *x)
{
  int nx;
  int k;
  double r;
  double d;
  nx = x->size[0];
  for (k = 0; k < nx; k++) {
    if (x->data[k].im == 0.0) {
      x->data[k].re = exp(x->data[k].re);
      x->data[k].im = 0.0;
    } else if (rtIsInf(x->data[k].im) && rtIsInf(x->data[k].re) && (x->data[k].
                re < 0.0)) {
      x->data[k].re = 0.0;
      x->data[k].im = 0.0;
    } else {
      r = exp(x->data[k].re / 2.0);
      d = x->data[k].im;
      x->data[k].re = r * (r * cos(x->data[k].im));
      x->data[k].im = r * (r * sin(d));
    }
  }
}

/* End of code generation (exp.c) */
