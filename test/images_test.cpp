#include "testing.hpp"

TEST_CASE("Prepare mat function test", "[PrepareMat")
{

    Images<int> a = Images<int>({3, 2}, {1, 2, 3, 4, 5, 6});
    NDArray<int> output = a.prepareMat();

    int index = 0;
    REQUIRE(output[index++] == index+1);
    REQUIRE(output[index++] == index + 1);
    REQUIRE(output[index++] == index + 1);
    REQUIRE(output[index++] == index + 1);
    REQUIRE(output[index++] == index + 1);
    REQUIRE(output[index++] == index + 1);

    a = Images<int>({2, 3, 2}, {1, 2, 
                                3, 4,
                                5, 6, 
                                
                                7, 8, 
                                9, 10,
                                11, 12});
    Images<int> b = Images<int>({6, 2}, {1, 7, 2, 8, 3, 9, 4, 10, 5, 11, 6, 12});
    output = a.prepareMat();

    REQUIRE(output.getShape() == b.getShape());

    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == b[i]);
    }
}

TEST_CASE("Count function test", "[Count]")
{

    Images<int> a = Images<int>({1, 2}, {1, 1});
    REQUIRE(a.count() == 1);

    a = Images<int>({2, 1}, {1, 1});
    REQUIRE(a.count() == 1);

    a = Images<int>({5, 1}, {1, 1, 1, 1, 1});
    REQUIRE(a.count() == 1);

    a = Images<int>({3, 2, 3}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    REQUIRE(a.count() == 3);

    REQUIRE_THROWS(Images<int>({5}, {1, 1, 1, 1, 1}));
}
/*
TEST_CASE("Filter function usage", "[Filter")
{

    Images<int> a = Images<int>::fromArray({5}, {1, 2, 3, 4, 5});

    // Test nothing left

    REQUIRE_THROWS(a.filter([](NDArray<int> input)
                            { input.getShape(); return false; }));

    // Test useful filtering
    Images<int> output = a.filter([](NDArray<int> input)
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
        a = Images<int>::fromArray({3, 3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
        output = a.filter([](NDArray<int> input)
                          {
            for (int i = 0; i < input.size(); i++)
                if (input[i] <= 2)
                    return false;
            return true; });
            *//*
}

TEST_CASE("Max function usage", "[Max]")
{

    Images<int> a = Images<int>({5}, {1, 2, 3, 4, 5});

    Images<int> output = a.max();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>({3, 2, 2}, {1, 2,
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

    Images<int> a = Images<int>({5}, {1, 2, 3, 4, 5});

    Images<int> output = a.min();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>({3, 2, 2}, {1, 2,
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

    Images<int> a = Images<int>({5}, {1, 2, 3, 4, 5});

    Images<int> output = a.sum();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>({3, 2, 2}, {1, 2,
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

    Images<int> a = Images<int>({5}, {1, 2, 3, 4, 5});

    Images<int> output = a.mean();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>({3, 2, 2}, {1, 2,
                                3, 4,

                                5, 6,
                                7, 8,

                                9, 10,
                                11, 12});
    output = a.mean();
    REQUIRE(output[0] == 6);
    REQUIRE(output[1] == 7);
}

TEST_CASE("Std integer function usage", "[Std]")
{
    // TODO: La funzione std usa il count di NDArray e non di Images
    Images<int> a = Images<int>({5}, {1, 4, 3, 10, 5});

    Images<int32_t> output = a.std();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == 0);
    }

    a = Images<int>({3, 2, 2}, {11, 12,
                                5, 6,

                                3, 4,
                                7, 8,

                                9, 10,
                                1, 2});
    output = a.std();
    REQUIRE(output[0] == 3);
    REQUIRE(output[1] == 3);
}

TEST_CASE("Std double function usage", "[Std]")
{

    Images<double> a = Images<double>({5}, {1.0, 4.0, 3.0, 10.0, 5.0});

    Images<double> output = a.std();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == Approx(0));
    }

    a = Images<double>({3, 2, 2}, {11.0, 12.0,
                                   5.0, 6.0,

                                   3.0, 4.0,
                                   7.0, 8.0,

                                   9.0, 10.0,
                                   1.0, 2.0});
    output = a.std();
    REQUIRE(output[0] == Approx(3.415650));
    REQUIRE(output[1] == Approx(3.415650));
}

TEST_CASE("Var integer function usage", "[Var]")
{

    Images<int> a = Images<int>({5}, {1, 4, 3, 10, 5});

    Images<int32_t> output = a.var();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == 0);
    }

    a = Images<int>({3, 2, 2}, {11, 12,
                                5, 6,

                                3, 4,
                                7, 8,

                                9, 10,
                                1, 2});
    output = a.var();
    REQUIRE(output[0] == 11);
    REQUIRE(output[1] == 11); // TODO: Should be 5?
}

TEST_CASE("Var double function usage", "[Var]")
{

    Images<double> a = Images<double>({5}, {1.0, 4.0, 3.0, 10.0, 5.0});

    Images<double> output = a.var();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == Approx(0));
    }

    a = Images<double>({3, 2, 2}, {11.0, 12.0,
                                   5.0, 6.0,

                                   3.0, 4.0,
                                   7.0, 8.0,

                                   9.0, 10.0,
                                   1.0, 2.0});
    output = a.var();
    REQUIRE(output[0] == Approx(11.666666));
    REQUIRE(output[1] == Approx(11.666666));
}
*/