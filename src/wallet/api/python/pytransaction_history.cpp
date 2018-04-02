#include "../wallet2_api.h"
#include <memory>
#include <pybind11/pybind11.h>

using namespace Monero;
namespace py = pybind11;

class PyTransactionHistory {
    public:
        int count() {
            return m_transaction_history->count();
        }

        std::shared_ptr<TransactionInfo> transaction(int index) {
            TransactionInfo * native_tx_info = m_transaction_history->transaction(index);
            std::shared_ptr<TransactionInfo> shared_tx_info (native_tx_info);
            return shared_tx_info;
        }

        std::shared_ptr<TransactionInfo> transactionById(const std::string &id) {
            TransactionInfo * native_tx_info = m_transaction_history->transaction(id);
            std::shared_ptr<TransactionInfo> shared_tx_info (native_tx_info);
            return shared_tx_info;
        }

        std::vector<std::shared_ptr<TransactionInfo>> getAll() {
            std::vector<TransactionInfo*> raw_txs_info = m_transaction_history->getAll();
            std::vector<std::shared_ptr<TransactionInfo>> shared_vector_txs_info(raw_txs_info.size());

            for (auto it = raw_txs_info.begin(); it!=raw_txs_info.end(); ++it) {
                std::shared_ptr<TransactionInfo> shared_tx_info(*it);
                shared_vector_txs_info.push_back(shared_tx_info);
            }

            return shared_vector_txs_info;
        }

        void refresh(){
            m_transaction_history->refresh();
        }

        void setSharedTransactionHistory(std::shared_ptr<TransactionHistory> tx_history) {
            m_transaction_history = tx_history;
        }

        std::shared_ptr<TransactionHistory> getNativeTransactionHistory() {
            return m_transaction_history;
        }

    private:
        std::shared_ptr<TransactionHistory> m_transaction_history = nullptr;
};
