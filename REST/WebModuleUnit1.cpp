
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


void __fastcall TWebModule1::WebModule1dodavanjeRadnikaAction(TObject *Sender, TWebRequest *Request,
		  TWebResponse *Response, bool &Handled)
{
	if (Request->Method != "POST")
	{
		Response->StatusCode = 405;
		Response->ReasonString = "Method Not Allowed";
		Response->Content = "Samo POST metoda je dopuštena za ovu rutu.";
		return;
	}

	String JSONData = Request->Content;

	TJSONObject *JSONObject = NULL;
	try
	{
		JSONObject = static_cast<TJSONObject*>(TJSONObject::ParseJSONValue(JSONData));
		if (!JSONObject)
		{
			Response->StatusCode = 400;
			Response->ReasonString = "Bad Request";
			Response->Content = "Neispravan JSON format.";
			return;
		}

		String Ime = JSONObject->GetValue("Ime")->Value();
		String Prezime = JSONObject->GetValue("Prezime")->Value();
		String Sifra = JSONObject->GetValue("Sifra")->Value();
		String Admin = JSONObject->GetValue("Admin")->Value();

        String IDzaposlenikS = JSONObject->GetValue("IDzaposlenik")->Value();
		int IDzaposlenik = StrToInt(IDzaposlenikS);


		if(!jeAdmin(IDzaposlenik)){
			Response->StatusCode = 403;
			Response->ReasonString = "Zabranjen Pristup";
			Response->Content = "Nemate ovlasti za dodavanje radnika.";
			return;
		}

		delete JSONObject;

		if (Ime.IsEmpty() || Prezime.IsEmpty() || Sifra.IsEmpty()) {
			Response->Content = "Ne valja";
		}else{
			ADOQueryLOG->SQL->Text = "INSERT INTO login (ime, prezime, sifra, admin) VALUES (:ime, :prezime, :sifra, :admin)";
			ADOQueryLOG->Parameters->ParamByName("ime")->Value = Ime;
			ADOQueryLOG->Parameters->ParamByName("prezime")->Value = Prezime;
			ADOQueryLOG->Parameters->ParamByName("sifra")->Value = Sifra;
			ADOQueryLOG->Parameters->ParamByName("admin")->Value = Admin;
			ADOQueryLOG->ExecSQL();
			}


		Response->Content = "Radnik je uspjesno dodan!";
		Response->ContentType = "text/plain";
		ADOQueryLOG->Close();
		}


	catch (const Exception &ex)
	{
		Response->StatusCode = 500;
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
		Response->StatusCode = 405;
		Response->ReasonString = "Method Not Allowed";
		Response->Content = "Samo PUT metoda je dopuštena za ovu rutu.";
		return;
	}

	String JSONData = Request->Content;

	TJSONObject *JSONObject = NULL;
	try
	{
		JSONObject = static_cast<TJSONObject*>(TJSONObject::ParseJSONValue(JSONData));
		if (!JSONObject)
		{
			Response->StatusCode = 400;
			Response->ReasonString = "Bad Request";
			Response->Content = "Neispravan JSON format.";
			return;
		}

		String Ime = JSONObject->GetValue("Ime")->Value();
		String Prezime = JSONObject->GetValue("Prezime")->Value();
		String ID = JSONObject->GetValue("ID")->Value();
		String Sifra = JSONObject->GetValue("Sifra")->Value();
		String Admin = JSONObject->GetValue("Admin")->Value();

		String IDzaposlenikS = JSONObject->GetValue("IDzaposlenik")->Value();
		int IDzaposlenik = StrToInt(IDzaposlenikS);

			if(!jeAdmin(IDzaposlenik)){
				Response->StatusCode = 403;
				Response->ReasonString = "Zabranjen Pristup";
				Response->Content = "Nemate ovlasti za uređivanje radnika.";
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
		Response->StatusCode = 500;
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
		Response->StatusCode = 403;
		Response->ReasonString = "Zabranjen Pristup";
		Response->Content = "Nemate ovlasti za uređivanje radnika.";
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
		pom = (admin == 1);
	}

	ADOQueryLOG->Close();

	return pom;
}



void __fastcall TWebModule1::WebModule1LogInAction(TObject *Sender, TWebRequest *Request,
		  TWebResponse *Response, bool &Handled)
{
	String JSONData = Request->Content;

    TJSONObject *JSONObject = TJSONObject::ParseJSONValue(JSONData) ? dynamic_cast<TJSONObject*>(TJSONObject::ParseJSONValue(JSONData)) : NULL;

    if (JSONObject != NULL) {
        String Ime = JSONObject->GetValue("Ime")->Value();
        String Prezime = JSONObject->GetValue("Prezime")->Value();
        String Sifra = JSONObject->GetValue("Sifra")->Value();

        delete JSONObject;

        ADOQueryLOG->SQL->Text = "SELECT * FROM login where ime = :ime AND prezime = :prezime AND sifra = :sifra";
        ADOQueryLOG->Parameters->ParamByName("ime")->Value = Ime;
        ADOQueryLOG->Parameters->ParamByName("prezime")->Value = Prezime;
        ADOQueryLOG->Parameters->ParamByName("sifra")->Value = Sifra;
        ADOQueryLOG->Open();

        if (ADOQueryLOG->Eof) {
            Response->Content = IntToStr(2);
            Response->ContentType = "text/plain";
        } else {
            int admin = ADOQueryLOG->FieldByName("admin")->AsInteger;
            Response->Content = IntToStr(admin);
            Response->ContentType = "text/plain";
        }
    } else {
        Response->Content = "Neuspjelo parsiranje JSON-a";
        Response->ContentType = "text/plain";
	}
}
//---------------------------------------------------------------------------

