
target = main
cc = gcc
flags = -std=c99 -Wall
include_paths = -I"C:/VulkanSDK/1.2.176.1/Include" -I"C:/mingw64/mingw64/include"
library_paths = -L"C:/VulkanSDK/1.2.176.1/Lib" -L"C:/mingw64/mingw64/lib"
libraries = -lvulkan-1
src = main.c

all: $(src)
	$(cc) $(flags) $(include_paths) -o $(target) $(src) $(library_paths) $(libraries)


.PHONY: clean run

run:
	./$(target)

clean:
	
