#ifndef MESSAGE_RECEIVER_H
#define MESSAGE_RECEIVER_H
#include <functional>
#include <unordered_map>
#include "pattern.h"
#include "message.h"

using CommandUMap = std::unordered_map<uint8_t, std::function<void(Message&)>>;


class Messenger {

    public:

        Messenger();
        void initialize();
        void update();

    protected:

        Pattern pat_;
        uint64_t msg_count_ = 0;

        CommandUMap cmd_umap_; 
        void on_cmd_comms_check(Message &msg);
        void on_cmd_display_gray_2(Message &msg);
        void on_cmd_display_gray_16(Message &msg);

};

#endif
