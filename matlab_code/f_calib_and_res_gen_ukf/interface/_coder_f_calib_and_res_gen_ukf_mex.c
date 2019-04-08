/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_f_calib_and_res_gen_ukf_mex.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 21-Mar-2019 13:36:35
 */

/* Include Files */
#include "_coder_f_calib_and_res_gen_ukf_api.h"
#include "_coder_f_calib_and_res_gen_ukf_mex.h"

/* Function Declarations */
static void c_f_calib_and_res_gen_ukf_mexFu(int32_T nlhs, mxArray *plhs[4],
  int32_T nrhs, const mxArray *prhs[14]);

/* Function Definitions */

/*
 * Arguments    : int32_T nlhs
 *                const mxArray *plhs[4]
 *                int32_T nrhs
 *                const mxArray *prhs[14]
 * Return Type  : void
 */
static void c_f_calib_and_res_gen_ukf_mexFu(int32_T nlhs, mxArray *plhs[4],
  int32_T nrhs, const mxArray *prhs[14])
{
  int32_T n;
  const mxArray *inputs[14];
  const mxArray *outputs[4];
  int32_T b_nlhs;

  /* Check for proper number of arguments. */
  if (nrhs != 14) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs",
                        5, 12, 14, 4, 23, "f_calib_and_res_gen_ukf");
  }

  if (nlhs > 4) {
    emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal,
                        "EMLRT:runTime:TooManyOutputArguments", 3, 4, 23,
                        "f_calib_and_res_gen_ukf");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
  }

  /* Call the function. */
  f_calib_and_res_gen_ukf_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  f_calib_and_res_gen_ukf_terminate();
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
  mexAtExit(f_calib_and_res_gen_ukf_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  f_calib_and_res_gen_ukf_initialize();

  /* Dispatch the entry-point. */
  c_f_calib_and_res_gen_ukf_mexFu(nlhs, plhs, nrhs, prhs);
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
 * File trailer for _coder_f_calib_and_res_gen_ukf_mex.c
 *
 * [EOF]
 */
