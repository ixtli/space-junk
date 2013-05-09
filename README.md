setup
===

## pull project
+ `git clone project && cd space-junk`

## build v8
+ `git submodule init && git submodule update && cd v8`
+ `export CC=/path/to/clang`
+ `export CXX=/path/to/clang++`
+ `export GYP_DEFINES="clang=1"`
+ `make dependencies && make native -j8 OUTDIR=../v8-build`

In the final line, replace the '8' with roughly 2x the amount of cores your build setup has. OUTDIR= is also very important, as it will put object files where they need to go for other build systems find them.

See: [documentation](https://code.google.com/p/v8/wiki/BuildingWithGYP) for more thorough build instructions
