#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
	void LedDriver_Create(uint16_t *address);
	void LedDriver_Destroy(void);
	void LedDriver_TurnOn(int ledNumber);
	void LedDriver_TurnOff(int ledNumber);
	void LedDriver_TurnAllOn(void);
#ifdef __cplusplus
}
#endif

#endif

