theory
===

> Write programs that do one thing and do it well. Write programs to work together. Write programs to handle text streams, because that is a universal interface.

All-in-one game or simulation development toolsets violate the basic software engineering philosophical tenent of doing [one thing well](http://www.faqs.org/docs/artu/ch01s06.html). They are generally monolithic (for example, unity, autodesk, or matlab for simulation programming) and thereby end up causing their users pain on installation, configuration, and use by causing them to make sacrifices in how they interface with the core competency of the application. The fact that what these applications do is often done extremely well makes this situation all the more frustrating.

This repository holds a 3D engine built using OpenGL3.2+ that is configured by executing JavaScript using the [V8 JavaScript engine](https://developers.google.com/v8/). It recieves JavaScript either by loading files off disk, or by recieving fragments over the [WebSocket](http://tools.ietf.org/html/rfc6455) protocol.

In this way, this application does one thing well: run an easily configured 3D graphics simulation. That configuration is done via ASCII text streams.

The ultimate goal of the project is to show that editors and tools can be decoupled from the engine they configure thereby increasing user freedom. Any editor may be used to edit the JavaScript that configures this simulation and  any program may construct asset bundles to be consumed by it.

An example toolchain is [implemented as a web application](https://github.com/ixtli/space-junk-tools) to demonstrate how this decoupling can be achieved using modern web browsers without sacrificing any of the minutia one might find in a complex editor such as 3DSMax or Unreal. 

setup
===

## pull project and configure this repo
+ `git clone <URL_HERE> && cd space-junk`
+ `git submodule init && git submodule update`


## build libpng
1. Download libPNG 1.6.15 [from SourceForge](http://sourceforge.net/projects/libpng/files/libpng16/1.6.15/libpng-1.6.15.tar.xz/download)
2. Decompress the .tar.xz and move the resulting directory (it should be called libpng-1.6.15) to the root level of this repo.
3. `mkdir -p libpng-build && cd libpng-1.6.15`
4. `./configure --prefix=$(pwd)"/../libpng-build/" && make check && make install`


## build v8
1. `cd v8`
2. `export CC=/path/to/clang`
3. `export CXX=/path/to/clang++ -std=c++11 -stdlib=libc++`
4. `export LINK="`which clang++` -std=c++11 -stdlib=libc++"`
4. `export GYP_DEFINES="clang=1 mac_deployment_target=10.8"`
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
## source style and notes
+ try to limit lines to 80 characters in width: not all of us edit code on 20+ inch monitors.
+ we take for granted that C++2003 value initialization rules are applied. By way of explanation, consider a template class `C<type T>` which contains a member variable of type T called x. We assume that after calling the default constructor `C<int> foo = C<int>()`, `foo.x` will be equal to zero.
+ don't cuddle { } with keywords or other statements except for `else` and `else if`

## troubleshooting
+ Sometimes you might get an svn error when `make dependencies` tries to use git-svn to update subdirectories in the v8 subrepo. Simply delete the offending directories and rerun `make dependencies`.
