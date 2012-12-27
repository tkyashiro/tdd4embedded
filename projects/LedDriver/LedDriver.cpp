#include "LedDriver.h"
#include "utils/RuntimeError.h"

// ****************************************
// TDD for Embedded : RUNTIME_ERROR
// ****************************************

// íËêî
static const int   OUT_OF_BOUNDS_PARAM   = -1;
static const char *OUT_OF_BOUNDS_MESSAGE = "LED Driver: out-of-bounds LED";

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};

// ïœêî
static uint16_t *ledsAddress;
static uint16_t ledsImage;

// ä÷êî
static uint16_t convertLedNumberToBit(int ledNumber)
{
	return 1 << (ledNumber-1);
}

static void updateHardware()
{
	*ledsAddress = ledsImage;
}

void LedDriver_Create(uint16_t *address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

void LedDriver_Destroy(void)
{
}

void LedDriver_TurnOn(int ledNumber)
{
	if( ledNumber <= 0 || ledNumber > 16 ){
		RUNTIME_ERROR(OUT_OF_BOUNDS_MESSAGE, OUT_OF_BOUNDS_PARAM);
		return;
	}
	ledsImage |= convertLedNumberToBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
	if( ledNumber <= 0 || ledNumber > 16 ){
		RUNTIME_ERROR(OUT_OF_BOUNDS_MESSAGE, OUT_OF_BOUNDS_PARAM);
		return;
	}
	ledsImage &= ~(convertLedNumberToBit(ledNumber));
	updateHardware();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

