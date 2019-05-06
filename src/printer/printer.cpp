#include "printer.hpp"

namespace printer {

    /**
     * Convert the data in the input stream to a c char array and write it 
     * to the given output stream
     * 
     * @param in stream to read in from and convert
     * @param out stream to print out converted input to
     */
    void printArrayString(std::istream* in, std::ostream* out) {
        // get the length of the stream
        in->seekg(0, in->end);
        int length = in->tellg();
        in->seekg(0, in->beg);

        // output length and beginning of array
        *out << "int data_length = " << length << ";" << std::endl;
        *out << "char data[] = {";

        // read through input and convert data to proper char array form
        for(int i = 0; i < length; i++) {
            char* buffer = new char[1];
            in->read(buffer, 1);
            *out << "0x" << std::hex << (int) *buffer << std::dec;

            // don't print out a comma after the last item
            if(i < length - 1)  *out << ", ";
        }

        // print closing brack for array
        *out << "};" << std::endl;
    }

}