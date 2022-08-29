#pragma once
#include<iostream>

#include "curlpp/cURLpp.hpp"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Exception.hpp>
#include "tod_cloud/todHttpMsgs.h"
#include "ros/ros.h"
#include <sstream>
class HttpHandler{
public:
    HttpHandler(const std::string& base_url);
    long post(const tod::HttpMsg::TodHttpMsg& msg, const std::string& path);
    long put(const tod::HttpMsg::TodHttpMsg& msg, const std::string& path);
    long get(tod::HttpMsg::TodHttpMsg& msg, const std::string& path);
    long post_query(const tod::HttpMsg::TodHttpMsg& msg, const std::string& path);
    void setIpAddress(const std::string& ipAddress);
private:
    long request(curlpp::Easy& request, std::stringstream& response, const std::string& path);
    std::string _url;
};

