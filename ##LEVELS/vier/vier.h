
//{{BLOCK(vier)

//======================================================================
//
//	vier, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 1025 tiles not compressed
//	+ regular map (flat), fake compressed, 32x32 
//	Total size: 512 + 65600 + 2052 = 68164
//
//	Time-stamp: 2013-11-08, 04:59:06
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_VIER_H
#define GRIT_VIER_H

#define vierTilesLen 65600
extern const unsigned int vierTiles[16400];

#define vierMapLen 2052
extern const unsigned short vierMap[1026];

#define vierPalLen 512
extern const unsigned short vierPal[256];

#endif // GRIT_VIER_H

//}}BLOCK(vier)
