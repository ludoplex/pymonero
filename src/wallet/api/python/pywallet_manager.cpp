#include "../wallet2_api.h"
#include <memory>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class PyWalletManager {
    public:
        bool walletExists(const std::string &path) {
            return manager->walletExists(path);
        }

        std::shared_ptr<PyWallet> createWallet(const std::string &path, const std::string &password, const std::string &language, bool testnet) {

            Monero::Wallet * w = manager->createWallet(path, password, language, testnet);
            std::shared_ptr<Monero::Wallet> shared_native_monero_wallet (w);

            if (!m_current_wallet) {
              std::shared_ptr<PyWallet> newWallet (new PyWallet());
              m_current_wallet = newWallet;
            }

            m_current_wallet->setWallet(shared_native_monero_wallet);
            return m_current_wallet;
        }

        /*!
         * \brief  Opens existing wallet
         * \param  path           Name of wallet file
         * \param  password       Password of wallet file
         * \return                Wallet instance (Wallet::status() needs to be called to check if opened successfully)
         */
         std::shared_ptr<PyWallet> openWallet(const std::string &path, const std::string &password, bool testnet = false) {
           Monero::Wallet * w = manager->openWallet(path, password, testnet);
           std::shared_ptr<Monero::Wallet> shared_native_monero_wallet (w);

           if (!m_current_wallet) {
             std::shared_ptr<PyWallet> newWallet (new PyWallet());
             m_current_wallet = newWallet;
           }

           m_current_wallet->setWallet(shared_native_monero_wallet);
           return m_current_wallet;
         }

        /*!
         * \brief  recovers existing wallet using mnemonic (electrum seed)
         * \param  path           Name of wallet file to be created
         * \param  password       Password of wallet file
         * \param  mnemonic       mnemonic (25 words electrum seed)
         * \param  testnet        testnet
         * \param  restoreHeight  restore from start height
         * \return                Wallet instance (Wallet::status() needs to be called to check if recovered successfully)
         */
        std::shared_ptr<PyWallet> recoveryWallet(const std::string &path, const std::string &password, const std::string &mnemonic,
           bool testnet = false, uint64_t restoreHeight = 0) {

            Monero::Wallet * w = manager->recoveryWallet(path, password, mnemonic, testnet, restoreHeight);
            std::shared_ptr<Monero::Wallet> shared_native_monero_wallet (w);

            if (!m_current_wallet) {
              std::shared_ptr<PyWallet> newWallet (new PyWallet());
              m_current_wallet = newWallet;
            }

            m_current_wallet->setWallet(shared_native_monero_wallet);
            return m_current_wallet;
        }

        /*!
         * \brief  recovers existing wallet using keys. Creates a view only wallet if spend key is omitted
         * \param  path           Name of wallet file to be created
         * \param  password       Password of wallet file
         * \param  language       language
         * \param  testnet        testnet
         * \param  restoreHeight  restore from start height
         * \param  addressString  public address
         * \param  viewKeyString  view key
         * \param  spendKeyString spend key (optional)
         * \return                Wallet instance (Wallet::status() needs to be called to check if recovered successfully)
         */
         std::shared_ptr<PyWallet> createWalletFromKeys(const std::string &path,
           const std::string &password,
           const std::string &language,
           bool testnet,
           uint64_t restoreHeight,
           const std::string &addressString,
           const std::string &viewKeyString,
           const std::string &spendKeyString = "") {

             Monero::Wallet * w = manager->createWalletFromKeys(path, password, language, testnet, restoreHeight, addressString, viewKeyString, spendKeyString);
             std::shared_ptr<Monero::Wallet> shared_native_monero_wallet (w);

             if (!m_current_wallet) {
               std::shared_ptr<PyWallet> newWallet (new PyWallet());
               m_current_wallet = newWallet;
             }

             m_current_wallet->setWallet(shared_native_monero_wallet);
             return m_current_wallet;
           }

        /*!
         * \brief Closes wallet. In case operation succeded, wallet object deleted. in case operation failed, wallet object not deleted
         * \param wallet        previously opened / created wallet instance
         * \return              None
         */
        bool closeWallet(std::shared_ptr<PyWallet> wallet, bool store = true) {
          return manager->closeWallet(wallet->getWallet().get(), store);
        }

        /*!
         * @brief verifyWalletPassword - check if the given filename is the wallet
         * @param keys_file_name - location of keys file
         * @param password - password to verify
         * @param no_spend_key - verify only view keys?
         * @return - true if password is correct
         */
        bool verifyWalletPassword(const std::string &keys_file_name, const std::string &password, bool no_spend_key) {
          return manager->verifyWalletPassword(keys_file_name, password, no_spend_key);
        }
        /*!
         * \brief findWallets - searches for the wallet files by given path name recursively
         * \param path - starting point to search
         * \return - list of strings with found wallets (absolute paths);
         */
        std::vector<std::string> findWallets(const std::string &path) {
          return manager->findWallets(path);
        }

        //! returns verbose error string regarding last error;
        std::string errorString() {
          return manager->errorString();
        }

        //! set the daemon address (hostname and port)
        void setDaemonAddress(const std::string &address) {
          manager->setDaemonAddress(address);
        }

        //! returns whether the daemon can be reached, and its version number
        bool connected(uint32_t *version = NULL) {
          return manager->connected(version);
        }

        //! returns current blockchain height
        uint64_t blockchainHeight() {
          return manager->blockchainHeight();
        }

        //! returns current blockchain target height
        uint64_t blockchainTargetHeight() {
          return manager->blockchainTargetHeight();
        }

        //! returns current network difficulty
        uint64_t networkDifficulty() {
          return manager->networkDifficulty();
        }

        double miningHashRate() {
          return manager->miningHashRate();
        }

        uint64_t blockTarget() {
            return manager->blockTarget();
        }

        bool isMining() {
          return manager->isMining();
        }

        bool startMining(const std::string &address, uint32_t threads = 1, bool background_mining = false, bool ignore_battery = true) {
          return manager->startMining(address, threads, background_mining, ignore_battery);
        }

        bool stopMining() {
          return manager->stopMining();
        }

        std::string resolveOpenAlias(const std::string &address, bool &dnssec_valid) {
          return manager->resolveOpenAlias(address, dnssec_valid);
        }

        void setManager(std::shared_ptr<Monero::WalletManager> walletManager) {
            manager = walletManager;
        }

        std::shared_ptr<Monero::WalletManager> getManager() {
            return manager;
        }

    private:
        std::shared_ptr<PyWallet> m_current_wallet = nullptr;
        std::shared_ptr<Monero::WalletManager> manager = nullptr;
};
