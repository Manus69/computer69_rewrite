name = computer69
source_folder = src/
obj_folder = obj/
cc = gcc
flags = -g -Wall -Wextra
release_flags = -O3

source = $(wildcard $(source_folder)*.c)
objects = $(subst $(source_folder),$(obj_folder),$(source:.c=.o))
headers = $(wildcard $(source_folder)*.h)

all: $(objects) $(name)

release: flags=$(release_flags)
release: clean all

test_:
	echo $(source)
	echo $(objects)

$(obj_folder)%.o : $(source_folder)%.c $(headers)
	$(cc) $(flags) $< -c -o $@

$(name): $(objects) $(headers)
	$(cc) $(flags) $(objects) -o $(name) -lm

clean:
	rm -f $(objects)

re: clean all
