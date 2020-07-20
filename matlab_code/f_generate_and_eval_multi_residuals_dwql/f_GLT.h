/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_GLT.h
 *
 * Code generation for function 'f_GLT'
 *
 */

#ifndef F_GLT_H
#define F_GLT_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void b_f_GLT(double Sigma, const emxArray_real_T *y, emxArray_real_T
                    *s_max);
extern void f_GLT(const double Sigma[4], const emxArray_real_T *y,
                  emxArray_real_T *s_max);

#endif

/* End of code generation (f_GLT.h) */
