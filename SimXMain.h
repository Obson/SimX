/***************************************************************
 * Name:      SimXMain.h
 * Purpose:   Defines Application Frame
 * Author:    David W. Brown (studio@cowlstreetpress.co.uk)
 * Created:   2015-06-11
 * Copyright: David W. Brown (www.cowlstreetpress.co.uk)
 * License:
 **************************************************************/

#ifndef SIMXMAIN_H
#define SIMXMAIN_H

//(*Headers(SimXFrame)
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
//*)

#include <wx/colour.h>
#include <wx/textfile.h>
#include <wx/richtext/richtextctrl.h>

#include <iostream>
#include <vector>
#include <array>
#include <thread>
#include <cstdlib>  // strtol
#include <sstream>  // stringstream
#include <string>

#include <iostream>
#include <fstream>

#include "version.h"

#include "sector.h"
#include "transfer.h"

/// @todo (david#2#): Improve top-level usability.class SimXFrame: public wxFrame
{
public:

    SimXFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~SimXFrame();

    void clearChart();
    bool nudge();

    static Sector *createSector(wxString &name, wxString &descr);

    int getPeriod();

private:

    const wxColour *getColour(int);

    typedef vector<double> Series;
    unordered_map<string, Series*> chart;
    void showRunOptions(bool clear = true);
    void drawChart(bool cont = false);
    void drawLegend();
    void writeChartToFile();
    void loadFile();
    void loadFilenames();

    void clearAll();
    void setDirty();
    void manageEquationsButton();

    struct Parameter {
        string str;
        wxStaticText *lab;
        wxTextCtrl *txt;
    };

    vector<Parameter> params;

    double getParameterValue(string str);

    //(*Handlers(SimXFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnPanel3Paint(wxPaintEvent& event);
    void OnButton1Click(wxCommandEvent& event);
    void OnTextCtrl2TextEnter(wxCommandEvent& event);
    void OnButton4Click(wxCommandEvent& event);
    void OnbtnRunClick(wxCommandEvent& event);
    void OnbtnSectorsClick(wxCommandEvent& event);
    void OnButton6Click(wxCommandEvent& event);
    void OnbtnProbesClick(wxCommandEvent& event);
    void OnbtnEquationsClick(wxCommandEvent& event);
    void OnChoice1Select(wxCommandEvent& event);
    void OnCheckListBox1Toggled(wxCommandEvent& event);
    void OnPanel6Paint(wxPaintEvent& event);
    void OnTextCtrl1Text(wxCommandEvent& event);
    void OnbtnSaveClick(wxCommandEvent& event);
    void OncbTrackAllClick(wxCommandEvent& event);
    void OnCheckBox1Click(wxCommandEvent& event);
    void OncbxPauseClick(wxCommandEvent& event);
    void OnbtnContinueClick(wxCommandEvent& event);
    void OnbtnResetParamsClick(wxCommandEvent& event);
    void OnButton1Click1(wxCommandEvent& event);
    void OnmnuSelectFolderSelected(wxCommandEvent& event);
    void OnbtnProbesClick1(wxCommandEvent& event);
    //*)


    void line(wxPaintDC &dc, int w, int h, int x1, int y1, int x2, int y2);
    int period, duration, range;
    double min_value, max_value;

    wxString fname;
    wxString caption;

    bool clear_only;
    int x_disp = 45;
    bool modified = false;
    bool paused = false;

    const wxColour *colours[16];

    //(*Identifiers(SimXFrame)
    static const long ID_STATICTEXT2;
    static const long ID_BUTTON11;
    static const long ID_CHOICE1;
    static const long ID_PANEL5;
    static const long ID_STATICTEXT3;
    static const long ID_CHECKLISTBOX1;
    static const long ID_CHECKBOX1;
    static const long ID_STATICTEXT6;
    static const long ID_BUTTON10;
    static const long ID_PANEL7;
    static const long ID_STATICTEXT1;
    static const long ID_TEXTCTRL1;
    static const long ID_BUTTON5;
    static const long ID_BUTTON3;
    static const long ID_PANEL1;
    static const long ID_PANEL3;
    static const long ID_TEXTCTRL2;
    static const long ID_STATICTEXT5;
    static const long ID_CHECKBOX2;
    static const long ID_TEXTCTRL3;
    static const long ID_PANEL4;
    static const long ID_PANEL2;
    static const long ID_STATICTEXT8;
    static const long ID_BUTTON2;
    static const long ID_BUTTON4;
    static const long ID_PANEL9;
    static const long ID_STATICTEXT7;
    static const long ID_BUTTON6;
    static const long ID_BUTTON7;
    static const long ID_BUTTON8;
    static const long ID_PANEL10;
    static const long ID_STATICTEXT9;
    static const long ID_BUTTON9;
    static const long ID_PANEL8;
    static const long ID_STATICTEXT4;
    static const long ID_PANEL6;
    static const long ID_BUTTON1;
    static const long ID_MENUITEM1;
    static const long idMenuQuit;
    static const long idMenuAbout;
    static const long ID_STATUSBAR1;
    //*)

    static const long ID_LEGEND;

    //(*Declarations(SimXFrame)
    wxPanel* Panel6;
    wxPanel* Panel1;
    wxPanel* Panel7;
    wxStatusBar* StatusBar1;
    wxMenuItem* mnuSelectFolder;
    wxButton* btnContinue;
    wxButton* btnResetParams;
    wxButton* Button4;
    wxButton* Button1;
    wxCheckBox* CheckBox1;
    wxButton* Button3;
    wxPanel* Panel8;
    wxPanel* Panel9;
    wxStaticText* StaticText1;
    wxPanel* Panel10;
    wxPanel* Panel2;
    wxStaticText* StaticText3;
    wxPanel* Panel4;
    wxButton* btnTransfers;
    wxButton* btnSectors;
    wxPanel* Panel5;
    wxChoice* Choice1;
    wxStaticText* StaticText8;
    wxCheckListBox* CheckListBox1;
    wxButton* btnUpdate;
    wxPanel* Panel3;
    wxStaticText* StaticText7;
    wxTextCtrl* TextCtrl1;
    wxStaticText* StaticText4;
    wxStaticText* StaticText5;
    wxStaticText* StaticText2;
    wxTextCtrl* textctrlCaption;
    wxStaticText* StaticText6;
    wxButton* btnEquations;
    wxButton* btnProbes;
    wxButton* btnSave;
    wxStaticText* StaticText9;
    wxTextCtrl* TextCtrl2;
    wxCheckBox* cbTrackAll;
    //*)

    wxRichTextCtrl *legend;
    wxFlexGridSizer *parameter_container;

    DECLARE_EVENT_TABLE()
};

#endif // SIMXMAIN_H
