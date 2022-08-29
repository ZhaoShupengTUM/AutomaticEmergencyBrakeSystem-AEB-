// Copyright 2020 Feiler
// not for open source

#pragma once

namespace tod_helper::Status {

class ModeChecker {
public:
    virtual ~ModeChecker() = default;
    virtual bool modeIsChosen() const = 0;
};

}; // namespace tod_helper::Status
