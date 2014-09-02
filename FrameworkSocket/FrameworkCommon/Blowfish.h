#pragma once

#include <cstdint>

#define MAXKEYBYTES 56 /* 448 bits */
#define little_endian 1 /* Eg: Intel */
//#define big_endian 1 /* Eg: Motorola */
#ifdef __cplusplus
extern "C"
{
#endif
	int16_t opensubkeyfile(void);
	uint32_t F(uint32_t x);
	void Blowfish_encipher(uint32_t *xl, uint32_t *xr);
	void Blowfish_decipher(uint32_t *xl, uint32_t *xr);
	short InitializeBlowfish(char key[], int16_t keybytes);

#ifdef __cplusplus
}
#endif