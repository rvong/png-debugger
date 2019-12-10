/**
 * @author Richard Vong
 * @date February 16, 2014
 * CS 141 Project 3: PNG Debugger
 *
 * PNG STRUCTURE
 * ====================
 * First 8 is PNG SIGNATURE
 *
 * Next 4 is CHUNK LENGTH
 * Next 4 is CHUNK TYPE
 * LENGTH = 13  => 13 BYTES OF DATA
 * 		- 4 Bytes Width
 * 		- 4 Bytes Height
 * 		- 1 Byte Bit Depth
 * 		- 1 Byte Color Type
 * 		- 1 Byte Compression method
 * 		- 1 Byte Filter method
 * 		- 1 Byte Interlace method
 * Next 4 is CRC CHECK (Chunk Type + Data), not including Chunk Length Unsigned Long
 *
 * Next 4 is CHUNK LENGTH
 * Next 4 is CHUNK TYPE
 * ...
 * ====================
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "constants.h"
#include "helperFuncts.h"
#include "crcCode.h"

void readPNG(char* path, int verbose);
void processPNG(unsigned char* buffer, long lSize, int verbose);

void readPNG(char* path, int verbose) {
	FILE* file = fopen(path, "rb");
	if (file == NULL) { printf("error: could not open file. (%s)", path); return; }

	fseek(file, 0, SEEK_END);	// Go to end
	long lSize = ftell(file);	// Get pos in stream
	rewind(file);				// Set pos to beginning

	unsigned char* buffer = malloc(sizeof(unsigned char) * lSize);
	if (buffer == NULL) { puts("error: memory error"); return; }

	size_t result = fread(buffer, 1, lSize, file);
	if (result != lSize) { puts("error: read error"); return; }
	fclose(file);

	printf("\t----\nfile-path=%s\n", path);
	printf("file-size=%ld bytes\n", lSize);
	processPNG(buffer, lSize, verbose);

	free(buffer);
	buffer = NULL;
}

void processPNG(unsigned char* buffer, long lSize, int verbose) {
	int cur = 0;
	unsigned char strBuffer[LEN_STR];

	printf("\n0x%08X\tpng-signature=", cur);
	getBytes(buffer, cur, LEN_PNGSIG);
	puts("");
	cur += LEN_PNGSIG;

	while (cur < lSize) {	// Print (LENGTH, TYPE, CRC) for each.
		long length = getNum(buffer, cur, LEN_CKLENGTH);
		printf("\n0x%08X\tchunk-length=0x%08lX\t(%ld)", cur, length, length);	// CHUNK LENGTH
		cur += LEN_CKLENGTH;

		unsigned char type[LEN_HDR];
		grabString(buffer, cur, LEN_CKTYPE, type);
		printf("\n0x%08X\tchunk-type=\'%s\'", cur, type);	// CHUNK TYPE
		int crcBegin = cur;
		cur += LEN_CKTYPE;

		if (verbose && (strcmp((char*)type, "IHDR") == 0)) { //if verbose, print expanded IHDR
			long width = getNum(buffer, cur, LEN_WIDTH);
			printf("\n0x%08X\twidth=0x%08lX\t(%ld)", cur, width, width);
			cur += LEN_WIDTH;

			long height = getNum(buffer, cur, LEN_HEIGHT);
			printf("\n0x%08X\theight=0x%08lX\t(%ld)", cur, height, height);
			cur += LEN_HEIGHT;

			printf("\n0x%08X\tbit-depth=%ld", cur, getNum(buffer, cur, LEN_BITDEPTH));
			cur += LEN_BITDEPTH;

			long colorType = getNum(buffer, cur, LEN_COLORTYPE);
			strColorType(colorType, strBuffer);		// Stores type description in strBuffer
			printf("\n0x%08X\tcolor-type=%ld \t(%s)", cur, colorType, strBuffer);
			cur += LEN_COLORTYPE;

			long compressMethod = getNum(buffer, cur, LEN_COMPRESS);
			strCompress(compressMethod, strBuffer);
			printf("\n0x%08X\tcompression-method=%ld \t(%s)", cur, compressMethod, strBuffer);
			cur += LEN_COMPRESS;

			long filterMethod = getNum(buffer, cur, LEN_FILTER);
			strFilter(filterMethod, strBuffer);
			printf("\n0x%08X\tfilter-method=%ld \t(%s)", cur, filterMethod, strBuffer);
			cur += LEN_FILTER;

			long interlaceMethod = getNum(buffer, cur, LEN_INTERLACE);
			strInterlace(interlaceMethod, strBuffer);
			printf("\n0x%08X\tinterlace-method=%ld \t(%s)", cur, interlaceMethod, strBuffer);
			cur += LEN_INTERLACE;
		}

		int crcLen = LEN_CKTYPE + length;
		unsigned char crcInput[crcLen];
		grabBytes(buffer, crcBegin, crcLen, crcInput);

		cur = crcBegin + crcLen;

		long crcCode = getNum(buffer, cur, LEN_CRC);
		long crcComputed = crc(crcInput, crcLen);
		char* crcResult = "CRC FAILED";
		if (crcCode == crcComputed) crcResult = "CRC OK!";

		printf("\n0x%08X\tcrc-code=0x%08lX", cur, crcCode);
		printf("\n>> (CRC CHECK)  crc-computed=0x%08lX \t=>\t%s\n\n", crcComputed, crcResult);
		cur += LEN_CRC;
	}
}

int main(int argc, char* argv[]) {
	// Test with example.png
	//readPNG(PNG_PATH, 1);

	/*
	printf("Arguments:\n\tARGC: %d\n", argc);
	puts("\tARGV: ");
	for (int i = 0; i < argc; i++)
		printf("\t\t%s\n", argv[i]);
	 */

	int verbose = 0;
	int i = 1;

	if (argc > 1)
		verbose = (strcmp(argv[1], "--verbose") == 0);

	if ((! verbose && argc > 1) || (verbose && argc > 2)) {
		if (verbose && argc > 2) i = 2;
		for (; i < argc; i++)
			readPNG(argv[i], verbose);
	}
	else {
		printf("Usage: pngDebugger (--verbose) file1.png file2.png file3.png ...\n");
	}

	return 0;
}
