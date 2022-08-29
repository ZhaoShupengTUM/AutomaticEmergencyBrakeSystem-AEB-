// Copyright 2020 Feiler

#if defined(PERCEPTION_MODIFICATION_TRUE_MACRO) || defined(NOT_OPEN_SOURCE_MACRO)
#pragma once

namespace tod_helper::Status {

class ModeChecker {
public:
    virtual ~ModeChecker() = default;
    virtual bool modeIsChosen() const = 0;
};

}; // namespace tod_helper::Status

#endif
