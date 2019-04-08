/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xgeqp3.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_calib_and_res_gen_ukf.h"
#include "xgeqp3.h"
#include "abs.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xscal.h"
#include "recip.h"
#include "xdlapy3.h"
#include "xzlarfg.h"
#include "ixamax.h"
#include "f_calib_and_res_gen_ukf_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *A
 *                creal_T tau_data[]
 *                int tau_size[1]
 *                int jpvt[4]
 * Return Type  : void
 */
void b_xgeqp3(emxArray_creal_T *A, creal_T tau_data[], int tau_size[1], int
              jpvt[4])
{
  int m;
  int mn;
  int k;
  int ix;
  int i;
  creal_T work[4];
  int i_i;
  double smax;
  int mmi;
  int pvt;
  double vn1[4];
  double temp2;
  double vn2[4];
  int iy;
  double absxk;
  creal_T atmp;
  double beta1;
  creal_T b_A;
  m = A->size[0];
  mn = A->size[0];
  if (!(mn < 4)) {
    mn = 4;
  }

  tau_size[0] = mn;
  k = 0;
  for (ix = 0; ix < 4; ix++) {
    jpvt[ix] = 1 + ix;
    work[ix].re = 0.0;
    work[ix].im = 0.0;
    smax = 0.0;
    if (!(m < 1)) {
      if (m == 1) {
        smax = rt_hypotd_snf(A->data[k].re, A->data[k].im);
      } else {
        temp2 = 2.2250738585072014E-308;
        iy = k + m;
        for (pvt = k; pvt + 1 <= iy; pvt++) {
          absxk = fabs(A->data[pvt].re);
          if (absxk > temp2) {
            beta1 = temp2 / absxk;
            smax = 1.0 + smax * beta1 * beta1;
            temp2 = absxk;
          } else {
            beta1 = absxk / temp2;
            smax += beta1 * beta1;
          }

          absxk = fabs(A->data[pvt].im);
          if (absxk > temp2) {
            beta1 = temp2 / absxk;
            smax = 1.0 + smax * beta1 * beta1;
            temp2 = absxk;
          } else {
            beta1 = absxk / temp2;
            smax += beta1 * beta1;
          }
        }

        smax = temp2 * sqrt(smax);
      }
    }

    vn1[ix] = smax;
    vn2[ix] = vn1[ix];
    k += m;
  }

  for (i = 0; i + 1 <= mn; i++) {
    i_i = i + i * m;
    mmi = (m - i) - 1;
    pvt = 0;
    if (4 - i > 1) {
      ix = i;
      smax = fabs(vn1[i]);
      for (k = 1; k + 1 <= 4 - i; k++) {
        ix++;
        temp2 = fabs(vn1[ix]);
        if (temp2 > smax) {
          pvt = k;
          smax = temp2;
        }
      }
    }

    pvt += i;
    if (pvt + 1 != i + 1) {
      ix = m * pvt;
      iy = m * i;
      for (k = 1; k <= m; k++) {
        atmp = A->data[ix];
        A->data[ix] = A->data[iy];
        A->data[iy] = atmp;
        ix++;
        iy++;
      }

      iy = jpvt[pvt];
      jpvt[pvt] = jpvt[i];
      jpvt[i] = iy;
      vn1[pvt] = vn1[i];
      vn2[pvt] = vn2[i];
    }

    if (i + 1 < m) {
      atmp = A->data[i_i];
      absxk = 0.0;
      temp2 = 0.0;
      if (!(1 + mmi <= 0)) {
        smax = c_xnrm2(mmi, A, i_i + 2);
        if ((smax != 0.0) || (A->data[i_i].im != 0.0)) {
          beta1 = xdlapy3(A->data[i_i].re, A->data[i_i].im, smax);
          if (A->data[i_i].re >= 0.0) {
            beta1 = -beta1;
          }

          if (fabs(beta1) < 1.0020841800044864E-292) {
            iy = 0;
            ix = i_i + mmi;
            do {
              iy++;
              for (k = i_i + 1; k + 1 <= ix + 1; k++) {
                smax = A->data[k].re;
                temp2 = A->data[k].im;
                A->data[k].re = 9.9792015476736E+291 * smax - 0.0 * temp2;
                A->data[k].im = 9.9792015476736E+291 * temp2 + 0.0 * smax;
              }

              beta1 *= 9.9792015476736E+291;
              atmp.re *= 9.9792015476736E+291;
              atmp.im *= 9.9792015476736E+291;
            } while (!(fabs(beta1) >= 1.0020841800044864E-292));

            smax = c_xnrm2(mmi, A, i_i + 2);
            beta1 = xdlapy3(atmp.re, atmp.im, smax);
            if (atmp.re >= 0.0) {
              beta1 = -beta1;
            }

            smax = beta1 - atmp.re;
            if (0.0 - atmp.im == 0.0) {
              absxk = smax / beta1;
              temp2 = 0.0;
            } else if (smax == 0.0) {
              absxk = 0.0;
              temp2 = (0.0 - atmp.im) / beta1;
            } else {
              absxk = smax / beta1;
              temp2 = (0.0 - atmp.im) / beta1;
            }

            b_A.re = atmp.re - beta1;
            b_A.im = atmp.im;
            c_xscal(mmi, recip(b_A), A, i_i + 2);
            for (k = 1; k <= iy; k++) {
              beta1 *= 1.0020841800044864E-292;
            }

            atmp.re = beta1;
            atmp.im = 0.0;
          } else {
            smax = beta1 - A->data[i_i].re;
            temp2 = 0.0 - A->data[i_i].im;
            if (temp2 == 0.0) {
              absxk = smax / beta1;
              temp2 = 0.0;
            } else if (smax == 0.0) {
              absxk = 0.0;
              temp2 /= beta1;
            } else {
              absxk = smax / beta1;
              temp2 /= beta1;
            }

            b_A.re = A->data[i_i].re - beta1;
            b_A.im = A->data[i_i].im;
            c_xscal(mmi, recip(b_A), A, i_i + 2);
            atmp.re = beta1;
            atmp.im = 0.0;
          }
        }
      }

      tau_data[i].re = absxk;
      tau_data[i].im = temp2;
      A->data[i_i] = atmp;
    } else {
      atmp = A->data[i_i];
      absxk = 0.0;
      temp2 = 0.0;
      if (A->data[i_i].im != 0.0) {
        beta1 = xdlapy3(A->data[i_i].re, A->data[i_i].im, 0.0);
        if (A->data[i_i].re >= 0.0) {
          beta1 = -beta1;
        }

        if (fabs(beta1) < 1.0020841800044864E-292) {
          iy = 0;
          do {
            iy++;
            for (k = i_i; k + 1 <= i_i; k++) {
              smax = A->data[k].re;
              temp2 = A->data[k].im;
              A->data[k].re = 9.9792015476736E+291 * smax - 0.0 * temp2;
              A->data[k].im = 9.9792015476736E+291 * temp2 + 0.0 * smax;
            }

            beta1 *= 9.9792015476736E+291;
            atmp.re *= 9.9792015476736E+291;
            atmp.im *= 9.9792015476736E+291;
          } while (!(fabs(beta1) >= 1.0020841800044864E-292));

          beta1 = xdlapy3(atmp.re, atmp.im, 0.0);
          if (atmp.re >= 0.0) {
            beta1 = -beta1;
          }

          smax = beta1 - atmp.re;
          if (0.0 - atmp.im == 0.0) {
            absxk = smax / beta1;
            temp2 = 0.0;
          } else if (smax == 0.0) {
            absxk = 0.0;
            temp2 = (0.0 - atmp.im) / beta1;
          } else {
            absxk = smax / beta1;
            temp2 = (0.0 - atmp.im) / beta1;
          }

          b_A.re = atmp.re - beta1;
          b_A.im = atmp.im;
          d_xscal(recip(b_A), A, i_i + 1);
          for (k = 1; k <= iy; k++) {
            beta1 *= 1.0020841800044864E-292;
          }

          atmp.re = beta1;
          atmp.im = 0.0;
        } else {
          smax = beta1 - A->data[i_i].re;
          temp2 = 0.0 - A->data[i_i].im;
          if (temp2 == 0.0) {
            absxk = smax / beta1;
            temp2 = 0.0;
          } else if (smax == 0.0) {
            absxk = 0.0;
            temp2 /= beta1;
          } else {
            absxk = smax / beta1;
            temp2 /= beta1;
          }

          b_A.re = A->data[i_i].re - beta1;
          b_A.im = A->data[i_i].im;
          d_xscal(recip(b_A), A, i_i + 1);
          atmp.re = beta1;
          atmp.im = 0.0;
        }
      }

      tau_data[i].re = absxk;
      tau_data[i].im = temp2;
      A->data[i_i] = atmp;
    }

    if (i + 1 < 4) {
      atmp = A->data[i_i];
      A->data[i_i].re = 1.0;
      A->data[i_i].im = 0.0;
      b_A.re = tau_data[i].re;
      b_A.im = -tau_data[i].im;
      xzlarf(1 + mmi, 3 - i, i_i + 1, b_A, A, (i + (i + 1) * m) + 1, m, work);
      A->data[i_i] = atmp;
    }

    for (ix = i + 1; ix + 1 < 5; ix++) {
      if (vn1[ix] != 0.0) {
        smax = rt_hypotd_snf(A->data[i + A->size[0] * ix].re, A->data[i +
                             A->size[0] * ix].im) / vn1[ix];
        smax = 1.0 - smax * smax;
        if (smax < 0.0) {
          smax = 0.0;
        }

        temp2 = vn1[ix] / vn2[ix];
        temp2 = smax * (temp2 * temp2);
        if (temp2 <= 1.4901161193847656E-8) {
          if (i + 1 < m) {
            vn1[ix] = d_xnrm2(mmi, A, (i + m * ix) + 2);
            vn2[ix] = vn1[ix];
          } else {
            vn1[ix] = 0.0;
            vn2[ix] = 0.0;
          }
        } else {
          vn1[ix] *= sqrt(smax);
        }
      }
    }
  }
}

/*
 * Arguments    : emxArray_creal_T *A
 *                creal_T tau_data[]
 *                int tau_size[1]
 *                int jpvt[2]
 * Return Type  : void
 */
void xgeqp3(emxArray_creal_T *A, creal_T tau_data[], int tau_size[1], int jpvt[2])
{
  int m;
  int mn;
  int i6;
  int k;
  int j;
  int i;
  creal_T work[2];
  double c_im;
  int i_i;
  double vn2[2];
  int mmi;
  double vn1[2];
  int ix;
  int iy;
  creal_T atmp;
  double c_re;
  double beta1;
  double temp2;
  int lastv;
  int lastc;
  boolean_T exitg1;
  creal_T b_A;
  boolean_T c_A;
  double absxk;
  int jy;
  int exitg2;
  m = A->size[0];
  mn = A->size[0];
  if (!(mn < 2)) {
    mn = 2;
  }

  tau_size[0] = mn;
  for (i6 = 0; i6 < 2; i6++) {
    jpvt[i6] = 1 + i6;
  }

  if (A->size[0] != 0) {
    k = 1;
    for (j = 0; j < 2; j++) {
      work[j].re = 0.0;
      work[j].im = 0.0;
      c_im = xnrm2(m, A, k);
      vn2[j] = c_im;
      k += m;
      vn1[j] = c_im;
    }

    for (i = 0; i + 1 <= mn; i++) {
      i_i = i + i * m;
      mmi = (m - i) - 1;
      j = (i + ixamax(2 - i, vn1, i + 1)) - 1;
      if (j + 1 != i + 1) {
        ix = m * j;
        iy = m * i;
        for (k = 1; k <= m; k++) {
          c_re = A->data[ix].re;
          c_im = A->data[ix].im;
          A->data[ix] = A->data[iy];
          A->data[iy].re = c_re;
          A->data[iy].im = c_im;
          ix++;
          iy++;
        }

        k = jpvt[j];
        jpvt[j] = jpvt[i];
        jpvt[i] = k;
        vn1[j] = vn1[i];
        vn2[j] = vn2[i];
      }

      if (i + 1 < m) {
        atmp = A->data[i_i];
        tau_data[i] = xzlarfg(1 + mmi, &atmp, A, i_i + 2);
        A->data[i_i] = atmp;
      } else {
        atmp = A->data[i_i];
        c_re = 0.0;
        c_im = 0.0;
        if (A->data[i_i].im != 0.0) {
          beta1 = xdlapy3(A->data[i_i].re, A->data[i_i].im, 0.0);
          if (A->data[i_i].re >= 0.0) {
            beta1 = -beta1;
          }

          if (fabs(beta1) < 1.0020841800044864E-292) {
            j = 0;
            do {
              j++;
              for (k = i_i; k + 1 <= i_i; k++) {
                temp2 = A->data[k].re;
                absxk = A->data[k].im;
                A->data[k].re = 9.9792015476736E+291 * temp2 - 0.0 * absxk;
                A->data[k].im = 9.9792015476736E+291 * absxk + 0.0 * temp2;
              }

              beta1 *= 9.9792015476736E+291;
              atmp.re *= 9.9792015476736E+291;
              atmp.im *= 9.9792015476736E+291;
            } while (!(fabs(beta1) >= 1.0020841800044864E-292));

            beta1 = xdlapy3(atmp.re, atmp.im, 0.0);
            if (atmp.re >= 0.0) {
              beta1 = -beta1;
            }

            c_im = beta1 - atmp.re;
            if (0.0 - atmp.im == 0.0) {
              c_re = c_im / beta1;
              c_im = 0.0;
            } else if (c_im == 0.0) {
              c_re = 0.0;
              c_im = (0.0 - atmp.im) / beta1;
            } else {
              c_re = c_im / beta1;
              c_im = (0.0 - atmp.im) / beta1;
            }

            b_A.re = atmp.re - beta1;
            b_A.im = atmp.im;
            b_xscal(recip(b_A), A, i_i + 1);
            for (k = 1; k <= j; k++) {
              beta1 *= 1.0020841800044864E-292;
            }

            atmp.re = beta1;
            atmp.im = 0.0;
          } else {
            c_im = beta1 - A->data[i_i].re;
            temp2 = 0.0 - A->data[i_i].im;
            if (temp2 == 0.0) {
              c_re = c_im / beta1;
              c_im = 0.0;
            } else if (c_im == 0.0) {
              c_re = 0.0;
              c_im = temp2 / beta1;
            } else {
              c_re = c_im / beta1;
              c_im = temp2 / beta1;
            }

            b_A.re = A->data[i_i].re - beta1;
            b_A.im = A->data[i_i].im;
            b_xscal(recip(b_A), A, i_i + 1);
            atmp.re = beta1;
            atmp.im = 0.0;
          }
        }

        tau_data[i].re = c_re;
        tau_data[i].im = c_im;
        A->data[i_i] = atmp;
      }

      if (i + 1 < 2) {
        atmp = A->data[i_i];
        A->data[i_i].re = 1.0;
        A->data[i_i].im = 0.0;
        if ((tau_data[0].re != 0.0) || (-tau_data[0].im != 0.0)) {
          lastv = 1 + mmi;
          k = i_i + mmi;
          exitg1 = false;
          while ((!exitg1) && (lastv > 0)) {
            c_A = ((A->data[k].re == 0.0) && (A->data[k].im == 0.0));
            if (c_A) {
              lastv--;
              k--;
            } else {
              exitg1 = true;
            }
          }

          lastc = 1;
          exitg1 = false;
          while ((!exitg1) && (lastc > 0)) {
            k = m;
            do {
              exitg2 = 0;
              if (k + 1 <= m + lastv) {
                c_A = ((A->data[k].re != 0.0) || (A->data[k].im != 0.0));
                if (c_A) {
                  exitg2 = 1;
                } else {
                  k++;
                }
              } else {
                lastc = 0;
                exitg2 = 2;
              }
            } while (exitg2 == 0);

            if (exitg2 == 1) {
              exitg1 = true;
            }
          }
        } else {
          lastv = 0;
          lastc = 0;
        }

        if (lastv > 0) {
          if (lastc != 0) {
            work[0].re = 0.0;
            work[0].im = 0.0;
            iy = 0;
            j = m;
            while ((m > 0) && (j + 1 <= 1 + m)) {
              ix = i_i;
              c_re = 0.0;
              c_im = 0.0;
              i6 = j + lastv;
              for (k = j; k + 1 <= i6; k++) {
                c_re += A->data[k].re * A->data[ix].re + A->data[k].im * A->
                  data[ix].im;
                c_im += A->data[k].re * A->data[ix].im - A->data[k].im * A->
                  data[ix].re;
                ix++;
              }

              work[iy].re += c_re - 0.0 * c_im;
              work[iy].im += c_im + 0.0 * c_re;
              iy++;
              j += m;
            }
          }

          b_A.re = -tau_data[0].re;
          b_A.im = -(-tau_data[0].im);
          if (!((-tau_data[0].re == 0.0) && (-(-tau_data[0].im) == 0.0))) {
            iy = m;
            jy = 0;
            j = 1;
            while (j <= lastc) {
              if ((work[jy].re != 0.0) || (work[jy].im != 0.0)) {
                c_re = work[jy].re * b_A.re + work[jy].im * b_A.im;
                c_im = work[jy].re * b_A.im - work[jy].im * b_A.re;
                ix = i_i;
                i6 = lastv + iy;
                for (k = iy; k + 1 <= i6; k++) {
                  temp2 = A->data[ix].re * c_re - A->data[ix].im * c_im;
                  absxk = A->data[ix].re * c_im + A->data[ix].im * c_re;
                  A->data[k].re += temp2;
                  A->data[k].im += absxk;
                  ix++;
                }
              }

              jy++;
              iy += m;
              j = 2;
            }
          }
        }

        A->data[i_i] = atmp;
      }

      j = i + 2;
      while (j < 3) {
        k = (i + m) + 1;
        if (vn1[1] != 0.0) {
          c_im = rt_hypotd_snf(A->data[i + A->size[0]].re, A->data[i + A->size[0]]
                               .im) / vn1[1];
          c_im = 1.0 - c_im * c_im;
          if (c_im < 0.0) {
            c_im = 0.0;
          }

          temp2 = vn1[1] / vn2[1];
          temp2 = c_im * (temp2 * temp2);
          if (temp2 <= 1.4901161193847656E-8) {
            if (i + 1 < m) {
              c_im = 0.0;
              if (!(mmi < 1)) {
                if (mmi == 1) {
                  c_im = rt_hypotd_snf(A->data[k].re, A->data[k].im);
                } else {
                  temp2 = 2.2250738585072014E-308;
                  j = k + mmi;
                  while (k + 1 <= j) {
                    absxk = fabs(A->data[k].re);
                    if (absxk > temp2) {
                      c_re = temp2 / absxk;
                      c_im = 1.0 + c_im * c_re * c_re;
                      temp2 = absxk;
                    } else {
                      c_re = absxk / temp2;
                      c_im += c_re * c_re;
                    }

                    absxk = fabs(A->data[k].im);
                    if (absxk > temp2) {
                      c_re = temp2 / absxk;
                      c_im = 1.0 + c_im * c_re * c_re;
                      temp2 = absxk;
                    } else {
                      c_re = absxk / temp2;
                      c_im += c_re * c_re;
                    }

                    k++;
                  }

                  c_im = temp2 * sqrt(c_im);
                }
              }

              vn1[1] = c_im;
              vn2[1] = c_im;
            } else {
              vn1[1] = 0.0;
              vn2[1] = 0.0;
            }
          } else {
            vn1[1] *= sqrt(c_im);
          }
        }

        j = 3;
      }
    }
  }
}

/*
 * File trailer for xgeqp3.c
 *
 * [EOF]
 */
