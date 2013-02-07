#include "LedDriver.h"
#include "utils/RuntimeError.h"

// ****************************************
// TDD for Embedded : 
// ****************************************

enum {FIRST_LED = 1, LAST_LED = 16};

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
	*ledsAddress = LED_IMAGE(ledsImage);
}

static bool IsLedOutOfBounds(int ledNumber)
{
	return ( ledNumber < FIRST_LED || ledNumber > LAST_LED );
}

static void setLedImageBit(int ledNumber)
{
	ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
	ledsImage &= ~(convertLedNumberToBit(ledNumber));
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
	if( IsLedOutOfBounds(ledNumber) ){
		RUNTIME_ERROR(OUT_OF_BOUNDS_MESSAGE, OUT_OF_BOUNDS_PARAM);
		return;
	}
	setLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
	if( IsLedOutOfBounds(ledNumber) ){
		RUNTIME_ERROR(OUT_OF_BOUNDS_MESSAGE, OUT_OF_BOUNDS_PARAM);
		return;
	}
	clearLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

void LedDriver_TurnAllOff(void)
{
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

bool LedDriver_IsOn(int ledNumber)
{
	if( IsLedOutOfBounds(ledNumber) ){
		return false;
	}
	return (ledsImage & convertLedNumberToBit(ledNumber));
}

bool LedDriver_IsOff(int ledNumber)
{
	return ! LedDriver_IsOn(ledNumber);
}

