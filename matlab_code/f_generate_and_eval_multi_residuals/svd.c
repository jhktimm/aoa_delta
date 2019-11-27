/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: svd.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "svd.h"
#include "xrot.h"
#include "xrotg.h"
#include "sqrt.h"
#include "xswap.h"
#include "xscal.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"

/* Function Definitions */

/*
 * Arguments    : const double A[20]
 *                double U[16]
 *                double s[4]
 *                double V[25]
 * Return Type  : void
 */
void svd(const double A[20], double U[16], double s[4], double V[25])
{
  double b_A[20];
  int i;
  double b_s[5];
  double e[5];
  double work[4];
  int q;
  int m;
  int qq;
  boolean_T apply_transform;
  double nrm;
  int qp1jj;
  int qs;
  double snorm;
  double rt;
  double r;
  int exitg1;
  boolean_T exitg2;
  double f;
  double varargin_1[5];
  double mtmp;
  double sqds;
  memcpy(&b_A[0], &A[0], 20U * sizeof(double));
  for (i = 0; i < 5; i++) {
    b_s[i] = 0.0;
    e[i] = 0.0;
  }

  for (i = 0; i < 4; i++) {
    work[i] = 0.0;
  }

  memset(&U[0], 0, sizeof(double) << 4);
  memset(&V[0], 0, 25U * sizeof(double));
  for (q = 0; q < 3; q++) {
    qq = q + (q << 2);
    apply_transform = false;
    nrm = c_xnrm2(4 - q, b_A, qq + 1);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq] < 0.0) {
        b_s[q] = -nrm;
      } else {
        b_s[q] = nrm;
      }

      if (fabs(b_s[q]) >= 1.0020841800044864E-292) {
        nrm = 1.0 / b_s[q];
        i = (qq - q) + 4;
        for (qp1jj = qq; qp1jj + 1 <= i; qp1jj++) {
          b_A[qp1jj] *= nrm;
        }
      } else {
        i = (qq - q) + 4;
        for (qp1jj = qq; qp1jj + 1 <= i; qp1jj++) {
          b_A[qp1jj] /= b_s[q];
        }
      }

      b_A[qq]++;
      b_s[q] = -b_s[q];
    } else {
      b_s[q] = 0.0;
    }

    for (qs = q + 1; qs + 1 < 6; qs++) {
      i = q + (qs << 2);
      if (apply_transform) {
        xaxpy(4 - q, -(xdotc(4 - q, b_A, qq + 1, b_A, i + 1) / b_A[q + (q << 2)]),
              qq + 1, b_A, i + 1);
      }

      e[qs] = b_A[i];
    }

    for (qp1jj = q; qp1jj + 1 < 5; qp1jj++) {
      U[qp1jj + (q << 2)] = b_A[qp1jj + (q << 2)];
    }

    nrm = d_xnrm2(4 - q, e, q + 2);
    if (nrm == 0.0) {
      e[q] = 0.0;
    } else {
      if (e[q + 1] < 0.0) {
        e[q] = -nrm;
      } else {
        e[q] = nrm;
      }

      nrm = e[q];
      if (fabs(e[q]) >= 1.0020841800044864E-292) {
        nrm = 1.0 / e[q];
        for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
          e[qp1jj] *= nrm;
        }
      } else {
        for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
          e[qp1jj] /= nrm;
        }
      }

      e[q + 1]++;
      e[q] = -e[q];
      for (qp1jj = q + 1; qp1jj + 1 < 5; qp1jj++) {
        work[qp1jj] = 0.0;
      }

      for (qs = q + 1; qs + 1 < 6; qs++) {
        b_xaxpy(3 - q, e[qs], b_A, (q + (qs << 2)) + 2, work, q + 2);
      }

      for (qs = q + 1; qs + 1 < 6; qs++) {
        c_xaxpy(3 - q, -e[qs] / e[q + 1], work, q + 2, b_A, (q + (qs << 2)) + 2);
      }
    }

    for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
      V[qp1jj + 5 * q] = e[qp1jj];
    }
  }

  m = 3;
  b_s[3] = b_A[15];
  b_s[4] = 0.0;
  e[3] = b_A[19];
  e[4] = 0.0;
  for (qp1jj = 0; qp1jj < 4; qp1jj++) {
    U[12 + qp1jj] = 0.0;
  }

  U[15] = 1.0;
  for (q = 2; q >= 0; q--) {
    qq = q + (q << 2);
    if (b_s[q] != 0.0) {
      for (qs = q + 1; qs + 1 < 5; qs++) {
        i = (q + (qs << 2)) + 1;
        d_xaxpy(4 - q, -(b_xdotc(4 - q, U, qq + 1, U, i) / U[qq]), qq + 1, U, i);
      }

      for (qp1jj = q; qp1jj + 1 < 5; qp1jj++) {
        U[qp1jj + (q << 2)] = -U[qp1jj + (q << 2)];
      }

      U[qq]++;
      for (qp1jj = 1; qp1jj <= q; qp1jj++) {
        U[(qp1jj + (q << 2)) - 1] = 0.0;
      }
    } else {
      for (qp1jj = 0; qp1jj < 4; qp1jj++) {
        U[qp1jj + (q << 2)] = 0.0;
      }

      U[qq] = 1.0;
    }
  }

  for (q = 4; q >= 0; q--) {
    if ((q + 1 <= 3) && (e[q] != 0.0)) {
      i = (q + 5 * q) + 2;
      for (qs = q + 1; qs + 1 < 6; qs++) {
        qp1jj = (q + 5 * qs) + 2;
        e_xaxpy(4 - q, -(c_xdotc(4 - q, V, i, V, qp1jj) / V[i - 1]), i, V, qp1jj);
      }
    }

    for (qp1jj = 0; qp1jj < 5; qp1jj++) {
      V[qp1jj + 5 * q] = 0.0;
    }

    V[q + 5 * q] = 1.0;
  }

  for (q = 0; q < 5; q++) {
    nrm = e[q];
    if (b_s[q] != 0.0) {
      rt = fabs(b_s[q]);
      r = b_s[q] / rt;
      b_s[q] = rt;
      if (q + 1 < 5) {
        nrm = e[q] / r;
      }

      if (q + 1 <= 4) {
        xscal(r, U, 1 + (q << 2));
      }
    }

    if ((q + 1 < 5) && (nrm != 0.0)) {
      rt = fabs(nrm);
      r = rt / nrm;
      nrm = rt;
      b_s[q + 1] *= r;
      b_xscal(r, V, 1 + 5 * (q + 1));
    }

    e[q] = nrm;
  }

  qq = 0;
  snorm = 0.0;
  for (qp1jj = 0; qp1jj < 5; qp1jj++) {
    nrm = fabs(b_s[qp1jj]);
    r = fabs(e[qp1jj]);
    if ((nrm > r) || rtIsNaN(r)) {
    } else {
      nrm = r;
    }

    if (!((snorm > nrm) || rtIsNaN(nrm))) {
      snorm = nrm;
    }
  }

  while ((m + 2 > 0) && (!(qq >= 75))) {
    qp1jj = m;
    do {
      exitg1 = 0;
      q = qp1jj + 1;
      if (qp1jj + 1 == 0) {
        exitg1 = 1;
      } else {
        nrm = fabs(e[qp1jj]);
        if ((nrm <= 2.2204460492503131E-16 * (fabs(b_s[qp1jj]) + fabs(b_s[qp1jj
               + 1]))) || (nrm <= 1.0020841800044864E-292) || ((qq > 20) && (nrm
              <= 2.2204460492503131E-16 * snorm))) {
          e[qp1jj] = 0.0;
          exitg1 = 1;
        } else {
          qp1jj--;
        }
      }
    } while (exitg1 == 0);

    if (qp1jj + 1 == m + 1) {
      i = 4;
    } else {
      qs = m + 2;
      i = m + 2;
      exitg2 = false;
      while ((!exitg2) && (i >= qp1jj + 1)) {
        qs = i;
        if (i == qp1jj + 1) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (i < m + 2) {
            nrm = fabs(e[i - 1]);
          }

          if (i > qp1jj + 2) {
            nrm += fabs(e[i - 2]);
          }

          r = fabs(b_s[i - 1]);
          if ((r <= 2.2204460492503131E-16 * nrm) || (r <=
               1.0020841800044864E-292)) {
            b_s[i - 1] = 0.0;
            exitg2 = true;
          } else {
            i--;
          }
        }
      }

      if (qs == qp1jj + 1) {
        i = 3;
      } else if (qs == m + 2) {
        i = 1;
      } else {
        i = 2;
        q = qs;
      }
    }

    switch (i) {
     case 1:
      f = e[m];
      e[m] = 0.0;
      for (qp1jj = m; qp1jj + 1 >= q + 1; qp1jj--) {
        xrotg(&b_s[qp1jj], &f, &nrm, &r);
        if (qp1jj + 1 > q + 1) {
          f = -r * e[qp1jj - 1];
          e[qp1jj - 1] *= nrm;
        }

        xrot(V, 1 + 5 * qp1jj, 1 + 5 * (m + 1), nrm, r);
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      for (qp1jj = q; qp1jj + 1 <= m + 2; qp1jj++) {
        xrotg(&b_s[qp1jj], &f, &nrm, &r);
        f = -r * e[qp1jj];
        e[qp1jj] *= nrm;
        b_xrot(U, 1 + (qp1jj << 2), 1 + ((q - 1) << 2), nrm, r);
      }
      break;

     case 3:
      varargin_1[0] = fabs(b_s[m + 1]);
      varargin_1[1] = fabs(b_s[m]);
      varargin_1[2] = fabs(e[m]);
      varargin_1[3] = fabs(b_s[q]);
      varargin_1[4] = fabs(e[q]);
      i = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        qp1jj = 2;
        exitg2 = false;
        while ((!exitg2) && (qp1jj < 6)) {
          i = qp1jj;
          if (!rtIsNaN(varargin_1[qp1jj - 1])) {
            mtmp = varargin_1[qp1jj - 1];
            exitg2 = true;
          } else {
            qp1jj++;
          }
        }
      }

      if (i < 5) {
        while (i + 1 < 6) {
          if (varargin_1[i] > mtmp) {
            mtmp = varargin_1[i];
          }

          i++;
        }
      }

      f = b_s[m + 1] / mtmp;
      nrm = b_s[m] / mtmp;
      r = e[m] / mtmp;
      sqds = b_s[q] / mtmp;
      rt = ((nrm + f) * (nrm - f) + r * r) / 2.0;
      nrm = f * r;
      nrm *= nrm;
      if ((rt != 0.0) || (nrm != 0.0)) {
        r = rt * rt + nrm;
        b_sqrt(&r);
        if (rt < 0.0) {
          r = -r;
        }

        r = nrm / (rt + r);
      } else {
        r = 0.0;
      }

      f = (sqds + f) * (sqds - f) + r;
      rt = sqds * (e[q] / mtmp);
      for (qp1jj = q + 1; qp1jj <= m + 1; qp1jj++) {
        xrotg(&f, &rt, &nrm, &r);
        if (qp1jj > q + 1) {
          e[qp1jj - 2] = f;
        }

        f = nrm * b_s[qp1jj - 1] + r * e[qp1jj - 1];
        e[qp1jj - 1] = nrm * e[qp1jj - 1] - r * b_s[qp1jj - 1];
        rt = r * b_s[qp1jj];
        b_s[qp1jj] *= nrm;
        xrot(V, 1 + 5 * (qp1jj - 1), 1 + 5 * qp1jj, nrm, r);
        b_s[qp1jj - 1] = f;
        xrotg(&b_s[qp1jj - 1], &rt, &nrm, &r);
        f = nrm * e[qp1jj - 1] + r * b_s[qp1jj];
        b_s[qp1jj] = -r * e[qp1jj - 1] + nrm * b_s[qp1jj];
        rt = r * e[qp1jj];
        e[qp1jj] *= nrm;
        if (qp1jj < 4) {
          b_xrot(U, 1 + ((qp1jj - 1) << 2), 1 + (qp1jj << 2), nrm, r);
        }
      }

      e[m] = f;
      qq++;
      break;

     default:
      if (b_s[q] < 0.0) {
        b_s[q] = -b_s[q];
        b_xscal(-1.0, V, 1 + 5 * q);
      }

      i = q + 1;
      while ((q + 1 < 5) && (b_s[q] < b_s[i])) {
        rt = b_s[q];
        b_s[q] = b_s[i];
        b_s[i] = rt;
        xswap(V, 1 + 5 * q, 1 + 5 * (q + 1));
        if (q + 1 < 4) {
          b_xswap(U, 1 + (q << 2), 1 + ((q + 1) << 2));
        }

        q = i;
        i++;
      }

      qq = 0;
      m--;
      break;
    }
  }

  for (qp1jj = 0; qp1jj < 4; qp1jj++) {
    s[qp1jj] = b_s[qp1jj];
  }
}

/*
 * File trailer for svd.c
 *
 * [EOF]
 */
