#include <iostream>

#include <knekt.h>

int main() {
    Knekt::ServerSpecification serverSpec;
    serverSpec.port = 8080;

    Knekt::Server server(serverSpec);
    server.get("/", [](Knekt::Request req) {
        return Knekt::Response { Knekt::StatusCode::Ok, "Hello, World"};
    });

    while (true) {
        server.update();
    }

    return 0;
}