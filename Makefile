name = computer69
source_folder = src/
test_folder = src/test/
why_folder = src/why/
obj_folder = obj/
cc = gcc
flags = -g -Wall -Wextra
release_flags = -O3

headers = $(wildcard $(source_folder)*.h)

source = $(wildcard $(source_folder)*.c)
test_source = $(wildcard $(test_folder)*.c)
why_source = $(wildcard $(why_folder)*.c)

objects = $(subst $(source_folder),$(obj_folder),$(source:.c=.o))
test_objects = $(subst $(test_folder),$(obj_folder),$(test_source:.c=.o))
why_objects = $(subst $(why_folder),$(obj_folder),$(why_source:.c=.o))

all: $(why_objects) $(test_objects) $(objects) $(name)

release: flags=$(release_flags)
release: clean all

test_:
	echo $(test_objects)

$(obj_folder)%.o : $(why_folder)%.c $(headers)
	$(cc) $(flags) $< -c -o $@

$(obj_folder)%.o : $(test_folder)%.c $(headers)
	$(cc) $(flags) -I $(why_folder) -I $(source_folder) $< -c -o $@

$(obj_folder)%.o : $(source_folder)%.c $(headers)
	$(cc) $(flags) -I $(why_folder) $< -c -o $@

$(name): $(test_objects) $(objects) $(headers)
	$(cc) $(flags) $(why_objects) $(test_objects) $(objects) -o $(name) -lm

clean:
	rm -f $(why_objects) $(objects) $(test_objects)

fclean: clean
	rm -f $(name)

re: fclean all
