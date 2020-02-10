/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eps.c
 *
 * Code generation for function 'eps'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "eps.h"

/* Function Definitions */
double eps(double x)
{
  double r;
  double absxk;
  int exponent;
  absxk = fabs(x);
  if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
    if (absxk <= 2.2250738585072014E-308) {
      r = 4.94065645841247E-324;
    } else {
      frexp(absxk, &exponent);
      r = ldexp(1.0, exponent - 53);
    }
  } else {
    r = rtNaN;
  }

  return r;
}

/* End of code generation (eps.c) */
