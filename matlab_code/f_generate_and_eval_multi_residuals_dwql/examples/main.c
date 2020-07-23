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
#include "main.h"
#include "f_generate_and_eval_multi_residuals_dwql.h"
#include "f_generate_and_eval_multi_residuals_dwql_emxAPI.h"
#include "f_generate_and_eval_multi_residuals_dwql_terminate.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void argInit_2x1_real_T(double result[2]);
static void argInit_2x2_real_T(double result[4]);
static void argInit_4x1_creal_T(creal_T result[4]);
static void argInit_4x1_real_T(double result[4]);
static void argInit_6x6_real_T(double result[36]);
static emxArray_real_T *argInit_Unboundedx1_real_T(void);
static creal_T argInit_creal_T(void);
static double argInit_real_T(void);
static void main_f_generate_and_eval_multi_residuals_dwql(void);

/* Function Definitions */
static void argInit_2x1_real_T(double result[2])
{
  double result_tmp;

  /* Loop over the array to initialize each element. */
  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result[0] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[1] = result_tmp;
}

static void argInit_2x2_real_T(double result[4])
{
  double result_tmp;

  /* Loop over the array to initialize each element. */
  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result[0] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[2] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[1] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[3] = result_tmp;
}

static void argInit_4x1_creal_T(creal_T result[4])
{
  creal_T result_tmp;

  /* Loop over the array to initialize each element. */
  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result_tmp = argInit_creal_T();
  result[0] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[1] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[2] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[3] = result_tmp;
}

static void argInit_4x1_real_T(double result[4])
{
  double result_tmp;

  /* Loop over the array to initialize each element. */
  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result[0] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[1] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[2] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[3] = result_tmp;
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
  static const int b_iv[1] = { 2 };

  int idx0;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real_T(1, b_iv);

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
  double re_tmp;

  /* Set the value of the complex variable.
     Change this value to the value that the application requires. */
  re_tmp = argInit_real_T();
  result.re = re_tmp;
  result.im = re_tmp;
  return result;
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void main_f_generate_and_eval_multi_residuals_dwql(void)
{
  emxArray_real_T *s_max_UKF;
  emxArray_real_T *s_max_UKF_dwfix;
  emxArray_real_T *s_max_dwql;
  emxArray_real_T *s_max_PS1;
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  double FS_tmp;
  emxArray_real_T *dwfix;
  emxArray_real_T *w12fix;
  double tau_m_tmp[4];
  double Sigma_nom_UKF_tmp[4];
  double r_mean_nom_UKF_dwfix_tmp[2];
  emxArray_real_T *r_PS1_nom;
  creal_T dcv[4];
  double dv[36];
  double classis_UKF;
  double classis_dwfix;
  double classis_PS;
  double classis_dwql;
  double strengthis_UKF;
  double strengthis_dwfix;
  double strengthis_PS;
  double strengthis_dwql;
  double max_UKF;
  double max_dwfix;
  double max_PS;
  double max_dwql;
  double median_UKF;
  double median_dwfix;
  double median_PS;
  double median_dwql;
  double mode_UKF;
  double mode_dwfix;
  double mode_PS;
  double mode_dwql;
  double var_UKF;
  double var_dwfix;
  double var_PS;
  double var_dwql;
  double rm_I;
  double rm_Q;
  double rm_I_dwfix;
  double rm_Q_dwfix;
  double rvar_1;
  double rvar_2;
  double rvar_3;
  double QL;
  double dw_stat;
  double SP_F;
  double SP_P;
  double PC;
  double calib_check;
  double dec_hq;
  double zpth;
  emxInitArray_real_T(&s_max_UKF, 1);
  emxInitArray_real_T(&s_max_UKF_dwfix, 1);
  emxInitArray_real_T(&s_max_dwql, 1);
  emxInitArray_real_T(&s_max_PS1, 1);

  /* Initialize function 'f_generate_and_eval_multi_residuals_dwql' input arguments. */
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
  FS_tmp = argInit_real_T();

  /* Initialize function input argument 'cal_coeff'. */
  /* Initialize function input argument 'dwfix'. */
  dwfix = argInit_Unboundedx1_real_T();

  /* Initialize function input argument 'w12fix'. */
  w12fix = argInit_Unboundedx1_real_T();

  /* Initialize function input argument 'tau_m'. */
  argInit_4x1_real_T(tau_m_tmp);

  /* Initialize function input argument 'K_m'. */
  /* Initialize function input argument 'X0'. */
  /* Initialize function input argument 'Sigma_nom_UKF'. */
  argInit_2x2_real_T(Sigma_nom_UKF_tmp);

  /* Initialize function input argument 'Sigma_nom_UKF_dwfix'. */
  /* Initialize function input argument 'r_mean_nom_UKF_dwfix'. */
  argInit_2x1_real_T(r_mean_nom_UKF_dwfix_tmp);

  /* Initialize function input argument 'r_mean_nom_UKF'. */
  /* Initialize function input argument 'MeasNoiseVar'. */
  /* Initialize function input argument 'ProcessVar'. */
  /* Initialize function input argument 'r_mean_nom_dwql'. */
  /* Initialize function input argument 'Sigma_nom_dwql'. */
  /* Initialize function input argument 'r_PS1_nom'. */
  r_PS1_nom = argInit_Unboundedx1_real_T();

  /* Call the entry-point 'f_generate_and_eval_multi_residuals_dwql'. */
  argInit_4x1_creal_T(dcv);
  argInit_6x6_real_T(dv);
  f_generate_and_eval_multi_residuals_dwql(PA, PP, FA, FP, RA, RP, FS_tmp,
    FS_tmp, dcv, dwfix, w12fix, tau_m_tmp, tau_m_tmp, tau_m_tmp, FS_tmp, FS_tmp,
    FS_tmp, FS_tmp, Sigma_nom_UKF_tmp, Sigma_nom_UKF_tmp,
    r_mean_nom_UKF_dwfix_tmp, r_mean_nom_UKF_dwfix_tmp, Sigma_nom_UKF_tmp, dv,
    FS_tmp, r_mean_nom_UKF_dwfix_tmp, Sigma_nom_UKF_tmp, r_PS1_nom, FS_tmp,
    s_max_UKF, s_max_UKF_dwfix, s_max_dwql, s_max_PS1, &classis_UKF,
    &classis_dwfix, &classis_PS, &classis_dwql, &strengthis_UKF,
    &strengthis_dwfix, &strengthis_PS, &strengthis_dwql, &max_UKF, &max_dwfix,
    &max_PS, &max_dwql, &median_UKF, &median_dwfix, &median_PS, &median_dwql,
    &mode_UKF, &mode_dwfix, &mode_PS, &mode_dwql, &var_UKF, &var_dwfix, &var_PS,
    &var_dwql, &rm_I, &rm_Q, &rm_I_dwfix, &rm_Q_dwfix, &rvar_1, &rvar_2, &rvar_3,
    &QL, &dw_stat, &SP_F, &SP_P, &PC, &calib_check, &dec_hq, &zpth);
  emxDestroyArray_real_T(s_max_PS1);
  emxDestroyArray_real_T(s_max_dwql);
  emxDestroyArray_real_T(s_max_UKF_dwfix);
  emxDestroyArray_real_T(s_max_UKF);
  emxDestroyArray_real_T(r_PS1_nom);
  emxDestroyArray_real_T(w12fix);
  emxDestroyArray_real_T(dwfix);
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

  /* The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_f_generate_and_eval_multi_residuals_dwql();

  /* Terminate the application.
     You do not need to do this more than one time. */
  f_generate_and_eval_multi_residuals_dwql_terminate();
  return 0;
}

/* End of code generation (main.c) */
