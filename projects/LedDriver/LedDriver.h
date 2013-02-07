#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

//TY@test
#define INV_LOGIC 0
#if INV_LOGIC
#	define LED_IMAGE(val) ((0x0000ffff)&~(val)) // 下位16ビットだけ使用
#else
#	define LED_IMAGE(val) (val)
#endif


#ifdef __cplusplus
extern "C" {
#endif
	void LedDriver_Create(uint16_t *address);
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

