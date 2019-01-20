sample: sample.o
	gcc -o sample sample.o

sample.o : sample.c
	gcc -c -o0 -g -Wall sample.c -o sample.o

.PHONY : clean valgrind
valgrind :
	valgrind --log-file=valgrind.log \
			--tool=memcheck --leak-check=full \
			--show-reachable=yes ./sample \
			
.clean :
	-rm -rf *.o sample

