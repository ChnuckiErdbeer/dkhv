
//{{BLOCK(gnade)

//======================================================================
//
//	gnade, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 1025 tiles not compressed
//	+ regular map (flat), fake compressed, 32x32 
//	Total size: 512 + 65600 + 2052 = 68164
//
//	Time-stamp: 2013-11-08, 04:50:16
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.10
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GNADE_H
#define GRIT_GNADE_H

#define gnadeTilesLen 65600
extern const unsigned int gnadeTiles[16400];

#define gnadeMapLen 2052
extern const unsigned short gnadeMap[1026];

#define gnadePalLen 512
extern const unsigned short gnadePal[256];

#endif // GRIT_GNADE_H

//}}BLOCK(gnade)
