// std
#include <iostream>
// CoreString
#include "CoreString/CoreString.h"

//------------------------------------------------------------------------------
// Make easier to users use CoreString repository by now making them borther
// with the multiple main functions, while still let us have some "tests"
#define CORESTRING_TESTS_ENABLED 0
#if CORESTRING_TESTS_ENABLED

int main() {
    using namespace std;

    //--------------------------------------------------------------------------
    cout << "Concat: "                                                << endl;
    cout << CoreString::Concat("ola ", "mundo", ' ', 123, '-', 1.23f) << endl;
    cout << endl;

    //--------------------------------------------------------------------------
    cout << "Contains 1: "                                  << endl;
    cout << CoreString::Contains("ola mundo", "ola")        << endl;
    cout << CoreString::Contains("ola mundo", "OLA")        << endl;
    cout << CoreString::Contains("ola mundo", "OLA", false) << endl;
    cout << endl;

    //--------------------------------------------------------------------------
    cout << "Ends With: "                                    << endl;
    cout << CoreString::EndsWith("ola mundo", "undo")        << endl;
    cout << CoreString::EndsWith("ola mundo", "UNDO")        << endl;
    cout << CoreString::EndsWith("ola mundo", "UNDO", false) << endl;
    cout << endl;

    //--------------------------------------------------------------------------
    cout << CoreString::EndsWith("ola mundo", "undo")        << endl;
    cout << CoreString::EndsWith("ola mundo", "UNDO")        << endl;
    cout << CoreString::EndsWith("ola mundo", "UNDO", false) << endl;
    cout << endl;

    //--------------------------------------------------------------------------
    cout << "Index Of: 1"                         << endl;
    cout << CoreString::IndexOf("ola mundo", 'o') << endl;
    cout << CoreString::IndexOf("ola mundo", 'm') << endl;
    cout << CoreString::IndexOf("ola mundo", 'o') << endl;
    cout << CoreString::IndexOf("ola mundo", 'G') << endl;

    //--------------------------------------------------------------------------
    cout << "Index Of: 2"                             << endl;
    cout << CoreString::IndexOf("ola mundo", 'o',  2) << endl;
    cout << CoreString::IndexOf("ola mundo", 'm',  5) << endl;
    cout << CoreString::IndexOf("ola mundo", 'o',  9) << endl;
    cout << CoreString::IndexOf("ola mundo", 'G',123) << endl;

    //--------------------------------------------------------------------------
    cout << "Index Of: 3"                                  << endl;
    cout << CoreString::IndexOf("ola mundo", 'o',  2, 999) << endl;
    cout << CoreString::IndexOf("ola mundo", 'm',  5, 999) << endl;
    cout << CoreString::IndexOf("ola mundo", 'o',  9, 999) << endl;
    cout << CoreString::IndexOf("ola mundo", 'G',123, 999) << endl;

    //--------------------------------------------------------------------------
    cout << "Index Of Any: 1"                          << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG") << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG") << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG") << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG") << endl;

    //--------------------------------------------------------------------------
    cout << "Index Of Any: 2"                               << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG",   2) << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG",   5) << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG",   9) << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG", 123) << endl;

    //--------------------------------------------------------------------------
    cout << "Index Of Any: 3"                                    << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG",   2, 999) << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG",   5, 999) << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG",   9, 999) << endl;
    cout << CoreString::IndexOfAny("ola mundo", "omG", 123, 999) << endl;

    //--------------------------------------------------------------------------
    cout << "Is Null Or White Space: "                << endl;
    cout << CoreString::IsNullOrWhiteSpace("       ") << endl;
    cout << CoreString::IsNullOrWhiteSpace("   2   ") << endl;

    //--------------------------------------------------------------------------
    cout << "Join 1: " << endl;
    cout << CoreString::Join("**", "ola", "mundo", '-', 123, '-', 1.23f) << endl;

    //--------------------------------------------------------------------------
    cout << "Pad Left: "                              << endl;
    cout << CoreString::PadLeft("ola mundo", 80, '-') << endl;
    cout << CoreString::PadLeft("ola mundo", 2, '-')  << endl;

    //--------------------------------------------------------------------------
    cout << "Pad Right: "                              << endl;
    cout << CoreString::PadRight("ola mundo", 80, '-') << endl;
    cout << CoreString::PadRight("ola mundo", 2,  '-') << endl;

    //--------------------------------------------------------------------------
    cout << "Replace: " << endl;
    cout << CoreString::Replace("ola mundo", "ola", "hello") << endl;
    cout << CoreString::Replace("ola mundo", "ola",  "")     << endl;
    cout << CoreString::Replace("ola mundo", "TEST", "")     << endl;

    //--------------------------------------------------------------------------
    cout << "Split 1: " << endl;
    auto v = CoreString::Split("/usr/local/bin/awesome", "/");
    for(const auto &i : v)
        cout << i << endl;

    //--------------------------------------------------------------------------
    cout << "Split 2: " << endl;
    v = CoreString::Split("/usr/local/bin/awesome", "-");
    for(const auto &i : v)
        cout << i << endl;

    //--------------------------------------------------------------------------
    cout << "Split 3: " << endl;
    v = CoreString::Split("/usr/local/bin?awesome", "-/?");
    for(const auto &i : v)
        cout << i << endl;

    //--------------------------------------------------------------------------
    cout << "Starts With: "                                   << endl;
    cout << CoreString::StartsWith("ola mundo", "ola")        << endl;
    cout << CoreString::StartsWith("ola mundo", "OLA")        << endl;
    cout << CoreString::StartsWith("ola mundo", "OLA", false) << endl;
    cout << endl;

    //--------------------------------------------------------------------------
    cout << "To Lower: "                     << endl;
    cout << CoreString::ToLower("Ola Mundo") << endl;

    //--------------------------------------------------------------------------
    cout << "To Upper: "                     << endl;
    cout << CoreString::ToUpper("Ola Mundo") << endl;

    //--------------------------------------------------------------------------
    cout << "Trim:"                          << endl;
    cout << CoreString::Trim("Ola")          << endl;
    cout << CoreString::Trim("  Ola  ")      << endl;
    cout << CoreString::Trim("**Ola**")      << endl;
    cout << CoreString::Trim("**Ola**", "*") << endl;

    //--------------------------------------------------------------------------
    cout << "Trim End:"                         << endl;
    cout << CoreString::TrimEnd("Ola")          << endl;
    cout << CoreString::TrimEnd("  Ola  ")      << endl;
    cout << CoreString::TrimEnd("**Ola**")      << endl;
    cout << CoreString::TrimEnd("**Ola**", "*") << endl;

    //--------------------------------------------------------------------------
    cout << "Trim Start: "                        << endl;
    cout << CoreString::TrimStart("Ola")          << endl;
    cout << CoreString::TrimStart("  Ola  ")      << endl;
    cout << CoreString::TrimStart("**Ola**")      << endl;
    cout << CoreString::TrimStart("**Ola**", "*") << endl;


    return 0;
}
#endif // #if CORESTRING_TESTS_ENABLED
