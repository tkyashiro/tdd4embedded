#include "CppUTest/CommandLineTestRunner.h"
#include "LedDriver.h"

/* ************************************************************
 *     LED Driver Tests
 * _ All LEDs are off after the driver is initialized
 * _ A single LED can be turned on.
 * _ A single LED can be turned off.
 * _ Multiple LEDs can be turned off.
 * _ Turn on all LEDs
 * _ Turn off all LEDs
 * _ Query LED state.
 * _ Check boundary values.
 * _ Check out-of-bounds values
 * *************************************************************/

static uint16_t virtualLeds = 0xffff;
TEST_GROUP(LedDriver)
{
	TEST_SETUP(){
		LedDriver_Create(&virtualLeds);
	}
	TEST_TEARDOWN(){
	}
};


TEST(LedDriver, LedsOffAfterCrate)
{
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);
	LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
	LedDriver_TurnOn(1);
	CHECK_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	CHECK_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	CHECK_EQUAL(0x180, virtualLeds);
	// 0x180 : 000001100000000
	//       : fdcba9876543210
}

TEST(LedDriver, TurnOffAnyLed)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	LedDriver_TurnOff(8);
	CHECK_EQUAL(0x100, virtualLeds);
	// 0x100 : 000001000000000
	//       : fdcba9876543210
}

TEST(LedDriver, AllOn)
{
	LedDriver_TurnAllOn();
	CHECK_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, )
{
}

int main( int argc, char **argv )
{
	return RUN_ALL_TESTS(argc, argv);
}

