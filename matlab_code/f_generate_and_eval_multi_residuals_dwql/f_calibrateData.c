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
#include "f_calibrateData.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void f_calibrateData(const emxArray_creal_T *Forw, const emxArray_creal_T *Refl,
                     const creal_T cof22[4], emxArray_creal_T *Forw_cal,
                     emxArray_creal_T *Refl_cal)
{
  int i;
  int loop_ub;

  /* Initialize */
  i = Forw_cal->size[0];
  Forw_cal->size[0] = Forw->size[0];
  emxEnsureCapacity_creal_T(Forw_cal, i);
  loop_ub = Forw->size[0];
  for (i = 0; i < loop_ub; i++) {
    Forw_cal->data[i].re = 0.0;
    Forw_cal->data[i].im = 0.0;
  }

  i = Refl_cal->size[0];
  Refl_cal->size[0] = Forw->size[0];
  emxEnsureCapacity_creal_T(Refl_cal, i);
  loop_ub = Forw->size[0];
  for (i = 0; i < loop_ub; i++) {
    Refl_cal->data[i].re = 0.0;
    Refl_cal->data[i].im = 0.0;
  }

  /*  compute calibrated FORW and REFL signal */
  loop_ub = Forw_cal->size[0];
  for (i = 0; i < loop_ub; i++) {
    Forw_cal->data[i].re = (Forw->data[i].re * cof22[0].re - Forw->data[i].im *
      cof22[0].im) + (Refl->data[i].re * cof22[1].re - Refl->data[i].im * cof22
                      [1].im);
    Forw_cal->data[i].im = (Forw->data[i].re * cof22[0].im + Forw->data[i].im *
      cof22[0].re) + (Refl->data[i].re * cof22[1].im + Refl->data[i].im * cof22
                      [1].re);
  }

  loop_ub = Refl_cal->size[0];
  for (i = 0; i < loop_ub; i++) {
    Refl_cal->data[i].re = (Forw->data[i].re * cof22[2].re - Forw->data[i].im *
      cof22[2].im) + (Refl->data[i].re * cof22[3].re - Refl->data[i].im * cof22
                      [3].im);
    Refl_cal->data[i].im = (Forw->data[i].re * cof22[2].im + Forw->data[i].im *
      cof22[2].re) + (Refl->data[i].re * cof22[3].im + Refl->data[i].im * cof22
                      [3].re);
  }

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

/* End of code generation (f_calibrateData.c) */
