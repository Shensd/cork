# CORK

A simple command line tool for converting anything to C arrays

### What is this?

Because I am eccentric and spend a lot of time doing odd things in C, I found myself needing a tool that can convert pretty much anything into a C char array, and as such this tool was born.

Cork is a command line tool to convert files, strings, and really anything else you can throw at it into a C char array for whatever you would like to do with. 

### How do I use it?

Cork has a simple job, and has an equally simple interface for using it.

```
cork - turn anything to a c array

USAGE: cork [OPTIONS] [TEXT]

Options:
--help, -h
   show this help text and exit
--text, -t
   text to encode
--out, -o
   (use - for stdout) name of output c file
--in, -i
   (use - for stdin) name of input file
```

You given input, you give output, and the input is written to the output as a C char array, neat, right?

### How do I build it?

Cork has an included CMake file, so all one needs to do is the following:

 * Create a directory named `build` or something similar
 * `cd` into the directory
 * Execute `cmake .. && make`

The output executable will be named `cork`.

###### This project is licensed under the MIT Open Source License, see `LICENSE` for more information.