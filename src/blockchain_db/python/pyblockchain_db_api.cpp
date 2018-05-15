#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "pyblockchain_db.cpp"

namespace py = pybind11;

using namespace cryptonote;

PYBIND11_MODULE(pyblockchain_db_api, m) {
    m.doc() = "pbdoc() ..";

    py::class_<PyBlockchainDb>(m, "PyBlockchainDb")
        .def(py::init<>())
        .def("height", &PyBlockchainDb::height)
        .def("sync", &PyBlockchainDb::sync)
        ;


    #ifdef VERSION_INFO
        m.attr("__version__") = VERSION_INFO;
    #else
        m.attr("__version__") = "dev";
    #endif
}
