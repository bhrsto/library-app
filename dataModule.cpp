//---------------------------------------------------------------------------


#pragma hdrstop

#include "dataModule.h"
#include "RegistracijaKorisnika.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TDataModule1 *DataModule1;
//---------------------------------------------------------------------------
__fastcall TDataModule1::TDataModule1(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TDataModule1::ADOQueryKORISNICICalcFields(TDataSet *DataSet)
{
	int korisnikID = DataSet->FieldByName("ID")->AsInteger;
    int ukupnoPosudjeno = 0;

    if (ADOQueryKNJIGE->Active)  // Provjerite je li upit otvoren
    {
        ADOQueryKNJIGE->First();
        while (!ADOQueryKNJIGE->Eof)
        {
            if (ADOQueryKNJIGE->FieldByName("idKorisnik")->AsInteger == korisnikID)
            {
                ukupnoPosudjeno++;
            }
            ADOQueryKNJIGE->Next();
        }
    }

	DataSet->FieldByName("UkupnoPosudjenoKnjiga")->AsInteger = ukupnoPosudjeno;
}

//---------------------------------------------------------------------------

