#!/bin/bash
#Coded by Philip "DevCooL" Simonson
####################################################

if [ -d "bin" ]; then
	if [[ -e bin/fileio && -e bin/opengl1 && -e bin/opengl2 && -e bin/opengl3 ]]; then
		echo Files exist rebuilding...
		make -f Makefile.linux rebuild
	else
		echo Files not found building...
		make -f Makefile.linux all
	fi

	if [[ -e bin/fileio.exe && -e bin/opengl1.exe && -e bin/opengl2.exe && -e bin/opengl3.exe ]]; then
		echo Win32 Files exist rebuilding...
		make -f Makefile.win32 rebuild
	else
		echo Win32 Files not found building...
		make -f Makefile.win32 all
	fi
else
	mkdir bin
fi

