//
// Created by Wiszc on 11.10.2023.
//

#include "Sequencer.hpp"

void r8ge::SimpleSequencer::createAll() {
    r8ge::Note* noteptr;
    for(auto& command : m_commands){
        noteptr = new Note(m_sixteenthBeatSecs * command.m_sixteenthBeatStart,
                           command.m_tone,
                           m_generators.at(command.m_genIndex),
                           m_envelopes.at(command.m_envelopeIndex));
        noteptr->setEndTime(m_sixteenthBeatSecs * (command.m_sixteenthBeatStart + command.m_sixteenthBeatCount));
        m_pusher->addSound(noteptr);
    }
}

void r8ge::SimpleSequencer::setBPM(double bpm) {
    m_bpm = bpm;
    m_sixteenthBeatSecs = 1 / bpm / 16;
}
