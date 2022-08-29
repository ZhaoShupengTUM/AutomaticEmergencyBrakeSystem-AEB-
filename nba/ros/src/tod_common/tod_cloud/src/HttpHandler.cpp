#include "tod_cloud/HttpHandler.h"
#include <chrono>

HttpHandler::HttpHandler(const std::string& base_url) {
    _url = base_url;

    bool debug{false}; 
    if (debug) // print ROS_DEBUG
        if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                ros::console::levels::Debug))
            ros::console::notifyLoggerLevelsChanged();
    
    ROS_DEBUG_STREAM("Http Handler for URL " << _url << " initialized!");
}

long HttpHandler::post(const tod::HttpMsg::TodHttpMsg& msg, const std::string& path) {
    std::string post = msg.toJsonString();
    std::stringstream response;
    curlpp::Easy request;
    request.setOpt(new curlpp::options::PostFields(post));
    request.setOpt(new curlpp::options::PostFieldSize(post.length()));

    long http_code = this->request(request, response, path);
    if(http_code != 201){
        ROS_DEBUG_STREAM(ros::this_node::getName() << ": Code-" << http_code
        << " - Response: " << response.str());
    }
    return http_code;
}

long HttpHandler::post_query(const tod::HttpMsg::TodHttpMsg& msg, const std::string& path) {
    std::stringstream response;
    curlpp::Easy request;

    std::string post = ""; // empty, just needed to set method to POST
    request.setOpt(new curlpp::options::PostFields(post));
    request.setOpt(new curlpp::options::PostFieldSize(post.length()));

    long httpCode = this->request(request, response, path + msg.get_query_string());
    
    if(httpCode != 201){
        std::cout << "Node " << ros::this_node::getName() << ": Code-" <<
                     httpCode << " - Response: " << response.str() << "\n";
    }
    return httpCode;
}

long HttpHandler::put(const tod::HttpMsg::TodHttpMsg& msg, const std::string& path) {
    std::string post = msg.toJsonString();
    std::stringstream response;
    curlpp::Easy request;
    request.setOpt(new curlpp::options::PostFields(post));
    request.setOpt(new curlpp::options::PostFieldSize(post.length()));
    request.setOpt(new curlpp::options::CustomRequest{"PUT"});
    
    long http_code = this->request(request, response, path);
    if(http_code != 200){
        ROS_DEBUG_STREAM(ros::this_node::getName() << ": Code-" << http_code
        << " - Response: " << response.str());
    }
    return http_code;
}


long HttpHandler::get(tod::HttpMsg::TodHttpMsg& msg, const std::string& path) {
    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    std::stringstream response;
    curlpp::Easy request;
    long http_code = this->request(request, response, path);
    std::chrono::time_point afterRequest = std::chrono::high_resolution_clock::now();
    if(http_code != 200){
        ROS_DEBUG_STREAM(ros::this_node::getName() << ": Code-" << http_code
        << " - Response: " << response.str());
    }
    if(http_code == 200) {
        msg.fromString(response.str());
    }
    std::chrono::time_point end = std::chrono::high_resolution_clock::now();
//    auto overall = (float)(end - start).count();
//    auto requestTime = (float)(afterRequest - start).count();
//    printf("request %f\trest %f\n", requestTime/overall, 1-requestTime/overall);
    return http_code;
}

long HttpHandler::request(curlpp::Easy& request, std::stringstream& response,
        const std::string& path) {
    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    std::list<std::string> header;
    header.push_back("Content-Type: application/json");
    long http_code{ 0 };
    using Clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<Clock> before, after;
    try{
        curlpp::Cleanup cleaner;
        std::string cookieForAuth = "unicaragil-auth-token=xVCTB4xNBdyLJIxan87gev";
        request.setOpt(new curlpp::options::Cookie(cookieForAuth));
        std::string completePath = _url + path;
        ROS_DEBUG_STREAM("Request from: " << completePath);
        request.setOpt(new curlpp::options::Url(completePath));
        request.setOpt(new curlpp::options::Verbose(false));
        request.setOpt(new curlpp::options::SslVerifyPeer(false)); // No CA-Certificate required .. unsafe
        request.setOpt(new curlpp::options::HttpHeader(header));
        request.setOpt(new curlpp::options::WriteStream(&response));
        request.setOpt(new curlpp::options::IpResolve(CURL_IPRESOLVE_V4));
        before = Clock::now();
        request.perform(); // this takes 120 ms on average -> this is too long
        after = Clock::now();
        http_code = curlpp::infos::ResponseCode::get(request);
    }
    catch (curlpp::LogicError &e){
        ROS_DEBUG_STREAM(ros::this_node::getName() << ": "<< e.what() );
    }
    catch (curlpp::RuntimeError &e){
        ROS_DEBUG_STREAM(ros::this_node::getName() << ": "<< e.what() );
    }
    
    ROS_DEBUG_STREAM(ros::this_node::getName() << ": " 
        << response.str() << "; Http-Code: " << http_code);

//    auto finished = Clock::now();
//    auto overall = (float)(finished-start).count();
//    float performing = (float)(after-before).count();
//    auto overallMs = std::chrono::duration_cast<std::chrono::milliseconds>(
//        finished-start);
//    printf("overall request took %f ms\t part of performing http request in
//          percentage %f\n", (float)overallMs.count(),
//        (performing/overall));
    return http_code;
}

void HttpHandler::setIpAddress(const std::string& ipAddress) {
    _url = ipAddress;
}
