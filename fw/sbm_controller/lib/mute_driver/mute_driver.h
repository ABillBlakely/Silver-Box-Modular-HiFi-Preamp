#pragma once

#include <stdint.h>
#include "RuntimeError.h"

class MuteDriver{
private:
    int16_t *mute_state;
    bool is_channel_out_of_bounds(int16_t channelNum);
    int16_t convert_channel_num_to_bit(int16_t channelNum);
public:
    MuteDriver();
    MuteDriver(int16_t *address);
    void unmute_all();
    void mute_all();
    void unmute_single_channel(int16_t channelNum);
    void mute_single_channel(int16_t channelNum);
    bool channel_is_muted(int16_t channelNum);
    bool channel_is_unmuted(int16_t channelNum);

};
