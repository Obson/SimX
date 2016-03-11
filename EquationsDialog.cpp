#include "wx_pch.h"
#include "EquationsDialog.h"
#include "SimXMain.h"

#include "globals.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(EquationsDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(EquationsDialog)
//*)

//(*IdInit(EquationsDialog)
const long EquationsDialog::ID_CHOICE1 = wxNewId();
const long EquationsDialog::ID_STATICTEXT1 = wxNewId();
const long EquationsDialog::ID_TEXTCTRL1 = wxNewId();
const long EquationsDialog::ID_PANEL3 = wxNewId();
const long EquationsDialog::ID_BUTTON1 = wxNewId();
const long EquationsDialog::ID_CHECKLISTBOX1 = wxNewId();
const long EquationsDialog::ID_PANEL4 = wxNewId();
const long EquationsDialog::ID_BUTTON2 = wxNewId();
const long EquationsDialog::ID_BUTTON4 = wxNewId();
const long EquationsDialog::ID_PANEL1 = wxNewId();
const long EquationsDialog::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EquationsDialog,wxDialog)
	//(*EventTable(EquationsDialog)
	//*)
END_EVENT_TABLE()

EquationsDialog::EquationsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(EquationsDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Equations"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	Panel3 = new wxPanel(Panel1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	Choice1 = new wxChoice(Panel3, ID_CHOICE1, wxDefaultPosition, wxSize(50,-1), 0, 0, wxCB_SORT, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice1->SetFocus();
	BoxSizer3->Add(Choice1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl1 = new wxTextCtrl(Panel3, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer3->Add(TextCtrl1, 3, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3->SetSizer(BoxSizer3);
	BoxSizer3->Fit(Panel3);
	BoxSizer3->SetSizeHints(Panel3);
	FlexGridSizer1->Add(Panel3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnAddEquation = new wxButton(Panel1, ID_BUTTON1, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnAddEquation->Disable();
	FlexGridSizer1->Add(btnAddEquation, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel4 = new wxPanel(Panel1, ID_PANEL4, wxDefaultPosition, wxSize(269,112), wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	CheckListBox1 = new wxCheckListBox(Panel4, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(288,240), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	FlexGridSizer1->Add(Panel4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	btnEditEquation = new wxButton(Panel1, ID_BUTTON2, _("Edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btnEditEquation->Disable();
	BoxSizer2->Add(btnEditEquation, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnRemoveEquation = new wxButton(Panel1, ID_BUTTON4, _("Remove"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	btnRemoveEquation->Disable();
	BoxSizer2->Add(btnRemoveEquation, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Panel1->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(Panel1);
	FlexGridSizer1->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxDOUBLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer4->Add(-1,-1,1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(Panel2, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(Panel2, wxID_HELP, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer4->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(BoxSizer4);
	BoxSizer4->Fit(Panel2);
	BoxSizer4->SetSizeHints(Panel2);
	BoxSizer1->Add(Panel2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&EquationsDialog::OnChoice1Select);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&EquationsDialog::OnTextCtrl1Text);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EquationsDialog::OnbtnAddEquationClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EquationsDialog::OnbtnEditEquationClick);
	//*)

	populate();
}

EquationsDialog::~EquationsDialog()
{
	//(*Destroy(EquationsDialog)
	//*)
}

void EquationsDialog::populate()
{
    Choice1->Clear();
    CheckListBox1->Clear();

    if (Expression::haveFreeVariables()) {
        // Create a dropdown for the lhs, containing currently undefined variables
        vector<string> &freeVars = Expression::getFreeVariables();
        for (auto it : freeVars) {
            Choice1->Append(s2ws(it));
        }
        // Set first item as default selection
        Choice1->Enable(true);
        Choice1->SetSelection(0);
        Choice1->SetFocus();
    } else {
        Choice1->Enable(false);
    }

    unordered_map<string, Expression*> &definitions = Expression::getDefinitions();
    for (auto it : definitions) {
        // Specials are now listed separately so don't need to be filtered out.
        CheckListBox1->Append(s2ws(it.first) + _(" = ") + s2ws(it.second->getRHS()));
    }

    btnAddEquation->Enable(!TextCtrl1->GetValue().IsEmpty() && Choice1->GetSelection() != wxNOT_FOUND);
    btnEditEquation->Enable(!CheckListBox1->IsEmpty());
}

Expression *EquationsDialog::createEquation(wxString &wsVar, wxString &wsExp)
{
    string var = ws2s(wsVar);
    string exp = ws2s(wsExp);

    string filtered;
    char last, c;
    for (unsigned int i = 0; i < exp.size(); i++)
    {
        c = exp[i];
        if (last != ' ' || c != ' ' || i == 0) {
            last = c;
            filtered += c;
        }
    }

    cout << "EquationsDialog::createEquation(" << var << "," << filtered << ")" << endl;
    return new Expression(var, filtered);
}

void EquationsDialog::OnbtnAddEquationClick(wxCommandEvent& event)
{
    // Create an expression with the LHS (from Choice1) as its name and RHS
    // as its value. This should automatically add all the required names to
    // the dictionary (via makeToken) so we can then re-populate Choice1.

    /// @todo Build a mechanism for extracting equations from the definitions
    /// vector and use it to repopulate the equations list (CheckListBox1).
    /// Expression::getRHS() will help.

    wxString lhs, rhs;
    wxASSERT(!Choice1.IsEmpty());
    int sel = Choice1->GetSelection();
    lhs = Choice1->GetString(sel);
    rhs = TextCtrl1->GetValue();
    if (rhs.IsEmpty()) {
        wxMessageBox(_("Please enter a value for this variable"), _("Error"), wxICON_ERROR);
    } else {
        createEquation(lhs, rhs.Trim().Trim(false));
        populate();
    }
}

void EquationsDialog::OnChoice1Select(wxCommandEvent& event)
{
    btnAddEquation->Enable(!TextCtrl1->GetValue().IsEmpty());
}

void EquationsDialog::OnTextCtrl1Text(wxCommandEvent& event)
{
    btnAddEquation->Enable(!TextCtrl1->GetValue().IsEmpty() && Choice1->GetSelection() != wxNOT_FOUND);
}

void EquationsDialog::OnbtnEditEquationClick(wxCommandEvent& event)
{
    int sel = CheckListBox1->GetSelection();

    // This parses out the variable name and predicate assuming is was created
    // using the procedure in populate(). If populate is changed this must be
    // updated to match
    wxString str = CheckListBox1->GetString(sel);
    CheckListBox1->Delete(sel);
    int pos = str.rfind(_(" = "));
    wxString var = str.Mid(0, pos);
    wxString rhs = str.Mid(pos + 3);
    Choice1->Clear();
    Choice1->Append(var);
    Choice1->SetSelection(0);
    TextCtrl1->SetValue(rhs);
}
