/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * calcSigmaPoints.c
 *
 * Code generation for function 'calcSigmaPoints'
 *
 */

/* Include files */
#include "calcSigmaPoints.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void b_calcSigmaPoints(const double covariance[4], const double X1[2], double c,
  double X2[8])
{
  double sqrtP[4];
  int info;
  int j;
  boolean_T exitg1;
  int idxAjj;
  double ssq;
  int k;
  sqrtP[0] = covariance[0];
  sqrtP[1] = covariance[1];
  sqrtP[2] = covariance[2];
  sqrtP[3] = covariance[3];
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 2)) {
    idxAjj = j + (j << 1);
    ssq = 0.0;
    if (j >= 1) {
      ssq = sqrtP[1] * sqrtP[1];
    }

    ssq = sqrtP[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = sqrt(ssq);
      sqrtP[idxAjj] = ssq;
      if (j + 1 < 2) {
        idxAjj += 2;
        ssq = 1.0 / ssq;
        for (k = idxAjj; k <= idxAjj; k++) {
          sqrtP[k - 1] *= ssq;
        }
      }

      j++;
    } else {
      sqrtP[idxAjj] = ssq;
      info = j + 1;
      exitg1 = true;
    }
  }

  if (info == 0) {
    info = 2;
  } else {
    info--;
  }

  if (2 <= info) {
    sqrtP[2] = 0.0;
  }

  ssq = sqrt(c);
  sqrtP[0] *= ssq;
  sqrtP[1] *= ssq;
  sqrtP[2] *= ssq;
  sqrtP[3] *= ssq;
  X2[0] = sqrtP[0];
  X2[4] = -sqrtP[0];
  X2[1] = sqrtP[1];
  X2[5] = -sqrtP[1];
  X2[2] = sqrtP[2];
  X2[6] = -sqrtP[2];
  X2[3] = sqrtP[3];
  X2[7] = -sqrtP[3];
  for (info = 0; info < 4; info++) {
    idxAjj = info << 1;
    X2[idxAjj] += X1[0];
    idxAjj++;
    X2[idxAjj] += X1[1];
  }
}

void calcSigmaPoints(const double covariance[36], const double X1[6], double c,
                     double X2[72])
{
  double sqrtP[36];
  int info;
  int j;
  boolean_T exitg1;
  int idxAjj;
  int jmax;
  double ssq;
  int ix;
  int iy;
  int i;
  int i1;
  int idxAjp1j;
  int iac;
  double b_c;
  int ia;
  memcpy(&sqrtP[0], &covariance[0], 36U * sizeof(double));
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 6)) {
    idxAjj = j + j * 6;
    ssq = 0.0;
    if (j >= 1) {
      ix = j;
      iy = j;
      for (jmax = 0; jmax < j; jmax++) {
        ssq += sqrtP[ix] * sqrtP[iy];
        ix += 6;
        iy += 6;
      }
    }

    ssq = sqrtP[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = sqrt(ssq);
      sqrtP[idxAjj] = ssq;
      if (j + 1 < 6) {
        jmax = j + 2;
        idxAjp1j = idxAjj + 2;
        if (j != 0) {
          ix = j;
          i = (j + 6 * (j - 1)) + 2;
          for (iac = jmax; iac <= i; iac += 6) {
            b_c = -sqrtP[ix];
            iy = idxAjj + 1;
            i1 = (iac - j) + 4;
            for (ia = iac; ia <= i1; ia++) {
              sqrtP[iy] += sqrtP[ia - 1] * b_c;
              iy++;
            }

            ix += 6;
          }
        }

        ssq = 1.0 / ssq;
        i = (idxAjj - j) + 6;
        for (jmax = idxAjp1j; jmax <= i; jmax++) {
          sqrtP[jmax - 1] *= ssq;
        }
      }

      j++;
    } else {
      sqrtP[idxAjj] = ssq;
      info = j + 1;
      exitg1 = true;
    }
  }

  if (info == 0) {
    jmax = 6;
  } else {
    jmax = info - 1;
  }

  for (j = 2; j <= jmax; j++) {
    for (info = 0; info <= j - 2; info++) {
      sqrtP[info + 6 * (j - 1)] = 0.0;
    }
  }

  ssq = sqrt(c);
  for (i = 0; i < 36; i++) {
    sqrtP[i] *= ssq;
  }

  for (i = 0; i < 6; i++) {
    for (i1 = 0; i1 < 6; i1++) {
      jmax = i1 + 6 * i;
      X2[jmax] = sqrtP[jmax];
      X2[i1 + 6 * (i + 6)] = -sqrtP[jmax];
    }
  }

  for (j = 0; j < 12; j++) {
    for (i = 0; i < 6; i++) {
      jmax = i + 6 * j;
      X2[jmax] += X1[i];
    }
  }
}

/* End of code generation (calcSigmaPoints.c) */
