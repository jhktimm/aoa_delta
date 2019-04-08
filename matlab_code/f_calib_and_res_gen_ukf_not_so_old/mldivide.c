/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mldivide.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:09:16
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "mldivide.h"
#include "f_calib_and_res_gen_ukf_emxutil.h"
#include "xgeqp3.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *A
 *                const emxArray_creal_T *B
 *                creal_T Y[4]
 * Return Type  : void
 */
void b_mldivide(const emxArray_creal_T *A, const emxArray_creal_T *B, creal_T Y
                [4])
{
  emxArray_creal_T *b_A;
  int minmn;
  int i3;
  creal_T A_data[16];
  int j;
  int jpvt[4];
  int c;
  creal_T tau_data[4];
  int tau_size[1];
  int rankR;
  int ix;
  double tol;
  int maxmn;
  double tauj_im;
  int i;
  emxArray_creal_T *b_B;
  double Y_re;
  double wj_re;
  double wj_im;
  if (A->size[0] == 4) {
    minmn = A->size[0] * A->size[1];
    for (i3 = 0; i3 < minmn; i3++) {
      A_data[i3] = A->data[i3];
    }

    for (i3 = 0; i3 < 4; i3++) {
      jpvt[i3] = 1 + i3;
    }

    for (j = 0; j < 3; j++) {
      c = j * 5;
      minmn = 0;
      ix = c;
      tol = fabs(A_data[c].re) + fabs(A_data[c].im);
      for (maxmn = 1; maxmn + 1 <= 4 - j; maxmn++) {
        ix++;
        tauj_im = fabs(A_data[ix].re) + fabs(A_data[ix].im);
        if (tauj_im > tol) {
          minmn = maxmn;
          tol = tauj_im;
        }
      }

      if ((A_data[c + minmn].re != 0.0) || (A_data[c + minmn].im != 0.0)) {
        if (minmn != 0) {
          jpvt[j] = (j + minmn) + 1;
          ix = j;
          minmn += j;
          for (maxmn = 0; maxmn < 4; maxmn++) {
            tol = A_data[ix].re;
            tauj_im = A_data[ix].im;
            A_data[ix] = A_data[minmn];
            A_data[minmn].re = tol;
            A_data[minmn].im = tauj_im;
            ix += 4;
            minmn += 4;
          }
        }

        i3 = (c - j) + 4;
        for (i = c + 1; i + 1 <= i3; i++) {
          wj_re = A_data[i].re;
          tol = A_data[c].re;
          if (A_data[c].im == 0.0) {
            if (A_data[i].im == 0.0) {
              A_data[i].re /= A_data[c].re;
              A_data[i].im = 0.0;
            } else if (A_data[i].re == 0.0) {
              A_data[i].re = 0.0;
              A_data[i].im /= tol;
            } else {
              A_data[i].re /= A_data[c].re;
              A_data[i].im /= tol;
            }
          } else if (A_data[c].re == 0.0) {
            if (A_data[i].re == 0.0) {
              A_data[i].re = A_data[i].im / A_data[c].im;
              A_data[i].im = 0.0;
            } else if (A_data[i].im == 0.0) {
              A_data[i].re = 0.0;
              A_data[i].im = -(wj_re / A_data[c].im);
            } else {
              A_data[i].re = A_data[i].im / A_data[c].im;
              A_data[i].im = -(wj_re / A_data[c].im);
            }
          } else {
            wj_im = fabs(A_data[c].re);
            tauj_im = fabs(A_data[c].im);
            if (wj_im > tauj_im) {
              tauj_im = A_data[c].im / A_data[c].re;
              tol = A_data[c].re + tauj_im * A_data[c].im;
              A_data[i].re = (A_data[i].re + tauj_im * A_data[i].im) / tol;
              A_data[i].im = (A_data[i].im - tauj_im * wj_re) / tol;
            } else if (tauj_im == wj_im) {
              if (A_data[c].re > 0.0) {
                tauj_im = 0.5;
              } else {
                tauj_im = -0.5;
              }

              if (A_data[c].im > 0.0) {
                tol = 0.5;
              } else {
                tol = -0.5;
              }

              A_data[i].re = (A_data[i].re * tauj_im + A_data[i].im * tol) /
                wj_im;
              A_data[i].im = (A_data[i].im * tauj_im - wj_re * tol) / wj_im;
            } else {
              tauj_im = A_data[c].re / A_data[c].im;
              tol = A_data[c].im + tauj_im * A_data[c].re;
              A_data[i].re = (tauj_im * A_data[i].re + A_data[i].im) / tol;
              A_data[i].im = (tauj_im * A_data[i].im - wj_re) / tol;
            }
          }
        }
      }

      minmn = c;
      maxmn = c + 4;
      for (rankR = 1; rankR <= 3 - j; rankR++) {
        if ((A_data[maxmn].re != 0.0) || (A_data[maxmn].im != 0.0)) {
          tol = -A_data[maxmn].re - A_data[maxmn].im * 0.0;
          tauj_im = A_data[maxmn].re * 0.0 + -A_data[maxmn].im;
          ix = c + 1;
          i3 = (minmn - j) + 8;
          for (i = 5 + minmn; i + 1 <= i3; i++) {
            wj_re = A_data[ix].re * tauj_im + A_data[ix].im * tol;
            A_data[i].re += A_data[ix].re * tol - A_data[ix].im * tauj_im;
            A_data[i].im += wj_re;
            ix++;
          }
        }

        maxmn += 4;
        minmn += 4;
      }
    }

    for (i3 = 0; i3 < 4; i3++) {
      Y[i3] = B->data[i3];
    }

    for (minmn = 0; minmn < 3; minmn++) {
      if ((signed char)jpvt[minmn] != minmn + 1) {
        tol = Y[minmn].re;
        tauj_im = Y[minmn].im;
        Y[minmn] = Y[(signed char)jpvt[minmn] - 1];
        Y[(signed char)jpvt[minmn] - 1].re = tol;
        Y[(signed char)jpvt[minmn] - 1].im = tauj_im;
      }
    }

    for (maxmn = 0; maxmn < 4; maxmn++) {
      minmn = maxmn << 2;
      if ((Y[maxmn].re != 0.0) || (Y[maxmn].im != 0.0)) {
        for (i = maxmn + 1; i + 1 < 5; i++) {
          tol = Y[maxmn].re * A_data[i + minmn].im + Y[maxmn].im * A_data[i +
            minmn].re;
          Y[i].re -= Y[maxmn].re * A_data[i + minmn].re - Y[maxmn].im * A_data[i
            + minmn].im;
          Y[i].im -= tol;
        }
      }
    }

    for (maxmn = 3; maxmn >= 0; maxmn += -1) {
      minmn = maxmn << 2;
      if ((Y[maxmn].re != 0.0) || (Y[maxmn].im != 0.0)) {
        Y_re = Y[maxmn].re;
        tol = A_data[maxmn + minmn].re;
        wj_re = A_data[maxmn + minmn].im;
        if (wj_re == 0.0) {
          if (Y[maxmn].im == 0.0) {
            Y[maxmn].re /= tol;
            Y[maxmn].im = 0.0;
          } else if (Y[maxmn].re == 0.0) {
            Y[maxmn].re = 0.0;
            Y[maxmn].im /= tol;
          } else {
            Y[maxmn].re /= tol;
            Y[maxmn].im /= tol;
          }
        } else if (tol == 0.0) {
          if (Y[maxmn].re == 0.0) {
            Y[maxmn].re = Y[maxmn].im / wj_re;
            Y[maxmn].im = 0.0;
          } else if (Y[maxmn].im == 0.0) {
            Y[maxmn].re = 0.0;
            Y[maxmn].im = -(Y_re / wj_re);
          } else {
            Y[maxmn].re = Y[maxmn].im / wj_re;
            Y[maxmn].im = -(Y_re / wj_re);
          }
        } else {
          wj_im = fabs(tol);
          tauj_im = fabs(wj_re);
          if (wj_im > tauj_im) {
            tauj_im = wj_re / tol;
            tol += tauj_im * wj_re;
            Y[maxmn].re = (Y[maxmn].re + tauj_im * Y[maxmn].im) / tol;
            Y[maxmn].im = (Y[maxmn].im - tauj_im * Y_re) / tol;
          } else if (tauj_im == wj_im) {
            if (tol > 0.0) {
              tauj_im = 0.5;
            } else {
              tauj_im = -0.5;
            }

            if (wj_re > 0.0) {
              tol = 0.5;
            } else {
              tol = -0.5;
            }

            Y[maxmn].re = (Y[maxmn].re * tauj_im + Y[maxmn].im * tol) / wj_im;
            Y[maxmn].im = (Y[maxmn].im * tauj_im - Y_re * tol) / wj_im;
          } else {
            tauj_im = tol / wj_re;
            tol = wj_re + tauj_im * tol;
            Y[maxmn].re = (tauj_im * Y[maxmn].re + Y[maxmn].im) / tol;
            Y[maxmn].im = (tauj_im * Y[maxmn].im - Y_re) / tol;
          }
        }

        for (i = 0; i + 1 <= maxmn; i++) {
          tol = Y[maxmn].re * A_data[i + minmn].im + Y[maxmn].im * A_data[i +
            minmn].re;
          Y[i].re -= Y[maxmn].re * A_data[i + minmn].re - Y[maxmn].im * A_data[i
            + minmn].im;
          Y[i].im -= tol;
        }
      }
    }
  } else {
    emxInit_creal_T1(&b_A, 2);
    i3 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = 4;
    emxEnsureCapacity((emxArray__common *)b_A, i3, sizeof(creal_T));
    minmn = A->size[0] * A->size[1];
    for (i3 = 0; i3 < minmn; i3++) {
      b_A->data[i3] = A->data[i3];
    }

    b_xgeqp3(b_A, tau_data, tau_size, jpvt);
    rankR = 0;
    if (b_A->size[0] < 4) {
      minmn = 3;
      maxmn = 4;
    } else {
      minmn = 4;
      maxmn = b_A->size[0];
    }

    tol = (double)maxmn * (fabs(b_A->data[0].re) + fabs(b_A->data[0].im)) *
      2.2204460492503131E-16;
    while ((rankR < minmn) && (fabs(b_A->data[rankR + b_A->size[0] * rankR].re)
            + fabs(b_A->data[rankR + b_A->size[0] * rankR].im) >= tol)) {
      rankR++;
    }

    emxInit_creal_T(&b_B, 1);
    i3 = b_B->size[0];
    b_B->size[0] = B->size[0];
    emxEnsureCapacity((emxArray__common *)b_B, i3, sizeof(creal_T));
    minmn = B->size[0];
    for (i3 = 0; i3 < minmn; i3++) {
      b_B->data[i3] = B->data[i3];
    }

    for (i = 0; i < 4; i++) {
      Y[i].re = 0.0;
      Y[i].im = 0.0;
    }

    minmn = b_A->size[0];
    if (b_A->size[0] < 4) {
      maxmn = 3;
    } else {
      maxmn = 4;
    }

    for (j = 0; j + 1 <= maxmn; j++) {
      if ((tau_data[j].re != 0.0) || (-tau_data[j].im != 0.0)) {
        wj_re = b_B->data[j].re;
        wj_im = b_B->data[j].im;
        for (i = j + 1; i + 1 <= minmn; i++) {
          wj_re += b_A->data[i + b_A->size[0] * j].re * b_B->data[i].re +
            b_A->data[i + b_A->size[0] * j].im * b_B->data[i].im;
          wj_im += b_A->data[i + b_A->size[0] * j].re * b_B->data[i].im -
            b_A->data[i + b_A->size[0] * j].im * b_B->data[i].re;
        }

        tol = wj_re;
        wj_re = tau_data[j].re * wj_re - -tau_data[j].im * wj_im;
        wj_im = tau_data[j].re * wj_im + -tau_data[j].im * tol;
        if ((wj_re != 0.0) || (wj_im != 0.0)) {
          b_B->data[j].re -= wj_re;
          b_B->data[j].im -= wj_im;
          for (i = j + 1; i + 1 <= minmn; i++) {
            tol = b_A->data[i + b_A->size[0] * j].re * wj_re - b_A->data[i +
              b_A->size[0] * j].im * wj_im;
            tauj_im = b_A->data[i + b_A->size[0] * j].re * wj_im + b_A->data[i +
              b_A->size[0] * j].im * wj_re;
            b_B->data[i].re -= tol;
            b_B->data[i].im -= tauj_im;
          }
        }
      }
    }

    for (i = 0; i + 1 <= rankR; i++) {
      Y[jpvt[i] - 1] = b_B->data[i];
    }

    emxFree_creal_T(&b_B);
    for (j = rankR - 1; j + 1 > 0; j--) {
      Y_re = Y[jpvt[j] - 1].re;
      tol = b_A->data[j + b_A->size[0] * j].re;
      wj_re = b_A->data[j + b_A->size[0] * j].im;
      if (wj_re == 0.0) {
        if (Y[jpvt[j] - 1].im == 0.0) {
          Y[jpvt[j] - 1].re /= tol;
          Y[jpvt[j] - 1].im = 0.0;
        } else if (Y[jpvt[j] - 1].re == 0.0) {
          Y[jpvt[j] - 1].re = 0.0;
          Y[jpvt[j] - 1].im /= tol;
        } else {
          Y[jpvt[j] - 1].re /= tol;
          Y[jpvt[j] - 1].im /= tol;
        }
      } else if (tol == 0.0) {
        if (Y[jpvt[j] - 1].re == 0.0) {
          Y[jpvt[j] - 1].re = Y[jpvt[j] - 1].im / wj_re;
          Y[jpvt[j] - 1].im = 0.0;
        } else if (Y[jpvt[j] - 1].im == 0.0) {
          Y[jpvt[j] - 1].re = 0.0;
          Y[jpvt[j] - 1].im = -(Y_re / wj_re);
        } else {
          Y[jpvt[j] - 1].re = Y[jpvt[j] - 1].im / wj_re;
          Y[jpvt[j] - 1].im = -(Y_re / wj_re);
        }
      } else {
        wj_im = fabs(tol);
        tauj_im = fabs(wj_re);
        if (wj_im > tauj_im) {
          tauj_im = wj_re / tol;
          tol += tauj_im * wj_re;
          Y[jpvt[j] - 1].re = (Y[jpvt[j] - 1].re + tauj_im * Y[jpvt[j] - 1].im) /
            tol;
          Y[jpvt[j] - 1].im = (Y[jpvt[j] - 1].im - tauj_im * Y_re) / tol;
        } else if (tauj_im == wj_im) {
          if (tol > 0.0) {
            tauj_im = 0.5;
          } else {
            tauj_im = -0.5;
          }

          if (wj_re > 0.0) {
            tol = 0.5;
          } else {
            tol = -0.5;
          }

          Y[jpvt[j] - 1].re = (Y[jpvt[j] - 1].re * tauj_im + Y[jpvt[j] - 1].im *
                               tol) / wj_im;
          Y[jpvt[j] - 1].im = (Y[jpvt[j] - 1].im * tauj_im - Y_re * tol) / wj_im;
        } else {
          tauj_im = tol / wj_re;
          tol = wj_re + tauj_im * tol;
          Y[jpvt[j] - 1].re = (tauj_im * Y[jpvt[j] - 1].re + Y[jpvt[j] - 1].im) /
            tol;
          Y[jpvt[j] - 1].im = (tauj_im * Y[jpvt[j] - 1].im - Y_re) / tol;
        }
      }

      for (i = 0; i + 1 <= j; i++) {
        Y_re = Y[jpvt[j] - 1].re * b_A->data[i + b_A->size[0] * j].re - Y[jpvt[j]
          - 1].im * b_A->data[i + b_A->size[0] * j].im;
        tol = Y[jpvt[j] - 1].re * b_A->data[i + b_A->size[0] * j].im + Y[jpvt[j]
          - 1].im * b_A->data[i + b_A->size[0] * j].re;
        Y[jpvt[i] - 1].re -= Y_re;
        Y[jpvt[i] - 1].im -= tol;
      }
    }

    emxFree_creal_T(&b_A);
  }
}

/*
 * Arguments    : const double A[4]
 *                const double B[4]
 *                double Y[4]
 * Return Type  : void
 */
void c_mldivide(const double A[4], const double B[4], double Y[4])
{
  int r1;
  int r2;
  double a21;
  double a22;
  int k;
  if (fabs(A[1]) > fabs(A[0])) {
    r1 = 1;
    r2 = 0;
  } else {
    r1 = 0;
    r2 = 1;
  }

  a21 = A[r2] / A[r1];
  a22 = A[2 + r2] - a21 * A[2 + r1];
  for (k = 0; k < 2; k++) {
    Y[1 + (k << 1)] = (B[r2 + (k << 1)] - B[r1 + (k << 1)] * a21) / a22;
    Y[k << 1] = (B[r1 + (k << 1)] - Y[1 + (k << 1)] * A[2 + r1]) / A[r1];
  }
}

/*
 * Arguments    : const emxArray_creal_T *A
 *                const emxArray_creal_T *B
 *                creal_T Y[2]
 * Return Type  : void
 */
void mldivide(const emxArray_creal_T *A, const emxArray_creal_T *B, creal_T Y[2])
{
  emxArray_creal_T *b_A;
  emxArray_creal_T *b_B;
  int i;
  int minmn;
  int maxmn;
  creal_T A_data[4];
  int jpvt[2];
  creal_T tau_data[2];
  int tau_size[1];
  int rankR;
  boolean_T c_A;
  double wj_re;
  double tol;
  int j;
  double wj_im;
  double tauj_im;
  double Y_re;
  emxInit_creal_T1(&b_A, 2);
  emxInit_creal_T(&b_B, 1);
  if ((A->size[0] == 0) || (B->size[0] == 0)) {
    for (i = 0; i < 2; i++) {
      Y[i].re = 0.0;
      Y[i].im = 0.0;
    }
  } else if (A->size[0] == 2) {
    maxmn = A->size[0] * A->size[1];
    for (minmn = 0; minmn < maxmn; minmn++) {
      A_data[minmn] = A->data[minmn];
    }

    for (minmn = 0; minmn < 2; minmn++) {
      jpvt[minmn] = 1 + minmn;
    }

    minmn = 0;
    if (fabs(A->data[1].re) + fabs(A->data[1].im) > fabs(A->data[0].re) + fabs
        (A->data[0].im)) {
      minmn = 1;
    }

    c_A = ((A->data[minmn].re != 0.0) || (A->data[minmn].im != 0.0));
    if (c_A) {
      if (minmn != 0) {
        jpvt[0] = 2;
        minmn = 0;
        maxmn = 1;
        for (j = 0; j < 2; j++) {
          tol = A_data[minmn].re;
          tauj_im = A_data[minmn].im;
          A_data[minmn] = A_data[maxmn];
          A_data[maxmn].re = tol;
          A_data[maxmn].im = tauj_im;
          minmn += 2;
          maxmn += 2;
        }
      }

      wj_re = A_data[1].re;
      if (A_data[0].im == 0.0) {
        if (A_data[1].im == 0.0) {
          A_data[1].re /= A_data[0].re;
          A_data[1].im = 0.0;
        } else if (A_data[1].re == 0.0) {
          A_data[1].re = 0.0;
          A_data[1].im /= A_data[0].re;
        } else {
          A_data[1].re /= A_data[0].re;
          A_data[1].im /= A_data[0].re;
        }
      } else if (A_data[0].re == 0.0) {
        if (A_data[1].re == 0.0) {
          A_data[1].re = A_data[1].im / A_data[0].im;
          A_data[1].im = 0.0;
        } else if (A_data[1].im == 0.0) {
          A_data[1].re = 0.0;
          A_data[1].im = -(wj_re / A_data[0].im);
        } else {
          A_data[1].re = A_data[1].im / A_data[0].im;
          A_data[1].im = -(wj_re / A_data[0].im);
        }
      } else {
        wj_im = fabs(A_data[0].re);
        tauj_im = fabs(A_data[0].im);
        if (wj_im > tauj_im) {
          tauj_im = A_data[0].im / A_data[0].re;
          tol = A_data[0].re + tauj_im * A_data[0].im;
          A_data[1].re = (A_data[1].re + tauj_im * A_data[1].im) / tol;
          A_data[1].im = (A_data[1].im - tauj_im * wj_re) / tol;
        } else if (tauj_im == wj_im) {
          if (A_data[0].re > 0.0) {
            tauj_im = 0.5;
          } else {
            tauj_im = -0.5;
          }

          if (A_data[0].im > 0.0) {
            tol = 0.5;
          } else {
            tol = -0.5;
          }

          A_data[1].re = (A_data[1].re * tauj_im + A_data[1].im * tol) / wj_im;
          A_data[1].im = (A_data[1].im * tauj_im - wj_re * tol) / wj_im;
        } else {
          tauj_im = A_data[0].re / A_data[0].im;
          tol = A_data[0].im + tauj_im * A_data[0].re;
          A_data[1].re = (tauj_im * A_data[1].re + A_data[1].im) / tol;
          A_data[1].im = (tauj_im * A_data[1].im - wj_re) / tol;
        }
      }
    }

    if ((A_data[2].re != 0.0) || (A_data[2].im != 0.0)) {
      wj_re = -A_data[2].re - A_data[2].im * 0.0;
      tol = A_data[2].re * 0.0 + -A_data[2].im;
      A_data[3].re += A_data[1].re * wj_re - A_data[1].im * tol;
      A_data[3].im += A_data[1].re * tol + A_data[1].im * wj_re;
    }

    for (minmn = 0; minmn < 2; minmn++) {
      Y[minmn] = B->data[minmn];
    }

    if (jpvt[0] != 1) {
      Y[0] = B->data[1];
      Y[1] = B->data[0];
    }

    for (j = 0; j < 2; j++) {
      minmn = j << 1;
      if ((Y[j].re != 0.0) || (Y[j].im != 0.0)) {
        i = j + 2;
        while (i < 3) {
          tol = Y[j].re * A_data[minmn + 1].im + Y[j].im * A_data[minmn + 1].re;
          Y[1].re -= Y[j].re * A_data[minmn + 1].re - Y[j].im * A_data[minmn + 1]
            .im;
          Y[1].im -= tol;
          i = 3;
        }
      }
    }

    for (j = 1; j >= 0; j += -1) {
      minmn = j << 1;
      if ((Y[j].re != 0.0) || (Y[j].im != 0.0)) {
        Y_re = Y[j].re;
        tol = A_data[j + minmn].re;
        wj_re = A_data[j + minmn].im;
        if (wj_re == 0.0) {
          if (Y[j].im == 0.0) {
            Y[j].re /= tol;
            Y[j].im = 0.0;
          } else if (Y[j].re == 0.0) {
            Y[j].re = 0.0;
            Y[j].im /= tol;
          } else {
            Y[j].re /= tol;
            Y[j].im /= tol;
          }
        } else if (tol == 0.0) {
          if (Y[j].re == 0.0) {
            Y[j].re = Y[j].im / wj_re;
            Y[j].im = 0.0;
          } else if (Y[j].im == 0.0) {
            Y[j].re = 0.0;
            Y[j].im = -(Y_re / wj_re);
          } else {
            Y[j].re = Y[j].im / wj_re;
            Y[j].im = -(Y_re / wj_re);
          }
        } else {
          wj_im = fabs(tol);
          tauj_im = fabs(wj_re);
          if (wj_im > tauj_im) {
            tauj_im = wj_re / tol;
            tol += tauj_im * wj_re;
            Y[j].re = (Y[j].re + tauj_im * Y[j].im) / tol;
            Y[j].im = (Y[j].im - tauj_im * Y_re) / tol;
          } else if (tauj_im == wj_im) {
            if (tol > 0.0) {
              tauj_im = 0.5;
            } else {
              tauj_im = -0.5;
            }

            if (wj_re > 0.0) {
              tol = 0.5;
            } else {
              tol = -0.5;
            }

            Y[j].re = (Y[j].re * tauj_im + Y[j].im * tol) / wj_im;
            Y[j].im = (Y[j].im * tauj_im - Y_re * tol) / wj_im;
          } else {
            tauj_im = tol / wj_re;
            tol = wj_re + tauj_im * tol;
            Y[j].re = (tauj_im * Y[j].re + Y[j].im) / tol;
            Y[j].im = (tauj_im * Y[j].im - Y_re) / tol;
          }
        }

        i = 1;
        while (i <= j) {
          tol = Y[1].re * A_data[minmn].im + Y[1].im * A_data[minmn].re;
          Y[0].re -= Y[1].re * A_data[minmn].re - Y[1].im * A_data[minmn].im;
          Y[0].im -= tol;
          i = 2;
        }
      }
    }
  } else {
    minmn = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)b_A, minmn, sizeof(creal_T));
    maxmn = A->size[0] * A->size[1];
    for (minmn = 0; minmn < maxmn; minmn++) {
      b_A->data[minmn] = A->data[minmn];
    }

    xgeqp3(b_A, tau_data, tau_size, jpvt);
    rankR = 0;
    if (b_A->size[0] < 2) {
      minmn = b_A->size[0];
      maxmn = 2;
    } else {
      minmn = 2;
      maxmn = b_A->size[0];
    }

    if (minmn > 0) {
      tol = (double)maxmn * (fabs(b_A->data[0].re) + fabs(b_A->data[0].im)) *
        2.2204460492503131E-16;
      while ((rankR < minmn) && (fabs(b_A->data[rankR + b_A->size[0] * rankR].re)
              + fabs(b_A->data[rankR + b_A->size[0] * rankR].im) >= tol)) {
        rankR++;
      }
    }

    minmn = b_B->size[0];
    b_B->size[0] = B->size[0];
    emxEnsureCapacity((emxArray__common *)b_B, minmn, sizeof(creal_T));
    maxmn = B->size[0];
    for (minmn = 0; minmn < maxmn; minmn++) {
      b_B->data[minmn] = B->data[minmn];
    }

    for (i = 0; i < 2; i++) {
      Y[i].re = 0.0;
      Y[i].im = 0.0;
    }

    minmn = b_A->size[0];
    maxmn = b_A->size[0];
    if (!(maxmn < 2)) {
      maxmn = 2;
    }

    for (j = 0; j + 1 <= maxmn; j++) {
      if ((tau_data[j].re != 0.0) || (-tau_data[j].im != 0.0)) {
        wj_re = b_B->data[j].re;
        wj_im = b_B->data[j].im;
        for (i = j + 1; i + 1 <= minmn; i++) {
          wj_re += b_A->data[i + b_A->size[0] * j].re * b_B->data[i].re +
            b_A->data[i + b_A->size[0] * j].im * b_B->data[i].im;
          wj_im += b_A->data[i + b_A->size[0] * j].re * b_B->data[i].im -
            b_A->data[i + b_A->size[0] * j].im * b_B->data[i].re;
        }

        tol = wj_re;
        wj_re = tau_data[j].re * wj_re - -tau_data[j].im * wj_im;
        wj_im = tau_data[j].re * wj_im + -tau_data[j].im * tol;
        if ((wj_re != 0.0) || (wj_im != 0.0)) {
          b_B->data[j].re -= wj_re;
          b_B->data[j].im -= wj_im;
          for (i = j + 1; i + 1 <= minmn; i++) {
            tol = b_A->data[i + b_A->size[0] * j].re * wj_re - b_A->data[i +
              b_A->size[0] * j].im * wj_im;
            tauj_im = b_A->data[i + b_A->size[0] * j].re * wj_im + b_A->data[i +
              b_A->size[0] * j].im * wj_re;
            b_B->data[i].re -= tol;
            b_B->data[i].im -= tauj_im;
          }
        }
      }
    }

    for (i = 0; i + 1 <= rankR; i++) {
      Y[jpvt[i] - 1] = b_B->data[i];
    }

    for (j = rankR - 1; j + 1 > 0; j--) {
      Y_re = Y[jpvt[j] - 1].re;
      tol = b_A->data[j + b_A->size[0] * j].re;
      wj_re = b_A->data[j + b_A->size[0] * j].im;
      if (wj_re == 0.0) {
        if (Y[jpvt[j] - 1].im == 0.0) {
          Y[jpvt[j] - 1].re /= tol;
          Y[jpvt[j] - 1].im = 0.0;
        } else if (Y[jpvt[j] - 1].re == 0.0) {
          Y[jpvt[j] - 1].re = 0.0;
          Y[jpvt[j] - 1].im /= tol;
        } else {
          Y[jpvt[j] - 1].re /= tol;
          Y[jpvt[j] - 1].im /= tol;
        }
      } else if (tol == 0.0) {
        if (Y[jpvt[j] - 1].re == 0.0) {
          Y[jpvt[j] - 1].re = Y[jpvt[j] - 1].im / wj_re;
          Y[jpvt[j] - 1].im = 0.0;
        } else if (Y[jpvt[j] - 1].im == 0.0) {
          Y[jpvt[j] - 1].re = 0.0;
          Y[jpvt[j] - 1].im = -(Y_re / wj_re);
        } else {
          Y[jpvt[j] - 1].re = Y[jpvt[j] - 1].im / wj_re;
          Y[jpvt[j] - 1].im = -(Y_re / wj_re);
        }
      } else {
        wj_im = fabs(tol);
        tauj_im = fabs(wj_re);
        if (wj_im > tauj_im) {
          tauj_im = wj_re / tol;
          tol += tauj_im * wj_re;
          Y[jpvt[j] - 1].re = (Y[jpvt[j] - 1].re + tauj_im * Y[jpvt[j] - 1].im) /
            tol;
          Y[jpvt[j] - 1].im = (Y[jpvt[j] - 1].im - tauj_im * Y_re) / tol;
        } else if (tauj_im == wj_im) {
          if (tol > 0.0) {
            tauj_im = 0.5;
          } else {
            tauj_im = -0.5;
          }

          if (wj_re > 0.0) {
            tol = 0.5;
          } else {
            tol = -0.5;
          }

          Y[jpvt[j] - 1].re = (Y[jpvt[j] - 1].re * tauj_im + Y[jpvt[j] - 1].im *
                               tol) / wj_im;
          Y[jpvt[j] - 1].im = (Y[jpvt[j] - 1].im * tauj_im - Y_re * tol) / wj_im;
        } else {
          tauj_im = tol / wj_re;
          tol = wj_re + tauj_im * tol;
          Y[jpvt[j] - 1].re = (tauj_im * Y[jpvt[j] - 1].re + Y[jpvt[j] - 1].im) /
            tol;
          Y[jpvt[j] - 1].im = (tauj_im * Y[jpvt[j] - 1].im - Y_re) / tol;
        }
      }

      i = 1;
      while (i <= j) {
        Y_re = Y[jpvt[j] - 1].re * b_A->data[b_A->size[0] * j].re - Y[jpvt[j] -
          1].im * b_A->data[b_A->size[0] * j].im;
        tol = Y[jpvt[j] - 1].re * b_A->data[b_A->size[0] * j].im + Y[jpvt[j] - 1]
          .im * b_A->data[b_A->size[0] * j].re;
        Y[jpvt[0] - 1].re -= Y_re;
        Y[jpvt[0] - 1].im -= tol;
        i = 2;
      }
    }
  }

  emxFree_creal_T(&b_B);
  emxFree_creal_T(&b_A);
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */
