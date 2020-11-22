/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_cavitySystem.h
 *
 * Code generation for function 'f_cavitySystem'
 *
 */

#ifndef F_CAVITYSYSTEM_H
#define F_CAVITYSYSTEM_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_dwql_types.h"

/* Function Declarations */
extern void f_cavitySystem(const double x[6], const double u_mC[2], double fs,
  const double tau_m[4], const double K_m[4], double QL, double dx[6]);

#endif

/* End of code generation (f_cavitySystem.h) */
