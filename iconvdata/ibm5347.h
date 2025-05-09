/* Tables for conversion from and to IBM5347.
   Copyright (C) 2005-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <stdint.h>

static const uint32_t to_ucs4[256] =
{
  [0x00] = 0x0000, [0x01] = 0x0001, [0x02] = 0x0002, [0x03] = 0x0003,
  [0x04] = 0x0004, [0x05] = 0x0005, [0x06] = 0x0006, [0x07] = 0x0007,
  [0x08] = 0x0008, [0x09] = 0x0009, [0x0a] = 0x000a, [0x0b] = 0x000b,
  [0x0c] = 0x000c, [0x0d] = 0x000d, [0x0e] = 0x000e, [0x0f] = 0x000f,
  [0x10] = 0x0010, [0x11] = 0x0011, [0x12] = 0x0012, [0x13] = 0x0013,
  [0x14] = 0x0014, [0x15] = 0x0015, [0x16] = 0x0016, [0x17] = 0x0017,
  [0x18] = 0x0018, [0x19] = 0x0019, [0x1a] = 0x001a, [0x1b] = 0x001b,
  [0x1c] = 0x001c, [0x1d] = 0x001d, [0x1e] = 0x001e, [0x1f] = 0x001f,
  [0x20] = 0x0020, [0x21] = 0x0021, [0x22] = 0x0022, [0x23] = 0x0023,
  [0x24] = 0x0024, [0x25] = 0x0025, [0x26] = 0x0026, [0x27] = 0x0027,
  [0x28] = 0x0028, [0x29] = 0x0029, [0x2a] = 0x002a, [0x2b] = 0x002b,
  [0x2c] = 0x002c, [0x2d] = 0x002d, [0x2e] = 0x002e, [0x2f] = 0x002f,
  [0x30] = 0x0030, [0x31] = 0x0031, [0x32] = 0x0032, [0x33] = 0x0033,
  [0x34] = 0x0034, [0x35] = 0x0035, [0x36] = 0x0036, [0x37] = 0x0037,
  [0x38] = 0x0038, [0x39] = 0x0039, [0x3a] = 0x003a, [0x3b] = 0x003b,
  [0x3c] = 0x003c, [0x3d] = 0x003d, [0x3e] = 0x003e, [0x3f] = 0x003f,
  [0x40] = 0x0040, [0x41] = 0x0041, [0x42] = 0x0042, [0x43] = 0x0043,
  [0x44] = 0x0044, [0x45] = 0x0045, [0x46] = 0x0046, [0x47] = 0x0047,
  [0x48] = 0x0048, [0x49] = 0x0049, [0x4a] = 0x004a, [0x4b] = 0x004b,
  [0x4c] = 0x004c, [0x4d] = 0x004d, [0x4e] = 0x004e, [0x4f] = 0x004f,
  [0x50] = 0x0050, [0x51] = 0x0051, [0x52] = 0x0052, [0x53] = 0x0053,
  [0x54] = 0x0054, [0x55] = 0x0055, [0x56] = 0x0056, [0x57] = 0x0057,
  [0x58] = 0x0058, [0x59] = 0x0059, [0x5a] = 0x005a, [0x5b] = 0x005b,
  [0x5c] = 0x005c, [0x5d] = 0x005d, [0x5e] = 0x005e, [0x5f] = 0x005f,
  [0x60] = 0x0060, [0x61] = 0x0061, [0x62] = 0x0062, [0x63] = 0x0063,
  [0x64] = 0x0064, [0x65] = 0x0065, [0x66] = 0x0066, [0x67] = 0x0067,
  [0x68] = 0x0068, [0x69] = 0x0069, [0x6a] = 0x006a, [0x6b] = 0x006b,
  [0x6c] = 0x006c, [0x6d] = 0x006d, [0x6e] = 0x006e, [0x6f] = 0x006f,
  [0x70] = 0x0070, [0x71] = 0x0071, [0x72] = 0x0072, [0x73] = 0x0073,
  [0x74] = 0x0074, [0x75] = 0x0075, [0x76] = 0x0076, [0x77] = 0x0077,
  [0x78] = 0x0078, [0x79] = 0x0079, [0x7a] = 0x007a, [0x7b] = 0x007b,
  [0x7c] = 0x007c, [0x7d] = 0x007d, [0x7e] = 0x007e, [0x7f] = 0x007f,
  [0x80] = 0x0402, [0x81] = 0x0403, [0x82] = 0x201a, [0x83] = 0x0453,
  [0x84] = 0x201e, [0x85] = 0x2026, [0x86] = 0x2020, [0x87] = 0x2021,
  [0x88] = 0x20ac, [0x89] = 0x2030, [0x8a] = 0x0409, [0x8b] = 0x2039,
  [0x8c] = 0x040a, [0x8d] = 0x040c, [0x8e] = 0x040b, [0x8f] = 0x040f,
  [0x90] = 0x0452, [0x91] = 0x2018, [0x92] = 0x2019, [0x93] = 0x201c,
  [0x94] = 0x201d, [0x95] = 0x2022, [0x96] = 0x2013, [0x97] = 0x2014,
  [0x98] = 0x0098, [0x99] = 0x2122, [0x9a] = 0x0459, [0x9b] = 0x203a,
  [0x9c] = 0x045a, [0x9d] = 0x045c, [0x9e] = 0x045b, [0x9f] = 0x045f,
  [0xa0] = 0x00a0, [0xa1] = 0x040e, [0xa2] = 0x045e, [0xa3] = 0x0408,
  [0xa4] = 0x00a4, [0xa5] = 0x0490, [0xa6] = 0x00a6, [0xa7] = 0x00a7,
  [0xa8] = 0x0401, [0xa9] = 0x00a9, [0xaa] = 0x0404, [0xab] = 0x00ab,
  [0xac] = 0x00ac, [0xad] = 0x00ad, [0xae] = 0x00ae, [0xaf] = 0x0407,
  [0xb0] = 0x00b0, [0xb1] = 0x00b1, [0xb2] = 0x0406, [0xb3] = 0x0456,
  [0xb4] = 0x0491, [0xb5] = 0x00b5, [0xb6] = 0x00b6, [0xb7] = 0x00b7,
  [0xb8] = 0x0451, [0xb9] = 0x2116, [0xba] = 0x0454, [0xbb] = 0x00bb,
  [0xbc] = 0x0458, [0xbd] = 0x0405, [0xbe] = 0x0455, [0xbf] = 0x0457,
  [0xc0] = 0x0410, [0xc1] = 0x0411, [0xc2] = 0x0412, [0xc3] = 0x0413,
  [0xc4] = 0x0414, [0xc5] = 0x0415, [0xc6] = 0x0416, [0xc7] = 0x0417,
  [0xc8] = 0x0418, [0xc9] = 0x0419, [0xca] = 0x041a, [0xcb] = 0x041b,
  [0xcc] = 0x041c, [0xcd] = 0x041d, [0xce] = 0x041e, [0xcf] = 0x041f,
  [0xd0] = 0x0420, [0xd1] = 0x0421, [0xd2] = 0x0422, [0xd3] = 0x0423,
  [0xd4] = 0x0424, [0xd5] = 0x0425, [0xd6] = 0x0426, [0xd7] = 0x0427,
  [0xd8] = 0x0428, [0xd9] = 0x0429, [0xda] = 0x042a, [0xdb] = 0x042b,
  [0xdc] = 0x042c, [0xdd] = 0x042d, [0xde] = 0x042e, [0xdf] = 0x042f,
  [0xe0] = 0x0430, [0xe1] = 0x0431, [0xe2] = 0x0432, [0xe3] = 0x0433,
  [0xe4] = 0x0434, [0xe5] = 0x0435, [0xe6] = 0x0436, [0xe7] = 0x0437,
  [0xe8] = 0x0438, [0xe9] = 0x0439, [0xea] = 0x043a, [0xeb] = 0x043b,
  [0xec] = 0x043c, [0xed] = 0x043d, [0xee] = 0x043e, [0xef] = 0x043f,
  [0xf0] = 0x0440, [0xf1] = 0x0441, [0xf2] = 0x0442, [0xf3] = 0x0443,
  [0xf4] = 0x0444, [0xf5] = 0x0445, [0xf6] = 0x0446, [0xf7] = 0x0447,
  [0xf8] = 0x0448, [0xf9] = 0x0449, [0xfa] = 0x044a, [0xfb] = 0x044b,
  [0xfc] = 0x044c, [0xfd] = 0x044d, [0xfe] = 0x044e, [0xff] = 0x044f
};

static const struct gap from_idx[] =
{
  { start: 0x0000, end: 0x007f, idx:     0 },
  { start: 0x0098, end: 0x0098, idx:   -24 },
  { start: 0x00a0, end: 0x00bb, idx:   -31 },
  { start: 0x0401, end: 0x045f, idx:  -868 },
  { start: 0x0490, end: 0x0491, idx:  -916 },
  { start: 0x2013, end: 0x2026, idx: -7957 },
  { start: 0x2030, end: 0x2030, idx: -7966 },
  { start: 0x2039, end: 0x203a, idx: -7974 },
  { start: 0x20ac, end: 0x20ac, idx: -8087 },
  { start: 0x2116, end: 0x2116, idx: -8192 },
  { start: 0x2122, end: 0x2122, idx: -8203 },
  { start: 0xffff, end: 0xffff, idx:     0 }
};

static const char from_ucs4[] =
{
  '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07',
  '\x08', '\x09', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f',
  '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17',
  '\x18', '\x19', '\x1a', '\x1b', '\x1c', '\x1d', '\x1e', '\x1f',
  '\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27',
  '\x28', '\x29', '\x2a', '\x2b', '\x2c', '\x2d', '\x2e', '\x2f',
  '\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37',
  '\x38', '\x39', '\x3a', '\x3b', '\x3c', '\x3d', '\x3e', '\x3f',
  '\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47',
  '\x48', '\x49', '\x4a', '\x4b', '\x4c', '\x4d', '\x4e', '\x4f',
  '\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57',
  '\x58', '\x59', '\x5a', '\x5b', '\x5c', '\x5d', '\x5e', '\x5f',
  '\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67',
  '\x68', '\x69', '\x6a', '\x6b', '\x6c', '\x6d', '\x6e', '\x6f',
  '\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77',
  '\x78', '\x79', '\x7a', '\x7b', '\x7c', '\x7d', '\x7e', '\x7f',
  '\x98', '\xa0', '\x00', '\x00', '\x00', '\xa4', '\x00', '\xa6',
  '\xa7', '\x00', '\xa9', '\x00', '\xab', '\xac', '\xad', '\xae',
  '\x00', '\xb0', '\xb1', '\x00', '\x00', '\x00', '\xb5', '\xb6',
  '\xb7', '\x00', '\x00', '\x00', '\xbb', '\xa8', '\x80', '\x81',
  '\xaa', '\xbd', '\xb2', '\xaf', '\xa3', '\x8a', '\x8c', '\x8e',
  '\x8d', '\x00', '\xa1', '\x8f', '\xc0', '\xc1', '\xc2', '\xc3',
  '\xc4', '\xc5', '\xc6', '\xc7', '\xc8', '\xc9', '\xca', '\xcb',
  '\xcc', '\xcd', '\xce', '\xcf', '\xd0', '\xd1', '\xd2', '\xd3',
  '\xd4', '\xd5', '\xd6', '\xd7', '\xd8', '\xd9', '\xda', '\xdb',
  '\xdc', '\xdd', '\xde', '\xdf', '\xe0', '\xe1', '\xe2', '\xe3',
  '\xe4', '\xe5', '\xe6', '\xe7', '\xe8', '\xe9', '\xea', '\xeb',
  '\xec', '\xed', '\xee', '\xef', '\xf0', '\xf1', '\xf2', '\xf3',
  '\xf4', '\xf5', '\xf6', '\xf7', '\xf8', '\xf9', '\xfa', '\xfb',
  '\xfc', '\xfd', '\xfe', '\xff', '\x00', '\xb8', '\x90', '\x83',
  '\xba', '\xbe', '\xb3', '\xbf', '\xbc', '\x9a', '\x9c', '\x9e',
  '\x9d', '\x00', '\xa2', '\x9f', '\xa5', '\xb4', '\x96', '\x97',
  '\x00', '\x00', '\x00', '\x91', '\x92', '\x82', '\x00', '\x93',
  '\x94', '\x84', '\x00', '\x86', '\x87', '\x95', '\x00', '\x00',
  '\x00', '\x85', '\x89', '\x8b', '\x9b', '\x88', '\xb9', '\x99'
};
