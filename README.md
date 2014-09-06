# Getting Started

## Quick install

Run the commands:

	git clone https://github.com/trfd/cAttrib.git
	./configure

This might be long since it will also clone LLVM, Ninja and CMake.
When done, run the following commands. 

	cd build
	cmake -G Ninja ../llvm
	
	ninja
	ninja install

	ccmake ../llvm

Then build the LLVM using the command

	ninja

***This step is very long!!***