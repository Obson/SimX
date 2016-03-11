#include "wx_pch.h"
#include "RunDialog.h"
#include "globals.h"
#include "ProbesDialog.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(RunDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(RunDialog)
#include <wx/button.h>
//*)

//#include "expression.h"
#include "sector.h"
#include "transfer.h"

//(*IdInit(RunDialog)
const long RunDialog::ID_STATICTEXT1 = wxNewId();
const long RunDialog::ID_TEXTCTRL1 = wxNewId();
const long RunDialog::ID_STATICTEXT2 = wxNewId();
const long RunDialog::ID_CHECKLISTBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(RunDialog,wxDialog)
	//(*EventTable(RunDialog)
	//*)
END_EVENT_TABLE()

RunDialog::RunDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(RunDialog)
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;
	
	Create(parent, wxID_ANY, _("Run Model"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Number of iterations:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("50"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->SetFocus();
	BoxSizer2->Add(TextCtrl1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Check quantities to include in the chart:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer1->Add(StaticText2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckListBox1 = new wxCheckListBox(this, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(0,200), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	BoxSizer1->Add(CheckListBox1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer3->Add(StdDialogButtonSizer1, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&RunDialog::OnTextCtrl1Text);
	//*)

	populate();
}

RunDialog::~RunDialog()
{
	//(*Destroy(RunDialog)
	//*)
}


void RunDialog::populate()
{
    CheckListBox1->Clear();

    unordered_map<string, Expression*> &definitions = Expression::getDefinitions();
    for (auto it : definitions) {
        string name = it.first;
        Expression *exp = it.second;
        if (exp->isSectorBalance()) {
            CheckListBox1->Append(s2ws(exp->getSector()->getLongName()) + _(" sector balance"));
        } else {
            Transfer *t = Transfer::find(name);
            if (t != nullptr) {
                string descr = t->getDescription();
                CheckListBox1->Append(s2ws(name) + _("\t") + s2ws(descr));
            }
        }
        /*
        Transfer *t = Transfer::find(name);
        if (t != nullptr) {
            string descr = t->getDescription();
            CheckListBox1->Append(s2ws(name) + _("\t") + s2ws(descr));
        }
        */
    }
/*
	vector<Sector*> &sectors = Sector::getSectors();
	for (auto it : sectors) {
	    CheckListBox1->Append(s2ws(it->getLongName()) + _(" (stock") + _(")"));
	}
*/
    unordered_map<string,string> &probes = ProbesDialog::getIndex();
    for (auto it : probes) {
	    CheckListBox1->Append(s2ws(it.first) + _("\t") + s2ws(it.second));
    }
}

vector<string> &RunDialog::getCheckedItems()
{
    int nItems = CheckListBox1->GetCount();
    for (int i = 0; i < nItems; i++) {
        if (CheckListBox1->IsChecked(i)) {
            checkedItems.push_back(ws2s(CheckListBox1->GetString(i)));
        }
    }
    return checkedItems;
}

int RunDialog::getNumCycles()
{
    return ws2i(TextCtrl1->GetValue());
}

void RunDialog::OnTextCtrl1Text(wxCommandEvent& event)
{
}
