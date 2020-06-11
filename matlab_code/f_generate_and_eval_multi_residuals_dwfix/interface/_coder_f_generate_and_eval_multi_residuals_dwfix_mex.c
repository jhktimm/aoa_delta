/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_generate_and_eval_multi_residuals_dwfix_mex.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 11-Jun-2020 08:14:38
 */

/* Include Files */
#include "_coder_f_generate_and_eval_multi_residuals_dwfix_api.h"
#include "_coder_f_generate_and_eval_multi_residuals_dwfix_mex.h"

/* Function Declarations */
static void c_f_generate_and_eval_multi_res(int32_T nlhs, mxArray *plhs[44],
  int32_T nrhs, const mxArray *prhs[27]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[44]
 *                int32_T nrhs
 *                const mxArray *prhs[27]
 * Return Type  : void
 */
static void c_f_generate_and_eval_multi_res(int32_T nlhs, mxArray *plhs[44],
  int32_T nrhs, const mxArray *prhs[27])
{
  int32_T n;
  const mxArray *inputs[27];
  const mxArray *outputs[44];
  int32_T b_nlhs;

  /* Check for proper number of arguments. */
  if (nrhs != 27) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 27, 4, 41,
                        "f_generate_and_eval_multi_residuals_dwfix");
  }

  if (nlhs > 44) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 41,
                        "f_generate_and_eval_multi_residuals_dwfix");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  f_generate_and_eval_multi_residuals_dwfix_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  f_generate_and_eval_multi_residuals_dwfix_terminate();
}

/*
 * Arguments    : int32_T nlhs
 *                const mxArray * const plhs[]
 *                int32_T nrhs
 *                const mxArray * const prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(f_generate_and_eval_multi_residuals_dwfix_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  f_generate_and_eval_multi_residuals_dwfix_initialize();

  /* Dispatch the entry-point. */
  c_f_generate_and_eval_multi_res(nlhs, plhs, nrhs, prhs);
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/*
 * File trailer for _coder_f_generate_and_eval_multi_residuals_dwfix_mex.c
 *
 * [EOF]
 */
