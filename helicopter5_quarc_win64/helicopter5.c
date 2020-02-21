/*
 * helicopter5.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter5".
 *
 * Model version              : 1.187
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Fri Feb 21 15:30:09 2020
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter5.h"
#include "helicopter5_private.h"
#include "helicopter5_dt.h"

/* Block signals (auto storage) */
B_helicopter5_T helicopter5_B;

/* Continuous states */
X_helicopter5_T helicopter5_X;

/* Block states (auto storage) */
DW_helicopter5_T helicopter5_DW;

/* Real-time model */
RT_MODEL_helicopter5_T helicopter5_M_;
RT_MODEL_helicopter5_T *const helicopter5_M = &helicopter5_M_;

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
  helicopter5_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter5_output(void)
{
  /* local block i/o variables */
  real_T rtb_FromWorkspace[2];
  real_T rtb_TmpSignalConversionAtK_tran[6];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_Sum4[2];
  int32_T i;
  int32_T i_0;
  real_T tmp;
  real_T rtb_Gain1_idx_2;
  real_T rtb_Gain1_idx_3;
  real_T rtb_Gain1_idx_4;
  real_T rtb_Gain1_idx_5;
  if (rtmIsMajorTimeStep(helicopter5_M)) {
    /* set solver stop time */
    if (!(helicopter5_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter5_M->solverInfo,
                            ((helicopter5_M->Timing.clockTickH0 + 1) *
        helicopter5_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter5_M->solverInfo,
                            ((helicopter5_M->Timing.clockTick0 + 1) *
        helicopter5_M->Timing.stepSize0 + helicopter5_M->Timing.clockTickH0 *
        helicopter5_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter5_M)) {
    helicopter5_M->Timing.t[0] = rtsiGetT(&helicopter5_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter5_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter5/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(helicopter5_DW.HILReadEncoderTimebase_Task,
        1, &helicopter5_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter5_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter5_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter5_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter5_B.TravelCounttorad = helicopter5_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter5_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter5_B.Gain = helicopter5_P.Gain_Gain *
      helicopter5_B.TravelCounttorad;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter5_B.PitchCounttorad = helicopter5_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter5_B.Gain_i = helicopter5_P.Gain_Gain_a *
      helicopter5_B.PitchCounttorad;
  }

  /* Gain: '<S13>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter5_B.Gain_d = (helicopter5_P.TravelTransferFcn_C *
    helicopter5_X.TravelTransferFcn_CSTATE + helicopter5_P.TravelTransferFcn_D *
    helicopter5_B.TravelCounttorad) * helicopter5_P.Gain_Gain_l;

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter5_B.Gain_b = (helicopter5_P.PitchTransferFcn_C *
    helicopter5_X.PitchTransferFcn_CSTATE + helicopter5_P.PitchTransferFcn_D *
    helicopter5_B.PitchCounttorad) * helicopter5_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter5_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo WorkspaceInport1' */
    helicopter5_B.TmpSignalConversionAtToWorkspac[0] = 0.0;
    helicopter5_B.TmpSignalConversionAtToWorkspac[1] = 0.0;
    helicopter5_B.TmpSignalConversionAtToWorkspac[2] = helicopter5_B.Gain;
    helicopter5_B.TmpSignalConversionAtToWorkspac[3] = helicopter5_B.Gain_d;
    helicopter5_B.TmpSignalConversionAtToWorkspac[4] = helicopter5_B.Gain_i;
    helicopter5_B.TmpSignalConversionAtToWorkspac[5] = helicopter5_B.Gain_b;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter5_B.Sum3 = helicopter5_P.Constant_Value + helicopter5_B.Gain;

    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter5_B.ElevationCounttorad = helicopter5_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter5_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopter5_B.Gain_e = helicopter5_P.Gain_Gain_lv *
      helicopter5_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter5_B.Sum = helicopter5_B.Gain_e +
      helicopter5_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter5_B.Gain_dg = (helicopter5_P.ElevationTransferFcn_C *
    helicopter5_X.ElevationTransferFcn_CSTATE +
    helicopter5_P.ElevationTransferFcn_D * helicopter5_B.ElevationCounttorad) *
    helicopter5_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1_idx_2 = helicopter5_P.Gain1_Gain * helicopter5_B.Gain_i;
  rtb_Gain1_idx_3 = helicopter5_P.Gain1_Gain * helicopter5_B.Gain_b;
  rtb_Gain1_idx_4 = helicopter5_P.Gain1_Gain * helicopter5_B.Sum;
  rtb_Gain1_idx_5 = helicopter5_P.Gain1_Gain * helicopter5_B.Gain_dg;

  /* FromWorkspace: '<S6>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *) helicopter5_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter5_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter5_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter5_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[180]) {
      currTimeIndex = 179;
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

    helicopter5_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_TmpSignalConversionAtK_tran[0])[elIdx] =
                pDataValues[currTimeIndex];
              pDataValues += 181;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_TmpSignalConversionAtK_tran[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 181;
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
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_TmpSignalConversionAtK_tran[0])[elIdx] = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 181;
          }
        }
      }
    }
  }

  /* SignalConversion: '<Root>/TmpSignal ConversionAtK_transposedInport1' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Sum: '<S6>/Sum1'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   *  Sum: '<S6>/Sum5'
   *  Sum: '<S6>/Sum6'
   *  Sum: '<S6>/Sum7'
   */
  rtb_TmpSignalConversionAtK_tran[0] = helicopter5_P.Gain1_Gain *
    helicopter5_B.Sum3 - rtb_TmpSignalConversionAtK_tran[0];
  rtb_TmpSignalConversionAtK_tran[1] = helicopter5_P.Gain1_Gain *
    helicopter5_B.Gain_d - rtb_TmpSignalConversionAtK_tran[1];
  rtb_TmpSignalConversionAtK_tran[2] = rtb_Gain1_idx_2 -
    rtb_TmpSignalConversionAtK_tran[2];
  rtb_TmpSignalConversionAtK_tran[3] = rtb_Gain1_idx_3 -
    rtb_TmpSignalConversionAtK_tran[3];
  rtb_TmpSignalConversionAtK_tran[4] = rtb_Gain1_idx_4 -
    rtb_TmpSignalConversionAtK_tran[4];
  rtb_TmpSignalConversionAtK_tran[5] = rtb_Gain1_idx_5 -
    rtb_TmpSignalConversionAtK_tran[5];

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helicopter5_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter5_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter5_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter5_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[180]) {
      currTimeIndex = 179;
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

    helicopter5_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 181;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 181;
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
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_FromWorkspace[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 181;
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/K_transposed'
   */
  for (i = 0; i < 2; i++) {
    tmp = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      tmp += helicopter5_P.Klqr[(i_0 << 1) + i] *
        rtb_TmpSignalConversionAtK_tran[i_0];
    }

    rtb_Sum4[i] = rtb_FromWorkspace[i] - tmp;
  }

  /* End of Sum: '<Root>/Sum4' */

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  helicopter5_B.Sum1 = ((rtb_Sum4[0] - rtb_Gain1_idx_2) * helicopter5_P.K_pp -
                        helicopter5_P.K_pd * rtb_Gain1_idx_3) +
    helicopter5_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter5_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter5_X.Integrator_CSTATE >= helicopter5_P.Integrator_UpperSat) {
    helicopter5_X.Integrator_CSTATE = helicopter5_P.Integrator_UpperSat;
  } else {
    if (helicopter5_X.Integrator_CSTATE <= helicopter5_P.Integrator_LowerSat) {
      helicopter5_X.Integrator_CSTATE = helicopter5_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Gain1_idx_2 = rtb_Sum4[1] - rtb_Gain1_idx_4;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  helicopter5_B.Sum2 = ((helicopter5_P.K_ep * rtb_Gain1_idx_2 +
    helicopter5_X.Integrator_CSTATE) - helicopter5_P.K_ed * rtb_Gain1_idx_5) +
    helicopter5_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter5_M)) {
  }

  /* Gain: '<S3>/K_ei' */
  helicopter5_B.K_ei = helicopter5_P.K_ei * rtb_Gain1_idx_2;
  if (rtmIsMajorTimeStep(helicopter5_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter5_DW.TimeStampA >= helicopter5_M->Timing.t[0]) &&
      (helicopter5_DW.TimeStampB >= helicopter5_M->Timing.t[0])) {
    rtb_Gain1_idx_2 = 0.0;
  } else {
    rtb_Gain1_idx_2 = helicopter5_DW.TimeStampA;
    lastU = &helicopter5_DW.LastUAtTimeA;
    if (helicopter5_DW.TimeStampA < helicopter5_DW.TimeStampB) {
      if (helicopter5_DW.TimeStampB < helicopter5_M->Timing.t[0]) {
        rtb_Gain1_idx_2 = helicopter5_DW.TimeStampB;
        lastU = &helicopter5_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter5_DW.TimeStampA >= helicopter5_M->Timing.t[0]) {
        rtb_Gain1_idx_2 = helicopter5_DW.TimeStampB;
        lastU = &helicopter5_DW.LastUAtTimeB;
      }
    }

    rtb_Gain1_idx_2 = (helicopter5_B.PitchCounttorad - *lastU) /
      (helicopter5_M->Timing.t[0] - rtb_Gain1_idx_2);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S11>/Gain' */
  helicopter5_B.Gain_l = helicopter5_P.Gain_Gain_a1 * rtb_Gain1_idx_2;
  if (rtmIsMajorTimeStep(helicopter5_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Gain1_idx_5 = (helicopter5_B.Sum2 - helicopter5_B.Sum1) *
    helicopter5_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Gain1_idx_5 > helicopter5_P.BackmotorSaturation_UpperSat) {
    helicopter5_B.BackmotorSaturation =
      helicopter5_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Gain1_idx_5 < helicopter5_P.BackmotorSaturation_LowerSat) {
    helicopter5_B.BackmotorSaturation =
      helicopter5_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter5_B.BackmotorSaturation = rtb_Gain1_idx_5;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter5_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Gain1_idx_5 = (helicopter5_B.Sum1 + helicopter5_B.Sum2) *
    helicopter5_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Gain1_idx_5 > helicopter5_P.FrontmotorSaturation_UpperSat) {
    helicopter5_B.FrontmotorSaturation =
      helicopter5_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Gain1_idx_5 < helicopter5_P.FrontmotorSaturation_LowerSat) {
    helicopter5_B.FrontmotorSaturation =
      helicopter5_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter5_B.FrontmotorSaturation = rtb_Gain1_idx_5;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter5_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter5/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter5_DW.HILWriteAnalog_Buffer[0] =
        helicopter5_B.FrontmotorSaturation;
      helicopter5_DW.HILWriteAnalog_Buffer[1] =
        helicopter5_B.BackmotorSaturation;
      result = hil_write_analog(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILWriteAnalog_channels, 2,
        &helicopter5_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter5_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter5_DW.TimeStampA == (rtInf)) {
    helicopter5_DW.TimeStampA = helicopter5_M->Timing.t[0];
    lastU = &helicopter5_DW.LastUAtTimeA;
  } else if (helicopter5_DW.TimeStampB == (rtInf)) {
    helicopter5_DW.TimeStampB = helicopter5_M->Timing.t[0];
    lastU = &helicopter5_DW.LastUAtTimeB;
  } else if (helicopter5_DW.TimeStampA < helicopter5_DW.TimeStampB) {
    helicopter5_DW.TimeStampA = helicopter5_M->Timing.t[0];
    lastU = &helicopter5_DW.LastUAtTimeA;
  } else {
    helicopter5_DW.TimeStampB = helicopter5_M->Timing.t[0];
    lastU = &helicopter5_DW.LastUAtTimeB;
  }

  *lastU = helicopter5_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter5_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter5_M->solverInfo);
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
  if (!(++helicopter5_M->Timing.clockTick0)) {
    ++helicopter5_M->Timing.clockTickH0;
  }

  helicopter5_M->Timing.t[0] = rtsiGetSolverStopTime(&helicopter5_M->solverInfo);

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
    if (!(++helicopter5_M->Timing.clockTick1)) {
      ++helicopter5_M->Timing.clockTickH1;
    }

    helicopter5_M->Timing.t[1] = helicopter5_M->Timing.clockTick1 *
      helicopter5_M->Timing.stepSize1 + helicopter5_M->Timing.clockTickH1 *
      helicopter5_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter5_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter5_T *_rtXdot;
  _rtXdot = ((XDot_helicopter5_T *) helicopter5_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter5_P.TravelTransferFcn_A *
    helicopter5_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter5_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter5_P.PitchTransferFcn_A *
    helicopter5_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter5_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter5_P.ElevationTransferFcn_A *
    helicopter5_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter5_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter5_X.Integrator_CSTATE <= helicopter5_P.Integrator_LowerSat);
  usat = (helicopter5_X.Integrator_CSTATE >= helicopter5_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter5_B.K_ei > 0.0)) || (usat &&
       (helicopter5_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter5_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter5_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter5/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter5_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter5_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter5_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter5_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter5_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter5_M, _rt_error_message);
      return;
    }

    if ((helicopter5_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helicopter5_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter5_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helicopter5_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter5_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter5_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_analog_input_chan, 8U,
        &helicopter5_DW.HILInitialize_AIMinimums[0],
        &helicopter5_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter5_P.HILInitialize_set_analog_output && !is_switching) ||
        (helicopter5_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter5_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helicopter5_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter5_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter5_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_analog_output_cha, 8U,
        &helicopter5_DW.HILInitialize_AOMinimums[0],
        &helicopter5_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter5_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helicopter5_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter5_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter5_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_analog_output_cha, 8U,
        &helicopter5_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }

    if (helicopter5_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter5_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter5_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter5_DW.HILInitialize_Card,
         helicopter5_P.HILInitialize_analog_output_cha, 8U,
         &helicopter5_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter5_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helicopter5_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter5_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter5_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_encoder_channels, 8U,
        (t_encoder_quadrature_mode *)
        &helicopter5_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter5_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helicopter5_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter5_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter5_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_encoder_channels, 8U,
        &helicopter5_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter5_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helicopter5_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter5_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter5_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter5_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter5_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &helicopter5_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter5_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            helicopter5_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopter5_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter5_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter5_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helicopter5_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter5_DW.HILInitialize_Card,
          &helicopter5_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helicopter5_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter5_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter5_DW.HILInitialize_Card,
          &helicopter5_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter5_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter5_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter5_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter5_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &helicopter5_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter5_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter5_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter5_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helicopter5_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter5_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter5_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helicopter5_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter5_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter5_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter5_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_pwm_channels, 8U,
        &helicopter5_DW.HILInitialize_POSortedFreqs[0],
        &helicopter5_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter5_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helicopter5_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter5_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter5_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter5_DW.HILInitialize_Card,
        helicopter5_P.HILInitialize_pwm_channels, 8U,
        &helicopter5_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }

    if (helicopter5_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter5_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter5_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter5_DW.HILInitialize_Card,
         helicopter5_P.HILInitialize_pwm_channels, 8U,
         &helicopter5_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter5/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopter5_DW.HILInitialize_Card,
      helicopter5_P.HILReadEncoderTimebase_samples_,
      helicopter5_P.HILReadEncoderTimebase_channels, 3,
      &helicopter5_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter5_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<S6>/From Workspace1' */
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
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1389397088782545, 3.130980874743639, 3.1150632064744084,
      3.0885337593590236, 3.0487395886859465, 2.9930277497436388,
      2.9187452978205619, 2.8254761872436389, 2.7176419925321005,
      2.5996642882051773, 2.4759646487821003, 2.3509646487821003,
      2.2259646487821003, 2.1009646487821003, 1.9759646487821003,
      1.8509646487821003, 1.7259646487821003, 1.6009646487821003,
      1.4759646487821003, 1.3509646487821003, 1.2259646487821003,
      1.1009646487821003, 0.97596464878210032, 0.85096464878210032,
      0.72596464878210032, 0.60096464878210032, 0.47813789114672106,
      0.36180337694514236, 0.25638268069659509, 0.16582104384856489,
      0.092474423841498427, 0.036830645288765285, -0.0022482137715700611,
      -0.02700026287747035, -0.04007844674047404, -0.044135710072119604,
      -0.0418249975839455, -0.035657117875989013, -0.027701618035933007,
      -0.019489832803465681, -0.012030823571780229, -0.00588611275456893,
      -0.0012687554955628426, 0.0018543586610753377, 0.0036701068827447686,
      0.0044431273389914849, 0.004458651516341082, 0.0039836752388471477,
      0.00324406645492113, 0.0024143514928179977, 0.0016168352054928767,
      0.0009268376386929461, 0.00038113563488915915, -1.2249367492881511E-5,
      -0.00026469351167646512, -0.00039879146254156712, -0.00044192181474531349,
      -0.00042161393365097174, -0.00036245940934412721, -0.00028453644861861079,
      -0.00020285400563882627, -0.00012757697525455134, -6.4594094215742262E-5,
      -1.6462122547199591E-5, 1.6729700214466096E-5, 3.6465328990849365E-5,
      4.5183327137660993E-5, 4.5603310028914932E-5, 4.0465224332217793E-5,
      3.2219527753632331E-5, 2.2816296429336081E-5, 1.3727660586215002E-5,
      5.8874961009915755E-6, -1.5795287117183656E-7, -4.2470245321556963E-6,
      -6.490872856892825E-6, -7.1190681200596173E-6, -6.4688596981548268E-6,
      -4.9442699458927371E-6, -2.9464106286266149E-6, -8.6890879658497312E-7,
      9.79238605239386E-7, 2.3913409573131122E-6, 3.2306358498694056E-6,
      3.515258604604069E-6, 3.3166447862958718E-6, 2.708489731234621E-6,
      1.8555329199057132E-6, 9.0058213496617617E-7, 1.864231399122322E-9,
      -7.6184016543279462E-7, -1.3308099692550625E-6, -1.6809446167987111E-6,
      -1.7644705468392439E-6, -1.5959123879941589E-6, -1.1705921493455597E-6,
      -5.27649631243483E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      -0.010611778846153847, -0.031835336538461545, -0.06367067307692309,
      -0.10611778846153848, -0.15917668269230772, -0.22284735576923081,
      -0.29712980769230773, -0.37307644230769232, -0.43133677884615385,
      -0.4719108173076923, -0.49479855769230768, -0.5, -0.5, -0.5, -0.5, -0.5,
      -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
      -0.491307030541517, -0.46533805680631463, -0.42168278499418921,
      -0.36224654739212081, -0.29338648002826584, -0.22257511421093257,
      -0.15631543624134139, -0.099008196423601161, -0.052312735452014779,
      -0.016229053326582251, 0.0092428499526964244, 0.024671518831825976,
      0.031821999360224007, 0.03284714092986929, 0.029836036926741815,
      0.0245788432688452, 0.018469429036024349, 0.01249245662655272,
      0.0072629928866777237, 0.0030920818249868635, 6.2096709398392131E-5,
      -0.0018999051099757376, -0.00295843513570407, -0.0033188598484125294,
      -0.0031900651493004845, -0.0027599902671997223, -0.0021828080152151478,
      -0.0015735400095281626, -0.0010097765767343345, -0.00053639180346040779,
      -0.00017252140881498555, 8.12315243773669E-5, 0.00023661809722737821,
      0.00031169184290206548, 0.0003267297719191382, 0.00030110812153709963,
      0.00025193152415523636, 0.0001925278866741707, 0.00013276729104666276,
      7.8942515105533061E-5, 3.4871992587246539E-5, 1.6799315650157589E-6,
      -2.055234278678855E-5, -3.2982786314341842E-5, -3.7612925297185008E-5,
      -3.6354543372484314E-5, -3.1360657940893707E-5, -2.4181795888653645E-5,
      -1.6356286643935446E-5, -8.9753932989485148E-6, -2.5127810526671708E-6,
      2.6008336876191655E-6, 6.0983590090483594E-6, 7.9914372690644887E-6,
      8.3100073281665669E-6, 7.3925896072974384E-6, 5.6484094082949024E-6,
      3.3571795702251774E-6, 1.1384910189386586E-6, -7.9445527323279243E-7,
      -2.432620220245005E-6, -3.4118272453156296E-6, -3.8198031397581511E-6,
      -3.5948716142682137E-6, -3.0548175873276708E-6, -2.27587921528907E-6,
      -1.4005385901745938E-6, -3.3410372016213275E-7, 6.7423263538033733E-7,
      1.701280954594398E-6, 2.5717700724083041E-6, 3.4486725856406141E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.075, 0.15, 0.22499999999999998, 0.3, 0.375,
      0.45, 0.525, 0.53676180767923876, 0.41176180767923881, 0.28676180767923881,
      0.16176180767923878, 0.036761807679238791, 2.2265836431864637E-17,
      -1.7199487695494752E-16, 1.7876638147901569E-16, 9.4776276721289862E-17,
      5.3890227727561277E-17, -1.2763307975055627E-16, -1.5398408041456731E-16,
      -5.1887754875656325E-17, -1.3280057572796634E-16, 9.2511853941583657E-17,
      -1.6604018820066155E-16, -4.8508883473237429E-17, 9.38492910182036E-17,
      -1.1804653238248721E-16, -0.061438588085778657, -0.18353878820666295,
      -0.30853878820666292, -0.42007262729290634, -0.48667665686992251,
      -0.50046768909294348, -0.46829809778032477, -0.40502568406693734,
      -0.33002568406693733, -0.25502568406693732, -0.18002568406693728,
      -0.10904393907098019, -0.050536865440257907, -0.0072453090888963271,
      0.021281333083605664, 0.037155836929748429, 0.043179006470497341,
      0.042242958245671036, 0.036959852459870858, 0.029478406416299653,
      0.021414777575344955, 0.013866679525308154, 0.007481285944665076,
      0.0025473442148610079, -0.0009102717436393254, -0.0030396050111097016,
      -0.0040793037177299166, -0.0043060735706045824, -0.0039844646286481883,
      -0.0033457027808690711, -0.0025716969788055666, -0.0017934288176693614,
      -0.0010982129511655574, -0.00053059256202293435, -0.00010628233895858366,
      0.00018108403939735024, 0.00034756140861119829, 0.00041984222208840124,
      0.00042236506593685527, 0.00038041295942082821, 0.00031147362160392783,
      0.00023458881048671432, 0.00015712922409701988, 8.7853627377882569E-5,
      3.2724053973203477E-5, -8.8937628385233956E-6, -3.5294874949739977E-5,
      -5.0737455211210759E-5, -5.5307710598076316E-5, -5.2165335227906265E-5,
      -4.567527513511788E-5, -3.6141075976199722E-5, -2.4719173185772077E-5,
      -1.3379554131272679E-5, -2.25153150843467E-6, 6.4839580679843181E-6,
      1.2327199503653671E-5, 1.6193537421627683E-5, 1.5680843311844915E-5,
      1.3661326156019768E-5, 1.1577924192271157E-5, 6.9206612713112375E-6,
      2.8834178064575128E-6, -1.5897301155931696E-6, -3.8168956032495029E-6,
      -5.50523891892725E-6, -6.1865732254098207E-6, -7.5371543650218094E-6,
      -7.1265362539189177E-6, -7.2587852666165387E-6, -6.1522846247126178E-6,
      -6.1976120541053443E-6, -5.6615994330508331E-6, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.047047230716955074, -0.5, -0.5,
      -0.5, -0.5, -0.14704723071695508, -7.7704285354724873E-16,
      1.4030450337358529E-15, -3.3596041903090332E-16, -1.6354419597491434E-16,
      -7.260932299124702E-16, -1.0540400265604412E-16, 4.0838530215564395E-16,
      -3.2365111879319905E-16, 9.0124950268846251E-16, -1.0342080969853403E-15,
      4.7012495454716054E-16, 5.6943299853196222E-16, -8.4758391307527755E-16,
      -0.24575435234311416, -0.48840080048353718, -0.5, -0.44613535634497375,
      -0.26641611830806455, -0.055164128892084031, 0.12867836525047482,
      0.25308965485354984, 0.3, 0.3, 0.3, 0.28392697998382843,
      0.23402829452288912, 0.17316622540544629, 0.11410656869000796,
      0.06349801538457106, 0.024092678162995654, -0.0037441928993052,
      -0.021132423143200733, -0.029925784174284809, -0.0322545153638188,
      -0.030192392200147206, -0.025541574322572314, -0.019735766919216271,
      -0.013830463834001333, -0.0085173330698815036, -0.0041587948264808607,
      -0.00090707941149866477, 0.0012864357678255775, 0.0025550473911164673,
      0.0030960232082540198, 0.0031130726445448204, 0.0027808634660152157,
      0.0022704815565704924, 0.0016972408922574028, 0.0011494655134237357,
      0.00066590947685539221, 0.00028912325390881185, 1.0091375393816127E-5,
      -0.00016780842606410829, -0.0002757573512676016, -0.00030753924446885408,
      -0.00030983834555877777, -0.00027710238687654923, -0.00022051829361871637,
      -0.0001664712672469075, -0.00010560444844486634, -6.17703210458831E-5,
      -1.8281021547462243E-5, 1.2569501480680223E-5, 2.5960240371153526E-5,
      3.8136796635672612E-5, 4.568761116171058E-5, 4.53584762179976E-5,
      4.4512090491352032E-5, 3.4941958305675953E-5, 2.3372965742677413E-5,
      1.5465351671896053E-5, -2.0507764391310818E-6, -8.0780686233005942E-6,
      -8.333607854994437E-6, -1.8629051683839683E-5, -1.61489738594149E-5,
      -1.789259168820273E-5, -8.9086619506253324E-6, -6.753373262710992E-6,
      -2.7253372259302838E-6, -5.4023245584479562E-6, 1.6424724444115648E-6,
      -5.2899605079048334E-7, 4.426002567615683E-6, -1.8130971757090535E-7,
      2.1440504842180465E-6, 1.842887420947093E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.012327438727306081, 0.024827438727306084, 0.037327438727306081,
      0.049827438727306078, 0.062327438727306082, 0.074827438727306086,
      0.087327438727306084, 0.099827438727306081, 0.11232743872730608,
      0.12482743872730608, 0.13732743872730607, 0.14982743872730608,
      0.16232743872730609, 0.17482743872730611, 0.18732743872730612,
      0.19982743872730613, 0.20627578929967022, 0.20799002588583362,
      0.20605280271864757, 0.20135013156266662, 0.19460363416748541,
      0.18639765963802338, 0.17720247847755766, 0.16739353516205757,
      0.15726793084644902, 0.14705807505302368, 0.13694323781777429,
      0.12705923041556047, 0.1175063753985572, 0.10835634300781216,
      0.099657658216461414, 0.091440498130926862, 0.083720353190861629,
      0.076501353628774763, 0.069778846988590951, 0.063541534413545875,
      0.057773175740491331, 0.052453971624893382, 0.047561740651571136,
      0.04307297987014129, 0.038963211618852717, 0.035207880191873063,
      0.031782564794668622, 0.028663499325051248, 0.025827690015316943,
      0.023253061391667655, 0.020918648501162873, 0.018804529935451772,
      0.016892163878567693, 0.015164056912045341, 0.013604051687358598,
      0.012197209802881609, 0.010929527351568854, 0.0097882418406578658,
      0.0087616100168036309, 0.0078387977329197889, 0.0070099282477069647,
      0.0062658218132909064, 0.0055983341012039731, 0.0049999397931899574,
      0.0044637643662125536, 0.0039836577786795955, 0.0035539709963677488,
      0.0031695077250768894, 0.0028257137625715138, 0.0025183775386973216,
      0.0022437815408528957, 0.0019985346274471478, 0.0017795555640683213,
      0.001584183287803901, 0.0014099255314900137, 0.0012545505039509664,
      0.0011160705312949454, 0.000992614516486343, 0.00088261036090244935,
      0.00078467560744652242, 0.00069750420102817528, 0.00061993190787117982,
      0.00055083748684271066, 0.000489406895737291, 0.00043469932984074042,
      0.00038603790718039221, 0.00034272901009369937, 0.00030421690622120339,
      0.00026997777130607209, 0.00023953092598716212, 0.00021240659557103154,
      0.00018833285483751695, 0.00016694774954869519, 0.00014800359899733869,
      0.00013117881108149886, 0.00011632358789830974, 0.00010310210715143841,
      9.1435028579196228E-5, 8.1021156585084846E-5, 7.1741204134964171E-5,
      6.3491249055935549E-5, 5.6213794387227147E-5, 4.9790632682822273E-5, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.049309754909224325, 0.05, 0.05, 0.05, 0.05,
      0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
      0.025793402289456372, 0.0068569463446536407, -0.0077488926687442053,
      -0.018810684623923792, -0.026985989580724845, -0.032823898117848124,
      -0.036780724641862855, -0.039235773262000395, -0.040502417262434177,
      -0.040839423173701442, -0.040459348940997647, -0.039536029608855279,
      -0.038211420068013063, -0.036600129562980151, -0.034794739165402988,
      -0.032868640342138204, -0.030880579760260905, -0.028875998248347457,
      -0.026890026560735216, -0.024949250300180324, -0.023073434692218158,
      -0.021276816462391809, -0.019568923893288979, -0.017955043125719373,
      -0.016439073005154278, -0.015021325707918622, -0.013701261588817777,
      -0.012476261878469482, -0.011343237238937234, -0.010298514494597148,
      -0.0093376515620191263, -0.0084564742628443976, -0.0076494642275363152,
      -0.0069124278660894134, -0.0062400208987469776, -0.0056273675379079511,
      -0.0050707298052510182, -0.0045651420436439456, -0.0041065272954169431,
      -0.0036912491355353626, -0.0033154779408513016, -0.0029764257376642313,
      -0.0026699508483477344, -0.0023935772320560649, -0.0021447017079096156,
      -0.0019204263501318285, -0.0017187471292473883, -0.0015378530851634375,
      -0.0013751758500215026, -0.0012293448954967679, -0.0010983839913777027,
      -0.00098098765362299189, -0.00087591625351530577, -0.00078148910505768175,
      -0.00069703102525554882, -0.00062150011015618917, -0.00055391989062408364,
      -0.00049382405923440961, -0.00044001662233557418, -0.00039173901382370786,
      -0.00034868562567338853, -0.000310289172627982, -0.00027637768411387678,
      -0.00024572236442167857, -0.00021883026358620239, -0.00019464569064139289,
      -0.00017323558834677141, -0.00015404841548998378, -0.00013695653966052523,
      -0.00012178738127563984, -0.00010849732166452233, -9.6294962934058388E-5,
      -8.5540421155287E-5, -7.5776602205425948E-5, -6.7299151663359437E-5,
      -5.9420892732756456E-5, -5.2885922987485289E-5, -4.6668314288968759E-5,
      -4.165548797644556E-5, -3.7119809800482708E-5, -3.2999820316114495E-5,
      -2.9109818674833619E-5, -2.5692646817619502E-5, -2.278284726241632E-5, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter5_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter5_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter5_DW.FromWorkspace1_IWORK.PrevIndex = 0;
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
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0, 35.25, 35.5, 35.75, 36.0,
      36.25, 36.5, 36.75, 37.0, 37.25, 37.5, 37.75, 38.0, 38.25, 38.5, 38.75,
      39.0, 39.25, 39.5, 39.75, 40.0, 40.25, 40.5, 40.75, 41.0, 41.25, 41.5,
      41.75, 42.0, 42.25, 42.5, 42.75, 43.0, 43.25, 43.5, 43.75, 44.0, 44.25,
      44.5, 44.75, 45.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.37037037037037035, 0.33333333333333337, 0.40833333333333333,
      0.48333333333333334, 0.55833333333333324, 0.6333333333333333,
      0.70833333333333337, 0.47104596384809272, -0.098092250705797,
      -0.018793747876316817, -0.14379374787631682, -0.26879374787631682,
      0.041950411732380642, 0.054915786780096482, 1.8503514155560344E-15,
      -7.5997626263950133E-16, 1.833656163725762E-17, -7.814444767539926E-16,
      1.3402968882132718E-17, 3.8955914546086143E-16, -6.0397130141304068E-16,
      1.1007229105408209E-15, -1.5208660042976812E-15, 8.00592912725149E-16,
      4.7892337565281907E-16, -1.1652090947990138E-15, -0.30340043499149877,
      -0.57262390771509375, -0.61842614358163828, -0.67259478369428483,
      -0.58236913718637551, -0.45528561131917494, -0.32100409126537532,
      -0.20389754300837268, -0.12917336381162717, -0.071692350733603957,
      0.0033076492663960773, 0.0584644146785299, 0.073845422753440831,
      0.075849142352670956, 0.0689568952380919, 0.057060071794523756,
      0.043186119039826096, 0.029558971848754889, 0.017551841219546453,
      0.0079064868136157988, 0.00083400437790749822, -0.0038141129216822355,
      -0.0063905744031212131, -0.00734518403883881, -0.0071568463295074037,
      -0.0062604171264740195, -0.0049930637430130433, -0.00364602467635733,
      -0.0023791262992417144, -0.0013105133059948177, -0.00047765170378106034,
      0.00011537169285860577, 0.00047713783793608064, 0.00066631835513183751,
      0.00071683981006944722, 0.0006789647518017515, 0.00057391880365008146,
      0.00045581528164830411, 0.00032432566787408095, 0.00021142547689890755,
      0.00010264098116995303, 3.4778997270094973E-5, -3.3075046435445425E-5,
      -6.92612541067073E-5, -8.090541162033993E-5, -9.044197494932224E-5,
      -7.7099800002321944E-5, -7.2115832222963486E-5, -5.0238071792794219E-5,
      -3.2962635908215144E-5, -2.4809821433773231E-5, -8.2878381926503927E-6,
      6.0209365909849911E-6, 1.4216596989018235E-5, 2.4634213072934434E-5,
      2.4263346185444306E-5, 2.2290159741083627E-5, 2.269143349715508E-5,
      7.8860740637515887E-6, 6.47379547176659E-6, 6.3897309752222244E-6,
      -8.3086626073632469E-6, -6.05919764850777E-6, -1.3175257620369307E-5,
      -5.9059683439191035E-6, -8.82739316207275E-6, -6.347759676902818E-6,
      -1.1838314024920988E-5, -3.49187581768592E-6, -8.3930102850608711E-6,
      -1.5970273987402367E-6, -8.0290444941874928E-6, -3.4829248025210906E-6,
      -4.1871399892593092E-6, -4.1871399892593092E-6, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.7889560785475892, 0.20828294108930812, 0.21232743872730608,
      0.22482743872730604, 0.237327438727306, 0.24982743872730606,
      0.262327438727306, 0.27482743872730608, 0.28732743872730604,
      0.299827438727306, 0.31232743872730606, 0.324827438727306,
      0.33732743872730603, 0.34982743872730604, 0.36232743872730605,
      0.37482743872730606, 2.1875358607959432E-5, 1.775276828792599E-5,
      1.0150463919236518E-5, 5.7839279834406835E-6, 5.1849141355160042E-6,
      -3.6335420529123554E-7, -1.1826881428257554E-6, -6.0168516286559942E-6,
      -6.91857738436024E-6, -8.2284679554179591E-6, -8.5741250959455343E-6,
      -6.2113966889276309E-6, -7.1279641713868661E-6, -5.8017759651950988E-6,
      -7.8964921287082127E-6, -5.032481563294287E-6, -7.93384205460407E-6,
      -8.5167195015672E-6, -8.0928007323509253E-6, -6.33244528778065E-6,
      -5.1044847357015815E-6, -6.3126781051944078E-6, -7.8090034306867761E-6,
      3.6833285115370343E-7, -2.909922264840181E-6, 6.4460529471891527E-7,
      -1.0653072082510594E-6, 2.8292021746801238E-6, 5.9115133066563123E-6,
      6.11427874369212E-6, 7.4389581766826384E-6, 1.2919303868199169E-6,
      4.9120147145760175E-6, -7.4519154305803457E-7, 9.6389168901924885E-7,
      6.4270904818435156E-6, 7.8525823773767151E-7, 3.6947675906927321E-6,
      6.79514862510831E-6, 6.583217095382907E-6, 8.9525896071597756E-6,
      1.721220507711401E-6, 7.8235261139863655E-6, 7.9962805666803055E-6,
      6.0335593229044844E-6, 9.538685996089995E-6, 8.9264998362833933E-6,
      2.9739670332552457E-6, 5.3944179849556882E-6, 2.0995973866316975E-6,
      3.7086464894876982E-6, 3.1829772618843683E-6, 9.7332808390641036E-7,
      5.7039887079077277E-6, 4.9284206717203509E-6, 4.553828371461616E-6,
      5.2086033789451471E-6, 4.0424368941798107E-7, 1.6932847386728576E-6,
      4.9897633339071163E-6, 4.508516012727394E-6, 4.2763534794723019E-6,
      -1.0686732580685951E-6, 4.906286490843687E-6, -1.7783574763846935E-6,
      1.0390085094330799E-6, -1.3217960108872292E-6, 9.0319501908628224E-8,
      5.3614051010909132E-9, -9.0271826273111947E-7, -4.5308000186070666E-6,
      7.7937901649594977E-7, -7.0058770485958077E-7, 2.3922734141454557E-6,
      -5.1945059994444228E-7, 4.8591352335485445E-6, -1.9452439251883251E-6,
      4.2616351246330317E-6, -3.3659290040653854E-6, -2.6160725111803691E-6,
      -1.5382508669546879E-6, 1.9819491310002741E-6, 1.7267240720269339E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter5_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter5_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter5_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter5_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter5_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter5_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter5_X.Integrator_CSTATE = helicopter5_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter5_DW.TimeStampA = (rtInf);
  helicopter5_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter5_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter5/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter5_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter5_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter5_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helicopter5_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter5_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter5_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter5_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helicopter5_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter5_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter5_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter5_DW.HILInitialize_Card
                         , helicopter5_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter5_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter5_DW.HILInitialize_AOVoltages[0]
                         , &helicopter5_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter5_DW.HILInitialize_Card,
            helicopter5_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs, &helicopter5_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter5_DW.HILInitialize_Card,
            helicopter5_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helicopter5_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter5_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter5_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter5_DW.HILInitialize_Card);
    hil_close(helicopter5_DW.HILInitialize_Card);
    helicopter5_DW.HILInitialize_Card = NULL;
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
  helicopter5_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter5_update();
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
  helicopter5_initialize();
}

void MdlTerminate(void)
{
  helicopter5_terminate();
}

/* Registration function */
RT_MODEL_helicopter5_T *helicopter5(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter5_P.Integrator_UpperSat = rtInf;
  helicopter5_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter5_M, 0,
                sizeof(RT_MODEL_helicopter5_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter5_M->solverInfo,
                          &helicopter5_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter5_M->solverInfo, &rtmGetTPtr(helicopter5_M));
    rtsiSetStepSizePtr(&helicopter5_M->solverInfo,
                       &helicopter5_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter5_M->solverInfo, &helicopter5_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter5_M->solverInfo, (real_T **)
                         &helicopter5_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter5_M->solverInfo,
      &helicopter5_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter5_M->solverInfo,
      &helicopter5_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter5_M->solverInfo,
      &helicopter5_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter5_M->solverInfo,
      &helicopter5_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter5_M->solverInfo, (&rtmGetErrorStatus
      (helicopter5_M)));
    rtsiSetRTModelPtr(&helicopter5_M->solverInfo, helicopter5_M);
  }

  rtsiSetSimTimeStep(&helicopter5_M->solverInfo, MAJOR_TIME_STEP);
  helicopter5_M->ModelData.intgData.f[0] = helicopter5_M->ModelData.odeF[0];
  helicopter5_M->ModelData.contStates = ((real_T *) &helicopter5_X);
  rtsiSetSolverData(&helicopter5_M->solverInfo, (void *)
                    &helicopter5_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter5_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter5_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter5_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter5_M->Timing.sampleTimes = (&helicopter5_M->
      Timing.sampleTimesArray[0]);
    helicopter5_M->Timing.offsetTimes = (&helicopter5_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter5_M->Timing.sampleTimes[0] = (0.0);
    helicopter5_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter5_M->Timing.offsetTimes[0] = (0.0);
    helicopter5_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter5_M, &helicopter5_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter5_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter5_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter5_M, -1);
  helicopter5_M->Timing.stepSize0 = 0.002;
  helicopter5_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter5_M->Sizes.checksums[0] = (3464453201U);
  helicopter5_M->Sizes.checksums[1] = (1994306398U);
  helicopter5_M->Sizes.checksums[2] = (2926393910U);
  helicopter5_M->Sizes.checksums[3] = (473275086U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter5_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter5_M->extModeInfo,
      &helicopter5_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter5_M->extModeInfo,
                        helicopter5_M->Sizes.checksums);
    rteiSetTPtr(helicopter5_M->extModeInfo, rtmGetTPtr(helicopter5_M));
  }

  helicopter5_M->solverInfoPtr = (&helicopter5_M->solverInfo);
  helicopter5_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter5_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter5_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter5_M->ModelData.blockIO = ((void *) &helicopter5_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter5_B.TmpSignalConversionAtToWorkspac[i] = 0.0;
    }

    helicopter5_B.TravelCounttorad = 0.0;
    helicopter5_B.Gain = 0.0;
    helicopter5_B.Gain_d = 0.0;
    helicopter5_B.PitchCounttorad = 0.0;
    helicopter5_B.Gain_i = 0.0;
    helicopter5_B.Gain_b = 0.0;
    helicopter5_B.Sum3 = 0.0;
    helicopter5_B.ElevationCounttorad = 0.0;
    helicopter5_B.Gain_e = 0.0;
    helicopter5_B.Sum = 0.0;
    helicopter5_B.Gain_dg = 0.0;
    helicopter5_B.Sum1 = 0.0;
    helicopter5_B.Sum2 = 0.0;
    helicopter5_B.K_ei = 0.0;
    helicopter5_B.Gain_l = 0.0;
    helicopter5_B.BackmotorSaturation = 0.0;
    helicopter5_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter5_M->ModelData.defaultParam = ((real_T *)&helicopter5_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter5_X;
    helicopter5_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter5_X, 0,
                  sizeof(X_helicopter5_T));
  }

  /* states (dwork) */
  helicopter5_M->ModelData.dwork = ((void *) &helicopter5_DW);
  (void) memset((void *)&helicopter5_DW, 0,
                sizeof(DW_helicopter5_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter5_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter5_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter5_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter5_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter5_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter5_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter5_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter5_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter5_DW.TimeStampA = 0.0;
  helicopter5_DW.LastUAtTimeA = 0.0;
  helicopter5_DW.TimeStampB = 0.0;
  helicopter5_DW.LastUAtTimeB = 0.0;
  helicopter5_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter5_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter5_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter5_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter5_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter5_M->Sizes.numY = (0);     /* Number of model outputs */
  helicopter5_M->Sizes.numU = (0);     /* Number of model inputs */
  helicopter5_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter5_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter5_M->Sizes.numBlocks = (68);/* Number of blocks */
  helicopter5_M->Sizes.numBlockIO = (18);/* Number of block outputs */
  helicopter5_M->Sizes.numBlockPrms = (155);/* Sum of parameter "widths" */
  return helicopter5_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
