/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_comp_dw_ql_Rybaniec.h
 *
 * Code generation for function 'f_comp_dw_ql_Rybaniec'
 *
 */

#ifndef F_COMP_DW_QL_RYBANIEC_H
#define F_COMP_DW_QL_RYBANIEC_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void f_comp_dw_ql_Rybaniec(const emxArray_creal_T *y_mC, const
  emxArray_creal_T *u_mC, double fs, double K, emxArray_real_T *dw,
  emxArray_real_T *w12);

#endif

/* End of code generation (f_comp_dw_ql_Rybaniec.h) */
