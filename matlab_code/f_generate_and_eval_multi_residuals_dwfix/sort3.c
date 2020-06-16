/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: sort3.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "sort3.h"

/* Function Definitions */

/*
 * Arguments    : int i1
 *                double v1
 *                int i2
 *                double v2
 *                int i3
 *                double v3
 *                int *b_j1
 *                int *j2
 *                int *j3
 * Return Type  : void
 */
void sort3(int i1, double v1, int i2, double v2, int i3, double v3, int *b_j1,
           int *j2, int *j3)
{
  if (v1 < v2) {
    if (v2 < v3) {
      *b_j1 = i1;
      *j2 = i2;
      *j3 = i3;
    } else if (v1 < v3) {
      *b_j1 = i1;
      *j2 = i3;
      *j3 = i2;
    } else {
      *b_j1 = i3;
      *j2 = i1;
      *j3 = i2;
    }
  } else if (v1 < v3) {
    *b_j1 = i2;
    *j2 = i1;
    *j3 = i3;
  } else if (v2 < v3) {
    *b_j1 = i2;
    *j2 = i3;
    *j3 = i1;
  } else {
    *b_j1 = i3;
    *j2 = i2;
    *j3 = i1;
  }
}

/*
 * File trailer for sort3.c
 *
 * [EOF]
 */
