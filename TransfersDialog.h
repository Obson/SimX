#ifndef TRANSFERSDIALOG_H
#define TRANSFERSDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(TransfersDialog)
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	#include <wx/choice.h>
	#include <wx/listbox.h>
	//*)
#endif
//(*Headers(TransfersDialog)
//*)

#include "transfer.h"

class TransfersDialog: public wxDialog
{
	public:

		TransfersDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TransfersDialog();

        static Transfer *createTransfer(wxString &to, wxString &from, wxString &name, wxString &descr);

		//(*Declarations(TransfersDialog)
		wxListBox* ListBox1;
		wxButton* Button4;
		wxButton* Button2;
		wxButton* Button3;
		wxStaticText* StaticText1;
		wxChoice* ddTo;
		wxStaticText* StaticText3;
		wxButton* btnAddTransfer;
		wxTextCtrl* TextCtrl1;
		wxStaticText* StaticText2;
		wxChoice* ddFrom;
		wxButton* btnOK;
		wxTextCtrl* TextCtrl2;
		//*)

	protected:

        void populateList();


		//(*Identifiers(TransfersDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT2;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT3;
		static const long ID_CHOICE2;
		static const long ID_BUTTON1;
		static const long ID_LISTBOX1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		//*)

	private:

		//(*Handlers(TransfersDialog)
		void OnbtnAddTransferClick(wxCommandEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
