#include "thruster.h"

void Thruster::SendActivationSignal(float signalStrengthPct) {
    if (signalStrengthPct > 1.0f) {
        signalStrengthPct = 1.0f;
    } else if (signalStrengthPct < 0.0f) {
        signalStrengthPct = 0.0f;
    }

    m_signalStrength = signalStrengthPct;
}
