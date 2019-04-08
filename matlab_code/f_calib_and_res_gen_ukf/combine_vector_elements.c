/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: combine_vector_elements.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "combine_vector_elements.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double y[2]
 * Return Type  : void
 */
void combine_vector_elements(const emxArray_real_T *x, double y[2])
{
  int i;
  double s;
  int k;
  if (x->size[1] == 0) {
    for (i = 0; i < 2; i++) {
      y[i] = 0.0;
    }
  } else {
    for (i = 0; i < 2; i++) {
      s = x->data[i];
      for (k = 2; k <= x->size[1]; k++) {
        s += x->data[i + ((k - 1) << 1)];
      }

      y[i] = s;
    }
  }
}

/*
 * File trailer for combine_vector_elements.c
 *
 * [EOF]
 */
