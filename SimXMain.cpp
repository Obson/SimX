/***************************************************************
 * Name:      SimXMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    David W. Brown (studio@cowlstreetpress.co.uk)
 * Created:   2015-06-11
 * Copyright: David W. Brown (www.cowlstreetpress.co.uk)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "SimXMain.h"
#include "SectorsDialog.h"
#include "TransfersDialog.h"
#include "EquationsDialog.h"
#include "ProbesDialog.h"
//#include "RunDialog.h"

#include <wx/msgdlg.h>
#include <wx/textfile.h>
#include <wx/fileconf.h>
#include <wx/arrstr.h>
#include <wx/dir.h>
#include <wx/wfstream.h>

//(*InternalHeaders(SimXFrame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

#include <cstdlib>
#include <cassert>

#include "sector.h"
#include "transfer.h"
#include "globals.h"

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SimXFrame)
const long SimXFrame::ID_STATICTEXT2 = wxNewId();
const long SimXFrame::ID_BUTTON11 = wxNewId();
const long SimXFrame::ID_CHOICE1 = wxNewId();
const long SimXFrame::ID_PANEL5 = wxNewId();
const long SimXFrame::ID_STATICTEXT3 = wxNewId();
const long SimXFrame::ID_CHECKLISTBOX1 = wxNewId();
const long SimXFrame::ID_CHECKBOX1 = wxNewId();
const long SimXFrame::ID_STATICTEXT6 = wxNewId();
const long SimXFrame::ID_BUTTON10 = wxNewId();
const long SimXFrame::ID_PANEL7 = wxNewId();
const long SimXFrame::ID_STATICTEXT1 = wxNewId();
const long SimXFrame::ID_TEXTCTRL1 = wxNewId();
const long SimXFrame::ID_BUTTON5 = wxNewId();
const long SimXFrame::ID_BUTTON3 = wxNewId();
const long SimXFrame::ID_PANEL1 = wxNewId();
const long SimXFrame::ID_PANEL3 = wxNewId();
const long SimXFrame::ID_TEXTCTRL2 = wxNewId();
const long SimXFrame::ID_STATICTEXT5 = wxNewId();
const long SimXFrame::ID_CHECKBOX2 = wxNewId();
const long SimXFrame::ID_TEXTCTRL3 = wxNewId();
const long SimXFrame::ID_PANEL4 = wxNewId();
const long SimXFrame::ID_PANEL2 = wxNewId();
const long SimXFrame::ID_STATICTEXT8 = wxNewId();
const long SimXFrame::ID_BUTTON2 = wxNewId();
const long SimXFrame::ID_BUTTON4 = wxNewId();
const long SimXFrame::ID_PANEL9 = wxNewId();
const long SimXFrame::ID_STATICTEXT7 = wxNewId();
const long SimXFrame::ID_BUTTON6 = wxNewId();
const long SimXFrame::ID_BUTTON7 = wxNewId();
const long SimXFrame::ID_BUTTON8 = wxNewId();
const long SimXFrame::ID_PANEL10 = wxNewId();
const long SimXFrame::ID_STATICTEXT9 = wxNewId();
const long SimXFrame::ID_BUTTON9 = wxNewId();
const long SimXFrame::ID_PANEL8 = wxNewId();
const long SimXFrame::ID_STATICTEXT4 = wxNewId();
const long SimXFrame::ID_PANEL6 = wxNewId();
const long SimXFrame::ID_BUTTON1 = wxNewId();
const long SimXFrame::ID_MENUITEM1 = wxNewId();
const long SimXFrame::idMenuQuit = wxNewId();
const long SimXFrame::idMenuAbout = wxNewId();
const long SimXFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SimXFrame,wxFrame)
    //(*EventTable(SimXFrame)
    //*)
END_EVENT_TABLE()

//vector<Transfer*> transfers;

SimXFrame::SimXFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SimXFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;

    Create(parent, wxID_ANY, _("SimX Control Centre"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1000,585));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMaxSize(wxSize(-1,-1));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    Panel5 = new wxPanel(Panel1, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    BoxSizer6 = new wxBoxSizer(wxVERTICAL);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(Panel5, ID_STATICTEXT2, _("Model"), wxDefaultPosition, wxSize(45,20), 0, _T("ID_STATICTEXT2"));
    BoxSizer11->Add(StaticText2, 0, wxTOP|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 10);
    BoxSizer11->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel5, ID_BUTTON11, _("Reload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    Button1->Disable();
    BoxSizer11->Add(Button1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6->Add(BoxSizer11, 0, wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice1 = new wxChoice(Panel5, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_SORT, wxDefaultValidator, _T("ID_CHOICE1"));
    BoxSizer6->Add(Choice1, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
    Panel5->SetSizer(BoxSizer6);
    BoxSizer6->Fit(Panel5);
    BoxSizer6->SetSizeHints(Panel5);
    BoxSizer2->Add(Panel5, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Tracking"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer2->Add(StaticText3, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox1 = new wxCheckListBox(Panel1, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
    BoxSizer2->Add(CheckListBox1, 1, wxTOP|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    cbTrackAll = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Track intermediate variables"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    cbTrackAll->SetValue(false);
    BoxSizer7->Add(cbTrackAll, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer7, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _("Parameters"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer10->Add(StaticText6, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer10->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnResetParams = new wxButton(Panel1, ID_BUTTON10, _("Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    BoxSizer10->Add(btnResetParams, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer10, 0, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel7 = new wxPanel(Panel1, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    BoxSizer2->Add(Panel7, 1, wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Iterations:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer5->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("100"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetMaxSize(wxSize(40,-1));
    BoxSizer5->Add(TextCtrl1, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    btnContinue = new wxButton(Panel1, ID_BUTTON5, _("Extend"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    btnContinue->Disable();
    BoxSizer5->Add(btnContinue, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnUpdate = new wxButton(Panel1, ID_BUTTON3, _("Update"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer5->Add(btnUpdate, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer5, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER|wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL2"));
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    Panel3 = new wxPanel(Panel2, ID_PANEL3, wxDefaultPosition, wxSize(500,600), wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL3"));
    BoxSizer4->Add(Panel3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel4 = new wxPanel(Panel2, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 5, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    textctrlCaption = new wxTextCtrl(Panel4, ID_TEXTCTRL2, _("Untitled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer1->Add(textctrlCaption, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel4, ID_STATICTEXT5, _("Maximum value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox1 = new wxCheckBox(Panel4, ID_CHECKBOX2, _("auto"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox1->SetValue(true);
    FlexGridSizer1->Add(CheckBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl2 = new wxTextCtrl(Panel4, ID_TEXTCTRL3, _("1000"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl2->Disable();
    FlexGridSizer1->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel4->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel4);
    FlexGridSizer1->SetSizeHints(Panel4);
    BoxSizer4->Add(Panel4, 0, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(BoxSizer4);
    BoxSizer4->Fit(Panel2);
    BoxSizer4->SetSizeHints(Panel2);
    BoxSizer1->Add(Panel2, 2, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Filing"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer3->Add(StaticText8, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    btnSave = new wxButton(this, ID_BUTTON2, _("Save Model As..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(btnSave, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button4 = new wxButton(this, ID_BUTTON4, _("Start New Model"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer3->Add(Button4, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel9 = new wxPanel(this, ID_PANEL9, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    BoxSizer3->Add(Panel9, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Setup"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer3->Add(StaticText7, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    btnSectors = new wxButton(this, ID_BUTTON6, _("Sectors"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer3->Add(btnSectors, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTransfers = new wxButton(this, ID_BUTTON7, _("Transfers"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer3->Add(btnTransfers, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnEquations = new wxButton(this, ID_BUTTON8, _("Equations"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer3->Add(btnEquations, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel10 = new wxPanel(this, ID_PANEL10, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    BoxSizer3->Add(Panel10, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Monitoring"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer3->Add(StaticText9, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    btnProbes = new wxButton(this, ID_BUTTON9, _("Probes"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    BoxSizer3->Add(btnProbes, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel8 = new wxPanel(this, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    BoxSizer3->Add(Panel8, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Legend"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer3->Add(StaticText4, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Panel6 = new wxPanel(this, ID_PANEL6, wxDefaultPosition, wxSize(150,-1), 0, _T("ID_PANEL6"));
    Panel6->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    BoxSizer3->Add(Panel6, 1, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(Button3, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    mnuSelectFolder = new wxMenuItem(Menu1, ID_MENUITEM1, _("Select Folder"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(mnuSelectFolder);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[2] = { -24, -60 };
    int __wxStatusBarStyles_1[2] = { wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(2,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(2,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnButton1Click1);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SimXFrame::OnButton1Click);
    Connect(ID_CHECKLISTBOX1,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&SimXFrame::OnCheckListBox1Toggled);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SimXFrame::OncbTrackAllClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnbtnResetParamsClick);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&SimXFrame::OnTextCtrl1Text);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnbtnContinueClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnCheckListBox1Toggled);
    Panel3->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SimXFrame::OnPanel3Paint,0,this);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SimXFrame::OnCheckBox1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnbtnSaveClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnButton4Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnbtnSectorsClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnButton6Click);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnbtnEquationsClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnbtnProbesClick1);
    Panel6->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SimXFrame::OnPanel6Paint,0,this);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SimXFrame::OnQuit);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SimXFrame::OnmnuSelectFolderSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SimXFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SimXFrame::OnAbout);
    //*)

    // parameter_container = FlexGridSizer2;

    loadFilenames();

    // To clear the chart prior to redrawing, set clear_only to true and call
    // Window.Refresh.
    clear_only = false;

    colours[0] = wxRED;
    colours[1] = wxGREEN;
    colours[2] = wxBLUE;
    colours[3] = wxCYAN;
    colours[4] = new wxColour(0x00, 0x45, 0x86);
    colours[5] = new wxColour(0x00, 0x84, 0xd1);
    colours[6] = new wxColour(0xff, 0xd3, 0x20);
    colours[7] = new wxColour(0x57, 0x9d, 0x1c);
    colours[8] = new wxColour(0x7e, 0x00, 0x21);
    colours[9] = new wxColour(0x83, 0xca, 0xff);
    colours[10] = new wxColour(0x31, 0x40, 0x04);
    colours[11] = new wxColour(0xae, 0xcf, 0x00);
    colours[12] = new wxColour(0x4b, 0x1f, 0x6f);
    colours[13] = new wxColour(0xff, 0x95, 0x0e);
    colours[14] = new wxColour(0xcf, 0x00, 0x0b);
    colours[15] = new wxColour(0xff, 0x42, 0x0e);

    // Set up special built-in expressions. This is kept separate from user
    // definitions so should remain intact whenever a model is loaded from a file
    string T("T");
    new Expression(T, Expression::sp_time);

    ////////////////////////////////////////////////////////////////////////////
    //                                                                        //
    // How to pass member functions as arguments (keep for future reference)  //
    //                                                                        //
    // Simplifying the syntax:                                                //
    // typedef int(SimXFrame::*mp)();                                         //
    // mp *f;                                                                 //
    //                                                                        //
    // Initialised declarations:                                              //
    // int(SimXFrame::*pmf)() = &SimXFrame::getPeriod;                        //
    // Expression *special = new Expression(string("T"), pmf);                //
    //                                                                        //
    ////////////////////////////////////////////////////////////////////////////

    wxString msg = wxString(_("SimX version "))
                    << cs2ws(AutoVersion::_UBUNTU_VERSION_STYLE)
                    << wxString(_(" (Linux), revision "))
                    << cs2ws(AutoVersion::_FULLVERSION_STRING)
                    << wxString(_("-"))
                    << cs2ws(AutoVersion::_STATUS_SHORT);
    StatusBar1->SetStatusText(msg, 0);
    StatusBar1->SetStatusText(wxDateTime::Now().Format(), 1);

    // Initialise button states...

    // An equation can only be created for an existing free (i.e. undefined)
    // variable, so we disable the equations button until a free variable has
    // been created, either as a transfer or on the rhs of another equation
    manageEquationsButton();
}

SimXFrame::~SimXFrame()
{
    //(*Destroy(SimXFrame)
    //*)
}

void SimXFrame::loadFilenames()
{
    wxDir dir(wxGetCwd());
    wxString test = dir.GetName();
    wxString filename;
    bool cont = dir.GetFirst(&filename, _("*.sim"));
    while (cont) {
        Choice1->Append(filename);  // replace this with model name from file
        cont = dir.GetNext(&filename);
    }
}

int SimXFrame::getPeriod()
{
    return period;
}

void SimXFrame::clearChart()
{
    max_value = 0;
    period = 0;

    Sector::clearBalances();

    if (!chart.empty()) {
        for (auto it : chart) {
            delete it.second;   // delete the vector containing the series values
        }
        chart.clear();
    }

}

void SimXFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void SimXFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxString(_("This is SimX version "))
                    << cs2ws(AutoVersion::_UBUNTU_VERSION_STYLE)
                    << wxString(_(" (Linux only), revision "))
                    << cs2ws(AutoVersion::_FULLVERSION_STRING)
                    << wxString(_("-"))
                    << cs2ws(AutoVersion::_STATUS_SHORT)
                    << wxString(_("\n\nIt was created using "))
                    << wxbuildinfo(long_f)
                    << _(" with Code::Blocks 10.05 (binary install).\n\n")
                    << _("Source code is available from david@cowlstreetpress.co.uk.\n\n")
                    << _("The program is currently under development and documentation is not yet available.");
    wxMessageBox(msg, _("About SimX"));
}

void SimXFrame::line(wxPaintDC &dc, int w, int h, int x1, int y1, int x2, int y2)
{
    dc.DrawLine(x1 + x_disp, -y1 + 1 + h/2, x2 + x_disp, -y2 + 1 + h/2);
}

const wxColour *SimXFrame::getColour(int x)
{
    return colours[x % 15];
}

/// @todo (david#5#): Consider using spline instead of line segments for
/// smoother appearance.void SimXFrame::OnPanel3Paint(wxPaintEvent& event)
{
    cout << "SimXFrame::OnPanel3Paint()" << endl;

    int w, h;
    wxPaintDC dc(Panel3);
    Panel3->GetSize(&w, &h);

    dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    wxPen myPen(*wxLIGHT_GREY, 2, wxSOLID);
    dc.SetPen(myPen);

    // Draw border
    dc.DrawRectangle(1,1,w-1,h-1);

    // Draw axes
    dc.DrawLine(x_disp, 1, x_disp, h - 1);
    dc.DrawLine(x_disp - 10, 1 + h/2, w, 1 + h/2);

    cout << "SimXFrame::OnPanel3Paint(): about to draw chart" << endl;

    // Draw chart
    if (!chart.empty() && !clear_only)
    {
        cout << "SimXFrame::OnPanel3Paint(): chart not empty" << endl;

        // Calculate scaling factors so graph will fit in panel
        double x_incr = double(w - 20) / range;
        int datum;
        int mv = CheckBox1->IsChecked() ? max_value : ws2i(TextCtrl2->GetLineText(0));

        if (mv < 1) {
            mv = 1;
            datum = 1;
        } else {
            datum = int(pow(10, (floor(log10(mv)))));
        }

        double y_incr = double(h) / (2.2 * mv);
        int col = 0;

        cout << "SimXFrame::OnPanel3Paint(): x_incr = " << x_incr
            << ", range = " << range << ", y_incr = " << y_incr
            << ", datum = " << datum << ", mv = " << mv << endl;

        int ypos;
        if (datum >= 10) {
            int step = datum / 10;
            for (int y = step; ; y += step) {
                ypos = (h/2) - (y_incr * y);
                if (ypos < 0) {
                    break;
                }
                bool maj = (y % datum == 0);
                dc.DrawLine((maj ? - 10 : -5) + x_disp, ypos, x_disp, ypos);
                ypos = (h/2) + (y_incr * y);
                dc.DrawLine((maj ? -10 : -5) + x_disp, ypos, x_disp, ypos);
            }
        }

        wxFont font(10, wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL, false);
        dc.SetFont(font);

        int ypos_down;
        for (int n = datum, ypos_up = (h/2) - (y_incr * n);
            ypos_up > 0;
            n += datum, ypos_up = (h/2) - (y_incr * n))
        {
            cout << "SimXFrame::OnPanel3Paint(): n = " << n << ", ypos_up = " << ypos_up << endl;
            ypos_down = (h/2) + (y_incr * n);
            wxString number_up;
            wxString number_down;
            number_up << n;
            number_down << _("-") << n;
            dc.DrawText(number_up, 5, ypos_up - 8);
            dc.DrawText(number_down, 5, ypos_down - 8);
        }
        cout << "SimXFrame::OnPanel3Paint(): Axes drawn" << endl;

        for (auto it : chart)
        {
            // Change pen colour for each series
            const wxColour *colour = getColour(col++);
            wxPen myPen(*colour, 3, wxSOLID);
            dc.SetPen(myPen);

            int x = 0;
            double y = 0, last = 0;
            for (auto it2 : *(it.second)) {
                y = it2;
                if (x > 0) {
                    line(dc, w, h, x_incr * x, y_incr * last, x_incr * (x + 1),
                         y_incr * y);
                }
                last = y;
                x += 1;
            }
        }
    }
    clear_only = false;

    cout << "SimXFrame::OnPanel3Paint() returns" << endl;
}

Sector *SimXFrame::createSector(wxString &name, wxString &descr)
{
    string strName = ws2s(name);
    string strDescr = ws2s(descr);
    return Sector::create(strName, strDescr);
}

void SimXFrame::loadFile()
{
    wxDir dir(wxGetCwd());
    int sel = Choice1->GetSelection();
    if (sel == -1) {
        return;
    }

    fname = dir.GetName() + _("/") + Choice1->GetString(sel);

    clearAll();

    wxFileConfig iniFile(wxEmptyString, wxEmptyString, fname, wxEmptyString,
                         wxCONFIG_USE_LOCAL_FILE
                         );
    iniFile.Read(_("model"), &caption);
    textctrlCaption->SetValue(caption);

    // Enumeration variables
    wxString str;
    long dummy;

    wxArrayString wasSectors;
    wxArrayString wasTransfers;
    wxArrayString wasTxDescrs;
    wxArrayString wasEquations;
    wxArrayString wasPredicates;
    wxArrayString wasProbes;

    if (iniFile.HasGroup(_("/sectors"))) {
        iniFile.SetPath(_("/sectors"));
        wxString wsName, wsDescr;
        bool OK = iniFile.GetFirstEntry(wsName, dummy);
        while (OK) {
            iniFile.Read(wsName, &wsDescr);
            createSector(wsName, wsDescr);
            OK = iniFile.GetNextEntry(wsName, dummy);
        }
    }

    if (iniFile.HasGroup(_("/transfers"))) {
        iniFile.SetPath(_("/transfers"));
        bool OK = iniFile.GetFirstEntry(str, dummy);
        while (OK) {
            wasTransfers.Add(str);
            wxString descr;
            iniFile.Read(str, &descr);
            wasTxDescrs.Add(descr);
            OK = iniFile.GetNextEntry(str, dummy);
        }
    }

    int numTransfers = wasTransfers.GetCount();
    for (int i = 0; i < numTransfers; i++) {
        wxString name = wasTransfers[i];
        wxString txDescr = wasTxDescrs[i];
        wxString source;
        wxString dest;
        wxString path = _("/transfers/") + name;
        iniFile.SetPath(path);
        iniFile.Read(_("source"), &source);
        iniFile.Read(_("dest"), &dest);
        TransfersDialog::createTransfer(dest, source, name, txDescr);
    }

    if (iniFile.HasGroup(_("/equations"))) {
        iniFile.SetPath(_("/equations"));
        bool OK = iniFile.GetFirstEntry(str, dummy);
        while (OK) {
            wxString wsPred;
            wasEquations.Add(str);
            iniFile.Read(str, &wsPred);
            EquationsDialog::createEquation(str, wsPred);
            OK = iniFile.GetNextEntry(str, dummy);
        }
    }

    /// @todo (david#3#): Investigate: imported probes don't seem to work    // Probes are just equations at present (although set up slightly
    // differently), but this could change.
    if (iniFile.HasGroup(_("/probes"))) {
        iniFile.SetPath(_("/probes"));
        bool OK = iniFile.GetFirstEntry(str, dummy);
        while (OK) {
            wxString wsPred;
            wasProbes.Add(str);
            iniFile.Read(str, &wsPred);
            EquationsDialog::createEquation(str, wsPred);
            ProbesDialog::addProbeToIndex(ws2s(str), "Probe");    // *** need to add description
            OK = iniFile.GetNextEntry(str, dummy);
        }
    }

    modified = false;
    Button4->Enable(true);
    showRunOptions();
}

void SimXFrame::OnButton1Click(wxCommandEvent& event)
{
    Button1->Enable(true);
    loadFile();
}

void SimXFrame::clearAll()
{
    // Clear everything
    Sector::clear();
    clearChart();
    Expression::clearAll();
    ProbesDialog::clearProbes();
    Transfer::clear();

    // Display empty chart
    CheckListBox1->Clear();
    Panel6->Refresh();
    Panel3->Refresh();

    setDirty();
}

void SimXFrame::setDirty()
{
    if (!modified) {
        textctrlCaption->AppendText(_(" (modified)"));
        modified = true;
    }
}


void SimXFrame::OnButton4Click(wxCommandEvent& event)
{
    // Remove current model ready to start a new one

    clearAll();
    modified = false;
    textctrlCaption->SetValue(_("Untitled"));

    Choice1->Clear();   // remove all items from the control
    loadFilenames();    // reload it
    showRunOptions();   // ensure that the parameter list is cleared
}

bool SimXFrame::nudge()
{
    cout << "SimXFrame::nudge(): calling Transfer::execAll(" << period << ")" << endl;
    if (Transfer::execAll(period))
    {
        for (auto it : chart)
        {
            string var = it.first;
            cout << "SimXFrame::nudge(): evaluating " << var << " for period " << period << endl;
            Expression *exp = Expression::find(var);
            wxASSERT_MSG(exp != nullptr, _("Could not find expression named " + s2ws(var)));
            if (exp->evaluate(period)) {
                double val = exp->value();
                cout << "SimXFrame::nudge(): value returned for " << var << " is " << val << endl;
                if (fabs(val) > max_value) {
                    max_value = fabs(val);
                }
                chart[var]->push_back(val);
            } else {
                wxMessageBox(_("Could not evaluate " + s2ws(var) + _("\n") + s2ws(exp->error_string())));
            }
        }
        return true;
    }

    return false;
}

double SimXFrame::getParameterValue(string name)
{
    for (auto it : params) {
        if (it.str == name) {
            return ws2d(it.txt->GetValue());
        }
    }

    // Shouldn't happen
    wxFAIL_MSG(_("Unrecognised parameter ") + s2ws(name));
}

void SimXFrame::showRunOptions(bool clear)
{
    if (clear) {
        CheckListBox1->Clear();
    }

    parameter_container = new wxFlexGridSizer(0, 6, 0, 0);
    parameter_container->AddGrowableCol(0);
    parameter_container->AddGrowableCol(2);
    parameter_container->AddGrowableCol(4);

    unordered_map<string, Expression*> &definitions = Expression::getDefinitions();
    unordered_map<string, Expression*> &probes = Expression::getProbes();

    parameter_container->Clear();
    Layout();

    if (!params.empty()) {
        for (auto it : params) {
            it.lab->Destroy();
            it.txt->Destroy();
        }
        params.clear();
    }

    for (auto it : definitions) {
        string name = it.first;
        Expression *exp = it.second;
        if (exp->isSectorBalance()) {
            CheckListBox1->Append(s2ws(exp->getSector()->getLongName()) + _(" sector balance"));
        } else {
            Transfer *t = Transfer::find(name);
            if (t != nullptr || cbTrackAll->IsChecked()) {
                string descr = (t == nullptr ? "..." : t->getDescription());
                CheckListBox1->Append(s2ws(name) + _("\t") + s2ws(descr));
            }
        }

        if (exp->isParameter())
        {
            wxStaticText *label = new wxStaticText(
                Panel7, wxNewId(), s2ws(name) + _(" ="), wxDefaultPosition, wxDefaultSize, 0);

            parameter_container->Add(
                label, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

            wxTextCtrl *txtctrl = new wxTextCtrl(
                Panel7, wxNewId(), d2ws(exp->getDefault()), wxDefaultPosition,
                wxSize(50,-1), 0, wxDefaultValidator/*, _T("ID_TEXTCTRL4")*/);

            parameter_container->Add(
                txtctrl, 1,
                wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND,
                5);

            Parameter p;
            p.str = name;
            p.lab = label;
            p.txt = txtctrl;
            params.push_back(p);
        }
    }

    for (auto it : probes) {
        string name = it.first;
        Expression *exp = it.second;
        CheckListBox1->Append(s2ws(name) + _("\t") + s2ws(ProbesDialog::getDescription(name)));

        /// @todo It doesn't make sense for probes to be parameters but as we
        /// don't prevent this from happening we have to allow for the
        /// possibility
        if (exp->isParameter())
        {
            wxStaticText *label = new wxStaticText(
                Panel7, wxNewId(), s2ws(name) + _(" ="), wxDefaultPosition, wxDefaultSize, 0);

            parameter_container->Add(
                label, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

            wxTextCtrl *txtctrl = new wxTextCtrl(
                Panel7, wxNewId(), d2ws(exp->getDefault()), wxDefaultPosition,
                wxSize(50,-1), 0, wxDefaultValidator/*, _T("ID_TEXTCTRL4")*/);

            parameter_container->Add(
                txtctrl, 1,
                wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND,
                5);

            Parameter p;
            p.str = name;
            p.lab = label;
            p.txt = txtctrl;
            params.push_back(p);
        }
    }

    Panel7->SetSizer(parameter_container);
    parameter_container->Fit(Panel7);
    parameter_container->SetSizeHints(Panel7);

    Layout();   // The missing link!
}

void SimXFrame::writeChartToFile()
{
    if (chart.empty() || range == 0) {
        return;
    }

    wxTextFile tsvFile(fname + _(".tab"));
    tsvFile.Create();   // deletes existing, if any

    // Output headings
    bool first = true;
    stringstream ss;
    for (auto it : chart) {
        if (first) {
            first = false;
        } else {
            ss << "\t ";
        }
        ss << '\"' << it.first << '\"';
    }
    tsvFile.AddLine(s2ws(ss.str()));

    for (int i = 0; i < range; i++) {
        first = true;
        ss.str("");
        for (auto it : chart) {
            if (first) {
                first = false;
            } else {
                ss << "\t ";
            }
            Series *series = it.second;
            ss << '\"' << (*series)[i] << '\"';
        }
        tsvFile.AddLine(s2ws(ss.str()));
    }

    tsvFile.Write();
    tsvFile.Close();
}

void SimXFrame::drawChart(bool cont)
{
    if (!cont) {
        cout << "SimXFrame::drawChart(): starting";
        clear_only = true;
        Panel3->Refresh();
        Panel3->Update();
        wxYield();
        //::wxMilliSleep(100);

        vector<string> checkedItems;
        int nItems = CheckListBox1->GetCount();
        if (nItems > 0) {
            for (int i = 0; i < nItems; i++) {
                if (CheckListBox1->IsChecked(i)) {
                    checkedItems.push_back(ws2s(CheckListBox1->GetString(i)));
                }
            }
        } else {
            return;
        }


        clearChart();

        for (auto it : checkedItems)
        {
            // checkedItems includes description, prefixed by \t
            string s = it;
            int pos = s.find_first_of('\t');
            Series *ser = new Series;
            chart[s.substr(0, pos)] = ser;
        }

        Expression::revertAll();
    }

    for (auto it : params) {
        /// @note Ths is a bit silly. We could just as easily have stored a
        /// pointer to the expression and then we wouldn't have to look it up
        /// each and every time.
        Expression *exp = Expression::find(it.str);
        wxASSERT_MSG(exp != nullptr, _("Expression " + s2ws(it.str) + _(" not found")));
        exp->setValue(ws2d(it.txt->GetValue()));
    }

    // Execute requested number of cycles. This is where we update the period.
    // It shouldn't normally be done anywhere else
    range = ws2i(TextCtrl1->GetValue());
    for (period = (cont ? period : 0); period <= range; period++) {
        if (!nudge()) {
            return;
        }
    }

    writeChartToFile();
    Panel3->Refresh();
    Panel6->Refresh();

    cout << "SimXFrame::drawChart(): returns" << endl;
}

void SimXFrame::OnbtnSectorsClick(wxCommandEvent& event)
{
    SectorsDialog dlg(this);
    if (dlg.ShowModal() == wxID_OK/* && !modified*/) {
        showRunOptions();   ///< testing
        setDirty();
    }
}

/// This function (despite the name) is called when btnTransfers is clicked.
void SimXFrame::OnButton6Click(wxCommandEvent& event)
{
    TransfersDialog dlg(this);
    if (dlg.ShowModal() == wxID_OK/* && !modified*/) {
        showRunOptions();   ///< testing
        setDirty();
        manageEquationsButton();
    }
}

void SimXFrame::OnbtnEquationsClick(wxCommandEvent& event)
{
    EquationsDialog dlg(this);
    if (dlg.ShowModal() == wxID_OK/* && !modified*/) {
        showRunOptions();
        setDirty();
        manageEquationsButton();
    }
}

void SimXFrame::manageEquationsButton()
{
    // Uncomment the following line to enable/disable the Transfers button
    // depending on the existence of free variables. Doesn't seem a good idea
    // at the moment as we might wish to interrogate the equations even if
    // there is nothing left to define.

    // btnEquations->Enable(Expression::haveFreeVariables());

    // Small change to test git processing.
}

void SimXFrame::OnChoice1Select(wxCommandEvent& event)
{
}

void SimXFrame::OnCheckListBox1Toggled(wxCommandEvent& event)
{
    drawChart();
    //btnContinue->Enable(paused);
}


void SimXFrame::OnPanel6Paint(wxPaintEvent& event)
{
    int w, h;
    wxPaintDC dc(Panel6);
    Panel6->GetSize(&w, &h);

    dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    // Draw border
    wxPen myPen(*wxLIGHT_GREY, 2, wxSOLID);
    dc.SetPen(myPen);
    dc.DrawRectangle(1,1,w-1,h-1);

    wxPen textPen(*wxBLACK, 1, wxSOLID);

    if (!chart.empty() && !clear_only)
    {
        wxFont font(10, wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL, false);
        dc.SetFont(font);

        int y = 5;
        int col = 0;

        for (auto it : chart)
        {
            cout << "SimXFrame::OnPanel6Paint(): col = " << col << endl;

            dc.SetPen(textPen);
            dc.DrawText(s2ws(it.first), 10, y);

            // Change pen colour for each series
            const wxColour *lineColour = getColour(col++);
            wxPen myPen(*lineColour, 4, wxSOLID);
            dc.SetPen(myPen);
            dc.DrawLine(w - 50, y + 10, w - 15, y + 10);

            y += 20;
        }
    }
    cout << "SimXFrame::OnPanel6Paint(): returns" << endl;
}

void SimXFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
    btnUpdate->Enable(true);
    btnContinue->Enable(ws2i(TextCtrl1->GetValue()) > period);
}

void SimXFrame::OnbtnSaveClick(wxCommandEvent& event)
{
    // Save the current model
    wxFileDialog saveFileDialog(this,
                                _("Save SimX file"), wxGetCwd(), _(""),
                                _("SimX files (*.sim)|*.sim"),
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT
                                );

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxFileConfig iniFile(wxEmptyString, wxEmptyString, saveFileDialog.GetPath(),
                         wxEmptyString, wxCONFIG_USE_LOCAL_FILE
                         );

    iniFile.Write(_("model"), textctrlCaption->GetValue());

    vector<Sector*> sectors = Sector::getSectors();
    for (auto it : sectors) {
        iniFile.Write(_("/sectors/") + s2ws(it->getName()),
                      s2ws(it->getDescription())
                      );
    }

    vector<Transfer*> transfers = Transfer::getTransfers();
    for (auto it : transfers) {
        iniFile.Write(_("/transfers/") + s2ws(it->getVarName()),
                      s2ws(it->getDescription())
                      );
        iniFile.Write(_("/transfers/") + s2ws(it->getVarName()) + _("/source"),
                      s2ws(it->getSource()->getName())
                      );
        iniFile.Write(_("/transfers/") + s2ws(it->getVarName()) + _("/dest"),
                      s2ws(it->getDest()->getName())
                      );
    }

    unordered_map<string, Expression*> definitions = Expression::getDefinitions();
    for (auto it : definitions) {
        Expression *e = it.second;
        if (!e->isSectorBalance()) {
            iniFile.Write(_("/equations/") + s2ws(it.first),
                          s2ws(it.second->getRHS())
                          );
        }
    }

    iniFile.Flush();
    Choice1->Clear();
    loadFilenames();
}

void SimXFrame::OncbTrackAllClick(wxCommandEvent& event)
{
    showRunOptions(!cbTrackAll->IsChecked());
}

void SimXFrame::OnCheckBox1Click(wxCommandEvent& event)
{
    TextCtrl2->Enable(!CheckBox1->IsChecked());
}

void SimXFrame::OnbtnContinueClick(wxCommandEvent& event)
{
    btnContinue->Enable(false);
    drawChart(true);
}

void SimXFrame::OnbtnResetParamsClick(wxCommandEvent& event)
{
    for (auto it : params) {
        it.txt->SetValue(d2ws((Expression::find(it.str))->getDefault()));
    }
}

void SimXFrame::OnButton1Click1(wxCommandEvent& event)
{
    loadFile();
}

void SimXFrame::OnmnuSelectFolderSelected(wxCommandEvent& event)
{
    wxDir dir(wxGetCwd());
    wxDirDialog dlg(NULL, _("Choose directory"), dir.GetName());
    if (dlg.ShowModal() == wxID_OK) {
        wxSetWorkingDirectory(dlg.GetPath());
        Choice1->Clear();
        loadFilenames();
    }
}

void SimXFrame::OnbtnProbesClick1(wxCommandEvent& event)
{
    ProbesDialog dlg(this);
    if (dlg.ShowModal() == wxID_OK) {
        showRunOptions();
        setDirty();
    }
}
