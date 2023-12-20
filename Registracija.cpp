//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <System.Classes.hpp>

#include "Registracija.h"

#include "dataModule.h"
#include "nadzor.h"
#include "dodavanjeNadzor.h"
#include "XMLhandler.h"
#include "translateForm.h"
#include "Main.h"
#include "Login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uTPLb_BaseNonVisualComponent"
#pragma link "uTPLb_CryptographicLibrary"
#pragma link "uTPLb_Hash"
#pragma resource "*.dfm"
TFRegistracija *FRegistracija;
//---------------------------------------------------------------------------
__fastcall TFRegistracija::TFRegistracija(TComponent* Owner)
	: TForm(Owner)
{
	translation["BdodajRadnika"] = {
		{
			{"EN", "Add user:"},
			{"HR", "Dodaj radnika:"}
		}
	};

	translation["Bazuiraj"] = {
		{
			{"EN", "Update"},
			{"HR", "Azuriraj"}
		}
	};

	translation["Bizbris"] = {
		{
			{"EN", "Delete"},
			{"HR", "Izbrisi"}
		}
	};

	translation["Bosvjezi"] = {
		{
			{"EN", "Refresh"},
			{"HR", "Osvjezi"}
		}
	};

	translation["Label2"] = {
		{
			{"EN", "Name"},
			{"HR", "Ime"}
		}
	};

	translation["Label3"] = {
		{
			{"EN", "Surname"},
			{"HR", "Prezime"}
		}
	};

	translation["Label4"] = {
		{
			{"EN", "Password"},
			{"HR", "Sifra"}
		}
	};

	translation["Bobrisi"] = {
		{
			{"EN", "Delete"},
			{"HR", "Obrisi"}
		}
	};


	translation["Bdodaj"] = {
		{
			{"EN", "Add"},
			{"HR", "Dodaj"}
		}
	};

	translation["Buredi"] = {
		{
			{"EN", "Edit"},
			{"HR", "Uredi"}
		}
	};


	translateForm(this, jezik, translation);

	if (jezik == "EN") {
		ListView1->Columns->Items[0]->Caption = "Name";
		ListView1->Columns->Items[1]->Caption = "Surname";
		ListView1->Columns->Items[2]->Caption = "Time";
	} else {
		ListView1->Columns->Items[0]->Caption = "Ime";
		ListView1->Columns->Items[1]->Caption = "Prezime";
		ListView1->Columns->Items[2]->Caption = "Vrijeme";
	}

}
//---------------------------------------------------------------------------

void __fastcall napuniList(TXMLDocument *XMLDoc, TListView *ListView1){
	_di_IXMLnadzorType nadzor = Getnadzor(XMLDoc);

	ListView1->Clear();

	for (int i = 0; i<nadzor->Count; i++){
		ListView1->Items->Add();
		ListView1->Items->Item[i]->Caption = nadzor->korsinik[i]->ime;
		ListView1->Items->Item[i]->SubItems->Add(nadzor->korsinik[i]->prezime);
		ListView1->Items->Item[i]->SubItems->Add(nadzor->korsinik[i]->vrijeme);
	}
}

 //---------------------------------------------------------------------------
void __fastcall TFRegistracija::dodajNadzor(String imeN, String prezimeN, String vrijemeN){
	_di_IXMLnadzorType nadzor = Getnadzor(FRegistracija->XMLDocument2);
	_di_IXMLkorsinikType korsinik = nadzor->Add();

	korsinik->ime = imeN;
	korsinik->prezime = prezimeN;
	korsinik->vrijeme = vrijemeN;
	FRegistracija->XMLDocument2->SaveToFile(FRegistracija->XMLDocument2->FileName);
}
   //---------------------------------------------------------------------------
void __fastcall TFRegistracija::FormCreate(TObject *Sender)
{
	promjeni(this);

	DataModule1->ADOQueryLOG->SQL->Text = "SELECT * FROM login";
	DataModule1->ADOQueryLOG->Open();

	for (int i = 0; i < DBGrid1->FieldCount; i++){
		DBGrid1->Columns->Items[i]->Width = 80;
	}

	napuniList(XMLDocument2, ListView1);
}

//---------------------------------------------------------------------------

void __fastcall osvjezi(TXMLDocument *XMLDoc, TListView *ListView1){
	napuniList(XMLDoc, ListView1);
	ListView1->Repaint();
}

//---------------------------------------------------------------------------
void __fastcall TFRegistracija::BobrisiClick(TObject *Sender)
{
	int indeks = ListView1->ItemIndex;
	xml *XML1 = new xml(XMLDocument2, indeks);
	XML1->izbrisiNadzor();
	delete XML1;

	osvjezi(XMLDocument2, ListView1);
}
//---------------------------------------------------------------------------


void __fastcall TFRegistracija::BdodajClick(TObject *Sender)
{
	TFdodavanjeNadzor *Forma = new TFdodavanjeNadzor(this, XMLDocument2, false);
	if (Forma->ShowModal() == mrOk)
	{
		osvjezi(XMLDocument2, ListView1);
	}
	delete Forma;
}

//---------------------------------------------------------------------------

void __fastcall TFRegistracija::BurediClick(TObject *Sender)
{
	int indeks = ListView1->Selected->Index;
	if (indeks != -1)
	{
		TFdodavanjeNadzor *Forma = new TFdodavanjeNadzor(this, XMLDocument2, true);
		Forma->OdabraniIndeks = indeks;  // Postavi selektirani indeks

        Forma->Eime->Text = ListView1->Selected->Caption;
		Forma->Eprezime->Text = ListView1->Selected->SubItems->Strings[0];
		Forma->Evrijeme->Text = ListView1->Selected->SubItems->Strings[1];

		if (Forma->ShowModal() == mrOk)
		{
			osvjezi(XMLDocument2, ListView1);
		}
		delete Forma;
	}
	else
	{
        ShowMessage("Nijedna stavka nije selektirana!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TFRegistracija::BdodajRadnikaClick(TObject *Sender)
{
	String Ime = Edit2->Text;
	String Prezime = Edit3->Text;
	String Sifra = Edit4->Text;
	String Admin = Edit5->Text;
	String IDzaposlenik = IntToStr(globalID);


	String sol = Ime + Prezime;
	Hash->HashId = "native.hash.SHA-256";
	Hash->HashString(sol, TEncoding::UTF8);


	String sazetaSol = Stream_To_Hex(Hash->HashOutputValue);
	String sifraSaSoli = sazetaSol + Sifra;

	Hash->HashId = "native.hash.SHA-512";
	Hash->HashString(sifraSaSoli, TEncoding::UTF8);
	String pravaSifra = Stream_To_Hex(Hash->HashOutputValue);


	TIdHTTP *HTTP = new TIdHTTP(NULL);
	String URL = "http://localhost:8080/dodavanjeRadnika";

	// Konstruirajte JSON objekt s podacima koje �elite poslati
	String json = "{\"Ime\":\"" + Ime + "\",\"Prezime\":\"" + Prezime + "\",\"Sifra\":\"" + pravaSifra + "\",\"Admin\":\"" + Admin + "\",\"IDzaposlenik\":\"" + IDzaposlenik + "\"}";
	TStringStream *podaci = new TStringStream(json);
	try
	{
		HTTP->Request->ContentType = "application/json";

		// Postavite sadr�aj streama na JSON podatke


		// Po�aljite JSON podatke kao telo HTTP POST zahtjeva
		String ResponseText = HTTP->Post(URL, podaci);

		// Obrada odgovora ako je potrebno
		ShowMessage(ResponseText); // Prikazivanje odgovora u dijalo�kom oknu (mo�ete prilagoditi na�in prikaza odgovora)
	}
	__finally
	{
		delete HTTP;
		delete podaci;
	}
}

//---------------------------------------------------------------------------

void __fastcall TFRegistracija::BosvjeziClick(TObject *Sender)
{
    DataModule1->ADOQueryLOG->SQL->Text = "SELECT * FROM login";
	DataModule1->ADOQueryLOG->Open();

	for (int i = 0; i < DBGrid1->FieldCount; i++){
		DBGrid1->Columns->Items[i]->Width = 80;
	}
}
//---------------------------------------------------------------------------



void __fastcall TFRegistracija::BazuirajClick(TObject *Sender)
{
	String Ime = Edit2->Text;
    String Prezime = Edit3->Text;
    String ID = Edit1->Text;
    String Sifra = Edit4->Text;
    String Admin = Edit5->Text;
	String IDzaposlenik = IntToStr(globalID);

	String sol = Ime + Prezime;
	Hash->HashId = "native.hash.SHA-256";
	Hash->HashString(sol, TEncoding::UTF8);


	String sazetaSol = Stream_To_Hex(Hash->HashOutputValue);
	String sifraSaSoli = sazetaSol + Sifra;

	Hash->HashId = "native.hash.SHA-512";
	Hash->HashString(sifraSaSoli, TEncoding::UTF8);
	String pravaSifra = Stream_To_Hex(Hash->HashOutputValue);

	TIdHTTP *HTTP = new TIdHTTP(NULL);
	String URL = "http://localhost:8080/urediRadnika";

	// Konstruirajte JSON objekt s podacima koje �elite poslati
	String json = "{\"Ime\":\"" + Ime + "\",\"Prezime\":\"" + Prezime + "\",\"ID\":\"" + ID + "\",\"Sifra\":\"" + pravaSifra + "\",\"Admin\":\"" + Admin + "\",\"IDzaposlenik\":\"" + IDzaposlenik + "\"}";
	TStringStream *podaci = new TStringStream(json);
	try
	{
		HTTP->Request->ContentType = "application/json";

		String ResponseText = HTTP->Put(URL, podaci);

        // Obrada odgovora ako je potrebno
        ShowMessage(ResponseText); // Prikazivanje odgovora u dijalo�kom oknu (mo�ete prilagoditi na�in prikaza odgovora)
    }
    __finally
    {
		delete HTTP;
		delete podaci; // Oslobodite memoriju za slanje podataka
	}

}

//---------------------------------------------------------------------------

void __fastcall TFRegistracija::BizbrisClick(TObject *Sender)
{
	String Ime = Edit2->Text;
	String Prezime = Edit3->Text;
	String IDbrisanje = Edit1->Text;
	String IDzaposlenik = IntToStr(globalID);


	TIdHTTP *HTTP = new TIdHTTP(NULL);
	String URL = "http://localhost:8080/izbrisiRadnika";
	URL += "?Ime=" + Ime + "&Prezime=" + Prezime + "&ID=" + IDbrisanje + "&IDzaposlenik=" + IDzaposlenik;

	try
	{
		HTTP->Request->ContentType = "application/x-www-form-urlencoded";
		String ResponseText = HTTP->Delete(URL); // Ovdje koristimo odgovaraju�i URL za dodavanje radnika
		// Obrada odgovora ako je potrebno
		ShowMessage(ResponseText); // Prikazivanje odgovora u dijalo�kom oknu (mo�ete prilagoditi na�in prikaza odgovora)
	}
	__finally
	{
		delete HTTP;
	}
}
//---------------------------------------------------------------------------

