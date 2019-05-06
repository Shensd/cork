#ifndef PARSE_ARGS_HPP
#define PARSE_ARGS_HPP

#include <string>
#include <vector>
#include <functional>
#include <map>

#include <iostream>

namespace arg {
    enum inputFormat {
        IMAGE,
        TEXT
    };

    struct flags {
        bool helpSet = false;
        
        bool textSet = false;
        std::string text = "";

        bool outFilenameSet = false;
        std::string outFilename = "out.c";

        bool inFilenameSet = false;
        std::string inFilename = "";

        bool error = false;
        std::string errorText = "";
    };

    // private namespace
    namespace {

        // flag parse funcs
        void flagParseHelp(std::string flagText, struct flags* flagPool);
        void flagParseText(std::string flagText, std::string content, struct flags* flagPool);
        void flagParseOutFilename(std::string flagText, std::string content, struct flags* flagPool);
        void flagParseInFilename(std::string flagText, std::string content, struct flags* flagPool);

        // flag parse func map
        std::map<std::string, void(*)(std::string, std::string, struct flags*)> flagFuncs;
        std::map<std::string, void(*)(std::string, struct flags*)> flagFuncsNoContent;

        // split helper function
        std::vector<std::string> split(std::string str, char delim);

        // vector map helper function
        template<class T, typename F> std::vector<T> vectorMap(std::vector<T> arr, F func);

        // string to lower helper function
        std::string toLower(std::string str);
    };

    flags parse(std::vector<std::string>  rawArgs);
};   

#endif // !PARSE_ARGS_HPP