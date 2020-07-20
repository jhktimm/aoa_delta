/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * svd.c
 *
 * Code generation for function 'svd'
 *
 */

/* Include files */
#include "svd.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "rt_nonfinite.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void svd(const double A[20], double U[16], double s[4], double V[25])
{
  double b_A[20];
  int i;
  double work[4];
  double b_s[5];
  double e[5];
  int q;
  int m;
  int qp1;
  int iter;
  int qq;
  boolean_T apply_transform;
  double nrm;
  int k;
  int qp1jj;
  double snorm;
  double r;
  int exitg1;
  boolean_T exitg2;
  double scale;
  double sm;
  double sqds;
  double b;
  memcpy(&b_A[0], &A[0], 20U * sizeof(double));
  for (i = 0; i < 5; i++) {
    b_s[i] = 0.0;
    e[i] = 0.0;
  }

  work[0] = 0.0;
  work[1] = 0.0;
  work[2] = 0.0;
  work[3] = 0.0;
  memset(&U[0], 0, 16U * sizeof(double));
  memset(&V[0], 0, 25U * sizeof(double));
  for (q = 0; q < 3; q++) {
    qp1 = q + 2;
    iter = q << 2;
    qq = (q + iter) + 1;
    apply_transform = false;
    nrm = xnrm2(4 - q, b_A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0) {
        nrm = -nrm;
      }

      b_s[q] = nrm;
      if (fabs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qp1jj = (qq - q) + 3;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qp1jj = (qq - q) + 3;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] /= b_s[q];
        }
      }

      b_A[qq - 1]++;
      b_s[q] = -b_s[q];
    } else {
      b_s[q] = 0.0;
    }

    for (k = qp1; k < 6; k++) {
      i = q + ((k - 1) << 2);
      if (apply_transform) {
        xaxpy(4 - q, -(xdotc(4 - q, b_A, qq, b_A, i + 1) / b_A[q + (q << 2)]),
              qq, b_A, i + 1);
      }

      e[k - 1] = b_A[i];
    }

    for (k = q + 1; k < 5; k++) {
      i = (k + iter) - 1;
      U[i] = b_A[i];
    }

    nrm = b_xnrm2(4 - q, e, q + 2);
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
        for (k = qp1; k < 6; k++) {
          e[k - 1] *= nrm;
        }
      } else {
        for (k = qp1; k < 6; k++) {
          e[k - 1] /= nrm;
        }
      }

      e[q + 1]++;
      e[q] = -e[q];
      for (k = qp1; k < 5; k++) {
        work[k - 1] = 0.0;
      }

      for (k = qp1; k < 6; k++) {
        b_xaxpy(3 - q, e[k - 1], b_A, (q + ((k - 1) << 2)) + 2, work, q + 2);
      }

      for (k = qp1; k < 6; k++) {
        c_xaxpy(3 - q, -e[k - 1] / e[q + 1], work, q + 2, b_A, (q + ((k - 1) <<
                  2)) + 2);
      }
    }

    for (k = qp1; k < 6; k++) {
      V[(k + 5 * q) - 1] = e[k - 1];
    }
  }

  m = 3;
  b_s[3] = b_A[15];
  b_s[4] = 0.0;
  e[3] = b_A[19];
  e[4] = 0.0;
  U[12] = 0.0;
  U[13] = 0.0;
  U[14] = 0.0;
  U[15] = 1.0;
  for (q = 2; q >= 0; q--) {
    qp1 = q + 2;
    iter = q << 2;
    qq = q + iter;
    if (b_s[q] != 0.0) {
      for (k = qp1; k < 5; k++) {
        i = (q + ((k - 1) << 2)) + 1;
        d_xaxpy(4 - q, -(b_xdotc(4 - q, U, qq + 1, U, i) / U[qq]), qq + 1, U, i);
      }

      for (k = q + 1; k < 5; k++) {
        i = (k + iter) - 1;
        U[i] = -U[i];
      }

      U[qq]++;
      for (k = 0; k < q; k++) {
        U[k + iter] = 0.0;
      }
    } else {
      U[iter] = 0.0;
      U[iter + 1] = 0.0;
      U[iter + 2] = 0.0;
      U[iter + 3] = 0.0;
      U[qq] = 1.0;
    }
  }

  for (q = 4; q >= 0; q--) {
    if ((q + 1 <= 3) && (e[q] != 0.0)) {
      qp1 = q + 2;
      i = (q + 5 * q) + 2;
      for (k = qp1; k < 6; k++) {
        qp1jj = (q + 5 * (k - 1)) + 2;
        e_xaxpy(4 - q, -(c_xdotc(4 - q, V, i, V, qp1jj) / V[i - 1]), i, V, qp1jj);
      }
    }

    for (k = 0; k < 5; k++) {
      V[k + 5 * q] = 0.0;
    }

    V[q + 5 * q] = 1.0;
  }

  iter = 0;
  snorm = 0.0;
  for (q = 0; q < 5; q++) {
    if (b_s[q] != 0.0) {
      nrm = fabs(b_s[q]);
      r = b_s[q] / nrm;
      b_s[q] = nrm;
      if (q + 1 < 5) {
        e[q] /= r;
      }

      if (q + 1 <= 4) {
        i = q << 2;
        qp1jj = i + 4;
        for (k = i + 1; k <= qp1jj; k++) {
          U[k - 1] *= r;
        }
      }
    }

    if ((q + 1 < 5) && (e[q] != 0.0)) {
      nrm = fabs(e[q]);
      r = nrm / e[q];
      e[q] = nrm;
      b_s[q + 1] *= r;
      i = 5 * (q + 1);
      qp1jj = i + 5;
      for (k = i + 1; k <= qp1jj; k++) {
        V[k - 1] *= r;
      }
    }

    nrm = fabs(b_s[q]);
    r = fabs(e[q]);
    if ((nrm > r) || rtIsNaN(r)) {
      r = nrm;
    }

    if ((!(snorm > r)) && (!rtIsNaN(r))) {
      snorm = r;
    }
  }

  while ((m + 2 > 0) && (iter < 75)) {
    k = m;
    do {
      exitg1 = 0;
      q = k + 1;
      if (k + 1 == 0) {
        exitg1 = 1;
      } else {
        nrm = fabs(e[k]);
        if ((nrm <= 2.2204460492503131E-16 * (fabs(b_s[k]) + fabs(b_s[k + 1]))) ||
            (nrm <= 1.0020841800044864E-292) || ((iter > 20) && (nrm <=
              2.2204460492503131E-16 * snorm))) {
          e[k] = 0.0;
          exitg1 = 1;
        } else {
          k--;
        }
      }
    } while (exitg1 == 0);

    if (k + 1 == m + 1) {
      i = 4;
    } else {
      qp1jj = m + 2;
      i = m + 2;
      exitg2 = false;
      while ((!exitg2) && (i >= k + 1)) {
        qp1jj = i;
        if (i == k + 1) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (i < m + 2) {
            nrm = fabs(e[i - 1]);
          }

          if (i > k + 2) {
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

      if (qp1jj == k + 1) {
        i = 3;
      } else if (qp1jj == m + 2) {
        i = 1;
      } else {
        i = 2;
        q = qp1jj;
      }
    }

    switch (i) {
     case 1:
      r = e[m];
      e[m] = 0.0;
      qp1jj = m + 1;
      for (k = qp1jj; k >= q + 1; k--) {
        xrotg(&b_s[k - 1], &r, &sm, &sqds);
        if (k > q + 1) {
          b = e[k - 2];
          r = -sqds * b;
          e[k - 2] = b * sm;
        }

        xrot(V, 5 * (k - 1) + 1, 5 * (m + 1) + 1, sm, sqds);
      }
      break;

     case 2:
      r = e[q - 1];
      e[q - 1] = 0.0;
      for (k = q + 1; k <= m + 2; k++) {
        xrotg(&b_s[k - 1], &r, &sm, &sqds);
        b = e[k - 1];
        r = -sqds * b;
        e[k - 1] = b * sm;
        b_xrot(U, ((k - 1) << 2) + 1, ((q - 1) << 2) + 1, sm, sqds);
      }
      break;

     case 3:
      i = m + 1;
      nrm = b_s[m + 1];
      scale = fabs(nrm);
      r = fabs(b_s[m]);
      if ((!(scale > r)) && (!rtIsNaN(r))) {
        scale = r;
      }

      r = fabs(e[m]);
      if ((!(scale > r)) && (!rtIsNaN(r))) {
        scale = r;
      }

      r = fabs(b_s[q]);
      if ((!(scale > r)) && (!rtIsNaN(r))) {
        scale = r;
      }

      r = fabs(e[q]);
      if ((!(scale > r)) && (!rtIsNaN(r))) {
        scale = r;
      }

      sm = nrm / scale;
      nrm = b_s[m] / scale;
      r = e[m] / scale;
      sqds = b_s[q] / scale;
      b = ((nrm + sm) * (nrm - sm) + r * r) / 2.0;
      nrm = sm * r;
      nrm *= nrm;
      if ((b != 0.0) || (nrm != 0.0)) {
        r = sqrt(b * b + nrm);
        if (b < 0.0) {
          r = -r;
        }

        r = nrm / (b + r);
      } else {
        r = 0.0;
      }

      r += (sqds + sm) * (sqds - sm);
      nrm = sqds * (e[q] / scale);
      for (k = q + 1; k <= i; k++) {
        xrotg(&r, &nrm, &sm, &sqds);
        if (k > q + 1) {
          e[k - 2] = r;
        }

        nrm = e[k - 1];
        b = b_s[k - 1];
        e[k - 1] = sm * nrm - sqds * b;
        r = sqds * b_s[k];
        b_s[k] *= sm;
        xrot(V, 5 * (k - 1) + 1, 5 * k + 1, sm, sqds);
        b_s[k - 1] = sm * b + sqds * nrm;
        xrotg(&b_s[k - 1], &r, &sm, &sqds);
        r = sm * e[k - 1] + sqds * b_s[k];
        b_s[k] = -sqds * e[k - 1] + sm * b_s[k];
        nrm = sqds * e[k];
        e[k] *= sm;
        if (k < 4) {
          b_xrot(U, ((k - 1) << 2) + 1, (k << 2) + 1, sm, sqds);
        }
      }

      e[m] = r;
      iter++;
      break;

     default:
      if (b_s[q] < 0.0) {
        b_s[q] = -b_s[q];
        i = 5 * q;
        qp1jj = i + 5;
        for (k = i + 1; k <= qp1jj; k++) {
          V[k - 1] = -V[k - 1];
        }
      }

      qp1 = q + 1;
      while ((q + 1 < 5) && (b_s[q] < b_s[qp1])) {
        nrm = b_s[q];
        b_s[q] = b_s[qp1];
        b_s[qp1] = nrm;
        xswap(V, 5 * q + 1, 5 * (q + 1) + 1);
        if (q + 1 < 4) {
          b_xswap(U, (q << 2) + 1, ((q + 1) << 2) + 1);
        }

        q = qp1;
        qp1++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  s[0] = b_s[0];
  s[1] = b_s[1];
  s[2] = b_s[2];
  s[3] = b_s[3];
}

/* End of code generation (svd.c) */
