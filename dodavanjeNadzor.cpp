//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dodavanjeNadzor.h"
#include "nadzor.h"
#include "XMLhandler.h"
#include "translateForm.h"
#include "Main.h"
#include "Login.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFdodavanjeNadzor *FdodavanjeNadzor;
//---------------------------------------------------------------------------
 std::map<String, std::map<String, String>> translation;

__fastcall TFdodavanjeNadzor::TFdodavanjeNadzor(TComponent* Owner, TXMLDocument *xmlDoc, bool n)
	: TForm(Owner), XMLDocument2(xmlDoc), n(n)
{
	translation["Lime"] = {
		{
			{"EN", "Name:"},
			{"HR", "Ime:"}
		}
	};

	translation["Lprezime"] = {
		{
			{"EN", "Surname:"},
			{"HR", "Prezime:"}
		}
	};

	translation["Lvrijeme"] = {
		{
			{"EN", "Time"},
			{"HR", "Vrijeme"}
		}
	};

	translation["BpotvrdiN"] = {
		{
			{"EN", "Confirm"},
			{"HR", "Potvrdi"}
		}
	};

	translateForm(this, jezik, translation);

}

//---------------------------------------------------------------------------
void __fastcall TFdodavanjeNadzor::FormCreate(TObject *Sender)
{
	promjeni(this);
}

//---------------------------------------------------------------------------
void __fastcall TFdodavanjeNadzor::BpotvrdiNClick(TObject *Sender)
{
	 if(n == false){
		if (!Eime->Text.IsEmpty() && !Eprezime->Text.IsEmpty() && !Evrijeme->Text.IsEmpty()) {
			String imeN, prezimeN, vrijemeN;

			imeN = Eime->Text;
			prezimeN = Eprezime->Text;
			vrijemeN = Evrijeme->Text;

			xml *XML1 = new xml(XMLDocument2, imeN, prezimeN, vrijemeN);
			XML1->dodajNadzor();
			delete XML1;

			ModalResult = mrOk;
		}
		else{
			ShowMessage("Sva polja trebaju biti unesena!!!");
		}
	 }

	 else{

		 if (!Eime->Text.IsEmpty() && !Eprezime->Text.IsEmpty() && !Evrijeme->Text.IsEmpty()){
			String imeN = Eime->Text;
			String prezimeN = Eprezime->Text;
			String vrijemeN = Evrijeme->Text;

			if (OdabraniIndeks != -1)
			{
				xml *XML1 = new xml(XMLDocument2, imeN, prezimeN, vrijemeN);
				XML1->urediNadzor(OdabraniIndeks);
				delete XML1;
			}
			ModalResult = mrOk;
		}
		else
		{
			ShowMessage("Sva polja trebaju biti unesena!!!");
		}
   }

}
//---------------------------------------------------------------------------
