#pragma once

namespace sf
{
    class Clock;
}

class Time {
public:
    Time();
    ~Time();
    
    void init();
    
    void destroy();
    
    void update();
    
    float getDeltaTime();
    
    sf::Clock* clock;
    
    float deltaTime;
};
