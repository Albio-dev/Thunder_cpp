#include "testing.hpp"

using namespace std;

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
            REQUIRE(n.getValue()[i] == inputArray[i]);
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
        
        REQUIRE(n.getPosition({0, 0, 0})[0] == 1);
        REQUIRE(n.getPosition({0, 1, 0})[0] == 3);
        REQUIRE(n.getPosition({1, 0, 0})[0] == 5);
        REQUIRE(n.getPosition({1, 1, 1})[0] == 8);
    }

    SECTION("Multidimensional indexing"){
        NDArray<int> output = n.getPosition({1});
        
        for (int i = 0; i < 4; i++){
            REQUIRE(output[i] == arr[i+4]);
        }
        REQUIRE(output.getShape().size() == 2);
        REQUIRE(output.getShape()[0] == 2);
        REQUIRE(output.getShape()[1] == 2);

        output = n.getPosition({1, 1});

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



TEST_CASE("Clip function usage", "[Clip]"){
    NDArray<int> a = NDArray<int>({10}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    a.clip(5, 6);

    int index = 0;
    REQUIRE(a[index++] == 5);
    REQUIRE(a[index++] == 5);
    REQUIRE(a[index++] == 5);
    REQUIRE(a[index++] == 5);
    REQUIRE(a[index++] == 5);
    REQUIRE(a[index++] == 5);
    REQUIRE(a[index++] == 6);
    REQUIRE(a[index++] == 6);
    REQUIRE(a[index++] == 6);
}

TEST_CASE("Plus function usage", "[Plus]"){
    NDArray<int> a = NDArray<int>({10}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    NDArray<int> b = NDArray<int>({10}, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});

    NDArray<int> output = a.plus(b);

    for (int i = 0; i < a.size(); i++)
    {
        REQUIRE(output[i] == 9);
    }

    a = NDArray<int>({5, 2, 1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    b = NDArray<int>({5, 2, 1}, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});

    output = a.plus(b);

    for (int i = 0; i < a.size(); i++)
    {
        REQUIRE(output[i] == 9);
    }
}

TEST_CASE("Minus function usage", "[Minus]")
{
    NDArray<int> a = NDArray<int>({10}, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    NDArray<int> b = NDArray<int>({10}, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});

    NDArray<int> output = a.minus(b);

    for (int i = 0; i < a.size(); i++)
    {
        REQUIRE(output[i] == 0);
    }

    a = NDArray<int>({5, 2, 1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    b = NDArray<int>({5, 2, 1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    output = a.minus(b);

    for (int i = 0; i < a.size(); i++)
    {
        REQUIRE(output[i] == 0);
    }
}

TEST_CASE("Map function usage", "[Map]"){
    NDArray<int> a = NDArray<int>({5, 2, 1}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    //NDArray<int> output = a.map([](int b){return b*0;});
    a.map([](int b)
            { return b * 0; });
    for (int i = 0; i < a.size(); i++)
    {
        REQUIRE(a[i] == 0);
    }
}

TEST_CASE("Count function usage", "[Count]")
{
    NDArray<int> a = NDArray<int>({1, 2}, {1, 1});
    REQUIRE(a.count() == 2);

    a = NDArray<int>({2, 1}, {1, 1});
    REQUIRE(a.count() == 1);

    a = NDArray<int>({5, 1}, {1, 1, 1, 1, 1});
    REQUIRE(a.count() == 1);

    a = NDArray<int>({3, 2, 3}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    REQUIRE(a.count() == 6);

    a = NDArray<int>({5}, {1, 1, 1, 1, 1});
    REQUIRE(a.count() == 5);
}

TEST_CASE("Filter function usage ndarray", "[Filter]"){

    NDArray<int> a = NDArray<int>({5}, {1, 2, 3, 4, 5});

    // Test nothing left
    REQUIRE_THROWS(a.filter([](NDArray<int> input)
                            { input.getShape(); return false; }));

    // Test useful filtering
    NDArray<int> output = a.filter([](NDArray<int> input){
        for (int i = 0; i < input.size(); i++)
            if (input[i] <= 2)
                return false;
        return true;
        });

    
    REQUIRE(output.getShape()[0] == 3);

    for (int i = 0; i < output.size()-2; i++){
        REQUIRE(output[i] == a[2+i]);
    }

    
}

TEST_CASE("Max function usage ndarray", "[Max]"){

    NDArray<int> a = NDArray<int>({5}, {1, 2, 3, 4, 5});

    NDArray<int> output = a.max();
    REQUIRE(output[0] == 5);

    a = NDArray<int>({3, 2, 2}, {1, 2, 
                                3, 4, 
                                
                                5, 6,
                                7, 8, 
                                
                                9, 10, 
                                11, 12});
    output = a.max();
    REQUIRE(output[0] == 4);
    REQUIRE(output[1] == 8);
    REQUIRE(output[2] == 12);
}

TEST_CASE("Min function usage ndarray", "[Min]")
{

    NDArray<int> a = NDArray<int>({5}, {1, 2, 3, 4, 5});

    NDArray<int> output = a.min();
    REQUIRE(output[0] == 1);

    a = NDArray<int>({3, 2, 2}, {1, 2,
                                 3, 4,

                                 5, 6,
                                 7, 8,

                                 9, 10,
                                 11, 12});
    output = a.min();
    REQUIRE(output[0] == 1);
    REQUIRE(output[1] == 5);
    REQUIRE(output[2] == 9);
}

TEST_CASE("Sum function usage ndarray", "[Sum]")
{

    NDArray<int> a = NDArray<int>({5}, {1, 2, 3, 4, 5});

    NDArray<int> output = a.sum();
    REQUIRE(output[0] == 15);

    a = NDArray<int>({3, 2, 2}, {1, 2,
                                 3, 4,

                                 5, 6,
                                 7, 8,

                                 9, 10,
                                 11, 12});
    output = a.sum();
    REQUIRE(output[0] == 10);
    REQUIRE(output[1] == 26);
    REQUIRE(output[2] == 42);
}

TEST_CASE("Mean function usage ndarray", "[Mean]")
{

    NDArray<int> a = NDArray<int>({5}, {1, 2, 3, 4, 5});

    NDArray<int> output = a.mean();
    REQUIRE(output[0] == 3);

    a = NDArray<int>({3, 2, 2}, {1, 2,
                                 3, 4,

                                 5, 6,
                                 7, 8,

                                 9, 10,
                                 11, 12});
    output = a.mean();
    REQUIRE(output[0] == 2);
    REQUIRE(output[1] == 6);
    REQUIRE(output[2] == 10);
}

TEST_CASE("Std integer function usage ndarray", "[Std]")
{

    NDArray<int> a = NDArray<int>({5}, {1, 4, 3, 10, 5});

    NDArray<int32_t> output = a.std();
    REQUIRE(output[0] == 3);

    a = NDArray<int>({3, 2, 2}, {11, 12,
                                 5, 6,

                                 3, 4,
                                 7, 8,

                                 9, 10,
                                 1, 2});
    output = a.std();
    REQUIRE(output[0] == 3);
    REQUIRE(output[1] == 2);
    REQUIRE(output[2] == 4);
}

TEST_CASE("Std double function usage ndarray", "[Std]")
{

    NDArray<double> a = NDArray<double>({5}, {1.0, 4.0, 3.0, 10.0, 5.0});

    NDArray<double> output = a.std();
    REQUIRE(output[0] == Approx(3.006659));

    a = NDArray<double>({3, 2, 2}, {11.0, 12.0,
                                    5.0, 6.0,

                                    3.0, 4.0,
                                    7.0, 8.0,

                                    9.0, 10.0,
                                    1.0, 2.0});
    output = a.std();
    REQUIRE(output[0] == Approx(3.041381));
    REQUIRE(output[1] == Approx(2.061552));
    REQUIRE(output[2] == Approx(4.031128));
}

TEST_CASE("Var integer function usage ndarray", "[Var]")
{

    NDArray<int> a = NDArray<int>({5}, {1, 4, 3, 10, 5});

    NDArray<int32_t> output = a.var();
    REQUIRE(output[0] == 9);

    a = NDArray<int>({3, 2, 2}, {11, 12,
                                 5, 6,

                                 3, 4,
                                 7, 8,

                                 9, 10,
                                 1, 2});
    output = a.var();
    REQUIRE(output[0] == 9);
    REQUIRE(output[1] == 4);
    REQUIRE(output[2] == 16);
}

TEST_CASE("Var double function usage ndarray", "[Var]")
{

    NDArray<double> a = NDArray<double>({5}, {1.0, 4.0, 3.0, 10.0, 5.0});

    NDArray<double> output = a.var();
    REQUIRE(output[0] == Approx(9.04));

    a = NDArray<double>({3, 2, 2}, {11.0, 12.0,
                                    5.0, 6.0,

                                    3.0, 4.0,
                                    7.0, 8.0,

                                    9.0, 10.0,
                                    1.0, 2.0});
    output = a.var();
    REQUIRE(output[0] == Approx(9.25));
    REQUIRE(output[1] == Approx(4.25));
    REQUIRE(output[2] == Approx(16.25));
}

TEST_CASE("Get current object errors and length", "[get_current_dimension]")
{
    NDArray<int> n = NDArray<int>({2, 2}, {1,1,1,1});
    REQUIRE(n.get_current_dimension() == 4);
    n = NDArray<int>({2}, {1,1});
    REQUIRE(n.get_current_dimension() == 2);
}

TEST_CASE("Test from binary function", "[from_binary]")
{
    NDArray<int> n = NDArray<int>({1}, {1});
    SECTION("Some errors file don't exists") {
        REQUIRE_THROWS(n.frombinary({1, 2}, "../data/binary.txt"));
        REQUIRE_THROWS(n.frombinary({1}, "../data/binary_values.txt"));
    }

    REQUIRE_NOTHROW(n.frombinary({3}, "../data/binary_values.txt"));
    std::vector<int> vecOfNums1{ 11, 12, 13 };
    REQUIRE(n.getValue() == vecOfNums1);
}

TEST_CASE("Test random function for generating data", "[fromrandom]")
{
    NDArray<float> n = NDArray<float>({1}, {1});
    REQUIRE_NOTHROW(n.fromrandom());
    for (int i = 0; i < 2; i++)
    {
        REQUIRE(n.getShape()[i] == 2);
    }
    REQUIRE_THROWS(n.fromrandom({0}));
    REQUIRE_THROWS(n.fromrandom({12, 0}));

}