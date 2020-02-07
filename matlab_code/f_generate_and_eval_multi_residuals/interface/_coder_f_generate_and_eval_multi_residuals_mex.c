/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_f_generate_and_eval_multi_residuals_mex.c
 *
 * Code generation for function '_coder_f_generate_and_eval_multi_residuals_mex'
 *
 */

/* Include files */
#include "_coder_f_generate_and_eval_multi_residuals_api.h"
#include "_coder_f_generate_and_eval_multi_residuals_mex.h"

/* Function Declarations */
static void c_f_generate_and_eval_multi_res(int32_T nlhs, mxArray *plhs[17],
  int32_T nrhs, const mxArray *prhs[24]);

/* Function Definitions */
static void c_f_generate_and_eval_multi_res(int32_T nlhs, mxArray *plhs[17],
  int32_T nrhs, const mxArray *prhs[24])
{
  int32_T n;
  const mxArray *inputs[24];
  const mxArray *outputs[17];
  int32_T b_nlhs;

  /* Check for proper number of arguments. */
  if (nrhs != 24) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 24, 4, 35, "f_generate_and_eval_multi_residuals");
  }

  if (nlhs > 17) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 35,
                        "f_generate_and_eval_multi_residuals");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  f_generate_and_eval_multi_residuals_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  f_generate_and_eval_multi_residuals_terminate();
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(f_generate_and_eval_multi_residuals_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  f_generate_and_eval_multi_residuals_initialize();

  /* Dispatch the entry-point. */
  c_f_generate_and_eval_multi_res(nlhs, plhs, nrhs, prhs);
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_f_generate_and_eval_multi_residuals_mex.c) */
