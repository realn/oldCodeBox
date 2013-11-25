CodeBox
=======

Codebox Framework is a set of libraries (called "Modules") that main target is to 
simplify much tedious work with writing multimedia applications (mostly - games)
and easy to understand, see trough structure without much noise.

The main principles:
1. Maximal resuability.
2. Minimal namespace garbage.
3. Optional Extensibility.

Framework consists of modules of four main types:
1. Core - elemental, can be used independly from other core modules (ex. Common Module).
2. Driver Interface - interface for dynamically loaded modules, called "Drivers". Can 
    depend only on Core modules or other interface drivers.
3. Driver - Driver writen againts one, or more interface driver and can be only accesed by
    such. Can only depend on core modules or other interace drivers, but not drivers directly.
4. Tools - Tools module consists of usefull classes that can be used with specified 
    Core modules and Driver Interfaces (but not drivers). Bassicly, they are extensions.
    
License
========
Whole framework is published under the LGPL v3 license, that can be accessed from:
http://www.gnu.org/licenses/lgpl.txt
