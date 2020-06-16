/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_calibrateData.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "f_calibrateData.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"

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
  emxArray_int32_T *r2;
  emxArray_creal_T *b_Forw;
  double Forw_re;
  double Forw_im;
  double Refl_re;
  double Refl_im;
  emxArray_creal_T *c_Forw;
  i2 = Forw_cal->size[0];
  Forw_cal->size[0] = Forw->size[0];
  emxEnsureCapacity((emxArray__common *)Forw_cal, i2, sizeof(creal_T));
  loop_ub = Forw->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    Forw_cal->data[i2].re = 0.0;
    Forw_cal->data[i2].im = 0.0;
  }

  i2 = Refl_cal->size[0];
  Refl_cal->size[0] = Forw->size[0];
  emxEnsureCapacity((emxArray__common *)Refl_cal, i2, sizeof(creal_T));
  loop_ub = Forw->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    Refl_cal->data[i2].re = 0.0;
    Refl_cal->data[i2].im = 0.0;
  }

  emxInit_int32_T(&r2, 1);

  /*  compute calibrated FORW and REFL signal */
  loop_ub = Forw_cal->size[0];
  i2 = r2->size[0];
  r2->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r2, i2, sizeof(int));
  for (i2 = 0; i2 < loop_ub; i2++) {
    r2->data[i2] = i2;
  }

  emxInit_creal_T1(&b_Forw, 2);
  loop_ub = Forw->size[0];
  i2 = b_Forw->size[0] * b_Forw->size[1];
  b_Forw->size[0] = 1;
  b_Forw->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_Forw, i2, sizeof(creal_T));
  for (i2 = 0; i2 < loop_ub; i2++) {
    Forw_re = Forw->data[i2].re * cof22[0].re - Forw->data[i2].im * cof22[0].im;
    Forw_im = Forw->data[i2].re * cof22[0].im + Forw->data[i2].im * cof22[0].re;
    Refl_re = Refl->data[i2].re * cof22[1].re - Refl->data[i2].im * cof22[1].im;
    Refl_im = Refl->data[i2].re * cof22[1].im + Refl->data[i2].im * cof22[1].re;
    b_Forw->data[b_Forw->size[0] * i2].re = Forw_re + Refl_re;
    b_Forw->data[b_Forw->size[0] * i2].im = Forw_im + Refl_im;
  }

  loop_ub = r2->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    Forw_cal->data[r2->data[i2]] = b_Forw->data[i2];
  }

  emxFree_creal_T(&b_Forw);
  loop_ub = Refl_cal->size[0];
  i2 = r2->size[0];
  r2->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r2, i2, sizeof(int));
  for (i2 = 0; i2 < loop_ub; i2++) {
    r2->data[i2] = i2;
  }

  emxInit_creal_T1(&c_Forw, 2);
  loop_ub = Forw->size[0];
  i2 = c_Forw->size[0] * c_Forw->size[1];
  c_Forw->size[0] = 1;
  c_Forw->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)c_Forw, i2, sizeof(creal_T));
  for (i2 = 0; i2 < loop_ub; i2++) {
    Forw_re = Forw->data[i2].re * cof22[2].re - Forw->data[i2].im * cof22[2].im;
    Forw_im = Forw->data[i2].re * cof22[2].im + Forw->data[i2].im * cof22[2].re;
    Refl_re = Refl->data[i2].re * cof22[3].re - Refl->data[i2].im * cof22[3].im;
    Refl_im = Refl->data[i2].re * cof22[3].im + Refl->data[i2].im * cof22[3].re;
    c_Forw->data[c_Forw->size[0] * i2].re = Forw_re + Refl_re;
    c_Forw->data[c_Forw->size[0] * i2].im = Forw_im + Refl_im;
  }

  loop_ub = r2->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    Refl_cal->data[r2->data[i2]] = c_Forw->data[i2];
  }

  emxFree_creal_T(&c_Forw);
  emxFree_int32_T(&r2);

  /*      Forw_cal = Forw*cof22(1) +... */
  /*          Refl*cof22(2); */
  /*      Refl_cal = Forw*cof22(3) +... */
  /*          Refl*cof22(4); */
  /*  ------------Plot Before and After Calibration----------------------------- */
  /*  if plt == 1 */
  /*  */
  /*  figsize = f_fig_sizes(); */
  /*  figure('Renderer', 'painters', 'Position', [1500 100 2*figsize.wLong 2*figsize.hBig], 'Name', 'Calibration Basic Plot') */
  /*  subplot(2,1,1); set(gca, 'ColorOrder',  cbrewer('qual', 'Set1', 5)) */
  /*  hold on */
  /*  plot(abs(Forw(:,1))) */
  /*  plot(abs(Refl(:,1))) */
  /*  plot(abs(Probe(:,1))) */
  /*  plot(abs(Forw(:,1)+Refl(:,1)),'--') */
  /*  ylabel('Amplitude MV/m') */
  /*  axis tight; box on */
  /*  title('Before Calibration') */
  /*  legend({ 'Forward $\hat{V}_F$', 'Reflected $\hat{V}_R$', 'Probe $\hat{V}_P$','Virtual Probe $\hat{V}_F + \hat{V}_R$ '}, 'Orientation', 'vertical',... */
  /*      'Location', 'eastoutside') */
  /*  ylim([min(ylim), 1.05*max(ylim)]) */
  /*   */
  /*  subplot(2,1,2);set(gca, 'ColorOrder',  cbrewer('qual', 'Set1', 5)) */
  /*  hold on */
  /*  plot(abs(Forw_cal(:,1))) */
  /*  plot(abs(Refl_cal(:,1))) */
  /*  plot(abs(Probe(:,1))) */
  /*  plot(abs(Forw_cal(:,1)+Refl_cal(:,1)),'--') */
  /*  xlabel('Samples');ylabel('Amplitude MV/m') */
  /*  title('After Calibration') */
  /*  legend({ 'Forward $\hat{V}_F$', 'Reflected $\hat{V}_R$', 'Probe $\hat{V}_P$','Virtual Probe $\hat{V}_F + \hat{V}_R$ '}, 'Orientation', 'vertical',... */
  /*      'Location', 'eastoutside') */
  /*  axis tight; box on */
  /*  ylim([min(ylim), 1.05*max(ylim)]) */
  /*  end */
  /*  print -dpng -r600 /home/anawaz/ThesisFigs/Basisc_Calibration_plot.png */
  /*  This is a calibration plot for the real and imag parts of the signals */
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
  /*  */
  /*      legend({ 'Probe', 'Forward', 'Reflected','Virtual Probe'}, 'Orientation', 'vertical',... */
  /*          'Location', 'eastoutside') */
  /*  */
  /*      subplot(2,1,2) */
  /*      set(gca, 'ColorOrder',  cbrewer('qual', 'Dark2', 4)) */
  /*  */
  /*      hold on */
  /*      plot(real(Probe(:,1))) */
  /*      plot(real(Forw_cal(:,1))) */
  /*      plot(real(Refl_cal(:,1))) */
  /*      plot(real(Forw_cal(:,1)+Refl_cal(:,1)),'r--') */
  /*  */
  /*      %legend('Virtual Probe', 'Probe', 'Forward', 'Reflected') */
  /*      ylabel('Amplitude MV/m') */
  /*      xlabel('Samples') */
  /*      title('After Calibration') */
  /*      legend({ 'Probe', 'Forward', 'Reflected','Virtual Probe'}, 'Orientation', 'vertical',... */
  /*          'Location', 'eastoutside') */
  /*      axis tight */
  /* end */
}

/*
 * File trailer for f_calibrateData.c
 *
 * [EOF]
 */
