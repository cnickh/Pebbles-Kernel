CC = /usr/bin/gcc -m32
AR = ar
LDFLAGS = -static
CFLAGS = -Wall -gstabs -O0
PRINT = enscript
PRINTFLAGS = -2rG -fHelvetica7 -FHelvetica-Bold10
DOC = doxygen
AFS_DIR = /afs/cs.cmu.edu/academic/class/15410-s07/Web/update

include traceback.mk

TRACEBACK_OBJS = traceback_globals.o $(MY_TRACEBACK_OBJS)

.PHONY: update query_update html_doc print clean verify

all: query_update $(TEST_PROGS)

#doupdate:
#	./update.pl $(UPDATE_METHOD)

update:
	./update.sh $(UPDATE_METHOD)

query_update:
	./update.sh $(UPDATE_METHOD) query

%.o: %.c
	$(CC) -c -o $(*F).o $(CFLAGS) $(LDFLAGS) $(*F).c

%.o: %.s
	@echo "You should use the .S file extension rather than .s"
	@echo ".s does not support precompiler directives (like #include)"
	@false

%.o: %.S
	$(CC) -c -o $(*F).o $(CFLAGS) $(LDFLAGS) $(*F).S

libtraceback.a: $(TRACEBACK_OBJS)
	$(AR) rc libtraceback.a $(TRACEBACK_OBJS)

$(TEST_PROGS) verify_test: %: %.o libtraceback.a
	$(CC) -o $@ $@.o -L. libtraceback.a $(CFLAGS) $(LDFLAGS) $(LIBS)
	perl ./symtabgen.pl $@

html_doc:
	$(DOC) doxygen.conf

print:
	$(PRINT) $(PRINTFLAGS) -p traceback.ps $(SRCS) $(HDRS)

clean:
	rm -rf *.o *~ libtraceback.a $(TEST_PROGS) verify_test

verify: verify_test
	./verify_test # diff -bB sample.output - 2>&1 > /dev/null
