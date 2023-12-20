//---------------------------------------------------------------------------

#ifndef dataModuleH
#define dataModuleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Datasnap.DBClient.hpp>
//---------------------------------------------------------------------------
class TDataModule1 : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *ADOConnection1;
	TADOQuery *ADOQueryLOG;
	TADOTable *ADOTable1;
	TDataSource *DataSourceLOG;
	TADOQuery *ADOQueryKORISNICI;
	TDataSource *DataSourceKORISNICI;
	TADOQuery *ADOQueryKNJIGE;
	TDataSource *DataSourceKNJIGE;
	TAutoIncField *ADOTable1ID;
	TWideStringField *ADOTable1naziv;
	TWideStringField *ADOTable1pisac;
	TDateTimeField *ADOTable1datumPosudivanja;
	TDateTimeField *ADOTable1datumVracanja;
	TIntegerField *ADOTable1idKorisnik;
	TIntegerField *ADOTable1idLogin;
	TAutoIncField *ADOQueryKORISNICIID;
	TWideStringField *ADOQueryKORISNICIime;
	TWideStringField *ADOQueryKORISNICIprezime;
	TIntegerField *ADOQueryKORISNICIidKnjige;
	TIntegerField *ADOQueryKORISNICIUkupnoPosudjenoKnjiga;
	TAutoIncField *ADOQueryKNJIGEID;
	TWideStringField *ADOQueryKNJIGEnaziv;
	TWideStringField *ADOQueryKNJIGEpisac;
	TWideStringField *ADOQueryKNJIGEdatumPosudivanja;
	TWideStringField *ADOQueryKNJIGEdatumVracanja;
	TIntegerField *ADOQueryKNJIGEidKorisnik;
	TIntegerField *ADOQueryKNJIGEidLogin;
	TBlobField *ADOQueryKNJIGEIzgledkorice;
	void __fastcall ADOQueryKORISNICICalcFields(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TDataModule1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDataModule1 *DataModule1;
//---------------------------------------------------------------------------
#endif
