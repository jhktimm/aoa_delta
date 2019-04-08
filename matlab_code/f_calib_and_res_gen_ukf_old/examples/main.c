/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 12-Mar-2019 13:34:27
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
#include "f_calib_and_res_gen_ukf.h"
#include "main.h"
#include "f_calib_and_res_gen_ukf_terminate.h"
#include "f_calib_and_res_gen_ukf_emxAPI.h"
#include "f_calib_and_res_gen_ukf_initialize.h"

/* Function Declarations */
static void argInit_4x1_real_T(double result[4]);
static emxArray_real_T *argInit_Unboundedx1_real_T(void);
static double argInit_real_T(void);
static void main_f_calib_and_res_gen_ukf(void);

/* Function Definitions */

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
static void main_f_calib_and_res_gen_ukf(void)
{
  emxArray_real_T *PA;
  emxArray_real_T *PP;
  emxArray_real_T *FA;
  emxArray_real_T *FP;
  emxArray_real_T *RA;
  emxArray_real_T *RP;
  double dv5[4];
  double dv6[4];
  double dv7[4];
  double residual_ukf[6];
  double residual_ukf_mean[6];
  double residual_ukf_Variance[12];
  creal_T cal_Coeff[4];

  /* Initialize function 'f_calib_and_res_gen_ukf' input arguments. */
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

  /* Initialize function input argument 'tau_m'. */
  /* Initialize function input argument 'K_m'. */
  /* Initialize function input argument 'X0'. */
  /* Call the entry-point 'f_calib_and_res_gen_ukf'. */
  argInit_4x1_real_T(dv5);
  argInit_4x1_real_T(dv6);
  argInit_4x1_real_T(dv7);
  f_calib_and_res_gen_ukf(PA, PP, FA, FP, RA, RP, argInit_real_T(),
    argInit_real_T(), dv5, dv6, dv7, argInit_real_T(), argInit_real_T(),
    argInit_real_T(), residual_ukf, residual_ukf_mean, residual_ukf_Variance,
    cal_Coeff);
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
  f_calib_and_res_gen_ukf_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_f_calib_and_res_gen_ukf();

  /* Terminate the application.
     You do not need to do this more than one time. */
  f_calib_and_res_gen_ukf_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
