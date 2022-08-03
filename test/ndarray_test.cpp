#define CATCH_CONFIG_MAIN
#include "../third_party/catch.hpp"
#include "../src/ndarray.cpp"


TEST_CASE("Create an ndarray", "[Creation]")
{
    SECTION("Proper usage with integers"){
        // synthetic data
        int inputArray[] = {1, 2, 3, 4};
        vector<uint16_t> dimensions = {2, 2};

        // Object creation 
        NDArray<int> n = NDArray<int>(dimensions, inputArray);

        // Testing for data
        for (int i = 0; i < 4; i++){
            REQUIRE(n.getData()[i] == inputArray[i]);
        }

        // Testing for shape
        for (int i = 0; i < 2; i++){
            REQUIRE(n.getShape()[i] == dimensions[i]);
        }
    }

    SECTION("Proper usage with floating points")
    {
        // synthetic data
        double inputArray[] = {1.5, 2.21654, 35.2, 4.0};
        vector<uint16_t> dimensions = {2, 2};

        // Object creation
        NDArray<double> n = NDArray<double>(dimensions, inputArray);

        // Testing for data
        for (int i = 0; i < 4; i++)
        {
            REQUIRE(n.getData()[i] == Approx(inputArray[i]));
        }

        // Testing for shape
        for (int i = 0; i < 2; i++)
        {
            REQUIRE(n.getShape()[i] == dimensions[i]);
        }
    }

    SECTION("Limit case: 0 valued input dimensions"){
        // Limit cases //
        int inputArray[] = {1, 2, 3, 4};
        vector<uint16_t> dimensions;

        // Object creation
        REQUIRE_THROWS(NDArray<int>(dimensions, inputArray));

    }

}
