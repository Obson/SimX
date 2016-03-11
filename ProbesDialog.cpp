#include "wx_pch.h"
#include "ProbesDialog.h"

#include "SimXMain.h"

//#include "expression.h"
#include "globals.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(ProbesDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(ProbesDialog)
//*)

//(*IdInit(ProbesDialog)
const long ProbesDialog::ID_TEXTCTRL1 = wxNewId();
const long ProbesDialog::ID_STATICTEXT1 = wxNewId();
const long ProbesDialog::ID_TEXTCTRL2 = wxNewId();
const long ProbesDialog::ID_PANEL2 = wxNewId();
const long ProbesDialog::ID_BUTTON1 = wxNewId();
const long ProbesDialog::ID_STATICTEXT2 = wxNewId();
const long ProbesDialog::ID_TEXTCTRL3 = wxNewId();
const long ProbesDialog::ID_STATICTEXT3 = wxNewId();
const long ProbesDialog::ID_CHECKLISTBOX1 = wxNewId();
const long ProbesDialog::ID_PANEL3 = wxNewId();
const long ProbesDialog::ID_BUTTON2 = wxNewId();
const long ProbesDialog::ID_BUTTON4 = wxNewId();
const long ProbesDialog::ID_PANEL1 = wxNewId();
const long ProbesDialog::ID_PANEL4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ProbesDialog,wxDialog)
	//(*EventTable(ProbesDialog)
	//*)
END_EVENT_TABLE()

unordered_map<string,string> ProbesDialog::probes;

ProbesDialog::ProbesDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ProbesDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;
	wxBoxSizer* BoxSizer5;

	Create(parent, wxID_ANY, _("Probes"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableCol(1);
	FlexGridSizer1->AddGrowableRow(2);
	Panel2 = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	TextCtrl1 = new wxTextCtrl(Panel2, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(30,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->SetFocus();
	BoxSizer2->Add(TextCtrl1, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _(" = "), wxDefaultPosition, wxSize(20,-1), 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl2 = new wxTextCtrl(Panel2, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(210,26), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer2->Add(TextCtrl2, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(BoxSizer2);
	BoxSizer2->Fit(Panel2);
	BoxSizer2->SetSizeHints(Panel2);
	FlexGridSizer1->Add(Panel2, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnAddProbe = new wxButton(Panel1, ID_BUTTON1, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnAddProbe, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer5 = new wxBoxSizer(wxVERTICAL);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Description:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer5->Add(StaticText2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl3 = new wxTextCtrl(Panel1, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer5->Add(TextCtrl3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer5, 1, wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3 = new wxPanel(Panel1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	CheckListBox1 = new wxCheckListBox(Panel3, ID_CHECKLISTBOX1, wxPoint(0,0), wxSize(280,112), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	FlexGridSizer1->Add(Panel3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	Button2 = new wxButton(Panel1, ID_BUTTON2, _("Edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer3->Add(Button2, 0, wxTOP|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button4 = new wxButton(Panel1, ID_BUTTON4, _("Remove"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer3->Add(Button4, 0, wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel1->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(Panel1);
	FlexGridSizer1->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel4 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(Panel4, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(Panel4, wxID_HELP, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer4->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4->SetSizer(BoxSizer4);
	BoxSizer4->Fit(Panel4);
	BoxSizer4->SetSizeHints(Panel4);
	BoxSizer1->Add(Panel4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProbesDialog::OnbtnAddProbeClick);
	//*)

	populate();
}

ProbesDialog::~ProbesDialog()
{
	//(*Destroy(ProbesDialog)
	//*)
}

void ProbesDialog::populate()
{
    CheckListBox1->Clear();

//    unordered_map<string, Expression*> &definitions = Expression::getDefinitions();
//    for (auto it : definitions) {
//        CheckListBox1->Append(s2ws(it.first) + _(" = ") + s2ws(it.second->getRHS()));
//    }

    for (auto it : probes) {
        CheckListBox1->Append(s2ws(it.first) + _(" = ") + s2ws(it.second));
    }

    TextCtrl1->Clear();
    TextCtrl2->Clear();
    TextCtrl3->Clear();

    TextCtrl1->SetFocus();
}

void ProbesDialog::OnbtnAddProbeClick(wxCommandEvent& event)
{
    // Create the equation
    string var = ws2s(TextCtrl1->GetLineText(0));
    unordered_map<string,string>::const_iterator found = probes.find(var);

    if (found != probes.end() || Expression::find(var) != nullptr) {
        wxMessageBox(TextCtrl1->GetLineText(0) + _(" has already been used"), _("Error"), wxICON_ERROR);
        return;
    }

    string exp = ws2s(TextCtrl2->GetLineText(0));
    string descr = ws2s(TextCtrl3->GetLineText(0));
    Expression *expression = new Expression(var, exp, Expression::exp_probe);
    if (expression->error == Expression::none) {
        probes[var] = descr;
        populate();
    }
}

void ProbesDialog::addProbeToIndex(string name, string description)
{
    probes[name] = description;
}

string ProbesDialog::getDescription(string name)
{
    return probes[name];
}

unordered_map<string,string> &ProbesDialog::getIndex()
{
    return probes;
}

void ProbesDialog::clearProbes()
{
    probes.clear();
}


