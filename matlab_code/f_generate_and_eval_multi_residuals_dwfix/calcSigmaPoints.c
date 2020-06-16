/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calcSigmaPoints.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "calcSigmaPoints.h"

/* Function Definitions */

/*
 * Arguments    : const double covariance[4]
 *                const double X1[2]
 *                double c
 *                double X2[8]
 * Return Type  : void
 */
void b_calcSigmaPoints(const double covariance[4], const double X1[2], double c,
  double X2[8])
{
  int j;
  int info;
  double sqrtP[4];
  boolean_T exitg1;
  int jj;
  int b_info;
  double ajj;
  int ix;
  int iy;
  int k;
  for (j = 0; j < 4; j++) {
    sqrtP[j] = covariance[j];
  }

  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j + 1 < 3)) {
    jj = j + (j << 1);
    ajj = 0.0;
    if (!(j < 1)) {
      ix = j;
      iy = j;
      k = 1;
      while (k <= j) {
        ajj += sqrtP[ix] * sqrtP[iy];
        ix += 2;
        iy += 2;
        k = 2;
      }
    }

    ajj = sqrtP[jj] - ajj;
    if (ajj > 0.0) {
      ajj = sqrt(ajj);
      sqrtP[jj] = ajj;
      if (j + 1 < 2) {
        ajj = 1.0 / ajj;
        for (k = jj + 1; k + 1 <= jj + 2; k++) {
          sqrtP[k] *= ajj;
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
    b_info = 2;
  } else {
    b_info = info - 1;
  }

  if (2 <= b_info) {
    sqrtP[2] = 0.0;
  }

  ajj = sqrt(c);
  for (j = 0; j < 4; j++) {
    sqrtP[j] *= ajj;
  }

  for (j = 0; j < 2; j++) {
    for (info = 0; info < 2; info++) {
      X2[info + (j << 1)] = sqrtP[info + (j << 1)];
      X2[info + ((j + 2) << 1)] = -sqrtP[info + (j << 1)];
    }
  }

  for (info = 0; info < 4; info++) {
    for (j = 0; j < 2; j++) {
      X2[j + (info << 1)] += X1[j];
    }
  }
}

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
  int i32;
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
          i32 = (j + 6 * (j - 1)) + 2;
          for (kkR = j + 2; kkR <= i32; kkR += 6) {
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
        i32 = (jj - j) + 6;
        for (jmax = jj + 1; jmax + 1 <= i32; jmax++) {
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
  for (i32 = 0; i32 < 36; i32++) {
    sqrtP[i32] *= ajj;
  }

  for (i32 = 0; i32 < 6; i32++) {
    for (jmax = 0; jmax < 6; jmax++) {
      X2[jmax + 6 * i32] = sqrtP[jmax + 6 * i32];
      X2[jmax + 6 * (i32 + 6)] = -sqrtP[jmax + 6 * i32];
    }
  }

  for (kkC = 0; kkC < 12; kkC++) {
    for (i32 = 0; i32 < 6; i32++) {
      X2[i32 + 6 * kkC] += X1[i32];
    }
  }
}

/*
 * File trailer for calcSigmaPoints.c
 *
 * [EOF]
 */
