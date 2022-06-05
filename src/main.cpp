#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

#include "pet.hpp"
#include "animal.hpp"
#include "vec.hpp"
#include "num.hpp"

#include <chrono>
using system_time = std::chrono::system_clock::time_point;

int add(int i, int j) {
    return i + j;
}

void print_kwargs(const py::kwargs &kwargs)
{
    for (auto &&i : kwargs)
        py::print(i.first, i.second);
}

namespace py = pybind11;

class PyAnimal : public Animal {
public:
    /* Inherit the constructors */
    using Animal::Animal;

    /* Trampoline (need one for each virtual function) */
    std::string go(int n_times) override {
        PYBIND11_OVERRIDE_PURE(
            std::string, /* Return type */
            Animal,      /* Parent class */
            go,          /* Name of function in C++ (must match Python name) */
            n_times      /* Argument(s) */
        );
    }
};

PYBIND11_MODULE(_fseg, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: _fseg

        .. autosummary::
           :toctree: _generate

           add
           substract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc", py::arg("i"), py::arg("j")=1);

    m.def("substract", [](int i, int j) { return i - j; }, R"pbdoc(
        Substract two numbers

        Some other explanation about the substract function.
    )pbdoc", py::arg("i"), py::arg("j"));

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif

    m.attr("the_answer") = 42;
    py::object world = py::cast("World");
    m.attr("what") = world;

    py::class_<Pet> pet(m, "Pet");

    pet.def(py::init<const std::string &, Pet::Kind>())
        .def_readwrite("name", &Pet::name)
        .def_readwrite("type", &Pet::type)
        .def_readwrite("attr", &Pet::attr);

    py::enum_<Pet::Kind>(pet, "Kind", py::arithmetic())
        .value("Dog", Pet::Kind::Dog)
        .value("Cat", Pet::Kind::Cat)
        .export_values();
    
    py::class_<Pet::Attributes> attributes(pet, "Attributes");

    attributes.def(py::init<>())
        .def_readwrite("age", &Pet::Attributes::age);

    py::class_<Animal, PyAnimal>(m, "Animal")
        .def(py::init<>())
        .def("go", &Animal::go);

    py::class_<Dog, Animal>(m, "Dog")
        .def(py::init<>());

    m.def("call_go", &call_go);

    py::class_<Vector2>(m, "Vector2")
        .def(py::init<float, float>())
        .def(py::self + py::self)
        .def(py::self += py::self)
        .def(py::self *= float())
        .def(float() * py::self)
        .def(py::self * float())
        .def(-py::self)
        .def("__repr__", &Vector2::toString);

    m.def("vectorized_func", py::vectorize(my_func));

    py::class_<VectorizeTestClass> vtc(m, "VectorizeTestClass");
    vtc.def(py::init<int>())
        .def_readwrite("value", &VectorizeTestClass::value);

    // Automatic vectorizing of methods
    vtc.def("method", py::vectorize(&VectorizeTestClass::method));

    m.def("datetime_demo", [](){
        py::object datetime = py::module::import("datetime").attr("datetime");
        py::object dt = datetime.attr("now")();
        // py::object year = dt.attr("year");
        // py::object month = dt.attr("month");
        // py::object day = dt.attr("day");
        // py::object hour = dt.attr("hour");
        // py::object minute = dt.attr("minute");
        // py::object second = dt.attr("second");
        auto year     = dt.attr("year").cast<int>();
        auto month   = dt.attr("month").cast<int>();
        auto day       = dt.attr("day").cast<int>();
        auto hour     = dt.attr("hour").cast<int>();
        auto minute = dt.attr("minute").cast<int>();
        auto second = dt.attr("second").cast<int>();
        py::print(year, month, day, hour, minute, second);
        
        std::string fmt("%Y-%m-%d %H:%M:%S");
        py::object dt2 = datetime.attr("strptime")("1970-10-14 10:30:12", fmt);
        py::print(dt2);
    });

    m.def("kwargs_demo", [](const py::kwargs &kwargs){
        for (auto &&i : kwargs)
            py::print(i.first, i.second);

        py::dict kwargs2 = py::dict(py::arg("number")=1234, py::arg("say")="hello");
        print_kwargs(kwargs2);
        
        py::print("----------------");
        // kwargs2.operator[]("year") = 1996;
        kwargs2["year"] = 1996;
        print_kwargs(kwargs2);

        py::print("----------------");
        py::dict kwargs3 = py::dict(py::arg("foo") = 100, **kwargs);
        print_kwargs(kwargs3);
    });

    m.def("chrono_demo", [](system_time t){
        auto d = t.time_since_epoch();
    });
}
