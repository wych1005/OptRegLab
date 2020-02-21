/*
 * helicopter3.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter3".
 *
 * Model version              : 1.186
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Fri Feb 21 16:06:47 2020
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter3.h"
#include "helicopter3_private.h"
#include "helicopter3_dt.h"

/* Block signals (auto storage) */
B_helicopter3_T helicopter3_B;

/* Continuous states */
X_helicopter3_T helicopter3_X;

/* Block states (auto storage) */
DW_helicopter3_T helicopter3_DW;

/* Real-time model */
RT_MODEL_helicopter3_T helicopter3_M_;
RT_MODEL_helicopter3_T *const helicopter3_M = &helicopter3_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter3_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter3_output(void)
{
  /* local block i/o variables */
  real_T rtb_Derivative;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_TmpSignalConversionAtK_tr_0;
  if (rtmIsMajorTimeStep(helicopter3_M)) {
    /* set solver stop time */
    if (!(helicopter3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter3_M->solverInfo,
                            ((helicopter3_M->Timing.clockTickH0 + 1) *
        helicopter3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter3_M->solverInfo,
                            ((helicopter3_M->Timing.clockTick0 + 1) *
        helicopter3_M->Timing.stepSize0 + helicopter3_M->Timing.clockTickH0 *
        helicopter3_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter3_M)) {
    helicopter3_M->Timing.t[0] = rtsiGetT(&helicopter3_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter3_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(helicopter3_DW.HILReadEncoderTimebase_Task,
        1, &helicopter3_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter3_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter3_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter3_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S5>/Travel: Count to rad' incorporates:
     *  Gain: '<S5>/Travel_gain'
     */
    helicopter3_B.TravelCounttorad = helicopter3_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter3_P.TravelCounttorad_Gain;

    /* Gain: '<S13>/Gain' */
    helicopter3_B.Gain = helicopter3_P.Gain_Gain *
      helicopter3_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter3_B.Sum3 = helicopter3_P.Constant_Value + helicopter3_B.Gain;

    /* Gain: '<S5>/Pitch: Count to rad' */
    helicopter3_B.PitchCounttorad = helicopter3_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopter3_B.Gain_i = helicopter3_P.Gain_Gain_a *
      helicopter3_B.PitchCounttorad;
  }

  /* Gain: '<S14>/Gain' incorporates:
   *  TransferFcn: '<S5>/Travel: Transfer Fcn'
   */
  helicopter3_B.Gain_d = (helicopter3_P.TravelTransferFcn_C *
    helicopter3_X.TravelTransferFcn_CSTATE + helicopter3_P.TravelTransferFcn_D *
    helicopter3_B.TravelCounttorad) * helicopter3_P.Gain_Gain_l;

  /* Gain: '<S11>/Gain' incorporates:
   *  TransferFcn: '<S5>/Pitch: Transfer Fcn'
   */
  helicopter3_B.Gain_b = (helicopter3_P.PitchTransferFcn_C *
    helicopter3_X.PitchTransferFcn_CSTATE + helicopter3_P.PitchTransferFcn_D *
    helicopter3_B.PitchCounttorad) * helicopter3_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter3_M)) {
    /* Gain: '<S5>/Elevation: Count to rad' incorporates:
     *  Gain: '<S5>/Elevation_gain'
     */
    helicopter3_B.ElevationCounttorad = helicopter3_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter3_P.ElevationCounttorad_Gain;

    /* Gain: '<S8>/Gain' */
    helicopter3_B.Gain_e = helicopter3_P.Gain_Gain_lv *
      helicopter3_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter3_B.Sum = helicopter3_B.Gain_e +
      helicopter3_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S5>/Elevation: Transfer Fcn'
   */
  helicopter3_B.Gain_dg = (helicopter3_P.ElevationTransferFcn_C *
    helicopter3_X.ElevationTransferFcn_CSTATE +
    helicopter3_P.ElevationTransferFcn_D * helicopter3_B.ElevationCounttorad) *
    helicopter3_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  helicopter3_B.Gain1[0] = helicopter3_P.Gain1_Gain * helicopter3_B.Sum3;
  helicopter3_B.Gain1[1] = helicopter3_P.Gain1_Gain * helicopter3_B.Gain_d;
  helicopter3_B.Gain1[2] = helicopter3_P.Gain1_Gain * helicopter3_B.Gain_i;
  helicopter3_B.Gain1[3] = helicopter3_P.Gain1_Gain * helicopter3_B.Gain_b;
  helicopter3_B.Gain1[4] = helicopter3_P.Gain1_Gain * helicopter3_B.Sum;
  helicopter3_B.Gain1[5] = helicopter3_P.Gain1_Gain * helicopter3_B.Gain_dg;

  /* FromWorkspace: '<S7>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *) helicopter3_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter3_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter3_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter3_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter3_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&helicopter3_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex];
              pDataValues += 141;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&helicopter3_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 141;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 4; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&helicopter3_B.FromWorkspace1[0])[elIdx] = (real_T) rtInterpolate
              (d1, d2, f1, f2);
            pDataValues += 141;
          }
        }
      }
    }
  }

  /* Sum: '<S7>/Sum6' */
  rtb_Derivative = helicopter3_B.Gain1[2] - helicopter3_B.FromWorkspace1[2];

  /* SignalConversion: '<Root>/TmpSignal ConversionAtK_transposedInport1' */
  rtb_TmpSignalConversionAtK_tr_0 = rtb_Derivative;

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helicopter3_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter3_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter3_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter3_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter3_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Derivative = pDataValues[currTimeIndex];
        } else {
          rtb_Derivative = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Derivative = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/K_transposed'
   *  Sum: '<S7>/Sum3'
   *  Sum: '<S7>/Sum5'
   *  Sum: '<S7>/Sum7'
   */
  helicopter3_B.Sum4 = rtb_Derivative - ((((helicopter3_B.Gain1[0] -
    helicopter3_B.FromWorkspace1[0]) * helicopter3_P.Klqr[0] +
    (helicopter3_B.Gain1[1] - helicopter3_B.FromWorkspace1[1]) *
    helicopter3_P.Klqr[1]) + helicopter3_P.Klqr[2] *
    rtb_TmpSignalConversionAtK_tr_0) + (helicopter3_B.Gain1[3] -
    helicopter3_B.FromWorkspace1[3]) * helicopter3_P.Klqr[3]);
  if (rtmIsMajorTimeStep(helicopter3_M)) {
    /* Constant: '<Root>/elevation_ref' */
    helicopter3_B.elevation_ref = helicopter3_P.elevation_ref_Value;

    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo WorkspaceInport1' */
    helicopter3_B.TmpSignalConversionAtToWorkspac[0] = helicopter3_B.Sum4;
    helicopter3_B.TmpSignalConversionAtToWorkspac[1] =
      helicopter3_B.elevation_ref;
    helicopter3_B.TmpSignalConversionAtToWorkspac[2] = helicopter3_B.Gain;
    helicopter3_B.TmpSignalConversionAtToWorkspac[3] = helicopter3_B.Gain_d;
    helicopter3_B.TmpSignalConversionAtToWorkspac[4] = helicopter3_B.Gain_i;
    helicopter3_B.TmpSignalConversionAtToWorkspac[5] = helicopter3_B.Gain_b;
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   */
  helicopter3_B.Sum1 = ((helicopter3_B.Sum4 - helicopter3_B.Gain1[2]) *
                        helicopter3_P.K_pp - helicopter3_P.K_pd *
                        helicopter3_B.Gain1[3]) + helicopter3_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter3_M)) {
  }

  /* Integrator: '<S4>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter3_X.Integrator_CSTATE >= helicopter3_P.Integrator_UpperSat) {
    helicopter3_X.Integrator_CSTATE = helicopter3_P.Integrator_UpperSat;
  } else {
    if (helicopter3_X.Integrator_CSTATE <= helicopter3_P.Integrator_LowerSat) {
      helicopter3_X.Integrator_CSTATE = helicopter3_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S4>/Sum' */
  rtb_Derivative = helicopter3_B.elevation_ref - helicopter3_B.Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S4>/K_ed'
   *  Gain: '<S4>/K_ep'
   *  Integrator: '<S4>/Integrator'
   *  Sum: '<S4>/Sum1'
   */
  helicopter3_B.Sum2 = ((helicopter3_P.K_ep * rtb_Derivative +
    helicopter3_X.Integrator_CSTATE) - helicopter3_P.K_ed * helicopter3_B.Gain1
                        [5]) + helicopter3_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter3_M)) {
    /* Gain: '<S3>/Gain1' */
    helicopter3_B.Gain1_b = helicopter3_P.Gain1_Gain_m * helicopter3_B.Gain_i;
  }

  /* Gain: '<S4>/K_ei' */
  helicopter3_B.K_ei = helicopter3_P.K_ei * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter3_M)) {
  }

  /* Derivative: '<S5>/Derivative' */
  if ((helicopter3_DW.TimeStampA >= helicopter3_M->Timing.t[0]) &&
      (helicopter3_DW.TimeStampB >= helicopter3_M->Timing.t[0])) {
    rtb_Derivative = 0.0;
  } else {
    rtb_TmpSignalConversionAtK_tr_0 = helicopter3_DW.TimeStampA;
    lastU = &helicopter3_DW.LastUAtTimeA;
    if (helicopter3_DW.TimeStampA < helicopter3_DW.TimeStampB) {
      if (helicopter3_DW.TimeStampB < helicopter3_M->Timing.t[0]) {
        rtb_TmpSignalConversionAtK_tr_0 = helicopter3_DW.TimeStampB;
        lastU = &helicopter3_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter3_DW.TimeStampA >= helicopter3_M->Timing.t[0]) {
        rtb_TmpSignalConversionAtK_tr_0 = helicopter3_DW.TimeStampB;
        lastU = &helicopter3_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter3_B.PitchCounttorad - *lastU) /
      (helicopter3_M->Timing.t[0] - rtb_TmpSignalConversionAtK_tr_0);
  }

  /* End of Derivative: '<S5>/Derivative' */

  /* Gain: '<S12>/Gain' */
  helicopter3_B.Gain_l = helicopter3_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter3_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_TmpSignalConversionAtK_tr_0 = (helicopter3_B.Sum2 - helicopter3_B.Sum1) *
    helicopter3_P.Backgain_Gain;

  /* Saturate: '<S5>/Back motor: Saturation' */
  if (rtb_TmpSignalConversionAtK_tr_0 >
      helicopter3_P.BackmotorSaturation_UpperSat) {
    helicopter3_B.BackmotorSaturation =
      helicopter3_P.BackmotorSaturation_UpperSat;
  } else if (rtb_TmpSignalConversionAtK_tr_0 <
             helicopter3_P.BackmotorSaturation_LowerSat) {
    helicopter3_B.BackmotorSaturation =
      helicopter3_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter3_B.BackmotorSaturation = rtb_TmpSignalConversionAtK_tr_0;
  }

  /* End of Saturate: '<S5>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter3_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_TmpSignalConversionAtK_tr_0 = (helicopter3_B.Sum1 + helicopter3_B.Sum2) *
    helicopter3_P.Frontgain_Gain;

  /* Saturate: '<S5>/Front motor: Saturation' */
  if (rtb_TmpSignalConversionAtK_tr_0 >
      helicopter3_P.FrontmotorSaturation_UpperSat) {
    helicopter3_B.FrontmotorSaturation =
      helicopter3_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_TmpSignalConversionAtK_tr_0 <
             helicopter3_P.FrontmotorSaturation_LowerSat) {
    helicopter3_B.FrontmotorSaturation =
      helicopter3_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter3_B.FrontmotorSaturation = rtb_TmpSignalConversionAtK_tr_0;
  }

  /* End of Saturate: '<S5>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter3_M)) {
    /* S-Function (hil_write_analog_block): '<S5>/HIL Write Analog' */

    /* S-Function Block: helicopter3/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter3_DW.HILWriteAnalog_Buffer[0] =
        helicopter3_B.FrontmotorSaturation;
      helicopter3_DW.HILWriteAnalog_Buffer[1] =
        helicopter3_B.BackmotorSaturation;
      result = hil_write_analog(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILWriteAnalog_channels, 2,
        &helicopter3_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
      }
    }

    /* SignalConversion: '<S7>/TmpSignal ConversionAtTo WorkspaceInport1' */
    helicopter3_B.TmpSignalConversionAtToWorksp_o[0] = helicopter3_B.Gain1[0];
    helicopter3_B.TmpSignalConversionAtToWorksp_o[4] =
      helicopter3_B.FromWorkspace1[0];
    helicopter3_B.TmpSignalConversionAtToWorksp_o[1] = helicopter3_B.Gain1[1];
    helicopter3_B.TmpSignalConversionAtToWorksp_o[5] =
      helicopter3_B.FromWorkspace1[1];
    helicopter3_B.TmpSignalConversionAtToWorksp_o[2] = helicopter3_B.Gain1[2];
    helicopter3_B.TmpSignalConversionAtToWorksp_o[6] =
      helicopter3_B.FromWorkspace1[2];
    helicopter3_B.TmpSignalConversionAtToWorksp_o[3] = helicopter3_B.Gain1[3];
    helicopter3_B.TmpSignalConversionAtToWorksp_o[7] =
      helicopter3_B.FromWorkspace1[3];
  }
}

/* Model update function */
void helicopter3_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S5>/Derivative' */
  if (helicopter3_DW.TimeStampA == (rtInf)) {
    helicopter3_DW.TimeStampA = helicopter3_M->Timing.t[0];
    lastU = &helicopter3_DW.LastUAtTimeA;
  } else if (helicopter3_DW.TimeStampB == (rtInf)) {
    helicopter3_DW.TimeStampB = helicopter3_M->Timing.t[0];
    lastU = &helicopter3_DW.LastUAtTimeB;
  } else if (helicopter3_DW.TimeStampA < helicopter3_DW.TimeStampB) {
    helicopter3_DW.TimeStampA = helicopter3_M->Timing.t[0];
    lastU = &helicopter3_DW.LastUAtTimeA;
  } else {
    helicopter3_DW.TimeStampB = helicopter3_M->Timing.t[0];
    lastU = &helicopter3_DW.LastUAtTimeB;
  }

  *lastU = helicopter3_B.PitchCounttorad;

  /* End of Update for Derivative: '<S5>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter3_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter3_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopter3_M->Timing.clockTick0)) {
    ++helicopter3_M->Timing.clockTickH0;
  }

  helicopter3_M->Timing.t[0] = rtsiGetSolverStopTime(&helicopter3_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter3_M->Timing.clockTick1)) {
      ++helicopter3_M->Timing.clockTickH1;
    }

    helicopter3_M->Timing.t[1] = helicopter3_M->Timing.clockTick1 *
      helicopter3_M->Timing.stepSize1 + helicopter3_M->Timing.clockTickH1 *
      helicopter3_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter3_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter3_T *_rtXdot;
  _rtXdot = ((XDot_helicopter3_T *) helicopter3_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter3_P.TravelTransferFcn_A *
    helicopter3_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter3_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter3_P.PitchTransferFcn_A *
    helicopter3_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter3_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter3_P.ElevationTransferFcn_A *
    helicopter3_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter3_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  lsat = (helicopter3_X.Integrator_CSTATE <= helicopter3_P.Integrator_LowerSat);
  usat = (helicopter3_X.Integrator_CSTATE >= helicopter3_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter3_B.K_ei > 0.0)) || (usat &&
       (helicopter3_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter3_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S4>/Integrator' */
}

/* Model initialize function */
void helicopter3_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter3_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter3_M, _rt_error_message);
      return;
    }

    if ((helicopter3_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helicopter3_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter3_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helicopter3_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter3_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter3_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_analog_input_chan, 8U,
        &helicopter3_DW.HILInitialize_AIMinimums[0],
        &helicopter3_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter3_P.HILInitialize_set_analog_output && !is_switching) ||
        (helicopter3_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter3_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helicopter3_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter3_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter3_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_analog_output_cha, 8U,
        &helicopter3_DW.HILInitialize_AOMinimums[0],
        &helicopter3_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter3_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helicopter3_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter3_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_analog_output_cha, 8U,
        &helicopter3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }

    if (helicopter3_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter3_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter3_DW.HILInitialize_Card,
         helicopter3_P.HILInitialize_analog_output_cha, 8U,
         &helicopter3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter3_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helicopter3_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter3_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter3_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_encoder_channels, 8U,
        (t_encoder_quadrature_mode *)
        &helicopter3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter3_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helicopter3_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter3_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter3_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_encoder_channels, 8U,
        &helicopter3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter3_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helicopter3_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter3_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter3_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter3_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &helicopter3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            helicopter3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopter3_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter3_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter3_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helicopter3_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter3_DW.HILInitialize_Card,
          &helicopter3_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helicopter3_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter3_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter3_DW.HILInitialize_Card,
          &helicopter3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter3_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter3_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &helicopter3_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter3_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter3_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter3_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helicopter3_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter3_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter3_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helicopter3_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter3_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter3_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_pwm_channels, 8U,
        &helicopter3_DW.HILInitialize_POSortedFreqs[0],
        &helicopter3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter3_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helicopter3_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter3_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter3_DW.HILInitialize_Card,
        helicopter3_P.HILInitialize_pwm_channels, 8U,
        &helicopter3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }

    if (helicopter3_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter3_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter3_DW.HILInitialize_Card,
         helicopter3_P.HILInitialize_pwm_channels, 8U,
         &helicopter3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopter3_DW.HILInitialize_Card,
      helicopter3_P.HILReadEncoderTimebase_samples_,
      helicopter3_P.HILReadEncoderTimebase_channels, 3,
      &helicopter3_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter3_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<S7>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413625279, 3.1262155534580049,
      3.1033093000299821, 3.0666274151912156, 3.014453922394225,
      2.9456562771176764, 2.8595077632937147, 2.7555515879654058,
      2.6335051104906526, 2.4931956060326308, 2.3345185760651095,
      2.1583782719260478, 1.967800077870473, 1.7674110445466207,
      1.5625810512761342, 1.3586839679386824, 1.1605920903248916,
      0.97235419679771251, 0.79695012325984027, 0.63643293374959031,
      0.49215959796927394, 0.36485729820996027, 0.25463993267205992,
      0.16109623593017905, 0.083400591252192985, 0.020423624533390517,
      -0.02916751281594173, -0.066823004653064941, -0.09403918530479391,
      -0.11230169021979587, -0.12304167596519089, -0.12760358353335186,
      -0.12722285379205733, -0.12301203948381056, -0.11595384747675899,
      -0.10689976340781566, -0.096573044536239674, -0.085575006872611561,
      -0.07439367354278649, -0.063413988602610077, -0.052928930978585739,
      -0.043150984592951386, -0.034223531491125961, -0.026231833998759245,
      -0.019213359191285462, -0.013167274288011302, -0.0080630053551753473,
      -0.0038478045493674511, -0.0004533138735937955, 0.0021988530036483617,
      0.0041924638884134032, 0.0056128908698021649, 0.006544125285162493,
      0.0070665002189294656, 0.0072550329904089864, 0.0071783005100552882,
      0.00689776339525422, 0.0064674596661119148, 0.005933995110177709,
      0.0053367645211473743, 0.0047083455725129364, 0.0040750147523033915,
      0.0034573422992259205, 0.0028708302460222221, 0.0023265643498006213,
      0.0018318567755375489, 0.001390861841342055, 0.0010051519083085054,
      0.00067424460561774189, 0.00039607604483589968, 0.00016741753288223541,
      -1.5764411858470834E-5, -0.00015800314738642174, -0.00026407916771299997,
      -0.00033881565345682892, -0.00038691781724583347, -0.00041285121080772679,
      -0.00042075405089002691, -0.00041437869183475569, -0.00039705758179327467,
      -0.00037168935026994572, -0.00034074105498252204, -0.0003062630387661212,
      -0.00026991328973278831, -0.00023298864146415997, -0.00019646057949526018,
      -0.00016101382346239443, -0.00012708622092749206, -9.4908810282185837E-5,
      -6.4545177863867975E-5, -3.5929439305404995E-5, -8.9023060705418331E-6,
      1.6755258848342908E-5, 4.129135336461343E-5, 6.4956154500282447E-5,
      8.7979679297890879E-5, 0.00011055569399486017, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048909061991,
      -0.046506351618091031, -0.091625013712091086, -0.14672753935506733,
      -0.20869397118796093, -0.2751905811061946, -0.34459405529584686,
      -0.415824701313235, -0.48818590989901212, -0.5612380178320886,
      -0.63470811987008435, -0.7045612165562456, -0.7623127762223002,
      -0.80155613329540876, -0.81931997308194571, -0.81558833334980674,
      -0.79236751045516307, -0.75295157410871638, -0.70161629415148907,
      -0.64206875804099994, -0.57709334312126559, -0.5092091990372547,
      -0.44086946215160139, -0.37417478696752343, -0.3107825787119442,
      -0.25190786687520988, -0.19836454939732898, -0.15062196734849284,
      -0.10886472260691589, -0.07305001966000782, -0.042959942981580138,
      -0.018247630272643787, 0.0015229189651780285, 0.0168432572329871,
      0.028232768028206259, 0.036216336275773316, 0.0413068754863039,
      0.043992150654512459, 0.04472533331930028, 0.04391873976070567,
      0.04194023049609736, 0.039111785542537414, 0.035709812407301686,
      0.031966789969466863, 0.028073899229895134, 0.024184339613096646,
      0.020417075731343822, 0.01686080322323158, 0.013577962703094623,
      0.01060866750896863, 0.007974443539060164, 0.0056817079255550469,
      0.0037249376614413117, 0.0020894997350678914, 0.00075413108591808364,
      -0.00030692992141479413, -0.0011221484592042685, -0.0017212149165692209,
      -0.0021338582237368222, -0.0023889223561213389, -0.0025136757945377524,
      -0.0025333232808381796, -0.0024706898123098824, -0.0023460482128147934,
      -0.0021770635848864035, -0.0019788302970522894, -0.001763979736781975,
      -0.0015428397321341982, -0.0013236292107630539, -0.0011126742431273691,
      -0.000914634047814657, -0.000732727778962825, -0.0005689549421118036,
      -0.00042430408130631278, -0.000298945942975316, -0.00019240865515601812,
      -0.00010373357424757338, -3.1611360329200294E-5, 2.5501436221085026E-5,
      6.9284440165923956E-5, 0.00010147292609331567, 0.00012379318114969477,
      0.00013791206486560344, 0.00014539899613333143, 0.00014769859307451339,
      0.00014611224787559922, 0.000141787024131463, 0.00013571041013960949,
      0.00012870964258122485, 0.00012145452967327145, 0.0001144629542338519,
      0.00010810853293945266, 0.00010263025967553898, 9.8144378065082063E-5,
      9.4659204542676067E-5, 9.2094099190433742E-5, 9.0304058787877162E-5,
      8.9110958714119383E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.10602875205861005, 0.22266037932307303, 0.31888147181624232,
      0.38944360631121483, 0.43795507377648213, 0.46997264230352054,
      0.49051724877497993, 0.50343100141409236, 0.51142138585938279,
      0.51630439857559973, 0.5192586212675202, 0.49369500885904027,
      0.40816596705876146, 0.27735705984392089, 0.12554803518857222,
      -0.026373804426941632, -0.16411590764817865, -0.27857678423584414,
      -0.36281815260289818, -0.42085924264294028, -0.45922141703380021,
      -0.47977920385573458, -0.482999159776279, -0.47137249195678604,
      -0.44803191699491929, -0.41610397764324636, -0.37842371849810486,
      -0.33742633592109811, -0.29512425777261325, -0.253124641962517,
      -0.21266516986452461, -0.17465718802102481, -0.13973069118134343,
      -0.10827829968414159, -0.08049671238211295, -0.056424811263810673,
      -0.035977986944966428, -0.018978499319992542, -0.0051818550552452328,
      0.005700695215347577, 0.013983347843646937, 0.019990368682992504,
      0.024043846827354092, 0.026454253043480886, 0.027513464961974848,
      0.027489921858446682, 0.026625582310723317, 0.025134375864333876,
      0.023201863003346493, 0.020985844389337639, 0.018617688948044882,
      0.016204179667314449, 0.013829704890780049, 0.01155865065190864,
      0.0094378756039130152, 0.0074991739560053864, 0.0057616532742171466,
      0.0042339729232725156, 0.002916405297005134, 0.001802695872782176,
      0.00088170965649384827, 0.00013886092934043117, -0.00044266943438280059,
      -0.00088091922171180807, -0.0011943188110467248, -0.0014010371685183717,
      -0.0015184817035754474, -0.0015629330943505802, -0.0015492962434657846,
      -0.0014909491426511206, -0.0013996724643236189, -0.0012856440340190628,
      -0.0011574838622158488, -0.0010223370386524668, -0.0008859834445411937,
      -0.000752964861244103, -0.00062672160478955167, -0.00050973226282778118,
      -0.00040365143331496246, -0.00030944155013681613, -0.00022749592500501104,
      -0.00015775103811508149, -9.9786877774685765E-5, -5.291477076749646E-5,
      -1.625267291083392E-5, 1.1211682003878463E-5, 3.0569029520228667E-5,
      4.2947186894513517E-5, 4.9478751347061014E-5, 5.1276367137421262E-5,
      4.941378496089933E-5, 4.4910622807850582E-5, 3.8718343149644846E-5,
      3.1704497960415822E-5, 2.4631875387714809E-5, 1.8129184956384733E-5,
      1.2651321907297637E-5, 8.4323756487128E-6, 5.4485883366234407E-6, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823444021,
      0.46652650905785192, 0.38488436997267728, 0.28224853797988991,
      0.19404586986106923, 0.12807027410815364, 0.082178425885837569,
      0.051655010556449658, 0.031961537781161641, 0.019532050864867839,
      0.011816890767682161, -0.1022544496339198, -0.34211616720111521,
      -0.52323562885936215, -0.60723609862139483, -0.60768735846205535,
      -0.550968412884948, -0.457843506350662, -0.33696547346821631,
      -0.23216436016016817, -0.1534486975634396, -0.082231147287737547,
      -0.012879823682177601, 0.046506671277971624, 0.093362299847467134,
      0.12771175740669169, 0.15072103658056604, 0.16398953030802704,
      0.16920831259393948, 0.16799846324038509, 0.16183788839196961,
      0.15203192737399915, 0.1397059873587255, 0.12580956598880741,
      0.11112634920811452, 0.096287604473209137, 0.081787297275377,
      0.067997950499895557, 0.055186577058989238, 0.043530201082371239,
      0.033130610513197434, 0.024028083357382258, 0.016213912577446362,
      0.0096416248645071773, 0.0042368476739758484, -9.4172414112660469E-5,
      -0.0034573581908934627, -0.0059648257855577638, -0.0077300514439495255,
      -0.00886407445603541, -0.009472621765171026, -0.009654037122921743,
      -0.0094978991061375959, -0.0090842169554856342, -0.0084831001919825049,
      -0.0077548065916305106, -0.0069500827271529574, -0.0061107214037785258,
      -0.0052702705050695258, -0.0044548376968918321, -0.0036839448651533112,
      -0.0029713949086136683, -0.0023261214548929272, -0.00175299914931603,
      -0.0012535983573396673, -0.0008268734298865878, -0.00046977814022830267,
      -0.00017780556310053165, 5.4547403539183139E-5, 0.00023338840325865505,
      0.00036510671331000749, 0.00045611372121822372, 0.00051264068721285571,
      0.00054058729425352761, 0.00054541437644509258, 0.00053207433318836254,
      0.00050497302581820546, 0.00046795736784708175, 0.000424323318051275,
      0.00037683953271258548, 0.0003277825005272203, 0.00027897954755971816,
      0.00023185664136158289, 0.00018748842802875722, 0.00014664839142665016,
      0.00010985741965884953, 7.7429390065400817E-5, 4.95126294971394E-5,
      2.6126257810189979E-5, 7.1904631614409744E-6, -7.4503287060877071E-6,
      -1.8012648612194989E-5, -2.4769118632822942E-5, -2.8055380756916093E-5,
      -2.8290490290804048E-5, -2.6010761725320305E-5, -2.1911452196348387E-5,
      -1.687578503433935E-5, -1.1935149248357439E-5, -8.023739200293113E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0 } ;

    helicopter3_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter3_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter3_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559807444,
      0.52359877559803447, 0.52359877559798307, 0.52359877559791523,
      0.523598775597823, 0.5235987755976923, 0.52359877559749723,
      0.52359877559718215, 0.5235987755966055, 0.52359877559526735,
      0.52359877558925361, 0.38860546189573797, 0.10951698887526927,
      -0.11003833946102218, -0.2769112375529158, -0.39790682731646904,
      -0.47963675127901123, -0.523591909441963, -0.52359877534342569,
      -0.52359877536343258, -0.5235987224145312, -0.50343489391626572,
      -0.46497044043306424, -0.42077345861352539, -0.37347862555446426,
      -0.32522986550994037, -0.27772344682220707, -0.23225530276673961,
      -0.18977018817324465, -0.15091074088283749, -0.11606494657763654,
      -0.085410890684983393, -0.0589580160110362, -0.036584388943327391,
      -0.018069712651425169, -0.0031240162861197467, 0.0085879009858575318,
      0.017426078578606431, 0.023758780967378868, 0.027949332008985632,
      0.030346034333594656, 0.031274796827770436, 0.031034093821064389,
      0.029891891654304281, 0.02808419891071845, 0.025814923189764534,
      0.023256747740391891, 0.020552773751695549, 0.017818707168261894,
      0.015145401405518491, 0.012601598411287867, 0.010236739517233147,
      0.008083744017371523, 0.0061616771427812694, 0.0044782499569109855,
      0.0030321116735972068, 0.0018149100878760917, 0.00081310836210016278,
      9.5565276842163957E-6, -0.00061517602288165712, -0.0010816948208518147,
      -0.001410884895240463, -0.0016232063484833868, -0.001738160063038257,
      -0.0017739020793310282, -0.001746985387332328, -0.0016722086841820876,
      -0.0015625529081204719, -0.0014291879259837976, -0.0012815335105175721,
      -0.00112736059780635, -0.00097292068600022814, -0.00082309306297666371,
      -0.00068154128644839368, -0.00055087195231493544, -0.00043279025403042577,
      -0.00032824814515925637, -0.00023758206462032359, -0.00016063817112712338,
      -9.6883866645734235E-5, -4.550507867797261E-5, -5.4893309923763985E-6,
      2.4304922656237212E-5, 4.5091880270843148E-5, 5.811379953861603E-5,
      6.460693357347208E-5, 6.5776522273753584E-5, 6.2779201128075162E-5,
      5.6710998483779338E-5, 4.8598837981454231E-5, 3.939310317146619E-5,
      2.9958323012006171E-5, 2.1058409934228412E-5, 1.3332266149043421E-5,
      7.25543918037023E-6, 3.0850995699961848E-6, 7.9190498794152728E-7,
      -4.05937442205473E-17, -1.5332144814809975E-17, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 } ;

    helicopter3_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter3_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter3_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  helicopter3_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  helicopter3_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  helicopter3_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  helicopter3_X.Integrator_CSTATE = helicopter3_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S5>/Derivative' */
  helicopter3_DW.TimeStampA = (rtInf);
  helicopter3_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter3_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter3_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter3_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helicopter3_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter3_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter3_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helicopter3_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter3_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter3_DW.HILInitialize_Card
                         , helicopter3_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter3_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter3_DW.HILInitialize_AOVoltages[0]
                         , &helicopter3_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter3_DW.HILInitialize_Card,
            helicopter3_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs, &helicopter3_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter3_DW.HILInitialize_Card,
            helicopter3_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helicopter3_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter3_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter3_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter3_DW.HILInitialize_Card);
    hil_close(helicopter3_DW.HILInitialize_Card);
    helicopter3_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter3_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter3_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter3_initialize();
}

void MdlTerminate(void)
{
  helicopter3_terminate();
}

/* Registration function */
RT_MODEL_helicopter3_T *helicopter3(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter3_P.Integrator_UpperSat = rtInf;
  helicopter3_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter3_M, 0,
                sizeof(RT_MODEL_helicopter3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter3_M->solverInfo,
                          &helicopter3_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter3_M->solverInfo, &rtmGetTPtr(helicopter3_M));
    rtsiSetStepSizePtr(&helicopter3_M->solverInfo,
                       &helicopter3_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter3_M->solverInfo, &helicopter3_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter3_M->solverInfo, (real_T **)
                         &helicopter3_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter3_M->solverInfo,
      &helicopter3_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter3_M->solverInfo,
      &helicopter3_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter3_M->solverInfo,
      &helicopter3_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter3_M->solverInfo,
      &helicopter3_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter3_M->solverInfo, (&rtmGetErrorStatus
      (helicopter3_M)));
    rtsiSetRTModelPtr(&helicopter3_M->solverInfo, helicopter3_M);
  }

  rtsiSetSimTimeStep(&helicopter3_M->solverInfo, MAJOR_TIME_STEP);
  helicopter3_M->ModelData.intgData.f[0] = helicopter3_M->ModelData.odeF[0];
  helicopter3_M->ModelData.contStates = ((real_T *) &helicopter3_X);
  rtsiSetSolverData(&helicopter3_M->solverInfo, (void *)
                    &helicopter3_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter3_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter3_M->Timing.sampleTimes = (&helicopter3_M->
      Timing.sampleTimesArray[0]);
    helicopter3_M->Timing.offsetTimes = (&helicopter3_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter3_M->Timing.sampleTimes[0] = (0.0);
    helicopter3_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter3_M->Timing.offsetTimes[0] = (0.0);
    helicopter3_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter3_M, &helicopter3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter3_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter3_M, -1);
  helicopter3_M->Timing.stepSize0 = 0.002;
  helicopter3_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter3_M->Sizes.checksums[0] = (16407450U);
  helicopter3_M->Sizes.checksums[1] = (1269378406U);
  helicopter3_M->Sizes.checksums[2] = (2424257702U);
  helicopter3_M->Sizes.checksums[3] = (2384276355U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter3_M->extModeInfo,
      &helicopter3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter3_M->extModeInfo,
                        helicopter3_M->Sizes.checksums);
    rteiSetTPtr(helicopter3_M->extModeInfo, rtmGetTPtr(helicopter3_M));
  }

  helicopter3_M->solverInfoPtr = (&helicopter3_M->solverInfo);
  helicopter3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter3_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter3_M->ModelData.blockIO = ((void *) &helicopter3_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter3_B.Gain1[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      helicopter3_B.TmpSignalConversionAtToWorkspac[i] = 0.0;
    }

    for (i = 0; i < 8; i++) {
      helicopter3_B.TmpSignalConversionAtToWorksp_o[i] = 0.0;
    }

    helicopter3_B.TravelCounttorad = 0.0;
    helicopter3_B.Gain = 0.0;
    helicopter3_B.Sum3 = 0.0;
    helicopter3_B.Gain_d = 0.0;
    helicopter3_B.PitchCounttorad = 0.0;
    helicopter3_B.Gain_i = 0.0;
    helicopter3_B.Gain_b = 0.0;
    helicopter3_B.ElevationCounttorad = 0.0;
    helicopter3_B.Gain_e = 0.0;
    helicopter3_B.Sum = 0.0;
    helicopter3_B.Gain_dg = 0.0;
    helicopter3_B.FromWorkspace1[0] = 0.0;
    helicopter3_B.FromWorkspace1[1] = 0.0;
    helicopter3_B.FromWorkspace1[2] = 0.0;
    helicopter3_B.FromWorkspace1[3] = 0.0;
    helicopter3_B.Sum4 = 0.0;
    helicopter3_B.elevation_ref = 0.0;
    helicopter3_B.Sum1 = 0.0;
    helicopter3_B.Sum2 = 0.0;
    helicopter3_B.Gain1_b = 0.0;
    helicopter3_B.K_ei = 0.0;
    helicopter3_B.Gain_l = 0.0;
    helicopter3_B.BackmotorSaturation = 0.0;
    helicopter3_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter3_M->ModelData.defaultParam = ((real_T *)&helicopter3_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter3_X;
    helicopter3_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter3_X, 0,
                  sizeof(X_helicopter3_T));
  }

  /* states (dwork) */
  helicopter3_M->ModelData.dwork = ((void *) &helicopter3_DW);
  (void) memset((void *)&helicopter3_DW, 0,
                sizeof(DW_helicopter3_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter3_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter3_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter3_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter3_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter3_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter3_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter3_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter3_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter3_DW.TimeStampA = 0.0;
  helicopter3_DW.LastUAtTimeA = 0.0;
  helicopter3_DW.TimeStampB = 0.0;
  helicopter3_DW.LastUAtTimeB = 0.0;
  helicopter3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter3_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter3_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter3_M->Sizes.numY = (0);     /* Number of model outputs */
  helicopter3_M->Sizes.numU = (0);     /* Number of model inputs */
  helicopter3_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter3_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter3_M->Sizes.numBlocks = (72);/* Number of blocks */
  helicopter3_M->Sizes.numBlockIO = (24);/* Number of block outputs */
  helicopter3_M->Sizes.numBlockPrms = (149);/* Sum of parameter "widths" */
  return helicopter3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
