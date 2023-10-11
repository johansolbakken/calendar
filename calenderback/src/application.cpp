#include "application.h"

#include <knekt.h>
#include <iostream>

#include "db.h"
#include "config.h"

#include <nlohmann/json.hpp>

#include <thread>

namespace calender
{
    void read_db_env(DatabaseSpecification &sped)
    {
        const char* env_host = std::getenv("DB_HOST");
        if (env_host) sped.host = std::string(env_host);

        const char* env_port = std::getenv("DB_PORT");
        if (env_port) sped.port = std::stoi(env_port);

        const char* env_dbname = std::getenv("DB_NAME");
        if (env_dbname) sped.dbname = std::string(env_dbname);

        const char* env_user = std::getenv("DB_USER");
        if (env_user) sped.user = std::string(env_user);

        const char* env_password = std::getenv("DB_PASSWORD");
        if (env_password) sped.password = std::string(env_password);
    }

    Application::Application()
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));

        DatabaseSpecification dbSpec;
        dbSpec.host = "127.0.0.1";
        dbSpec.port = 5432;
        dbSpec.dbname = "calender";
        dbSpec.user = "postgres";
        dbSpec.password = "postgres";
        read_db_env(dbSpec);

        Database::init(dbSpec);
    }

    Application::~Application()
    {
        Database::shutdown();
    }

    void Application::run()
    {
        Knekt::ServerSpecification serverSpec;
        serverSpec.port = 8085;

        // Database::instance().exec("CREATE TABLE IF NOT EXISTS test (id SERIAL PRIMARY KEY, name VARCHAR(255))");

        Knekt::Server server(serverSpec);
        server.get("/", [](Knekt::Request req)
                   { return Knekt::Response{Knekt::StatusCode::Ok, "Hello, World"}; });

        server.get("/add", [](Knekt::Request req)
                   {
            Database::instance().exec0("INSERT INTO test (name) VALUES ('test')");
            return Knekt::Response{Knekt::StatusCode::Ok, "Add"}; });

        server.get("/joke", [](Knekt::Request req)
                   {
            std::string joke;

            Knekt::Client::get("https://sv443.net/jokeapi/v2/joke/any", [&joke](Knekt::Response response){
                nlohmann::json json = nlohmann::json::parse(response.body);
                if (json["type"] == "single")
                {
                    joke = json["joke"];
                }
                else
                {
                    joke = json["setup"];
                    joke += "\n";
                    joke += json["delivery"];
                }
            });

            return Knekt::Response{Knekt::StatusCode::Ok, joke}; });

        std::cout << "Server running on port " << serverSpec.port << std::endl;

        while (true)
        {
            server.update();
        }
    }
}