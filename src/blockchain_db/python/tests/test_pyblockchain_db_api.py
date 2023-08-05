import unittest
import pyblockchain_db_api

class TestPyBlockchainDB(unittest.TestCase):

    def test_create_db_object(self):
        db = pyblockchain_db_api.PyBlockchainDb()
        self.assertNotEqual(db, None)

    def test_open_db(self):
        db = pyblockchain_db_api.PyBlockchainDb()
        db.open("~/.bitmonero/lmdb", 0)
        self.assertTrue(db.is_open())

    def test_get_a_block_hash_in_str(self):
        db = pyblockchain_db_api.PyBlockchainDb()
        db.open("~/.bitmonero/lmdb", 0)
        h = db.top_block_hash()

        print(f" printing hash :{h.data()}")
        self.assertTrue(isinstance(h.data(), str))

if __name__ == '__main__':
    unittest.main()
