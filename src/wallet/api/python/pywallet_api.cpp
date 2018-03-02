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

    py::enum_<Monero::Wallet::ConnectionStatus>(m, "ConnectionStatus")
        .value("ConnectionStatus_Disconnected", Monero::Wallet::ConnectionStatus::ConnectionStatus_Disconnected)
        .value("ConnectionStatus_Connected", Monero::Wallet::ConnectionStatus::ConnectionStatus_Connected)
        .value("ConnectionStatus_WrongVersion", Monero::Wallet::ConnectionStatus::ConnectionStatus_WrongVersion)
        .export_values();

    py::enum_<Monero::Wallet::Status>(m, "Status")
        .value("Status_Ok", Monero::Wallet::Status::Status_Ok)
        .value("Status_Error", Monero::Wallet::Status::Status_Error)
        .value("Status_Critical", Monero::Wallet::Status::Status_Critical)
        .export_values();

    py::class_<Monero::UnsignedTransaction>(m, "UnsignedTransaction")
        .def("status", &Monero::UnsignedTransaction::status)
        .def("errorString", &Monero::UnsignedTransaction::errorString)
        .def("amount", &Monero::UnsignedTransaction::amount)
        .def("fee", &Monero::UnsignedTransaction::fee)
        .def("mixin", &Monero::UnsignedTransaction::mixin)
        .def("confirmationMessage", &Monero::UnsignedTransaction::confirmationMessage)
        .def("paymentId", &Monero::UnsignedTransaction::paymentId)
        .def("recipientAddress", &Monero::UnsignedTransaction::recipientAddress)
        .def("minMixinCount", &Monero::UnsignedTransaction::minMixinCount)
        .def("txCount", &Monero::UnsignedTransaction::txCount)
        .def("sign", &Monero::UnsignedTransaction::sign)
        ;

    py::class_<PyWallet>(m, "Wallet")
        .def(py::init<>())
        .def_property("m_wallet", &PyWallet::getWallet, &PyWallet::setWallet)
        .def("seed", &PyWallet::seed)
        .def("getSeedLanguage", &PyWallet::getSeedLanguage)
        .def("setSeedLanguage", &PyWallet::setSeedLanguage)
        .def("status", &PyWallet::status)
        .def("errorString", &PyWallet::errorString)
        .def("setPassword", &PyWallet::setPassword)
        .def("address", &PyWallet::address)
        .def("mainAddress", &PyWallet::mainAddress)
        .def("path", &PyWallet::path)
        .def("testnet", &PyWallet::testnet)
        .def("hardForkInfo", &PyWallet::hardForkInfo)
        .def("useForkRules", &PyWallet::useForkRules)
        .def("integratedAddress", &PyWallet::integratedAddress)
        .def("secretViewKey", &PyWallet::secretViewKey)
        .def("publicViewKey", &PyWallet::publicViewKey)
        .def("secretSpendKey", &PyWallet::secretSpendKey)
        .def("publicSpendKey", &PyWallet::publicSpendKey)
        .def("store", &PyWallet::store)
        .def("filename", &PyWallet::filename)
        .def("keysFilename", &PyWallet::keysFilename)
        .def("init", &PyWallet::init)
        //.def_static("init", &PyWallet::init)
        .def("createWatchOnly", &PyWallet::createWatchOnly)
        .def("setRefreshFromBlockHeight", &PyWallet::setRefreshFromBlockHeight)
        .def("getRefreshFromBlockHeight", &PyWallet::getRefreshFromBlockHeight)
        .def("setRecoveringFromSeed", &PyWallet::setRecoveringFromSeed)
        .def("connectToDaemon", &PyWallet::connectToDaemon)
        .def("setTrustedDaemon", &PyWallet::setTrustedDaemon)
        .def("trustedDaemon", &PyWallet::trustedDaemon)
        .def("balance", &PyWallet::balance)
        .def("balanceAll", &PyWallet::balanceAll)
        .def("unlockedBalance", &PyWallet::unlockedBalance)
        .def("unlockedBalanceAll", &PyWallet::unlockedBalanceAll)
        .def("watchOnly", &PyWallet::watchOnly)
        .def("blockChainHeight", &PyWallet::blockChainHeight)
        .def("approximateBlockChainHeight", &PyWallet::approximateBlockChainHeight)
        .def("daemonBlockChainHeight", &PyWallet::daemonBlockChainHeight)
        .def("daemonBlockChainTargetHeight", &PyWallet::daemonBlockChainTargetHeight)
        .def("synchronized", &PyWallet::synchronized)
        .def("displayAmount", &PyWallet::displayAmount)
        .def("amountFromString", &PyWallet::amountFromString)
        .def("amountFromDouble", &PyWallet::amountFromDouble)
        .def("genPaymentId", &PyWallet::genPaymentId)
        .def("paymentIdValid", &PyWallet::paymentIdValid)
        .def("addressValid", &PyWallet::addressValid)
        .def("keyValid", &PyWallet::keyValid)
        .def("paymentIdFromAddress", &PyWallet::paymentIdFromAddress)
        .def("maximumAllowedAmount", &PyWallet::maximumAllowedAmount)
        // .def("init", &PyWallet::init,
        //     py::arg("argv0"),
        //     py::arg("default_log_base_name"))
        .def("debug", &PyWallet::debug)
        .def("startRefresh", &PyWallet::startRefresh)
        .def("pauseRefresh", &PyWallet::pauseRefresh)
        .def("refresh", &PyWallet::refresh)
        .def("refreshAsync", &PyWallet::refreshAsync)
        .def("setAutoRefreshInterval", &PyWallet::setAutoRefreshInterval)
        .def("autoRefreshInterval", &PyWallet::autoRefreshInterval)
        .def("addSubaddressAccount", &PyWallet::addSubaddressAccount)
        .def("numSubaddressAccounts", &PyWallet::numSubaddressAccounts)
        .def("numSubaddresses", &PyWallet::numSubaddresses)
        .def("addSubaddress", &PyWallet::addSubaddress)
        .def("getSubaddressLabel", &PyWallet::getSubaddressLabel)
        .def("setSubaddressLabel", &PyWallet::setSubaddressLabel)
        .def("submitTransaction", &PyWallet::submitTransaction)
        .def("exportKeyImages", &PyWallet::exportKeyImages)
        .def("importKeyImages", &PyWallet::importKeyImages)
        .def("defaultMixin", &PyWallet::defaultMixin)
        .def("setDefaultMixin", &PyWallet::setDefaultMixin)
        .def("setUserNote", &PyWallet::setUserNote)
        .def("getUserNote", &PyWallet::getUserNote)
        .def("getTxKey", &PyWallet::getTxKey)
        .def("checkTxKey", &PyWallet::checkTxKey)
        .def("getTxProof", &PyWallet::getTxProof)
        .def("checkTxProof", &PyWallet::checkTxProof)
        .def("getSpendProof", &PyWallet::getSpendProof)
        .def("checkSpendProof", &PyWallet::checkSpendProof)
        .def("getReserveProof", &PyWallet::getReserveProof)
        .def("checkReserveProof", &PyWallet::checkReserveProof)
        .def("signMessage", &PyWallet::signMessage)
        .def("verifySignedMessage", &PyWallet::verifySignedMessage)
        .def("parse_uri", &PyWallet::parse_uri)
        .def("getDefaultDataDir", &PyWallet::getDefaultDataDir)
        .def("rescanSpent", &PyWallet::rescanSpent)
        .def("lightWalletLogin", &PyWallet::lightWalletLogin)
        .def("lightWalletImportWalletRequest", &PyWallet::lightWalletImportWalletRequest)
        .def("connected", &PyWallet::connected)
        ;

    py::class_<PyWalletManager>(m, "WalletManager")
        .def(py::init<>())
        .def("walletExists", &PyWalletManager::walletExists)
        .def_property("manager", &PyWalletManager::getManager, &PyWalletManager::setManager)
        .def("createWallet", &PyWalletManager::createWallet)
        .def("openWallet", &PyWalletManager::openWallet)
        .def("recoveryWallet", &PyWalletManager::recoveryWallet, py::arg("path"),
                    py::arg("password"),
                    py::arg("mnemonic"),
                    py::arg("testnet") = 0,
                    py::arg("restoreHeight") = 0)

        .def("createWalletFromKeys", &PyWalletManager::createWalletFromKeys, py::arg("path"),
                    py::arg("password"),
                    py::arg("language"),
                    py::arg("testnet") = 0,
                    py::arg("restoreHeight") = 0,
                    py::arg("addressString"),
                    py::arg("viewKeyString"),
                    py::arg("spendKeyString"))

        .def("closeWallet", &PyWalletManager::closeWallet)
        .def("verifyWalletPassword", &PyWalletManager::verifyWalletPassword)
        .def("findWallets", &PyWalletManager::findWallets)
        .def("errorString", &PyWalletManager::errorString)
        .def("setDaemonAddress", &PyWalletManager::setDaemonAddress)
        .def("connected", &PyWalletManager::connected)
        .def("blockchainHeight", &PyWalletManager::blockchainHeight)
        .def("blockchainTargetHeight", &PyWalletManager::blockchainTargetHeight)
        .def("networkDifficulty", &PyWalletManager::networkDifficulty)
        .def("miningHashRate", &PyWalletManager::miningHashRate)
        .def("blockTarget", &PyWalletManager::blockTarget)
        .def("isMining", &PyWalletManager::isMining)
        .def("startMining", &PyWalletManager::startMining)
        .def("stopMining", &PyWalletManager::stopMining)
        .def("resolveOpenAlias", &PyWalletManager::resolveOpenAlias)
        ;

    py::class_<PyWalletManagerFactory>(m, "WalletManagerFactory")
        //.def(py::init<>())
        .def_static("setLogLevel", &PyWalletManagerFactory::setLogLevel)
        .def_static("getWalletManager", &PyWalletManagerFactory::getWalletManager);

  //  m.def("getWalletManager", &Monero::WalletManagerFactory::getWalletManager, py::return_value_policy::copy);

  #ifdef VERSION_INFO
      m.attr("__version__") = VERSION_INFO;
  #else
      m.attr("__version__") = "dev";
  #endif
}
