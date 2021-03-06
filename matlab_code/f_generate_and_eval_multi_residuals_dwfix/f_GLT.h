/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_GLT.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

#ifndef F_GLT_H
#define F_GLT_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwfix_types.h"

/* Function Declarations */
extern void b_f_GLT(double Sigma, const emxArray_real_T *y, emxArray_real_T
                    *s_max);
extern void f_GLT(const double Sigma[4], const emxArray_real_T *y,
                  emxArray_real_T *s_max);

#endif

/*
 * File trailer for f_GLT.h
 *
 * [EOF]
 */
