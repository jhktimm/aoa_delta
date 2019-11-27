/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_generate_and_eval_multi_residuals_mex.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Nov-2019 17:33:56
 */

/* Include Files */
#include "_coder_f_generate_and_eval_multi_residuals_api.h"
#include "_coder_f_generate_and_eval_multi_residuals_mex.h"

/* Function Declarations */
static void c_f_generate_and_eval_multi_res(int32_T nlhs, mxArray *plhs[17],
  int32_T nrhs, const mxArray *prhs[24]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[17]
 *                int32_T nrhs
 *                const mxArray *prhs[24]
 * Return Type  : void
 */
static void c_f_generate_and_eval_multi_res(int32_T nlhs, mxArray *plhs[17],
  int32_T nrhs, const mxArray *prhs[24])
{
  const mxArray *inputs[24];
  const mxArray *outputs[17];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 24) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 24, 4,
                        35, "f_generate_and_eval_multi_residuals");
  }

  if (nlhs > 17) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 35,
                        "f_generate_and_eval_multi_residuals");
  }

  /* Temporary copy for mex inputs. */
  if (0 <= nrhs - 1) {
    memcpy((void *)&inputs[0], (void *)&prhs[0], (uint32_T)(nrhs * (int32_T)
            sizeof(const mxArray *)));
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
  mexAtExit(f_generate_and_eval_multi_residuals_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  f_generate_and_eval_multi_residuals_initialize();

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
 * File trailer for _coder_f_generate_and_eval_multi_residuals_mex.c
 *
 * [EOF]
 */
