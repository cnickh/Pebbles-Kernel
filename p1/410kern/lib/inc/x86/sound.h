/**
 * The 15-410 Reference Kernel
 * @name sound.h
 *
 * Function for using the PC Speaker.
 *
 * @author Zachary Anderson(zra)
 */

#ifndef _SOUND_H
#define _SOUND_H

#define PITCH_LC  9121
#define PITCH_LCS 8609
#define PITCH_LD  8126
#define PITCH_LDS 7670
#define PITCH_LE  7239
#define PITCH_LF  6833
#define PITCH_LFS 6449
#define PITCH_LG  6087
#define PITCH_LGS 5746
#define PITCH_LA  5423
#define PITCH_LAS 5119
#define PITCH_LB  4831
#define PITCH_C   4560
#define PITCH_CS  4304
#define PITCH_D   4063
#define PITCH_DS  3834
#define PITCH_E   3619
#define PITCH_F   3416
#define PITCH_FS  3224
#define PITCH_G   3043
#define PITCH_GS  2873
#define PITCH_A   2711
#define PITCH_AS  2559
#define PITCH_B   2415
#define PITCH_HC  2280
#define PITCH_HCS 2152
#define PITCH_HD  2031
#define PITCH_HDS 1917
#define PITCH_HE  1809
#define PITCH_HF  1715
#define PITCH_HFS 1612
#define PITCH_HG  1521
#define PITCH_HGS 1436
#define PITCH_HA  1355
#define PITCH_HAS 1292
#define PITCH_HB  1207
#define PITCH_HHC 1140

void spkr_on( unsigned int pitch );
void spkr_off();

#endif /* _SOUND_H */
