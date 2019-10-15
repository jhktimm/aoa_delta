/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: isSymmetricPositiveSemiDefinite.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 15-Oct-2019 14:56:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "isSymmetricPositiveSemiDefinite.h"
#include "xdlanv2.h"
#include "xdhseqr.h"
#include "xgehrd.h"
#include "xzgeev.h"
#include "eps.h"
#include "xhseqr.h"

/* Function Definitions */

/*
 * Arguments    : const double value[36]
 * Return Type  : void
 */
void b_isSymmetricPositiveSemiDefini(const double value[36])
{
  int ixstart;
  double y[6];
  double mtmp;
  int ix;
  boolean_T exitg1;
  boolean_T p;
  double b_y[36];
  creal_T alpha1[6];
  creal_T beta1[6];
  int exitg2;
  int istart;
  double b;
  double c;
  double d;
  double rt1r;
  double rt1i;
  double rt2r;
  double rt2i;
  double cs;
  double sn;
  for (ixstart = 0; ixstart < 6; ixstart++) {
    y[ixstart] = fabs(value[ixstart * 7]);
  }

  ixstart = 1;
  mtmp = y[0];
  if (rtIsNaN(y[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 7)) {
      ixstart = ix;
      if (!rtIsNaN(y[ix - 1])) {
        mtmp = y[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 6) {
    while (ixstart + 1 < 7) {
      if (y[ixstart] > mtmp) {
        mtmp = y[ixstart];
      }

      ixstart++;
    }
  }

  eps(mtmp);
  for (ixstart = 0; ixstart < 6; ixstart++) {
    for (ix = 0; ix < 6; ix++) {
      b_y[ix + 6 * ixstart] = (value[ix + 6 * ixstart] + value[ixstart + 6 * ix])
        / 2.0;
    }
  }

  p = true;
  for (ixstart = 0; ixstart < 36; ixstart++) {
    if (p && ((!rtIsInf(b_y[ixstart])) && (!rtIsNaN(b_y[ixstart])))) {
      p = true;
    } else {
      p = false;
    }
  }

  if (p) {
    p = true;
    ixstart = 0;
    exitg1 = false;
    while ((!exitg1) && (ixstart < 6)) {
      ix = 0;
      do {
        exitg2 = 0;
        if (ix <= ixstart) {
          if (!(b_y[ix + 6 * ixstart] == b_y[ixstart + 6 * ix])) {
            p = false;
            exitg2 = 1;
          } else {
            ix++;
          }
        } else {
          ixstart++;
          exitg2 = 2;
        }
      } while (exitg2 == 0);

      if (exitg2 == 1) {
        exitg1 = true;
      }
    }

    if (p) {
      p = true;
      for (ixstart = 0; ixstart < 36; ixstart++) {
        if (p && ((!rtIsInf(b_y[ixstart])) && (!rtIsNaN(b_y[ixstart])))) {
          p = true;
        } else {
          p = false;
        }
      }

      if (p) {
        b_xgehrd(b_y);
        eml_dlahqr(b_y);
        istart = 4;
        for (ixstart = 0; ixstart < 3; ixstart++) {
          for (ix = istart; ix < 7; ix++) {
            b_y[(ix + 6 * ixstart) - 1] = 0.0;
          }

          istart++;
        }

        for (ixstart = 4; ixstart >= 0; ixstart--) {
          if (b_y[(ixstart + 6 * ixstart) + 1] != 0.0) {
            mtmp = b_y[ixstart + 6 * ixstart];
            b = b_y[ixstart + 6 * (ixstart + 1)];
            c = b_y[(ixstart + 6 * ixstart) + 1];
            d = b_y[(ixstart + 6 * (ixstart + 1)) + 1];
            xdlanv2(&mtmp, &b, &c, &d, &rt1r, &rt1i, &rt2r, &rt2i, &cs, &sn);
          }
        }
      }
    } else {
      b_xzgeev(b_y, &ixstart, alpha1, beta1);
    }
  }
}

/*
 * Arguments    : const double value[4]
 * Return Type  : void
 */
void isSymmetricPositiveSemiDefinite(const double value[4])
{
  int ixstart;
  double y[2];
  double mtmp;
  int ix;
  boolean_T exitg1;
  boolean_T p;
  double b_y[4];
  creal_T alpha1[2];
  creal_T beta1[2];
  int exitg2;
  double b;
  double c;
  double d;
  double rt1r;
  double rt1i;
  double rt2r;
  double rt2i;
  double cs;
  double sn;
  for (ixstart = 0; ixstart < 2; ixstart++) {
    y[ixstart] = fabs(value[ixstart * 3]);
  }

  ixstart = 1;
  mtmp = y[0];
  if (rtIsNaN(y[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 3)) {
      ixstart = 2;
      if (!rtIsNaN(y[1])) {
        mtmp = y[1];
        exitg1 = true;
      } else {
        ix = 3;
      }
    }
  }

  if ((ixstart < 2) && (y[1] > mtmp)) {
    mtmp = y[1];
  }

  eps(mtmp);
  for (ixstart = 0; ixstart < 2; ixstart++) {
    for (ix = 0; ix < 2; ix++) {
      b_y[ix + (ixstart << 1)] = (value[ix + (ixstart << 1)] + value[ixstart +
        (ix << 1)]) / 2.0;
    }
  }

  p = true;
  for (ixstart = 0; ixstart < 4; ixstart++) {
    if (p && ((!rtIsInf(b_y[ixstart])) && (!rtIsNaN(b_y[ixstart])))) {
      p = true;
    } else {
      p = false;
    }
  }

  if (p) {
    p = true;
    ixstart = 0;
    exitg1 = false;
    while ((!exitg1) && (ixstart < 2)) {
      ix = 0;
      do {
        exitg2 = 0;
        if (ix <= ixstart) {
          if (!(b_y[ix + (ixstart << 1)] == b_y[ixstart + (ix << 1)])) {
            p = false;
            exitg2 = 1;
          } else {
            ix++;
          }
        } else {
          ixstart++;
          exitg2 = 2;
        }
      } while (exitg2 == 0);

      if (exitg2 == 1) {
        exitg1 = true;
      }
    }

    if (p) {
      p = true;
      for (ixstart = 0; ixstart < 4; ixstart++) {
        if (p && ((!rtIsInf(b_y[ixstart])) && (!rtIsNaN(b_y[ixstart])))) {
          p = true;
        } else {
          p = false;
        }
      }

      if (p) {
        xgehrd(b_y);
        xhseqr(b_y);
        if (b_y[1] != 0.0) {
          mtmp = b_y[0];
          b = b_y[2];
          c = b_y[1];
          d = b_y[3];
          xdlanv2(&mtmp, &b, &c, &d, &rt1r, &rt1i, &rt2r, &rt2i, &cs, &sn);
        }
      }
    } else {
      xzgeev(b_y, &ixstart, alpha1, beta1);
    }
  }
}

/*
 * File trailer for isSymmetricPositiveSemiDefinite.c
 *
 * [EOF]
 */
