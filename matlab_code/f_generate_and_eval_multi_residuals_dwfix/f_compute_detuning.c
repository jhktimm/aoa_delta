/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_compute_detuning.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals_dwfix.h"
#include "f_compute_detuning.h"
#include "f_generate_and_eval_multi_residuals_dwfix_emxutil.h"
#include "rdivide.h"
#include "power.h"
#include "abs.h"
#include "filter.h"

/* Function Definitions */

/*
 * y_mC_inter = interp1([0:1820-1],(y_mC),[0:0.1:1820-1],'makima');
 *  u_mC_inter = interp1([0:1820-1],(u_mC),[0:0.1:1820-1],'makima');
 *  [numOfSampl,numOfPulses] = size(y_mC_inter);
 *  f0 = 1.3e9;
 *  w12 = f0*pi./QL;
 *  w12 = repmat(w12, [numOfSampl,1]);
 *  dt = 0.1/fs ;
 *  smooth_span = 1;
 *  dVI_inter = zeros(numOfSampl, numOfPulses);
 *  dVQ_inter = zeros(numOfSampl, numOfPulses);
 *  %-------- Calculate w12 with the decay time--------------
 *
 *  %     for k = 1:numOfPulses
 *  %         dVI(:,k) = [0 ; diff(real(y_mC(:,k)))/dt];
 *  %         dVQ(:,k) = [0 ; diff(imag(y_mC(:,k)))/dt];
 *  %     end
 *  %
 *
 *  for k = 1:numOfPulses
 *      dVI_inter(:,k) = [filter(-smooth_diff(20),1,real(y_mC_inter(:,k)))/dt];
 *      dVQ_inter(:,k) = [filter(-smooth_diff(20),1,imag(y_mC_inter(:,k)))/dt];
 *  end
 *  dw1_inter = real(y_mC_inter).*(dVQ_inter - 2*w12.*imag(u_mC_inter))./abs(y_mC_inter).^2;
 *  dw2_inter = imag(y_mC_inter).*(2*w12.*real(u_mC_inter) - dVI_inter)./abs(y_mC_inter).^2;
 *
 *  dw_inter = zeros(numOfSampl, numOfPulses);
 *  for k = 1:numOfPulses
 *      dw_inter(:, k) = (dw1_inter(:,k) + dw2_inter(:,k));
 *  end
 *  figure(3),hold on,  plot(mean(dw_inter(2000:end,:),2))
 * if sum(sum(isnan(dVI)))> 0 || sum(sum(isnan(dVQ)))>0
 *     warning('the values of dw could not be calculated correctly!')
 * end
 * Arguments    : const emxArray_creal_T *y_mC
 *                const emxArray_creal_T *u_mC
 *                double fs
 *                double QL
 *                emxArray_real_T *dw
 * Return Type  : void
 */
void f_compute_detuning(const emxArray_creal_T *y_mC, const emxArray_creal_T
  *u_mC, double fs, double QL, emxArray_real_T *dw)
{
  emxArray_real_T *b_y_mC;
  double w12;
  unsigned int varargin_1_idx_0;
  double dt;
  int i28;
  int loop_ub;
  emxArray_real_T *A;
  emxArray_real_T *c_y_mC;
  emxArray_real_T *dw2;
  emxArray_real_T *r8;
  emxArray_real_T *r9;
  emxArray_real_T *r10;
  emxArray_real_T *d_y_mC;
  emxArray_real_T *dw1;
  emxArray_real_T *e_y_mC;
  emxInit_real_T1(&b_y_mC, 1);
  w12 = 4.0840704496667309E+9 / QL;
  varargin_1_idx_0 = (unsigned int)y_mC->size[0];
  dt = 1.0 / fs;

  /* smooth_span = 1; */
  /* dVI = zeros(numOfSampl, numOfPulses); */
  /* dVQ = zeros(numOfSampl, numOfPulses); */
  /* for k = 1:numOfPulses */
  i28 = b_y_mC->size[0];
  b_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)b_y_mC, i28, sizeof(double));
  loop_ub = y_mC->size[0];
  for (i28 = 0; i28 < loop_ub; i28++) {
    b_y_mC->data[i28] = y_mC->data[i28].re;
  }

  emxInit_real_T1(&A, 1);
  emxInit_real_T1(&c_y_mC, 1);
  filter(b_y_mC, A);
  i28 = c_y_mC->size[0];
  c_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)c_y_mC, i28, sizeof(double));
  loop_ub = y_mC->size[0];
  emxFree_real_T(&b_y_mC);
  for (i28 = 0; i28 < loop_ub; i28++) {
    c_y_mC->data[i28] = y_mC->data[i28].im;
  }

  emxInit_real_T1(&dw2, 1);
  emxInit_real_T(&r8, 2);
  filter(c_y_mC, dw2);

  /* end */
  /* framelen = 29; */
  /* order = 1; */
  /* dVI_s = sgolayfilt(dVI,order,framelen); */
  /* dVQ_s = sgolayfilt(dVQ,order,framelen); */
  /* dw1_s = real(y_mC).*(dVQ_s - 2*w12.*imag(u_mC))./abs(y_mC).^2; */
  /* dw2_s = imag(y_mC).*(2*w12.*real(u_mC) - dVI_s)./abs(y_mC).^2; */
  i28 = r8->size[0] * r8->size[1];
  r8->size[0] = (int)varargin_1_idx_0;
  r8->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)r8, i28, sizeof(double));
  loop_ub = (int)varargin_1_idx_0;
  emxFree_real_T(&c_y_mC);
  for (i28 = 0; i28 < loop_ub; i28++) {
    r8->data[i28] = 2.0 * w12;
  }

  emxInit_real_T1(&r9, 1);
  emxInit_real_T1(&r10, 1);
  emxInit_real_T1(&d_y_mC, 1);
  b_abs(y_mC, r9);
  power(r9, r10);
  i28 = d_y_mC->size[0];
  d_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)d_y_mC, i28, sizeof(double));
  loop_ub = y_mC->size[0];
  for (i28 = 0; i28 < loop_ub; i28++) {
    d_y_mC->data[i28] = y_mC->data[i28].re * (dw2->data[i28] / dt - r8->data[i28]
      * u_mC->data[i28].im);
  }

  emxInit_real_T1(&dw1, 1);
  rdivide(d_y_mC, r10, dw1);
  i28 = r8->size[0] * r8->size[1];
  r8->size[0] = (int)varargin_1_idx_0;
  r8->size[1] = 1;
  emxEnsureCapacity((emxArray__common *)r8, i28, sizeof(double));
  loop_ub = (int)varargin_1_idx_0;
  emxFree_real_T(&d_y_mC);
  for (i28 = 0; i28 < loop_ub; i28++) {
    r8->data[i28] = 2.0 * w12;
  }

  emxInit_real_T1(&e_y_mC, 1);
  b_abs(y_mC, r9);
  power(r9, r10);
  i28 = e_y_mC->size[0];
  e_y_mC->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)e_y_mC, i28, sizeof(double));
  loop_ub = y_mC->size[0];
  emxFree_real_T(&r9);
  for (i28 = 0; i28 < loop_ub; i28++) {
    e_y_mC->data[i28] = y_mC->data[i28].im * (r8->data[i28] * u_mC->data[i28].re
      - A->data[i28] / dt);
  }

  emxFree_real_T(&A);
  emxFree_real_T(&r8);
  rdivide(e_y_mC, r10, dw2);
  i28 = dw->size[0];
  dw->size[0] = y_mC->size[0];
  emxEnsureCapacity((emxArray__common *)dw, i28, sizeof(double));
  loop_ub = y_mC->size[0];
  emxFree_real_T(&e_y_mC);
  emxFree_real_T(&r10);
  for (i28 = 0; i28 < loop_ub; i28++) {
    dw->data[i28] = 0.0;
  }

  loop_ub = dw1->size[0] - 1;
  for (i28 = 0; i28 <= loop_ub; i28++) {
    dw->data[i28] = dw1->data[i28] + dw2->data[i28];
  }

  emxFree_real_T(&dw2);
  emxFree_real_T(&dw1);

  /*  dw_s(:, k) = (dw1_s(:,k) + dw2_s(:,k)); */
  /*  figure, */
  /*  hold on */
  /*  plot(dw(60:end,1),'k') */
  /* plot(dw_s(60:end,1),'r') */
  /*  */
  /* -----------Plot-------------- */
  /*      figure(555) */
  /*      hold on */
  /*      plot([1:1:length(dw)-1]*1e-6,dw(1:end-1)) */
  /*      xlabel('Time') */
  /*      ylabel('\Delta\omega') */
  /*  */
}

/*
 * File trailer for f_compute_detuning.c
 *
 * [EOF]
 */
