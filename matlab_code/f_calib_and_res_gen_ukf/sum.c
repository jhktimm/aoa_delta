/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sum.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "sum.h"
#include "combine_vector_elements.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double y[2]
 * Return Type  : void
 */
void b_sum(const emxArray_real_T *x, double y[2])
{
  combine_vector_elements(x, y);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                double y[4]
 * Return Type  : void
 */
void sum(const emxArray_real_T *x, double y[4])
{
  int vlen;
  int npages;
  int k;
  int i;
  int xoffset;
  double s;
  if (x->size[0] == 0) {
    for (vlen = 0; vlen < 4; vlen++) {
      y[vlen] = 0.0;
    }
  } else {
    vlen = x->size[0];
    npages = 1;
    for (k = 0; k < 2; k++) {
      npages <<= 1;
    }

    for (i = 0; i + 1 <= npages; i++) {
      xoffset = i * vlen;
      s = x->data[xoffset];
      for (k = 2; k <= vlen; k++) {
        s += x->data[(xoffset + k) - 1];
      }

      y[i] = s;
    }
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
