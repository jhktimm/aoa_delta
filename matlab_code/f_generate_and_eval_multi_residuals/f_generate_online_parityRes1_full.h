/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_generate_online_parityRes1_full.h
 *
 * Code generation for function 'f_generate_online_parityRes1_full'
 *
 */

#ifndef F_GENERATE_ONLINE_PARITYRES1_FULL_H
#define F_GENERATE_ONLINE_PARITYRES1_FULL_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_generate_and_eval_multi_residuals_types.h"

/* Function Declarations */
extern void c_f_generate_online_parityRes1_(const emxArray_real_T *Probe_Ampl,
  const emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Probe, double FS,
  double QL_nom, emxArray_real_T *residual1);

#endif

/* End of code generation (f_generate_online_parityRes1_full.h) */
