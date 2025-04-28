#include "iphysicalobject.h"
#include <iostream>
#include <cmath>

SpaceShip::SpaceShip(const Vector2 &position, const float rotation, const float mass):
    IPhysicalObject(position, rotation, mass),
    m_sprite(LoadTexture("../resources/sprites/spaceship.png")),
    m_srcRect(Rectangle ( 0, 0, m_sprite.width, m_sprite.height )) {

    auto scaledWidth = m_sprite.width * m_scale;
    auto scaledHeight = m_sprite.height * m_scale;

    // Rendering stuff
    m_destRect = Rectangle ( m_position.x, m_position.y, scaledWidth, scaledHeight);
    m_localCenter = Vector2(scaledWidth, scaledHeight) * 0.5f;

    // Building the ship...
    auto leftThruster = new Thruster(Vector2(scaledWidth * 0.47, scaledHeight * 0.48));
    auto rightThruster = new Thruster(Vector2(scaledWidth * -0.47, scaledHeight * 0.48));
    auto centerThruster = new Thruster(Vector2(0, scaledHeight * 0.48));
    // Allow ship to maintain references to the thrusters for rendering and because the physical portion of
    // the thrusters belong to the physical ship. Because of this the ship is also responsible for the memory
    // management of the thrusters (as opposed to the guidance system).
    m_thrusters.push_back(leftThruster);
    m_thrusters.push_back(rightThruster);
    m_thrusters.push_back(centerThruster);

    // Initialize electronics
    m_gcs = new GuidanceSystem(this);
    m_gcs->RegisterThruster(leftThruster);
    m_gcs->RegisterThruster(rightThruster);
    m_gcs->RegisterThruster(centerThruster);
}

void SpaceShip::Update(float dt) {
    m_gcs->Update(dt);

    m_rotation += m_angularVelocity * dt;
    
    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, dt));
}

void SpaceShip::Render() {
    // Draw Ship
    m_destRect.x = m_position.x;
    m_destRect.y = m_position.y;
    DrawTexturePro(m_sprite, m_srcRect, m_destRect, m_localCenter, m_rotation, WHITE);
    DrawCircle(m_position.x, m_position.y, 2, DARKBLUE); // Visualize Center

    // Draw Thrusters
    for (const auto thruster : m_thrusters) {
        const Vector2 thrustWorldPos = m_position + Vector2Rotate(thruster->GetRelativePosition(), m_rotation * DEG2RAD);
        DrawCircle(thrustWorldPos.x, thrustWorldPos.y, 5, RED);
    }

    // Draw Debug Text
    DrawText(TextFormat("Angle: %.8f", m_rotation), 10, 100, 20, BLUE);
}
