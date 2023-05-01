#include <mute_driver.h>

enum {LOWEST_CH = 0, HIGHEST_CH=8};
enum { ALL_CH_UNMUTED = 0x0000, ALL_CH_MUTED = 0x01FF};

MuteDriver::MuteDriver(int16_t *address) 
{
     mute_state = address; *mute_state = ALL_CH_MUTED; 
}

bool MuteDriver::is_channel_out_of_bounds(int16_t channelNum)
{
    if (channelNum <  LOWEST_CH || channelNum > HIGHEST_CH)
    {
        RUNTIME_ERROR("Mute Driver: out-of-bounds channel number", channelNum);
        return true;
    }
    return false;

}
int16_t MuteDriver::convert_channel_num_to_bit(int16_t channelNum)
{
    return (1 << channelNum);
}

void MuteDriver::unmute_all() 
{
    *mute_state = ALL_CH_UNMUTED; 
}

void MuteDriver::mute_all() 
{
    *mute_state = ALL_CH_MUTED; 
}

void MuteDriver::unmute_single_channel(int16_t channelNum) 
{
    if (is_channel_out_of_bounds(channelNum))
        return;

    *mute_state &= ~(1 << channelNum);
}
void MuteDriver::mute_single_channel(int16_t channelNum) 
{
    if (is_channel_out_of_bounds(channelNum))
        return;

    *mute_state |= 1 << channelNum;
}

bool MuteDriver::channel_is_muted(int16_t channelNum)
{
    if (is_channel_out_of_bounds(channelNum))
    {
        return true;
    }
    return (*mute_state & convert_channel_num_to_bit(channelNum));
}

bool MuteDriver::channel_is_unmuted(int16_t channelNum)
{
    return !(channel_is_muted(channelNum));
}