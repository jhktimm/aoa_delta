/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calcSigmaPoints.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 24-Sep-2019 18:29:39
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "calcSigmaPoints.h"

/* Function Definitions */

/*
 * Arguments    : const double covariance[36]
 *                const double X1[6]
 *                double c
 *                double X2[72]
 * Return Type  : void
 */
void calcSigmaPoints(const double covariance[36], const double X1[6], double c,
                     double X2[72])
{
  double sqrtP[36];
  int info;
  int j;
  boolean_T exitg1;
  int jj;
  int jmax;
  double ajj;
  int kkC;
  int ix;
  int iy;
  int kkR;
  int i13;
  double b_c;
  memcpy(&sqrtP[0], &covariance[0], 36U * sizeof(double));
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j + 1 < 7)) {
    jj = j + j * 6;
    ajj = 0.0;
    if (!(j < 1)) {
      ix = j;
      iy = j;
      for (jmax = 1; jmax <= j; jmax++) {
        ajj += sqrtP[ix] * sqrtP[iy];
        ix += 6;
        iy += 6;
      }
    }

    ajj = sqrtP[jj] - ajj;
    if (ajj > 0.0) {
      ajj = sqrt(ajj);
      sqrtP[jj] = ajj;
      if (j + 1 < 6) {
        if (j != 0) {
          ix = j;
          i13 = (j + 6 * (j - 1)) + 2;
          for (kkR = j + 2; kkR <= i13; kkR += 6) {
            b_c = -sqrtP[ix];
            iy = jj + 1;
            jmax = (kkR - j) + 4;
            for (kkC = kkR; kkC <= jmax; kkC++) {
              sqrtP[iy] += sqrtP[kkC - 1] * b_c;
              iy++;
            }

            ix += 6;
          }
        }

        ajj = 1.0 / ajj;
        i13 = (jj - j) + 6;
        for (jmax = jj + 1; jmax + 1 <= i13; jmax++) {
          sqrtP[jmax] *= ajj;
        }
      }

      j++;
    } else {
      sqrtP[jj] = ajj;
      info = j + 1;
      exitg1 = true;
    }
  }

  if (info == 0) {
    jmax = 6;
  } else {
    jmax = info - 1;
  }

  for (kkC = 1; kkC + 1 <= jmax; kkC++) {
    for (kkR = 1; kkR <= kkC; kkR++) {
      sqrtP[(kkR + 6 * kkC) - 1] = 0.0;
    }
  }

  ajj = sqrt(c);
  for (i13 = 0; i13 < 36; i13++) {
    sqrtP[i13] *= ajj;
  }

  for (i13 = 0; i13 < 6; i13++) {
    for (jmax = 0; jmax < 6; jmax++) {
      X2[jmax + 6 * i13] = sqrtP[jmax + 6 * i13];
      X2[jmax + 6 * (i13 + 6)] = -sqrtP[jmax + 6 * i13];
    }
  }

  for (kkC = 0; kkC < 12; kkC++) {
    for (i13 = 0; i13 < 6; i13++) {
      X2[i13 + 6 * kkC] += X1[i13];
    }
  }
}

/*
 * File trailer for calcSigmaPoints.c
 *
 * [EOF]
 */
