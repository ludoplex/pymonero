#include "../wallet2_api.h"
#include "../wallet_manager.h"

struct PyWalletManagerFactory {
    public:
        std::shared_ptr<PyWalletManager> getWalletManager() {

            if  (!m_manager) {
                std::shared_ptr<Monero::WalletManagerImpl> m_impl = std::make_shared<Monero::WalletManagerImpl>();
                m_manager = std::make_shared<PyWalletManager>();
                m_manager->setManager(m_impl);
            }

            return m_manager;
        }

    private:
        std::shared_ptr<PyWalletManager> m_manager = nullptr;
};
