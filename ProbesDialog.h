#ifndef PROBESDIALOG_H
#define PROBESDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(ProbesDialog)
	#include <wx/checklst.h>
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/panel.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	//*)
#endif
//(*Headers(ProbesDialog)
//*)

// Que pasa?
// ---------
// I don't understand this, but putting this include here instead of in the .cpp
// file (which is the logical place for it), fixes a problem with unordered_map.
// The logical thing would be to include <unordered_map> rather than
// expression.h here, but if we do this the compiler complains bitterly that
// "unordered_map does not name a type"! This makes no sense at all. I supect
// some kind of interaction between the compiler version, the wxWidgets version
// and, possibly, the way pre-compiled headers are handled -- who knows! I have
// tried upgrading the compiler, and although this is not supposed to be
// possible for Ubuntu 12.04 it seemed to work for the use of unordered_map in
// the non-wxWidgets parts of the code. Anyway, the answer seems to be: leave
// this include where it is...
#include "expression.h"

class ProbesDialog: public wxDialog
{
    friend class SimXFrame;

	public:

		ProbesDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ProbesDialog();

		static unordered_map<string,string> &getIndex();
		static void clearProbes();
		static string getDescription(string);

		//(*Declarations(ProbesDialog)
		wxTextCtrl* TextCtrl3;
		wxPanel* Panel1;
		wxButton* Button4;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxButton* btnAddProbe;
		wxPanel* Panel2;
		wxStaticText* StaticText3;
		wxPanel* Panel4;
		wxCheckListBox* CheckListBox1;
		wxPanel* Panel3;
		wxTextCtrl* TextCtrl1;
		wxStaticText* StaticText2;
		wxTextCtrl* TextCtrl2;
		//*)

	protected:

		//(*Identifiers(ProbesDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL2;
		static const long ID_PANEL2;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT3;
		static const long ID_CHECKLISTBOX1;
		static const long ID_PANEL3;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_PANEL1;
		static const long ID_PANEL4;
		//*)

        void populate();

        // Not to be confused with very similar object declared in Expression
        static unordered_map<string,string> probes;

        // This function does no error checking at all. It simply adds the name
        // and description to the index, so it's the acller's responsibility to
        // ensure that the probe is also listed as an expression. The only
        // reason for calling it that is currently envisaged is when a model is
        // being loaded from a file (hence the declaration of class SimXFrame
        // as friend).
		static void addProbeToIndex(string name, string description);

	private:

		//(*Handlers(ProbesDialog)
		void OnbtnAddProbeClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
