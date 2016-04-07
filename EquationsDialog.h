#ifndef EQUATIONSDIALOG_H
#define EQUATIONSDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(EquationsDialog)
	#include <wx/checklst.h>
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/panel.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	#include <wx/choice.h>
	//*)
#endif
//(*Headers(EquationsDialog)
//*)

#include "expression.h"


/// @class EquationsDialog
/// Handles manual input and editing of equations connecting the variables that
/// determine the behaviour of the model.

class EquationsDialog: public wxDialog
{
	public:

		EquationsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~EquationsDialog();

        static Expression *createEquation(wxString &wsVar, wxString &wsExp);

		//(*Declarations(EquationsDialog)
		wxButton* btnRemoveEquation;
		wxPanel* Panel1;
		wxButton* btnEditEquation;
		wxButton* btnAddEquation;
		wxStaticText* StaticText1;
		wxPanel* Panel2;
		wxPanel* Panel4;
		wxChoice* Choice1;
		wxCheckListBox* CheckListBox1;
		wxPanel* Panel3;
		wxTextCtrl* TextCtrl1;
		//*)

	protected:

		//(*Identifiers(EquationsDialog)
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_PANEL3;
		static const long ID_BUTTON1;
		static const long ID_CHECKLISTBOX1;
		static const long ID_PANEL4;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_PANEL1;
		static const long ID_PANEL2;
		//*)

        void populate();

	private:

		//(*Handlers(EquationsDialog)
		void OnbtnAddEquationClick(wxCommandEvent& event);
		void OnChoice1Select(wxCommandEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnbtnEditEquationClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
