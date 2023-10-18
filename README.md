# graphics\_programming
## For graphics programming endeavors

----------------

# SETUP
## GLFW Download:
download and extract GLFW 64-bit Windows binaries:
https://www.glfw.org/download.html

## file strucutre
graphics\_programming/
-- dependencies/
|  --include/
|  |  GLFW/
|  |  --glfw3.h
|  --lib/
|     --libglfw3.a
--main.cpp

----------------

# COMPILATION:
## navigate to the project root directory and run:
1. g++ -o main main.cpp glad.c -Idependencies/include -Ldependencies/lib -lglfw3 -lopengl32 -lgdi32
## command explaination:
- g++: command to compile c++ code.
- -o <program>: output the program with a name
- main.cpp glad.c: the file to compile
- -Idependencies/include: the path to search for include files
- -Ldependencies/lib: the path to search for libraries to link
- -lglfw3 -lopengl32 -lgdi32: the necessary libraries to link for this project.

# COMPILATION USING CMAKE
# in root/cmake
1. Clear cache by deleting CMakeCache.txt
2. cmake -G "Unix Makefiles" .
3. make
----------------
