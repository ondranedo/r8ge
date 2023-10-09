//
// Created by Wiszc on 02.10.2023.
//

#ifndef R8GE_GENERATORS_HPP
#define R8GE_GENERATORS_HPP

#include <vector>
#include <cmath>
#include <string>

// this will be refactored a lot and I will curse myself

namespace r8ge{

    struct Envelope{
        double m_attackTime = 0.1;
        double m_decayTime = 0.1;
        double m_releaseTime = 0.2;

        double m_sustainVolume = 0.9;
        double m_maxVolume = 1.1;
    };

    class Sound{
    public:
        explicit Sound(double startTime);
        virtual double generate(double timeSecs, unsigned char channel) = 0;
        virtual ~Sound() = default;
        void setVolumes(double left, double right);
        void setEndTime(double endTime);
        void setState(bool state);
        [[nodiscard]] bool getState() const;
    protected:
        double m_left = 1.0;
        double m_right = 1.0;
        double m_startTime;
        double m_endTime = 999999.0;
        bool m_isActive;
    };

    class Note : public Sound{
    public:
        explicit Note(double startTime, double frequency = 440.0, double (*generator)(double) = &std::sin, Envelope envelope = {});
        // converts frequency to angular velocity
        double generate(double timeSecs, unsigned char channel) override;
        ~Note() override;

    private:
        double (*m_generator)(double);
        double m_frequency;
        Envelope m_envelope;
    };
// 1 is a0, 40 is c4 and so on
    double toneToFrequency(short note);

    double square(double time);

    class Wave : public Sound{
    public:
        Wave(double startTime, const std::string& filename);
        double generate(double timeSecs, unsigned char channel) override;
        ~Wave() override;

        double getDuration();
    private:
        unsigned short m_format{};
        unsigned short m_channels{};
        unsigned long m_sampleRate{};
        unsigned short m_blockAlign{};
        double m_timeStep;

        unsigned long m_sampleCount;
        char* m_data = nullptr; // takes up to megabytes but allows for instant skipping
    };

}

#endif //R8GE_GENERATORS_HPP
