#include "../wallet2_api.h"

class PyWallet {
    public:
        void setWallet(std::shared_ptr<Monero::Wallet> wallet) {
            m_wallet = wallet;
        }

        std::shared_ptr<Monero::Wallet> getWallet() {
            return m_wallet;
        }

        std::string seed() {
          return m_wallet->seed();
        }

        std::string getSeedLanguage() {
            return m_wallet->getSeedLanguage();
        }

        void setSeedLanguage(const std::string &arg) {
          m_wallet->setSeedLanguage(arg);
        }
        //! returns wallet status (Status_Ok | Status_Error)
        int status() {
          return m_wallet->status();
        }
        //! in case error status, returns error string
        std::string errorString() {
          return m_wallet->errorString();
        }

        bool setPassword(const std::string &password) {
          return m_wallet->setPassword(password);
        }

        std::string address(uint32_t accountIndex = 0, uint32_t addressIndex = 0) {
          return m_wallet->address(accountIndex, addressIndex);
        }

        std::string mainAddress() {
          return m_wallet->mainAddress();
        }

        std::string path() {
          return m_wallet->path();
        }

        bool testnet() {
          return m_wallet->testnet();
        }

        //! returns current hard fork info
        void hardForkInfo(uint8_t &version, uint64_t &earliest_height) {
          m_wallet->hardForkInfo(version, earliest_height);
        }
        //! check if hard fork rules should be used
        bool useForkRules(uint8_t version, int64_t early_blocks) {
          return m_wallet->useForkRules(version, early_blocks);
        }

        /*!
         * \brief integratedAddress - returns integrated address for current wallet address and given payment_id.
         *                            if passed "payment_id" param is an empty string or not-valid payment id string
         *                            (16 characters hexadecimal string) - random payment_id will be generated
         *
         * \param payment_id        - 16 characters hexadecimal string or empty string if new random payment id needs to be
         *                            generated
         * \return                  - 106 characters string representing integrated address
         */
        std::string integratedAddress(const std::string &payment_id) {
          return m_wallet->integratedAddress(payment_id);
        }

       /*!
        * \brief secretViewKey     - returns secret view key
        * \return                  - secret view key
        */
        std::string secretViewKey() {
          return m_wallet->secretViewKey();
        }

       /*!
        * \brief publicViewKey     - returns public view key
        * \return                  - public view key
        */
        std::string publicViewKey() {
          return m_wallet->publicViewKey();
        }

       /*!
        * \brief secretSpendKey    - returns secret spend key
        * \return                  - secret spend key
        */
        std::string secretSpendKey() {
          return m_wallet->secretSpendKey();
        }

       /*!
        * \brief publicSpendKey    - returns public spend key
        * \return                  - public spend key
        */
        std::string publicSpendKey() {
          return m_wallet->publicSpendKey();
        }

        /*!
         * \brief store - stores wallet to file.
         * \param path - main filename to store wallet to. additionally stores address file and keys file.
         *               to store to the same file - just pass empty string;
         * \return
         */
        bool store(const std::string &path) {
          return m_wallet->store(path);
        }
        /*!
         * \brief filename - returns wallet filename
         * \return
         */
        std::string filename() {
          return m_wallet->filename();
        }
        /*!
         * \brief keysFilename - returns keys filename. usually this formed as "wallet_filename".keys
         * \return
         */
        std::string keysFilename() {
          return m_wallet->keysFilename();
        }
        /*!
         * \brief init - initializes wallet with daemon connection params.
         *               if daemon_address is local address, "trusted daemon" will be set to true forcibly
         *               startRefresh() should be called when wallet is initialized.
         *
         * \param daemon_address - daemon address in "hostname:port" format
         * \param upper_transaction_size_limit
         * \param daemon_username
         * \param daemon_password
         * \param lightWallet - start wallet in light mode, connect to a openmonero compatible server.
         * \return  - true on success
         */
        bool init(const std::string &daemon_address, uint64_t upper_transaction_size_limit = 0, const std::string &daemon_username = "", const std::string &daemon_password = "",
        bool use_ssl = false, bool lightWallet = false) {
          return m_wallet->init(daemon_address, upper_transaction_size_limit, daemon_username, daemon_password, use_ssl, lightWallet);
        }

       /*!
        * \brief createWatchOnly - Creates a watch only wallet
        * \param path - where to store the wallet
        * \param password
        * \param language
        * \return  - true if created successfully
        */
        bool createWatchOnly(const std::string &path, const std::string &password, const std::string &language) {
          return m_wallet->createWatchOnly(path, password, language);
        }

       /*!
        * \brief setRefreshFromBlockHeight - start refresh from block height on recover
        *
        * \param refresh_from_block_height - blockchain start height
        */
        void setRefreshFromBlockHeight(uint64_t refresh_from_block_height) {
          m_wallet->setRefreshFromBlockHeight(refresh_from_block_height);
        }

       /*!
        * \brief getRestoreHeight - get wallet creation height
        *
        */
        uint64_t getRefreshFromBlockHeight() {
          return m_wallet->getRefreshFromBlockHeight();
        }

       /*!
        * \brief setRecoveringFromSeed - set state recover form seed
        *
        * \param recoveringFromSeed - true/false
        */
        void setRecoveringFromSeed(bool recoveringFromSeed) {
          m_wallet->setRecoveringFromSeed(recoveringFromSeed);
        }

        /**
         * @brief connectToDaemon - connects to the daemon. TODO: check if it can be removed
         * @return
         */
        bool connectToDaemon() {
          return m_wallet->connectToDaemon();
        }

        /**
         * @brief connected - checks if the wallet connected to the daemon
         * @return - true if connected
         */
        Monero::Wallet::ConnectionStatus connected() {
          return m_wallet->connected();
        }
        //##

        void setTrustedDaemon(bool arg) {
          m_wallet->setTrustedDaemon(arg);
        }

        bool trustedDaemon() {
            return m_wallet->trustedDaemon();
        }

        uint64_t balance(uint32_t accountIndex = 0) {
          return m_wallet->balance(accountIndex);
        }

        uint64_t balanceAll()  {
            return m_wallet->balanceAll();
        }

        uint64_t unlockedBalance(uint32_t accountIndex = 0) {
          return m_wallet->unlockedBalance(accountIndex);
        }

        uint64_t unlockedBalanceAll() {
            return m_wallet->unlockedBalanceAll();
        }

       /**
        * @brief watchOnly - checks if wallet is watch only
        * @return - true if watch only
        */
        bool watchOnly() {
          return m_wallet->watchOnly();
        }

        /**
         * @brief blockChainHeight - returns current blockchain height
         * @return
         */
        uint64_t blockChainHeight() {
          return m_wallet->blockChainHeight();
        }

        /**
        * @brief approximateBlockChainHeight - returns approximate blockchain height calculated from date/time
        * @return
        */
        uint64_t approximateBlockChainHeight() {
          return m_wallet->approximateBlockChainHeight();
        }

        /**
         * @brief daemonBlockChainHeight - returns daemon blockchain height
         * @return 0 - in case error communicating with the daemon.
         *             status() will return Status_Error and errorString() will return verbose error description
         */
        uint64_t daemonBlockChainHeight() {
          return m_wallet->daemonBlockChainHeight();
        }

        /**
         * @brief daemonBlockChainTargetHeight - returns daemon blockchain target height
         * @return 0 - in case error communicating with the daemon.
         *             status() will return Status_Error and errorString() will return verbose error description
         */
        uint64_t daemonBlockChainTargetHeight() {
          return m_wallet->daemonBlockChainTargetHeight();
        }

        /**
         * @brief synchronized - checks if wallet was ever synchronized
         * @return
         */
        bool synchronized() {
          return m_wallet->synchronized();
        }

        static std::string displayAmount(uint64_t amount) {
          return Monero::Wallet::displayAmount(amount);
        }

        static uint64_t amountFromString(const std::string &amount) {
          return Monero::Wallet::amountFromString(amount);
        }

        static uint64_t amountFromDouble(double amount) {
          return Monero::Wallet::amountFromDouble(amount);
        }

        static std::string genPaymentId() {
          return Monero::Wallet::genPaymentId();
        }

        static bool paymentIdValid(const std::string &paiment_id) {
          return Monero::Wallet::paymentIdValid(paiment_id);
        }

        static bool addressValid(const std::string &str, bool testnet) {
          return Monero::Wallet::addressValid(str, testnet);
        }

        static bool keyValid(const std::string &secret_key_string, const std::string &address_string, bool isViewKey, bool testnet, std::string &error) {
          return Monero::Wallet::keyValid(secret_key_string, address_string, isViewKey, testnet, error);
        }

        static std::string paymentIdFromAddress(const std::string &str, bool testnet) {
          return Monero::Wallet::paymentIdFromAddress(str, testnet);
        }

        static uint64_t maximumAllowedAmount() {
          return Monero::Wallet::maximumAllowedAmount();
        }

        // Easylogger wrapper
        // static void init(const char *argv0, const char *default_log_base_name) {
        //   Monero::Wallet::init(argv0, default_log_base_name);
        // }

        //##

        static void debug(const std::string &category, const std::string &str) {
           Monero::Wallet::debug(category, str);
        }

       /**
        * @brief StartRefresh - Start/resume refresh thread (refresh every 10 seconds)
        */
        void startRefresh() {
          m_wallet->startRefresh();
        }
       /**
        * @brief pauseRefresh - pause refresh thread
        */
        void pauseRefresh() {
          m_wallet->pauseRefresh();
        }

        /**
         * @brief refresh - refreshes the wallet, updating transactions from daemon
         * @return - true if refreshed successfully;
         */
        bool refresh() {
          return m_wallet->refresh();
        }

        /**
         * @brief refreshAsync - refreshes wallet asynchronously.
         */
        void refreshAsync() {
          return m_wallet->refreshAsync();
        }

        /**
         * @brief setAutoRefreshInterval - setup interval for automatic refresh.
         * @param seconds - interval in millis. if zero or less than zero - automatic refresh disabled;
         */
        void setAutoRefreshInterval(int millis) {
          m_wallet->setAutoRefreshInterval(millis);
        }

        /**
         * @brief autoRefreshInterval - returns automatic refresh interval in millis
         * @return
         */
        int autoRefreshInterval() {
          return m_wallet->autoRefreshInterval();
        }

        /**
         * @brief addSubaddressAccount - appends a new subaddress account at the end of the last major index of existing subaddress accounts
         * @param label - the label for the new account (which is the as the label of the primary address (accountIndex,0))
         */
        void addSubaddressAccount(const std::string& label) {
          m_wallet->addSubaddressAccount(label);
        }
        /**
         * @brief numSubaddressAccounts - returns the number of existing subaddress accounts
         */
        size_t numSubaddressAccounts() {
          return m_wallet->numSubaddressAccounts();
        }
        /**
         * @brief numSubaddresses - returns the number of existing subaddresses associated with the specified subaddress account
         * @param accountIndex - the major index specifying the subaddress account
         */
        size_t numSubaddresses(uint32_t accountIndex) {
          return m_wallet->numSubaddresses(accountIndex);
        }
        /**
         * @brief addSubaddress - appends a new subaddress at the end of the last minor index of the specified subaddress account
         * @param accountIndex - the major index specifying the subaddress account
         * @param label - the label for the new subaddress
         */
        void addSubaddress(uint32_t accountIndex, const std::string& label) {
          m_wallet->addSubaddress(accountIndex, label);
        }
        /**
         * @brief getSubaddressLabel - gets the label of the specified subaddress
         * @param accountIndex - the major index specifying the subaddress account
         * @param addressIndex - the minor index specifying the subaddress
         */
        std::string getSubaddressLabel(uint32_t accountIndex, uint32_t addressIndex) {
          return m_wallet->getSubaddressLabel(accountIndex, addressIndex);
        }
        /**
         * @brief setSubaddressLabel - sets the label of the specified subaddress
         * @param accountIndex - the major index specifying the subaddress account
         * @param addressIndex - the minor index specifying the subaddress
         * @param label - the new label for the specified subaddress
         */
        void setSubaddressLabel(uint32_t accountIndex, uint32_t addressIndex, const std::string &label) {
          m_wallet->setSubaddressLabel(accountIndex, addressIndex, label);
        }

        /*!
         * \brief createTransaction creates transaction. if dst_addr is an integrated address, payment_id is ignored
         * \param dst_addr          destination address as string
         * \param payment_id        optional payment_id, can be empty string
         * \param amount            amount
         * \param mixin_count       mixin count. if 0 passed, wallet will use default value
         * \param subaddr_account   subaddress account from which the input funds are taken
         * \param subaddr_indices   set of subaddress indices to use for transfer or sweeping. if set empty, all are chosen when sweeping, and one or more are automatically chosen when transferring. after execution, returns the set of actually used indices
         * \param priority
         * \return                  PendingTransaction object. caller is responsible to check PendingTransaction::status()
         *                          after object returned
         */

       //  virtual PendingTransaction * createTransaction(const std::string &dst_addr, const std::string &payment_id,
       //                                                 optional<uint64_t> amount, uint32_t mixin_count,
       //                                                 PendingTransaction::Priority = PendingTransaction::Priority_Low,
       //                                                 uint32_t subaddr_account = 0,
       //                                                 std::set<uint32_t> subaddr_indices = {}) = 0;
       //
       //  /*!
       //   * \brief createSweepUnmixableTransaction creates transaction with unmixable outputs.
       //   * \return                  PendingTransaction object. caller is responsible to check PendingTransaction::status()
       //   *                          after object returned
       //   */
       //
       //  virtual PendingTransaction * createSweepUnmixableTransaction() = 0;
       //
       // /*!
       //  * \brief loadUnsignedTx  - creates transaction from unsigned tx file
       //  * \return                - UnsignedTransaction object. caller is responsible to check UnsignedTransaction::status()
       //  *                          after object returned
       //  */
       //  virtual UnsignedTransaction * loadUnsignedTx(const std::string &unsigned_filename) = 0;


       /// ##

       /*!
        * \brief submitTransaction - submits transaction in signed tx file
        * \return                  - true on success
        */
        bool submitTransaction(const std::string &fileName) {
          return m_wallet->submitTransaction(fileName);
        }


        /*!
         * \brief disposeTransaction - destroys transaction object
         * \param t -  pointer to the "PendingTransaction" object. Pointer is not valid after function returned;
         */
        //virtual void disposeTransaction(PendingTransaction * t) = 0;



//##



       /*!
        * \brief exportKeyImages - exports key images to file
        * \param filename
        * \return                  - true on success
        */
        bool exportKeyImages(const std::string &filename) {
          return m_wallet->exportKeyImages(filename);
        }

       /*!
        * \brief importKeyImages - imports key images from file
        * \param filename
        * \return                  - true on success
        */
        bool importKeyImages(const std::string &filename) {
          return m_wallet->importKeyImages(filename);
        }

// ##

        // virtual TransactionHistory * history() = 0;
        // virtual AddressBook * addressBook() = 0;
        // virtual def * subaddress() = 0;
        // virtual SubaddressAccount * subaddressAccount() = 0;
        // virtual void setListener(WalletListener *) = 0;


        /*!
         * \brief defaultMixin - returns number of mixins used in transactions
         * \return
         */
        uint32_t defaultMixin() {
          return m_wallet->defaultMixin();
        }

        /*!
         * \brief setDefaultMixin - setum number of mixins to be used for new transactions
         * \param arg
         */
        void setDefaultMixin(uint32_t arg) {
          m_wallet->setDefaultMixin(arg);
        }

        /*!
         * \brief setUserNote - attach an arbitrary string note to a txid
         * \param txid - the transaction id to attach the note to
         * \param note - the note
         * \return true if succesful, false otherwise
         */
        bool setUserNote(const std::string &txid, const std::string &note) {
          return m_wallet->setUserNote(txid, note);
        }
        /*!
         * \brief getUserNote - return an arbitrary string note attached to a txid
         * \param txid - the transaction id to attach the note to
         * \return the attached note, or empty string if there is none
         */
        std::string getUserNote(const std::string &txid) {
          return m_wallet->getUserNote(txid);
        }

        std::string getTxKey(const std::string &txid) {
          return m_wallet->getTxKey(txid);
        }

        bool checkTxKey(const std::string &txid, std::string tx_key, const std::string &address, uint64_t &received, bool &in_pool, uint64_t &confirmations) {
          return m_wallet->checkTxKey(txid, tx_key, address, received, in_pool, confirmations);
        }

        std::string getTxProof(const std::string &txid, const std::string &address, const std::string &message) {
          return m_wallet->getTxProof(txid, address, message);
        }

        bool checkTxProof(const std::string &txid, const std::string &address, const std::string &message, const std::string &signature, bool &good, uint64_t &received, bool &in_pool,
          uint64_t &confirmations) {
          return m_wallet->checkTxProof(txid, address, message, signature, good, received, in_pool, confirmations);
        }

        std::string getSpendProof(const std::string &txid, const std::string &message) {
            return m_wallet->getSpendProof(txid, message);
        }

        bool checkSpendProof(const std::string &txid, const std::string &message, const std::string &signature, bool &good) {
          return m_wallet->checkSpendProof(txid, message, signature, good);
        }
        /*!
         * \brief getReserveProof - Generates a proof that proves the reserve of unspent funds
         *                          Parameters `account_index` and `amount` are ignored when `all` is true
         */
        std::string getReserveProof(bool all, uint32_t account_index, uint64_t amount, const std::string &message) {
            return m_wallet->getReserveProof(all, account_index, amount, message);
        }

        bool checkReserveProof(const std::string &address, const std::string &message, const std::string &signature, bool &good, uint64_t &total, uint64_t &spent) {
          return m_wallet->checkReserveProof(address, message, signature, good, total, spent);
        }

        /*
         * \brief signMessage - sign a message with the spend private key
         * \param message - the message to sign (arbitrary byte data)
         * \return the signature
         */
        std::string signMessage(const std::string &message) {
            return m_wallet->signMessage(message);
        }

        /*!
         * \brief verifySignedMessage - verify a signature matches a given message
         * \param message - the message (arbitrary byte data)
         * \param address - the address the signature claims to be made with
         * \param signature - the signature
         * \return true if the signature verified, false otherwise
         */
        bool verifySignedMessage(const std::string &message, const std::string &addres, const std::string &signature) {
          return m_wallet->verifySignedMessage(message, addres, signature);
        }

        bool parse_uri(const std::string &uri, std::string &address, std::string &payment_id, uint64_t &amount, std::string &tx_description, std::string &recipient_name, std::vector<std::string> &unknown_parameters, std::string &error) {
          return m_wallet->parse_uri(uri, address, payment_id, amount, tx_description, recipient_name, unknown_parameters, error);
        }

        std::string getDefaultDataDir() {
          return m_wallet->getDefaultDataDir();
        }

       /*
        * \brief rescanSpent - Rescan spent outputs - Can only be used with trusted daemon
        * \return true on success
        */
        bool rescanSpent() {
          return m_wallet->rescanSpent();
        }

        //! Light wallet authenticate and login
        bool lightWalletLogin(bool &isNewWallet) {
          return m_wallet->lightWalletLogin(isNewWallet);
        }

        //! Initiates a light wallet import wallet request
        bool lightWalletImportWalletRequest(std::string &payment_id, uint64_t &fee, bool &new_request, bool &request_fulfilled, std::string &payment_address, std::string &status) {
          return m_wallet->lightWalletImportWalletRequest(payment_id, fee, new_request, request_fulfilled, payment_address, status);
        }


    private:
        std::shared_ptr<Monero::Wallet> m_wallet;
};
