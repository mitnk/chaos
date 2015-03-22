.DEFAULT_GOAL := hello

objects = hello.o abc.o

run: hello
	./hello

hello:
	cc -o hello hello.c

.PHONY: clean
clean:
	@rm -f hello $(objects)
ifeq ($(CC), cc)
		@echo "you are using cc."
else
		@echo "you are not using cc."
endif
