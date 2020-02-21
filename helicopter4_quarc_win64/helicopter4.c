/*
 * helicopter4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter4".
 *
 * Model version              : 1.190
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Fri Feb 21 16:50:35 2020
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter4.h"
#include "helicopter4_private.h"
#include "helicopter4_dt.h"

/* Block signals (auto storage) */
B_helicopter4_T helicopter4_B;

/* Continuous states */
X_helicopter4_T helicopter4_X;

/* Block states (auto storage) */
DW_helicopter4_T helicopter4_DW;

/* Real-time model */
RT_MODEL_helicopter4_T helicopter4_M_;
RT_MODEL_helicopter4_T *const helicopter4_M = &helicopter4_M_;

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
  helicopter4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter4_output(void)
{
  /* local block i/o variables */
  real_T rtb_FromWorkspace[2];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_Sum3_d;
  real_T rtb_Sum4[2];
  int32_T i;
  real_T tmp[6];
  int32_T i_0;
  if (rtmIsMajorTimeStep(helicopter4_M)) {
    /* set solver stop time */
    if (!(helicopter4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter4_M->solverInfo,
                            ((helicopter4_M->Timing.clockTickH0 + 1) *
        helicopter4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter4_M->solverInfo,
                            ((helicopter4_M->Timing.clockTick0 + 1) *
        helicopter4_M->Timing.stepSize0 + helicopter4_M->Timing.clockTickH0 *
        helicopter4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter4_M)) {
    helicopter4_M->Timing.t[0] = rtsiGetT(&helicopter4_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(helicopter4_DW.HILReadEncoderTimebase_Task,
        1, &helicopter4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter4_B.TravelCounttorad = helicopter4_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter4_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter4_B.Gain = helicopter4_P.Gain_Gain *
      helicopter4_B.TravelCounttorad;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter4_B.PitchCounttorad = helicopter4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter4_B.Gain_i = helicopter4_P.Gain_Gain_a *
      helicopter4_B.PitchCounttorad;
  }

  /* Gain: '<S13>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter4_B.Gain_d = (helicopter4_P.TravelTransferFcn_C *
    helicopter4_X.TravelTransferFcn_CSTATE + helicopter4_P.TravelTransferFcn_D *
    helicopter4_B.TravelCounttorad) * helicopter4_P.Gain_Gain_l;

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter4_B.Gain_b = (helicopter4_P.PitchTransferFcn_C *
    helicopter4_X.PitchTransferFcn_CSTATE + helicopter4_P.PitchTransferFcn_D *
    helicopter4_B.PitchCounttorad) * helicopter4_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter4_M)) {
    /* SignalConversion: '<Root>/TmpSignal ConversionAtTo WorkspaceInport1' */
    helicopter4_B.TmpSignalConversionAtToWorkspac[0] = 0.0;
    helicopter4_B.TmpSignalConversionAtToWorkspac[1] = 0.0;
    helicopter4_B.TmpSignalConversionAtToWorkspac[2] = helicopter4_B.Gain;
    helicopter4_B.TmpSignalConversionAtToWorkspac[3] = helicopter4_B.Gain_d;
    helicopter4_B.TmpSignalConversionAtToWorkspac[4] = helicopter4_B.Gain_i;
    helicopter4_B.TmpSignalConversionAtToWorkspac[5] = helicopter4_B.Gain_b;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter4_B.Sum3 = helicopter4_P.Constant_Value + helicopter4_B.Gain;

    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopter4_B.ElevationCounttorad = helicopter4_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopter4_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopter4_B.Gain_e = helicopter4_P.Gain_Gain_lv *
      helicopter4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter4_B.Sum = helicopter4_B.Gain_e +
      helicopter4_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter4_B.Gain_dg = (helicopter4_P.ElevationTransferFcn_C *
    helicopter4_X.ElevationTransferFcn_CSTATE +
    helicopter4_P.ElevationTransferFcn_D * helicopter4_B.ElevationCounttorad) *
    helicopter4_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  helicopter4_B.Gain1[0] = helicopter4_P.Gain1_Gain * helicopter4_B.Sum3;
  helicopter4_B.Gain1[1] = helicopter4_P.Gain1_Gain * helicopter4_B.Gain_d;
  helicopter4_B.Gain1[2] = helicopter4_P.Gain1_Gain * helicopter4_B.Gain_i;
  helicopter4_B.Gain1[3] = helicopter4_P.Gain1_Gain * helicopter4_B.Gain_b;
  helicopter4_B.Gain1[4] = helicopter4_P.Gain1_Gain * helicopter4_B.Sum;
  helicopter4_B.Gain1[5] = helicopter4_P.Gain1_Gain * helicopter4_B.Gain_dg;

  /* FromWorkspace: '<S6>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *) helicopter4_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter4_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter4_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter4_M->Timing.t[0];

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

    helicopter4_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&helicopter4_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex];
              pDataValues += 181;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&helicopter4_B.FromWorkspace1[0])[elIdx] =
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
            (&helicopter4_B.FromWorkspace1[0])[elIdx] = (real_T) rtInterpolate
              (d1, d2, f1, f2);
            pDataValues += 181;
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helicopter4_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter4_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopter4_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopter4_M->Timing.t[0];

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

    helicopter4_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

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

  /* SignalConversion: '<Root>/TmpSignal ConversionAtK_transposedInport1' incorporates:
   *  Sum: '<S6>/Sum1'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   *  Sum: '<S6>/Sum5'
   *  Sum: '<S6>/Sum6'
   *  Sum: '<S6>/Sum7'
   */
  tmp[0] = helicopter4_B.Gain1[0] - helicopter4_B.FromWorkspace1[0];
  tmp[1] = helicopter4_B.Gain1[1] - helicopter4_B.FromWorkspace1[1];
  tmp[2] = helicopter4_B.Gain1[2] - helicopter4_B.FromWorkspace1[2];
  tmp[3] = helicopter4_B.Gain1[3] - helicopter4_B.FromWorkspace1[3];
  tmp[4] = helicopter4_B.Gain1[4] - helicopter4_B.FromWorkspace1[4];
  tmp[5] = helicopter4_B.Gain1[5] - helicopter4_B.FromWorkspace1[5];

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/K_transposed'
   */
  for (i = 0; i < 2; i++) {
    rtb_Sum3_d = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Sum3_d += helicopter4_P.Klqr[(i_0 << 1) + i] * tmp[i_0];
    }

    rtb_Sum4[i] = rtb_FromWorkspace[i] - rtb_Sum3_d;
  }

  /* End of Sum: '<Root>/Sum4' */

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  helicopter4_B.Sum1 = ((rtb_Sum4[0] - helicopter4_B.Gain1[2]) *
                        helicopter4_P.K_pp - helicopter4_P.K_pd *
                        helicopter4_B.Gain1[3]) + helicopter4_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter4_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter4_X.Integrator_CSTATE >= helicopter4_P.Integrator_UpperSat) {
    helicopter4_X.Integrator_CSTATE = helicopter4_P.Integrator_UpperSat;
  } else {
    if (helicopter4_X.Integrator_CSTATE <= helicopter4_P.Integrator_LowerSat) {
      helicopter4_X.Integrator_CSTATE = helicopter4_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Sum3_d = rtb_Sum4[1] - helicopter4_B.Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  helicopter4_B.Sum2 = ((helicopter4_P.K_ep * rtb_Sum3_d +
    helicopter4_X.Integrator_CSTATE) - helicopter4_P.K_ed * helicopter4_B.Gain1
                        [5]) + helicopter4_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter4_M)) {
  }

  /* Gain: '<S3>/K_ei' */
  helicopter4_B.K_ei = helicopter4_P.K_ei * rtb_Sum3_d;
  if (rtmIsMajorTimeStep(helicopter4_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter4_DW.TimeStampA >= helicopter4_M->Timing.t[0]) &&
      (helicopter4_DW.TimeStampB >= helicopter4_M->Timing.t[0])) {
    rtb_Sum3_d = 0.0;
  } else {
    rtb_Sum3_d = helicopter4_DW.TimeStampA;
    lastU = &helicopter4_DW.LastUAtTimeA;
    if (helicopter4_DW.TimeStampA < helicopter4_DW.TimeStampB) {
      if (helicopter4_DW.TimeStampB < helicopter4_M->Timing.t[0]) {
        rtb_Sum3_d = helicopter4_DW.TimeStampB;
        lastU = &helicopter4_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter4_DW.TimeStampA >= helicopter4_M->Timing.t[0]) {
        rtb_Sum3_d = helicopter4_DW.TimeStampB;
        lastU = &helicopter4_DW.LastUAtTimeB;
      }
    }

    rtb_Sum3_d = (helicopter4_B.PitchCounttorad - *lastU) /
      (helicopter4_M->Timing.t[0] - rtb_Sum3_d);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S11>/Gain' */
  helicopter4_B.Gain_l = helicopter4_P.Gain_Gain_a1 * rtb_Sum3_d;
  if (rtmIsMajorTimeStep(helicopter4_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Sum3_d = (helicopter4_B.Sum2 - helicopter4_B.Sum1) *
    helicopter4_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Sum3_d > helicopter4_P.BackmotorSaturation_UpperSat) {
    helicopter4_B.BackmotorSaturation =
      helicopter4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Sum3_d < helicopter4_P.BackmotorSaturation_LowerSat) {
    helicopter4_B.BackmotorSaturation =
      helicopter4_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter4_B.BackmotorSaturation = rtb_Sum3_d;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter4_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Sum3_d = (helicopter4_B.Sum1 + helicopter4_B.Sum2) *
    helicopter4_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Sum3_d > helicopter4_P.FrontmotorSaturation_UpperSat) {
    helicopter4_B.FrontmotorSaturation =
      helicopter4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Sum3_d < helicopter4_P.FrontmotorSaturation_LowerSat) {
    helicopter4_B.FrontmotorSaturation =
      helicopter4_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter4_B.FrontmotorSaturation = rtb_Sum3_d;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter4_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter4/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter4_DW.HILWriteAnalog_Buffer[0] =
        helicopter4_B.FrontmotorSaturation;
      helicopter4_DW.HILWriteAnalog_Buffer[1] =
        helicopter4_B.BackmotorSaturation;
      result = hil_write_analog(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILWriteAnalog_channels, 2,
        &helicopter4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
      }
    }

    /* SignalConversion: '<S6>/TmpSignal ConversionAtTo WorkspaceInport1' */
    for (i = 0; i < 6; i++) {
      helicopter4_B.TmpSignalConversionAtToWorksp_o[i] = helicopter4_B.Gain1[i];
      helicopter4_B.TmpSignalConversionAtToWorksp_o[i + 6] =
        helicopter4_B.FromWorkspace1[i];
    }

    /* End of SignalConversion: '<S6>/TmpSignal ConversionAtTo WorkspaceInport1' */
  }
}

/* Model update function */
void helicopter4_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter4_DW.TimeStampA == (rtInf)) {
    helicopter4_DW.TimeStampA = helicopter4_M->Timing.t[0];
    lastU = &helicopter4_DW.LastUAtTimeA;
  } else if (helicopter4_DW.TimeStampB == (rtInf)) {
    helicopter4_DW.TimeStampB = helicopter4_M->Timing.t[0];
    lastU = &helicopter4_DW.LastUAtTimeB;
  } else if (helicopter4_DW.TimeStampA < helicopter4_DW.TimeStampB) {
    helicopter4_DW.TimeStampA = helicopter4_M->Timing.t[0];
    lastU = &helicopter4_DW.LastUAtTimeA;
  } else {
    helicopter4_DW.TimeStampB = helicopter4_M->Timing.t[0];
    lastU = &helicopter4_DW.LastUAtTimeB;
  }

  *lastU = helicopter4_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter4_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter4_M->solverInfo);
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
  if (!(++helicopter4_M->Timing.clockTick0)) {
    ++helicopter4_M->Timing.clockTickH0;
  }

  helicopter4_M->Timing.t[0] = rtsiGetSolverStopTime(&helicopter4_M->solverInfo);

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
    if (!(++helicopter4_M->Timing.clockTick1)) {
      ++helicopter4_M->Timing.clockTickH1;
    }

    helicopter4_M->Timing.t[1] = helicopter4_M->Timing.clockTick1 *
      helicopter4_M->Timing.stepSize1 + helicopter4_M->Timing.clockTickH1 *
      helicopter4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter4_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter4_T *_rtXdot;
  _rtXdot = ((XDot_helicopter4_T *) helicopter4_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter4_P.TravelTransferFcn_A *
    helicopter4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter4_P.PitchTransferFcn_A *
    helicopter4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter4_P.ElevationTransferFcn_A *
    helicopter4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter4_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter4_X.Integrator_CSTATE <= helicopter4_P.Integrator_LowerSat);
  usat = (helicopter4_X.Integrator_CSTATE >= helicopter4_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter4_B.K_ei > 0.0)) || (usat &&
       (helicopter4_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter4_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter4_M, _rt_error_message);
      return;
    }

    if ((helicopter4_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helicopter4_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helicopter4_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter4_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_analog_input_chan, 8U,
        &helicopter4_DW.HILInitialize_AIMinimums[0],
        &helicopter4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter4_P.HILInitialize_set_analog_output && !is_switching) ||
        (helicopter4_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helicopter4_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter4_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_analog_output_cha, 8U,
        &helicopter4_DW.HILInitialize_AOMinimums[0],
        &helicopter4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter4_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helicopter4_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter4_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_analog_output_cha, 8U,
        &helicopter4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter4_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter4_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter4_DW.HILInitialize_Card,
         helicopter4_P.HILInitialize_analog_output_cha, 8U,
         &helicopter4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter4_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helicopter4_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter4_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_encoder_channels, 8U,
        (t_encoder_quadrature_mode *)
        &helicopter4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter4_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helicopter4_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopter4_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_encoder_channels, 8U,
        &helicopter4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter4_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helicopter4_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter4_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter4_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &helicopter4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            helicopter4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopter4_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter4_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter4_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helicopter4_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter4_DW.HILInitialize_Card,
          &helicopter4_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helicopter4_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter4_DW.HILInitialize_Card,
          &helicopter4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopter4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter4_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &helicopter4_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter4_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter4_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helicopter4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helicopter4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter4_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter4_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_pwm_channels, 8U,
        &helicopter4_DW.HILInitialize_POSortedFreqs[0],
        &helicopter4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter4_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helicopter4_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter4_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter4_DW.HILInitialize_Card,
        helicopter4_P.HILInitialize_pwm_channels, 8U,
        &helicopter4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter4_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter4_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter4_DW.HILInitialize_Card,
         helicopter4_P.HILInitialize_pwm_channels, 8U,
         &helicopter4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopter4_DW.HILInitialize_Card,
      helicopter4_P.HILReadEncoderTimebase_samples_,
      helicopter4_P.HILReadEncoderTimebase_channels, 3,
      &helicopter4_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter4_M, _rt_error_message);
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
      3.0885337593590236, 3.0489883906113238, 2.9945850589417717,
      2.9240247721246906, 2.8364358562019203, 2.7328618074809965,
      2.61772420048115, 2.495444609721611, 2.370444609721611, 2.245444609721611,
      2.120444609721611, 1.995444609721611, 1.870444609721611, 1.745444609721611,
      1.620444609721611, 1.495444609721611, 1.370444609721611, 1.245444609721611,
      1.120444609721611, 0.995444609721611, 0.870444609721611, 0.745444609721611,
      0.620444609721611, 0.49818702395898995, 0.38269660608475281,
      0.27757100480819796, 0.1855501457301246, 0.10855965827684912,
      0.047888907323077712, 0.0036189543777907052, -0.025585717540186112,
      -0.042053103945347836, -0.048436149549232928, -0.047387799063379851,
      -0.041560997199327064, -0.033258000745277926, -0.024259489524994755,
      -0.015797371367613288, -0.0086085551850160619, -0.0030284171532220356,
      0.00090346634899262344, 0.0033423510056471771, 0.0045518384234357074,
      0.0048363968713771967, 0.0044934265548987875, 0.0037832034682227563,
      0.00291357709292996, 0.0020359486445280114, 0.0012487124526683333,
      0.00060544826824725283, 0.00012499190327521298, -0.00019824099628028643,
      -0.00038498695350348247, -0.00046341872281793024, -0.00046349618962102882,
      -0.00041301549326077644, -0.00033540795181364539, -0.00024873899823738173,
      -0.00016563569648192958, -9.3875539216139829E-5, -3.7244221701271685E-5,
      3.4357375777051717E-6, 2.9329154453682557E-5, 4.2780220786039123E-5,
      4.6660894588776128E-5, 4.3891996846504129E-5, 3.7095387481275794E-5,
      2.845272068243444E-5, 1.9582752392878428E-5, 1.1567819464135235E-5,
      5.059497750112658E-6, 3.0160873820476237E-7, -2.7594372166778708E-6,
      -4.3022412665273141E-6, -4.6519420333888032E-6, -4.158904834336043E-6,
      -3.14474418494229E-6, -1.9365619866333305E-6, -7.9265882868894726E-7,
      1.4224103053173207E-7, 8.0223843645557721E-7, 1.1657056975257584E-6,
      1.265219643744125E-6, 1.1180310657515682E-6, 7.8000916257033644E-7,
      3.5562233624960691E-7, -5.6182861607125655E-8, -3.777077007287542E-7,
      -5.7358463380306342E-7, -6.1540526762555926E-7, -5.1902619766866049E-7,
      -3.2807621452214185E-7, -7.5414362317551162E-8, 2.08571537706191E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.010611778846153847,
      -0.031835336538461545, -0.06367067307692309, -0.10611778846153848,
      -0.15818147499079921, -0.21761332667820829, -0.28224114726832533,
      -0.35035566369108123, -0.41429619488369551, -0.46055042799938678,
      -0.48911836303815492, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
      -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.48903034305048432,
      -0.46196167149694861, -0.42050240510621939, -0.36808343631229345,
      -0.307961949813102, -0.24268300381508559, -0.177079811781148,
      -0.11681868767190727, -0.0658695456206469, -0.02553218241554037,
      0.0041934019434123112, 0.023307207456211145, 0.033211985816196526,
      0.0359940448811327, 0.033848472629525866, 0.028755264730388905,
      0.022320552127176107, 0.015727534008858634, 0.009755538626618215,
      0.0048379496711541212, 0.0011382337917659592, -0.0013718812659136354,
      -0.0028408923467041275, -0.0034785055011711864, -0.0035105137936077926,
      -0.0031489447674387131, -0.0025730567376843218, -0.0019218254598881591,
      -0.0012929315982219977, -0.00074698382889278416, -0.00031372707725779112,
      -3.0986721239426976E-7, 0.00020192278544100927, 0.00031043016578852429,
      0.00034667581430505487, 0.00033241320702180854, 0.00028704062906315895,
      0.0002265252700594726, 0.00016271983711590743, 0.00010357366750390953,
      5.3804265329426265E-5, 1.5522695210947998E-5, -1.1075590969087995E-5,
      -2.7186437460913336E-5, -3.4570667195365406E-5, -3.5479873158224045E-5,
      -3.2059731714972771E-5, -2.6033286856090303E-5, -1.9031556047631585E-5,
      -1.2244183819530532E-5, -6.1712161993977754E-6, -1.3988030674459557E-6,
      1.9721487962110456E-6, 4.0566425975750071E-6, 4.8327287932358411E-6,
      4.575612631777531E-6, 3.7395994368827174E-6, 2.63998962369538E-6,
      1.4538690442807227E-6, 3.980557848734679E-7, -5.88754311970228E-7,
      -1.3520876127249246E-6, -1.6975473052829186E-6, -1.64722079142693E-6,
      -1.2860993564865129E-6, -7.8350773229723507E-7, -1.6728253528998857E-7,
      3.8551627982759495E-7, 7.63799932586075E-7, 1.0106474088183636E-6,
      1.1359436000949683E-6, 1.1780136647103174E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.075, 0.15, 0.22499999999999998, 0.3, 0.36796625205865552,
      0.42004162932317657, 0.4567647530664064, 0.48140738756144164,
      0.45190725409662852, 0.32690725409662852, 0.20190725409662852,
      0.0769072540966285, -1.5747504220080624E-16, 1.3259728309966267E-16,
      3.3109371296517451E-16, 1.2239988036510714E-16, 1.6142519760237383E-16,
      1.948769669259438E-16, -1.7916437315632314E-16, -1.72687827645542E-16,
      -7.3168875900462358E-17, -1.3302933387788928E-16, 3.28243537475615E-17,
      -8.0959033194303738E-17, 1.1034434666386852E-16, -8.1334512135994133E-17,
      -0.077529345752608433, -0.19131103238652478, -0.2930182605936687,
      -0.37047725141476734, -0.42491570478531482, -0.4613666587695347,
      -0.4636583059143396, -0.42590261008229957, -0.36008907735855106,
      -0.28508907735855105, -0.21008907735855104, -0.13508907735855102,
      -0.070003190583654715, -0.019662530938046995, 0.015164085230520584,
      0.035996848216802164, 0.045478091113430562, 0.046596934033640312,
      0.042207782518043059, 0.034755640595872626, 0.026148178828159622,
      0.017740534556485069, 0.010382409269603203, 0.0045064062565120036,
      0.00022622238623221582, -0.0025554317853608058, -0.0040701566493004894,
      -0.004602653951124764, -0.0044447816250955336, -0.00385855032349563,
      -0.0030620932497478267, -0.0022151131392946838, -0.0014293031516108708,
      -0.00076688872280948411, -0.000256170400660495, 0.00010080266105726256,
      0.00032067605217122355, 0.00042769944521803467, 0.0004509524312695058,
      0.00041802253752278495, 0.00035175112647952838, 0.00027055951697735228,
      0.00018798652821771952, 0.00011386530989805204, 5.2188915554401331E-5,
      6.425920498627151E-6, -2.4172253489509489E-5, -4.2592610623430293E-5,
      -4.9485559230697027E-5, -4.7970554653245631E-5, -4.2921415731825109E-5,
      -3.3729593321304063E-5, -2.382460032757921E-5, -1.473240607148162E-5,
      -5.4850808256015438E-6, 1.8171988305582264E-6, 5.9086219686755441E-6,
      7.771622193101127E-6, 8.3830472483264917E-6, 7.4620848779038038E-6,
      6.9743968788137534E-6, 5.3949482350314956E-6, 2.4415771679260174E-6,
      -3.5568857907052906E-7, -2.5522683815020954E-6, -3.5521256483645877E-6,
      -4.3552443417433672E-6, -3.9069708985544467E-6, -2.6735643823908886E-6,
      -1.7446236852298998E-6, -8.8554562641977063E-7, -2.9733514916726319E-7,
      -6.9389863814782268E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.3, 0.3, 0.3, 0.3,
      0.271865008234622, 0.20830150905808423, 0.14689249497291942,
      0.098570537980140926, -0.11800053385925249, -0.5, -0.5, -0.5,
      -0.30762901638651469, 1.1602893012018756E-15, 7.9398571946204714E-16,
      -8.3477533040026948E-16, 1.5610126894906681E-16, 1.3380707729427985E-16,
      -1.4961653603290677E-15, 2.59061820431246E-17, 3.9807592524782356E-16,
      -2.3944194195476478E-16, 6.6341473963319516E-16, -4.5513364237434875E-16,
      7.6521359159785039E-16, -7.6671553360241219E-16, -0.3101173830104334,
      -0.45512674653566532, -0.4068289128285757, -0.3098359632843945,
      -0.21775381348218981, -0.14580381593687947, -0.0091665885792195038,
      0.15102278332816021, 0.26325413089499389, 0.3, 0.3, 0.3,
      0.26034354709958524, 0.20136263858243086, 0.13930646467427032,
      0.083331051945126342, 0.037924971586513583, 0.0044753716808390064,
      -0.017556606062389023, -0.02980856768868172, -0.034429847070852004,
      -0.033630577086698213, -0.029432501147527469, -0.023504012052364798,
      -0.017120735481119153, -0.011126616686372087, -0.0060588994557587315,
      -0.0021299892072970997, 0.00063148930411692364, 0.002344925206399613,
      0.0031858282949912124, 0.0033879204418125718, 0.0031432399507352509,
      0.0026496577152055473, 0.0020428732885959559, 0.0014278922468710304,
      0.000879493564455844, 0.00042809357218724447, 9.3011944205884589E-5,
      -0.00013171957498688347, -0.0002650856441730262, -0.00032476643800870433,
      -0.00033029195503853103, -0.00029648487327866993, -0.00024670557737460283,
      -0.00018305198022309672, -0.00012239269595254657, -7.3681428535683218E-5,
      -2.7571794429066917E-5, 6.0600183098055561E-6, 2.0196555685682094E-5,
      3.6767289642084191E-5, 3.9619971974899405E-5, 3.6368777024390361E-5,
      3.69893009835203E-5, 2.9209118624639084E-5, 1.6365692552469271E-5,
      7.4520008977023285E-6, 2.4457002209014617E-6, -3.6838494816907579E-6,
      -1.9507519963602024E-6, -6.3177945751290313E-6, -1.1813484268421913E-5,
      -1.1189062987986186E-5, -8.7863192097262653E-6, -3.9994290674499709E-6,
      -3.2124747735151163E-6, 1.7930937727556805E-6, 4.9336260646542315E-6,
      3.7157627886439549E-6, 3.4363122352405146E-6, 2.3528419090100306E-6,
      -1.5862539559222388E-6, 2.9700480308979755E-6, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0098040282912313578, 0.022304028291231359,
      0.034804028291231352, 0.047304028291231356, 0.059804028291231354,
      0.072304028291231365, 0.084804028291231362, 0.097304028291231359,
      0.10980402829123136, 0.12230402829123135, 0.13480402829123136,
      0.14730402829123138, 0.15980402829123139, 0.1723040282912314,
      0.18480402829123141, 0.19730402829123142, 0.20379184023126151,
      0.2055751805815367, 0.20372871821899435, 0.1991320240690051,
      0.19250151108353958, 0.18441725436014719, 0.17534629573973909,
      0.165661523240942, 0.15565819837980771, 0.14556723242043135,
      0.13556674932924026, 0.12579166359599145, 0.1163419365385062,
      0.10728895947525165, 0.098681199723102062, 0.090548708245515,
      0.082907280226724264, 0.07576127790923709, 0.069106235329619042,
      0.0629310502166759, 0.057219762506254809, 0.051952917680541326,
      0.04710866249616915, 0.042663587369687457, 0.038593669642153418,
      0.034874605481477444, 0.031482331259770763, 0.028393163356817165,
      0.025584419080375689, 0.023034275539997928, 0.020721909769684955,
      0.018627718410859143, 0.016733385726849213, 0.015021631728423893,
      0.013476495860131183, 0.012082980236483236, 0.010827363651039082,
      0.0096969506331879163, 0.0086800860036262677, 0.0077659929475463151,
      0.0069449038431805884, 0.0062078541341728695, 0.005546644971495502,
      0.0049538125403046787, 0.00442256051409681, 0.0039467260191806807,
      0.0035208090124662821, 0.0031397758590982713, 0.0027991365476501078,
      0.0024947442095917109, 0.0022229014306040006, 0.0019802791977339036,
      0.0017636806907414576, 0.0015701526503155204, 0.0013976681763483755,
      0.0012439834939757025, 0.0011069515972718018, 0.00098485508656981119,
      0.00087609543813182663, 0.00077932246698679119, 0.00069312890480994571,
      0.000616383901293058, 0.00054815338990473763, 0.00048741723833379495,
      0.00043339491929617291, 0.0003854284082121306, 0.00034273855948194226,
      0.00030477953464809427, 0.00027110000188704784, 0.00024120847861678696,
      0.00021462588327845848, 0.00019098206679920006, 0.00017007126809855336,
      0.00015148522267207566, 0.00013492963558721773, 0.00012024105604490498,
      0.00010731354908725789, 9.5808766213166673E-5, 8.5356876308011859E-5,
      7.6109162223407856E-5, 6.77202803154118E-5, 6.0272990859518656E-5,
      5.3528291643338168E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.039216113164925431, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05,
      0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.025951247760120408,
      0.0071333614011007624, -0.0073858494501694164, -0.018386776599957144,
      -0.026522051941861975, -0.032337026893569626, -0.036283834481632388,
      -0.038739089995188346, -0.040013299444537111, -0.040363863837505495,
      -0.040001932364764341, -0.03910034293299533, -0.037798908229940989,
      -0.036211908253018177, -0.034431039008598389, -0.0325299659103482,
      -0.030565712075162975, -0.028584009269948672, -0.026620170318472185,
      -0.024700740451772556, -0.022845150841684373, -0.021067379302853923,
      -0.019377020737488728, -0.017780300505926765, -0.01627967091013614,
      -0.014876256642703896, -0.013569096886826717, -0.012356671611814392,
      -0.011234977105765903, -0.010200574161511048, -0.0092494630812518831,
      -0.0083767654353032565, -0.0075773307360397241, -0.0068470159937012763,
      -0.00618054347317084, -0.0055740624945917906, -0.005022466341776618,
      -0.0045216520714046636, -0.004067458518246591, -0.0036563722243198051,
      -0.00328435641746291, -0.002948198836030873, -0.0026448366507094709,
      -0.0023713297247632925, -0.0021250081048314736, -0.0019033379796645192,
      -0.0017036680268575938, -0.0015241326134720437, -0.0013625572457926537,
      -0.0012175693522335871, -0.0010873711159508409, -0.00097048893148038884,
      -0.0008663940279697843, -0.00077411216170374954, -0.00068993789586857914,
      -0.00061473872949069223, -0.0005481275868156032, -0.00048838604280796133,
      -0.00043503859375193841, -0.0003870918845801421, -0.00034477424870738179,
      -0.00030698001406755094, -0.00027292204555328097, -0.00024294460628377089,
      -0.00021608927615048812, -0.00019186604433616932, -0.00017075939492075323,
      -0.00015183609933539215, -0.00013471813104418555, -0.00011956609308104352,
      -0.00010633038135331387, -9.4575265917033627E-5, -8.3643194802586848E-5,
      -7.4344181705910862E-5, -6.6222348339431712E-5, -5.875431816925099E-5,
      -5.1710027830588404E-5, -4.6019131496364823E-5, -4.1807559620619255E-5,
      -3.699085633841602E-5, -3.3555527631984206E-5, -2.9789157823572596E-5,
      -2.6978796864721949E-5, -2.4001159577261377E-5, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter4_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter4_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter4_DW.FromWorkspace1_IWORK.PrevIndex = 0;
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
      0.0, 0.37037037037037041, 0.33333333333333337, 0.40833333333333333,
      0.48333333333333334, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.29891587941546,
      -0.12130859591272479, -0.10364830145892708, -0.22864830145892712,
      -0.11615325996079706, 0.11488614500854533, 6.7950864834469956E-16,
      -9.9601247288363877E-16, 6.268700117171421E-16, 2.6832204135198755E-16,
      -1.7022119234574976E-15, 4.1157168060005656E-16, 3.0908909232949311E-16,
      -5.1744028929425795E-16, 7.7542246328228155E-16, -7.7682575739038227E-16,
      1.0337218866178626E-15, -1.1219921932826523E-15, -0.38286096667954728,
      -0.52359877559829882, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.52359877559829882, -0.41823200970572416,
      -0.27378710051511218, -0.15729799410918172, -0.088032749698965435,
      -0.026755744025217687, 0.048244255974782282, 0.074285672147109807,
      0.081365594088945725, 0.07712051412749002, 0.066016981997384261,
      0.051697253615706949, 0.036839903182465925, 0.02325075379185905,
      0.011963715413340535, 0.00338186856497659, -0.00251299197155085,
      -0.0060363192445041444, -0.0076431221566162291, -0.00785257131790627,
      -0.007116486506772159, -0.005880244017621516, -0.0044370358121771352,
      -0.0030275785939342745, -0.0017856462029915286, -0.0008011572123162112,
      -6.9244629281493725E-5, 0.0004001881163682147, 0.00066801491025102286,
      0.00076564440033406939, 0.00074373463276018856, 0.00065334112991819761,
      0.00052073379160252193, 0.00038265455462450774, 0.00025359972990016811,
      0.00013994787981970596, 4.9802940496363089E-5, -1.5922097270669927E-5,
      -5.4694406201433968E-5, -7.9985187889361771E-5, -8.1667310454585558E-5,
      -7.6314168310088687E-5, -6.9428596711778486E-5, -4.9115033212347267E-5,
      -3.1707181299094186E-5, -2.5299690274275374E-5, -5.0722409822382485E-6,
      1.4529583554477106E-6, 6.278776835363128E-6, 1.7351230883632234E-5,
      1.6761653837514747E-5, 1.1113413853417424E-5, 8.9967440681574888E-6,
      8.0080048466153324E-6, 2.921721571149392E-6, 6.4295076826584357E-6,
      -9.6827931346828876E-8, -6.8301769618146551E-6, -6.9602549268746719E-6,
      -7.0243646974167573E-6, -4.2085245623758924E-6, -6.0245299454158214E-6,
      -9.4182780872607834E-7, 1.5142824327981933E-6, 7.130093129559348E-8,
      1.1100602551104936E-6, 7.3588333388859348E-7, -3.1343581533620445E-6,
      3.5652246366231064E-6, 3.5652246366231064E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.6274578106388069, 0.32940664202089492, 0.20980402829123135,
      0.2223040282912313, 0.23480402829123126, 0.24730402829123133,
      0.25980402829123128, 0.27230402829123135, 0.2848040282912313,
      0.29730402829123137, 0.30980402829123133, 0.32230402829123128,
      0.33480402829123135, 0.3473040282912313, 0.35980402829123137,
      0.37230402829123133, 2.399245315784179E-5, 2.2837587398737566E-5,
      1.7912215341702065E-5, 1.694838425540689E-5, 1.7206348688460054E-5,
      4.217074234793831E-6, 4.4821002569935746E-6, -2.1717832776756654E-6,
      2.5845694054228351E-6, -7.0482470060676849E-7, -6.3534063557829451E-6,
      -1.5066130321839791E-5, -1.1667153871648333E-5, -1.196969300757546E-5,
      -1.178856284989414E-5, -1.8026987138966515E-5, -1.060255532708278E-5,
      -6.8951717080614861E-6, -7.3336294466367331E-6, -8.5254974576154113E-6,
      -7.29271606023109E-6, -5.2085287743466565E-6, -4.0176593177738817E-6,
      -7.641564422181546E-6, -2.4659948878888408E-6, -4.6799194123258709E-7,
      3.1991653727071903E-6, -2.9776656322209284E-6, 2.7569092889997403E-6,
      3.7020418312321697E-6, -1.0028152185908666E-7, -4.1444983157836133E-7,
      5.8032166884333E-6, 3.4313441153988675E-6, 8.8820805310785952E-6,
      3.1534930053301818E-6, 5.7843268067797132E-6, 6.1431953280293741E-6,
      7.8522159496024828E-6, 4.4972630301176546E-6, 6.8500160573731169E-6,
      7.08858060726379E-6, 5.9034641995316713E-6, 4.6183464738417083E-6,
      2.4719913514339492E-6, 5.0212365005857577E-7, 3.9278403495372133E-6,
      4.6205259191057815E-6, 9.48444144834755E-6, 9.3531728727222171E-6,
      1.2030919239698341E-5, 1.5374697315579037E-5, 6.4641608521158959E-6,
      -8.787053888674797E-6, 1.4020297289184868E-5, 1.3587728887396012E-5,
      4.491541187030553E-6, 7.3378508355593993E-6, 6.9666109363225046E-6,
      1.1848058310799718E-5, 4.8100737754233057E-6, 4.9332263945575114E-6,
      1.0136344768060718E-5, 4.33474739209519E-6, 6.0602469021785707E-6,
      1.0631842760943163E-5, 3.6371325981532814E-6, 5.1635578948947988E-6,
      9.2816547996796013E-6, 8.3396178816242418E-6, 4.6070172065479491E-6,
      3.9688001840156555E-6, 1.1237957441472427E-5, 5.1934971356685053E-6,
      2.6438751385762433E-6, 6.0843120372403226E-6, 1.2621008328815177E-5,
      4.4552860701286304E-6, -9.3778268862723378E-6, 5.6457802459414716E-6,
      -7.6412897427431683E-6, 2.1489686300568215E-6, -6.4705756372682858E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter4_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter4_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopter4_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter4_X.Integrator_CSTATE = helicopter4_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter4_DW.TimeStampA = (rtInf);
  helicopter4_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter4_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helicopter4_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter4_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter4_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helicopter4_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter4_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter4_DW.HILInitialize_Card
                         , helicopter4_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter4_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter4_DW.HILInitialize_AOVoltages[0]
                         , &helicopter4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter4_DW.HILInitialize_Card,
            helicopter4_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs, &helicopter4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter4_DW.HILInitialize_Card,
            helicopter4_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helicopter4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter4_DW.HILInitialize_Card);
    hil_close(helicopter4_DW.HILInitialize_Card);
    helicopter4_DW.HILInitialize_Card = NULL;
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
  helicopter4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter4_update();
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
  helicopter4_initialize();
}

void MdlTerminate(void)
{
  helicopter4_terminate();
}

/* Registration function */
RT_MODEL_helicopter4_T *helicopter4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter4_P.Integrator_UpperSat = rtInf;
  helicopter4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter4_M, 0,
                sizeof(RT_MODEL_helicopter4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter4_M->solverInfo,
                          &helicopter4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter4_M->solverInfo, &rtmGetTPtr(helicopter4_M));
    rtsiSetStepSizePtr(&helicopter4_M->solverInfo,
                       &helicopter4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter4_M->solverInfo, &helicopter4_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter4_M->solverInfo, (real_T **)
                         &helicopter4_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter4_M->solverInfo,
      &helicopter4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter4_M->solverInfo,
      &helicopter4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter4_M->solverInfo,
      &helicopter4_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter4_M->solverInfo,
      &helicopter4_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter4_M->solverInfo, (&rtmGetErrorStatus
      (helicopter4_M)));
    rtsiSetRTModelPtr(&helicopter4_M->solverInfo, helicopter4_M);
  }

  rtsiSetSimTimeStep(&helicopter4_M->solverInfo, MAJOR_TIME_STEP);
  helicopter4_M->ModelData.intgData.f[0] = helicopter4_M->ModelData.odeF[0];
  helicopter4_M->ModelData.contStates = ((real_T *) &helicopter4_X);
  rtsiSetSolverData(&helicopter4_M->solverInfo, (void *)
                    &helicopter4_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter4_M->Timing.sampleTimes = (&helicopter4_M->
      Timing.sampleTimesArray[0]);
    helicopter4_M->Timing.offsetTimes = (&helicopter4_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter4_M->Timing.sampleTimes[0] = (0.0);
    helicopter4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter4_M->Timing.offsetTimes[0] = (0.0);
    helicopter4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter4_M, &helicopter4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter4_M, -1);
  helicopter4_M->Timing.stepSize0 = 0.002;
  helicopter4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter4_M->Sizes.checksums[0] = (2056774572U);
  helicopter4_M->Sizes.checksums[1] = (1020395416U);
  helicopter4_M->Sizes.checksums[2] = (3575393286U);
  helicopter4_M->Sizes.checksums[3] = (3111446719U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter4_M->extModeInfo,
      &helicopter4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter4_M->extModeInfo,
                        helicopter4_M->Sizes.checksums);
    rteiSetTPtr(helicopter4_M->extModeInfo, rtmGetTPtr(helicopter4_M));
  }

  helicopter4_M->solverInfoPtr = (&helicopter4_M->solverInfo);
  helicopter4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter4_M->ModelData.blockIO = ((void *) &helicopter4_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter4_B.TmpSignalConversionAtToWorkspac[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      helicopter4_B.Gain1[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      helicopter4_B.FromWorkspace1[i] = 0.0;
    }

    for (i = 0; i < 12; i++) {
      helicopter4_B.TmpSignalConversionAtToWorksp_o[i] = 0.0;
    }

    helicopter4_B.TravelCounttorad = 0.0;
    helicopter4_B.Gain = 0.0;
    helicopter4_B.Gain_d = 0.0;
    helicopter4_B.PitchCounttorad = 0.0;
    helicopter4_B.Gain_i = 0.0;
    helicopter4_B.Gain_b = 0.0;
    helicopter4_B.Sum3 = 0.0;
    helicopter4_B.ElevationCounttorad = 0.0;
    helicopter4_B.Gain_e = 0.0;
    helicopter4_B.Sum = 0.0;
    helicopter4_B.Gain_dg = 0.0;
    helicopter4_B.Sum1 = 0.0;
    helicopter4_B.Sum2 = 0.0;
    helicopter4_B.K_ei = 0.0;
    helicopter4_B.Gain_l = 0.0;
    helicopter4_B.BackmotorSaturation = 0.0;
    helicopter4_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter4_M->ModelData.defaultParam = ((real_T *)&helicopter4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter4_X;
    helicopter4_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter4_X, 0,
                  sizeof(X_helicopter4_T));
  }

  /* states (dwork) */
  helicopter4_M->ModelData.dwork = ((void *) &helicopter4_DW);
  (void) memset((void *)&helicopter4_DW, 0,
                sizeof(DW_helicopter4_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter4_DW.TimeStampA = 0.0;
  helicopter4_DW.LastUAtTimeA = 0.0;
  helicopter4_DW.TimeStampB = 0.0;
  helicopter4_DW.LastUAtTimeB = 0.0;
  helicopter4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter4_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter4_M->Sizes.numY = (0);     /* Number of model outputs */
  helicopter4_M->Sizes.numU = (0);     /* Number of model inputs */
  helicopter4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter4_M->Sizes.numBlocks = (72);/* Number of blocks */
  helicopter4_M->Sizes.numBlockIO = (21);/* Number of block outputs */
  helicopter4_M->Sizes.numBlockPrms = (155);/* Sum of parameter "widths" */
  return helicopter4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
