/*
#include <stdio.h>
#include <stdlib.h>

#define PIC_SZ 3

unsigned char shrink_pxl(unsigned char* rgb) {
	unsigned char out = 0;
	out |= rgb[0] & 0xe0;          // 3 MSBs of R
	out |= (rgb[1] & 0xc0) >> 3;   // 2 MSBs of G
	out |= (rgb[2] & 0xe0) >> 5;   // 3 MSBs of B
	return out;
}

unsigned char* shrink_row(unsigned char* row) {
	unsigned char* shrinked_row = malloc(sizeof(unsigned char) * PIC_SZ);
	if (!shrinked_row) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	for (int i = 0; i < PIC_SZ; i++) {
		shrinked_row[i] = shrink_pxl(row + (3 * i));
	}
	return shrinked_row;
}

unsigned char** shrink_picture(unsigned char pic[][PIC_SZ * 3]) {
	// Allocate memory for the vector of pointers (one for each row)
	unsigned char** ret = malloc(PIC_SZ * sizeof(unsigned char*));
	if (!ret) {
		printf("Memory allocation failed\n");
		return NULL;
	}

	// Compress each row and store the pointer in the vector
	for (int i = 0; i < PIC_SZ; i++) {
		ret[i] = shrink_row(pic[i]);
		if (!ret[i]) {
			printf("Memory allocation failed for row %d\n", i);
			// Free previously allocated rows in case of failure
			for (int j = 0; j < i; j++) {
				free(ret[j]);
			}
			free(ret);
			return NULL;
		}
	}

	return ret;
}

void free_picture(unsigned char** compressed_pic) {
	for (int i = 0; i < PIC_SZ; i++) {
		free(compressed_pic[i]); // Free each row
	}
	free(compressed_pic); // Free the vector of row pointers
}

int main() {
	// Define a picture with 3 rows of 3 pixels (each pixel is RGB)
	unsigned char pic[PIC_SZ][PIC_SZ * 3] = {
		{ 0b11100000, 0b11000000, 0b10100000 }, // Row 1
		{ 0b01100000, 0b10000000, 0b11100000 }, // Row 2
		{ 0b10100000, 0b01100000, 0b00100000 }  // Row 3
	};

	// Compress the picture
	unsigned char** compressed_pic = shrink_picture(pic);

	// Print the compressed picture
	printf("Compressed Picture:\n");
	for (int i = 0; i < PIC_SZ; i++) {
		printf("Row %d: ", i);
		for (int j = 0; j < PIC_SZ; j++) {
			printf("0x%02x ", compressed_pic[i][j]);
		}
		printf("\n");
	}

	// Free the memory allocated for the compressed picture
	free_picture(compressed_pic);

	return 0;
}
*/