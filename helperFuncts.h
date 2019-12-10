/**
 * PNG SPEC:
 * 		http://www.w3.org/TR/PNG/
 *
 */
#ifndef HELPERFUNCTS_H
#define HELPERFUNCTS_H
#include "constants.h"

 long getNum(unsigned char* a, int start, int size) {
	unsigned long result = 0, shift = 8 * (size - 1);
	for (unsigned long i = start; i < start + size; i++) {
		result |= (unsigned long)a[i] << shift;
		shift -= 8;
	}
	return result;
}

void getBytes(unsigned char* a, int start, int size) { printf("0x"); for (int i = start; i < start + size; i++) printf("%02X", a[i]); }
void grabBytes(unsigned char* a, int start, int size, unsigned char* buffer) { memcpy(buffer, a + start, size); }
void grabString(unsigned char* a, int start, int size, unsigned char* buffer) { memcpy(buffer, a + start, size); buffer[size] = '\0'; }

void strColorType(int ct, unsigned char* buffer) {
	char* s = "unrecognized color type";
	switch (ct) {
		case 0: s = "greyscale"; break;
		case 2: s = "truecolour"; break;
		case 3: s = "indexed-colour"; break;
		case 4: s = "greyscale with alpha"; break;
		case 6: s = "truecolour with alpha"; break;
	}
	memcpy(buffer, s, LEN_STR);
}

void strCompress(int cm, unsigned char* buffer) {
	char* s = "unrecognized compression method";
	if (cm == 0) s = "deflate/inflate";
	memcpy(buffer, s, LEN_STR);
}

void strFilter(int fm, unsigned char* buffer) {
	char* s = "unrecognized filter method";
	if (fm == 0) s = "adaptive";
	memcpy(buffer, s, LEN_STR);
}

void strInterlace(int im, unsigned char* buffer) {
	char* s = "unrecognized interface method";
	if (im == 0)
		s = "standard";
	else if (im == 1)
		s = "Adam7 interlace";
	memcpy(buffer, s, LEN_STR);
}

#endif
