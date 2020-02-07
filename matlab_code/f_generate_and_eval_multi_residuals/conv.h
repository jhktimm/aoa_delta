/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * conv.h
 *
 * Code generation for function 'conv'
 *
 */

#ifndef CONV_H
#define CONV_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern void conv(const emxArray_real_T *A, const double B[5], emxArray_real_T *C);

#endif

/* End of code generation (conv.h) */
