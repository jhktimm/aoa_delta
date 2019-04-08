/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_cavitySystem.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
 */

#ifndef F_CAVITYSYSTEM_H
#define F_CAVITYSYSTEM_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_calib_and_res_gen_ukf_types.h"

/* Function Declarations */
extern void f_cavitySystem(const double x[6], const double u_mC[2], double f0,
  double fs, const double tau_m[4], const double K_m[4], double QL, double dx[6]);

#endif

/*
 * File trailer for f_cavitySystem.h
 *
 * [EOF]
 */
