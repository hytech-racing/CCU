#ifndef CANFDINTERFACE
#define CANFDINTERFACE

#include <cstdint>
#include "FlexCAN_T4.h"

#include "etl/delegate.h"


/**
 * @brief CAN FD setup function for flexcan FD devices
 *
 * @tparam CAN_DEVICE the type of the FD CAN device being used
 * @param CAN_dev ref to the CAN device to be setup
 * @param timings the bit timings to set the device to have
 * @param on_recv_func the receive function callback that will get registered to be ran on the receive of a CAN FD message
 */
template <typename CAN_DEVICE>
void handle_CANFD_setup(CAN_DEVICE &CAN_dev, const CANFD_timings_t &timings, void (*on_recv_func)(const CANFD_message_t &msg))
{
    CAN_dev.begin();
    CAN_dev.setBaudRate(timings);
    uint8_t num_mb = CAN_dev.setRegions(64);
    // uint8_t num_rx_mb = 12;
    // for (uint8_t i=0; i<num_mb; i++)
    // {
    //     CAN_dev.setMB(static_cast<FLEXCAN_MAILBOX>(i), i < num_rx_mb ? RX : TX, STD);
    // }
    CAN_dev.enableMBInterrupts();
    CAN_dev.onReceive(on_recv_func);
}

namespace CAN_util
{
    template <typename can_struct, typename queue_type>
    void enqueue_fd_msg(can_struct* structure, uint32_t (* pack_function)(can_struct*, uint8_t*, uint8_t*, uint8_t*), queue_type& CAN_msg_out_queue) {
        CANFD_message_t can_msg;
        can_msg.id = pack_function(structure, can_msg.buf, &can_msg.len, (uint8_t*) &can_msg.flags.extended);
        uint8_t buf[sizeof(CANFD_message_t)] = {};
        memmove(buf, &can_msg, sizeof(CANFD_message_t));
        CAN_msg_out_queue.push_back(buf, sizeof(CANFD_message_t));
    }

    template <typename can_struct, typename queue_type>
    void enqueue_fd_msg(can_struct* structure, uint32_t (* pack_function)(can_struct*, uint8_t*, uint8_t*, uint8_t*), queue_type& CAN_msg_out_queue, uint32_t id) {
        CANFD_message_t can_msg;
        pack_function(structure, can_msg.buf, &can_msg.len, (uint8_t*) &can_msg.flags.extended);
        can_msg.id = id;
        uint8_t buf[sizeof(CANFD_message_t)] = {};
        memmove(buf, &can_msg, sizeof(CANFD_message_t));
        CAN_msg_out_queue.push_back(buf, sizeof(CANFD_message_t));
    }
}

#endif /* CANINTERFACE */