/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 15-Oct-2019 14:56:32
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
/* Include Files */
#include "rt_nonfinite.h"
#include "f_generate_and_eval_residual.h"
#include "main.h"
#include "f_generate_and_eval_residual_terminate.h"
#include "f_generate_and_eval_residual_emxAPI.h"
#include "f_generate_and_eval_residual_initialize.h"

/* Function Declarations */
static void argInit_2x1_real_T(double result[2]);
static void argInit_2x2_real_T(double result[4]);
static void argInit_4x1_creal_T(creal_T result[4]);
static void argInit_4x1_real_T(double result[4]);
static void argInit_6x6_real_T(double result[36]);
static emxArray_real_T *argInit_Unboundedx1_real_T(void);
static creal_T argInit_creal_T(void);
static double argInit_real_T(void);
static void main_f_generate_and_eval_residual(void);

/* Function Definitions */

/*
 * Arguments    : double result[2]
 * Return Type  : void
 */
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

/*
 * Arguments    : double result[4]
 * Return Type  : void
 */
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

/*
 * Arguments    : creal_T result[4]
 * Return Type  : void
 */
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

/*
 * Arguments    : double result[4]
 * Return Type  : void
 */
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

/*
 * Arguments    : double result[36]
 * Return Type  : void
 */
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

/*
 * Arguments    : void
 * Return Type  : emxArray_real_T *
 */
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

/*
 * Arguments    : void
 * Return Type  : creal_T
 */
static creal_T argInit_creal_T(void)
{
  creal_T result;

  /* Set the value of the complex variable.
     Change this value to the value that the application requires. */
  result.re = argInit_real_T();
  result.im = argInit_real_T();
  return result;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_f_generate_and_eval_residual(void)
{
  emxArray_real_T *s_max;
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  double FS;
  double F0;
  creal_T cal_coeff[4];
  double dv3[4];
  double dv4[4];
  double dv5[4];
  double dv6[4];
  double dv7[2];
  double dv8[4];
  double dv9[36];
  double classis;
  double strengthis;
  double strengtVar;
  double maxis;
  double minis;
  double QL;
  double dw_stat;
  double SP_F;
  double SP_P;
  double PC;
  double calib_check;
  double dec_hq;
  double dw_stat_nom;
  emxInitArray_real_T(&s_max, 1);

  /* Initialize function 'f_generate_and_eval_residual' input arguments. */
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
  /* Initialize function input argument 'K_m'. */
  /* Initialize function input argument 'X0'. */
  /* Initialize function input argument 'Sigma_nom'. */
  /* Initialize function input argument 'r_mean_nom'. */
  /* Initialize function input argument 'MeasNoiseVar'. */
  /* Initialize function input argument 'ProcessVar'. */
  /* Call the entry-point 'f_generate_and_eval_residual'. */
  argInit_4x1_real_T(dv3);
  argInit_4x1_real_T(dv4);
  argInit_4x1_real_T(dv5);
  argInit_2x2_real_T(dv6);
  argInit_2x1_real_T(dv7);
  argInit_2x2_real_T(dv8);
  argInit_6x6_real_T(dv9);
  f_generate_and_eval_residual(PA, PP, FA, FP, RA, RP, FS, F0, cal_coeff, dv3,
    dv4, dv5, argInit_real_T(), argInit_real_T(), argInit_real_T(),
    argInit_real_T(), dv6, dv7, dv8, dv9, s_max, &classis, &strengthis,
    &strengtVar, &maxis, &minis, &QL, &dw_stat, &SP_F, &SP_P, &PC, &calib_check,
    &dec_hq, &dw_stat_nom);
  emxDestroyArray_real_T(s_max);
  emxDestroyArray_real_T(RP);
  emxDestroyArray_real_T(RA);
  emxDestroyArray_real_T(FP);
  emxDestroyArray_real_T(FA);
  emxDestroyArray_real_T(PP);
  emxDestroyArray_real_T(PA);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  f_generate_and_eval_residual_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_f_generate_and_eval_residual();

  /* Terminate the application.
     You do not need to do this more than one time. */
  f_generate_and_eval_residual_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
