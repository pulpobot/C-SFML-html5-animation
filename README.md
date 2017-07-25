Sample code from https://github.com/lamberta/html5-animation ported to C++ and SFML.

State: In-Progress.

SFML Version: 2.4.2

Folder Structure:
- chapter#-example#-examplename
	* CMakeList.txt
	* /deps: Any libraries required by the example (except for SFML)
	* /src: Source Code.
	* /res: stores any assets required by the example (e.g fonts or images).
	* /build: Precompiled Windows Executable x86 File.

- shared-deps
	* /SFML-x.x.x: Current SFML Version being used by all the examples

Note 1: If you want to build any example, just run CMake on their own root folder.

Note 2: I have built all the examples on Windows with CMake; eventually will try to add Linux and OSx support, but I'll be more than happy to recieve any help on this in the meanwhile :)

Note 3: Example ch04-12-video-frames uses Visual Studio temporarily.