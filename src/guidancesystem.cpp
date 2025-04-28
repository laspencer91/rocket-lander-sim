#include "guidancesystem.h"

#include <iostream>
#include <ostream>
#include <cmath>

#include "iphysicalobject.h"

void GuidanceSystem::Update(float dt) {
    // I think that the guidance system should invoke the thrusters, and the thrusters should apply a force
    // in the world at a position. The applied force would then impact the ship.
    // In a real world scenario the guidance system would not tell the ship to rotate.
    //
    // Maybe I could have something like:
    //
    // IWorld::CurrentActive()->ApplyForceAtPosition(Vector2 position, Vector2 forceVector);

    m_attitudeSensor->Update(dt);
    float sensorReading = m_attitudeSensor->Read();
    
    if (std::isnan(sensorReading)) {
        std::cout << "WARN: Sensor reading is NaN! Skipping PID update." << std::endl;
        return;
    }
    
    const float attitudeAdjustment = m_attitudePID->Process(dt, sensorReading, 0);
    
    if (std::isnan(attitudeAdjustment)) {
        std::cout << "WARN: Attitude adjustment is NaN!" << std::endl;
        return; // Skip applying NaN values
    }

    // Calculate the final angular velocity to apply
    float newAngularVelocity = attitudeAdjustment;
    
    m_ship->SetAngularVelocity(newAngularVelocity);
}
