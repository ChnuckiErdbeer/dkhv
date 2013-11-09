
//{{BLOCK(test)

//======================================================================
//
//	test, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 1025 tiles not compressed
//	+ regular map (flat), fake compressed, 32x32 
//	Total size: 512 + 65600 + 2052 = 68164
//
//	Time-stamp: 2013-11-08, 04:52:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TEST_H
#define GRIT_TEST_H

#define testTilesLen 65600
extern const unsigned int testTiles[16400];

#define testMapLen 2052
extern const unsigned short testMap[1026];

#define testPalLen 512
extern const unsigned short testPal[256];

#endif // GRIT_TEST_H

//}}BLOCK(test)
