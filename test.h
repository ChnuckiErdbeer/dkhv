
//{{BLOCK(test)

//======================================================================
//
//	test, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 408 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 26112 + 2048 = 28672
//
//	Time-stamp: 2013-11-07, 06:15:04
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TEST_H
#define GRIT_TEST_H

#define testTilesLen 26112
extern const unsigned int testTiles[6528];

#define testMapLen 2048
extern const unsigned short testMap[1024];

#define testPalLen 512
extern const unsigned short testPal[256];

#endif // GRIT_TEST_H

//}}BLOCK(test)
