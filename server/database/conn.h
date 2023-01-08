#include "rocksdb/db.h"

namespace db
{
    class DBConn
    {

    private:
        rocksdb::DB *db;
    };
}