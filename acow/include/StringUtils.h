
//https://msdn.microsoft.com/en-us/library/system.string(v=vs.110).aspx
#pragma once

// std
#include <algorithm>
#include <initializer_list>
#include <sstream>
#include <string>
#include <vector>
// acow_StringUtils - Libs
#include "../libs/asprintf/asprintf.h"

namespace acow { namespace StringUtils {

//----------------------------------------------------------------------------//
// Private Stuff                                                              //
//----------------------------------------------------------------------------//
namespace Private_Concat
{
    template <typename T> std::string
    Concat(const T &value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
}

namespace Private_Join
{
    template <typename T>
    std::string Join(const std::string &separator, const T &value)
    {
        std::stringstream ss;
        ss << value << separator;
        return ss.str();
    }
}

namespace Private_Format
{
    //--------------------------------------------------------------------------
    // Reference:
    //   https://msdn.microsoft.com/en-us/magazine/dn913181.aspx
    //   As usual Kenny Kerr is awesome!
    template <typename T>
    T Argument(T value) noexcept { return value; }

    template <typename T>
    T const* Argument(const std::basic_string<T> &value) noexcept
    {
        return value.c_str();
    }
}


//----------------------------------------------------------------------------//
// Capitalize                                                                 //
//----------------------------------------------------------------------------//
void Capitalize_InPlace(std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return a copy of the string S with only its first character capitalized.
inline std::string
Capitalize(const std::string &str) noexcept
{
    auto new_str = str;
    Capitalize_InPlace(new_str);
    return new_str;
}


//----------------------------------------------------------------------------//
// Center                                                                     //
//----------------------------------------------------------------------------//
void Center_InPlace(std::string &str, size_t length, char c = ' ') noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return S centered in a string of length width. Padding is
///   done using the specified fill character (default is a space)
inline std::string
Center(const std::string &str, size_t length, char c = ' ') noexcept
{
    auto new_str = str;
    Center_InPlace(new_str, length, c);
    return new_str;
}

//----------------------------------------------------------------------------//
// Count                                                                      //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Return the number of non-overlapping occurrences of substring sub in
///   string S[start:end].  Optional arguments start and end are interpreted
///   as in slice notation.
size_t Count(
    const std::string &haystack,
    const std::string &needle,
    size_t             start = 0,
    size_t             end   = std::string::npos) noexcept;


//----------------------------------------------------------------------------//
// ExpandTabs                                                                 //
//----------------------------------------------------------------------------//
void ExpandTabs_InPlace(std::string &str, size_t tabSize = 8) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///  Return a copy of S where all tab characters are expanded using spaces.
///  If tabsize is not given, a tab size of 8 characters is assumed.
inline std::string
ExpandTabs(const std::string &str, size_t tabSize = 8) noexcept
{
    auto new_str = str;
    ExpandTabs_InPlace(new_str, tabSize);
    return new_str;
}


//----------------------------------------------------------------------------//
// Is*Something*                                                              //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///  Return True if all characters in S are alphanumeric
///  and there is at least one character in S, False otherwise.
bool IsAlNum(const std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return True if all characters in S are alphabetic
///   and there is at least one character in S, False otherwise.
bool IsAlpha(const std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return True if all characters in S are digits
///   and there is at least one character in S, False otherwise.
bool IsDigit(const std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return True if all cased characters in S are lowercase and there is
///   at least one cased character in S, False otherwise.
bool IsLower(const std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return True if all characters in S are whitespace
///   and there is at least one character in S, False otherwise.
bool IsSpace(const std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return True if S is a titlecased string and there is at least one
///   character in S, i.e. uppercase characters may only follow uncased
///   characters and lowercase characters only cased ones. Return False
///   otherwise.
bool IsTitle(const std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return True if all cased characters in S are uppercase and there is
///   at least one cased character in S, False otherwise.
bool IsUpper(const std::string &str) noexcept;


//----------------------------------------------------------------------------//
// SwapCase                                                                   //
//----------------------------------------------------------------------------//
void SwapCase_InPlace(std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return a copy of the string S with uppercase characters
///   converted to lowercase and vice versa.
inline std::string
SwapCase(const std::string &str) noexcept
{
    auto new_str = str;
    SwapCase_InPlace(new_str);
    return new_str;
}


//----------------------------------------------------------------------------//
// Title                                                                      //
//----------------------------------------------------------------------------//
void Title_InPlace(std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Return a titlecased version of S, i.e. words start with uppercase
///   characters, all remaining cased characters have lowercase.
inline std::string
Title(const std::string &str) noexcept
{
    auto new_str = str;
    Title_InPlace(new_str);
    return new_str;
}


//----------------------------------------------------------------------------//
// Concat                                                                     //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Concatenates the string representations of the elements
///   in a specified list.
/// @param list
///   An initializer_list that will be concatenated.
/// @returns
///   The string with all items concatenated.
/// @note
///   This function use the operator << to tranform the item into the
///   its string representation.
template <typename T, typename... Args> std::string
Concat(const T& first, const Args&... args) noexcept
{
    using namespace Private_Concat;
    return Concat(first) +  Concat(args...);
}

//----------------------------------------------------------------------------//
// Contains                                                                   //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Returns a value indicating whether a specified substring
///   occurs within this string.
/// @param haystack
///   The string that will be searched against.
/// @param needle
///   The string that will searched in haystack.
/// @param caseSensitive
///   If the search will consider the case of both strings (Default: true)
/// @returns
///   True if the needle is on haystack, false otherwise.
bool Contains(
    const std::string &haystack,
    const std::string &needle,
    bool              caseSensitive = true) noexcept;


//----------------------------------------------------------------------------//
// EndsWith                                                                   //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Determines whether the end of this string instance
///   matches the specified string.
/// @param haystack
///   The string that will be searched against.
/// @param needled
///   The string that will be searched in haystack.
/// @param caseSensitive
///   If the search will consider the case of both strings (Default: true)
/// @returns
///   True if the haystack ends with the needle, false otherwise.
bool EndsWith(
    const std::string &haystack,
    const std::string &needle,
    bool               caseSensitive = true) noexcept;


//----------------------------------------------------------------------------//
// Format                                                                     //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Replaces the format item in a specified string with the string
///   representation of a corresponding object in a specified array.
/// @param fmt
///   The formatting string
template <typename... Args> std::string
Format(const std::string &str, Args ...args) noexcept
{
    using namespace Private_Format;

    //COWTODO(n2omatt): Performance is trash here because we're allocating
    // and release memory everytime that we do a format.
    // This works for now, but I need research a little further to learn
    // how to make this better.
    char *buf = nullptr;
    if(sizeof...(args) == 0)
        return str;

	// COWTODO(n2omatt): asprintf isn't standard...
    insanecoding::asprintf(&buf, str.c_str(), Argument(args) ...);

    std::string ret_str(buf);
    free(buf);

    return ret_str;
}

//----------------------------------------------------------------------------//
// IndexOf                                                                    //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Reports the zero-based index of the first occurrence of the
///   specified character in this instance. The search starts at a
///   specified character position and examines a specified number
///   of character positions.
/// @param str
///   The string that will be searched.
/// @param c
///   The character that will be searched on str.
/// @param beginIndex
///   The to start the search (Default: 0 - Start of string).
/// @param charsCount
///   How many chars is to search from the beginIndex
///   (Default: std::string::npos - Search everything).
/// @returns
///   The index of the c char in the str string or std::string::npos if
///   c isn't in the str string.
size_t IndexOf(
    const std::string &str,
    char               c,
    size_t             beginIndex = 0,
    size_t             charsCount   = std::string::npos) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///    Reports the zero-based index of the first occurrence in this instance
///    of any character in a specified array of Unicode characters.
///    The search starts at a specified character position and examines
///    a specified number of character positions.
/// @param str
///   The string that will be searched.
/// @param chars
///   The character array (as a string) that will be searched in str.
/// @param beginIndex
///   The to start the search (Default: 0 - Start of string).
/// @param charsCount
///   How many chars is to search from the beginIndex
///   (Default: std::string::npos - Search everything).
/// @returns
///   The index of the c char in the str string or std::string::npos if
///   any of the chars isn't in the str string.
size_t IndexOfAny(
    const std::string &str,
    const std::string &chars,
    size_t             beginIndex = 0,
    size_t             charsCount   = std::string::npos) noexcept;


//----------------------------------------------------------------------------//
// IsNullOrWhiteSpace                                                         //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Indicates whether a specified string is null, empty, or consists only
///   of white-space characters.
/// @param str
///   The string that will be queried.
/// @returns
///   True if the string is empty or has only whitespaces, false otherwise.
bool IsNullOrWhiteSpace(const std::string &str) noexcept;


//----------------------------------------------------------------------------//
// Join                                                                       //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Concatenates the elements of an object array, using the specified
///   separator between each element.
/// @param separator
///   The string that will be placed between the other components.
/// @param first
///   The first object that will be joined.
/// @param args
///   The rest of objects that will be joined.
template <typename T, typename... Args> std::string
Join(const std::string &separator, const T &first,  Args... args) noexcept
{
    using namespace Private_Join;
    return Join(separator, first) + Join(separator, args...);
}


//----------------------------------------------------------------------------//
// LastIndexOf                                                                //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Reports the zero-based index position of the last occurrence of a
///   specified Unicode character within this instance.
/// @param str
///   The string that will be searched.
/// @param c
///   The character that will be searched on str.
/// @param beginIndex
///   The to start the search (Default: 0 - Start of string).
/// @param charsCount
///   How many chars is to search from the beginIndex
///   (Default: std::string::npos - Search everything).
/// @returns
///   The index of the c char in the str string or std::string::npos if
///   c isn't in the str string.
size_t LastIndexOf(
    const std::string &str,
    char               c,
    size_t             beginIndex = 0,
    size_t             charsCount   = std::string::npos) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Reports the zero-based index position of the last occurrence in this
///   instance of one or more characters specified in a Unicode array.
/// @param str
///   The string that will be searched.
/// @param chars
///   The character array (as a string) that will be searched in str.
/// @param beginIndex
///   The to start the search (Default: 0 - Start of string).
/// @param charsCount
///   How many chars is to search from the beginIndex
///   (Default: std::string::npos - Search everything).
/// @returns
///   The index of the c char in the str string or std::string::npos if
///   any of the chars isn't in the str string.
size_t LastIndexOfAny(
    const std::string &str,
    const std::string &chars,
    size_t             beginIndex = 0,
    size_t             charsCount   = std::string::npos) noexcept;


//----------------------------------------------------------------------------//
// PadLeft                                                                    //
//----------------------------------------------------------------------------//
void PadLeft_InPlace(std::string &str, size_t length, char c = ' ') noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Returns a new string that right-aligns the characters in this
///   instance by padding them on the left with a specified Unicode character,
///   for a specified total length.
/// @param str
///   The string that will be padded.
/// @param length
///   The total size of the resulting string.
/// @param c
///   The char that will be used to pad the string (Default = ' ' [space]).
/// @returns
///   The padded string.
/// @note
///   If the length of resulting string is less than length of str
///   nothing will ocurr and the str will be returned as is instead.
inline std::string
PadLeft(const std::string &str, size_t length, char c = ' ') noexcept
{
    auto new_str = str;
    PadLeft_InPlace(new_str, length, c);
    return new_str;
}


//----------------------------------------------------------------------------//
// PadRight                                                                   //
//----------------------------------------------------------------------------//
void PadRight_InPlace(std::string &str, size_t length, char c = ' ') noexcept;

///-----------------------------------------------------------------------------
/// @brief
///  Returns a new string that left-aligns the characters in this string
///  by padding them on the right with a specified Unicode character,
///  for a specified total length.
/// @param str
///   The string that will be padded.
/// @param length
///   The total size of the resulting string.
/// @param c
///   The char that will be used to pad the string (Default = ' ' [space]).
/// @returns
///   The padded string.
/// @note
///   If the length of resulting string is less than length of str
///   nothing will ocurr and the str will be returned as is instead.
inline std::string
PadRight(const std::string &str, size_t length, char c = ' ') noexcept
{
    auto new_str = str;
    PadRight_InPlace(new_str, length, c);
    return new_str;
}


//----------------------------------------------------------------------------//
// Replace                                                                    //
//----------------------------------------------------------------------------//
void Replace_InPlace(
    std::string       &str,
    const std::string &what,
    const std::string &to) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Returns a new string in which all occurrences of a specified string
///   in the current instance are replaced with another specified string.
/// @param str
///   The string that will be replaced.
/// @param what
///   What will be replaced.
/// @param to
///   For what will be replaced.
/// @returns
///   The string with all 'what' strings replaced by the 'to' strings, or
///   the original str if any 'what' was found.
inline std::string
Replace(
    const std::string &str,
    const std::string &what,
    const std::string &to) noexcept
{
    auto new_str = str;
    Replace_InPlace(new_str, what, to);
    return new_str;
}


//----------------------------------------------------------------------------//
// Split                                                                      //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Splits a string into substrings that are based on the
///   characters in an array.
/// @param str
///   The string that will be split.
/// @param chars
///   The char array (as a string) of separators.
/// @returns
///   A vector of all components split.
std::vector<std::string> Split(
    const std::string &str,
    const std::string &chars) noexcept;

///-----------------------------------------------------------------------------
/// @brief Same as Split with a char array (as a string)
/// but only with one char.
std::vector<std::string> Split(const std::string &str, char c) noexcept;


//----------------------------------------------------------------------------//
// StartsWith                                                                 //
//----------------------------------------------------------------------------//
///-----------------------------------------------------------------------------
/// @brief
///   Determines whether the beginning of this string instance matches
///   the specified string.
/// @param haystack
///   The string that will be searched against.
/// @param needle
///   The string that will be searched in haystack.
/// @param caseSensitive
///   If the search will consider the case in both strings.
/// @returns
///   True if the haystack starts with the needle, false otherwise.
bool StartsWith(
    const std::string &haystack,
    const std::string &needle,
    bool               caseSensitive = true) noexcept;


//----------------------------------------------------------------------------//
// ToLower                                                                    //
//----------------------------------------------------------------------------//
void ToLower_InPlace(std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Returns a copy of this string converted to lowercase.
inline std::string
ToLower(const std::string &str) noexcept
{
    auto new_str = str;
    ToLower_InPlace(new_str);
    return str;
}


//----------------------------------------------------------------------------//
// ToUpper                                                                    //
//----------------------------------------------------------------------------//
void ToUpper_InPlace(std::string &str) noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Returns a copy of this string converted to uppercase.
inline std::string
ToUpper(const std::string &str) noexcept
{
    auto new_str = str;
    ToUpper_InPlace(new_str);
    return str;
}


//----------------------------------------------------------------------------//
// Trim                                                                       //
//----------------------------------------------------------------------------//
void Trim_InPlace(std::string &str, const std::string &chars = " ") noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Removes all leading and trailing white-space characters from the current
///   string object.
/// @param str
///   The string that will be trimmed.
/// @param chars
///   The char array (as a string) that will be trimmed (Default = " " [space]).
/// @returns
///   The string without any chars at both ends.
inline std::string
Trim(const std::string &str, const std::string &chars = " ") noexcept
{
    auto new_str = str;
    Trim_InPlace(new_str);
    return new_str;
}


void TrimEnd_InPlace(std::string &str, const std::string &chars = " ") noexcept;

///-----------------------------------------------------------------------------
/// @brief
///   Removes all trailing occurrences of a set of characters specified
///   in an array from the current const std::string & object.
/// @param str
///   The string that will be trimmed.
/// @param chars
///   The char array (as a string) that will be trimmed (Default = " " [space]).
/// @returns
///   The string without any chars at end.
inline std::string
TrimEnd(const std::string &str, const std::string &chars = " ") noexcept
{
    auto new_str = str;
    TrimEnd_InPlace(new_str);
    return new_str;
}

void TrimStart_InPlace(std::string &str, const std::string &chars = " ") noexcept;


///-----------------------------------------------------------------------------
/// @brief
///   Removes all leading occurrences of a set of characters specified
///   in an array from the current const std::string & object.
/// @param str
///   The string that will be trimmed.
/// @param chars
///   The char array (as a string) that will be trimmed (Default = " " [space]).
/// @returns
///   The string without any chars at beginning.
inline std::string
TrimStart(const std::string &str, const std::string &chars = " ")
{
    auto new_str = str;
    TrimStart_InPlace(new_str);
    return new_str;
}

} // namespace StringUtils
} // namespace acow
