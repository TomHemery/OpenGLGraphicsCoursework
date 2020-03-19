# Open GL Graphics Coursework

This is my final submission for a third year graphics coursework.

In order to run the scene please open the .sln file in visual studio 2017 and follow the following steps: 

* Retarget the solution to match the version of the windows SDK present on your machine 
* Switch to the x86 (32 bit) debug mode, and click the "run" button to run the scene in debug mode

It is heavily suggested that you use a machine with at least a fairly modern dedicated GPU - in order to facilitate better framerates

The scene renders at full 60FPS when tested with machines with the following specifications: 

* GTX 1050 + intel i5 7300HQ
* GTX 980 + intel i7 4790K

The scene renders at ~20 FPS on a machine with the following specifications: 

* Quadro K600 + intel i7 4790

Performance is heavily GPU dependent, the models present in the scene have several thousand polygons each.
