#ifndef _LCORE_VGA_H
#define _LCORE_VGA_H

#define VGA_MAX_ROW			30
#define VGA_MAX_COL			80

#define VGA_TAB_LEN			4

/*
 * top of the screen(28lines) is used to log input/output on the console
 * bottom of the screen(2lines) is used to display system realtime info
 */
#define VGA_ROW_SYSTEM		2
#define VGA_ROW_CONSOLE		(VGA_MAX_ROW - VGA_ROW_SYSTEM)

extern unsigned int cursor_row;
extern unsigned int cursor_col;
extern unsigned short *vga_buffer;

extern void init_vga(unsigned int buffer);
extern void clean_screen(unsigned int scope);
extern void set_cursor(unsigned short row, unsigned short col);
extern void scroll_screen(unsigned int scope);
extern void put_char_ex(unsigned int ch, unsigned int bg, unsigned int fg, unsigned int row, unsigned int col, unsigned int scope);
extern void put_char(unsigned int ch, unsigned int bg, unsigned int fg, unsigned int scope);

#endif

