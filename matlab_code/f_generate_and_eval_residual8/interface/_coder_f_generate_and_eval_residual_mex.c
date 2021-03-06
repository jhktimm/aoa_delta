/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_generate_and_eval_residual_mex.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 16-Oct-2019 16:31:43
 */

/* Include Files */
#include "_coder_f_generate_and_eval_residual_api.h"
#include "_coder_f_generate_and_eval_residual_mex.h"

/* Function Declarations */
static void c_f_generate_and_eval_residual_(int32_T nlhs, mxArray *plhs[13],
  int32_T nrhs, const mxArray *prhs[20]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[13]
 *                int32_T nrhs
 *                const mxArray *prhs[20]
 * Return Type  : void
 */
static void c_f_generate_and_eval_residual_(int32_T nlhs, mxArray *plhs[13],
  int32_T nrhs, const mxArray *prhs[20])
{
  const mxArray *inputs[20];
  const mxArray *outputs[13];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 20) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 20, 4,
                        28, "f_generate_and_eval_residual");
  }

  if (nlhs > 13) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 28,
                        "f_generate_and_eval_residual");
  }

  /* Temporary copy for mex inputs. */
  if (0 <= nrhs - 1) {
    memcpy((void *)&inputs[0], (void *)&prhs[0], (uint32_T)(nrhs * (int32_T)
            sizeof(const mxArray *)));
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
  mexAtExit(f_generate_and_eval_residual_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  f_generate_and_eval_residual_initialize();

  /* Dispatch the entry-point. */
  c_f_generate_and_eval_residual_(nlhs, plhs, nrhs, prhs);
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
 * File trailer for _coder_f_generate_and_eval_residual_mex.c
 *
 * [EOF]
 */
