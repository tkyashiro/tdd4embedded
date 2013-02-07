#include "CppUTest/CommandLineTestRunner.h"
#include "LedDriver.h"
#include "mocks/RuntimeErrorStub.h"

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

static uint16_t virtualLeds = LED_IMAGE(0xffff);
TEST_GROUP(LedDriver)
{
	TEST_SETUP(){
		LedDriver_Create(&virtualLeds);
	}
	TEST_TEARDOWN(){
	}
};


TEST(LedDriver, LedsOffAfterCreate)
{
	uint16_t virtualLeds = LED_IMAGE(0xffff);
	LedDriver_Create(&virtualLeds);
	LONGS_EQUAL(LED_IMAGE(0x0000), virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
	LedDriver_TurnOn(1);
	CHECK_EQUAL(LED_IMAGE(0x0001), virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	CHECK_EQUAL(LED_IMAGE(0x0000), virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	CHECK_EQUAL(LED_IMAGE(0x180), virtualLeds);
	// 0x180 : 0000000110000000
	//       : 0fedcba987654321
}

TEST(LedDriver, TurnOffAnyLed)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	CHECK_EQUAL(LED_IMAGE(0xFF7F), virtualLeds);
	// 0xFF7F : 1111111101111111
	//        : 0fedcba987654321
}

TEST(LedDriver, AllOn)
{
	LedDriver_TurnAllOn();
	CHECK_EQUAL(LED_IMAGE(0xffff), virtualLeds);
}

TEST(LedDriver, AllOff)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnAllOff();
	CHECK_EQUAL(LED_IMAGE(0x0000), virtualLeds);
}

TEST(LedDriver, LedDriverIsNotReadable)
{
	virtualLeds = LED_IMAGE(0xffff);
	LedDriver_TurnOn(8);
	CHECK_EQUAL(LED_IMAGE(0x80), virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);

	CHECK_EQUAL( LED_IMAGE(0x8001), virtualLeds);
	// 0x8001 : 1000000000000001
	//        : 0fedcba987654321
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
	CHECK_EQUAL( LED_IMAGE(0x0000), virtualLeds);
	LedDriver_TurnOn(-1);
	CHECK_EQUAL( LED_IMAGE(0x0000), virtualLeds);
	LedDriver_TurnOn(0);
	CHECK_EQUAL( LED_IMAGE(0x0000), virtualLeds);
	LedDriver_TurnOn(17);
	CHECK_EQUAL( LED_IMAGE(0x0000), virtualLeds);
	LedDriver_TurnOn(3141);
	CHECK_EQUAL( LED_IMAGE(0x0000), virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_TurnAllOn();
	CHECK_EQUAL( LED_IMAGE(0xFFFF), virtualLeds);
	LedDriver_TurnOff(-1);
	CHECK_EQUAL( LED_IMAGE(0xFFFF), virtualLeds);
	LedDriver_TurnOff(0);
	CHECK_EQUAL( LED_IMAGE(0xFFFF), virtualLeds);
	LedDriver_TurnOff(17);
	CHECK_EQUAL( LED_IMAGE(0xFFFF), virtualLeds);
	LedDriver_TurnOff(3141);
	CHECK_EQUAL( LED_IMAGE(0xFFFF), virtualLeds);
}

IGNORE_TEST(LedDriver, OutofBoundsProducesRuntimeError)
{
	LedDriver_TurnOn(-1);
	STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
	CHECK_EQUAL(-1, RuntimeErrorStub_GetLastParameter() );
}

TEST(LedDriver, IsOn)
{
	CHECK_EQUAL(false, LedDriver_IsOn(11));
	LedDriver_TurnOn(11);
	CHECK_EQUAL(true, LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
	CHECK_EQUAL(true, LedDriver_IsOff(0));
	CHECK_EQUAL(true, LedDriver_IsOff(17));

	CHECK_EQUAL(false, LedDriver_IsOn(0));
	CHECK_EQUAL(false, LedDriver_IsOn(17));
}

TEST(LedDriver, IsOff)
{
	CHECK_EQUAL(true, LedDriver_IsOff(12));
	LedDriver_TurnOn(12);
	CHECK_EQUAL(false, LedDriver_IsOff(12));
}

TEST(LedDriver, TurnOffMultipleLeds)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(9);
	LedDriver_TurnOff(8);
	CHECK_EQUAL(LED_IMAGE((~0x180)&0xFFFF), virtualLeds);
	// 0x180 : 0000000110000000
	//       : 0fedcba987654321
}

int main( int argc, char **argv )
{
	return RUN_ALL_TESTS(argc, argv);
}

