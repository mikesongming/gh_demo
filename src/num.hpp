#if !defined(NUM_H)
#define NUM_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

using namespace pybind11::literals;

double my_func(int x, float y, double z) {
    py::print("my_func(x:int={}, y:float={:.0f}, z:float={:.0f})"_s.format(x, y, z));
    // py::print(py::str("my_func(x:int={}, y:float={:.0f}, z:float={:.0f})").format(x, y, z));
    return (float) x * y * z;
}

struct VectorizeTestClass {
    explicit VectorizeTestClass(int v) : value{v} {};
    float method(int x, float y) const { return y + (float) (x + value); }
    int value = 0;
};

#endif // NUM_H
