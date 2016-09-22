SET(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} -O0 -Wall -g -Werror") 
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall    -Werror") 
SET(CMAKE_CXX_FLAGS         "$ENV{CXXFLAGS} -O3 -Wall    -Werror") 

SET(CMAKE_C_FLAGS_DEBUG     "$ENV{CFLAGS}   -O0 -Wall -g -Werror") 
SET(CMAKE_C_FLAGS_RELEASE   "$ENV{CFLAGS}   -O3 -Wall    -Werror") 
SET(CMAKE_C_FLAGS           "$ENV{CFLAGS}   -O3 -Wall -g -Werror") 


