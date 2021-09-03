#include <iostream>

#include "Application.h"

int main() {
    Application* app = new Application();

    try {
        app->Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    delete app;

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