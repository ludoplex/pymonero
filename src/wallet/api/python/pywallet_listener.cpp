#include "../wallet2_api.h"
#include <memory>
#include <pybind11/pybind11.h>

using namespace Monero;
namespace py = pybind11;

class PyWalletListener : public Monero::WalletListener{
public:
    PyWalletListener() : WalletListener(){
        // m_moneySpent = nullptr;
        // m_moneyReceived = nullptr;
        // m_unconfirmedMoneyReceived = nullptr;
        // m_newBlock = nullptr;
        // m_updated = nullptr;
        // m_refreshed = nullptr;
    }

    void add_callbacks (const std::function<void(const std::string &txId, uint64_t amount)> &moneySpent,
    const std::function<void(const std::string &txId, uint64_t amount)> &moneyReceived,
    const std::function<void(const std::string &txId, uint64_t amount)> &unconfirmedMoneyReceived,
    const std::function<void(uint64_t height)> &newBlock,
    const std::function<void()> &updated,
    const std::function<void()> &refreshed) {

        m_moneySpent = moneySpent;
        m_moneyReceived = moneyReceived;
        m_unconfirmedMoneyReceived = unconfirmedMoneyReceived;
        m_newBlock = newBlock;
        m_updated = updated;
        m_refreshed = refreshed;
    }

    /**
    * @brief moneySpent - called when money spent
    * @param txId       - transaction id
    * @param amount     - amount
    */
    void moneySpent(const std::string &txId, uint64_t amount) {
        m_moneySpent(txId, amount);
    }

    /**
    * @brief moneyReceived - called when money received
    * @param txId          - transaction id
    * @param amount        - amount
    */
    void moneyReceived(const std::string &txId, uint64_t amount) {
        m_moneyReceived(txId, amount);
    }

    /**
    * @brief unconfirmedMoneyReceived - called when payment arrived in tx pool
    * @param txId          - transaction id
    * @param amount        - amount
    */
    void unconfirmedMoneyReceived(const std::string &txId, uint64_t amount) {
        m_unconfirmedMoneyReceived(txId, amount);
    }

    /**
    * @brief newBlock      - called when new block received
    * @param height        - block height
    */
    void newBlock(uint64_t height) {
        m_newBlock(height);
    }

    /**
    * @brief updated  - generic callback, called when any event (sent/received/block reveived/etc) happened with the wallet;
    */
    void updated() {
        m_updated();
    }


    /**
    * @brief refreshed - called when wallet refreshed by background thread or explicitly refreshed by calling "refresh" synchronously
    */
    void refreshed() {
        m_refreshed();
    }

    private:
        std::function<void(const std::string &txId, uint64_t amount)> m_moneySpent;
        std::function<void(const std::string &txId, uint64_t amount)> m_moneyReceived;
        std::function<void(const std::string &txId, uint64_t amount)> m_unconfirmedMoneyReceived;
        std::function<void(uint64_t height)> m_newBlock;
        std::function<void()> m_updated;
        std::function<void()> m_refreshed;
};
