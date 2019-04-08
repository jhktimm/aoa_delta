/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_calib_and_res_gen_ukf_initialize.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "f_calib_and_res_gen_ukf_initialize.h"
#include "f_compute_ukf_residual.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void f_calib_and_res_gen_ukf_initialize(void)
{
  rt_InitInfAndNaN(8U);
  f_compute_ukf_residual_init();
}

/*
 * File trailer for f_calib_and_res_gen_ukf_initialize.c
 *
 * [EOF]
 */
