setup
===

## pull project
+ `git clone project && cd space-junk`

## build v8
+ `git submodule init && git submodule update && cd v8`
+ `export CC=/path/to/clang`
+ `export CXX=/path/to/clang++`
+ `export GYP_DEFINES="clang=1"`
+ `make dependencies && make native -j8`

See: [documentation](https://code.google.com/p/v8/wiki/BuildingWithGYP) for more thorough build instructions
