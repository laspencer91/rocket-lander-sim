#ifndef IPID_H
#define IPID_H

template <typename OutT, typename InT>
class IPID {
protected:
    InT m_p, m_i, m_d;
    InT m_kp, m_ki, m_kd;
    InT m_previousError;

public:
    IPID(InT kp, InT ki, InT kd) {
        m_kp = kp;
        m_ki = ki;
        m_kd = kd;
        m_p = 0;
        m_i = 0;
        m_d = 0;
        m_previousError = 0;
    }

    virtual ~IPID() = default;

    virtual OutT Process(float dt, InT input, InT goal) = 0;
};

class AttitudeAdjustmentPID final : public IPID<float, float> {
public:
    AttitudeAdjustmentPID(const float kp, const float ki, const float kd)
        : IPID(kp, ki, kd) {
    }

    float Process(float dt, float input, float goal) override;
};


#endif //IPID_H
