#
# This is the include file for the make file.
# You should only have to edit this file to get things to build.
#

#
# The object files that should be linked into the traceback library
# go here
#
MY_TRACEBACK_OBJS = traceback.o asm.o

#
# Specifies the method for acquiring and project updates. This should be
# "afs" for any andrew machine, "web" for non-andrew machines and
# "offline" for machines with no network access.
#
# "offline" is strongly not recommended as you may miss important project
# updates.
#
UPDATE_METHOD = offline

#
# Any test programs that use the traceback function go here
#
TEST_PROGS = simple_test evil_test voidstar_test

#
# Any libs that are necessary for your test programs go here
#
# NOTE: You probably don't need to put anything here, but if
# you do it MUST be of the form "-lfoo".  You must NOT name
# a source file in LIBS!!
#
LIBS =
