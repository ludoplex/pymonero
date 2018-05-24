#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/complex.h>
#include <pybind11/chrono.h>
#include "../../cryptonote_basic/cryptonote_format_utils.h"
//
// #include <pybind11/stl.h>
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

    py::class_<crypto::hash>(m, "CryptoHash")
        .def(py::init<>())
        .def("data", [](const crypto::hash &h) {
            // We can change returned format as we see fit
            return short_hash_str(h);
            //return py::bytes(h.data);
        })
    ;

    py::class_<cryptonote::transaction>(m, "Transaction")
        // .def(py::init<>())
        // .def(py::init<cryptonote::transaction &>())
        .def_readonly("hash", &cryptonote::transaction::hash)
        .def_readonly("blob_size", &cryptonote::transaction::blob_size)
    ;

    py::class_<cryptonote::block_header>(m, "BlockHeader")
        .def_readonly("prev_id", &cryptonote::block_header::prev_id)
        .def_readonly("major_version", &cryptonote::block_header::major_version)
        .def_readonly("minor_version", &cryptonote::block_header::minor_version)
        .def_readonly("timestamp", &cryptonote::block_header::timestamp)
        .def_readonly("nonce", &cryptonote::block_header::nonce)
    ;

    py::class_<cryptonote::block>(m, "Block")
        .def("is_hash_valid", &cryptonote::block::is_hash_valid)
        .def_readonly("miner_tx", &cryptonote::block::miner_tx)
        .def_readonly("tx_hashes", &cryptonote::block::tx_hashes)
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
        .def("top_block_hash", &PyBlockchainDb::top_block_hash)
        .def("get_top_block", &PyBlockchainDb::get_top_block)
        .def("get_block_hash_from_height", &PyBlockchainDb::get_block_hash_from_height)
        .def("get_blocks_range", &PyBlockchainDb::get_blocks_range)
        .def("is_open", &PyBlockchainDb::is_open)

        // TODO:: Add the rest of the mappings

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
