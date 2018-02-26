#include "../wallet_manager.h"
#include <pybind11/pybind11.h>

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

    py::class_<Monero::WalletManagerImpl>(m, "WalletManagerImpl")
        .def(py::init<>())
        .def("walletExists", &Monero::WalletManagerImpl::walletExists);

    // py::class_<Monero::WalletManagerFactory>(m, "WalletManagerFactory")
    //     .def(py::init<>())
    //     .def("getWalletManager", &Monero::WalletManagerFactory::getWalletManager);

  //  m.def("getWalletManager", &Monero::WalletManagerFactory::getWalletManager, py::return_value_policy::copy);

  #ifdef VERSION_INFO
      m.attr("__version__") = VERSION_INFO;
  #else
      m.attr("__version__") = "dev";
  #endif
}
