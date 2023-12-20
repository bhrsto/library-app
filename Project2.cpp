//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <Login.h>
#include "Main.h"
#include <memory>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Postavke.cpp", FPostavke);
USEFORM("Registracija.cpp", FRegistracija);
USEFORM("RegistracijaKorisnika.cpp", RegistracijaK);
USEFORM("dodavanjeNadzor.cpp", FdodavanjeNadzor);
USEFORM("dataModule.cpp", DataModule1); /* TDataModule: File Type */
USEFORM("Main.cpp", MainForm);
USEFORM("Login.cpp", LoginForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TLoginForm* LoginForm = new TLoginForm(NULL);

		if(LoginForm->ShowModal()== mrOk){
			Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TFPostavke), &FPostavke);
		Application->CreateForm(__classid(TDataModule1), &DataModule1);
		Application->CreateForm(__classid(TRegistracijaK), &RegistracijaK);
		Application->CreateForm(__classid(TFdodavanjeNadzor), &FdodavanjeNadzor);
		MainForm->LimePrezime->Caption = LoginForm->Eime->Text;
			Application-> Run();
		}




	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}

	delete LoginForm;
	return 0;
}
//---------------------------------------------------------------------------
