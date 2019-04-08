/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_get_calCoeff_codegen.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:09:16
 */

#ifndef F_GET_CALCOEFF_CODEGEN_H
#define F_GET_CALCOEFF_CODEGEN_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_calib_and_res_gen_ukf_types.h"

/* Function Declarations */
extern void f_get_calCoeff_codegen(const emxArray_real_T *Probe_Ampl, const
  emxArray_real_T *Probe_Phase, const emxArray_real_T *Forw_Ampl, const
  emxArray_real_T *Forw_Phase, const emxArray_real_T *Refl_Ampl, const
  emxArray_real_T *Refl_Probe, double DELAY, double FILLING, double FLATTOP,
  double FS, creal_T calCoeff[4]);

#endif

/*
 * File trailer for f_get_calCoeff_codegen.h
 *
 * [EOF]
 */
