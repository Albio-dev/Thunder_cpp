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