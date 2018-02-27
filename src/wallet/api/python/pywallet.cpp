#include "../wallet2_api.h"

class PyWallet {
    public:
        void setWallet(std::shared_ptr<Monero::Wallet> wallet) {
            m_wallet = wallet;
        }

        std::shared_ptr<Monero::Wallet> getWallet() {
            return m_wallet;
        }

    private:
        std::shared_ptr<Monero::Wallet> m_wallet;
};
