#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "guidancesystem.h"
#include "irenderable.h"
#include "iupdateable.h"
#include "thruster.h"

class GuidanceSystem;

class IPhysicalObject : public IUpdateable, public IRenderable {
public:
    IPhysicalObject(const Vector2 position, const float rotation, const float mass):
        m_velocity({0, 0}), m_position(position), m_rotation(rotation), m_mass(mass) {}

    void Update(float dt) override = 0;
    void Render() override = 0;

    [[nodiscard]] float GetMass() const { return m_mass; }
    [[nodiscard]] float GetRotation() const { return m_rotation; }
    [[nodiscard]] float GetAngularVelocity() const { return m_angularVelocity; };
    [[nodiscard]] Vector2 GetVelocity() const { return m_velocity; }
    [[nodiscard]] Vector2 GetPosition() const { return m_position; }

    void SetVelocity(const Vector2 velocity) { m_velocity = velocity; }

    void SetPosition(const Vector2 position) { m_position = position; }

    void SetRotation(const float rotation) { m_rotation = rotation; }

    void SetAngularVelocity(const float angularVelocity) { m_angularVelocity = angularVelocity; }

protected:
    Vector2 m_velocity;
    Vector2 m_position;
    float m_rotation;
    float m_angularVelocity;
    float m_mass;
};

/**
 * SPACESHIP
**/
class SpaceShip final : public IPhysicalObject {
public:
    SpaceShip(const Vector2 &position, float rotation, float mass);
    ~SpaceShip() override {
        for (auto thruster : m_thrusters) {
            delete thruster;
            thruster = nullptr;
        }

        delete m_gcs;
    };

    void Update(float dt) override;
    void Render() override;

private:
    Texture2D m_sprite;         // The image to be drawn
    Rectangle m_srcRect;        // The bounds that define the source
    Rectangle m_destRect;       // The bounds that define the destination
    Vector2 m_localCenter;      // The local center point
    float m_scale = 0.1f;       // The scale of the image

    GuidanceSystem *m_gcs;

    std::vector<IShipComponent *> m_thrusters; // Only interacts with physical portion of the thrusters.
};


#endif //PHYSICALOBJECT_H
