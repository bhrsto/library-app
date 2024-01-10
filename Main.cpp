#include <vcl.h>
#pragma hdrstop
#include <Vcl.ExtCtrls.hpp>
#include <System.SysUtils.hpp>
#include <IdHTTP.hpp>
#include <Vcl.Dialogs.hpp>
#include <Data.DB.hpp>
#include <Data.DB.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <XMLIntf.hpp>

#include "Main.h"
#include "Registracija.h"
#include "Postavke.h"
#include "RegistracijaKorisnika.h"
#include "dataModule.h"
#include <registry.hpp>
#include <memory>

#include "GIzvjestaj.h"
#include "skidanjeDretva.h"
//#include "Encryptor.h"
#include "EncryptorAsymmetric.h"
#include "LIB\\Encryptor.h"
#include "translateForm.h"
#include "Login.h"



using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uTPLb_BaseNonVisualComponent"
#pragma link "uTPLb_Codec"
#pragma link "uTPLb_CryptographicLibrary"
#pragma link "uTPLb_Signatory"
#pragma resource "*.dfm"
TMainForm *MainForm;

int velicinaFonta;
String odabraniFont;
TColor bojaPozadine ;




//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	translation["LKorisnik"] = {
		{
			{"EN", "User:"},
			{"HR", "Korisnik:"}
		}
	};

	translation["GroupBox1"] = {
		{
			{"EN", "User registration and editing:"},
			{"HR", "Registracija i uređivanje korisnika:"}
		}
	};

	translation["BRegistracijaK"] = {
		{
			{"EN", "Registration"},
			{"HR", "Registracija"}
		}
	};

	translation["SekcijaRegistracijaZaposlenika"] = {
		{
			{"EN", "Registration and editing of employees"},
			{"HR", "Registracija i uređivanje zaposlenika"}
		}
	};

	translation["BRegistracijaZ"] = {
		{
			{"EN", "Registration"},
			{"HR", "Registracija"}
		}
	};

	translation["GBIzvjestaj"] = {
		{
			{"EN", "Generating reports per client"},
			{"HR", "Generiranje izvještaja po klijentu"}
		}
	};

	translation["BIzvjestaj"] = {
		{
			{"EN", "Report"},
			{"HR", "Izvjestaj"}
		}
	};

	translation["BPrikaziIzvjestaj"] = {
		{
			{"EN", "Show"},
			{"HR", "Prikazi"}
		}
	};


	translation["BgeneriranjeKljuceva"] = {
		{
			{"EN", "Key generation"},
			{"HR", "Generiranje kljuceva"}
		}
	};

	translation["BzakasnjelePosudbe"] = {
		{
			{"EN", "Overdue loans"},
			{"HR", "Zakasnjele posudbe"}
		}
	};

	translation["Bpreuzmi"] = {
		{
			{"EN", "Download"},
			{"HR", "Preuzmi"}
		}
	};

	translation["BzamjeniBaze"] = {
		{
			{"EN", "Replce data base"},
			{"HR", "Zamjeni Baze"}
		}
	};

	translation["BPostavke"] = {
		{
			{"EN", "Settings"},
			{"HR", "Postavke"}
		}
	};

	translateForm(this, jezik, translation);
}
//---------------------------------------------------------------------------
  //ucitavanje podataka iz ini datoteke
void __fastcall ucitaj()
{
	TIniFile* ini = new TIniFile(GetCurrentDir() + "\\ini.ini");

	odabraniFont = ini->ReadString("Main Window", "Font", "Calibri");
	velicinaFonta = ini->ReadInteger("Main Window", "FontSize", 12);
	bojaPozadine = (TColor)ini->ReadInteger("Main Window", "BackgroundColor", clBtnFace); // Dodano

	delete ini;
	}
//--------------------------------------------------------

void __fastcall promjeni(TForm* forma)
{
	TFont* font = new TFont;
	font->Name = odabraniFont;
	font->Size = velicinaFonta;

	forma->Font->Assign(font);
	forma->Color = bojaPozadine;

	delete font;
}


void __fastcall TMainForm::BRegistracijaZClick(TObject *Sender)
{
	std::unique_ptr<TFRegistracija> Forma(new TFRegistracija(this));
	//TFRegistracija *Forma = new TFRegistracija(this);
	Forma->ShowModal();
	//delete Forma;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BRegistracijaKClick(TObject *Sender)
{
	TRegistracijaK *Forma = new TRegistracijaK(this);
	Forma->ShowModal();
	delete Forma;
}
//--------------------------------------------------
Encryptor* simetricno = nullptr;

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	ucitaj();
	promjeni(this);
	simetricno = new Encryptor(Codec1, CryptographicLibrary1);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BPostavkeClick(TObject *Sender)
{
	TFPostavke *postavke = new TFPostavke(this);
	if (postavke->ShowModal() == mrOk) {
		promjeni(this);

	}
	delete postavke;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------




void __fastcall TMainForm::TCP_serverExecute(TIdContext *AContext)
{

	String prviPaket = AContext->Connection->Socket->ReadLn();
	if(prviPaket == "KLJUCEVI"){
		String naziv = AContext->Connection->Socket->ReadLn();
		int velicina = AContext->Connection->Socket->ReadInt64();

		TFileStream* datoteka = new TFileStream(naziv, fmCreate);
		//std::unique_ptr<TFileStream> fs(new TFileStream(naziv, fmCreate));
		AContext->Connection->Socket->ReadStream(datoteka, velicina);

		delete datoteka;

		TFileStream* datotekaServer = new TFileStream("javniKljucServer.bin",fmOpenRead);
		AContext->Connection->Socket->WriteLn(ExtractFileName(datotekaServer->FileName));
		AContext->Connection->Socket->Write(datotekaServer->Size);
		AContext->Connection->Socket->Write(datotekaServer);
		AContext->Connection->Disconnect();
		delete datotekaServer;

	}
	else if(prviPaket == "PODACI"){

		String kriptiraniUpit = AContext->Connection->Socket->ReadLn();
		String Poruka1;

		unique_ptr<EncryptorAsymmetric> asimetricno(new EncryptorAsymmetric(ACodec, CryptographicLibrary1, Signatory1));


		String imeKlijenta, prezimeKlijenta, sifraKlijenta;
		asimetricno->LoadPrivateKey("privatniKljucServer.bin");
		String Upit = asimetricno->DecryptAsymmetric(kriptiraniUpit);

		TStringList* items = new TStringList;
		items->Delimiter = ',';
		items->DelimitedText = Upit;

		if(items->Count == 3){
		   imeKlijenta = items->Strings[0].Trim();
		   prezimeKlijenta = items->Strings[1].Trim();
		   sifraKlijenta = items->Strings[2].Trim();
		}
		delete items;

		String sqlKorisnikQuery = "SELECT * FROM korisnici "
								  "WHERE ime = :ime AND prezime = :prezime AND ID = :id";
		DataModule1->ADOQueryKORISNICI->SQL->Text = sqlKorisnikQuery;
		DataModule1->ADOQueryKORISNICI->Parameters->ParamByName("ime")->Value = imeKlijenta;
		DataModule1->ADOQueryKORISNICI->Parameters->ParamByName("prezime")->Value = prezimeKlijenta;
		DataModule1->ADOQueryKORISNICI->Parameters->ParamByName("id")->Value = sifraKlijenta;
		DataModule1->ADOQueryKORISNICI->Open();

		String knjige;

		//int idKorisnika = DataModule1->ADOQueryKORISNICI->FieldByName("ID")->AsInteger;

		if (!DataModule1->ADOQueryKORISNICI->IsEmpty()){
			DataModule1->ADOQueryKNJIGE->SQL->Text = "SELECT * FROM knjige "
													"WHERE knjige.idKorisnik = :idKorisnika";
			DataModule1->ADOQueryKNJIGE->Parameters->ParamByName("idKorisnika")->Value = sifraKlijenta;
			DataModule1->ADOQueryKNJIGE->Open();

			knjige = "";

			 while (!DataModule1->ADOQueryKNJIGE->Eof){

				knjige += DataModule1->ADOQueryKNJIGE->FieldByName("naziv")->AsString;
				knjige += "-";
				knjige += DataModule1->ADOQueryKNJIGE->FieldByName("datumVracanja")->AsString;
				knjige += ", ";
				DataModule1->ADOQueryKNJIGE->Next();
			}
		}else{
			 knjige = "Korisnik ne postoji.";
		}

		DataModule1->ADOQueryKORISNICI->Close();
		DataModule1->ADOQueryKNJIGE->Close();

		asimetricno->LoadPublicKey("javniKljucKlijent.bin");
		String kriptiraneKnjige = asimetricno->EncryptAsymmetric(knjige);

		AContext->Connection->Socket->WriteLn(kriptiraneKnjige);

		AContext->Connection->Disconnect();
	}

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
		  TIdSocketHandle *ABinding)
{
   String kriptiraniPisac = BytesToString(AData);



	String pisac = simetricno->DecryptSymmetric(kriptiraniPisac);

	String djela;

	String sqlAutor = "SELECT * FROM knjige "
					  "WHERE pisac = :pisac";
	DataModule1->ADOQueryKNJIGE->SQL->Text = sqlAutor;
	DataModule1->ADOQueryKNJIGE->Parameters->ParamByName("pisac")->Value = pisac;
	DataModule1->ADOQueryKNJIGE->Open();

	if (!DataModule1->ADOQueryKNJIGE->IsEmpty()){


		while (!DataModule1->ADOQueryKNJIGE->Eof){

			djela += DataModule1->ADOQueryKNJIGE->FieldByName("naziv")->AsString;
			djela += ",";
			DataModule1->ADOQueryKNJIGE->Next();
			}
	}
	else{
		djela = "Nema knjizevnih djela";
		}


	DataModule1->ADOQueryKNJIGE->Close();

	String kriptiraniTekst = simetricno->EncryptSymmetric(djela);

	AThread->Server->Send(ABinding->PeerIP, ABinding->PeerPort, kriptiraniTekst);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BIzvjestajClick(TObject *Sender)
{
	String naslov = "Izvjestaj posudenih knjiga po korisniku";

	Izvjestaj *izvjestaj = new Izvjestaj(naslov);
	izvjestaj->GenerirajIzvjestaj();
	//ShowMessage("Izvjestaj je generiran.");
	delete izvjestaj;
}
//---------------------------------------------------------------------------

  void __fastcall TMainForm::BPrikaziIzvjestajClick(TObject *Sender)
{
	  Izvjestaj *izvjestaj = new Izvjestaj(MemoIspis);
	  izvjestaj-> PrikaziIzvjestaj();
	  delete izvjestaj;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::BpreuzmiClick(TObject *Sender)
{
	PreuzimanjeThread *Preuzimanje = new PreuzimanjeThread(true, ProgressBar1, HttpClient,Edit1->Text, LabelPostotak, AEditBrzina, HttpRequest);
	Preuzimanje->FreeOnTerminate = true;
	Preuzimanje->Start();
}


//---------------------------------------------------------------------------

void __fastcall TMainForm::BzamjeniBazeClick(TObject *Sender)
{
	DataModule1->ADOConnection1->Close();

	DataModule1->ADOQueryKORISNICI->Close();
    DataModule1->ADOQueryKNJIGE->Close();
	DataModule1->ADOQueryLOG->Close();

	if (FileExists("baza.accdb"))
	{
		try
		{
			DeleteFile("baza.accdb");
			ShowMessage("Stara baza uspješno izbrisana!");
		}
		catch (Exception &E)
		{
			ShowMessage("Greška pri brisanju stare baze: " + E.Message);
			return;
		}
	}

	if (FileExists("nova_baza.accdb"))
	{
		try
		{
			RenameFile("nova_baza.accdb", "baza.accdb");
			ShowMessage("Nova baza uspješno preimenovana u staru bazu!");
		}
		catch (Exception &E)
		{
			ShowMessage("Greška pri preimenovanju nove baze: " + E.Message);
			return;
		}
	}
	else
	{
		ShowMessage("Nova baza nije pronađena na odredištu.");
		return;
	}

	DataModule1->ADOConnection1->Open();
	DataModule1->ADOQueryKORISNICI->Open();
	DataModule1->ADOQueryKNJIGE->Open();
	DataModule1->ADOQueryLOG->Open();

	ShowMessage("Baza podataka uspješno zamijenjena i veze ponovno otvorene.");
}
//---------------------------------------------------------------------------




void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	delete simetricno;
	//delete asimetricno;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BgeneriranjeKljucevaClick(TObject *Sender)
{
	 if (!FileExists("privatniKljucServer.bin") || !FileExists("javniKljucServer.bin")) {

		  TMemoryStream* privatniKljuc = new TMemoryStream();
		  TMemoryStream* javniKljuc = new TMemoryStream();

		try {
			if(Signatory1->GenerateKeys()){

				Signatory1->StoreKeysToStream(privatniKljuc,TKeyStoragePartSet() << partPrivate);
				Signatory1->StoreKeysToStream(javniKljuc,TKeyStoragePartSet() << partPublic);

				privatniKljuc->SaveToFile("privatniKljucServer.bin");
				javniKljuc->SaveToFile("javniKljucServer.bin");

			}
			ShowMessage("Ključevi su uspešno generisani i sačuvani.");
		} catch (Exception &e) {
			ShowMessage("Greška pri generisanju ključeva: " + e.Message);
		}

		delete privatniKljuc;
		delete javniKljuc;

	} else {
		ShowMessage("Ključevi već postoje.");
	}
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::ComboBox1Change(TObject *Sender)
{
	 translateForm(this, ComboBox1->Text, translation);
	jezik = ComboBox1->Text;
}
//---------------------------------------------------------------------------




