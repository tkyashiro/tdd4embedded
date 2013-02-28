#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

typedef enum { LedDriver_PositiveLogic = 0, LedDriver_NegativeLogic = 1} LedDriver_Logic;

#ifdef __cplusplus
extern "C" {
#endif
	void LedDriver_Create(uint16_t *address, LedDriver_Logic logic );
	void LedDriver_Destroy(void);
	void LedDriver_TurnOn(int ledNumber);
	void LedDriver_TurnOff(int ledNumber);
	void LedDriver_TurnAllOn(void);
	void LedDriver_TurnAllOff(void);
	bool LedDriver_IsOn(int ledNumber);
	bool LedDriver_IsOff(int ledNumber);
#ifdef __cplusplus
}
#endif

#endif

