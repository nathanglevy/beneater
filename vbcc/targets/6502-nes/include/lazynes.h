  // lazyNES - As lazy as possible NES hardware support library for vbcc6502
 // (happily cooperates with Shiru's famitone2 replay code)
// V1.0, 'Lazycow 2020


typedef signed char    byte;
typedef unsigned char  ubyte;
typedef signed short   word;
typedef unsigned short uword;


   // Wait for next vblank
  // flags: 0, lfBlank or lfSplit (see below)
 // result: Amount of frames since last sync [0..31], 128 is added on NTSC
//
ubyte lnSync(__reg("a") ubyte flags);
	enum {
	lfBlank = 1, // activates blank mode, blanks screen and allows lnPush() calls
	lfSplit = 2 // activates split mode, NMI waits for SPR0HIT and sets registers
	};


     // Write data into nametables, palettes, CHRRAM, etc.
    //  (System must be in blank mode!)
   // o: Destination address offset in vram
  //  a: Amount of bytes that should be written
 //   p: Pointer to data
//
void lnPush(__reg("a/x") uword o, __reg("r0") ubyte a, __reg("r2/r3") void* s);


   // Write data into nametables, palettes, CHRRAM, etc.
  //  (Screen has to be visible, doesn't work in blank mode!)
 // updateList: Pointer to update list
//
void lnList(__reg("a/x") void* updateList);
	enum { lfHor=64, lfVer=128, lfEnd=255 };
	//
	// remarks:
	// - The format of the update list is an array of unsigned bytes.
	// - There can be 3 different commands in the update list:
	//   a) addressHi, addressLo, value
	//   b) addressHi|lfHor, addressLo, amountOfBytes, byte1, byte2, byte3, ...
	//   c) addressHi|lfVer, addressLo, amountOfBytes, byte1, byte2, byte3, ...
	// - Multiple commands can be queued in one list,
	//   but there can only be one activated updatelist at a time.
	// - The end of the list is marked by lfEnd! (important!)
	// - It's the same format that's used in set_vram_update() of Shiru's neslib


        // Common offsets for lnPush() and lnList()
enum { //
	lnNameTab0=0x2000, lnNameTab1=0x2400, lnNameTab2=0x2800, lnNameTab3=0x2C00,
	lnAttrTab0=0x23C0, lnAttrTab1=0x27C0, lnAttrTab2=0x2BC0, lnAttrTab3=0x2FC0,
	 lnBackCol=0x3F00,
	 lnChrPal0=0x3F01,  lnChrPal1=0x3F05,  lnChrPal2=0x3F09,  lnChrPal3=0x3F0D,
	 lnSprPal0=0x3F11,  lnSprPal1=0x3F15,  lnSprPal2=0x3F19,  lnSprPal3=0x3F1D
};


   // Scroll background
  // x: New horizotnal scrolling offset in pixels, allowed range: [0..511]
 //  y: New vertical scrolling offset in pixels, allowed range: [0..479]
//
void lnScroll(__reg("r0/r1") uword x, __reg("r2/r3") uword y);
	//
	// remarks:
	// - If a SPR0HIT based splitscreen is used, the 1st call of lnScroll() sets
	//   the scrolling offsets of the area above the split and the 2nd call of
	//   lnScroll() sets the scrolling offsets of the area below the split.


    // Add meta-sprite to display list
   //    p: Pointer to metasprite data
  //   x,y: Sprite coordinates
 // result: New position offset in OAM after the meta sprite has been added
//
ubyte lnAddSpr(__reg("r0/r1") void* p,
	__reg("r2/r3") word x, __reg("r4/r5") word y);
	//
	// remarks:
	// - The format for the metasprite data is an array of unsigned bytes.
	// - Four bytes per sprite: x-offset, y-offset, tile, attributes
	// - The end of the list is marked by the value 128! (important!)
	// - It's the same format that's used in oam_meta_spr() from Shiru's neslib


   // Query joypad state
  //  port: Joypad port (1 or 2)
 // result: Set of joypad flags (see below)
//
ubyte lnGetPad(__reg("a") ubyte port);
	enum { lfU=8, lfD=4, lfL=2, lfR=1, lfA=128, lfB=64, lfStart=16, lfSelect=32 };


  //
 // advanced usage
//

extern __zpage volatile ubyte
	lnSpr0Wait,  // delay until scroll registers will be set after a SPR0HIT
	lnPPUCTRL,  // current value of PPUCTRL register (will be written in NMI)
	lnPPUMASK; // current value of PPUMASK register (will be written in NMI)
	//
	// remark: The lazyNES NMI will write the PPUCTRL and PPUMASK registers,
	//         so don't write PPUCTRL and PPUMASK directly - use these two
	//         variables insead. Their values will be written in the next NMI.
	//         Also, don't use these variables before the 1st call of lnSync()!
