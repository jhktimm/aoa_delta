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
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "exp.h"

/* Function Definitions */
void b_exp(emxArray_creal_T *x)
{
  int nx;
  int k;
  double x_re;
  double r;
  nx = x->size[0];
  for (k = 0; k + 1 <= nx; k++) {
    if (x->data[k].im == 0.0) {
      x_re = exp(x->data[k].re);
      r = 0.0;
    } else if (rtIsInf(x->data[k].im) && rtIsInf(x->data[k].re) && (x->data[k].
                re < 0.0)) {
      x_re = 0.0;
      r = 0.0;
    } else {
      r = exp(x->data[k].re / 2.0);
      x_re = r * (r * cos(x->data[k].im));
      r *= r * sin(x->data[k].im);
    }

    x->data[k].re = x_re;
    x->data[k].im = r;
  }
}

/* End of code generation (exp.c) */
