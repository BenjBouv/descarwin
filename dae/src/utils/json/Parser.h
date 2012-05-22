# ifndef __JSON_PARSER_H__
# define __JSON_PARSER_H__

# include "Entity.h"
# include "String.h"
# include "Object.h"

/**
 * This file contains a tiny JSON parser used in DAE. This parser just handles 
 * a subset of JSON grammar, with the following restrictions :
 * - all strings must be surrounded by double quotes.
 * - everything which is not an object or an array is considered to be a string
 * (even integers, booleans,...).
 * - no syntax check is done. We trust the programmer and he has to ensure that
 *   every JSON string he produces is valid.
 *
 * @author Benjamin BOUVIER
 */

namespace json
{

/**
 * @brief Parser from a JSON source.
 *
 * This parser does just retrieve values and does NOT check the structure of
 * the input. This implies that if the input is not correct, the result is undefined
 * and can result to a failure on execution.
 */
class Parser
{
    public:

        /**
         * @brief Parses the given string and returns the JSON object read.
         */
        static json::Object* parse(const std::string & str);

    protected:

        /**
         * @brief Parses the right part of a JSON object as a string.
         *
         * The right part of an object can be a string (for instance :
         * "key":"value"), a JSON array (for instance: "key":["1"]) or
         * another JSON object (for instance: "key":{"another_key":"value"}).
         *
         * The right parts are found after keys (which are parsed by parseLeft)
         * and in arrays.
         *
         * @param str The string we're parsing.
         * @param pos The index of the current position in the string.
         * @return The JSON object matching the right part.
         */
        static json::Entity* parseRight(const std::string & str, size_t & pos);

        /**
         * @brief Parses the left value of a key-value pair, which is the key.
         *
         * @param str The string we're parsing.
         * @param pos The index of the current position in the string.
         * @param json The current JSON object for which we're adding a key-value pair.
         */
        static void parseLeft(const std::string & str, size_t & pos, json::Object* json);

        /**
         * @brief Retrieves a string in a JSON content.
         *
         * @param str The string we're parsing.
         * @param pos The index of the current position of parsing,
         * which will be updated.
         */
        static json::String* parseJsonString(const std::string & str, size_t & pos);
};

} // namespace json

# endif // __JSON_PARSER_H__
