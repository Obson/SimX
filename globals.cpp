#include "globals.h"

// -----------------------------------------------------------------------------
// These functions help get around the problems converting between wxString and
// standard string representations (C and stl).
// -----------------------------------------------------------------------------

// wxString to std::string
std::string ws2s(wxString as)
{
    return std::string(as.mb_str(wxConvISO8859_1));
}

// std::string to wxString
wxString s2ws(std::string s)
{
    return wxString((s).c_str(),wxConvISO8859_1);
}

// C string to wxString
wxString cs2ws(const char* s)
{
    return wxString(s,wxConvISO8859_1);
}

// wxString to int
int ws2i(wxString ws)
{
    return wxAtoi(ws);
}

// wxString to double, or zero if invalid
double ws2d(wxString ws)
{
    double res;
    bool OK = ws.ToDouble(&res);
    return (OK ? res : 0);
}

// double to wxString
wxString d2ws(double d)
{
    wxString ws;
    ws << d;
	return ws;
}
