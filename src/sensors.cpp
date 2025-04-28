#include "sensors.h"
#include <iostream>
#include <cmath>
#include "iphysicalobject.h"

void AttitudeSensor::Update(float dt) {
    float rotation = m_ship->GetRotation();
    m_value = rotation;
}

float AttitudeSensor::Read() {
    return m_value;
}