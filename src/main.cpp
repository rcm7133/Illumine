#include "pch.h"
#include "IllumineApplication.hpp"

int main()
{
    try {
        IllumineApplication app;
        app.Run();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}