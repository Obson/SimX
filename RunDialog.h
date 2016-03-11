#ifndef RUNDIALOG_H
#define RUNDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(RunDialog)
	#include <wx/checklst.h>
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	//*)
#endif
//(*Headers(RunDialog)
//*)

// For stl containers (specifically, vector). See Que Pasa comment in
// ProbesDialog.h  for more info.
#include "expression.h"

// Note: It would have been better to call this RunOptionsDialog, as it doesn't
// actually run the model, but it's too late now. Amy transfer its content and
// behaviour to a panel on the main window (SimXFrame) anyway.
class RunDialog: public wxDialog
{
	public:

		RunDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~RunDialog();

		vector<string> &getCheckedItems();
		int getNumCycles();

		//(*Declarations(RunDialog)
		wxStaticText* StaticText1;
		wxCheckListBox* CheckListBox1;
		wxTextCtrl* TextCtrl1;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(RunDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_CHECKLISTBOX1;
		//*)

	private:

		//(*Handlers(RunDialog)
		void OnTextCtrl1Text(wxCommandEvent& event);
		//*)

		void populate();
	    vector<string> checkedItems;    // not filled until getCheckedItems() is called

		DECLARE_EVENT_TABLE()
};

#endif
