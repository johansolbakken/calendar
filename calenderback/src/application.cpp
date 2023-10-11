#include "application.h"

#include <knekt.h>
#include <iostream>

#include "db.h"

namespace calender
{
    Application::Application()
    {
        Database::init();
    }

    Application::~Application()
    {
        Database::shutdown();
    }

    void Application::run()
    {
        Knekt::ServerSpecification serverSpec;
        serverSpec.port = 8085;

        //Database::instance().exec("CREATE TABLE IF NOT EXISTS test (id SERIAL PRIMARY KEY, name VARCHAR(255))");

        Knekt::Server server(serverSpec);
        server.get("/", [](Knekt::Request req) { 
            return Knekt::Response{Knekt::StatusCode::Ok, "Hello, World"}; 
        });

        server.get("/add", [](Knekt::Request req) {
            Database::instance().exec0("INSERT INTO test (name) VALUES ('test')");
            return Knekt::Response{Knekt::StatusCode::Ok, "Add"};
        });
 
        std::cout << "Server running on port " << serverSpec.port << std::endl;

        while (true)
        {
            server.update();
        }
    }
}