#ifndef GUIDANCESYSTEM_H
#define GUIDANCESYSTEM_H
#include <vector>

#include "iupdateable.h"
#include "sensors.h"
#include "ipid.h"
#include "thruster.h"


class GuidanceSystem final : public IUpdateable {
public:
    explicit GuidanceSystem(SpaceShip* ship) :
    m_ship(ship),
    m_attitudeSensor(new AttitudeSensor(ship)),
    m_attitudePID(new AttitudeAdjustmentPID(0.9f, 0.0002f, 0.1f)) {}

    ~GuidanceSystem() override {
        delete m_attitudeSensor;
        delete m_attitudePID;
    }

    void Update(float dt) override;
    void SetTargetAttitude(const float targetAttitude) { m_targetAttitude = targetAttitude; }
    void RegisterThruster(ISignalReceiver* thruster) { m_thrusters.push_back(thruster); }

    [[nodiscard]] float GetTargetAttitude() const { return m_targetAttitude; }

private:
    SpaceShip* m_ship;
    AttitudeSensor* m_attitudeSensor;
    AttitudeAdjustmentPID* m_attitudePID;
    std::vector<ISignalReceiver *> m_thrusters;     // Guidance system only interacts with Signal portion of a thruster.

    float m_targetAttitude = 0.0f;
};



#endif //GUIDANCESYSTEM_H
