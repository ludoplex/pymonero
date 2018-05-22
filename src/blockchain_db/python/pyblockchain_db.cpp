#include "../lmdb/db_lmdb.cpp"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using namespace cryptonote;

class PyBlockchainDb : public BlockchainLMDB {
public:
    PyBlockchainDb() {
        // BlockchainLMDB * db = new BlockchainLMDB();
        // std::shared_ptr<BlockchainLMDB> shared_native_blockchain_db (db);
        // m_db = shared_native_blockchain_db;
    }

    // uint64_t get_block_height(const std::string hash) {
    //     crypto::hash h = crypto::cn_fast_hash(hash.data(), hash.length());
    //     return BlockchainLMDB::get_block_height(h);
    // }

private:
    //std::shared_ptr<BlockchainLMDB> m_db;
};
