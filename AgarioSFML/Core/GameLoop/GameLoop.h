#pragma once
#include <chrono>
#include <memory>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

class ObjectFactory;
class Time;
class Object;
class Factory;

template<class T>
class IterratableSet
{
public:
    using Ptr = std::shared_ptr<T>;
    using Container = std::vector<Ptr>;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    bool add(const Ptr& item)
    {
        if (!item)
        {
            return false;
        }
        
        if (contains(item))
        {
            return false;
        }
        
        items.emplace_back(item);
        return true;
    }

    bool remove(const Ptr& item)
    {
        if (!item)
        {
            return false;
        }

        auto foundObject = std::find(items.begin(), items.end(), item);

        if (foundObject == items.end())
        {
            return false;
        }
        
        *foundObject = items.back();
        items.pop_back();
        
        return true;
    }

    template<class Predicate>
    void clearIf(Predicate predicate)
    {
        size_t currentIndex = 0;

        while (currentIndex < items.size())
        {
            if (predicate(items[currentIndex]))
            {
                items[currentIndex] = items.back();
                items.pop_back();
            }
            else
            {
                ++currentIndex;
            }
        }
    }

    bool contains(const Ptr& item) const
    {
        if (!item)
        {
            return false;
        }
        
        return std::find(items.begin(), items.end(), item) != items.end();
    }

    void clear() { items.clear(); }

    iterator begin() { return items.begin(); }
    
    iterator end() { return items.end(); }
    
    const_iterator begin() const { return items.begin(); }
    
    const_iterator end() const { return items.end(); }

private:
    Container items;
};

class GameLoop : public std::enable_shared_from_this<GameLoop>
{
public:
    virtual ~GameLoop() = default;

    GameLoop(unsigned int windowWidth, unsigned int windowHeight, std::string windowTitle);

    void runLoop();
    
    void addObject(const std::shared_ptr<Object>& obj);
    
    void removeObject(const std::shared_ptr<Object>& obj);

    std::weak_ptr<sf::RenderWindow> getWindow() const;
    
    std::shared_ptr<ObjectFactory> getFactory() const;

    sf::Event& getCurrentInput();

    void initialize();

private:
    std::shared_ptr<Time> time;
    
    IterratableSet<sf::Shape> drawableShapes;
    
    IterratableSet<Object> tickableObjects;

    std::shared_ptr<sf::RenderWindow> window;

    std::shared_ptr<ObjectFactory> objectFactory;

    sf::Event currentInputEvent;

    void updateWindow() const;

    virtual void generate();
    
    virtual void getInput();
    
    virtual void logic();

    void draw() const;
    
    bool isEndGame() const;

    void updateObjects();

    void updateObjectsCollision();

    void cleanupInactiveObjects();
};