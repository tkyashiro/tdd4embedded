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
	// 0x180 : 0000000110000000
	//       : 0fedcba987654321
}

TEST(LedDriver, TurnOffAnyLed)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	CHECK_EQUAL(0xFF7F, virtualLeds);
	// 0xFF7F : 1111111101111111
	//        : 0fedcba987654321
}

TEST(LedDriver, AllOn)
{
	LedDriver_TurnAllOn();
	CHECK_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, LedDriverIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	CHECK_EQUAL(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);

	CHECK_EQUAL( 0x8001, virtualLeds);
	// 0x8001 : 1000000000000001
	//        : 0fedcba987654321
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
	CHECK_EQUAL( 0x0000, virtualLeds);
	LedDriver_TurnOn(-1);
	CHECK_EQUAL( 0x0000, virtualLeds);
	LedDriver_TurnOn(0);
	CHECK_EQUAL( 0x0000, virtualLeds);
	LedDriver_TurnOn(17);
	CHECK_EQUAL( 0x0000, virtualLeds);
	LedDriver_TurnOn(3141);
	CHECK_EQUAL( 0x0000, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_TurnAllOn();
	CHECK_EQUAL( 0xFFFF, virtualLeds);
	LedDriver_TurnOff(-1);
	CHECK_EQUAL( 0xFFFF, virtualLeds);
	LedDriver_TurnOff(0);
	CHECK_EQUAL( 0xFFFF, virtualLeds);
	LedDriver_TurnOff(17);
	CHECK_EQUAL( 0xFFFF, virtualLeds);
	LedDriver_TurnOff(3141);
	CHECK_EQUAL( 0xFFFF, virtualLeds);
}

TEST(LedDriver, OutofBoundsProducesRuntimeError)
{
	LedDriver_TurnOn(-1);
	STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
	CHECK_EQUAL(-1, RuntimeErrorStub_GetLastParameter() );
}

int main( int argc, char **argv )
{
	return RUN_ALL_TESTS(argc, argv);
}

