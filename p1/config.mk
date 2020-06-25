# To build your project, edit this file--not the Makefile!

##################################################
# How to acquire updates.
##################################################
#
# afs - fastest on Andrew machines
# web - will probably work on non-Andrew machines
# offline - if machine has no network access
#
# WARNING - if you miss a staff-issued update
# because you were using "offline", you are
# responsible for the outcome.
#
##################################################
UPDATE_METHOD = offline

##################################################
# Object files from kern/ which the game AND the
# console tester should link against
##################################################
#
COMMON_OBJS = console.o handler_install.o handler_asm.o keyboard_driver.o

##################################################
# Object files from 410kern/ for just the game
##################################################
#
410_GAME_OBJS = othello_bot.o

##################################################
# Object files from kern/ for just the game
##################################################
#
KERN_GAME_OBJS = tick.o game_kern_main.o

##################################################
# Object files from 410kern/ for just the tester
##################################################
#
410TEST_OBJS = 410_test.o 410_tick.o

#
# A list of the library objects you would like included in your kernel
# YOU PROBABLY DO NOT WANT TO MODIFY THIS!  It is provided for those
# who might wish to rewrite some of this functionality; if you are not
# in that class (or think that class is crazy) leave this alone!
#
410KERNEL_LIBS = liblmm.a libkerndebug.a libstdio.a libstdlib.a \
                  libstring.a libx86.a libRNG.a
