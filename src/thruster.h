#ifndef THRUSTER_H
#define THRUSTER_H

#include <raylib.h>


struct IShipComponent {
    Vector2 m_relativePosition;

    explicit IShipComponent(const Vector2 relativePosition): m_relativePosition(relativePosition) {}
    virtual ~IShipComponent() = default;

    [[nodiscard]] Vector2 GetRelativePosition() const { return m_relativePosition; }
};


struct ISignalReceiver {
    virtual ~ISignalReceiver() = default;
    virtual void SendActivationSignal(float signalStrengthPct) = 0;

protected:
    float m_signalStrength = 0.0f;
};


class Thruster final : public IShipComponent, public ISignalReceiver {
    float m_maxThrust = 10.0f;

public:
    explicit Thruster(const Vector2 relativePosition): IShipComponent(relativePosition) {};

    void SendActivationSignal(float signalStrengthPct) override;
};


#endif //THRUSTER_H
