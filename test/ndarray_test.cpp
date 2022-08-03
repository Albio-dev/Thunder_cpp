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
            REQUIRE(n[i] == Approx(inputArray[i]));
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

TEST_CASE("Index NDArray elements", "[Indexing]"){

    // 8 long array
    int arr[] = {1, 2,
                 3, 4,

                 5, 6,
                 7, 8};

    // 2x2x2 dimensions definition
    vector<uint16_t> lengths = {2, 2, 2};
    // Object creation
    NDArray<int> n = NDArray<int>(lengths, arr);

    SECTION("Proper scalar indexing"){        
        REQUIRE((*(n.getPosition({0, 0, 0})))[0] == 1);
        REQUIRE((*(n.getPosition({0, 1, 0})))[0] == 3);
        REQUIRE((*(n.getPosition({1, 0, 0})))[0] == 5);
        REQUIRE((*(n.getPosition({1, 1, 1})))[0] == 8);
    }

    SECTION("Multidimensional indexing"){
        NDArray<int> output = *n.getPosition({1});
        for (int i = 0; i < 4; i++){
            REQUIRE(output[i] == arr[i+4]);
        }
        REQUIRE(output.getShape().size() == 2);
        REQUIRE(output.getShape()[0] == 2);
        REQUIRE(output.getShape()[1] == 2);

        output = *n.getPosition({1, 1});

        REQUIRE(output[0] == 7);
        REQUIRE(output[1] == 8);
    }

    SECTION("Wrong indexing"){
        REQUIRE_THROWS(n.getPosition({1, 1, 1, 1, 1}));
    }

    SECTION("Out of bounds indexing"){
        REQUIRE_THROWS(n.getPosition({3, 1, 1}));
    }
}