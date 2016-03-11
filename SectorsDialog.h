#ifndef SECTORSDIALOG_H
#define SECTORSDIALOG_H

#include <vector>

#ifndef WX_PRECOMP
	//(*HeadersPCH(SectorsDialog)
	#include <wx/dialog.h>
	#include <wx/sizer.h>
	#include <wx/button.h>
	#include <wx/textctrl.h>
	#include <wx/listbox.h>
	//*)
#endif
//(*Headers(SectorsDialog)
//*)

#include "SimXMain.h"

class SectorsDialog: public wxDialog
{
	public:

		SectorsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SectorsDialog();

		//(*Declarations(SectorsDialog)
		wxButton* btnUpdateSector;
		wxListBox* ListBox1;
		wxButton* btnRemoveSector;
		wxTextCtrl* TextCtrl1;
		wxTextCtrl* TextCtrl2;
		wxButton* btnAddSector;
		//*)

	protected:

		//(*Identifiers(SectorsDialog)
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_LISTBOX1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		//*)

	private:

		//(*Handlers(SectorsDialog)
		void OnbtnAddSectorClick(wxCommandEvent& event);
		void OnbtnAddSectorClick1(wxCommandEvent& event);
		//*)

		void displaySectors();

		DECLARE_EVENT_TABLE()
};

#endif
