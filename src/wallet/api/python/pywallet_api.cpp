#include "../wallet2_api.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <pybind11/pybind11.h>


#include "pywallet.cpp"
#include "pywallet_manager.cpp"
#include "pywallet_manager_factory.cpp"

namespace py = pybind11;

// class PyWalletManager : public Monero::WalletManagerImpl {
// public:
//     /* Inherit the constructors */
//     //using Monero::WalletManagerImpl::Monero::WalletManager;
//
//     /* Trampoline (need one for each virtual function) */
//     bool walletExists(const std::string &path) override {
//         PYBIND11_OVERLOAD (
//             bool, /* Return type */
//             Monero::WalletManagerImpl,      /* Parent class */
//             walletExists,          /* Name of function in C++ (must match Python name) */
//             path      /* Argument(s) */
//         );
//     }
// };


PYBIND11_MODULE(pywallet_api, m) {
    m.doc() = "pbdoc() ..";

    py::class_<PyWallet>(m, "PyWallet")
        .def(py::init<>())
        .def_property("m_wallet", &PyWallet::getWallet, &PyWallet::setWallet);

    py::class_<PyWalletManager>(m, "PyWalletManager")
        .def(py::init<>())
        .def("walletExists", &PyWalletManager::walletExists)
        .def_property("manager", &PyWalletManager::getManager, &PyWalletManager::setManager)
        .def("createWallet", &PyWalletManager::createWallet)
        ;

    py::class_<PyWalletManagerFactory>(m, "PyWalletManagerFactory")
        .def(py::init<>())
        .def("getWalletManager", &PyWalletManagerFactory::getWalletManager);

  //  m.def("getWalletManager", &Monero::WalletManagerFactory::getWalletManager, py::return_value_policy::copy);

  #ifdef VERSION_INFO
      m.attr("__version__") = VERSION_INFO;
  #else
      m.attr("__version__") = "dev";
  #endif
}
