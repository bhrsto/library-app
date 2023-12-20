
//---------------------------------------------------------------------------
#include "WebModuleUnit1.h"
#include <DateUtils.hpp>
#include <System.JSON.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TComponentClass WebModuleClass = __classid(TWebModule1);
//---------------------------------------------------------------------------
__fastcall TWebModule1::TWebModule1(TComponent* Owner)
	: TWebModule(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebModule1DefaultHandlerAction(TObject *Sender, TWebRequest *Request,
		  TWebResponse *Response, bool &Handled)
{
  Response->Content =
	"<html>"
	"<head><title>Web Server Application</title></head>"
	"<body>Web Server Application</body>"
	"</html>";
}
//---------------------------------------------------------------------------


void __fastcall TWebModule1::WebModule1zakasnjelePosudbeAction(TObject *Sender, TWebRequest *Request,
		  TWebResponse *Response, bool &Handled)
{
	  String jsonResponse = "{";

	  String trenutniKorisnik = "";
	  TDateTime vrijeme = Now();

	  String sqlKorisniciQuery = "SELECT * FROM korisnici";
	  ADOQueryKORISNICI->SQL->Text = sqlKorisniciQuery;
	  ADOQueryKORISNICI->Open();

	  jsonResponse += "\"korisnici\": [";

	  while (!ADOQueryKORISNICI->Eof)
	  {
		String ime = ADOQueryKORISNICI->FieldByName("ime")->AsString;
		String prezime = ADOQueryKORISNICI->FieldByName("prezime")->AsString;
		int korisnikID = ADOQueryKORISNICI->FieldByName("ID")->AsInteger;

		jsonResponse += "{";
		jsonResponse += "\"ime\": \"" + ime + "\",";
		jsonResponse += "\"prezime\": \"" + prezime + "\",";
		jsonResponse += "\"knjige\": [";

		String sqlKnjigeQuery = "SELECT * FROM knjige WHERE idKorisnik = :korisnikID";
		ADOQueryKNJIGE->SQL->Text = sqlKnjigeQuery;
		ADOQueryKNJIGE->Parameters->ParamByName("korisnikID")->Value = korisnikID;
		ADOQueryKNJIGE->Open();

		bool firstBook = true;

		while (!ADOQueryKNJIGE->Eof)
		{
			String nazivKnjige = ADOQueryKNJIGE->FieldByName("naziv")->AsString;
			TDateTime datumVracanja = ADOQueryKNJIGE->FieldByName("datumVracanja")->AsDateTime;

			  if (vrijeme > datumVracanja)
			  {
				double iznosDuga = DaysBetween(datumVracanja, vrijeme) * 0.5;

				if (!firstBook)
				  jsonResponse += ",";

                 String iznosDugaStr = FloatToStr(iznosDuga);
				 iznosDugaStr = StringReplace(iznosDugaStr, ",", ".", TReplaceFlags() << rfReplaceAll);

				jsonResponse += "{";
				jsonResponse += "\"naziv\": \"" + nazivKnjige + "\",";
				jsonResponse += "\"datumVracanja\": \"" + FormatDateTime("dd.mm.yyyy", datumVracanja) + "\",";
				jsonResponse += "\"dugovanje\": " + iznosDugaStr;
				jsonResponse += "}";

				firstBook = false;
			  }

			  ADOQueryKNJIGE->Next();
		}

		jsonResponse += "]";
		jsonResponse += "}";

		ADOQueryKORISNICI->Next();

		if (!ADOQueryKORISNICI->Eof)
		  jsonResponse += ",";

	  }

	  jsonResponse += "]";
	  jsonResponse += "}";

	  // Postavite ContentType na "application/json" za JSON format
	  Response->ContentType = "application/json; charset=UTF-8";

	  // Postavite odgovor na generirani JSON
	  Response->Content = jsonResponse;

}

//---------------------------------------------------------------------------
void __fastcall TWebModule1::WebModule1dodavanjeRadnikaAction(TObject *Sender, TWebRequest *Request,
		  TWebResponse *Response, bool &Handled)
{
	// Provjerite metodu zahtjeva - samo POST metoda je dopuštena
	if (Request->Method != "POST")
	{
		Response->StatusCode = 405; // Metoda nije dopuštena
		Response->ReasonString = "Method Not Allowed";
		Response->Content = "Samo POST metoda je dopuštena za ovu rutu.";
		return;
	}

	// Oèekujemo JSON podatke u tijelu zahtjeva
	String JSONData = Request->Content;

	// Parsiranje JSON podataka
	TJSONObject *JSONObject = NULL;
	try
	{
		JSONObject = static_cast<TJSONObject*>(TJSONObject::ParseJSONValue(JSONData));
		if (!JSONObject)
		{
			Response->StatusCode = 400; // Pogrešan zahtjev
			Response->ReasonString = "Bad Request";
			Response->Content = "Neispravan JSON format.";
			return;
		}

		// Izvadite potrebne vrijednosti iz JSON objekta
		String Ime = JSONObject->GetValue("Ime")->Value();
		String Prezime = JSONObject->GetValue("Prezime")->Value();
		String Sifra = JSONObject->GetValue("Sifra")->Value();
		String Admin = JSONObject->GetValue("Admin")->Value();

        String IDzaposlenikS = JSONObject->GetValue("IDzaposlenik")->Value();
		int IDzaposlenik = StrToInt(IDzaposlenikS);

		// Ovdje provjerite ovlasti i izvršite dodavanje radnika u bazu podataka
		// ...

		if(!jeAdmin(IDzaposlenik)){
			Response->StatusCode = 403; // Korisnik nema prava pristupa
			Response->ReasonString = "Zabranjen Pristup";
			Response->Content = "Nemate ovlasti za dodavanje radnika.";
			return;
		}

		delete JSONObject;

		if (Ime.IsEmpty() || Prezime.IsEmpty() || Sifra.IsEmpty()) {
			Response->Content = "Ne valja";
		}else{
			ADOQueryLOG->SQL->Text = "INSERT INTO login (ime, prezime, sifra, admin) VALUES (:ime, :prezime, :sifra, :admin)";
			ADOQueryLOG->Parameters->ParamByName("ime")->Value = Ime; // Ime je varijabla iz vašeg zahtjeva
			ADOQueryLOG->Parameters->ParamByName("prezime")->Value = Prezime; // Prezime je varijabla iz vašeg zahtjeva
			ADOQueryLOG->Parameters->ParamByName("sifra")->Value = Sifra; // Sifra je varijabla iz vašeg zahtjeva
			ADOQueryLOG->Parameters->ParamByName("admin")->Value = Admin;
			ADOQueryLOG->ExecSQL();
			}


		Response->Content = "Radnik je uspjesno dodan!";
		Response->ContentType = "text/plain";
		ADOQueryLOG->Close();
		}


	catch (const Exception &ex)
	{
		Response->StatusCode = 500; // Interna pogreška servera
		Response->ReasonString = "Internal Server Error";
		Response->Content = "Pogreška pri obradi zahtjeva: " + ex.Message;
		if (JSONObject)
			delete JSONObject;
	}
}

//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebModule1urediRadnikaAction(TObject *Sender, TWebRequest *Request,
		  TWebResponse *Response, bool &Handled)
{
   if (Request->Method != "PUT")
	{
		Response->StatusCode = 405; // Metoda nije dopuštena
		Response->ReasonString = "Method Not Allowed";
		Response->Content = "Samo PUT metoda je dopuštena za ovu rutu.";
		return;
	}

	// Oèekujemo JSON podatke u tijelu zahtjeva
	String JSONData = Request->Content;

	// Parsiranje JSON podataka
	TJSONObject *JSONObject = NULL;
	try
	{
		JSONObject = static_cast<TJSONObject*>(TJSONObject::ParseJSONValue(JSONData));
		if (!JSONObject)
		{
			Response->StatusCode = 400; // Pogrešan zahtjev
			Response->ReasonString = "Bad Request";
			Response->Content = "Neispravan JSON format.";
			return;
		}

		// Izvadite potrebne vrijednosti iz JSON objekta
		String Ime = JSONObject->GetValue("Ime")->Value();
		String Prezime = JSONObject->GetValue("Prezime")->Value();
		String ID = JSONObject->GetValue("ID")->Value();
		String Sifra = JSONObject->GetValue("Sifra")->Value();
		String Admin = JSONObject->GetValue("Admin")->Value();

		String IDzaposlenikS = JSONObject->GetValue("IDzaposlenik")->Value();
		int IDzaposlenik = StrToInt(IDzaposlenikS);

			if(!jeAdmin(IDzaposlenik)){
				Response->StatusCode = 403; // Korisnik nema prava pristupa
				Response->ReasonString = "Zabranjen Pristup";
				Response->Content = "Nemate ovlasti za ureðivanje radnika.";
				return;
		}

		delete JSONObject;

		if (Ime.IsEmpty() || Prezime.IsEmpty() || ID.IsEmpty()) {
			Response->Content = "Azuriranje radnika ne valja";
		}else{
			ADOQueryLOG->SQL->Text = "UPDATE login SET ime = :ime, prezime = :prezime, sifra = :sifra, admin = :admin WHERE ID = :ID";
			ADOQueryLOG->Parameters->ParamByName("ime")->Value = Ime;
			ADOQueryLOG->Parameters->ParamByName("prezime")->Value = Prezime;
			ADOQueryLOG->Parameters->ParamByName("ID")->Value = ID;
			ADOQueryLOG->Parameters->ParamByName("sifra")->Value = Sifra;
			ADOQueryLOG->Parameters->ParamByName("admin")->Value = Admin;
			ADOQueryLOG->ExecSQL();

			Response->Content = "Radnik je uspjesno azuriran!";
			Response->ContentType = "text/plain";
			ADOQueryLOG->Close();
		}
	}

	catch (const Exception &ex)
	{
		Response->StatusCode = 500; // Interna pogreška servera
		Response->ReasonString = "Internal Server Error";
		Response->Content = "Pogreška pri obradi zahtjeva: " + ex.Message;
		if (JSONObject)
			delete JSONObject;
	}

}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebModule1izbrisiRadnikaAction(TObject *Sender, TWebRequest *Request,
		  TWebResponse *Response, bool &Handled)
{

	String Ime = Request->QueryFields->Values["Ime"];
	String Prezime = Request->QueryFields->Values["Prezime"];
	String ID = Request->QueryFields->Values["ID"];
	String IDzaposlenikS = Request->QueryFields->Values["IDzaposlenik"];
	int IDzaposlenik = StrToInt(IDzaposlenikS);

	if(!jeAdmin(IDzaposlenik)){
		Response->StatusCode = 403; // Korisnik nema prava pristupa
		Response->ReasonString = "Zabranjen Pristup";
		Response->Content = "Nemate ovlasti za ureðivanje radnika.";
		Response->SendResponse();

		return;
	}

	if (Ime.IsEmpty() || Prezime.IsEmpty() || ID.IsEmpty()) {
		Response->Content = "Brisanje radnika neuspjesno";
	}else{
		ADOQueryLOG->SQL->Text = "DELETE FROM login WHERE ime = :ime AND prezime = :prezime AND ID = :ID";
		ADOQueryLOG->Parameters->ParamByName("ime")->Value = Ime;
		ADOQueryLOG->Parameters->ParamByName("prezime")->Value = Prezime;
		ADOQueryLOG->Parameters->ParamByName("ID")->Value = ID;
		ADOQueryLOG->ExecSQL();

		Response->Content = "Radnik je uspjesno izbrisan!";
		Response->ContentType = "text/plain";
		ADOQueryLOG->Close();
	}
}
//---------------------------------------------------------------------------
  bool TWebModule1::jeAdmin(const int IDzaposlenik)
{
	bool pom = false;
	ADOQueryLOG->SQL->Text = "SELECT * FROM login WHERE ID = :ID";
	ADOQueryLOG->Parameters->ParamByName("ID")->Value = IDzaposlenik;
	ADOQueryLOG->Open();

	if (ADOQueryLOG->RecordCount > 0)
	{
		int admin = ADOQueryLOG->FieldByName("admin")->AsInteger;
		pom = (admin == 1); // Provjerite je li admin postavljen na 1 (true)
	}

	ADOQueryLOG->Close(); // Obavezno zatvorite upit

	return pom;
}



