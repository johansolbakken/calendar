#include "db.h"

#include <pqxx/pqxx>

namespace calender
{
    static Database *s_instance = nullptr;

    Database &Database::instance()
    {
        return *s_instance;
    }

    void Database::init()
    {
        s_instance = new Database();
    }

    void Database::shutdown()
    {
        delete s_instance;
    }

    static pqxx::connection *s_connection = nullptr;

    Database::Database()
    {
        // Initialize the connection
        s_connection = new pqxx::connection("hostaddr=127.0.0.1 port=5432 dbname=calender user=postgres password=postgres");
    }

    Database::~Database()
    {
        delete s_connection;
    }

    void Database::exec0(const std::string &query)
    {
        pqxx::work txn(*s_connection);
        txn.exec0(query);
        txn.commit();
    }
}