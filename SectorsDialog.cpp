#include "wx_pch.h"
#include "SectorsDialog.h"
#include "globals.h"

//#include "expression.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(SectorsDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(SectorsDialog)
//*)

//(*IdInit(SectorsDialog)
const long SectorsDialog::ID_TEXTCTRL2 = wxNewId();
const long SectorsDialog::ID_TEXTCTRL1 = wxNewId();
const long SectorsDialog::ID_BUTTON1 = wxNewId();
const long SectorsDialog::ID_LISTBOX1 = wxNewId();
const long SectorsDialog::ID_BUTTON2 = wxNewId();
const long SectorsDialog::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SectorsDialog,wxDialog)
	//(*EventTable(SectorsDialog)
	//*)
END_EVENT_TABLE()

SectorsDialog::SectorsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SectorsDialog)
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Sectors"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(40,26), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	TextCtrl2->SetMaxLength(10);
	TextCtrl2->SetFocus();
	BoxSizer2->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(TextCtrl1, 4, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnAddSector = new wxButton(this, ID_BUTTON1, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(btnAddSector, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	ListBox1 = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(-1,150), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	BoxSizer3->Add(ListBox1, 4, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxVERTICAL);
	btnUpdateSector = new wxButton(this, ID_BUTTON2, _("Update"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer4->Add(btnUpdateSector, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnRemoveSector = new wxButton(this, ID_BUTTON3, _("Remove"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer4->Add(btnRemoveSector, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer4, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
	BoxSizer1->Add(BoxSizer3, 4, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_HELP, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer1->Add(StdDialogButtonSizer1, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 10);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SectorsDialog::OnbtnAddSectorClick1);
	//*)

    displaySectors();
}

SectorsDialog::~SectorsDialog()
{
	//(*Destroy(SectorsDialog)
	//*)
}

void SectorsDialog::displaySectors()
{
	vector<Sector*> &sectors = Sector::getSectors();
	ListBox1->Clear();
	for (auto it : sectors) {
	    ListBox1->Append(s2ws(it->getLongName()));
	}
}

void SectorsDialog::OnbtnAddSectorClick1(wxCommandEvent& event)
{
    if (!TextCtrl2->IsEmpty())
    {
        wxString wsName = TextCtrl2->GetValue();
        wxString wsDescr = TextCtrl1->GetValue();

        string str = ws2s(wsName);

        if (Sector::exists(str)) {
            wxMessageBox(_("A sector with that name already exists"), _("Error"), wxICON_ERROR);
        } else if (!isupper(str[0])) {
            wxMessageBox(_("Sector names must begin with a capital letter"), _("Error"), wxICON_ERROR);
        } else if (str.back() == '\'') {
            wxMessageBox(_("Sector names must not end with a \' character"), _("Error"), wxICON_ERROR);
        } else {
            SimXFrame::createSector(wsName, wsDescr);
            displaySectors();
            TextCtrl1->Clear();
            TextCtrl2->Clear();
            TextCtrl2->SetFocus();
        }
    }
}
