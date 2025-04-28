#ifndef ISENSOR_H
#define ISENSOR_H
#include "iupdateable.h"

class SpaceShip;

template <typename T>
class ISensor: public IUpdateable {

protected:
    T m_value;
    const SpaceShip* m_ship;

public:
    ISensor(const SpaceShip* ship, T value) : m_value(value), m_ship(ship) {}

    virtual T Read() {
        return m_value;
    }
};

#endif //ISENSOR_H
