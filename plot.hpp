#pragma once
#include "common.hpp"
#include <mculib/small_function.hpp>

#ifndef DISPLAY_ST7796
#define LCD_WIDTH                   320
#define LCD_HEIGHT                  240
// Offset of plot area
#define OFFSETX 10
#define OFFSETY  0
// WIDTH better be n*(POINTS_COUNT-1)
#define WIDTH  300
// HEIGHT = 8*GRIDY
#define HEIGHT 232
//#define NGRIDY 10
#define NGRIDY 8
#define FREQUENCIES_XPOS1 OFFSETX
#define FREQUENCIES_XPOS2 206
#define FREQUENCIES_XPOS3 135
#define FREQUENCIES_YPOS  (240-7)
#else
#define LCD_WIDTH                   480
#define LCD_HEIGHT                  320
// Offset of plot area
#define OFFSETX 15
#define OFFSETY  0
// WIDTH better be n*(POINTS_COUNT-1)
#define WIDTH  455
// HEIGHT = 8*GRIDY
#define HEIGHT 304
//#define NGRIDY 10
#define NGRIDY 8
#define FREQUENCIES_XPOS1 OFFSETX
#define FREQUENCIES_XPOS2 320
#define FREQUENCIES_XPOS3 200
#define FREQUENCIES_YPOS  (320-12)
#endif

// GRIDX calculated depends from frequency span
//#define GRIDY 29
#define GRIDY (HEIGHT / NGRIDY)

// Plot area size and left offset
#define CELLOFFSETX 5
#define AREA_WIDTH_NORMAL  (CELLOFFSETX + WIDTH  + 1 + 4)
#define AREA_HEIGHT_NORMAL (              HEIGHT + 1)

// Smith/polar chart
#define P_CENTER_X (CELLOFFSETX + WIDTH/2)
#define P_CENTER_Y (HEIGHT/2)
#define P_RADIUS   (HEIGHT/2)

#ifdef __USE_LC_MATCHING__
// X and Y offset to L/C match text
 #define STR_LC_MATH_X      (OFFSETX +  0)
// Better be aligned by cell
 #define STR_LC_MATH_Y      (OFFSETY + 32)
// 1/3 Width of text (need 3 column for data)
 #define STR_LC_MATH_WIDTH  (FONT_WIDTH * 10)
// String Height (need 2 + 0..4 string)
 #define STR_LC_MATH_HEIGHT (FONT_STR_HEIGHT + 2)
#endif

extern int area_width;
extern int area_height;

// for debugging plots
extern bool plot_checkerBoard; // draw a checkerboard pattern that indicates where the cells are
extern bool plot_shadeCells; // shade all drawn cells from now on

// this function is called to determine frequency in hz at a marker point
extern small_function<freqHz_t(int index)> plot_getFrequencyAt;

// this function is called periodically during plotting and can be used
// to process events in the event queue.
extern small_function<void()> plot_tick;

void plot_init(void);

// mark a cell for redraw. x: 0 to 15; y: 0 to 7
//void mark_map(int x, int y);

// cancel ongoing draw operations further up the stack
void plot_cancel();
// enable/disable draw_all()
void enable_redraw(bool enable);

void recalculate_grid(void);
void update_grid(void);
void request_to_redraw_grid(void);
void redraw_frame(void);
//void redraw_all(void);
void request_to_draw_cells_behind_menu(void);
void request_to_draw_cells_behind_numeric_input(void);
void request_to_redraw_marker(int marker);
void redraw_marker(int marker);
void trace_get_info(int t, char *buf, int len);
float groupdelay_from_array(int i, complexf array[SWEEP_POINTS_MAX]);
void plot_into_index(complexf measured[2][SWEEP_POINTS_MAX]);
void force_set_markmap(void);
void draw_all(bool flush);
void draw_all_cells(bool flush_markmap);
void draw_frequencies(void);
void draw_cal_status(void);

void markmap_all_markers(void);

int distance_to_index(int8_t t, uint16_t idx, int16_t x, int16_t y);
int search_nearest_index(int x, int y, int t);


int marker_search(MarkerSearchModes mode);
int marker_search_dir(MarkerSearchModes mode, int from, int dir);
