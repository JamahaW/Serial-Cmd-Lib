#pragma once

#include "serialcmd/StreamSerializer.hpp"


namespace serialcmd {
    enum Error : char {
        ok = 0x00,
        fail = 0x01
    };

    /// Протокол общения с мастер-устройством
    template<
        /// Класс устройства
        class Device,
        /// Тип индекса команды
        typename CommandIndex,
        /// Startup пакет данных
        typename Startup
    >
    class Protocol {
    public:
        /// Функция обработки команды
        typedef Error(*CommandFunc)(Device &, StreamSerializer &);

    private:

        /// Таблица команд
        CommandFunc *commands;

        /// Кол-во команд
        const CommandIndex command_count;

        StreamSerializer serializer;

    public:

        explicit Protocol(
            CommandFunc *commands,
            const CommandIndex command_count,
            Stream &stream
        ) :
            command_count(command_count), commands(commands), serializer(stream) {}

        /// Отправить начальный пакет
        void begin(Startup &&startup) {
            serializer.write(startup);
        }

        /// Обновление
        void pull() {

        }
    };
}