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
    static pqxx::work *s_work = nullptr;

    Database::Database()
    {
        // Initialize the connection
        s_connection = new pqxx::connection("hostaddr=127.0.0.1 port=5432 dbname=calender user=postgres password=postgres");
        s_work = new pqxx::work(*s_connection);
    }

    Database::~Database()
    {
        delete s_work;
        delete s_connection;
    }

}