#include <iostream>
#include <vector>
#include <sstream>

#include "args/parseArgs.hpp"
#include "printer/printer.hpp"

/**
 * Prints a help dialog
 */
void printHelp() {
    std::string helpDialog = 
            "cork - turn anything to a c array\n"
            "\n"
            "USAGE: cork [OPTIONS] [TEXT]\n"
            "\n"
            "Options:\n"
            "--help, -h\n"
            "   show this help text and exit\n"
            "--text, -t\n"
            "   text to encode\n"
            "--out, -o\n"
            "   (use - for stdout) name of output c file\n"
            "--in, -i\n"
            "   (use - for stdin) name of input file\n"
            "\n"
            "Copyright 2019 Jack Hance";

    std::cout << helpDialog << std::endl;
}

/**
 * Get an output stream from a given file name, if the given filename is '-' or
 * does not exist, stdout is returned
 * 
 * @param file file to get stream of
 * @return file stream or stdout if given file is named '-' or it cannot be used
 */
std::ostream* getOutputStream(std::string file) {
    if(file == "-") {
        return &std::cout;
    }

    std::ofstream* output = new std::ofstream(file);

    if(output->is_open()) {
        return output;
    } else {
        return &std::cout;
    }
}

/**
 * Get an input stream from a given file name, if the file cannot be opened 
 * or doesn't exist then an empty stringstream is returned
 * 
 * @param file file to create stream from
 * @return stream of file or an empty stringstream if file cannot be used
 */
std::istream* getInputStream(std::string file) {
    
    if(file == "-") {
        return new std::stringstream();
    }

    std::ifstream* input = new std::ifstream(file);

    if(input->is_open()) {
        return input;
    } else {
        return new std::stringstream();
    }
}

/**
 * Given a list of flags, convert the input flag to a char array and write to 
 * whatever output flag is set
 * 
 * @param flags argument flags
 */
void run(arg::flags* flags) {
    std::istream* in;
    std::ostream* out;

    // if text is given then use that as input, if a file is given then use
    // that as input, if neither are set then it is caught by main and a help
    // dialog is printed
    if(flags->textSet) in = new std::stringstream(flags->text);
    if(flags->inFilenameSet) in = getInputStream(flags->inFilename);
    
    // if the output file is set, write to it, otherwise print to stdout
    if(flags->outFilenameSet) out = getOutputStream(flags->outFilename);
    if(!flags->outFilenameSet) out = &std::cout;

    // convert and write, baby
    printer::printArrayString(in, out);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args;

    // don't include executable name in args
    for(int i = 1; i < argc; i++) args.push_back(argv[i]);

    // parse args into a flag struct
    arg::flags flags = arg::parse(args);

    // print a help dialog and exit if the help flag is set or if there
    // is not input given
    if(flags.helpSet || (!flags.textSet && !flags.inFilenameSet)) {
        printHelp();
        return 0;
    }

    run(&flags);

    return 0;
}