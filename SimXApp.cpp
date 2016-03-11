/***************************************************************
 * Name:      SimXApp.cpp
 * Purpose:   Code for Application Class
 * Author:    David W. Brown (studio@cowlstreetpress.co.uk)
 * Created:   2015-06-11
 * Copyright: David W. Brown (www.cowlstreetpress.co.uk)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "SimXApp.h"

//(*AppHeaders
#include "SimXMain.h"
#include <wx/image.h>
//*)

#include "version.h"

#include <iostream>

IMPLEMENT_APP(SimXApp);

bool SimXApp::OnInit()
{
    cout << "SimxApp::OnInit(): SimX starting" << endl;

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SimXFrame* Frame = new SimXFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
