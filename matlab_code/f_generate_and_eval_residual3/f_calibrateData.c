/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_calibrateData.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 23-Aug-2019 08:22:53
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "f_calibrateData.h"
#include "f_generate_and_eval_residual_emxutil.h"

/* Function Definitions */

/*
 * Initialize
 * Arguments    : const emxArray_creal_T *Forw
 *                const emxArray_creal_T *Refl
 *                const creal_T cof22[4]
 *                emxArray_creal_T *Forw_cal
 *                emxArray_creal_T *Refl_cal
 * Return Type  : void
 */
void f_calibrateData(const emxArray_creal_T *Forw, const emxArray_creal_T *Refl,
                     const creal_T cof22[4], emxArray_creal_T *Forw_cal,
                     emxArray_creal_T *Refl_cal)
{
  int i2;
  int loop_ub;
  emxArray_int32_T *r0;
  emxArray_creal_T *b_Forw;
  double Forw_re;
  double Forw_im;
  double Refl_re;
  double Refl_im;
  i2 = Forw_cal->size[0];
  Forw_cal->size[0] = Forw->size[0];
  emxEnsureCapacity_creal_T(Forw_cal, i2);
  loop_ub = Forw->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    Forw_cal->data[i2].re = 0.0;
    Forw_cal->data[i2].im = 0.0;
  }

  i2 = Refl_cal->size[0];
  Refl_cal->size[0] = Forw->size[0];
  emxEnsureCapacity_creal_T(Refl_cal, i2);
  loop_ub = Forw->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    Refl_cal->data[i2].re = 0.0;
    Refl_cal->data[i2].im = 0.0;
  }

  emxInit_int32_T(&r0, 1);

  /*  compute calibrated FORW and REFL signal */
  loop_ub = Forw_cal->size[0];
  i2 = r0->size[0];
  r0->size[0] = loop_ub;
  emxEnsureCapacity_int32_T(r0, i2);
  for (i2 = 0; i2 < loop_ub; i2++) {
    r0->data[i2] = i2;
  }

  emxInit_creal_T1(&b_Forw, 2);
  loop_ub = Forw->size[0];
  i2 = b_Forw->size[0] * b_Forw->size[1];
  b_Forw->size[0] = 1;
  b_Forw->size[1] = loop_ub;
  emxEnsureCapacity_creal_T1(b_Forw, i2);
  for (i2 = 0; i2 < loop_ub; i2++) {
    Forw_re = Forw->data[i2].re * cof22[0].re - Forw->data[i2].im * cof22[0].im;
    Forw_im = Forw->data[i2].re * cof22[0].im + Forw->data[i2].im * cof22[0].re;
    Refl_re = Refl->data[i2].re * cof22[1].re - Refl->data[i2].im * cof22[1].im;
    Refl_im = Refl->data[i2].re * cof22[1].im + Refl->data[i2].im * cof22[1].re;
    b_Forw->data[b_Forw->size[0] * i2].re = Forw_re + Refl_re;
    b_Forw->data[b_Forw->size[0] * i2].im = Forw_im + Refl_im;
  }

  loop_ub = r0->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    Forw_cal->data[r0->data[i2]] = b_Forw->data[i2];
  }

  loop_ub = Refl_cal->size[0];
  i2 = r0->size[0];
  r0->size[0] = loop_ub;
  emxEnsureCapacity_int32_T(r0, i2);
  for (i2 = 0; i2 < loop_ub; i2++) {
    r0->data[i2] = i2;
  }

  loop_ub = Forw->size[0];
  i2 = b_Forw->size[0] * b_Forw->size[1];
  b_Forw->size[0] = 1;
  b_Forw->size[1] = loop_ub;
  emxEnsureCapacity_creal_T1(b_Forw, i2);
  for (i2 = 0; i2 < loop_ub; i2++) {
    Forw_re = Forw->data[i2].re * cof22[2].re - Forw->data[i2].im * cof22[2].im;
    Forw_im = Forw->data[i2].re * cof22[2].im + Forw->data[i2].im * cof22[2].re;
    Refl_re = Refl->data[i2].re * cof22[3].re - Refl->data[i2].im * cof22[3].im;
    Refl_im = Refl->data[i2].re * cof22[3].im + Refl->data[i2].im * cof22[3].re;
    b_Forw->data[b_Forw->size[0] * i2].re = Forw_re + Refl_re;
    b_Forw->data[b_Forw->size[0] * i2].im = Forw_im + Refl_im;
  }

  loop_ub = r0->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    Refl_cal->data[r0->data[i2]] = b_Forw->data[i2];
  }

  emxFree_creal_T(&b_Forw);
  emxFree_int32_T(&r0);

  /* ------------Plot Before and After Calibration----------------------------- */
}

/*
 * File trailer for f_calibrateData.c
 *
 * [EOF]
 */
