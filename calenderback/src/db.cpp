#include "db.h"

#include <pqxx/pqxx>

#include <sstream>

namespace calender
{
    static Database *s_instance = nullptr;

    Database &Database::instance()
    {
        return *s_instance;
    }

    void Database::init(const DatabaseSpecification &spec)
    {
        s_instance = new Database(spec);
    }

    void Database::shutdown()
    {
        delete s_instance;
    }

    static pqxx::connection *s_connection = nullptr;

    Database::Database(const DatabaseSpecification &spec)
        : m_spec(spec)
    {
        std::stringstream builder;
        builder << "postgres://" << m_spec.user << ":" << m_spec.password << "@" << m_spec.host << ":" << m_spec.port << "/"
                << m_spec.dbname;
        s_connection = new pqxx::connection(builder.str());
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