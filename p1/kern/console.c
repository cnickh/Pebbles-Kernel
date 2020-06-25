/** @file console.c
 *  @brief A console driver.
 *
 *  @author Charles Nick Henry
 *  @bug None known
 */

#include <console.h>
#include <x86/pio.h>

#define GET_OFFSET(ptr) (((unsigned int)ptr - CONSOLE_MEM_BASE)/2)

char *curse = (char *)CONSOLE_MEM_BASE;
int console_color = BGND_BLACK | FGND_GREEN;
unsigned int MAX_MEM = CONSOLE_MEM_BASE + CONSOLE_WIDTH*CONSOLE_HEIGHT*2;
short hide_curse = 0;

int putbyte( char ch )
{
  switch(ch){

    case '\n': //Set curse on next line
    curse =
    (char *)((2*CONSOLE_WIDTH + (unsigned int)curse) - 2*(GET_OFFSET(curse) % CONSOLE_WIDTH));
    break;

    case '\r'://Put curse at start of current line
    curse =
    (char *)((unsigned int)curse - 2*(GET_OFFSET(curse) % CONSOLE_WIDTH));

    break;

    case '\b':
    curse -=2;
    *curse = 0x20;
    *(curse +1) = console_color;
    break;

    default:
    *curse = ch;
    *(curse +1) = console_color;
    curse+=2;
    break;

  }

  if(!hide_curse) show_cursor();

  return 0;
}

void
putbytes( const char *s, int len )
{
  for(int i = 0; i < len; i++){
    putbyte(s[i]);
  }
}

int
set_term_color( int color )
{
  console_color = color;
  return 0;
}

void
get_term_color( int *color )
{
  *color = console_color;
}

int
set_cursor( int row, int col )
{
  curse = (char *)(CONSOLE_MEM_BASE + 2*(col + row*CONSOLE_WIDTH));
  return 0;
}

void
get_cursor( int *row, int *col )
{
  *row = (unsigned int)curse / CONSOLE_WIDTH;
  *col =(unsigned int)curse % CONSOLE_WIDTH;
}

void
hide_cursor()
{
  hide_curse = 1;
  outb(CRTC_IDX_REG, CRTC_CURSOR_LSB_IDX); //tell crtc we want to edit lsb
  outb(CRTC_DATA_REG, 0x0001); //edit lsb
  outb(CRTC_IDX_REG,CRTC_CURSOR_MSB_IDX);  //tell crtc we want to edit msb
  outb(CRTC_DATA_REG, 0xB800); //edit msb
}

void
show_cursor()
{
  hide_curse = 0;
  unsigned int offset = GET_OFFSET(curse);
  unsigned int curse_lsb = offset & 0xff;//Get lsb from curse
  outb(CRTC_IDX_REG, CRTC_CURSOR_LSB_IDX); //tell crtc we want to edit lsb
  outb(CRTC_DATA_REG, curse_lsb); //edit lsb

  unsigned int curse_msb = offset >> (1 << 3);//Get msb from curse
  outb(CRTC_IDX_REG,CRTC_CURSOR_MSB_IDX);  //tell crtc we want to edit msb
  outb(CRTC_DATA_REG, curse_msb); //edit msb
}

void
clear_console()
{
  unsigned int i = CONSOLE_MEM_BASE;
  for(;i<MAX_MEM; i++){
    if((i-CONSOLE_MEM_BASE) % 160 == 0){ *(char *)i = '#';}
    else if(i % 2 == 0){ *(char *)i = 0x20;}
    else {*(char *)i = console_color;}
  }
}

void
draw_char( int row, int col, int ch, int color )
{
  *(char *)(CONSOLE_MEM_BASE + 2*(col + row*CONSOLE_WIDTH)) = ch;
  *(char *)(CONSOLE_MEM_BASE + 2*(col + row*CONSOLE_WIDTH + 1)) = color;
}

char
get_char( int row, int col )
{
  return *(char *)(CONSOLE_MEM_BASE + 2*(col + row*CONSOLE_WIDTH));
}
