#pragma once

#include <string>

namespace calender
{
    class Database
    {
    public:
        Database(const Database &) = delete;
        Database &operator=(const Database &) = delete;

        static Database &instance();
        static void init();
        static void shutdown();

        void exec0(const std::string &query);
        void commit();

    private:
        Database();
        ~Database();
    };
}