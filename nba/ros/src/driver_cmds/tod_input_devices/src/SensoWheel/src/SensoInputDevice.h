// Copyright 2020 Simon Hoffmann
#pragma once
#include "InputDevice.h"
#include "AudiSteeringWheelController.h"
#include <iostream>
#include "SensoController.h"
#include <thread>
#include <vector>
class SensoInputDevice : public InputDevice {
public:
    SensoInputDevice(std::function<void(const int, const double)> axisCb,
        std::function<void(const int, const int)> buttonCb);
    ~SensoInputDevice();

    bool activate() override;
    bool deactivate() override;

private:
    void onSteeringWheelMsgReceived(const int steeringPosition);
    void onPedalMsgReceived(const int accPedalPos, const int breakPedalPos, const int clutchPedalPos);
    void onButtonCallback(const std::vector<bool> &buttonState);

    SensoController _sensoController;
    AudiSteeringWheelController _audiController;
    std::thread _sensoRecvThread;
    std::thread _sensoCyclThread;
    std::thread _audiRecvThread;

    void DoCyclicEvents();
};

