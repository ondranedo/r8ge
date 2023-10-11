//
// Created by Wiszc on 11.10.2023.
//

#ifndef R8GE_SEQUENCER_HPP
#define R8GE_SEQUENCER_HPP

#include <vector>
#include "Sound.hpp"

namespace r8ge{
    struct Command{
        short m_tone;
        long m_sixteenthBeatStart;
        long m_sixteenthBeatCount;
        short m_genIndex;
        short m_envelopeIndex;
    };
    class SimpleSequencer{
    public:
        void createAll();
        void loadMIDI();
        void setBPM(double bpm);
    private:
        double m_bpm;
        double m_sixteenthBeatSecs;
        std::vector<Command> m_commands;
        std::vector<double(*)(double)> m_generators;
        std::vector<Envelope> m_envelopes;

        AudioPusher* m_pusher;
    };
}

#endif //R8GE_SEQUENCER_HPP
