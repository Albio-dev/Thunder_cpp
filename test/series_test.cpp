#define CATCH_CONFIG_MAIN
#include "../third_party/catch.hpp"
#include "../src/series.cpp"
#include "../src/ndarray.cpp"

using namespace std;

TEST_CASE("Prepare mat function test", "[PrepareMat"){

 
    Series<int> a = Series<int>::fromArray({3, 2}, {1, 2, 3, 4, 5, 6});
    NDArray<int> output = a.prepareMat();

    int index = 0;
    REQUIRE(output[index++] == 1);
    REQUIRE(output[index++] == 3);
    REQUIRE(output[index++] == 5);
    REQUIRE(output[index++] == 2);
    REQUIRE(output[index++] == 4);
    REQUIRE(output[index++] == 6); 

    a = Series<int>::fromArray({2, 3, 2}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    Series<int> b = Series<int>::fromArray({2, 6}, {1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10, 12});
    output = a.prepareMat();

    REQUIRE(output.getShape() == b.getShape());

    for (int i = 0; i < output.size(); i++){
        REQUIRE(output[i] == b[i]);
    }

}

TEST_CASE("Count function test", "[Count]"){

    Series<int> a = Series<int>::fromArray({1, 2}, {1, 1});
    REQUIRE(a.count() == 1);

    a = Series<int>::fromArray({2, 1}, {1, 1});
    REQUIRE(a.count() == 2);

    a = Series<int>::fromArray({5, 1}, {1, 1, 1, 1, 1});
    REQUIRE(a.count() == 5);

    a = Series<int>::fromArray({3, 2, 3}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    REQUIRE(a.count() == 6);

    a = Series<int>::fromArray({5}, {1, 1, 1, 1, 1});
    REQUIRE(a.count() == 1);
}

TEST_CASE("Filter function usage", "[Filter")
{

    Series<int> a = Series<int>::fromArray({5}, {1, 2, 3, 4, 5});

    // Test nothing left
    
    REQUIRE_THROWS(a.filter([](NDArray<int> input)
                            { input.getShape(); return false; }));

    // Test useful filtering
    Series < int > output = a.filter([](NDArray<int> input)
                                      {
        for (int i = 0; i < input.size(); i++)
            if (input[i] <= 2)
                return false;
        return true; });

    REQUIRE(output.getShape()[0] == 3);

    for (int i = 0; i < output.size() - 2; i++)
    {
        REQUIRE(output[i] == a[2 + i]);
    }
/*
    a = Series<int>::fromArray({3, 3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    output = a.filter([](NDArray<int> input)
                      {
        for (int i = 0; i < input.size(); i++)
            if (input[i] <= 2)
                return false;
        return true; });*/
}

TEST_CASE("Max function usage", "[Max]")
{

    Series<int> a = Series<int>({5}, {1, 2, 3, 4, 5});

    Series<int> output = a.max();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Series<int>({3, 2, 2}, {1, 2,
                                3, 4,

                                5, 6,
                                7, 8,

                                9, 10,
                                11, 12});
    output = a.max();
    REQUIRE(output[0] == 11);
    REQUIRE(output[1] == 12);
}

TEST_CASE("Min function usage", "[Min]")
{

    Series<int> a = Series<int>({5}, {1, 2, 3, 4, 5});

    Series<int> output = a.min();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Series<int>({3, 2, 2}, {1, 2,
                                3, 4,

                                5, 6,
                                7, 8,

                                9, 10,
                                11, 12});
    output = a.min();
    REQUIRE(output[0] == 1);
    REQUIRE(output[1] == 2);
}

TEST_CASE("Sum function usage", "[Sum]")
{

    Series<int> a = Series<int>({5}, {1, 2, 3, 4, 5});

    Series<int> output = a.sum();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Series<int>({3, 2, 2}, {1, 2,
                                3, 4,

                                5, 6,
                                7, 8,

                                9, 10,
                                11, 12});
    output = a.sum();
    REQUIRE(output[0] == 36);
    REQUIRE(output[1] == 42);
}

TEST_CASE("Mean function usage", "[Mean]")
{

    Series<int> a = Series<int>({5}, {1, 2, 3, 4, 5});

    Series<int> output = a.mean();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Series<int>({3, 2, 2}, {1, 2,
                                3, 4,

                                5, 6,
                                7, 8,

                                9, 10,
                                11, 12});
    output = a.mean();
    REQUIRE(output[0] == 6);
    REQUIRE(output[1] == 7);
}
/*
TEST_CASE("Std integer function usage", "[Std]")
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

TEST_CASE("Std double function usage", "[Std]")
{

    NDArray<double> a = NDArray<double>({5}, {1.0, 4.0, 3.0, 10.0, 5.0});

    NDArray<double> output = a.std();
    REQUIRE(output[0] == Approx(3.361547));

    a = NDArray<double>({3, 2, 2}, {11.0, 12.0,
                                    5.0, 6.0,

                                    3.0, 4.0,
                                    7.0, 8.0,

                                    9.0, 10.0,
                                    1.0, 2.0});
    output = a.std();
    REQUIRE(output[0] == Approx(3.511884));
    REQUIRE(output[1] == Approx(2.380476));
    REQUIRE(output[2] == Approx(4.654746));
}

TEST_CASE("Var integer function usage", "[Var]")
{

    NDArray<int> a = NDArray<int>({5}, {1, 4, 3, 10, 5});

    NDArray<int32_t> output = a.var();
    REQUIRE(output[0] == 11);

    a = NDArray<int>({3, 2, 2}, {11, 12,
                                 5, 6,

                                 3, 4,
                                 7, 8,

                                 9, 10,
                                 1, 2});
    output = a.var();
    REQUIRE(output[0] == 12);
    REQUIRE(output[1] == 6);  // TODO: Should be 5?
    REQUIRE(output[2] == 22); // TODO: should be 21?
}

TEST_CASE("Var double function usage", "[Var]")
{

    NDArray<double> a = NDArray<double>({5}, {1.0, 4.0, 3.0, 10.0, 5.0});

    NDArray<double> output = a.var();
    REQUIRE(output[0] == Approx(11.3));

    a = NDArray<double>({3, 2, 2}, {11.0, 12.0,
                                    5.0, 6.0,

                                    3.0, 4.0,
                                    7.0, 8.0,

                                    9.0, 10.0,
                                    1.0, 2.0});
    output = a.var();
    REQUIRE(output[0] == Approx(12.333333));
    REQUIRE(output[1] == Approx(5.666666));
    REQUIRE(output[2] == Approx(21.666666));
}
*/