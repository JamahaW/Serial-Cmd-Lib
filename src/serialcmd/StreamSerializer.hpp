#pragma once

#include <Stream.h>


namespace serialcmd {

    /// Вспомогательный класс для чтения структур и примитивных типов из потока
    class StreamSerializer {
    private:

        Stream &stream;

    public:
        explicit StreamSerializer(Stream &stream) :
            stream(stream) {}

        /// Побайтово считать тип
        template<class T> void read(T &destination) {
            this->stream.readBytes(reinterpret_cast<uint8_t *>(&destination), sizeof(T));
        }

        /// Побайтово записать тип
        template<class T> void write(T &&source) {
            this->stream.write(reinterpret_cast<const uint8_t *>(&source), sizeof(T));
        }
    };
}