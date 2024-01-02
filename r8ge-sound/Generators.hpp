//
// Created by Wiszc on 02.10.2023.
//

#ifndef R8GE_GENERATORS_HPP
#define R8GE_GENERATORS_HPP

#include <vector>
#include <string>
#include <r8ge/r8ge.h>
#include "Instruments.h"

// this will be refactored a lot and I will curse myself

namespace r8ge{

    class Sound{
    public:
        explicit Sound(double startTime);
        virtual double generate(double timeSecs, unsigned char channel) = 0;
        virtual ~Sound() = default;
        void setVolumes(double left, double right);
        void setEndTime(double endTime);
        void setState(bool state);
        [[nodiscard]] bool getState() const;
        [[nodiscard]] int getID() const;
        void setID(int ID);
    protected:
        double m_left = 1.0;
        double m_right = 1.0;
        double m_startTime;
        double m_endTime = std::numeric_limits<double>::infinity();
        bool m_isActive;
        int m_id = -1;
    };

    class Note : public Sound{
    public:
        explicit Note(double startTime, short tone = 49, double (*generator)(double) = &std::sin, Envelope envelope = {});
        // converts frequency to angular velocity
        double generate(double timeSecs, unsigned char channel) override;
        ~Note() override;

    private:
        double (*m_generator)(double);
        double m_frequency;
        Envelope m_envelope;
    };
// 1 is a0, 40 is c4 and so on
    double toneToFrequency(short tone);

    double square(double time);
    double saw(double time);

    class Wave : public Sound{
    public:
        Wave(double startTime, const std::string& filename);
        double generate(double timeSecs, unsigned char channel) override;
        ~Wave() override;

        double getDuration();
    private:
        WaveData m_data;
    };

}

#endif //R8GE_GENERATORS_HPP
