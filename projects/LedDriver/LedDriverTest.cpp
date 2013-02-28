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

TEST_GROUP(LedDriverPositive)
{
	TEST_SETUP(){
		virtualLeds = 0xffff;
		LedDriver_Create(&virtualLeds, LedDriver_PositiveLogic);
	}
	TEST_TEARDOWN(){
	}
	void CheckLedImage(uint16_t desired_positive, uint16_t actual)
	{
		CHECK_EQUAL(desired_positive, actual);
	}
};

TEST_GROUP(LedDriverNegative)
{
	TEST_SETUP(){
		virtualLeds = 0x0000;
		LedDriver_Create(&virtualLeds, LedDriver_NegativeLogic);
	}
	TEST_TEARDOWN(){
	}
	void CheckLedImage(uint16_t desired_positive, uint16_t actual)
	{
		CHECK_EQUAL((uint16_t)(~desired_positive), actual);
	}
};

TEST(LedDriverPositive, LedImageCheck)
{
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverNegative, LedImageCheck)
{
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverPositive, LedsOffAfterCreate)
{
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds, LedDriver_PositiveLogic);
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverNegative, LedsOffAfterCreate)
{
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds, LedDriver_NegativeLogic);
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverPositive, TurnOnLedOne)
{
	LedDriver_TurnOn(1);
	CheckLedImage(0x0001, virtualLeds);
}

TEST(LedDriverNegative, TurnOnLedOne)
{
	LedDriver_TurnOn(1);
	CheckLedImage(0x0001, virtualLeds);
}

TEST(LedDriverPositive, TurnOffLedOne)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverNegative, TurnOffLedOne)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverPositive, TurnOnMultipleLeds)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	CheckLedImage(0x180, virtualLeds);
	// 0x180 : 0000000110000000
	//       : 0fedcba987654321
}

TEST(LedDriverNegative, TurnOnMultipleLeds)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	CheckLedImage(0x180, virtualLeds);
	// 0x180 : 0000000110000000
	//       : 0fedcba987654321
}

TEST(LedDriverPositive, TurnOffAnyLed)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	CheckLedImage(0xFF7F, virtualLeds);
	// 0xFF7F : 1111111101111111
	//        : 0fedcba987654321
}

TEST(LedDriverNegative, TurnOffAnyLed)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	CheckLedImage(0xFF7F, virtualLeds);
	// 0xFF7F : 1111111101111111
	//        : 0fedcba987654321
}

TEST(LedDriverPositive, AllOn)
{
	LedDriver_TurnAllOn();
	CheckLedImage(0xffff, virtualLeds);
}

TEST(LedDriverNegative, AllOn)
{
	LedDriver_TurnAllOn();
	CheckLedImage(0xffff, virtualLeds);
}

TEST(LedDriverPositive, AllOff)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnAllOff();
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverNegative, AllOff)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnAllOff();
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverPositive, LedDriverIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	CheckLedImage(0x80, virtualLeds);
}

TEST(LedDriverNegative, LedDriverIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	CheckLedImage(0x80, virtualLeds);
}

TEST(LedDriverPositive, UpperAndLowerBounds)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);

	CheckLedImage(0x8001, virtualLeds);
	// 0x8001 : 1000000000000001
	//        : 0fedcba987654321
}

TEST(LedDriverNegative, UpperAndLowerBounds)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);

	CheckLedImage(0x8001, virtualLeds);
	// 0x8001 : 1000000000000001
	//        : 0fedcba987654321
}

TEST(LedDriverPositive, OutOfBoundsTurnOnDoesNoHarm)
{
	CheckLedImage(0x0000, virtualLeds);
	LedDriver_TurnOn(-1);
	CheckLedImage(0x0000, virtualLeds);
	LedDriver_TurnOn(0);
	CheckLedImage(0x0000, virtualLeds);
	LedDriver_TurnOn(17);
	CheckLedImage(0x0000, virtualLeds);
	LedDriver_TurnOn(3141);
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverNegative, OutOfBoundsTurnOnDoesNoHarm)
{
	CheckLedImage(0x0000, virtualLeds);
	LedDriver_TurnOn(-1);
	CheckLedImage(0x0000, virtualLeds);
	LedDriver_TurnOn(0);
	CheckLedImage(0x0000, virtualLeds);
	LedDriver_TurnOn(17);
	CheckLedImage(0x0000, virtualLeds);
	LedDriver_TurnOn(3141);
	CheckLedImage(0x0000, virtualLeds);
}

TEST(LedDriverPositive, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_TurnAllOn();
	CheckLedImage(0xFFFF, virtualLeds);
	LedDriver_TurnOff(-1);
	CheckLedImage(0xFFFF, virtualLeds);
	LedDriver_TurnOff(0);
	CheckLedImage(0xFFFF, virtualLeds);
	LedDriver_TurnOff(17);
	CheckLedImage(0xFFFF, virtualLeds);
	LedDriver_TurnOff(3141);
	CheckLedImage(0xFFFF, virtualLeds);
}

TEST(LedDriverNegative, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_TurnAllOn();
	CheckLedImage(0xFFFF, virtualLeds);
	LedDriver_TurnOff(-1);
	CheckLedImage(0xFFFF, virtualLeds);
	LedDriver_TurnOff(0);
	CheckLedImage(0xFFFF, virtualLeds);
	LedDriver_TurnOff(17);
	CheckLedImage(0xFFFF, virtualLeds);
	LedDriver_TurnOff(3141);
	CheckLedImage(0xFFFF, virtualLeds);
}

IGNORE_TEST(LedDriverPositive, OutofBoundsProducesRuntimeError)
{
	LedDriver_TurnOn(-1);
	STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
	CHECK_EQUAL(-1, RuntimeErrorStub_GetLastParameter() );
}

IGNORE_TEST(LedDriverNegative, OutofBoundsProducesRuntimeError)
{
	LedDriver_TurnOn(-1);
	STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
	CHECK_EQUAL(-1, RuntimeErrorStub_GetLastParameter() );
}

TEST(LedDriverPositive, IsOn)
{
	CHECK_EQUAL(false, LedDriver_IsOn(11));
	LedDriver_TurnOn(11);
	CHECK_EQUAL(true, LedDriver_IsOn(11));
}

TEST(LedDriverNegative, IsOn)
{
	CHECK_EQUAL(false, LedDriver_IsOn(11));
	LedDriver_TurnOn(11);
	CHECK_EQUAL(true, LedDriver_IsOn(11));
}

TEST(LedDriverPositive, OutOfBoundsLedsAreAlwaysOff)
{
	CHECK_EQUAL(true, LedDriver_IsOff(0));
	CHECK_EQUAL(true, LedDriver_IsOff(17));

	CHECK_EQUAL(false, LedDriver_IsOn(0));
	CHECK_EQUAL(false, LedDriver_IsOn(17));
}

TEST(LedDriverNegative, OutOfBoundsLedsAreAlwaysOff)
{
	CHECK_EQUAL(true, LedDriver_IsOff(0));
	CHECK_EQUAL(true, LedDriver_IsOff(17));

	CHECK_EQUAL(false, LedDriver_IsOn(0));
	CHECK_EQUAL(false, LedDriver_IsOn(17));
}

TEST(LedDriverPositive, IsOff)
{
	CHECK_EQUAL(true, LedDriver_IsOff(12));
	LedDriver_TurnOn(12);
	CHECK_EQUAL(false, LedDriver_IsOff(12));
}

TEST(LedDriverNegative, IsOff)
{
	CHECK_EQUAL(true, LedDriver_IsOff(12));
	LedDriver_TurnOn(12);
	CHECK_EQUAL(false, LedDriver_IsOff(12));
}

TEST(LedDriverPositive, TurnOffMultipleLeds)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(9);
	LedDriver_TurnOff(8);
	CheckLedImage(((~0x180)&0xFFFF), virtualLeds);
	// 0x180 : 0000000110000000
	//       : 0fedcba987654321
}

TEST(LedDriverNegative, TurnOffMultipleLeds)
{
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(9);
	LedDriver_TurnOff(8);
	CheckLedImage(((~0x180)&0xFFFF), virtualLeds);
	// 0x180 : 0000000110000000
	//       : 0fedcba987654321
}


int main( int argc, char **argv )
{
	return RUN_ALL_TESTS(argc, argv);
}

