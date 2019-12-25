#include <stdlib.h>
#include <peekpoke.h>
#include <string.h>
#include <conio.h>

char spriteData[] = {
	31,255,248,31,255,252,0,15,252,62,7,252,62,3,254,124,
	3,222,124,7,158,124,15,159,124,63,15,127,252,15,255,240,
	15,0,0,7,0,0,6,0,0,4,3,255,255,63,255,255,
	255,255,224,255,255,224,63,255,255,3,255,255,0,0,0,6,
	7,255,248,15,255,252,31,0,126,62,0,63,60,248,31,120, 
	248,31,240,240,62,241,240,62,225,240,252,193,255,240,129,255, 
	192,0,0,0,0,0,0,0,0,0,255,255,128,255,255,252, 
	7,255,255,7,255,255,255,255,252,255,255,128,0,0,0,6
};

char possibleColors[] = {
	6, 3, 4, 5, 2, 7, 8, 10, 13, 14
};

int main() {
	const unsigned v = 53248L; // VIC-II base address
	unsigned x = 160;
	char y = 140;
	unsigned xDir;
	char yDir;
	unsigned timer = 0;
	char colorIndex = 0;

	_randomize();

	xDir = (rand() % 2) ? 1L : -1L;
	yDir = (rand() % 2) ? 1 : -1;

	clrscr();
	POKE(53281L, 0);

	POKE(v + 21, 3); // Enable sprites 0 and 1
	POKE(2040L, 192); // Set pointer for sprite 0
	POKE(2041L, 193); // Set pointer for sprite 1
	POKE(v + 39, 6); // Set colour for sprite 0
	POKE(v + 40, 6); // Set colour for sprite 1

	memcpy(12288L, spriteData, sizeof(spriteData));

	for(;;) {
		timer++;
		timer %= 30;
		if(!timer) {
			x += xDir;
			y += yDir;

			if(yDir == 1) {
				if(y == 230) {
					yDir = -1;
					if(x < 28L || x > 292L) {
						colorIndex++;
						colorIndex %= sizeof(possibleColors);
						POKE(v + 39, possibleColors[colorIndex]);
						POKE(v + 40, possibleColors[colorIndex]);
					}
				}
			} else {
				if(y == 50) {
					yDir = 1;
					if(x < 28L || x > 292L) {
						colorIndex++;
						colorIndex %= sizeof(possibleColors);
						POKE(v + 39, possibleColors[colorIndex]);
						POKE(v + 40, possibleColors[colorIndex]);
					}
				}
			}
			if(xDir == 1) {
				if(x == 296L) {
					xDir = -1;
					if(y < 54 || y > 226) {
						colorIndex++;
						colorIndex %= sizeof(possibleColors);
						POKE(v + 39, possibleColors[colorIndex]);
						POKE(v + 40, possibleColors[colorIndex]);
					}
				}
			} else {
				if(x == 24L) {
					xDir = 1;
					if(y < 54 || y > 226) {
						colorIndex++;
						colorIndex %= sizeof(possibleColors);
						POKE(v + 39, possibleColors[colorIndex]);
						POKE(v + 40, possibleColors[colorIndex]);
					}
				}
			}

			POKE(v + 0, x & 255); // Sprite 0 X
			POKE(v + 1, y); // Sprite 0 Y
			POKE(v + 2, (x + 24) & 255); // Sprite 1 X
			POKE(v + 3, y); // Sprite 1 Y
			POKE(v + 16, (x > 255) | ((x > 231) << 1)); // X msb
		}
	}

	return EXIT_SUCCESS;
}
