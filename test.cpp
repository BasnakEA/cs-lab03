#include "histogram.h"
#include "svg.h"
#include <cassert>

void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_same() {
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_one() {
    double min = 0;
    double max = 0;
    find_minmax({2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void test_color() {
    // Test 1
    vector<size_t> bins = {1, 5, 3};
    assert(make_color(bins, bins[0], 5) == "999");
    assert(make_color(bins, bins[1], 5) == "111");
    assert(make_color(bins, bins[2], 5) == "555");
    //Test 2
    bins = {10, 6, 3, 5};
    assert(make_color(bins, bins[0], 10) == "111");
    assert(make_color(bins, bins[1], 10) == "555");
    assert(make_color(bins, bins[2], 10) == "999");
    assert(make_color(bins, bins[3], 10) == "666");
}

void test_all() {
    test_positive();
    test_negative();
    test_same();
    test_one();
    test_empty();
    test_color();
}

int
main() {
   test_all();
}
