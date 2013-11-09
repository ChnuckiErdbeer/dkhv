
//{{BLOCK(sieben)

//======================================================================
//
//	sieben, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 1025 tiles not compressed
//	+ regular map (flat), fake compressed, 32x32 
//	Total size: 512 + 65600 + 2052 = 68164
//
//	Time-stamp: 2013-11-08, 23:45:18
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SIEBEN_H
#define GRIT_SIEBEN_H

#define siebenTilesLen 65600
extern const unsigned int siebenTiles[16400];

#define siebenMapLen 2052
extern const unsigned short siebenMap[1026];

#define siebenPalLen 512
extern const unsigned short siebenPal[256];

#endif // GRIT_SIEBEN_H

//}}BLOCK(sieben)
