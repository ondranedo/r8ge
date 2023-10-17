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
                           m_channels.at(command.m_channelIndex).m_gen,
                           m_channels.at(command.m_channelIndex).m_env);
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

    unsigned long chunklen = 0;
    short format;
    short nTracks;
    short tickdiv;
    long delay;
    unsigned char buff;
    unsigned long ticks;

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
    // byteswap because midi files are big endian ffs
    file.read(reinterpret_cast<char*>(&chunklen), 4);
    chunklen = std::byteswap(chunklen);
    if(chunklen >= 2){
        file.read(reinterpret_cast<char*>(&format), 2);
        format = std::byteswap(format);
    }
    if(chunklen >= 4){
        file.read(reinterpret_cast<char*>(&nTracks), 2);
        nTracks = std::byteswap(nTracks);
    }
    if(chunklen >= 6){
        file.read(reinterpret_cast<char*>(&tickdiv), 2);
        tickdiv = std::byteswap(tickdiv);
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
        enum State{
            READING_TIME = 0x10,
            READING_EVENT = 0x11,
            NOTE_OFF = 0x80,
            NOTE_ON = 0x90,
            POLYPHONIC_PRESSURE = 0xA0,
            CONTROLLER = 0xB0,
            PROGRAM_CHANGE = 0xC0,
            CHANNEL_PRESSURE = 0xD0,
            PITCH_BEND = 0xE0,
            SYSEX_MSG = 0xF0,
            ESCAPE_SEQUENCE = 0xF7,
            META_EVENT = 0xFF,
            META_SEQUENCE_NUM = 0x00,
            META_TEXT = 0x01,
            META_COPYRIGHT = 0x02,
            META_TRACK_NAME = 0x03,
            META_INSTRUMENT_NAME = 0x04,
            META_LYRIC = 0x05,
            META_MARKER = 0x06,
            META_CUE_POINT = 0x07,
            META_PROGRAM_NAME = 0x08,
            META_DEVICE_NAME = 0x09,
            META_MIDI_CHANNEL_PREFIX = 0x20,
            META_MIDI_PORT = 0x21,
            META_END_OF_TRACK = 0x2F,
            META_TEMPO = 0x51,
            META_SMPTE_OFFSET = 0x54,
            META_TIME_SIGNATURE = 0x58,
            META_KEY_SIGNATURE = 0x59,
            META_SEQ_SP_EVENT = 0x7F
        } state = READING_TIME;
        State previous = NOTE_OFF;
        ticks = 0;
        delay = 0;


        file.read(cStringBuff, 4);
        cmp = cStringBuff;
        if(cmp != "MTrk"){
            std::cout << "This file is broken" << std::endl;
            goto Exit;
        }

        file.read(reinterpret_cast<char*>(&chunklen), 4);
        chunklen = std::byteswap(chunklen);
        for(long j = 0; j < chunklen; j++){
            file.read(reinterpret_cast<char*>(&buff), 1);
            switch (state) {
                case READING_TIME:
                    delay += buff & 0x7F;
                    if(buff & 0x80){
                        delay = delay << 7;
                    }
                    else{
                        state = READING_EVENT;
                        ticks += delay;
                        delay = 0;
                    }
                    break;
                case READING_EVENT:
                    if(buff < 0x80){
                        state = previous;
                    }
                    else if(buff < 0xF0){
                        state = static_cast<State>(buff & 0xF0);
                        previous = state;
                    }
                    else{
                        state = static_cast<State>(buff);
                    }
                    break;
                case NOTE_OFF:
                    // todo
                    break;
                case NOTE_ON:
                    // todo
                    break;
                case POLYPHONIC_PRESSURE:
                    break;
                case CONTROLLER:
                    break;
                case PROGRAM_CHANGE:
                    // todo
                    break;
                case CHANNEL_PRESSURE:
                    break;
                case PITCH_BEND:
                    break;
                case SYSEX_MSG:
                    // don need yet
                    break;
                case ESCAPE_SEQUENCE:
                    // don need yet
                    break;
                case META_EVENT:
                    // todo
                    break;
                case META_COPYRIGHT:
                    // don need yet
                    break;
                case META_TRACK_NAME:
                    // todo
                    break;
                case META_INSTRUMENT_NAME:
                    // todo
                    break;
                case META_LYRIC:
                    break;
                case META_MARKER:
                    break;
                case META_CUE_POINT:
                    break;
                case META_PROGRAM_NAME:
                    break;
                case META_DEVICE_NAME:
                    break;
                case META_MIDI_CHANNEL_PREFIX:
                    break;
                case META_MIDI_PORT:
                    break;
                case META_END_OF_TRACK:
                    // todo
                    break;
                case META_TEMPO:
                    // todo
                    break;
                case META_SMPTE_OFFSET:
                    break;
                case META_TIME_SIGNATURE:
                    // todo
                    break;
                case META_KEY_SIGNATURE:
                    // todo
                    break;
                case META_SEQ_SP_EVENT:
                    break;
                case META_SEQUENCE_NUM:
                    break;
                case META_TEXT:
                    break;
            }
        }
    }

    Exit:
    delete[] cStringBuff;
    file.close();
}
