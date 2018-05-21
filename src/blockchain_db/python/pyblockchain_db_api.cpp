#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/complex.h>
#include <pybind11/chrono.h>

#include <pybind11/stl.h>
// for opaque containers
// link {http://pybind11.readthedocs.io/en/stable/advanced/cast/stl.html}
#include <pybind11/stl_bind.h>

#include "pyblockchain_db.cpp"

namespace py = pybind11;

using namespace cryptonote;

PYBIND11_MAKE_OPAQUE(std::vector<std::string>);

PYBIND11_MODULE(pyblockchain_db_api, m) {
    m.doc() = "pbdoc() ..";

    // For returning values of vector<string>
    py::class_<std::vector<std::string>>(m, "VectorString")
        .def(py::init<>())
        .def("clear", &std::vector<std::string>::clear)
        .def("pop_back", &std::vector<std::string>::pop_back)
        .def("__len__", [](const std::vector<std::string> &v) { return v.size(); })
        .def("__iter__", [](std::vector<std::string> &v) {
            return py::make_iterator(v.begin(), v.end());
        }, py::keep_alive<0, 1>()) /* Keep vector alive while iterator is used */
        ;

    py::class_<PyBlockchainDb>(m, "PyBlockchainDb")
        .def(py::init<>())
        .def("height", &PyBlockchainDb::height)
        .def("sync", &PyBlockchainDb::sync)
        .def("get_filenames", &PyBlockchainDb::get_filenames)
        .def("safesyncmode", &PyBlockchainDb::safesyncmode)
        .def("reset", &PyBlockchainDb::reset)
        .def("get_db_name", &PyBlockchainDb::get_db_name)
        .def("lock", &PyBlockchainDb::lock)
        .def("unlock", &PyBlockchainDb::unlock)
        .def("block_exists", &PyBlockchainDb::block_exists)
        .def("get_block_height", &PyBlockchainDb::get_block_height)
        .def("get_block_header", &PyBlockchainDb::get_block_header)
        // .def("remove_tx_outputs", &PyBlockchainDb::remove_tx_outputs)
        // .def("remove_output", &PyBlockchainDb::remove_output)
        // .def("add_spent_key", &PyBlockchainDb::add_spent_key)
        // .def("remove_spent_key", &PyBlockchainDb::remove_spent_key)
        // .def("output_to_blob", &PyBlockchainDb::output_to_blob)
        // .def("output_from_blob", &PyBlockchainDb::output_from_blob)
        // .def("check_open", &PyBlockchainDb::check_open)
        .def("open", &PyBlockchainDb::open)
        .def("close", &PyBlockchainDb::close)
        ;

    // py::bind_vector<std::vector<std::string>>(m, "VectorString");

    #ifdef VERSION_INFO
        m.attr("__version__") = VERSION_INFO;
    #else
        m.attr("__version__") = "dev";
    #endif
}
