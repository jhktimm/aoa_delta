/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzgeev.c
 *
 * Code generation for function 'xzgeev'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "xzgeev.h"
#include "xzlartg.h"
#include "xzhgeqz.h"
#include "abs.h"
#include "f_generate_and_eval_multi_residuals_rtwutil.h"

/* Function Definitions */
void b_xzgeev(const double A[36], int *info, creal_T alpha1[6], creal_T beta1[6])
{
  int ii;
  creal_T At[36];
  double anrm;
  boolean_T exitg1;
  double absxk;
  boolean_T ilascl;
  int i;
  double anrmto;
  int ilo;
  double ctoc;
  int ihi;
  boolean_T notdone;
  int exitg3;
  double stemp_im;
  int j;
  double cto1;
  double mul;
  int nzcount;
  int jj;
  creal_T atmp;
  boolean_T exitg4;
  int exitg2;
  for (ii = 0; ii < 36; ii++) {
    At[ii].re = A[ii];
    At[ii].im = 0.0;
  }

  *info = 0;
  anrm = 0.0;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii < 36)) {
    absxk = rt_hypotd_snf(At[ii].re, At[ii].im);
    if (rtIsNaN(absxk)) {
      anrm = rtNaN;
      exitg1 = true;
    } else {
      if (absxk > anrm) {
        anrm = absxk;
      }

      ii++;
    }
  }

  if (!((!rtIsInf(anrm)) && (!rtIsNaN(anrm)))) {
    for (i = 0; i < 6; i++) {
      alpha1[i].re = rtNaN;
      alpha1[i].im = 0.0;
      beta1[i].re = rtNaN;
      beta1[i].im = 0.0;
    }
  } else {
    ilascl = false;
    anrmto = anrm;
    if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
      anrmto = 6.7178761075670888E-139;
      ilascl = true;
    } else {
      if (anrm > 1.4885657073574029E+138) {
        anrmto = 1.4885657073574029E+138;
        ilascl = true;
      }
    }

    if (ilascl) {
      absxk = anrm;
      ctoc = anrmto;
      notdone = true;
      while (notdone) {
        stemp_im = absxk * 2.0041683600089728E-292;
        cto1 = ctoc / 4.9896007738368E+291;
        if ((stemp_im > ctoc) && (ctoc != 0.0)) {
          mul = 2.0041683600089728E-292;
          absxk = stemp_im;
        } else if (cto1 > absxk) {
          mul = 4.9896007738368E+291;
          ctoc = cto1;
        } else {
          mul = ctoc / absxk;
          notdone = false;
        }

        for (ii = 0; ii < 36; ii++) {
          At[ii].re *= mul;
          At[ii].im *= mul;
        }
      }
    }

    ilo = 0;
    ihi = 6;
    do {
      exitg3 = 0;
      i = 0;
      j = 0;
      notdone = false;
      ii = ihi;
      exitg1 = false;
      while ((!exitg1) && (ii > 0)) {
        nzcount = 0;
        i = ii;
        j = ihi;
        jj = 1;
        exitg4 = false;
        while ((!exitg4) && (jj <= ihi)) {
          if ((At[(ii + 6 * (jj - 1)) - 1].re != 0.0) || (At[(ii + 6 * (jj - 1))
               - 1].im != 0.0) || (ii == jj)) {
            if (nzcount == 0) {
              j = jj;
              nzcount = 1;
              jj++;
            } else {
              nzcount = 2;
              exitg4 = true;
            }
          } else {
            jj++;
          }
        }

        if (nzcount < 2) {
          notdone = true;
          exitg1 = true;
        } else {
          ii--;
        }
      }

      if (!notdone) {
        exitg3 = 2;
      } else {
        if (i != ihi) {
          for (ii = 0; ii < 6; ii++) {
            atmp = At[(i + 6 * ii) - 1];
            At[(i + 6 * ii) - 1] = At[(ihi + 6 * ii) - 1];
            At[(ihi + 6 * ii) - 1] = atmp;
          }
        }

        if (j != ihi) {
          for (ii = 0; ii + 1 <= ihi; ii++) {
            atmp = At[ii + 6 * (j - 1)];
            At[ii + 6 * (j - 1)] = At[ii + 6 * (ihi - 1)];
            At[ii + 6 * (ihi - 1)] = atmp;
          }
        }

        ihi--;
        if (ihi == 1) {
          exitg3 = 1;
        }
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
    } else {
      do {
        exitg2 = 0;
        i = 0;
        j = 0;
        notdone = false;
        jj = ilo + 1;
        exitg1 = false;
        while ((!exitg1) && (jj <= ihi)) {
          nzcount = 0;
          i = ihi;
          j = jj;
          ii = ilo + 1;
          exitg4 = false;
          while ((!exitg4) && (ii <= ihi)) {
            if ((At[(ii + 6 * (jj - 1)) - 1].re != 0.0) || (At[(ii + 6 * (jj - 1))
                 - 1].im != 0.0) || (ii == jj)) {
              if (nzcount == 0) {
                i = ii;
                nzcount = 1;
                ii++;
              } else {
                nzcount = 2;
                exitg4 = true;
              }
            } else {
              ii++;
            }
          }

          if (nzcount < 2) {
            notdone = true;
            exitg1 = true;
          } else {
            jj++;
          }
        }

        if (!notdone) {
          exitg2 = 1;
        } else {
          if (i != ilo + 1) {
            for (ii = ilo; ii + 1 < 7; ii++) {
              atmp = At[(i + 6 * ii) - 1];
              At[(i + 6 * ii) - 1] = At[ilo + 6 * ii];
              At[ilo + 6 * ii] = atmp;
            }
          }

          if (j != ilo + 1) {
            for (ii = 0; ii + 1 <= ihi; ii++) {
              atmp = At[ii + 6 * (j - 1)];
              At[ii + 6 * (j - 1)] = At[ii + 6 * ilo];
              At[ii + 6 * ilo] = atmp;
            }
          }

          ilo++;
          if (ilo + 1 == ihi) {
            exitg2 = 1;
          }
        }
      } while (exitg2 == 0);
    }

    if (!(ihi < ilo + 3)) {
      for (ii = ilo; ii + 1 < ihi - 1; ii++) {
        for (nzcount = ihi - 1; nzcount + 1 > ii + 2; nzcount--) {
          xzlartg(At[(nzcount + 6 * ii) - 1], At[nzcount + 6 * ii], &absxk,
                  &atmp, &At[(nzcount + 6 * ii) - 1]);
          At[nzcount + 6 * ii].re = 0.0;
          At[nzcount + 6 * ii].im = 0.0;
          for (j = ii + 1; j + 1 < 7; j++) {
            ctoc = absxk * At[(nzcount + 6 * j) - 1].re + (atmp.re * At[nzcount
              + 6 * j].re - atmp.im * At[nzcount + 6 * j].im);
            stemp_im = absxk * At[(nzcount + 6 * j) - 1].im + (atmp.re *
              At[nzcount + 6 * j].im + atmp.im * At[nzcount + 6 * j].re);
            cto1 = At[(nzcount + 6 * j) - 1].re;
            At[nzcount + 6 * j].re = absxk * At[nzcount + 6 * j].re - (atmp.re *
              At[(nzcount + 6 * j) - 1].re + atmp.im * At[(nzcount + 6 * j) - 1]
              .im);
            At[nzcount + 6 * j].im = absxk * At[nzcount + 6 * j].im - (atmp.re *
              At[(nzcount + 6 * j) - 1].im - atmp.im * cto1);
            At[(nzcount + 6 * j) - 1].re = ctoc;
            At[(nzcount + 6 * j) - 1].im = stemp_im;
          }

          atmp.re = -atmp.re;
          atmp.im = -atmp.im;
          for (i = 0; i + 1 <= ihi; i++) {
            ctoc = absxk * At[i + 6 * nzcount].re + (atmp.re * At[i + 6 *
              (nzcount - 1)].re - atmp.im * At[i + 6 * (nzcount - 1)].im);
            stemp_im = absxk * At[i + 6 * nzcount].im + (atmp.re * At[i + 6 *
              (nzcount - 1)].im + atmp.im * At[i + 6 * (nzcount - 1)].re);
            cto1 = At[i + 6 * nzcount].re;
            At[i + 6 * (nzcount - 1)].re = absxk * At[i + 6 * (nzcount - 1)].re
              - (atmp.re * At[i + 6 * nzcount].re + atmp.im * At[i + 6 * nzcount]
                 .im);
            At[i + 6 * (nzcount - 1)].im = absxk * At[i + 6 * (nzcount - 1)].im
              - (atmp.re * At[i + 6 * nzcount].im - atmp.im * cto1);
            At[i + 6 * nzcount].re = ctoc;
            At[i + 6 * nzcount].im = stemp_im;
          }
        }
      }
    }

    b_xzhgeqz(At, ilo + 1, ihi, info, alpha1, beta1);
    if ((*info == 0) && ilascl) {
      notdone = true;
      while (notdone) {
        stemp_im = anrmto * 2.0041683600089728E-292;
        cto1 = anrm / 4.9896007738368E+291;
        if ((stemp_im > anrm) && (anrm != 0.0)) {
          mul = 2.0041683600089728E-292;
          anrmto = stemp_im;
        } else if (cto1 > anrmto) {
          mul = 4.9896007738368E+291;
          anrm = cto1;
        } else {
          mul = anrm / anrmto;
          notdone = false;
        }

        for (ii = 0; ii < 6; ii++) {
          alpha1[ii].re *= mul;
          alpha1[ii].im *= mul;
        }
      }
    }
  }
}

void xzgeev(const double A[4], int *info, creal_T alpha1[2], creal_T beta1[2])
{
  int ii;
  creal_T At[4];
  double anrm;
  boolean_T exitg1;
  double absxk;
  boolean_T ilascl;
  int i;
  double anrmto;
  int ilo;
  double ctoc;
  int ihi;
  boolean_T notdone;
  int j;
  double cfrom1;
  double cto1;
  double mul;
  int nzcount;
  int jj;
  boolean_T exitg2;
  for (ii = 0; ii < 4; ii++) {
    At[ii].re = A[ii];
    At[ii].im = 0.0;
  }

  *info = 0;
  anrm = 0.0;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii < 4)) {
    absxk = rt_hypotd_snf(At[ii].re, At[ii].im);
    if (rtIsNaN(absxk)) {
      anrm = rtNaN;
      exitg1 = true;
    } else {
      if (absxk > anrm) {
        anrm = absxk;
      }

      ii++;
    }
  }

  if (!((!rtIsInf(anrm)) && (!rtIsNaN(anrm)))) {
    for (i = 0; i < 2; i++) {
      alpha1[i].re = rtNaN;
      alpha1[i].im = 0.0;
      beta1[i].re = rtNaN;
      beta1[i].im = 0.0;
    }
  } else {
    ilascl = false;
    anrmto = anrm;
    if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
      anrmto = 6.7178761075670888E-139;
      ilascl = true;
    } else {
      if (anrm > 1.4885657073574029E+138) {
        anrmto = 1.4885657073574029E+138;
        ilascl = true;
      }
    }

    if (ilascl) {
      absxk = anrm;
      ctoc = anrmto;
      notdone = true;
      while (notdone) {
        cfrom1 = absxk * 2.0041683600089728E-292;
        cto1 = ctoc / 4.9896007738368E+291;
        if ((cfrom1 > ctoc) && (ctoc != 0.0)) {
          mul = 2.0041683600089728E-292;
          absxk = cfrom1;
        } else if (cto1 > absxk) {
          mul = 4.9896007738368E+291;
          ctoc = cto1;
        } else {
          mul = ctoc / absxk;
          notdone = false;
        }

        for (ii = 0; ii < 4; ii++) {
          At[ii].re *= mul;
          At[ii].im *= mul;
        }
      }
    }

    ilo = 1;
    ihi = 2;
    i = 0;
    j = 0;
    notdone = false;
    ii = 2;
    exitg1 = false;
    while ((!exitg1) && (ii > 0)) {
      nzcount = 0;
      i = ii;
      j = 2;
      jj = 1;
      exitg2 = false;
      while ((!exitg2) && (jj <= 2)) {
        if ((At[(ii + ((jj - 1) << 1)) - 1].re != 0.0) || (At[(ii + ((jj - 1) <<
               1)) - 1].im != 0.0) || (ii == jj)) {
          if (nzcount == 0) {
            j = jj;
            nzcount = 1;
            jj++;
          } else {
            nzcount = 2;
            exitg2 = true;
          }
        } else {
          jj++;
        }
      }

      if (nzcount < 2) {
        notdone = true;
        exitg1 = true;
      } else {
        ii--;
      }
    }

    if (!notdone) {
      i = 0;
      j = 0;
      notdone = false;
      jj = 1;
      exitg1 = false;
      while ((!exitg1) && (jj <= 2)) {
        nzcount = 0;
        i = 2;
        j = jj;
        ii = 1;
        exitg2 = false;
        while ((!exitg2) && (ii <= 2)) {
          if ((At[(ii + ((jj - 1) << 1)) - 1].re != 0.0) || (At[(ii + ((jj - 1) <<
                 1)) - 1].im != 0.0) || (ii == jj)) {
            if (nzcount == 0) {
              i = ii;
              nzcount = 1;
              ii++;
            } else {
              nzcount = 2;
              exitg2 = true;
            }
          } else {
            ii++;
          }
        }

        if (nzcount < 2) {
          notdone = true;
          exitg1 = true;
        } else {
          jj++;
        }
      }

      if (notdone) {
        if (i != 1) {
          for (ii = 0; ii + 1 < 3; ii++) {
            absxk = At[(i + (ii << 1)) - 1].re;
            ctoc = At[(i + (ii << 1)) - 1].im;
            At[(i + (ii << 1)) - 1] = At[ii << 1];
            At[ii << 1].re = absxk;
            At[ii << 1].im = ctoc;
          }
        }

        if (j != 1) {
          for (ii = 0; ii + 1 < 3; ii++) {
            absxk = At[ii + ((j - 1) << 1)].re;
            ctoc = At[ii + ((j - 1) << 1)].im;
            At[ii + ((j - 1) << 1)] = At[ii];
            At[ii].re = absxk;
            At[ii].im = ctoc;
          }
        }

        ilo = 2;
      }
    } else {
      if (i != 2) {
        for (ii = 0; ii < 2; ii++) {
          absxk = At[ii << 1].re;
          ctoc = At[ii << 1].im;
          At[ii << 1] = At[1 + (ii << 1)];
          At[1 + (ii << 1)].re = absxk;
          At[1 + (ii << 1)].im = ctoc;
        }
      }

      if (j != 2) {
        for (ii = 0; ii + 1 < 3; ii++) {
          absxk = At[ii].re;
          ctoc = At[ii].im;
          At[ii] = At[2 + ii];
          At[2 + ii].re = absxk;
          At[2 + ii].im = ctoc;
        }
      }

      ihi = 1;
    }

    xzhgeqz(At, ilo, ihi, info, alpha1, beta1);
    if ((*info == 0) && ilascl) {
      notdone = true;
      while (notdone) {
        cfrom1 = anrmto * 2.0041683600089728E-292;
        cto1 = anrm / 4.9896007738368E+291;
        if ((cfrom1 > anrm) && (anrm != 0.0)) {
          mul = 2.0041683600089728E-292;
          anrmto = cfrom1;
        } else if (cto1 > anrmto) {
          mul = 4.9896007738368E+291;
          anrm = cto1;
        } else {
          mul = anrm / anrmto;
          notdone = false;
        }

        for (ii = 0; ii < 2; ii++) {
          alpha1[ii].re *= mul;
          alpha1[ii].im *= mul;
        }
      }
    }
  }
}

/* End of code generation (xzgeev.c) */
