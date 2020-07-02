/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * f_calibrateData.c
 *
 * Code generation for function 'f_calibrateData'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "f_calibrateData.h"
#include "f_generate_and_eval_multi_residuals_emxutil.h"

/* Function Definitions */
void f_calibrateData(const emxArray_creal_T *Forw, const emxArray_creal_T *Refl,
                     const creal_T cof22[4], emxArray_creal_T *Forw_cal,
                     emxArray_creal_T *Refl_cal)
{
  int i1;
  int loop_ub;
  emxArray_int32_T *r3;
  emxArray_creal_T *b_Forw;
  double Forw_re;
  double Forw_im;
  double Refl_re;
  double Refl_im;
  emxArray_creal_T *c_Forw;

  /* Initialize */
  i1 = Forw_cal->size[0];
  Forw_cal->size[0] = Forw->size[0];
  emxEnsureCapacity((emxArray__common *)Forw_cal, i1, sizeof(creal_T));
  loop_ub = Forw->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Forw_cal->data[i1].re = 0.0;
    Forw_cal->data[i1].im = 0.0;
  }

  i1 = Refl_cal->size[0];
  Refl_cal->size[0] = Forw->size[0];
  emxEnsureCapacity((emxArray__common *)Refl_cal, i1, sizeof(creal_T));
  loop_ub = Forw->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Refl_cal->data[i1].re = 0.0;
    Refl_cal->data[i1].im = 0.0;
  }

  emxInit_int32_T(&r3, 1);

  /*  compute calibrated FORW and REFL signal */
  loop_ub = Forw_cal->size[0];
  i1 = r3->size[0];
  r3->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r3, i1, sizeof(int));
  for (i1 = 0; i1 < loop_ub; i1++) {
    r3->data[i1] = i1;
  }

  emxInit_creal_T1(&b_Forw, 2);
  loop_ub = Forw->size[0];
  i1 = b_Forw->size[0] * b_Forw->size[1];
  b_Forw->size[0] = 1;
  b_Forw->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_Forw, i1, sizeof(creal_T));
  for (i1 = 0; i1 < loop_ub; i1++) {
    Forw_re = Forw->data[i1].re * cof22[0].re - Forw->data[i1].im * cof22[0].im;
    Forw_im = Forw->data[i1].re * cof22[0].im + Forw->data[i1].im * cof22[0].re;
    Refl_re = Refl->data[i1].re * cof22[1].re - Refl->data[i1].im * cof22[1].im;
    Refl_im = Refl->data[i1].re * cof22[1].im + Refl->data[i1].im * cof22[1].re;
    b_Forw->data[b_Forw->size[0] * i1].re = Forw_re + Refl_re;
    b_Forw->data[b_Forw->size[0] * i1].im = Forw_im + Refl_im;
  }

  loop_ub = r3->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Forw_cal->data[r3->data[i1]] = b_Forw->data[i1];
  }

  emxFree_creal_T(&b_Forw);
  loop_ub = Refl_cal->size[0];
  i1 = r3->size[0];
  r3->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r3, i1, sizeof(int));
  for (i1 = 0; i1 < loop_ub; i1++) {
    r3->data[i1] = i1;
  }

  emxInit_creal_T1(&c_Forw, 2);
  loop_ub = Forw->size[0];
  i1 = c_Forw->size[0] * c_Forw->size[1];
  c_Forw->size[0] = 1;
  c_Forw->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)c_Forw, i1, sizeof(creal_T));
  for (i1 = 0; i1 < loop_ub; i1++) {
    Forw_re = Forw->data[i1].re * cof22[2].re - Forw->data[i1].im * cof22[2].im;
    Forw_im = Forw->data[i1].re * cof22[2].im + Forw->data[i1].im * cof22[2].re;
    Refl_re = Refl->data[i1].re * cof22[3].re - Refl->data[i1].im * cof22[3].im;
    Refl_im = Refl->data[i1].re * cof22[3].im + Refl->data[i1].im * cof22[3].re;
    c_Forw->data[c_Forw->size[0] * i1].re = Forw_re + Refl_re;
    c_Forw->data[c_Forw->size[0] * i1].im = Forw_im + Refl_im;
  }

  loop_ub = r3->size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Refl_cal->data[r3->data[i1]] = c_Forw->data[i1];
  }

  emxFree_creal_T(&c_Forw);
  emxFree_int32_T(&r3);

  /*      Forw_cal = Forw*cof22(1) +... */
  /*          Refl*cof22(2); */
  /*      Refl_cal = Forw*cof22(3) +... */
  /*          Refl*cof22(4); */
  /*  ------------Plot Before and After Calibration----------------------------- */
  /*  if plt == 1 */
  /*      figure('Renderer', 'painters', 'Position', [100 100 1*600 2/3*700], 'Name', 'Amplitudes') */
  /*      subplot(2,1,1) */
  /*  %     set(gca, 'ColorOrder',  cbrewer('qual', 'Dark2', 4)) */
  /*      hold on */
  /*      plot(abs(Probe(:,1))) */
  /*      plot(abs(Forw(:,1))) */
  /*      plot(abs(Refl(:,1))) */
  /*      plot(abs(Forw(:,1)+Refl(:,1)),'r--') */
  /*      ylabel('Amplitude MV/m') */
  /*      axis tight */
  /*      title('Before Calibration') */
  /*       */
  /*      legend({ 'Probe', 'Forward', 'Reflected','Virtual Probe'}, 'Orientation', 'vertical',... */
  /*          'Location', 'eastoutside') */
  /*       */
  /*      subplot(2,1,2) */
  /*  %     set(gca, 'ColorOrder',  cbrewer('qual', 'Dark2', 4)) */
  /*       */
  /*      hold on */
  /*      plot(abs(Probe(:,1))) */
  /*      plot(abs(Forw_cal(:,1))) */
  /*      plot(abs(Refl_cal(:,1))) */
  /*      plot(abs(Forw_cal(:,1)+Refl_cal(:,1)),'r--') */
  /*       */
  /*      legend('Virtual Probe', 'Probe', 'Forward', 'Reflected') */
  /*      ylabel('Amplitude MV/m') */
  /*      xlabel('Samples') */
  /*      title('After Calibration') */
  /*      legend({ 'Probe', 'Forward', 'Reflected','Virtual Probe'}, 'Orientation', 'vertical',... */
  /*          'Location', 'eastoutside') */
  /*      axis tight */
  /*       */
  /*      figure('Renderer', 'painters', 'Position', [100 100 1*600 2/3*700], 'Name', 'I values') */
  /*      subplot(2,1,1) */
  /*      set(gca, 'ColorOrder',  cbrewer('qual', 'Dark2', 4)) */
  /*      hold on */
  /*      plot(real(Probe(:,1))) */
  /*      plot(real(Forw(:,1))) */
  /*      plot(real(Refl(:,1))) */
  /*      plot(real(Forw(:,1)+Refl(:,1)),'r--') */
  /*      ylabel('Amplitude MV/m') */
  /*      axis tight */
  /*      title('Before Calibration') */
  /*       */
  /*      legend({ 'Probe', 'Forward', 'Reflected','Virtual Probe'}, 'Orientation', 'vertical',... */
  /*          'Location', 'eastoutside') */
  /*       */
  /*      subplot(2,1,2) */
  /*      set(gca, 'ColorOrder',  cbrewer('qual', 'Dark2', 4)) */
  /*       */
  /*      hold on */
  /*      plot(real(Probe(:,1))) */
  /*      plot(real(Forw_cal(:,1))) */
  /*      plot(real(Refl_cal(:,1))) */
  /*      plot(real(Forw_cal(:,1)+Refl_cal(:,1)),'r--') */
  /*       */
  /*      %legend('Virtual Probe', 'Probe', 'Forward', 'Reflected') */
  /*      ylabel('Amplitude MV/m') */
  /*      xlabel('Samples') */
  /*      title('After Calibration') */
  /*      legend({ 'Probe', 'Forward', 'Reflected','Virtual Probe'}, 'Orientation', 'vertical',... */
  /*          'Location', 'eastoutside') */
  /*      axis tight */
  /*       */
  /*  end */
}

/* End of code generation (f_calibrateData.c) */
