setup
===

## pull project
+ `git clone <URL_HERE> && cd space-junk`

## build v8
1. `git submodule init && git submodule update && cd v8`
2. `export CC=/path/to/clang`
3. `export CXX=/path/to/clang++`
4. `export GYP_DEFINES="clang=1"`
5. `make dependencies && make native -j8 OUTDIR=../v8-build`

In the final line, replace the '8' with roughly 2x the amount of cores your build setup has. OUTDIR= is also very important, as it will put object files where they need to go for other build systems find them.

See: [documentation](https://code.google.com/p/v8/wiki/BuildingWithGYP) for more thorough build instructions

compilation
===
## build with xcode
The .xcodeproj in the SpaceJunk/ subdirectory should Just Work™ with the current version of xcode. As long as the v8 directory and v8-build directories are all correcly set up, it shouldn't have any issues building out of the box.

## build with something else
IDEs can often be dumb. If this is what troubles you, feel free to build with command line tools only, or even make a premake or automake script to do the work for all of us. The trick is going to be linking with opengl3, pthreads, and the v8 libraries mentioned above. Shouldn't be too hard, but might be a bit daunting for the uninitiated.

misc
===
## troubleshooting
+ Sometimes you might get an svn error when `make dependencies` tries to use git-svn to update subdirectories in the v8 subrepo. Simply delete the offending directories and rerun `makde dependencies`.