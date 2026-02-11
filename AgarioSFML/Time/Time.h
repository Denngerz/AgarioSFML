#pragma once

namespace sf
{
    class Clock;
}

class Time {
public:
    static void init();
    
    static void destroy();
    
    static void update();
    
    static float getDeltaTime();
    
    static sf::Clock* clock;
    
    static float deltaTime;
};
