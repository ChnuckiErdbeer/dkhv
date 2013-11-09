
//{{BLOCK(test)

//======================================================================
//
//	test, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 1024 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	External tile file: C:\devkitPro\##projects\dsgame\##GFX TEMP\finale\tilesets\test.png.
//	Total size: 512 + 65536 + 2048 = 68096
//
//	Time-stamp: 2013-11-06, 06:26:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TEST_H
#define GRIT_TEST_H

#define testTilesLen 65536
extern const unsigned short testTiles[32768];

#define testMapLen 2048
extern const unsigned short testMap[1024];

#define testPalLen 512
extern const unsigned short testPal[256];

#endif // GRIT_TEST_H

//}}BLOCK(test)
