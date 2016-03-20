#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <wx/string.h>

// -----------------------------------------------------------------------------
// These functions help get around the problems converting between wxString and
// standard string representations (C and stl). And a few other things. There's
// been no attempt to be consistent. These are just quick solutions.

// wxString to std::string
std::string ws2s(wxString as);

// std::string to wxString
wxString s2ws(std::string s);

// C string to wxString
wxString cs2ws(const char* s);

// wxString to int
int ws2i(wxString ws);

// wxString to double, or zero if invalid
double ws2d(wxString ws);

// double to wxString
wxString d2ws(double d);

// -----------------------------------------------------------------------------
// Other useful functions not included in STL
bool isparen(char c);


#endif // GLOBALS_H
