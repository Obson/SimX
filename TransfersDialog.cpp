#include "wx_pch.h"
#include "TransfersDialog.h"
#include "SimXMain.h"
#include "globals.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(TransfersDialog)
	#include <wx/string.h>
	#include <wx/intl.h>
	//*)
#endif
//(*InternalHeaders(TransfersDialog)
//*)

#include <wx/tokenzr.h>

//(*IdInit(TransfersDialog)
const long TransfersDialog::ID_STATICTEXT1 = wxNewId();
const long TransfersDialog::ID_TEXTCTRL1 = wxNewId();
const long TransfersDialog::ID_TEXTCTRL2 = wxNewId();
const long TransfersDialog::ID_STATICTEXT2 = wxNewId();
const long TransfersDialog::ID_CHOICE1 = wxNewId();
const long TransfersDialog::ID_STATICTEXT3 = wxNewId();
const long TransfersDialog::ID_CHOICE2 = wxNewId();
const long TransfersDialog::ID_BUTTON1 = wxNewId();
const long TransfersDialog::ID_LISTBOX1 = wxNewId();
const long TransfersDialog::ID_BUTTON2 = wxNewId();
const long TransfersDialog::ID_BUTTON3 = wxNewId();
const long TransfersDialog::ID_BUTTON4 = wxNewId();
const long TransfersDialog::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TransfersDialog,wxDialog)
	//(*EventTable(TransfersDialog)
	//*)
END_EVENT_TABLE()

TransfersDialog::TransfersDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(TransfersDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;

	Create(parent, wxID_ANY, _("Transfers"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 10, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Transfer"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->SetFocus();
	BoxSizer2->Add(TextCtrl1, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer2->Add(TextCtrl2, 3, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("From"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ddFrom = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer2->Add(ddFrom, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("To"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ddTo = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	FlexGridSizer2->Add(ddTo, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	btnAddTransfer = new wxButton(this, ID_BUTTON1, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnAddTransfer, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
	ListBox1 = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(350,200), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	FlexGridSizer1->Add(ListBox1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	Button2 = new wxButton(this, ID_BUTTON2, _("Update"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(Button2, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Button3 = new wxButton(this, ID_BUTTON3, _("Remove"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer1->Add(Button3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer1->Add(-1,-1,1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button4 = new wxButton(this, ID_BUTTON4, _("Help"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer1->Add(Button4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	btnOK = new wxButton(this, ID_BUTTON5, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	BoxSizer1->Add(btnOK, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransfersDialog::OnbtnAddTransferClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TransfersDialog::OnbtnOKClick);
	//*)

	// Populate dropdowns
	vector<Sector*> &sectors = Sector::getSectors();
	ddFrom->Clear();
	ddTo->Clear();
	if (sectors.size() > 0) {
        for (auto it : sectors) {
            wxString wxs_short = s2ws(it->getName());
            wxString wxs_long = s2ws(it->getLongName());
            ddFrom->Append(wxs_long, (void*)it);
            ddTo->Append(wxs_long, (void*)it);
        }
        ddFrom->SetSelection(0);
        ddTo->SetSelection(0);

	}
    btnAddTransfer->Enable(sectors.size() > 1);

    // Populate transfers listbox
    populateList();

    TextCtrl1->SetFocus();
}

TransfersDialog::~TransfersDialog()
{
	//(*Destroy(TransfersDialog)
	//*)
}

void TransfersDialog::populateList()
{
    vector<Transfer*> &transfers = Transfer::getTransfers();
    ListBox1->Clear();
    for (auto it : transfers) {
        wxString var = s2ws(it->getVarName());
        wxString descr = s2ws(it->getDescription());
        wxString src = s2ws(it->getSourceNameAlt());
        wxString dest = s2ws(it->getDestNameAlt());
        ListBox1->Append(descr + _(" (") + var + _(") : ") + src + _(" to ") + dest);
    }
}

Transfer *TransfersDialog::createTransfer(wxString &to, wxString &from, wxString &name, wxString &descr)
{
    string strVar = ws2s(name);
    string strDescr = ws2s(descr);
    string strFrom = ws2s(from);
    string strTo = ws2s(to);

    return Transfer::create(strTo, strFrom, strVar, strDescr);
}

void TransfersDialog::OnbtnAddTransferClick(wxCommandEvent& event)
{
    wxString wxstrId = TextCtrl1->GetValue();       // c
    wxString wxstrDescr = TextCtrl2->GetValue();    // consumption
    //string strId = string(TextCtrl2->GetValue().mb_str(wxConvISO8859_1));
    //string strDescr = string(TextCtrl1->GetValue().mb_str(wxConvISO8859_1));
    wxString wxstrFrom = ddFrom->GetString(ddFrom->GetCurrentSelection());
    wxStringTokenizer tok1(wxstrFrom, _("\t"));
    wxString wxstrFromShort = tok1.GetNextToken();
    wxString wxstrFromLong = tok1.GetNextToken();

    wxString wxstrTo = ddTo->GetString(ddTo->GetCurrentSelection());
    wxStringTokenizer tok2(wxstrTo, _("\t"));
    wxString wxstrToShort = tok2.GetNextToken();
    wxString wxstrToLong= tok2.GetNextToken();
    //wxString wxstrTo = ddTo->GetData(ddTo->GetCurrentSelection());

    string strVar = ws2s(wxstrId);
    string strDescr = ws2s(wxstrDescr);
    string strFrom = ws2s(wxstrFromShort);
    string strTo = ws2s(wxstrToShort);

    // USE CREATETRANSFER FUNCTION AND REMOVE CALL ON GETTRANSFERS

    createTransfer(wxstrToShort, wxstrFromShort, wxstrId, wxstrDescr);

    // Expression::makeToken(strVar); // moved to Transfer::create(...)

    populateList();
    TextCtrl1->Clear();
    TextCtrl2->Clear();
    TextCtrl1->SetFocus();
}

void TransfersDialog::OnbtnOKClick(wxCommandEvent& event)
{
    EndModal(wxID_OK);
}
