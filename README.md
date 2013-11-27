CodeBox
=======

The Point
-------
Codebox Framework is a set of libraries (called "Modules") that main target is to simplify much tedious work with writing multimedia applications (mostly - games) and easy to understand, see trough structure without much noise.

The main principles:
- Maximal resuability.
- Minimal namespace garbage.
- Optional Extensibility.

Framework consists of modules of four main types:
- Core - elemental, can be used independly from other core modules (ex. Common Module).
- Driver Interface - interface for dynamically loaded modules, called "Drivers". Can depend only on Core modules or other interface drivers.
- Driver - Driver writen againts one, or more interface driver and can be only accesed by such. Can only depend on core modules or other interace drivers, but not drivers directly.
- Tools - Tools module consists of usefull classes that can be used with specified Core modules and Driver Interfaces (but not drivers). Bassicly, they are extensions.

Third party libraries
-------
- libsndfile at http://www.mega-nerd.com/libsndfile/
- freetype2 at http://freetype.org/
- OpenAL Soft at http://kcat.strangesoft.net/openal.html
- FreeImage at http://freeimage.sourceforge.net
- cg shaders at https://developer.nvidia.com/cg-toolkit

License
-------
Whole framework is published under the LGPL v3 license, that can be accessed from: http://www.gnu.org/licenses/lgpl.txt
