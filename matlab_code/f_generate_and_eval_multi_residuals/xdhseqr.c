/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdhseqr.c
 *
 * Code generation for function 'xdhseqr'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "xdhseqr.h"
#include "xdlanv2.h"
#include "xzlarfg.h"

/* Function Definitions */
int eml_dlahqr(double h[36])
{
  int info;
  int j;
  int i;
  boolean_T exitg1;
  int L;
  boolean_T goto150;
  int its;
  boolean_T exitg2;
  int k;
  boolean_T exitg3;
  double tst;
  double htmp1;
  double aa;
  double ab;
  double ba;
  double rt2r;
  double rt1r;
  double s;
  double sn;
  int nr;
  int hoffset;
  int m;
  double d11;
  int b_k;
  double v[3];
  info = 0;
  for (j = 0; j < 3; j++) {
    h[(j + 6 * j) + 2] = 0.0;
    h[(j + 6 * j) + 3] = 0.0;
  }

  h[23] = 0.0;
  i = 5;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = 1;
    goto150 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 31)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && ((k + 1 > L) && (!(fabs(h[k + 6 * (k - 1)]) <=
                6.0125050800269183E-292)))) {
        tst = fabs(h[(k + 6 * (k - 1)) - 1]) + fabs(h[k + 6 * k]);
        if (tst == 0.0) {
          if (k - 1 >= 1) {
            tst = fabs(h[(k + 6 * (k - 2)) - 1]);
          }

          if (k + 2 <= 6) {
            tst += fabs(h[(k + 6 * k) + 1]);
          }
        }

        if (fabs(h[k + 6 * (k - 1)]) <= 2.2204460492503131E-16 * tst) {
          htmp1 = fabs(h[k + 6 * (k - 1)]);
          tst = fabs(h[(k + 6 * k) - 1]);
          if (htmp1 > tst) {
            ab = htmp1;
            ba = tst;
          } else {
            ab = tst;
            ba = htmp1;
          }

          htmp1 = fabs(h[k + 6 * k]);
          tst = fabs(h[(k + 6 * (k - 1)) - 1] - h[k + 6 * k]);
          if (htmp1 > tst) {
            aa = htmp1;
            htmp1 = tst;
          } else {
            aa = tst;
          }

          s = aa + ab;
          tst = 2.2204460492503131E-16 * (htmp1 * (aa / s));
          if ((6.0125050800269183E-292 > tst) || rtIsNaN(tst)) {
            d11 = 6.0125050800269183E-292;
          } else {
            d11 = tst;
          }

          if (ba * (ab / s) <= d11) {
            exitg3 = true;
          } else {
            k--;
          }
        } else {
          k--;
        }
      }

      L = k + 1;
      if (k + 1 > 1) {
        h[k + 6 * (k - 1)] = 0.0;
      }

      if (k + 1 >= i) {
        goto150 = true;
        exitg2 = true;
      } else {
        if (its == 10) {
          s = fabs(h[(k + 6 * k) + 1]) + fabs(h[(k + 6 * (k + 1)) + 2]);
          tst = 0.75 * s + h[k + 6 * k];
          aa = -0.4375 * s;
          htmp1 = s;
          ba = tst;
        } else if (its == 20) {
          s = fabs(h[i + 6 * (i - 1)]) + fabs(h[(i + 6 * (i - 2)) - 1]);
          tst = 0.75 * s + h[i + 6 * i];
          aa = -0.4375 * s;
          htmp1 = s;
          ba = tst;
        } else {
          tst = h[(i + 6 * (i - 1)) - 1];
          htmp1 = h[i + 6 * (i - 1)];
          aa = h[(i + 6 * i) - 1];
          ba = h[i + 6 * i];
        }

        s = ((fabs(tst) + fabs(aa)) + fabs(htmp1)) + fabs(ba);
        if (s == 0.0) {
          rt1r = 0.0;
          ab = 0.0;
          rt2r = 0.0;
          ba = 0.0;
        } else {
          tst /= s;
          htmp1 /= s;
          aa /= s;
          ba /= s;
          ab = (tst + ba) / 2.0;
          tst = (tst - ab) * (ba - ab) - aa * htmp1;
          htmp1 = sqrt(fabs(tst));
          if (tst >= 0.0) {
            rt1r = ab * s;
            rt2r = rt1r;
            ab = htmp1 * s;
            ba = -ab;
          } else {
            rt1r = ab + htmp1;
            rt2r = ab - htmp1;
            if (fabs(rt1r - ba) <= fabs(rt2r - ba)) {
              rt1r *= s;
              rt2r = rt1r;
            } else {
              rt2r *= s;
              rt1r = rt2r;
            }

            ab = 0.0;
            ba = 0.0;
          }
        }

        m = i - 2;
        exitg3 = false;
        while ((!exitg3) && (m + 1 >= k + 1)) {
          s = (fabs(h[m + 6 * m] - rt2r) + fabs(ba)) + fabs(h[(m + 6 * m) + 1]);
          tst = h[(m + 6 * m) + 1] / s;
          v[0] = (tst * h[m + 6 * (m + 1)] + (h[m + 6 * m] - rt1r) * ((h[m + 6 *
                    m] - rt2r) / s)) - ab * (ba / s);
          v[1] = tst * (((h[m + 6 * m] + h[(m + 6 * (m + 1)) + 1]) - rt1r) -
                        rt2r);
          v[2] = tst * h[(m + 6 * (m + 1)) + 2];
          s = (fabs(v[0]) + fabs(v[1])) + fabs(v[2]);
          tst = v[0] / s;
          v[0] /= s;
          htmp1 = v[1] / s;
          v[1] /= s;
          aa = v[2] / s;
          v[2] /= s;
          if ((m + 1 == k + 1) || (fabs(h[m + 6 * (m - 1)]) * (fabs(htmp1) +
                fabs(aa)) <= 2.2204460492503131E-16 * fabs(tst) * ((fabs(h[(m +
                   6 * (m - 1)) - 1]) + fabs(h[m + 6 * m])) + fabs(h[(m + 6 * (m
                   + 1)) + 1])))) {
            exitg3 = true;
          } else {
            m--;
          }
        }

        for (b_k = m; b_k + 1 <= i; b_k++) {
          nr = (i - b_k) + 1;
          if (3 < nr) {
            nr = 3;
          }

          if (b_k + 1 > m + 1) {
            hoffset = b_k + 6 * (b_k - 1);
            for (j = 1; j <= nr; j++) {
              v[j - 1] = h[(j + hoffset) - 1];
            }
          }

          tst = v[0];
          rt2r = xzlarfg(nr, &tst, v);
          v[0] = tst;
          if (b_k + 1 > m + 1) {
            h[b_k + 6 * (b_k - 1)] = tst;
            h[(b_k + 6 * (b_k - 1)) + 1] = 0.0;
            if (b_k + 1 < i) {
              h[(b_k + 6 * (b_k - 1)) + 2] = 0.0;
            }
          } else {
            if (m + 1 > k + 1) {
              h[b_k + 6 * (b_k - 1)] *= 1.0 - rt2r;
            }
          }

          tst = v[1];
          htmp1 = rt2r * v[1];
          if (nr == 3) {
            ab = v[2];
            ba = rt2r * v[2];
            for (j = b_k; j + 1 < 7; j++) {
              aa = (h[b_k + 6 * j] + tst * h[(b_k + 6 * j) + 1]) + ab * h[(b_k +
                6 * j) + 2];
              h[b_k + 6 * j] -= aa * rt2r;
              h[(b_k + 6 * j) + 1] -= aa * htmp1;
              h[(b_k + 6 * j) + 2] -= aa * ba;
            }

            if (b_k + 4 < i + 1) {
              nr = b_k;
            } else {
              nr = i - 3;
            }

            for (j = 0; j + 1 <= nr + 4; j++) {
              aa = (h[j + 6 * b_k] + tst * h[j + 6 * (b_k + 1)]) + ab * h[j + 6 *
                (b_k + 2)];
              h[j + 6 * b_k] -= aa * rt2r;
              h[j + 6 * (b_k + 1)] -= aa * htmp1;
              h[j + 6 * (b_k + 2)] -= aa * ba;
            }
          } else {
            if (nr == 2) {
              for (j = b_k; j + 1 < 7; j++) {
                aa = h[b_k + 6 * j] + tst * h[(b_k + 6 * j) + 1];
                h[b_k + 6 * j] -= aa * rt2r;
                h[(b_k + 6 * j) + 1] -= aa * htmp1;
              }

              for (j = 0; j + 1 <= i + 1; j++) {
                aa = h[j + 6 * b_k] + tst * h[j + 6 * (b_k + 1)];
                h[j + 6 * b_k] -= aa * rt2r;
                h[j + 6 * (b_k + 1)] -= aa * htmp1;
              }
            }
          }
        }

        its++;
      }
    }

    if (!goto150) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((L != i + 1) && (L == i)) {
        tst = h[(i + 6 * i) - 1];
        htmp1 = h[i + 6 * (i - 1)];
        aa = h[i + 6 * i];
        xdlanv2(&h[(i + 6 * (i - 1)) - 1], &tst, &htmp1, &aa, &ab, &ba, &rt2r,
                &rt1r, &s, &sn);
        h[(i + 6 * i) - 1] = tst;
        h[i + 6 * (i - 1)] = htmp1;
        h[i + 6 * i] = aa;
        if (6 > i + 1) {
          nr = (i + (i + 1) * 6) - 1;
          hoffset = i + (i + 1) * 6;
          for (k = 1; k <= 5 - i; k++) {
            tst = s * h[nr] + sn * h[hoffset];
            h[hoffset] = s * h[hoffset] - sn * h[nr];
            h[nr] = tst;
            hoffset += 6;
            nr += 6;
          }
        }

        if (!(i - 1 < 1)) {
          nr = (i - 1) * 6;
          hoffset = i * 6;
          for (k = 1; k < i; k++) {
            tst = s * h[nr] + sn * h[hoffset];
            h[hoffset] = s * h[hoffset] - sn * h[nr];
            h[nr] = tst;
            hoffset++;
            nr++;
          }
        }
      }

      i = L - 2;
    }
  }

  return info;
}

/* End of code generation (xdhseqr.c) */
