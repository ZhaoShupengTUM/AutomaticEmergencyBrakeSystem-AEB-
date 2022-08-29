#pragma once
#include "jsoncpp/json/json.h"
#include "string.h"
#include "ros/ros.h"
#include <vector>
#include <set>

struct Routepoint{
    double longitude;
    double latitude;
    Routepoint() = default;
    Routepoint(double longit, double lat) :
        longitude(longit), latitude(lat) { };
};

namespace tod{
namespace HttpMsg{

class TodHttpMsg{
protected:
    TodHttpMsg() = default;
    
public:
    virtual Json::Value toJson() const = 0;
    virtual void fromString(const std::string& msg) = 0;
    virtual std::string get_query_string() const = 0;
    std::string toJsonString() const{
        Json::StreamWriterBuilder builder;
        builder["indentation"] = ""; // If you want whitespace-less output
        return Json::writeString(builder, this->toJson());
    }
    Json::Value fromStringtoJson(const std::string& input) const{
        Json::Value obj;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( input.c_str(), obj );
        if ( !parsingSuccessful ){
            ROS_ERROR_STREAM("Failed to parse" << reader.getFormattedErrorMessages());
            return Json::Value();
        }
        return obj;
    }
};

class Car : public TodHttpMsg{
public:
    std::string vehicleType{"Taxi"};
    std::string ip_address{"127.0.0.1"};
    int id{1};

    Json::Value toJson() const override{
        Json::Value obj;
        obj[car_str][car_type_str] = vehicleType;
        obj[car_str][ip_address_str] = ip_address;
        obj[car_str][car_id_str] = id;
        return obj;
    }
    void fromString(const std::string& in) override{
        Json::Value obj = fromStringtoJson(in);
        vehicleType = obj[car_str][car_type_str].asString();
        ip_address= obj[car_str][ip_address_str].asString();
        id = obj[car_str][car_id_str].asInt(); 
    }

    std::string get_query_string() const override {
        return "?" + car_id_str + "=" + std::to_string(id) +
                "&" + car_type_str + "=" + vehicleType +
                "&" + ip_address_str + "=" + ip_address;
    }
    
private:
    std::string car_id_str {"car_id"};
    std::string car_type_str {"car_type"};
    std::string ip_address_str {"ip_address"};
    std::string car_str {"car"};
};

class PositionInfo: public TodHttpMsg{
    public:
        double latitude{0.0};
        double longitude{0.0};
        double orientation{0.0};
        double altitude{0.0};
        double timestamp{0.0};

    Json::Value toJson() const override{
        Json::Value obj;
        obj["position"]["latitude"] = latitude;
        obj["position"]["longitude"] = longitude;
        obj["position"]["altitude"] = orientation; // orientation currently not provided
        return obj;
    }
    void fromString(const std::string& in) override{
        Json::Value obj = fromStringtoJson(in);
        latitude = obj["car_id"]["latitude"].asDouble();
        longitude = obj["car_id"]["longitude"].asDouble();
        orientation = obj["car_id"]["altitude"].asDouble(); 
    }
    
    std::string get_query_string() const override {
        return "?";    }
};

class RouteInfo: public TodHttpMsg{
    public:
        Routepoint start;
        Routepoint destination;
        std::vector<Routepoint> route;

    Json::Value toJson() const override{
        Json::Value obj;
        return obj;
    }
    void fromString(const std::string& in) override{
        Json::Value obj = fromStringtoJson(in);
        start = Routepoint(obj["routepoints"]["startwp"]["longitude"].asDouble(),
            obj["routepoints"]["startwp"]["latitude"].asDouble());
        destination = Routepoint(obj["routepoints"]["destwp"]["longitude"].asDouble(),
            obj["routepoints"]["destwp"]["latitude"].asDouble());

        Json::Value points = obj["routepoints"]["routepoints"];    
        for (int i = 0; i < points.size(); i++) {
            route.emplace_back(points[i]["longitude"].asDouble(), points[i]["latitude"].asDouble());
        }
    }
    
    std::string get_query_string() const override {
        return "?";    }
};

class FleetIDs: public TodHttpMsg{
public:
    std::set<int> vehicleIDs;

    Json::Value toJson() const override{
        Json::Value array;
        for(auto id : vehicleIDs){
            array.append(id);
        }
        Json::Value obj;
        obj["IDs"] = array;
        return obj;
    }
    
    void fromString(const std::string& in) override {
        vehicleIDs.clear();
        Json::Value receivedMsg = fromStringtoJson(in);

        for ( Json::Value::iterator vehicleType = receivedMsg.begin();
              vehicleType != receivedMsg.end(); ++vehicleType ) {
            for( Json::Value::iterator vehicleID = vehicleType->begin();
                 vehicleID != vehicleType->end(); ++vehicleID ) {
                vehicleIDs.insert((*vehicleID).asInt());
            }
        }
    }

    std::set<int> getVehicleIds() {
        return vehicleIDs;
    }
    
    std::string get_query_string() const override {
        return "?";    }
};

}} //namespaces


