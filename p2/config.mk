###########################################################################
#
#    #####          #######         #######         ######            ###
#   #     #            #            #     #         #     #           ###
#   #                  #            #     #         #     #           ###
#    #####             #            #     #         ######             #
#         #            #            #     #         #
#   #     #            #            #     #         #                 ###
#    #####             #            #######         #                 ###
#
#
# Please read the directions in README and in this config.mk carefully.
# Do -N-O-T- just dump things randomly in here until your project builds.
# If you do that, you run an excellent chance of turning in something
# which can't be graded.  If you think the build infrastructure is
# somehow restricting you from doing something you need to do, contact
# the course staff--don't just hit it with a hammer and move on.
#
# [Once you've read this message, please edit it out of your config.mk!!]
###########################################################################



###########################################################################
# This is the include file for the make file.
###########################################################################
# You should have to edit only this file to get things to build.
#

###########################################################################
# The method for acquiring project updates.
###########################################################################
# This should be "afs" for any Andrew machine, "web" for non-andrew machines
# and "offline" for machines with no network access.
#
# "offline" is strongly not recommended as you may miss important project
# updates.
#
UPDATE_METHOD = offline

###########################################################################
# WARNING: Do not put extraneous test programs into the REQPROGS variables.
#          Doing so will put your grader in a bad mood which is likely to
#          make him or her less forgiving for other issues.
###########################################################################

###########################################################################
# Mandatory programs whose source is provided by course staff
###########################################################################
# A list of the programs in 410user/progs which are provided in source
# form and NECESSARY FOR THE KERNEL TO RUN
#
# The idle process is a really good thing to keep here.
#
410REQPROGS = idle

###########################################################################
# Mandatory programs provided in binary form by course staff
###########################################################################
# A list of the programs in 410user/progs which are provided in binary
# form and NECESSARY FOR THE KERNEL TO RUN
#
# You may move these to 410BINPROGS to test your syscall stubs once
# they exist, but we will grade you against the binary versions.
# This should be fine.
#
410REQBINPROGS = shell init

###########################################################################
# WARNING: When we test your code, the two TESTS variables below will be
# ignored.  Your kernel MUST RUN WITHOUT THEM.
###########################################################################

###########################################################################
# Test programs provided by course staff you wish to run
###########################################################################
# A list of the test programs you want compiled in from the 410user/progs
# directory
#
410TESTS = agility_drill

###########################################################################
# Test programs you have written which you wish to run
###########################################################################
# A list of the test programs you want compiled in from the user/progs
# directory
#
STUDENTTESTS = syscall_test forkedp thread_test

###########################################################################
# Object files for your thread library
###########################################################################
THREAD_OBJS = malloc.o thread.o mutex.o thr_fork.o cond.o

###########################################################################
# Object files for your syscall wrappers
###########################################################################
SYSCALL_OBJS = set_status.o vanish.o fork.o exec.o yield.o wait.o print.o new_pages.o remove_pages.o gettid.o

###########################################################################
# Libraries!
###########################################################################
#
# Once your thread library provides all necessary parts, at least in
# dummy form, remove the '#' from the next line to build our thread-group
# library.
#
# Otherwise, you should probably not modify any of these lines.
410USER_LIBS_EARLY = libthrgrp.a
410USER_LIBS_LATE = libRNG.a libmalloc.a libstdio.a libstdlib.a libstring.a
STUDENT_LIBS_EARLY = libthread.a
STUDENT_LIBS_LATE = libsyscall.a

###########################################################################
# Details of library structure (you do NOT have to read this part!!)
###########################################################################
#  _EARLY means "specified early in the compiler command line" and so
#               can be taken to mean "can depend on all _LATE files"
#  _LATE means "specified late in the compiler command line" and so
#              might be taken as "there be daemons here"; in particular
#              these libraries may not depend on _EARLY libraries
#              or any library in the list before them.
#
# The full command line order is
#   410USER_LIBS_EARLY -- can depend on everything
#   STUDENT_LIBS_EARLY -- can depend only on _LATE libs
#   410USER_LIBS_LATE -- must not depend on _EARLY libs
#   STUDENT_LIBS_LATE -- must not depend on any other lib group
