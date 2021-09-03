#include <iostream>

#include "Application.h"

int main() {
    Application app;

    try {
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// #include "HelloWorld.h"

// int main() {
//  HelloWorld world = HelloWorld();
//  world.say();
//  std::string uwu;
//  std::cin >> uwu;
//  return 0;
// }