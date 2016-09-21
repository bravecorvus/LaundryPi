all: bin.exec write.exec

bin.exec: bin.cpp
	g++ -g -Wall -Werror -Wextra $< -o $@
	chmod a+x $@
	chmod g+rw $@

write.exec: write.cpp
	g++ -g -Wall -Wextra -Werror $< -o $@
	chmod a+x $@
	chmod g+rw $@

clean:
	rm -f *.exec *.o
