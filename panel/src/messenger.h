#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H
#include <functional>
#include <unordered_map>
#include "message.h"


class Messenger {

    public:

        Messenger();
        void initialize();
        void update();


    protected:
        std::unordered_map<uint8_t, std::function<void(Message&)>> cmd_table_;
        uint64_t count_ = 0;

};

#endif
