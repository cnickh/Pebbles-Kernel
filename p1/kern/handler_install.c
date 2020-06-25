/** @file handler_install.c
 *
 *  @brief Handler installation function
 *
 *  Edit this file to allow your kernel to initialize and install handlers
 *
 *  Declared in 410_reqs.h
 *
 *  @author Charles Nick Henry
 *  @bug None known
 **/

#include <410_reqs.h>
#include <stdio.h> //strictly for debug purposes
#include <interrupts.h> //void *sidt(), idt location
#include <timer_defines.h> //timer specific constants
#include <x86/pio.h> //I/O ports communication
#include <x86/seg.h> //Memory Segment selections
#include <handler_asm.h> //Wrapper functions
#include <keyboard_driver.h> //functions for management of keyboard interrupts

extern void tick(unsigned int numTicks);

#define TIMER_INTERVAL 0.01

unsigned int numTicks = 0;

/*
Define interrupt for keyboard and timer
Make an entry in IDT, there is a description in this table for each interrupt
A descriptor to describe how to resolve the interrupt and where the handler is located

IDT entries have three types (gate = transition to new code (gate to procedure))
  - task gate, won't be using
  - interrupt gate, accesses interrupt handler through this gate and clears flags to defer other interrupts
  - **trap gate, does not defer other interrupts, P.151

Each 'gate'/entry is a 64-bit descriptor broken in two 32-bits parts
IDT base @ sidt()

                            -->-- (Traps + Exceptions) --- (Privaleged code/mode)
                          /
       PIC              CPU
    IRQ-  -\           /
    IRQ-  ----->----- CPU --->--(Interupt Vector)--->--IDT  <---This file makes
    IRQ-  -/           \                                |      entries here (IDT)
                        -----<---Handling-Code----<-----


*/
void timer_handler(){
  tick(numTicks++);
  outb(INT_CTL_REG, INT_CTL_DONE); //Tell PIC we have procesed its interrupt
}

void keyboard_handler(){
  int ch = inb(KEYBOARD_PORT); //Get keystroke from i/o port
  add_to_kbuf(ch); //put keystroke in buffer
  outb(INT_CTL_REG,INT_CTL_DONE); //Tell PIC we have procesed its interrupt
}

int handler_install(void)
{

  void *idt_base = sidt(); //Get base address of IDT
  printf("# handler_install() executing!\n# IDT @ (%08x)\n",(unsigned int)idt_base);

  /*TIMER INSTALL*/
  unsigned int timer_idt_addr = (unsigned int)idt_base + (TIMER_IDT_ENTRY*8);

  printf("# TIMER_ENTRY @ (%08x)\n", timer_idt_addr);


  /*Offset 15..0*/
  unsigned int timer_lwraddr = (unsigned int)timer_handler_asm & 0x0000FFFF;
  /*Offset 31..15*/
  unsigned int timer_uppraddr = (unsigned int)timer_handler_asm >> (1 << 4);

  /*Segment_Select | Offset_15..0*/
  unsigned int lsb_entry = (KERNEL_CS_SEGSEL << (1 << 4)) | timer_lwraddr;
  /*Offet_31..15 | P=1 | DPL=00 | 0D111, D=1 | 000 | misc (4..0)*/
  unsigned int msb_entry = (timer_uppraddr << (1 << 4)) | 0x00008F00;

  *((unsigned int *)timer_idt_addr) = lsb_entry; //write lower 32-bits
  *((unsigned int *)timer_idt_addr +1) = msb_entry; //write upper 32-bits

  /*Set-up timer i/o registers*/
  outb(TIMER_MODE_IO_PORT,TIMER_SQUARE_WAVE); //Set timer mode ig

  unsigned int time_period = TIMER_RATE * TIMER_INTERVAL;
  unsigned int time_period_lwr = time_period & 0x00FF;
  unsigned int time_period_uppr = time_period & 0xFF00;

  //Send time between interrupts (2-byte quantity)
  outb(TIMER_PERIOD_IO_PORT, time_period_lwr);
  outb(TIMER_PERIOD_IO_PORT, time_period_uppr);
  /*TIMER INSTALL COMPLETE*/


  /*KEYBOARD INSTALL*/
  unsigned int keyboard_idt_addr = (unsigned int)idt_base + (KEY_IDT_ENTRY*8);

  unsigned int keyboard_lwraddr = (unsigned int)keyboard_handler_asm & 0x0000FFFF;
  unsigned int keyboard_uppraddr = (unsigned int)keyboard_handler_asm >> (1 << 4);

  unsigned int key_lsb = (KERNEL_CS_SEGSEL << (1 << 4)) | keyboard_lwraddr;
  unsigned int key_msb = (keyboard_uppraddr << (1 << 4)) | 0x00008F00;

  *((unsigned int *)keyboard_idt_addr) = key_lsb; //write lower 32-bits
  *((unsigned int *)keyboard_idt_addr+1) = key_msb; //write upper 32-bits

  init_kbuf(); //Initialize keyboard buffer

  /*KEYBOARD INSTALL COMPLETE*/

  return 0;
}
