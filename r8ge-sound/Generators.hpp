//
// Created by Wiszc on 02.10.2023.
//

#ifndef R8GE_GENERATORS_HPP
#define R8GE_GENERATORS_HPP

#include <vector>
#include <cmath>

// this will be refactored a lot and I will curse myself

namespace r8ge{
    class Sound{
    public:
        virtual double generate(double timeSecs, unsigned char channel) = 0;
        ~Sound();
        void setVolumes(double left, double right);
        void setEndTime(double mEndTime);
        [[nodiscard]] double getEndTime() const;
    protected:
        double m_left = 1.0;
        double m_right = 1.0;
        double m_startTime = 0.0;
        double m_endTime = 9999999.0;
    };

    class Note : public Sound{
    public:
        // converts frequency to angular velocity
        double generate(double timeSecs, unsigned char channel) override;
        ~Note();

        void setGenerator(double (*m_generator)(double));
        void setFrequency(double freq);

    private:
        double (*m_generator)(double) = &std::sin;
        double m_frequency = 440.0;
    };
// 1 is a0, 40 is c4 and so on
    double toneToFrequency(short note);

    double square(double time);
}

#endif //R8GE_GENERATORS_HPP
