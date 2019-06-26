/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_f_generate_and_eval_residual_mex.c
 *
 * Code generation for function '_coder_f_generate_and_eval_residual_mex'
 *
 */

/* Include files */
#include "_coder_f_generate_and_eval_residual_api.h"
#include "_coder_f_generate_and_eval_residual_mex.h"

/* Function Declarations */
static void c_f_generate_and_eval_residual_(int32_T nlhs, mxArray *plhs[2],
  int32_T nrhs, const mxArray *prhs[20]);

/* Function Definitions */
static void c_f_generate_and_eval_residual_(int32_T nlhs, mxArray *plhs[2],
  int32_T nrhs, const mxArray *prhs[20])
{
  int32_T n;
  const mxArray *inputs[20];
  const mxArray *outputs[2];
  int32_T b_nlhs;

  /* Check for proper number of arguments. */
  if (nrhs != 20) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 20, 4, 28, "f_generate_and_eval_residual");
  }

  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 28,
                        "f_generate_and_eval_residual");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  f_generate_and_eval_residual_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  f_generate_and_eval_residual_terminate();
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(f_generate_and_eval_residual_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  f_generate_and_eval_residual_initialize();

  /* Dispatch the entry-point. */
  c_f_generate_and_eval_residual_(nlhs, plhs, nrhs, prhs);
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_f_generate_and_eval_residual_mex.c) */
