#include "../wallet2_api.h"

class PyWalletManager {
    public:
        bool walletExists(const std::string &path) {
            return manager->walletExists(path);
        }

        std::shared_ptr<PyWallet> createWallet(const std::string &path, const std::string &password, const std::string &language, bool testnet) {
            Monero::Wallet * w = manager->createWallet(path, password, language, testnet);
            std::shared_ptr<Monero::Wallet> shared_native_monero_wallet = std::shared_ptr<Monero::Wallet>(w);

            std::shared_ptr<PyWallet> newWallet = std::make_shared<PyWallet>();
            newWallet->setWallet(shared_native_monero_wallet);
            return newWallet;
        }

        void setManager(std::shared_ptr<Monero::WalletManager> walletManager) {
            manager = walletManager;
        }

        std::shared_ptr<Monero::WalletManager> getManager() {
            return manager;
        }

    private:
        std::shared_ptr<Monero::WalletManager> manager = nullptr;
};
