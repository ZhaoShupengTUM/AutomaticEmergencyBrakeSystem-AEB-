// Copyright 20xx FTM
#pragma once

#include "CanInterface.h"
#include <iostream>
#include <vector>
#include <functional>

class AudiSteeringWheelController : public CanInterface {
public:
    AudiSteeringWheelController();
    ~AudiSteeringWheelController();
    void set_button_callback(std::function<void(const std::vector<bool>)> f);

private:
    std::vector<bool> buttonState;
    std::function<void(const std::vector<bool>)> _button_callback;
    void HandleReply(unsigned int Identifier, unsigned char Length, const BYTE* Data) override;
};

