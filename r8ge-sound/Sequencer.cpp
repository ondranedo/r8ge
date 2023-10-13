//
// Created by Wiszc on 11.10.2023.
//

#include "Sequencer.hpp"
#include <fstream>
#include <iostream>

void r8ge::MIDISequencer::createAll() {
    r8ge::Note* noteptr;
    for(auto& command : m_commands){
        noteptr = new Note(m_tickSecs * command.m_tickStart,
                           command.m_tone,
                           m_generators.at(command.m_genIndex),
                           m_envelopes.at(command.m_envelopeIndex));
        noteptr->setEndTime(m_tickSecs * command.m_tickEnd);
        m_pusher->addSound(noteptr);
    }
}

void r8ge::MIDISequencer::setBPM(double bpm) {
    m_bpm = bpm;
    m_tickSecs = 1 / bpm / 16;
}

void r8ge::MIDISequencer::loadMIDI(const std::string& filename) {
    char* cStringBuff = new char[5];
    cStringBuff[4] = '\0';
    std::string cmp;

    long chunklen;
    short format;
    short nTracks;
    short tickdiv;
    long delay;
    char buff;
    long long ticks;

    std::ifstream file(filename, std::ios::binary);
    if(!file.is_open()){
        std::cout << "File not found" << std::endl;
        goto Exit;
    }

    file.read(cStringBuff, 4);
    cmp = cStringBuff;
    if(cmp != "MThd"){
        std::cout << "Can't read this file" << std::endl;
        goto Exit;
    }
// the following chunklen checks are unnecessary but might serve for debugging purposes
    file.read(reinterpret_cast<char*>(&chunklen), 4);
    if(chunklen >= 2){
        file.read(reinterpret_cast<char*>(&format), 2);
    }
    if(chunklen >= 4){
        file.read(reinterpret_cast<char*>(&nTracks), 2);
    }
    if(chunklen >= 6){
        file.read(reinterpret_cast<char*>(&tickdiv), 2);
    }

    if(format == 0 && nTracks > 1){
        std::cout << "This file is broken" << std::endl;
        goto Exit;
    }
    if(tickdiv & (1 << 15)){
        m_tickSecs = 1.0 / ((~tickdiv >> 8) + 1);
        m_tickSecs /= tickdiv & 0xFF;
    }

    for(int i = 0; i < nTracks; i++){
        bool runningStatus = false;
        ticks = 0;
        file.read(cStringBuff, 4);
        cmp = cStringBuff;
        if(cmp != "MTrk"){
            std::cout << "This file is broken" << std::endl;
            goto Exit;
        }

        file.read(reinterpret_cast<char*>(&chunklen), 4);
        for(long j = 0; j < chunklen;){
            //get the delay between events
            delay = 0;
            int b = 0;
            do{
                delay = delay << 7;
                file.read(&buff, 1);
                delay += buff & ~(1 << 7);
                b++;
            }while(buff & (1 << 7) && b != 4);
            j += b;
            ticks += delay;

            // process the event;
            file.read(&buff, 1);
        }
    }

    Exit:
    delete[] cStringBuff;
    file.close();
}
