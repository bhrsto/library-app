//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<string>
#include <future>
#include <string>
#include <vector>
#include <sstream>


#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uTPLb_BaseNonVisualComponent"
#pragma link "uTPLb_Codec"
#pragma link "uTPLb_CryptographicLibrary"
#pragma link "uTPLb_Signatory"
#pragma resource "*.dfm"
TForm1 *Form1;



void translateForm(TForm* Form, String Language, const std::map<String, std::map<String, String>>& translation){
	for (int i = 0; i < Form->ComponentCount; i++) // iterate though all components on the form
	   for (auto it_ComponentName = translation.begin(); it_ComponentName != translation.end(); it_ComponentName++)
		  if(Form->Components[i]->Name == it_ComponentName->first) // find component by name
			  for (auto it_Language = it_ComponentName->second.begin(); it_Language != it_ComponentName->second.end(); it_Language++)
				if(it_Language->first == Language) // find translation for the target languag
					if (IsPublishedProp (Form->Components[i], "Caption"))
						SetPropValue (Form->Components[i], "Caption", it_Language->second);
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
		translation["GroupBox1"] = {
		{
			{"EN", "Enter your data:"},
			{"HR", "Upišite vaše podatke:"}
		}
	};

	translation["Label1"] = {
		{
			{"EN", "Name"},
			{"HR", "Ime"}
		}
	};

	translation["Label2"] = {
		{
			{"EN", "Surname"},
			{"HR", "Prezime"}
		}
	};

	translation["Label3"] = {
		{
			{"HR", "Sifra"},
			{"EN", "Password"}
		}
	};

	translation["Label4"] = {
		{
			{"HR", "Vaše posuðenje knjige i datum vraæanja"},
			{"EN", "Your books and date of return"}
		}
	};

	translation["BgeneriranjeKljuceva"] = {
		{
			{"EN", "Key generation"},
			{"HR", "Generiranje kljuceva"}
		}
	};

	translation["BposaljiKljuceve"] = {
		{
			{"EN", "Send keys"},
			{"HR", "Posalji kljuceve"}
		}
	};

	translation["GroupBox2"] = {
		{
			{"HR", "Pretražite knjige po autoru"},
			{"EN", "Search books by author"}
		}
	};

	translation["Button1"] = {
		{
			{"HR", "Posalji"},
			{"EN", "Send"}
		}
	};

	translation["Button2"] = {
		{
			{"HR", "Pretrazi"},
			{"EN", "Search"}
		}
	};


}
//---------------------------------------------------------------------------


// ...

void __fastcall TForm1::Button1Click(TObject *Sender)
{

	TMemoryStream* javniKljucStream = new TMemoryStream();
	javniKljucStream->LoadFromFile("javniKljucServer.bin");

	try {
		Signatory1->LoadKeysFromStream(javniKljucStream, TKeyStoragePartSet() << partPublic);
	} catch (Exception &e) {
		ShowMessage("Greška pri uèitavanju javnog kljuèa: " + e.Message);
	}

	// Šifrirajte poruku
	String porukaZaSifriranje = Eime->Text + "," + Eprezime->Text + "," + Esifra->Text;
	String sifriranaPoruka;

	try {
		ACodec->EncryptString(porukaZaSifriranje, sifriranaPoruka,  TEncoding::UTF8);
	} catch (Exception &e) {
		ShowMessage("Greška pri šifrovanju poruke: " + e.Message);
	}

	ShowMessage(sifriranaPoruka);

	// Sada šaljemo šifriranu poruku preko TCP veze
	TCP_klijent->Connect();
	if (TCP_klijent->Connected()) {
		TCP_klijent->Socket->WriteLn("PODACI");
		TCP_klijent->Socket->WriteLn(sifriranaPoruka);

		// Ostatak koda za èitanje i obradu odgovora
	} else {
		ShowMessage("Nije moguæe uspostaviti vezu s poslužiteljem.");
		TCP_klijent->Disconnect();
	}

	delete javniKljucStream;

	String kriptiraniPopis = TCP_klijent->Socket->ReadLn();
	ShowMessage(kriptiraniPopis);

	String popis;
	TMemoryStream* privatniKljuc = new TMemoryStream();

	privatniKljuc->LoadFromFile("privatniKljuc.bin");
	Signatory1->LoadKeysFromStream(privatniKljuc,TKeyStoragePartSet() << partPrivate);
	ACodec->DecryptString(popis, kriptiraniPopis, TEncoding::UTF8);


	String delimeter = ", ";

	Memo1->Lines->Clear();
	if(ComboBox1->Text == "HR"){
		Memo1->Lines->Add("Vaše knjige: ");
	}else{
		Memo1->Lines->Add("Your books: ");
	}

	int start = 1; // Poèinjemo od poèetka stringa
	while (start <= popis.Length()) {
		int end = popis.SubString(start, popis.Length() - start + 1).Pos(delimeter); // Pronalazimo zarez u preostalom delu stringa

		String naslov;

		if (end > 0) {
			naslov = popis.SubString(start, end - 1); // Izdvajamo deo stringa izmeðu zareza
		} else {
			naslov = popis.SubString(start, popis.Length() - start + 1); // Ako nema više zareza, uzimamo ostatak stringa
		}

		naslov = naslov.Trim(); // Uklanjamo razmake ako postoje

		Memo1->Lines->Add(naslov); // Dodajemo naslov u Memo1

		if (end > 0) {
			start += end + delimeter.Length() - 1; // Postavljamo novu poèetnu poziciju nakon zareza
		} else {
			break; // Izlazimo iz petlje ako nema više zareza
		}
	}

    TCP_klijent->Disconnect();
	delete privatniKljuc;
}



//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	UDP_klijent->ReceiveTimeout = 5000;
	Codec1->Password = "Kljuc_koji_je_jako_dugacak";
 
	String SifriranaPoruka;
	Codec1->EncryptString(Eautor->Text, SifriranaPoruka, TEncoding::UTF8);


	UDP_klijent->SendBuffer("127.0.0.1", 5555, ToBytes(SifriranaPoruka));

	String kriptiraneKnjige = UDP_klijent->ReceiveString();

	String knjige;
	Codec1->DecryptString(knjige, kriptiraneKnjige, TEncoding::UTF8);
	//ShowMessage(knjige); // tajna poruka

	String delimeter = ", ";

	Memo2->Lines->Clear();


	int start = 1; // Poèinjemo od poèetka stringa
	while (start <= knjige.Length()) {
		int end = knjige.SubString(start, knjige.Length() - start + 1).Pos(delimeter); // Pronalazimo zarez u preostalom delu stringa

		String naslov;

		if (end > 0) {
			naslov = knjige.SubString(start, end - 1); // Izdvajamo deo stringa izmeðu zareza
		} else {
			naslov = knjige.SubString(start, knjige.Length() - start + 1); // Ako nema više zareza, uzimamo ostatak stringa
		}

		naslov = naslov.Trim(); // Uklanjamo razmake ako postoje

		Memo2->Lines->Add(naslov); // Dodajemo naslov u Memo1

		if (end > 0) {
			start += end + delimeter.Length() - 1; // Postavljamo novu poèetnu poziciju nakon zareza
		} else {
			break; // Izlazimo iz petlje ako nema više zareza
		}
	}

	ShowMessage("Saljem serveru: " + SifriranaPoruka);

	ShowMessage("Primam od servera: " + kriptiraneKnjige);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BgeneriranjeKljucevaClick(TObject *Sender)
{
	 if (!FileExists("privatniKljuc.bin") || !FileExists("javniKljucKlijent.bin")) {

	  TMemoryStream* privatniKljuc = new TMemoryStream();
	  TMemoryStream* javniKljuc = new TMemoryStream();

	try {
		if(Signatory1->GenerateKeys()){

			Signatory1->StoreKeysToStream(privatniKljuc,TKeyStoragePartSet() << partPrivate);
			Signatory1->StoreKeysToStream(javniKljuc,TKeyStoragePartSet() << partPublic);

			privatniKljuc->SaveToFile("privatniKljuc.bin");
			javniKljuc->SaveToFile("javniKljucKlijent.bin");

		}
		ShowMessage("Kljuèevi su uspešno generisani i saèuvani.");
	} catch (Exception &e) {
		ShowMessage("Greška pri generisanju kljuèeva: " + e.Message);
	}

	delete privatniKljuc;
	delete javniKljuc;

	} else {
		ShowMessage("Kljuèevi veæ postoje.");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BposaljiKljuceveClick(TObject *Sender)
{

	TFileStream* datoteka = new TFileStream("javniKljucKlijent.bin", fmOpenRead);

	TCP_klijent->Connect();
	if (TCP_klijent->Connected()){
		TCP_klijent->Socket->WriteLn("KLJUCEVI");
		TCP_klijent->Socket->WriteLn(ExtractFileName(datoteka->FileName)); // naziv
		TCP_klijent->Socket->Write(datoteka->Size); // velièina
		TCP_klijent->Socket->Write(datoteka); // tok (sadržaj)
	}
	delete datoteka;
	String nazivServera = TCP_klijent->Socket->ReadLn(); // Naziv serverovog javnog kljuèa
	int velicinaServera = TCP_klijent->Socket->ReadInt64(); // Velièina serverovog javnog kljuèa

	// Sada možete èitati sadržaj serverovog javnog kljuèa kao tok
	TFileStream* javniKljucServer = new TFileStream(nazivServera, fmCreate);
	TCP_klijent->Socket->ReadStream(javniKljucServer, velicinaServera);

	// Ovdje možete koristiti serverov javni kljuè za daljnju komunikaciju
	// ...
	TCP_klijent->Disconnect();
	delete javniKljucServer;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	translateForm(this, ComboBox1->Text, translation);
}
//---------------------------------------------------------------------------

