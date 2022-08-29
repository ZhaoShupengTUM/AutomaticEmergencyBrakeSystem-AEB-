// Copyright 2020 Simon Hoffmann
#include "SensoInputDevice.h"
#include <signal.h>


SensoInputDevice::SensoInputDevice(std::function<void(const int, const double)> axisCb,
        std::function<void(const int, const int)> buttonCb) : InputDevice(axisCb, buttonCb) {
    auto steeringWheelCallback = std::bind(
        &SensoInputDevice::onSteeringWheelMsgReceived, this, std::placeholders::_1);
    auto pedalCallback = std::bind(&SensoInputDevice::onPedalMsgReceived, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    auto buttonCallback = std::bind(
        &SensoInputDevice::onButtonCallback, this, std::placeholders::_1);

    _sensoController.set_steering_callback(steeringWheelCallback);
    _sensoController.set_pedal_callback(pedalCallback);
    _audiController.set_button_callback(buttonCallback);
}

SensoInputDevice::~SensoInputDevice() {
    deactivate();
}

bool SensoInputDevice::activate() {
    _sensoController.Init();
    _audiController.Init();

    // Create Threads
    _audiRecvThread = std::thread(&AudiSteeringWheelController::run, &_audiController);
    _sensoRecvThread = std::thread(&SensoController::run, &_sensoController);
    _sensoCyclThread = std::thread(&SensoInputDevice::DoCyclicEvents, this);

    _sensoController.reset_values();
    _sensoController.InitWheel();
    running = true;
    return true;
}

bool SensoInputDevice::deactivate() {
    if (running) {
        _sensoController._bGetData = false;
        _sensoController.SwitchOff();
        _sensoController.close();

        _audiController._bGetData = false;
        _audiController.close();

        usleep(5000);
        if (_sensoRecvThread.joinable()) { _sensoRecvThread.join();}
        if (_audiRecvThread.joinable()) { _audiRecvThread.join();}
        if (_sensoCyclThread.joinable()) { _sensoCyclThread.join();}

        running = false;
    }

    return true;
}

void SensoInputDevice::DoCyclicEvents() {
    while (_sensoController._bGetData) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        if (_sensoController.InitWheel()) {
            _sensoController.DoCyclicEvents();
        }
    }
}

void SensoInputDevice::onSteeringWheelMsgReceived(int steeringPosition) {
    static int lastSteeringPos{0};
    if (std::abs(steeringPosition-lastSteeringPos) > 3) {
        axisCallback(0, -scaleValue(steeringPosition, MIN_POSITION_INCREMENTS, MAX_POSITION_INCREMENTS));
        lastSteeringPos = steeringPosition;
    }
}

void SensoInputDevice::onPedalMsgReceived(int accPedalPos, int breakPedalPos, int clutchPedalPos) {
    static int lastAccPedal{0};
    static int lastBreakPedal{0};
    static int lastClutchPedal{0};

    if (std::abs(accPedalPos-lastAccPedal) > 10) {
        axisCallback(1, scaleValue(accPedalPos, MIN_ACC_PEDAL_INCREMENTS, MAX_ACC_PEDAL_INCREMENTS));
        lastAccPedal = accPedalPos;
    }

    if (std::abs(breakPedalPos - lastBreakPedal) > 10) {
        axisCallback(2, scaleValue(breakPedalPos, MIN_BRAKE_PEDAL_INCREMENTS, MAX_BRAKE_PEDAL_INCREMENTS));
        lastBreakPedal = breakPedalPos;
    }

    if (std::abs(clutchPedalPos - lastClutchPedal) > 10) {
        axisCallback(3, scaleValue(clutchPedalPos, MIN_CLUTCH_PEDAL_INCREMENTS, MAX_CLUTCH_PEDAL_INCREMENTS));
        lastClutchPedal = clutchPedalPos;
    }
}

void SensoInputDevice::onButtonCallback(const std::vector<bool> &buttonState)  {
    static std::vector<bool> prevButtonState;
    if (prevButtonState.size() != buttonState.size())
        prevButtonState.assign(buttonState.size(), false);

    for (int button = 0; button < buttonState.size(); ++button) {
        if (prevButtonState.at(button) != buttonState.at(button)) {
            buttonCallback(button, buttonState.at(button));
        }
    }
    prevButtonState = buttonState;
}
