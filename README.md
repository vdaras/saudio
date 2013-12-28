saudio
======

saudio is a simple audio file streaming server developed in C++11. 
It was mainly written for learning purposes as I wanted to get more familiar
with the language's new features. 

saudio compiles successfully in all platforms but running it is only supported
in Unix-like OSes. The code that handles platform specific code can be extended
to support other OSes. 

saudio is minimalistic, it only uses the STL and no external libraries. 

An SCons build script is included with the source code.
In order build the server using the aforementioned script you need to have the
SCons software installed in your machine.


How to build:

cd in the directory containing the SConstruct file
and enter the command

      scons

if you need to build with debugging symbols enabled
  
      scons --debug-build


When starting the server, it needs to receive the port number that it will listen
for incoming connections (using the -p command line argument) and where are the
audio files that the server can stream (-l). It can optionally receive the 
maximum simultaneous connections (-c) and how many serving threads to spawn (-t).

In order for a client to request an audio file stream, a URL like this should
be used

    http://hostname:port/filename

It is possible for a client to search the server's available audio files by
using a URL like this

    http://hostname:port/songsearch/keyword

The server's response will be an .m3u file containing all URLs for files matching
the keyword.






