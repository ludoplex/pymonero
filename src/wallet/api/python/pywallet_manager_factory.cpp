#include "../wallet2_api.h"
#include "../wallet_manager.h"

struct PyWalletManagerFactory {

    public:
      static std::shared_ptr<PyWalletManager> getWalletManager() {

        if  (!m_manager) {
          Monero::WalletManagerFactory::setLogLevel(0);

          Monero::WalletManagerImpl * managerImpl = dynamic_cast<Monero::WalletManagerImpl*>(Monero::WalletManagerFactory::getWalletManager());
          std::shared_ptr<Monero::WalletManagerImpl> m_impl(managerImpl);
          std::shared_ptr<PyWalletManager> newPyWalletManager (new PyWalletManager());

          m_manager = newPyWalletManager;
          m_manager->setManager(m_impl);
        }

        return m_manager;
      }

      static void setLogLevel(int level) {
        Monero::WalletManagerFactory::setLogLevel(level);
      }

    private:
        static std::shared_ptr<PyWalletManager> m_manager;
};

std::shared_ptr<PyWalletManager> PyWalletManagerFactory::m_manager = nullptr;
