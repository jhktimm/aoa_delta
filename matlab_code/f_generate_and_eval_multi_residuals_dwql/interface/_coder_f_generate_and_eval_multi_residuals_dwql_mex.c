/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_f_generate_and_eval_multi_residuals_dwql_mex.c
 *
 * Code generation for function '_coder_f_generate_and_eval_multi_residuals_dwql_mex'
 *
 */

/* Include files */
#include "_coder_f_generate_and_eval_multi_residuals_dwql_mex.h"
#include "_coder_f_generate_and_eval_multi_residuals_dwql_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void c_f_generate_and_eval_multi_res(int32_T nlhs, mxArray
  *plhs[43], int32_T nrhs, const mxArray *prhs[29]);

/* Function Definitions */
void c_f_generate_and_eval_multi_res(int32_T nlhs, mxArray *plhs[43], int32_T
  nrhs, const mxArray *prhs[29])
{
  const mxArray *outputs[43];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 29) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 29, 4,
                        40, "f_generate_and_eval_multi_residuals_dwql");
  }

  if (nlhs > 43) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 40,
                        "f_generate_and_eval_multi_residuals_dwql");
  }

  /* Call the function. */
  f_generate_and_eval_multi_residuals_dwql_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(&f_generate_and_eval_multi_residuals_dwql_atexit);

  /* Module initialization. */
  f_generate_and_eval_multi_residuals_dwql_initialize();

  /* Dispatch the entry-point. */
  c_f_generate_and_eval_multi_res(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  f_generate_and_eval_multi_residuals_dwql_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_f_generate_and_eval_multi_residuals_dwql_mex.c) */
