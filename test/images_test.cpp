#include "testing.hpp"

TEST_CASE("Prepare mat function test images", "[PrepareMat")
{

    Images<int> a = Images<int>::fromvector({3, 2}, {1, 2, 3, 4, 5, 6});
    ndarray<int> output = a.prepareMat();

    for (uint16_t i = 0; i < output.size(); i++){
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>::fromvector({2, 3, 2}, {1, 2,
                                            3, 4,
                                            5, 6,

                                            7, 8,
                                            9, 10,
                                            11, 12});
    Images<int> b = Images<int>::fromvector({6, 2}, {1, 7, 2, 8, 3, 9, 4, 10, 5, 11, 6, 12});
    output = a.prepareMat();

    REQUIRE(output.getShape() == b.getShape());

    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == b[i]);
    }
}

TEST_CASE("Count function test images", "[Count]")
{

    Images<int> a = Images<int>::fromvector({1, 2}, {1, 1});
    REQUIRE(a.count() == 1);

    a = Images<int>::fromvector({2, 1}, {1, 1});
    REQUIRE(a.count() == 1);

    a = Images<int>::fromvector({5, 1}, {1, 1, 1, 1, 1});
    REQUIRE(a.count() == 1);

    a = Images<int>::fromvector({3, 2, 3}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    REQUIRE(a.count() == 3);

    REQUIRE_THROWS(Images<int>::fromvector({5}, {1, 1, 1, 1, 1}));
}

TEST_CASE("Filter function usage images", "[Filter]")
{

    Images<int> a = Images<int>::fromvector({5, 1}, {1, 2, 3, 4, 5});

    // Test nothing left

    REQUIRE_THROWS(a.filter([](int input)
                            { input *=0; return false; }));

    // Test useful filtering
    Images<int> output = a.filter([](int input)
                                  {return input > 2; });

    REQUIRE(output.getShape()[0] == 1);

    for (int i = 0; i < output.size() - 2; i++)
    {
        REQUIRE(output[i] == a[2 + i]);
    }
}

TEST_CASE("Max function usage images", "[Max]")
{

    Images<int> a = Images<int>::fromvector({6, 1}, {1, 2, 3, 4, 5, 6});

    Images<int> output = a.max();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>::fromvector({3, 2, 2}, {1, 2,
                                            3, 4,

                                            5, 6,
                                            7, 8,

                                            9, 10,
                                            11, 12});
    output = a.max();
    REQUIRE(output[0] == 9);   
    REQUIRE(output[1] == 10);    
    REQUIRE(output[2] == 11);
    REQUIRE(output[3] == 12);
}

TEST_CASE("Min function usage images", "[Min]")
{

    Images<int> a = Images<int>::fromvector({6, 1}, {1, 2, 3, 4, 5, 6});

    Images<int> output = a.min();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>::fromvector({3, 2, 2}, {1, 2,
                                            3, 4,

                                            5, 6,
                                            7, 8,

                                            9, 10,
                                            11, 12});
    output = a.min();
    REQUIRE(output[0] == 1);
    REQUIRE(output[1] == 2);
    REQUIRE(output[2] == 3);
    REQUIRE(output[3] == 4);
}

TEST_CASE("Sum function usage images", "[Sum]")
{

    Images<int> a = Images<int>::fromvector({6, 1}, {1, 2, 3, 4, 5, 6});

    Images<int> output = a.sum();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>::fromvector({3, 2, 2}, {1, 2,
                                            3, 4,

                                            5, 6,
                                            7, 8,

                                            9, 10,
                                            11, 12});
    output = a.sum();
    REQUIRE(output[0] == 15);
    REQUIRE(output[1] == 18);    
    REQUIRE(output[2] == 21);
    REQUIRE(output[3] == 24);
}

TEST_CASE("Mean function usage images", "[Mean]")
{

    Images<int> a = Images<int>::fromvector({6, 1}, {1, 2, 3, 4, 5, 6});

    Images<int> output = a.mean();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == a[i]);
    }

    a = Images<int>::fromvector({3, 2, 2}, {1, 2,
                                            3, 4,

                                            5, 6,
                                            7, 8,

                                            9, 10,
                                            11, 12});
    output = a.mean();
    REQUIRE(output[0] == 5);
    REQUIRE(output[1] == 6);
    REQUIRE(output[2] == 7);
    REQUIRE(output[3] == 8);
}

TEST_CASE("Std integer function usage images", "[Std]")
{
    Images<int> a = Images<int>::fromvector({5, 1}, {1, 4, 3, 10, 5});

    Images<int32_t> output = a.std();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == 0);
    }

    a = Images<int>::fromvector({3, 2, 2}, {11, 12,
                                            5, 6,

                                            3, 4,
                                            7, 8,

                                            9, 10,
                                            1, 2});
    output = a.std();
    REQUIRE(output[0] == 3);
    REQUIRE(output[1] == 3);
    REQUIRE(output[2] == 2);
    REQUIRE(output[3] == 2);
}

TEST_CASE("Std double function usage images", "[Std]")
{

    Images<double> a = Images<double>::fromvector({5, 1}, {1.0, 4.0, 3.0, 10.0, 5.0});

    Images<double> output = a.std();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == Approx(0));
    }

    a = Images<double>::fromvector({3, 2, 2}, {11.0, 12.0,
                                   5.0, 6.0,

                                   3.0, 4.0,
                                   7.0, 8.0,

                                   9.0, 10.0,
                                   1.0, 2.0});
    output = a.std();
    REQUIRE(output[0] == Approx(3.399346));
    REQUIRE(output[1] == Approx(3.399346));
    REQUIRE(output[2] == Approx(2.494438));
    REQUIRE(output[3] == Approx(2.494438));
}

TEST_CASE("Var integer function usage images", "[Var]")
{

    Images<int> a = Images<int>::fromvector({5, 1}, {1, 4, 3, 10, 5});

    Images<int32_t> output = a.var();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == 0);
    }

    a = Images<int>::fromvector({3, 2, 2}, {11, 12,
                                5, 6,

                                3, 4,
                                7, 8,

                                9, 10,
                                1, 2});
    output = a.var();
    REQUIRE(output[0] == 12);
    REQUIRE(output[1] == 12); 
    REQUIRE(output[2] == 6); 
    REQUIRE(output[3] == 6); 
}

TEST_CASE("Var double function usage images", "[Var]")
{

    Images<double> a = Images<double>::fromvector({5, 1}, {1.0, 4.0, 3.0, 10.0, 5.0});

    Images<double> output = a.var();
    for (int i = 0; i < output.size(); i++)
    {
        REQUIRE(output[i] == Approx(0));
    }

    a = Images<double>::fromvector({3, 2, 2}, {11.0, 12.0,
                                   5.0, 6.0,

                                   3.0, 4.0,
                                   7.0, 8.0,

                                   9.0, 10.0,
                                   1.0, 2.0});
    output = a.var();
    REQUIRE(output[0] == Approx(11.555555));
    REQUIRE(output[1] == Approx(11.555555));
    REQUIRE(output[2] == Approx(6.222222));
    REQUIRE(output[3] == Approx(6.222222));
}

TEST_CASE("Retrieve and image png", "[Var]")
{
    Images<double> a = Images<double>::frompng("../data/singlelayer_png/dot1_grey.png");
    REQUIRE(a.getShape()[0] == 75);
    REQUIRE(a.getShape()[1] == 70);
    REQUIRE(a.getShape()[2] == 3);
    REQUIRE(a.get_current_dimension() == 15750);

}

TEST_CASE("Retrieve and image tif", "[Var]")
{
    Images<double> a = Images<double>::frompng("../data/singlelayer_tif/1.tif");
    REQUIRE(a.getShape()[0] == 75);
    REQUIRE(a.getShape()[1] == 70);
    REQUIRE(a.getShape()[2] == 3);
    REQUIRE(a.get_current_dimension() == 15750);

}

TEST_CASE("Retrieve an invalid image", "[Var]")
{
    Images<double> a = Images<double>::frompng("../data/singlelayer_png/dot1_grey.png");

    REQUIRE_THROWS(a.frompng("../data/singlelayer_png/no_real.png"));
    REQUIRE_THROWS(a.fromtif("../data/singlelayer_tif/0.tif"));

}
