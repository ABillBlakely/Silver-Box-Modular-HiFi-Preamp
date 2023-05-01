#include <unity.h>
#include <stdint.h>
#include "mute_driver.h"
#include "RuntimeErrorStub.h"

static int16_t virtualMutes;
static MuteDriver  *mute;


void setUp(void)
{
    // initialize to all muted state
    RuntimeErrorStub_Reset();
    mute = new MuteDriver(&virtualMutes);
}

void tearDown(void)
{
}

void always_passes()
{
    TEST_ASSERT_TRUE(1);
}

void driver_initialize_muted()
{

    TEST_ASSERT_EQUAL_HEX16(0x01FF, virtualMutes);
}

void unmute_all()
{
    mute->unmute_all();
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtualMutes);
}

void mute_all()
{
    mute->mute_all();
    TEST_ASSERT_EQUAL_HEX16(0x01FF, virtualMutes);
}

void unmute_single_channel()
{
    mute->unmute_single_channel(4);
    TEST_ASSERT_EQUAL_HEX16(0x1EF, virtualMutes);
}

void unmute_single_channel_min_max()
{
    mute->unmute_single_channel(0);
    mute->unmute_single_channel(8);
    TEST_ASSERT_EQUAL_HEX16(0x0FE, virtualMutes);
}

void unmute_single_channel_out_of_bounds()
{
    mute->unmute_single_channel(-1);
    mute->unmute_single_channel(9);
    mute->unmute_single_channel(2345);
    mute->unmute_single_channel(65535);
    TEST_ASSERT_EQUAL_HEX16(0x01FF, virtualMutes);
}

void unmute_unmuted_channel()
{
    mute->unmute_all();
    mute->mute_single_channel(4);
    mute->unmute_single_channel(0);
    TEST_ASSERT_EQUAL_HEX16(0x0010, virtualMutes);

}

void unmute_catch_error()
{
    mute->unmute_single_channel(9);
    TEST_ASSERT_EQUAL_STRING("Mute Driver: out-of-bounds channel number", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(9, RuntimeErrorStub_GetLastParameter());
    mute->unmute_single_channel(-2);
    TEST_ASSERT_EQUAL_STRING("Mute Driver: out-of-bounds channel number", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-2, RuntimeErrorStub_GetLastParameter());
}

void mute_single_channel()
{
    mute->unmute_all();
    mute->mute_single_channel(4);
    TEST_ASSERT_EQUAL_HEX16(0x010, virtualMutes);

}

void mute_single_channel_min_max()
{
    mute->unmute_all();
    mute->mute_single_channel(0);
    mute->mute_single_channel(8);
    TEST_ASSERT_EQUAL_HEX16(0x101, virtualMutes);
}

void mute_single_channel_out_of_bounds()
{
    mute->unmute_all();
    mute->mute_single_channel(-1);
    mute->mute_single_channel(9);
    mute->mute_single_channel(2345);
    mute->mute_single_channel(65535);
    TEST_ASSERT_EQUAL_HEX16(0x000, virtualMutes);
}

void mute_muted_channel()
{
    mute->mute_single_channel(0);
    TEST_ASSERT_EQUAL_HEX16(0x01FF, virtualMutes);
}

void mute_catch_error()
{
    mute->mute_single_channel(9);
    TEST_ASSERT_EQUAL_STRING("Mute Driver: out-of-bounds channel number", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(9, RuntimeErrorStub_GetLastParameter());
    mute->mute_single_channel(-2);
    TEST_ASSERT_EQUAL_STRING("Mute Driver: out-of-bounds channel number", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-2, RuntimeErrorStub_GetLastParameter());
}

void channel_is_muted()
{
    TEST_ASSERT_TRUE(mute->channel_is_muted(0));
    mute->unmute_single_channel(0);
    TEST_ASSERT_FALSE(mute->channel_is_muted(0));

}

void channel_is_muted_out_of_bounds()
{
    TEST_ASSERT_TRUE(mute->channel_is_muted(-1));
    TEST_ASSERT_TRUE(mute->channel_is_muted(9));
    
}

void channel_is_unmuted()
{
    TEST_ASSERT_FALSE(mute->channel_is_unmuted(0));
    mute->unmute_single_channel(0);
    TEST_ASSERT_TRUE(mute->channel_is_unmuted(0));

}

void channel_is_unmuted_out_of_bounds()
{
    TEST_ASSERT_FALSE(mute->channel_is_unmuted(-1));
    TEST_ASSERT_FALSE(mute->channel_is_unmuted(9));
    
}

void run_MuteDriver_tests()
{
    RUN_TEST(always_passes);

    RUN_TEST(driver_initialize_muted);
    
    RUN_TEST(unmute_all);
    RUN_TEST(mute_all);
    
    RUN_TEST(unmute_single_channel);
    RUN_TEST(unmute_single_channel_min_max);
    RUN_TEST(unmute_single_channel_out_of_bounds);
    RUN_TEST(unmute_unmuted_channel);
    RUN_TEST(unmute_catch_error);
    
    RUN_TEST(mute_single_channel);
    RUN_TEST(mute_single_channel_min_max);
    RUN_TEST(mute_single_channel_out_of_bounds);
    RUN_TEST(mute_muted_channel);
    RUN_TEST(mute_catch_error);

    RUN_TEST(channel_is_muted);
    RUN_TEST(channel_is_muted_out_of_bounds);
    RUN_TEST(channel_is_unmuted);
    RUN_TEST(channel_is_unmuted_out_of_bounds);

}

void NativeTests()
{
    run_MuteDriver_tests();
}

void HardwareTests()
{
    run_MuteDriver_tests();
}


#ifndef ARDUINO
int main(void) 
{
    UNITY_BEGIN();
    NativeTests();
    UNITY_END();
}
#endif

#ifdef ARDUINO

#include <Arduino.h>

void setup() { 
    delay(5000);

    UNITY_BEGIN();
    NativeTests();
    HardwareTests();
    UNITY_END();    
}

void loop() {

}
#endif