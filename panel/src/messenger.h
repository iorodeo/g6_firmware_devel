#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H
#include <functional>
#include <unordered_map>
#include "message.h"

using CommandUMap = std::unordered_map<uint8_t, std::function<void(Message&)>>;


class Messenger {

    public:

        Messenger();
        void initialize();
        void update();

    protected:
        uint64_t msg_count_ = 0;
        CommandUMap cmd_umap_;

};

#endif
