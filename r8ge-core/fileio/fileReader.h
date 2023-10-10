#ifndef R8GE_FILEREADER_H
#define R8GE_FILEREADER_H

namespace r8ge {
    class fileReader {
    public:
        virtual ~fileReader() = 0;

        virtual void save() = 0;
        virtual void load() = 0;
    };
}

#endif//!R8GE_FILEREADER_H
