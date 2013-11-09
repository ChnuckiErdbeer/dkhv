
//{{BLOCK(test)

//======================================================================
//
//	test, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 1025 tiles not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 65600 + 2048 = 68160
//
//	Time-stamp: 2013-11-07, 03:28:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TEST_H
#define GRIT_TEST_H

#define testTilesLen 65600
extern const unsigned short testTiles[32800];

#define testMapLen 2048
extern const unsigned short testMap[1024];

#define testPalLen 512
extern const unsigned short testPal[256];

#endif // GRIT_TEST_H

//}}BLOCK(test)
