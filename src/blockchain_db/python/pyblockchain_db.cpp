#include "../lmdb/db_lmdb.cpp"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using namespace cryptonote;

class PyBlockchainDb : BlockchainLMDB {
public:
    PyBlockchainDb() {
        BlockchainLMDB * db = new BlockchainLMDB();
        std::shared_ptr<BlockchainLMDB> shared_native_blockchain_db (db);
        m_db = shared_native_blockchain_db;
    }

    uint64_t height() {
        return m_db->height();
    }

    void sync() {
        m_db->sync();
    }

private:
    std::shared_ptr<BlockchainLMDB> m_db;
};
