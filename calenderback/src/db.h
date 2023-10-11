#pragma once

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

    private:
        Database();
        ~Database();
    };
}