/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: f_generate_and_eval_multi_residuals_dwfix_types.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 16-Jun-2020 10:46:40
 */

#ifndef F_GENERATE_AND_EVAL_MULTI_RESIDUALS_DWFIX_TYPES_H
#define F_GENERATE_AND_EVAL_MULTI_RESIDUALS_DWFIX_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray__common
#define struct_emxArray__common

struct emxArray__common
{
  void *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray__common*/

#ifndef typedef_emxArray__common
#define typedef_emxArray__common

typedef struct emxArray__common emxArray__common;

#endif                                 /*typedef_emxArray__common*/

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_boolean_T*/

#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T

typedef struct emxArray_boolean_T emxArray_boolean_T;

#endif                                 /*typedef_emxArray_boolean_T*/

#ifndef struct_emxArray_creal_T
#define struct_emxArray_creal_T

struct emxArray_creal_T
{
  creal_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_creal_T*/

#ifndef typedef_emxArray_creal_T
#define typedef_emxArray_creal_T

typedef struct emxArray_creal_T emxArray_creal_T;

#endif                                 /*typedef_emxArray_creal_T*/

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef typedef_unscentedKalmanFilter
#define typedef_unscentedKalmanFilter

typedef struct {
  double Alpha;
  double Beta;
  double Kappa;
  double pState[6];
  double pStateCovariance[36];
  double pProcessNoise[36];
  double pMeasurementNoise[4];
  boolean_T pIsValidStateTransitionFcn;
  boolean_T pIsValidMeasurementFcn;
} unscentedKalmanFilter;

#endif                                 /*typedef_unscentedKalmanFilter*/

#ifndef typedef_unscentedKalmanFilter_1
#define typedef_unscentedKalmanFilter_1

typedef struct {
  double Alpha;
  double Beta;
  double Kappa;
  double pState[2];
  double pStateCovariance[4];
  double pProcessNoise[4];
  double pMeasurementNoise[4];
  boolean_T pIsValidStateTransitionFcn;
  boolean_T pIsValidMeasurementFcn;
} unscentedKalmanFilter_1;

#endif                                 /*typedef_unscentedKalmanFilter_1*/
#endif

/*
 * File trailer for f_generate_and_eval_multi_residuals_dwfix_types.h
 *
 * [EOF]
 */
