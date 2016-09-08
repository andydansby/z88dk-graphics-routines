# z88dk-graphics-routines
Basic graphics for the Z88DK written for ZX Spectrum
 compile with
 
 zcc +zx -vn -lm -clib=sdcc_iy -startup=1 main.c zxgraphics.c -o main -create-app
 
 for optimized code use the compiling string
 
 zcc +zx -vn -lm -clib=sdcc_iy -startup=1 -SO3 --max-allocs-per-node200000  main.c zxgraphics.c -o main -create-app
