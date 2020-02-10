/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals.h"
#include "main.h"
#include "f_generate_and_eval_multi_residuals_terminate.h"
#include "f_generate_and_eval_multi_residuals_emxAPI.h"
#include "f_generate_and_eval_multi_residuals_initialize.h"

/* Function Declarations */
static void argInit_2x1_real_T(double result[2]);
static void argInit_2x2_real_T(double result[4]);
static void argInit_4x1_creal_T(creal_T result[4]);
static void argInit_4x1_real_T(double result[4]);
static void argInit_6x6_real_T(double result[36]);
static emxArray_real_T *argInit_Unboundedx1_real_T(void);
static creal_T argInit_creal_T(void);
static double argInit_real_T(void);
static void main_f_generate_and_eval_multi_residuals(void);

/* Function Definitions */
static void argInit_2x1_real_T(double result[2])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static void argInit_2x2_real_T(double result[4])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    for (idx1 = 0; idx1 < 2; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + (idx1 << 1)] = argInit_real_T();
    }
  }
}

static void argInit_4x1_creal_T(creal_T result[4])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_creal_T();
  }
}

static void argInit_4x1_real_T(double result[4])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static void argInit_6x6_real_T(double result[36])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 6; idx0++) {
    for (idx1 = 0; idx1 < 6; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 6 * idx1] = argInit_real_T();
    }
  }
}

static emxArray_real_T *argInit_Unboundedx1_real_T(void)
{
  emxArray_real_T *result;
  static int iv0[1] = { 2 };

  int idx0;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real_T(1, iv0);

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[idx0] = argInit_real_T();
  }

  return result;
}

static creal_T argInit_creal_T(void)
{
  creal_T result;

  /* Set the value of the complex variable.
     Change this value to the value that the application requires. */
  result.re = argInit_real_T();
  result.im = argInit_real_T();
  return result;
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void main_f_generate_and_eval_multi_residuals(void)
{
  emxArray_real_T *s_max_UKF;
  emxArray_real_T *s_max_dw;
  emxArray_real_T *s_max_PS1;
  emxArray_real_T *res_PS2;
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  double FS;
  double F0;
  creal_T cal_coeff[4];
  double tau_m[4];
  double K_m[4];
  double X0[4];
  double QL_nom;
  emxArray_real_T *dw_trace_nom;
  double DELAY;
  double FILLING;
  double FLATTOP;
  double Sigma_nom_UKF[4];
  double r_mean_nom_UKF[2];
  double MeasNoiseVar[4];
  double ProcessVar[36];
  double Sigma_nom_dw;
  emxArray_real_T *r_PS1_nom;
  double classis_UKF;
  double classis_PS;
  double classis_dw;
  double strengthis_UKF;
  double strengthis_PS;
  double strengthis_dw;
  double QL;
  double dw_stat;
  double SP_F;
  double SP_P;
  double PC;
  double calib_check;
  double dec_hq;
  emxInitArray_real_T(&s_max_UKF, 1);
  emxInitArray_real_T(&s_max_dw, 1);
  emxInitArray_real_T(&s_max_PS1, 1);
  emxInitArray_real_T(&res_PS2, 1);

  /* Initialize function 'f_generate_and_eval_multi_residuals' input arguments. */
  /* Initialize function input argument 'PA'. */
  PA = argInit_Unboundedx1_real_T();

  /* Initialize function input argument 'PP'. */
  PP = argInit_Unboundedx1_real_T();

  /* Initialize function input argument 'FA'. */
  FA = argInit_Unboundedx1_real_T();

  /* Initialize function input argument 'FP'. */
  FP = argInit_Unboundedx1_real_T();

  /* Initialize function input argument 'RA'. */
  RA = argInit_Unboundedx1_real_T();

  /* Initialize function input argument 'RP'. */
  RP = argInit_Unboundedx1_real_T();
  FS = argInit_real_T();
  F0 = argInit_real_T();

  /* Initialize function input argument 'cal_coeff'. */
  argInit_4x1_creal_T(cal_coeff);

  /* Initialize function input argument 'tau_m'. */
  argInit_4x1_real_T(tau_m);

  /* Initialize function input argument 'K_m'. */
  argInit_4x1_real_T(K_m);

  /* Initialize function input argument 'X0'. */
  argInit_4x1_real_T(X0);
  QL_nom = argInit_real_T();

  /* Initialize function input argument 'dw_trace_nom'. */
  dw_trace_nom = argInit_Unboundedx1_real_T();
  DELAY = argInit_real_T();
  FILLING = argInit_real_T();
  FLATTOP = argInit_real_T();

  /* Initialize function input argument 'Sigma_nom_UKF'. */
  argInit_2x2_real_T(Sigma_nom_UKF);

  /* Initialize function input argument 'r_mean_nom_UKF'. */
  argInit_2x1_real_T(r_mean_nom_UKF);

  /* Initialize function input argument 'MeasNoiseVar'. */
  argInit_2x2_real_T(MeasNoiseVar);

  /* Initialize function input argument 'ProcessVar'. */
  argInit_6x6_real_T(ProcessVar);
  Sigma_nom_dw = argInit_real_T();

  /* Initialize function input argument 'r_PS1_nom'. */
  r_PS1_nom = argInit_Unboundedx1_real_T();

  /* Call the entry-point 'f_generate_and_eval_multi_residuals'. */
  f_generate_and_eval_multi_residuals(PA, PP, FA, FP, RA, RP, FS, F0, cal_coeff,
    tau_m, K_m, X0, QL_nom, dw_trace_nom, DELAY, FILLING, FLATTOP, Sigma_nom_UKF,
    r_mean_nom_UKF, MeasNoiseVar, ProcessVar, Sigma_nom_dw, r_PS1_nom,
    argInit_real_T(), s_max_UKF, s_max_dw, s_max_PS1, res_PS2, &classis_UKF,
    &classis_PS, &classis_dw, &strengthis_UKF, &strengthis_PS, &strengthis_dw,
    &QL, &dw_stat, &SP_F, &SP_P, &PC, &calib_check, &dec_hq);
  emxDestroyArray_real_T(res_PS2);
  emxDestroyArray_real_T(s_max_PS1);
  emxDestroyArray_real_T(s_max_dw);
  emxDestroyArray_real_T(s_max_UKF);
  emxDestroyArray_real_T(r_PS1_nom);
  emxDestroyArray_real_T(dw_trace_nom);
  emxDestroyArray_real_T(RP);
  emxDestroyArray_real_T(RA);
  emxDestroyArray_real_T(FP);
  emxDestroyArray_real_T(FA);
  emxDestroyArray_real_T(PP);
  emxDestroyArray_real_T(PA);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  f_generate_and_eval_multi_residuals_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_f_generate_and_eval_multi_residuals();

  /* Terminate the application.
     You do not need to do this more than one time. */
  f_generate_and_eval_multi_residuals_terminate();
  return 0;
}

/* End of code generation (main.c) */
