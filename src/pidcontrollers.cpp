#include "ipid.h"
#include "raymath.h"
#include <iostream>
#include <cmath>
#include <bits/stl_algo.h>

float AttitudeAdjustmentPID::Process(const float dt, const float input, const float goal) {
    if (std::isnan(input)) {
        std::cout << "WARNING: PID received NaN input value!" << std::endl;
        return 0.0f;
    }

    if (dt < 0.0001f) {
        std::cout << "WARNING: dt is too small in PID controller: " << dt << std::endl;
        return 0.0f;
    }
    
    float error = goal - input;
    while (error < -180) { error += 360; }
    while (error > 180) { error -= 360; }

    m_p = error * dt * m_kp;

    m_d = ((error - m_previousError) * dt) * m_kd;
    m_previousError = error;

    m_i += error * m_ki * dt;
    
    if (std::isnan(m_p)) std::cout << "WARNING: P term is NaN! error: " << error << ", dt: " << dt << ", kp: " << m_kp << std::endl;
    if (std::isnan(m_i)) std::cout << "WARNING: I term is NaN! error: " << error << ", dt: " << dt << ", ki: " << m_ki << std::endl;
    if (std::isnan(m_d)) std::cout << "WARNING: D term is NaN! error: " << error << ", prev: " << m_previousError << ", dt: " << dt << ", kd: " << m_kd << std::endl;
    
    float result = m_p + m_i + m_d;
    if (std::isnan(result)) {
        std::cout << "WARNING: PID result is NaN! P=" << m_p << ", I=" << m_i << ", D=" << m_d << std::endl;
        return 0.0f;
    }
    
    return std::clamp(result, -1.0f, 1.0f);
}
