
//{{BLOCK(abc)

//======================================================================
//
//	abc, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 1025 tiles not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 65600 + 2048 = 68160
//
//	Time-stamp: 2013-10-31, 03:03:18
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ABC_H
#define GRIT_ABC_H

#define abcTilesLen 65600
extern const unsigned short abcTiles[32800];

#define abcMapLen 2048
extern const unsigned short abcMap[1024];

#define abcPalLen 512
extern const unsigned short abcPal[256];

#endif // GRIT_ABC_H

//}}BLOCK(abc)
