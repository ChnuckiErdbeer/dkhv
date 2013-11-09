
//{{BLOCK(basicmap)

//======================================================================
//
//	basicmap, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 2048 tiles not compressed
//	+ regular map (flat), not compressed, 32x32 
//	External tile file: C:\devkitPro\##projects\dsgame\##GFX TEMP\basictileset.png.
//	Total size: 512 + 65536 + 2048 = 68096
//
//	Time-stamp: 2013-10-30, 22:11:15
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BASICMAP_H
#define GRIT_BASICMAP_H

#define basicmapTilesLen 65536
extern const unsigned short basicmapTiles[32768];

#define basicmapMapLen 2048
extern const unsigned short basicmapMap[1024];

#define basicmapPalLen 512
extern const unsigned short basicmapPal[256];

#endif // GRIT_BASICMAP_H

//}}BLOCK(basicmap)
