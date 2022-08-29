#include <gtest/gtest.h>
#include <memory.h>
#include "tod_cloud/HttpHandler.h"
#include "tod_cloud/todHttpPaths.h"

// for breakpoints in here:
// catkin build tod_cloud --cmake-args -DCMAKE_BUILD_TYPE=DEBUG

class TestHttpHandler : public ::testing::Test {
protected:
    bool testWithAachenerCloud = false;
    std::string url;
    std::unique_ptr<HttpHandler> testHandler;
    void SetUp() override {
        if( testWithAachenerCloud ) {
            url =
                "https://unicaragil-server.embedded.rwth-aachen.de/fleetmanagement";
        } else {
            url =
                "http://10.162.44.161:8080/fleetmanagement";
        }
        testHandler = std::make_unique<HttpHandler>(url);
    }
};

TEST_F(TestHttpHandler, testReceivedhttpCode200) {
    tod::HttpMsg::FleetIDs fleetIDs;
    long httpCode = testHandler->get(fleetIDs, "/car");
//    printf("httpCode = %s\n", std::to_string(httpCode).c_str());

    EXPECT_EQ(httpCode, (long) 200);
}

TEST_F(TestHttpHandler, testGettingListOfCars) {
    // arrange
    int expected_vehicle_id = 11111; // ID 11111 is in the Aachener Cloud
    tod::HttpMsg::FleetIDs cars;
    long httpCode = testHandler->get(cars, tod::HttpPath::fleet());

    // act
    std::set<int> vehicleIDs = cars.getVehicleIds();

    // assert
    bool ID_found = vehicleIDs.find(expected_vehicle_id) != vehicleIDs.end();
    EXPECT_TRUE(ID_found);
}

TEST_F(TestHttpHandler, testCreatingAndGettingCar) {
    // arrange
    int new_vehicle_id = 54545;
    tod::HttpMsg::Car providedCar;
    providedCar.ip_address = "0.1.2.3";
    providedCar.vehicleType = "elf";
    providedCar.id = new_vehicle_id;

    // act
    long httpCode = testHandler->post_query(providedCar, tod::HttpPath::fleet());
    tod::HttpMsg::Car receivedCar;
    std::string requestPath = tod::HttpPath::car(new_vehicle_id);
    long httpCodeRequest = testHandler->get(receivedCar, requestPath);

    // assert
    EXPECT_EQ(providedCar.id, receivedCar.id);
    EXPECT_EQ(providedCar.ip_address, receivedCar.ip_address);
    EXPECT_EQ(providedCar.vehicleType, receivedCar.vehicleType);
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "unit_test_node");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
