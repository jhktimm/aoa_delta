/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgeqp3.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:09:16
 */

#ifndef XGEQP3_H
#define XGEQP3_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "f_calib_and_res_gen_ukf_types.h"

/* Function Declarations */
extern void b_xgeqp3(emxArray_creal_T *A, creal_T tau_data[], int tau_size[1],
                     int jpvt[4]);
extern void xgeqp3(emxArray_creal_T *A, creal_T tau_data[], int tau_size[1], int
                   jpvt[2]);

#endif

/*
 * File trailer for xgeqp3.h
 *
 * [EOF]
 */
