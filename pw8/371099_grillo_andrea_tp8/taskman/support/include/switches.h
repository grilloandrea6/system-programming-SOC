#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED

#ifdef __GECKO5__
#define SWITCHES_LEFT 0x20
#define SWITCHES_RIGHT 0x40
#define SWITCHES_UP 0x200
#define SWITCHES_DOWN 0x100
#define SWITCHES_RESET 0x80
#define SWITCHES_ZOOMIN 0x08
#define SWITCHES_ZOOMOUT 0x02
#else
#define SWITCHES_LEFT 0x2
#define SWITCHES_RIGHT 0x1
#define SWITCHES_UP 0x20
#define SWITCHES_DOWN 0x10
#define SWITCHES_RESET 0x0
#define SWITCHES_ZOOMIN 0x04
#define SWITCHES_ZOOMOUT 0x08
#endif

#define SWITCHES_INDEX_DIP_STATE 0
#define SWITCHES_INDEX_DIP_IRQ1 1
#define SWITCHES_INDEX_DIP_IRQ2 2
#define SWITCHES_INDEX_SW_STATE 3
#define SWITCHES_INDEX_SW_IRQ1 4
#define SWITCHES_INDEX_SW_IRQ2 5
#define SWITCHES_INDEX_IRQ_LATENCY 6
#define SWITCHES_INDEX_IRW_CLEAR 7

#define SWITCHES_IRQ_BUTTONS (1 << 3)

#endif /* BUTTONS_H_INCLUDED */
