/**
 * The 15-410 kernel project
 *   interrupts.h
 *
 * Prototype for function that
 * grabs the address of the IDT
 * in memory.
 */

#ifndef INTR_MANAGE_H
#define INTR_MANAGE_H

#define INT_CTL_REG 0x20
#define INT_CTL_DONE 0x20

#ifndef ASSEMBLER

void *sidt(void);

#endif /* ASSEMBLER */

#endif /* INTR_MANAGE_H */
