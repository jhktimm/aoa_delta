/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ixamax.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "ixamax.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const double x[2]
 *                int ix0
 * Return Type  : int
 */
int ixamax(int n, const double x[2], int ix0)
{
  int idxmax;
  idxmax = 1;
  if ((n > 1) && (fabs(x[ix0]) > fabs(x[ix0 - 1]))) {
    idxmax = 2;
  }

  return idxmax;
}

/*
 * File trailer for ixamax.c
 *
 * [EOF]
 */
