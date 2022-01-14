#include "./Interp.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    Example::Interp interp(std::cin, std::cout, std::cerr);
    if (argc > 1)
        interp.eval(argv[1]);
    else
        interp.help();
    return interp.loop();
}
