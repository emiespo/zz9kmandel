/*
 * MNT ZZ9000 Amiga Graphics Card Driver (ZZ9000.card)
 * Copyright (C) 2016-2019, Lukas F. Hartmann <lukas@mntre.com>
 *                          MNT Research GmbH, Berlin
 *                          https://mntre.com
 *
 * More Info: https://mntre.com/zz9000
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * GNU General Public License v3.0 or later
 *
 * https://spdx.org/licenses/GPL-3.0-or-later.html
 */

#ifndef ZZ9K_H
#define ZZ9K_H

#define uint8_t unsigned char
#define int16_t signed short
#define uint16_t unsigned short
#define uint32_t unsigned long
#define int32_t signed long

#define u16 uint16_t
#define u32 uint32_t

#define MNTVA_COLOR_8BIT     0
#define MNTVA_COLOR_16BIT565 1
#define MNTVA_COLOR_32BIT    2
#define MNTVA_COLOR_15BIT    3

#define ZZ9K_APP_SPACE 0x03000000
#define ZZ9K_APP_DATASPACE 0x05000000
#define ZZ9K_MEM_START 0x00200000

/**
 * ZZ9K Registers. They have to be in sync with the installed firmware.
 * 
 * @see https://source.mntmn.com/MNT/zz9000-firmware/src/branch/master/ZZ9000_proto.sdk/ZZ9000OS/src/zz_regs.h
 */
typedef volatile struct MNTZZ9KRegs {
  u16 unused_reg00; // 00
  u16 mode;         // 02
  u16 config;       // 04
  u16 sprite_x;     // 06
  u16 sprite_y;     // 08
  u16 pan_hi;       // 0a
  u16 pan_lo;       // 0c
  u16 vcap_mode;    // 0e

  u16 blitter_x1;   // 10
  u16 blitter_y1;   // 12
  u16 blitter_x2;   // 14
  u16 blitter_y2;   // 16
  u16 blitter_row_pitch; // 18 destination pitch
  u16 blitter_x3;   // 1a
  u16 blitter_y3;   // 1c
  u16 blitter_rgb_hi;       // 1e

  u16 blitter_rgb_lo;       // 20
  u16 blitter_op_fillrect;  // 22
  u16 blitter_op_copyrect;  // 24
  u16 blitter_op_filltemplate;   // 26  
  u16 blitter_src_hi; // 28
  u16 blitter_src_lo; // 2a
  u16 blitter_dst_hi; // 2c
  u16 blitter_dst_lo; // 2e
  
  u16 blitter_colormode; // 30 destination colormode
  u16 blitter_src_pitch; // 32
  u16 blitter_rgb2_hi; // 34 background/secondary color
  u16 blitter_rgb2_lo; // 36
  u16 p2c;             // 38
  u16 drawline;        // 3a
  u16 p2d;             // 3c
  u16 invertrect;      // 3e

  u16 user[4];         // 40-46
  u16 sprite_bitmap;   // 48
  u16 sprite_colors;   // 4a
  u16 vblank_status;   // 4c
  u16 unused_reg4e;    // 4e

  u16 unused_reg50[5]; // 50-58
  u16 blitter_dma_op;  // 5a
  u16 acc_op;          // 5c
  u16 set_split_pos;   // 5e

  u16 unused_reg60[8]; // 60-6e
  u16 unused_reg70[8]; // 70-7e

  u16 eth_tx;          // 80
  u16 eth_rx;          // 82
  u16 eth_mac_hi;      // 84
  u16 eth_mac_hi2;     // 86
  u16 eth_mac_low;     // 88
  u16 unused_reg80[3]; // 8a-8e

  u16 arm_run_hi; // 90
  u16 arm_run_lo; // 92
  u16 arm_argc;   // 94
  u16 arm_arg[8]; // 96,98,9a,9c..a4

  u16 unused_a6[5]; // a6..ae
  
  u16 arm_event_serial; // b0
  u16 arm_event_code;   // b2
  u16 unused_b4[6];     // b4-be

  u16 fw_version;       // c0
  u16 unused_c2[7];     // c2-ce

  u16 usbblk_tx_hi;	 //d0,
  u16 usbblk_tx_lo;	 //d2,
  u16 usbblk_rx_hi;	 //d4,
  u16 usbblk_rx_lo;	 //d6,
  u16 usb_status;	   //d8,
  u16 usb_bufsel;	   //da,
  u16 usb_capacity;	 //dc,
  u16 unused_regde;	 //de,

  u16 temperature;	 //e0,
  u16 voltage_aux;	 //e2,
  u16 voltage_int;	 //e4,
  u16 unused_rege6;	 //e6,
  u16 unused_rege8;	 //e8,
  u16 unused_regea;	 //ea,
  u16 unused_regec;	 //ec,
  u16 unused_regee;	 //ee,

  u16 unused_regf0;	 //f0,
  u16 unused_regf2;	 //f2,
  u16 unused_regf4;	 //f4,
  u16 unused_regf6;	 //f6,
  u16 unused_regf8;	 //f8,
  u16 unused_regfa;	 //fa,
  u16 debug;	       //fc,
  u16 unused_regfe;	 //fe,

} MNTZZ9KRegs;

typedef volatile struct MNTZZ9KCXRegs {
  u16 video_control_data_hi; // 00
  u16 video_control_data_lo; // 02
  u16 video_control_op;      // 04
  u16 videocap_mode;         // 06
} MNTZZ9KCXRegs;

/**
 * Holds ZZ9K configuration parameters
 */
struct MNTZZ9KConfigDev {
    uint8_t* memory;
    uint8_t* dest;
    uint32_t armArgs[4];
    uint32_t loadOffset;
    MNTZZ9KRegs* regs;
    uint8_t  programLoaded;
    uint8_t  pad_0;
};

#endif