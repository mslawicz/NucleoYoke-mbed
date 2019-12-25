
/*
 *
 * new Font
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : tahoma11.h
 * Date                : 22.02.2019
 * Font size in bytes  : 5437
 * Font width          : 10
 * Font height         : 11
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#ifndef TAHOMA_11_B_H
#define TAHOMA_11_B_H

const uint8_t FontTahoma11b[] =
{
    0x15, 0x3D, // size
    0x0A, // width
    0x0B, // height
    0x20, // first char
    0x60, // char count

    // char widths
    0x00, 0x02, 0x03, 0x06, 0x06, 0x0B, 0x07, 0x01, 0x04, 0x04, 0x05, 0x05,
    0x01, 0x03, 0x02, 0x04, 0x06, 0x04, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x02, 0x02, 0x06, 0x05, 0x06, 0x05, 0x09, 0x07, 0x06, 0x06,
    0x06, 0x05, 0x05, 0x06, 0x07, 0x04, 0x04, 0x06, 0x05, 0x08, 0x06, 0x07,
    0x06, 0x07, 0x06, 0x05, 0x06, 0x06, 0x06, 0x08, 0x06, 0x06, 0x05, 0x04,
    0x04, 0x04, 0x06, 0x06, 0x02, 0x05, 0x05, 0x04, 0x05, 0x05, 0x04, 0x05,
    0x05, 0x02, 0x03, 0x05, 0x02, 0x08, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04,
    0x03, 0x05, 0x05, 0x07, 0x05, 0x05, 0x04, 0x06, 0x02, 0x06, 0x06, 0x07,

    // font data
    0x7C, 0x7C, 0x20,
    0x20, // 33
    0x0E, 0x00, 0x0E, 0x00, 0x00,
    0x00, // 34
    0x50, 0xFC, 0x50, 0x50, 0xFC, 0x50, 0x00, 0x20, 0x00, 0x00, 0x20,
    0x00, // 35
    0x98, 0x3C, 0xE4, 0x3E, 0xE4, 0xC8, 0x00, 0x20, 0x60, 0x20, 0x20,
    0x00, // 36
    0x18, 0x3C, 0x24, 0xBC, 0x58, 0x20, 0xD0, 0xE8, 0x20, 0xE0, 0xC0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20,
    0x00, // 37
    0xD8, 0xFC, 0x24, 0x7C, 0xD8, 0xC0, 0x30, 0x00, 0x20, 0x20, 0x20, 0x00,
    0x20,
    0x20, // 38
    0x0E,
    0x00, // 39
    0xF8, 0xFC, 0x06, 0x02, 0x20, 0x60, 0xC0,
    0x80, // 40
    0x02, 0x06, 0xFC, 0xF8, 0x80, 0xC0, 0x60,
    0x20, // 41
    0x0A, 0x04, 0x1F, 0x04, 0x0A, 0x00, 0x00, 0x00, 0x00,
    0x00, // 42
    0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00,
    0x00, // 43
    0x80,
    0x60, // 44
    0x20, 0x20, 0x20, 0x00, 0x00,
    0x00, // 45
    0x80, 0x80, 0x20,
    0x20, // 46
    0x00, 0xC0, 0x38, 0x06, 0x60, 0x00, 0x00,
    0x00, // 47
    0xF8, 0xFC, 0x04, 0x04, 0xFC, 0xF8, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x00, // 48
    0x08, 0xFC, 0xFC, 0x00, 0x20, 0x20, 0x20,
    0x20, // 49
    0x18, 0x84, 0xC4, 0x64, 0x3C, 0x18, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, // 50
    0x88, 0x04, 0x24, 0x24, 0xFC, 0xD8, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x00, // 51
    0x60, 0x50, 0x48, 0xFC, 0xFC, 0x40, 0x00, 0x00, 0x00, 0x20, 0x20,
    0x00, // 52
    0x9C, 0x1C, 0x14, 0x14, 0xF4, 0xE4, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x00, // 53
    0xF8, 0xFC, 0x24, 0x24, 0xE4, 0xC0, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x00, // 54
    0x04, 0x04, 0xC4, 0xF4, 0x3C, 0x0C, 0x00, 0x00, 0x20, 0x20, 0x00,
    0x00, // 55
    0xD8, 0xFC, 0x24, 0x24, 0xFC, 0xD8, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x00, // 56
    0x18, 0x3C, 0x24, 0xA4, 0xFC, 0x78, 0x00, 0x20, 0x20, 0x20, 0x00,
    0x00, // 57
    0xB0, 0xB0, 0x20,
    0x20, // 58
    0xB0, 0x30, 0x60,
    0x00, // 59
    0x60, 0x60, 0x90, 0x90, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x20, // 60
    0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00,
    0x00, // 61
    0x08, 0x08, 0x90, 0x90, 0x60, 0x60, 0x20, 0x20, 0x00, 0x00, 0x00,
    0x00, // 62
    0x08, 0x44, 0x64, 0x3C, 0x18, 0x00, 0x20, 0x20, 0x00,
    0x00, // 63
    0xF0, 0x08, 0x64, 0xF4, 0x94, 0x74, 0xF4, 0x88, 0x70, 0x00, 0x20, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x00,
    0x00, // 64
    0xC0, 0xF0, 0x7C, 0x4C, 0x7C, 0xF0, 0xC0, 0x20, 0x20, 0x00, 0x00, 0x00,
    0x20,
    0x20, // 65
    0xFC, 0xFC, 0x24, 0x24, 0xFC, 0xD8, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x00, // 66
    0xF8, 0xFC, 0x04, 0x04, 0x04, 0x88, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x00, // 67
    0xFC, 0xFC, 0x04, 0x04, 0xFC, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x00, // 68
    0xFC, 0xFC, 0x24, 0x24, 0x04, 0x20, 0x20, 0x20, 0x20,
    0x20, // 69
    0xFC, 0xFC, 0x24, 0x24, 0x04, 0x20, 0x20, 0x00, 0x00,
    0x00, // 70
    0xF8, 0xFC, 0x04, 0x24, 0xE4, 0xE8, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x20, // 71
    0xFC, 0xFC, 0x20, 0x20, 0x20, 0xFC, 0xFC, 0x20, 0x20, 0x00, 0x00, 0x00,
    0x20,
    0x20, // 72
    0x04, 0xFC, 0xFC, 0x04, 0x20, 0x20, 0x20,
    0x20, // 73
    0x00, 0x04, 0xFC, 0xFC, 0x20, 0x20, 0x20,
    0x00, // 74
    0xFC, 0xFC, 0x70, 0xD8, 0x8C, 0x04, 0x20, 0x20, 0x00, 0x00, 0x20,
    0x20, // 75
    0xFC, 0xFC, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x20, // 76
    0xFC, 0x1C, 0x38, 0x70, 0x30, 0x18, 0xFC, 0xFC, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x20,
    0x20, // 77
    0xFC, 0x1C, 0x38, 0x70, 0xE0, 0xFC, 0x20, 0x00, 0x00, 0x00, 0x00,
    0x20, // 78
    0xF8, 0xFC, 0x04, 0x04, 0x04, 0xFC, 0xF8, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x20,
    0x00, // 79
    0xFC, 0xFC, 0x44, 0x44, 0x7C, 0x38, 0x20, 0x20, 0x00, 0x00, 0x00,
    0x00, // 80
    0xF8, 0xFC, 0x04, 0x04, 0x04, 0xFC, 0xF8, 0x00, 0x20, 0x20, 0x60, 0xE0,
    0xA0,
    0x80, // 81
    0xFC, 0xFC, 0x64, 0xE4, 0xBC, 0x18, 0x20, 0x20, 0x00, 0x00, 0x20,
    0x20, // 82
    0x98, 0x3C, 0x74, 0xE4, 0xC8, 0x00, 0x20, 0x20, 0x20,
    0x00, // 83
    0x04, 0x04, 0xFC, 0xFC, 0x04, 0x04, 0x00, 0x00, 0x20, 0x20, 0x00,
    0x00, // 84
    0xFC, 0xFC, 0x00, 0x00, 0xFC, 0xFC, 0x00, 0x20, 0x20, 0x20, 0x20,
    0x00, // 85
    0x1C, 0x7C, 0xE0, 0xE0, 0x7C, 0x1C, 0x00, 0x00, 0x20, 0x20, 0x00,
    0x00, // 86
    0x7C, 0xFC, 0x80, 0x7C, 0x7C, 0x80, 0xFC, 0x7C, 0x00, 0x20, 0x20, 0x00,
    0x00, 0x20, 0x20,
    0x00, // 87
    0x8C, 0xDC, 0x70, 0x70, 0xDC, 0x8C, 0x20, 0x20, 0x00, 0x00, 0x20,
    0x20, // 88
    0x0C, 0x3C, 0xF0, 0xF0, 0x3C, 0x0C, 0x00, 0x00, 0x20, 0x20, 0x00,
    0x00, // 89
    0xC4, 0xE4, 0x74, 0x3C, 0x1C, 0x20, 0x20, 0x20, 0x20,
    0x20, // 90
    0xFE, 0xFE, 0x02, 0x02, 0xE0, 0xE0, 0x80,
    0x80, // 91
    0x06, 0x18, 0xE0, 0x00, 0x00, 0x00, 0x00,
    0x60, // 92
    0x02, 0x02, 0xFE, 0xFE, 0x80, 0x80, 0xE0,
    0xE0, // 93
    0x10, 0x08, 0x04, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, // 95
    0x02, 0x04, 0x00,
    0x00, // 96
    0x80, 0xD0, 0x50, 0xF0, 0xE0, 0x00, 0x20, 0x20, 0x20,
    0x20, // 97
    0xFE, 0xFE, 0x10, 0xF0, 0xE0, 0x20, 0x20, 0x20, 0x20,
    0x00, // 98
    0xE0, 0xF0, 0x10, 0x10, 0x00, 0x20, 0x20,
    0x20, // 99
    0xE0, 0xF0, 0x10, 0xFE, 0xFE, 0x00, 0x20, 0x20, 0x20,
    0x20, // 100
    0xE0, 0xF0, 0x50, 0x70, 0x60, 0x00, 0x20, 0x20, 0x20,
    0x20, // 101
    0xFC, 0xFE, 0x12, 0x02, 0x20, 0x20, 0x00,
    0x00, // 102
    0xE0, 0xF0, 0x10, 0xF0, 0xF0, 0x00, 0xA0, 0xA0, 0xE0,
    0x60, // 103
    0xFE, 0xFE, 0x10, 0xF0, 0xE0, 0x20, 0x20, 0x00, 0x20,
    0x20, // 104
    0xF4, 0xF4, 0x20,
    0x20, // 105
    0x10, 0xF4, 0xF4, 0x80, 0xE0,
    0x60, // 106
    0xFE, 0xFE, 0xE0, 0xB0, 0x10, 0x20, 0x20, 0x00, 0x20,
    0x20, // 107
    0xFE, 0xFE, 0x20,
    0x20, // 108
    0xF0, 0xF0, 0x10, 0xF0, 0xE0, 0x10, 0xF0, 0xE0, 0x20, 0x20, 0x00, 0x20,
    0x20, 0x00, 0x20,
    0x20, // 109
    0xF0, 0xF0, 0x10, 0xF0, 0xE0, 0x20, 0x20, 0x00, 0x20,
    0x20, // 110
    0xE0, 0xF0, 0x10, 0xF0, 0xE0, 0x00, 0x20, 0x20, 0x20,
    0x00, // 111
    0xF0, 0xF0, 0x10, 0xF0, 0xE0, 0xE0, 0xE0, 0x20, 0x20,
    0x00, // 112
    0xE0, 0xF0, 0x10, 0xF0, 0xF0, 0x00, 0x20, 0x20, 0xE0,
    0xE0, // 113
    0xF0, 0xF0, 0x20, 0x30, 0x20, 0x20, 0x00,
    0x00, // 114
    0x20, 0x70, 0xD0, 0x90, 0x20, 0x20, 0x20,
    0x00, // 115
    0xF8, 0xF8, 0x10, 0x00, 0x20,
    0x20, // 116
    0xF0, 0xF0, 0x00, 0xF0, 0xF0, 0x00, 0x20, 0x20, 0x20,
    0x20, // 117
    0x30, 0xF0, 0xC0, 0xF0, 0x30, 0x00, 0x00, 0x20, 0x00,
    0x00, // 118
    0x70, 0xF0, 0x80, 0x60, 0x80, 0xF0, 0x70, 0x00, 0x20, 0x20, 0x00, 0x20,
    0x20,
    0x00, // 119
    0xB0, 0xF0, 0x40, 0xF0, 0xB0, 0x20, 0x20, 0x00, 0x20,
    0x20, // 120
    0x70, 0xF0, 0x80, 0xF0, 0x70, 0x00, 0xC0, 0xE0, 0x20,
    0x00, // 121
    0x90, 0xD0, 0x70, 0x30, 0x20, 0x20, 0x20,
    0x20, // 122
    0x20, 0x20, 0xFC, 0xDE, 0x02, 0x02, 0x00, 0x00, 0x60, 0xE0, 0x80,
    0x80, // 123
    0xFE, 0xFE, 0xE0,
    0xE0, // 124
    0x02, 0x02, 0xDE, 0xFC, 0x20, 0x20, 0x80, 0x80, 0xE0, 0x60, 0x00,
    0x00, // 125
    0xC0, 0x20, 0x60, 0xC0, 0x80, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, // 126
    0xFC, 0x04, 0x04, 0x04, 0x04, 0x04, 0xFC, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20 // 127
};

#endif
