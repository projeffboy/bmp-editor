CFLAGS=-g
COMMON_HEADERS=A3_provided_functions.h A3_solution.h
COMMON_SOURCES=A3_provided_functions.c A3_solution.c
ALL_COMMON=${COMMON_HEADERS} ${COMMON_SOURCES}

all: bmp_info bmp_scale bmp_collage

bmp_info: bmp_info.c ${ALL_COMMON}
	gcc ${CFLAGS} bmp_info.c ${COMMON_SOURCES} -o bmp_info

bmp_scale: bmp_scale.c ${ALL_COMMON}
	gcc  ${CFLAGS} bmp_scale.c ${COMMON_SOURCES} -o bmp_scale

bmp_collage: bmp_collage.c ${ALL_COMMON}
	gcc  ${CFLAGS} bmp_collage.c ${COMMON_SOURCES} -o bmp_collage

test: all
	./bmp_info    dog.bmp
	./bmp_info    metro_top_left.bmp
	./bmp_scale   dog.bmp                 dog_scaled.bmp 0.5
	./bmp_collage robots.bmp              rabbit.bmp     robots_with_one_ear.bmp   80  770 1.0
	./bmp_collage robots_with_one_ear.bmp dog.bmp        robots_with_both_ears.bmp 190 205 0.5
	./bmp_info marioland.bmp
	./bmp_info mariotime.bmp
	./bmp_scale marioland.bmp marioland_scaled.bmp 0.15
	./bmp_scale mariotime.bmp mariotime_scaled.bmp 5.0
	# ./bmp_collage mariotime.bmp marioland.bmp mariotimeland.bmp 0 0 1.0
	# ./bmp_collage marioland.bmp mariotime.bmp mariotimeland2.bmp 0 0 2.0
	./bmp_info mariotime_scaled.bmp
	./bmp_collage mariotime_scaled.bmp rabbit.bmp wth.bmp 50 50 1.0
	./bmp_info dog_scaled.bmp

clean:
	rm bmp_info bmp_scale bmp_collage
  
