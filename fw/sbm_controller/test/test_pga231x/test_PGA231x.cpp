#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

void PGA231X_always_true()
{
    TEST_ASSERT_TRUE(1);
}

void setup_serial_comms()
{
    TEST_IGNORE();
    
}

void initialize_reset_saved_value()
{
    TEST_IGNORE();
}

void cs_low_on_write()
{
    TEST_IGNORE();
}

void cs_high_on_read()
{
    TEST_IGNORE();
}

void set_gain_minimum()
{
    TEST_IGNORE();
}

void set_gain_maximum()
{
    TEST_IGNORE();
}

void set_LR_balance()
{
    TEST_IGNORE();
}

void set_gain_zero()
{
    TEST_IGNORE();
}

void set_gain_0dB()
{
    TEST_IGNORE();
}

void zero_X_enabled()
{
    TEST_IGNORE();
}

void zero_X_disabled()
{
    TEST_IGNORE();
}


void NativeTests()
{
    RUN_TEST(PGA231X_always_true);
    RUN_TEST(setup_serial_comms);
    RUN_TEST(initialize_reset_saved_value);
    RUN_TEST(cs_low_on_write);
    RUN_TEST(cs_high_on_read);
    RUN_TEST(set_gain_minimum);
    RUN_TEST(set_gain_maximum);
    RUN_TEST(set_LR_balance);
    RUN_TEST(set_gain_zero);
    RUN_TEST(set_gain_0dB);
    RUN_TEST(zero_X_enabled);
    RUN_TEST(zero_X_disabled);
}

void HardwareTests()
{
    
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
    TEST_IGNORE();
}
#endif
/*
Notes: 
- SDO is a daisy chain for more modules, shift data in twice to read the data out.
- Gain = 0 is equivalent to Mute, but is per channel.
Device gain is 00 on power up.

*/