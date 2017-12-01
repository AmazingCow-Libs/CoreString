#include "../include/CoreString.h"


//------------------------------------------------------------------------------
std::string CoreString::Capitalize(const std::string &str)
{
    if(str.empty())
        return str;

    auto new_string = str;
    new_string[0] = toupper(new_string[0]);

    return new_string;
}


//------------------------------------------------------------------------------
std::string CoreString::Center(
    const std::string &str,
    size_t             length,
    char               c /* = ' ' */)
{
    if(str.size() >= length)
        return str;

    auto total_chars = (length - str.size()) * 2;
    auto fill_str    = std::string(total_chars, c);

    return fill_str + str + fill_str;
}


//------------------------------------------------------------------------------
size_t CoreString::Count(
    const std::string &haystack,
    const std::string &needle,
    size_t             start /* = 0                 */,
    size_t             end   /* = std::string::npos */)
{
    //COWTODO(n2omatt): Implement....
}


//------------------------------------------------------------------------------
std::string CoreString::ExpandTabs(
    const std::string &str,
    size_t             tabSize /* = 8 */)
{
    auto spaces = std::string(tabSize, ' ');
    return CoreString::Replace(str, "\t", spaces);
}


//------------------------------------------------------------------------------
bool CoreString::IsAlNum(const std::string &str)
{
    if(str.empty())
        return false;

    auto it = std::find_if_not(
        std::begin(str),
        std::end(str),
        [](const char c){
            return isalnum(c);
        }
    );

    return it != std::end(str);
}


//------------------------------------------------------------------------------
bool CoreString::IsAlpha(const std::string &str)
{
    if(str.empty())
        return false;

    auto it = std::find_if_not(
        std::begin(str),
        std::end(str),
        [](const char c){
            return isalpha(c);
        }
    );

    return it != std::end(str);
}

//------------------------------------------------------------------------------
bool IsDigit(const std::string &str)
{
    if(str.empty())
        return false;

    auto it = std::find_if_not(
        std::begin(str),
        std::end(str),
        [](const char c){
            return isdigit(c);
        }
    );

    return it != std::end(str);
}


//------------------------------------------------------------------------------
bool CoreString::IsLower(const std::string &str)
{
    if(str.empty())
        return false;

    auto it = std::find_if_not(
        std::begin(str),
        std::end(str),
        [](const char c){
            return islower(c);
        }
    );

    return it != std::end(str);
}

//------------------------------------------------------------------------------
bool IsSpace(const std::string &str)
{
    if(str.empty())
        return false;

    auto it = std::find_if_not(
        std::begin(str),
        std::end(str),
        [](const char c){
            return isspace(c);
        }
    );

    return it != std::end(str);
}


//------------------------------------------------------------------------------
/// @brief
///   Return True if S is a titlecased string and there is at least one
///   character in S, i.e. uppercase characters may only follow uncased
///   characters and lowercase characters only cased ones. Return False
///   otherwise.
bool CoreString::IsTitle(const std::string &str)
{
    //COWTODO(n2omatt): Implement....
}


//------------------------------------------------------------------------------
bool CoreString::IsUpper(const std::string &str)
{
    if(str.empty())
        return false;

    auto it = std::find_if_not(
        std::begin(str),
        std::end(str),
        [](const char c){
            return isupper(c);
        }
    );

    return it != std::end(str);
}


//------------------------------------------------------------------------------
std::string CoreString::SwapCase(const std::string &str)
{
    auto new_string = str;
    std::transform(
        std::begin(new_string),
        std::end(new_string),
        std::begin(new_string),
        [](const char c){
            return (isupper(c)) ? tolower(c) : toupper(c);
        }
    );

    return new_string;
}


//------------------------------------------------------------------------------
/// @brief
///   Return a titlecased version of S, i.e. words start with uppercase
///   characters, all remaining cased characters have lowercase.
std::string CoreString::Title(const std::string &str)
{
    //COWTODO(n2omatt): Implement....
}




//------------------------------------------------------------------------------
// Implemented on CoreString.h
// template <typename T>
// std::string Concat(const std::initializer_list<T> &list)


//------------------------------------------------------------------------------
bool CoreString::Contains(
    const std::string &haystack,
    const std::string &needle,
    bool              caseSensitive /* = true */)
{
    // Simpler case, just forward to find.
    if(caseSensitive)
        return haystack.find(needle) != std::string::npos;

    // Case insensitive case, need to convert the strings.
    auto lower_haystack = ToLower(haystack);
    auto lower_needle   = ToLower(needle);

    return lower_haystack.find(lower_needle) != std::string::npos;
}


//------------------------------------------------------------------------------
bool CoreString::EndsWith(
    const std::string &haystack,
    const std::string &needle,
    bool               caseSensitive /* = true */)
{
    // needle cannot be contained on haystack since it's greater.
    if(haystack.size() < needle.size())
        return false;

    return std::equal(
        std::end(haystack) - needle.size(),
        std::end(haystack),
        std::begin(needle),
        [caseSensitive](const char &c1, const char &c2) {
            if(caseSensitive)
                return c1 == c2;
            return tolower(c1) == tolower(c2);
        }
    );
}


//Replaces one or more format items in a specified string with the string representation of a specified object.
//Format(const std::string &, Object)


//------------------------------------------------------------------------------
size_t CoreString::IndexOf(
    const std::string &str,
    char               c,
    size_t             beginIndex /* = 0                 */,
    size_t             charsCount /* = std::string::npos */)
{
    // Clamp the range.
    if(charsCount == std::string::npos)
        charsCount = str.size() - beginIndex;

    // Cache the iterators.
    auto begin_it = (std::begin(str) + beginIndex);
    auto end_it   = begin_it + charsCount;

    // The begin of string but the chars count will be out of bounds.
    //   This occur when the user asks for a charCount bigger than the
    //   string, and since we're not enforcing it for user's convenience
    //   we must check it here.
    if(end_it > std::end(str))
        end_it = std::end(str);

    auto find_it = std::find(begin_it, end_it, c);
    if(find_it == end_it)
        return std::string::npos;

    return (find_it - begin_it);
}


//------------------------------------------------------------------------------
size_t CoreString::IndexOfAny(
    const std::string &str,
    const std::string &chars,
    size_t             beginIndex /* = 0                 */,
    size_t             charsCount /* = std::string::npos */)
{
    // Clamp the range.
    if(beginIndex + charsCount > str.size())
        charsCount = (str.size() - beginIndex);

    return str.find_first_of(chars.c_str(), beginIndex, charsCount);
}


//------------------------------------------------------------------------------
bool CoreString::IsNullOrWhiteSpace(const std::string &str)
{
    if(str.empty())
        return true;

    return str.find_first_not_of(' ') == std::string::npos;
}


//------------------------------------------------------------------------------
// Implemented in CoreString.h
// template <typename T>
// std::string Join(
//     const std::initializer_list<T> &items,
//     const std::string              &separator = " ")



//------------------------------------------------------------------------------
size_t CoreString::LastIndexOf(
    const std::string &str,
    char               c,
    size_t             beginIndex /* = 0                 */,
    size_t             charsCount /* = std::string::npos */)
{
    // Clamp the range.
    if(charsCount == std::string::npos)
        charsCount = str.size() - beginIndex;

    char buf[2] = {c,'\0'};
    return str.rfind(buf, beginIndex, charsCount);
}


//------------------------------------------------------------------------------
size_t CoreString::LastIndexOfAny(
    const std::string &str,
    const std::string &chars,
    size_t             beginIndex /* = 0                 */,
    size_t             charsCount /* = std::string::npos */)
{
    // Clamp the range.
    if(beginIndex + charsCount > str.size())
        charsCount = (str.size() - beginIndex);

    return str.find_last_of(chars.c_str(), beginIndex, charsCount);
}


//------------------------------------------------------------------------------
std::string CoreString::PadLeft(
    const std::string &str,
    size_t             length,
    char               c /* = ' ' */)
{
    // Already big enough!
    if(str.size() >= length)
        return str;

    return std::string(length - str.size(), c) + str;
}


//------------------------------------------------------------------------------
std::string CoreString::PadRight(
    const std::string &str,
    size_t             length,
    char               c /* = ' ' */)
{
    // Already big enough!
    if(str.size() >= length)
        return str;

    return str + std::string(length - str.size(), c);
}


//------------------------------------------------------------------------------
std::string CoreString::Replace(
    const std::string &str,
    const std::string &what,
    const std::string &to)
{
    // Make a copy, so we can modify it.
    auto new_string = str;

    // Keep searching and replacing the contents of string
    // until we haven't anything to replace.
    while(true)
    {
        auto index = new_string.find(what);

        // We haven't found anything so there's no
        // meaning to continue searching.
        if(index == std::string::npos)
            break;

        new_string.replace(index, what.size(), to);
    }

    return new_string;
}


//------------------------------------------------------------------------------
std::vector<std::string> CoreString::Split(
    const std::string &str,
    const std::string &chars)
{
    auto vec = std::vector<std::string>();
    vec.reserve(str.size() / 2);

    auto index     = 0UL;
    auto new_index = 0UL;
    while(new_index != std::string::npos)
    {
        new_index = str.find_first_of(chars, index);

        auto sub_str = str.substr(index, new_index - index);
        vec.push_back(sub_str);

        index = new_index + 1;
    }

    return vec;
}


//------------------------------------------------------------------------------
bool CoreString::StartsWith(
    const std::string &haystack,
    const std::string &needle,
    bool               caseSensitive /* = true */)
{
    // needle cannot be contained on haystack since it's greater.
    if(haystack.size() < needle.size())
        return false;

    return std::equal(
        std::begin(haystack),
        std::begin(haystack) + needle.size(),
        std::begin(needle),
        [caseSensitive](const char &c1, const char &c2) {
            if(caseSensitive)
                return c1 == c2;
            return tolower(c1) == tolower(c2);
        }
    );
}


//------------------------------------------------------------------------------
std::string CoreString::ToLower(const std::string &str)
{
    auto lower_str = str;
    std::transform(
        std::begin(lower_str),
        std::end  (lower_str),
        std::begin(lower_str),
        [](char c){
            return tolower(c);
        }
    );

    return lower_str;
}


//------------------------------------------------------------------------------
std::string CoreString::ToUpper(const std::string &str)
{
    auto upper_str = str;
    std::transform(
        std::begin(upper_str),
        std::end  (upper_str),
        std::begin(upper_str),
        [](char c){
            return toupper(c);
        }
    );

    return upper_str;
}


//------------------------------------------------------------------------------
std::string CoreString::Trim(
    const std::string &str,
    const std::string &chars /* = " " */)
{
    auto begin = str.find_first_not_of(chars);
    auto end   = str.find_last_not_of (chars);

    return str.substr(begin, end-begin +1);
}


//------------------------------------------------------------------------------
std::string CoreString::TrimEnd(
    const std::string &str,
    const std::string &chars /* = " " */)
{
    auto end = str.find_last_not_of (chars);
    return str.substr(0, end+1);
}


//-----------------------------------------------------------------------------
std::string CoreString::TrimStart(
    const std::string &str,
    const std::string &chars /* = " " */)
{
    auto start = str.find_first_not_of(chars);
    return str.substr(start);
}
