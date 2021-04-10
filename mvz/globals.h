#pragma once

#include <string>
#include <map>

class Globals {

public:
    std::string currentScene;
    double time = 0.0;
    double deltaTime = 0.0;
    int windowWidth = 1280;
    int windowHeight = 720;

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


