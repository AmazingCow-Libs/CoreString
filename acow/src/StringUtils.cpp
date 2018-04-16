// Header
#include "acow/include/StringUtils.h"


//----------------------------------------------------------------------------//
// Capitalize                                                                 //
//----------------------------------------------------------------------------//
void
StringUtils::Capitalize_InPlace(std::string &str) noexcept
{
    if(str.empty()) { return; }

    StringUtils::ToLower_InPlace(str);
    str[0] = toupper(str[0]);
}


//----------------------------------------------------------------------------//
// Center                                                                     //
//----------------------------------------------------------------------------//
void
StringUtils::Center_InPlace(
    std::string &str,
    size_t       length,
    char         c /* = ' ' */) noexcept
{
    if(str.size() >= length) { return; }

    auto total_chars = (length - str.size()) * 2;
    auto fill_str    = std::string(total_chars, c);

    str.insert(str.begin(), fill_str);
    str.push_back(fill_str);
}

//----------------------------------------------------------------------------//
// Count                                                                      //
//----------------------------------------------------------------------------//
size_t
StringUtils::Count(
    const std::string &haystack,
    const std::string &needle,
    size_t             start /* = 0                 */,
    size_t             end   /* = std::string::npos */) noexcept
{
    ACOW_ASSERT(
        start >= 0 && start < haystack.size(),
        "start(%d) index isn't in haystack(%s) bounds[0, %d)",
        start,
        haystack.c_str(),
        haystack.size()
    );

    //--------------------------------------------------------------------------
    // Helper checks.
    if(needle.size() > haystack.size()) return 0;
    if(haystack.empty())                return 0;
    if(needle  .empty())                return 0;

    auto count       = 0;
    auto start_index = start;
    auto end_index   = end;

    // Clamp the range.
    if(start + end >= haystack.size())
        end_index = haystack.size() - start;

    while(true)
    {
        if(start_index == std::string::npos)
            return count;

        start_index = haystack.find_first_of(
            needle.c_str(),
            start_index,
            end_index
        );
    }

    // Just to let the compilers happy...
    return 0;
}


//----------------------------------------------------------------------------//
// ExpandTabs                                                                 //
//----------------------------------------------------------------------------//
std::string
StringUtils::ExpandTabs_InPlace(
    std::string &str,
    size_t       tabSize /* = 8 */) noexcept
{
    auto spaces = std::string(tabSize, ' ');
    StringUtils::Replace_InPlace(str, "\t", spaces);
}


//----------------------------------------------------------------------------//
// Is*Something*                                                              //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
bool
StringUtils::IsAlNum(const std::string &str) noexcept
{
    if(str.empty()) { return false; }

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
bool
StringUtils::IsAlpha(const std::string &str) noexcept
{
    if(str.empty()) { return false; }

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
bool
IsDigit(const std::string &str) noexcept
{
    if(str.empty()) { return false; }

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
bool
StringUtils::IsLower(const std::string &str) noexcept
{
    if(str.empty()) { return false; }

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
bool
IsSpace(const std::string &str) noexcept
{
    if(str.empty()) { return false; }

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
bool
StringUtils::IsTitle(const std::string &str) noexcept
{
    const auto size = str.size();
    if(size < 2) { return false; }

    auto curr_upper = isupper(str[0]);
    for(size_t i = 1; i < size; ++i) {
        if(!isalpha(str[i]) { continue; }

        if(!(curr_upper ^ isupper(str[i]))) {
            return false;
        } else {
            curr_upper = !curr_upper;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
bool
StringUtils::IsUpper(const std::string &str) noexcept
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


//----------------------------------------------------------------------------//
// SwapCase                                                                   //
//----------------------------------------------------------------------------//
void
StringUtils::SwapCase_InPlace(std::string &str) noexcept
{
    std::transform(
        std::begin(str),
        std::end  (str),
        std::begin(str),
        [](const char c){
            return (isupper(c)) ? tolower(c) : toupper(c);
        }
    );
}

//----------------------------------------------------------------------------//
// Title                                                                      //
//----------------------------------------------------------------------------//
void
StringUtils::Title_InPlace(std::string &str) noexcept
{
    if(str.empty()) { return false; }

    // COWTODO(n2omatt): Pretty sure that this is wrong...
    auto need_upper = true;
    for(auto &c : title_str)
    {
        if(need_upper)
        {
            c = toupper(c);
            need_upper = false;

            continue;
        }

        c = tolower(c);
    }

    return str;
}



//----------------------------------------------------------------------------//
// Contains                                                                   //
//----------------------------------------------------------------------------//
bool
StringUtils::Contains(
    const std::string &haystack,
    const std::string &needle,
    bool              caseSensitive /* = true */) noexcept
{
    // Simpler case, just forward to find.
    if(caseSensitive)
        return haystack.find(needle) != std::string::npos;

    // Case insensitive case, need to convert the strings.
    auto lower_haystack = ToLower(haystack);
    auto lower_needle   = ToLower(needle);

    return lower_haystack.find(lower_needle) != std::string::npos;
}


//----------------------------------------------------------------------------//
// EndsWith                                                                   //
//----------------------------------------------------------------------------//
bool
StringUtils::EndsWith(
    const std::string &haystack,
    const std::string &needle,
    bool               caseSensitive /* = true */) noexcept
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


//----------------------------------------------------------------------------//
// IndexOf                                                                    //
//----------------------------------------------------------------------------//
size_t
StringUtils::IndexOf(
    const std::string &str,
    char               c,
    size_t             beginIndex /* = 0                 */,
    size_t             charsCount /* = std::string::npos */) noexcept
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
size_t
StringUtils::IndexOfAny(
    const std::string &str,
    const std::string &chars,
    size_t             beginIndex /* = 0                 */,
    size_t             charsCount /* = std::string::npos */) noexcept
{
    // Clamp the range.
    if(beginIndex + charsCount > str.size())
        charsCount = (str.size() - beginIndex);

    //--------------------------------------------------------------------------
    // COWTODO(n2omatt): How we gonna check for all the characters
    //   in the chars string but still respecting the range to be
    //   searched in the str?
    //
    //   The std functions (for what I know now) doesn't provide
    //   this functionality out of the box, so to the sake of
    //   continue the project I'm working on a naive, and
    //   non perfomatic approach is used now.
    //
    //   Fix this soon as possible.

    // I'm creating a copy of string now to make the find_first_of
    // respect the range of str. This is not OK, check the comment
    // above.
    auto temp = std::string(str, beginIndex, charsCount);
    return temp.find_first_of(chars.c_str());
}


//----------------------------------------------------------------------------//
// IsNullOrWhiteSpace                                                         //
//----------------------------------------------------------------------------//
bool
StringUtils::IsNullOrWhiteSpace(const std::string &str) noexcept
{
    if(str.empty())
        return true;

    return str.find_first_not_of(' ') == std::string::npos;
}


//----------------------------------------------------------------------------//
// LastIndexOf                                                                //
//----------------------------------------------------------------------------//
size_t
StringUtils::LastIndexOf(
    const std::string &str,
    char               c,
    size_t             beginIndex /* = 0                 */,
    size_t             charsCount /* = std::string::npos */) noexcept
{
    // Clamp the range.
    if(charsCount == std::string::npos)
        charsCount = str.size() - beginIndex;

    char buf[2] = {c,'\0'};
    return str.rfind(buf, beginIndex, charsCount);
}


//------------------------------------------------------------------------------
size_t
StringUtils::LastIndexOfAny(
    const std::string &str,
    const std::string &chars,
    size_t             beginIndex /* = 0                 */,
    size_t             charsCount /* = std::string::npos */) noexcept
{
    // Clamp the range.
    if(beginIndex + charsCount > str.size())
        charsCount = (str.size() - beginIndex);

    auto search_str = str.substr(beginIndex, charsCount);
    return str.find_last_of(chars.c_str());
}


//----------------------------------------------------------------------------//
// PadLeft                                                                    //
//----------------------------------------------------------------------------//
std::string
StringUtils::PadLeft_Inplace(
    std::string &str,
    size_t      length,
    char        c /* = ' ' */) noexcept
{
    // Already big enough!
    if(str.size() >= length) { return; }

    auto pad = std::string(length - str.size(), c);
    str.insert(str.begin(), pad);
}


//----------------------------------------------------------------------------//
// PadRight                                                                   //
//----------------------------------------------------------------------------//
std::string
StringUtils::PadRight_Inplace(
    std::string &str,
    size_t       length,
    char         c /* = ' ' */) noexcept
{
    // Already big enough!
    if(str.size() >= length) { return; }

    str.push_back(std::string(length - str.size(), c));
}


//----------------------------------------------------------------------------//
// Replace                                                                    //
//----------------------------------------------------------------------------//
void
StringUtils::Replace(
    std::string       &str,
    const std::string &what,
    const std::string &to) noexcept
{
    // Keep searching and replacing the contents of string
    // until we haven't anything to replace.
    while(true) {
        auto index = str.find(what);

        // We haven't found anything so there's no
        // meaning to continue searching.
        if(index == std::string::npos)
            break;

        str.replace(index, what.size(), to);
    }
}


//----------------------------------------------------------------------------//
// Replace                                                                    //
//----------------------------------------------------------------------------//
std::vector<std::string>
StringUtils::Split(
    const std::string &str,
    const std::string &chars) noexcept
{
    auto vec = std::vector<std::string>();
    vec.reserve(str.size() / 2);

    auto index     = 0UL;
    auto new_index = 0UL;
    while(new_index != std::string::npos) {
        new_index = str.find_first_of(chars, index);

        auto sub_str = str.substr(index, new_index - index);
        vec.push_back(sub_str);

        index = new_index + 1;
    }

    return vec;
}

//------------------------------------------------------------------------------
std::vector<std::string>
StringUtils::Split(const std::string &str, char c) noexcept
{
    return StringUtils::Split(str, std::string(1, c));
}


//----------------------------------------------------------------------------//
// StartsWith                                                                 //
//----------------------------------------------------------------------------//
bool
StringUtils::StartsWith(
    const std::string &haystack,
    const std::string &needle,
    bool               caseSensitive /* = true */) noexcept
{
    // needle cannot be contained on haystack since it's greater.
    if(haystack.size() < needle.size()) { return false; }

    return std::equal(
        std::begin(haystack),
        std::begin(haystack) + needle.size(),
        std::begin(needle),
        [caseSensitive](const char &c1, const char &c2) {
            if(caseSensitive) {
                return c1 == c2;
            }
            return tolower(c1) == tolower(c2);
        }
    );
}


//----------------------------------------------------------------------------//
// ToLower                                                                    //
//----------------------------------------------------------------------------//
void
StringUtils::ToLower_InPlace(std::string &str) noexcept
{
    std::transform(
        std::begin(str),
        std::end  (str),
        std::begin(str),
        [](char c){
            return tolower(c);
        }
    );
}

//----------------------------------------------------------------------------//
// ToUpper                                                                    //
//----------------------------------------------------------------------------//
std::string
StringUtils::ToUpper(std::string &str) noexcept
{
    std::transform(
        std::begin(upper_str),
        std::end  (upper_str),
        std::begin(upper_str),
        [](char c){
            return toupper(c);
        }
    );
}


//----------------------------------------------------------------------------//
// Trim                                                                       //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
void
StringUtils::Trim_InPlace(
    std::string       &str,
    const std::string &chars /* = " " */) noexcept
{
    if(str.empty()) { return; }

    auto begin = str.find_first_not_of(chars);
    if(begin == std::string::npos) {
        str = "";
        return;
    }

    auto end = str.find_last_not_of(chars);
    if(end == std::string::npos) {
        str = "";
        return;
    }

    str = str.substr(begin, end-begin +1);
}


//------------------------------------------------------------------------------
void
StringUtils::TrimEnd_InPlace(
    std::string       &str,
    const std::string &chars /* = " " */) noexcept
{
    auto end = str.find_last_not_of(chars);
    str = str.substr(0, end+1);
}


//------------------------------------------------------------------------------
void
StringUtils::TrimStart_InPlace(
    std::string       &str,
    const std::string &chars /* = " " */) noexcept
{
    auto start = str.find_first_not_of(chars);

    // All chars should be trimmed.
    if(start == std::string::npos) {
        str = "";
    } else {
        str = str.substr(start);
    }
}
