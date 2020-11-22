/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_and_eval_multi_residuals_dwql_initialize.c
 *
 * Code generation for function 'f_generate_and_eval_multi_residuals_dwql_initialize'
 *
 */

/* Include files */
#include "f_generate_and_eval_multi_residuals_dwql_initialize.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void f_generate_and_eval_multi_residuals_dwql_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_f_generate_and_eval_multi_residuals_dwql = true;
}

/* End of code generation (f_generate_and_eval_multi_residuals_dwql_initialize.c) */
