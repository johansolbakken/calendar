#pragma once

#include <string>

namespace calender
{
    struct DatabaseSpecification
    {
        std::string host;
        uint32_t port;
        std::string dbname;
        std::string user;
        std::string password;
    };

    class Database
    {
    public:
        Database(const Database &) = delete;
        Database &operator=(const Database &) = delete;

        static Database &instance();
        static void init(const DatabaseSpecification &spec);
        static void shutdown();

        void exec0(const std::string &query);
        void commit();

    private:
        Database(const DatabaseSpecification &spec);
        ~Database();

    private:
        DatabaseSpecification m_spec;
    };
}