#ifndef SENSORS_H
#define SENSORS_H
#include "isensor.h"


class AttitudeSensor final : public ISensor<float> {
public:
    explicit AttitudeSensor(const SpaceShip* ship)
        : ISensor(ship, 0) {
    }

    void Update(float dt) override;

    float Read() override;
};



#endif //SENSORS_H
