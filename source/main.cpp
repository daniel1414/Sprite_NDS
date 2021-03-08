#include <nds.h>
#include <stdio.h>
#include <nds/arm9/input.h>

#include "Sprite.h"

#include "starship.h"
#include "planet.h"

int main(void) {

	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	lcdMainOnBottom();

	Sprite::init(SpriteMapping_1D_32, false);

	SpriteAttributes shipAttr("Starship", 84, 16, (void*)starshipTiles, starshipTilesLen, (void*)starshipPal, starshipPalLen);
	Sprite* ship = Sprite::create(shipAttr);

	SpriteAttributes planetAttr("Planet", 32, 384 - 32, (void*)planetTiles, planetTilesLen, (void*)planetPal, planetPalLen, SpriteSize_64x64);
	Sprite* planet = Sprite::create(planetAttr);

	int planetDirection = 2;
	while(1) {

		scanKeys();
		uint32_t keysD = keysDown();
		uint32_t keysH = keysHeld();

		if(keysH & KEY_LEFT)
		{
			ship->moveByOffset(-3, 0);
		}
		if(keysH & KEY_RIGHT)
		{
			ship->moveByOffset(3, 0);
		}
		if(keysH & KEY_UP)
		{
			ship->moveByOffset(0, 3);
		}
		if(keysH & KEY_DOWN)
		{
			ship->moveByOffset(0, -3);
		}
		if(keysD & KEY_A)
		{
			if(ship)
				ship = Sprite::destroy(ship->getName());
		}
		if(keysD & KEY_B)
		{
			if(!ship)
				ship = Sprite::create(shipAttr);
		}
		if(planet)
		{
			planet->moveByOffset(planetDirection, 0);
			if(planet->getX() > 256 - 32 || planet->getX() < 32)
				planetDirection = -planetDirection;
		}

		Sprite::updateAll();
		swiWaitForVBlank();
	}

	return 0;
}
