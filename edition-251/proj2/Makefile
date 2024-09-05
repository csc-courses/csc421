#
# Name: bjr
# Date: 31 aug 2024
# 
# Note: Makefiles begin with a capital M
#   Indentation MUST be with a tab
#
# 

COPTS=

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m

F= virtmem
G=

build:
	@echo read the source

chatter-cc: chatter.c $F-sub.o $F.h
	cc ${COPTS} -o chatter $F-sub.o $<

demand-cc: demand.c $F-sub.o $F.h
	cc ${COPTS} -o demand $F-sub.o $<

$F-sub.o: $F-sub$G.c $F.h
	cc ${COPTS} -c -o $@ $<
	
test0: chatter-cc
	./chatter > test-out.txt
	diff  test-out.txt chatter.ref
	@echo "*** ${GREEN}PASSED the test ${NC}***"

demand: demand-cc
	./demand -vv

test1-txt:
	echo "0" | head -c 1 > test-in.txt
	cat tell-tale.txt | head -c 400 >> test-in.txt
	echo "" >> test-in.txt
	echo "1" | head -c 1 >> test-in.txt
	cat the-stranger.txt | head -c 400 >> test-in.txt
	echo "" >> test-in.txt
	
test2-txt:
	make test1-txt
	echo "0" | head -c 1 >> test-in.txt
	cat tell-tale.txt | head -c 800 | tail -c 400 >> test-in.txt
	echo "" >> test-in.txt
	echo "1" | head -c 1 >> test-in.txt
	cat the-stranger.txt | head -c 800 | tail -c 400 >> test-in.txt
	echo "" >> test-in.txt
	
test1: test1-txt demand-cc
	cat test-in.txt | ./demand > test-out.txt
	hexdump -C test-out.txt
	diff  test-out.txt demand1.ref
	@echo "*** ${GREEN}PASSED the test ${NC}***"

test2: test2-txt demand-cc
	cat test-in.txt | ./demand > test-out.txt
	hexdump -C test-out.txt
	diff  test-out.txt demand2.ref
	@echo "*** ${GREEN}PASSED the test ${NC}***"

bitshift-experiment: bitshift-experiment.c
	cc ${COPTS} -o bitshift-experiment $<
	./bitshift-experiment

clean:
	-rm $F-sub.o chatter demand test-out.txt test-in.txt bitshift-experiment


