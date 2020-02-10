extern "C" {
#include "f_generate_and_eval_multi_residuals/abs.h"
#include "f_generate_and_eval_multi_residuals/calcSigmaPoints.h"
#include "f_generate_and_eval_multi_residuals/conv.h"
#include "f_generate_and_eval_multi_residuals/diff.h"
#include "f_generate_and_eval_multi_residuals/eps.h"
#include "f_generate_and_eval_multi_residuals/exp.h"
#include "f_generate_and_eval_multi_residuals/f_calibrateData.h"
#include "f_generate_and_eval_multi_residuals/f_cavitySystem.h"
#include "f_generate_and_eval_multi_residuals/f_compute_detuning.h"
#include "f_generate_and_eval_multi_residuals/f_compute_parity_Res1_full.h"
#include "f_generate_and_eval_multi_residuals/f_compute_parity_Res2_full.h"
#include "f_generate_and_eval_multi_residuals/f_computeQL.h"
#include "f_generate_and_eval_multi_residuals/f_compute_ukf_residual_not_pers.h"
#include "f_generate_and_eval_multi_residuals/f_generate_and_eval_multi_residuals_emxAPI.h"
#include "f_generate_and_eval_multi_residuals/f_generate_and_eval_multi_residuals_emxutil.h"
#include "f_generate_and_eval_multi_residuals/f_generate_and_eval_multi_residuals.h"
#include "f_generate_and_eval_multi_residuals/f_generate_and_eval_multi_residuals_initialize.h"
#include "f_generate_and_eval_multi_residuals/f_generate_and_eval_multi_residuals_rtwutil.h"
#include "f_generate_and_eval_multi_residuals/f_generate_and_eval_multi_residuals_terminate.h"
#include "f_generate_and_eval_multi_residuals/f_generate_and_eval_multi_residuals_types.h"
#include "f_generate_and_eval_multi_residuals/f_generate_online_parityRes1_full.h"
#include "f_generate_and_eval_multi_residuals/f_generate_online_parityRes2_full.h"
#include "f_generate_and_eval_multi_residuals/f_generate_online_UKF_residual_full.h"
#include "f_generate_and_eval_multi_residuals/f_GLT.h"
#include "f_generate_and_eval_multi_residuals/inv.h"
#include "f_generate_and_eval_multi_residuals/isSymmetricPositiveSemiDefinite.h"
#include "f_generate_and_eval_multi_residuals/mean.h"
#include "f_generate_and_eval_multi_residuals/mldivide.h"
#include "f_generate_and_eval_multi_residuals/power.h"
#include "f_generate_and_eval_multi_residuals/rdivide.h"
#include "f_generate_and_eval_multi_residuals/rtGetInf.h"
#include "f_generate_and_eval_multi_residuals/rtGetNaN.h"
#include "f_generate_and_eval_multi_residuals/rt_nonfinite.h"
#include "f_generate_and_eval_multi_residuals/rtwtypes.h"
#include "f_generate_and_eval_multi_residuals/sqrt.h"
#include "f_generate_and_eval_multi_residuals/sum.h"
#include "f_generate_and_eval_multi_residuals/svd.h"
#include "f_generate_and_eval_multi_residuals/UnscentedKalmanFilter1.h"
#include "f_generate_and_eval_multi_residuals/unscentedKalmanFilter.h"
#include "f_generate_and_eval_multi_residuals/xaxpy.h"
#include "f_generate_and_eval_multi_residuals/xdhseqr.h"
#include "f_generate_and_eval_multi_residuals/xdlanv2.h"
#include "f_generate_and_eval_multi_residuals/xdotc.h"
#include "f_generate_and_eval_multi_residuals/xgehrd.h"
#include "f_generate_and_eval_multi_residuals/xhseqr.h"
#include "f_generate_and_eval_multi_residuals/xnrm2.h"
#include "f_generate_and_eval_multi_residuals/xrotg.h"
#include "f_generate_and_eval_multi_residuals/xrot.h"
#include "f_generate_and_eval_multi_residuals/xscal.h"
#include "f_generate_and_eval_multi_residuals/xswap.h"
#include "f_generate_and_eval_multi_residuals/xzgeev.h"
#include "f_generate_and_eval_multi_residuals/xzhgeqz.h"
#include "f_generate_and_eval_multi_residuals/xzlarfg.h"
#include "f_generate_and_eval_multi_residuals/xzlartg.h"
}
