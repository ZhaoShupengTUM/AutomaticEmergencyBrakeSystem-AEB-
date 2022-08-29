// Copyright 20xx FTM
#pragma once
#include "CanInterface.h"
#include <functional>
#include <cstring>

typedef void(*MessageSendFunction)(uint64_t Identifier, unsigned char Length, BYTE* Data);
typedef void(*HandleErrorsFunction)(uint16_t uiError, bool bIsError);
typedef void(*HandleStatusFunction)(uint16_t uiStatus);

#define NU_POSITION_INCREMENTS 40000
#define MIN_POSITION_INCREMENTS (-1.25*NU_POSITION_INCREMENTS)
#define MAX_POSITION_INCREMENTS (1.25*NU_POSITION_INCREMENTS)
#define MIN_ACC_PEDAL_INCREMENTS 1980
#define MAX_ACC_PEDAL_INCREMENTS 2630
#define MIN_BRAKE_PEDAL_INCREMENTS 900
#define MAX_BRAKE_PEDAL_INCREMENTS 3350
#define MIN_CLUTCH_PEDAL_INCREMENTS 1990
#define MAX_CLUTCH_PEDAL_INCREMENTS 2600

class SensoController : public CanInterface{
private:
    void SendControlMessage();
    void SendMessage(unsigned int Identifier, unsigned char Length, BYTE* Data);
    void SendIO(uint16_t uiDigOut);
    void CheckSensoWheelStatus(int status, char* pTxtBuf);
    void CheckSensoWheelError(int status, char* pTxtBuf);

    uint16_t _uiCurrentError;
    uint16_t _uiInitStage;
    uint16_t _uiControlWord;
    uint16_t _uiCurrentState;
    uint16_t _uiAuxiliaryFunctions;
    uint16_t _uiDigitalInputs;
    uint16_t _uiAnalogInput1;
    uint16_t _uiAnalogInput2;
    BYTE _uiControlTorqueLimitation;
    BYTE _uiControlPeakTorqueLimitation;
    int _nEndStopPosition;
    int _nPositionOffset;
    int _nAnalogWheelPosition;
    int _nEncoderIndexPositionReceived;
    int _nActualSteeringPosition;
    int _nActualSteeringVelocity;
    int _nActualSteeringTorque;
    int _nActualAccPedalPos;
    int _nActualBrakePedalPos;
    int _nActualClutchPedalPos;
    int _nDemandedTorque;
    int _nDemandedFriction;
    int _nDemandedDamping;
    int _nDemandedStiffness;
    bool _bInputsReceived;
    bool _bAbsolutePositionSet;

    std::function<void(const int)> _steering_callback;
    std::function<void(const int, const int, const int)> _pedal_callback;

    HandleErrorsFunction    _cbHandleErrors;
    HandleStatusFunction    _cbHandleStatus;
    MessageSendFunction _cbMessageSend;

public:
    SensoController();
    ~SensoController();

    void HandleReply(unsigned int Identifier, unsigned char Length, const BYTE* Data) override;
    void SwitchOff();
    void HandleErrors();
    void HandleStatus();
    void CalculateAbsoluteWheelPosition(uint16_t _uiAnalogInput);
    void DoCyclicEvents();
    bool InitWheel();
    void set_steering_callback(std::function<void(const int)> f);
    void set_pedal_callback(std::function<void(const int, const int, const int)> f);
    void reset_values();
};

