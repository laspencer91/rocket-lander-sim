#include "physicalworld.h"

#include <iostream>
#include <ostream>
#include <raymath.h>
#include <cmath>

#include "renderables.h"

//   --------------
//     MARS WORLD
//   --------------

void MarsWorld::Render() {
    m_background->Render();

    for (const auto phyObject: m_physicalObjects) {
        phyObject->Render();
    }
}

void MarsWorld::Update(const float dt) {
    static int frame = 0;
    if (frame++ % 60 == 0) {
        std::cout << frame << std::endl;
    }

    for (const auto phyObject: m_physicalObjects) {
        // Apply Gravity
        Vector2 velocity = phyObject->GetVelocity();
        velocity += m_windVelocity;
        velocity.y += m_gravity * dt;
        phyObject->SetVelocity(velocity);

        // Modify objects' position
        Vector2 position = phyObject->GetPosition();
        position += velocity * dt;
        phyObject->SetPosition(position);

        // Apply angular velocity, and angular drag
        float anglularVelocity = phyObject->GetAngularVelocity();
        float rotation = phyObject->GetRotation();
        
        // Check for NaN values
        if (std::isnan(anglularVelocity)) {
            std::cout << "WARNING: Angular velocity is NaN in physical world update!" << std::endl;
            anglularVelocity = 0.0f;
        }
        
        if (std::isnan(rotation)) {
            std::cout << "WARNING: Rotation is NaN in physical world update!" << std::endl;
            rotation = 0.0f;
        }
        
        phyObject->SetRotation(rotation + anglularVelocity);
        
        // Calculate new angular velocity with drag
        float newAngularVelocity = anglularVelocity - (dt * m_angularDrag);
        
        // Check if the new angular velocity is NaN
        if (std::isnan(newAngularVelocity)) {
            std::cout << "WARNING: New angular velocity is NaN! angularVelocity: " << anglularVelocity 
                      << ", dt: " << dt << ", drag: " << m_angularDrag << std::endl;
            newAngularVelocity = 0.0f;
        }
        
        phyObject->SetAngularVelocity(newAngularVelocity);

        phyObject->Update(dt);
    }
}

// Set wind speed for Mars
void MarsWorld::SetWindVelocity(const Vector2 windVelocity) {
    m_windVelocity = windVelocity;
}

