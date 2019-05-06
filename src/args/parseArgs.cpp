#include "parseArgs.hpp"

namespace arg {

    // private namespace
    namespace {

        /**
         * Help flag parser, sets the help flag to true
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseHelp(std::string flagText, struct flags* flagPool) {
            flagPool->helpSet = true;
        }

        /**
         * Text flag parser, if content is given then text is set, error
         * flag set if no content is given
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseText(std::string flagText, std::string content, struct flags* flagPool) {
            if(content != "") {
                flagPool->textSet = true;
                flagPool->text = content;
            } else {
                flagPool->error = true;
                flagPool->errorText = "Text flag was set but no text given";
            }
        }

        /**
         * Filename flag parser, given content is converted into a type, error flag
         * set if given content cannot be translated into a file name
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseOutFilename(std::string flagText, std::string content, struct flags* flagPool ) {
            if(content == "") {
                flagPool->error = true;
                flagPool->errorText = "Output file name flag set but no file name given";
                return;
            }

            flagPool->outFilenameSet = true;
            flagPool->outFilename = content;
        }

        /**
         * Filename flag parser, given content is converted into a type, error flag
         * set if given content cannot be translated into a file name
         * 
         * @param flagText text of flag
         * @param content next block of text in command arg string
         * @param flagPool struct of already set flags
         */
        void flagParseInFilename(std::string flagText, std::string content, struct flags* flagPool ) {
            if(content == "") {
                flagPool->error = true;
                flagPool->errorText = "Input file name flag set but no file name given";
                return;
            }

            flagPool->inFilenameSet = true;
            flagPool->inFilename = content;
        }

        /**
         * splits a string by a given delim and returns the result in a vector
         * 
         * @param str string to be split
         * @param delim delimiter to split the string by
         * @returns vector of split string
         */
        std::vector<std::string> split(std::string str, char delim=' ') {
            std::vector<std::string> tokens;

            std::string temp = "";
            for(int i = 0; i < str.length(); i++) {
                
                if(str[i] == delim) {
                    tokens.push_back(temp);

                    temp = "";
                } else if(i == str.length() - 1) {
                    temp += str[i];

                    tokens.push_back(temp);
                } else {
                    temp += str[i];
                }
            }

            return tokens;
        }
        
        /**
         * Performs a given function on each item in a vector
         * 
         * @param arr vector to perform function on
         * @param func function to perform on each item
         */
        template<class T, typename F> std::vector<T> vectorMap(std::vector<T> arr, F func) {
            std::vector<T> tempArr;
            for(T a : arr) {
                tempArr.push_back(func(a));
            }
            return tempArr;
        }

        /**
         * Convert a string to lowercase
         * 
         * @param str string to convert
         * @return string in lowercase form
         */
        std::string toLower(std::string str) {
            for(int i = 0; i < str.size(); i++) {
                str[i] = std::tolower(str[i]);
            }
            return str;
        }
    }

    /**
     * Parses a given command line string and returns a flags structure of
     * set flags, if the `errorSet` is true then there was an error during 
     * parsing, the error message is under `error`
     * 
     * @param rawArgs command line arg string
     * @return a flag structure of set args
     */
    flags parse(std::vector<std::string> rawArgs) {
        struct flags parsedFlags;

        // create flag parse map
        flagFuncs = {
            {"text", &flagParseText},
            {"t", &flagParseText},

            {"out", &flagParseOutFilename},
            {"o", &flagParseOutFilename},

            {"in", &flagParseInFilename},
            {"i", &flagParseInFilename}
        };

        flagFuncsNoContent = {
            {"help", &flagParseHelp},
            {"h", &flagParseHelp}
        };

        for(int i = 0; i < rawArgs.size(); i++) {
            std::string s = rawArgs[i];

            // is tack flag, pull flag text
            if(s[0] == '-') {
                std::vector<std::string> parts = split(s, '-');
                std::string flagText = parts[parts.size() - 1];

                // check if flag function if it exists in the map
                auto iter = flagFuncs.find(flagText);
                if(iter != flagFuncs.end()) {

                    std::string content;
                    if(i < rawArgs.size() - 1) {
                        content = rawArgs[i + 1];
                    } else {
                        content = "";
                    }

                    // now call associated function pointer
                    iter->second(flagText, content, &parsedFlags);
                    
                    // increment i to skip next token since it was used by 
                    // the current flag
                    i++;
                } else {

                    // if a flag that requires content isn't found, try to process
                    // as a no content flag
                    auto iter = flagFuncsNoContent.find(flagText);

                    if(iter != flagFuncsNoContent.end()) {
                        iter->second(flagText, &parsedFlags);
                    } else {
                        // that flag doesnt have an entry in the function map
                        parsedFlags.error = true;
                        parsedFlags.errorText = "Unknown flag " + s;
                    } 
                }
            // given token is not a tack flag, but if text is not set
            // then it will be set by default
            } else {
                if(!parsedFlags.textSet) {
                    parsedFlags.textSet = true;
                    parsedFlags.text = s;
                }
            }

            // check if the error flag was set at any point and immediately
            // exit if it was

            if(parsedFlags.error) break;
        }

        return parsedFlags;
    }

}