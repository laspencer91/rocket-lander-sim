#ifndef PHYSICALWORLD_H
#define PHYSICALWORLD_H
#include <vector>
#include <random>

#include "iphysicalobject.h"
#include "irenderable.h"
#include "iupdateable.h"
#include "renderables.h"

/**
 * The idea of the Physical World is that it encapsulates physical objects and applies forces (gravity, wind, and other
 * environmental factors) to those physical objects. It is also responsible for Rendering the objects that live in it.
 * The system / class that creates and manages a physical world is essentially God, or in this case, a much more boring
 * name, "application", the creator of the world, and the one responsible for creating / destroying the objects that live
 * in it.
 */
class IPhysicalWorld: public IRenderable, public IUpdateable {
public:
    IPhysicalWorld(const float gravity, const Vector2 windVelocity, const float atmosphericPressure) :
        m_gravity(gravity), m_windVelocity(windVelocity), m_atmoshpericPressure(atmosphericPressure) {}

    virtual void SetWindVelocity(Vector2 windVelocity) = 0;
protected:
    Vector2 m_windVelocity;
    float m_gravity;
    float m_atmoshpericPressure;
    float m_angularDrag = 3.0f;
};

/**
 * Mars, the physical world.
 */
class MarsWorld final : public IPhysicalWorld {
public:
    MarsWorld() : IPhysicalWorld(3.73, Vector2(0, 0), 132) {
        m_background = new MarsSceneGraphics();
        auto* ship = new SpaceShip(Vector2(200, 0), GetRandomValue(0, 360), 10);
        m_physicalObjects.push_back(ship);
    }
    void Render() override;
    void Update(float dt) override;
private:
    void SetWindVelocity(Vector2 windVelocity) override;
    IRenderable* m_background;
    std::vector<IPhysicalObject*> m_physicalObjects = std::vector<IPhysicalObject*>();
};



#endif //PHYSICALWORLD_H
