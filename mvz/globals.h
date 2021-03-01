#pragma once

#include <string>

class Globals {

public:
    std::string currentScene;
    double time = 0.0;

public:
    Globals() = default;
    Globals(const Globals&) = delete;
    Globals(Globals&&) = delete;

    static Globals& Instance() {
        static Globals globals;
        return globals;
    }
};

namespace {
    Globals& globals = Globals::Instance();
}


