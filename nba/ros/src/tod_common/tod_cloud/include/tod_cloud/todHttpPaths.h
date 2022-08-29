#pragma once
#include <string>
#include "sstream"

namespace tod{
namespace HttpPath{

static std::string fleet(){
    return "/car";
};

static std::string car(int id){ // ... /fleet/<id>
    std::stringstream ss;
    ss << "/car/" << id;
    return ss.str();
};

static std::string pose(int id){// ... /fleet/<id>/pose
    std::stringstream ss;
    ss << "/car/" << id << "/status/position";
    return ss.str();
};

static std::string route(int id){// ... /fleet/<id>/pose
    std::stringstream ss;
    ss << "/car/" << id << "/route";
    return ss.str();
};

}
}