//---------------------------------------------------------------------------

#ifndef PostavkeH
#define PostavkeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <map>
//---------------------------------------------------------------------------
class TFPostavke : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TComboBox *CBFont;
	TLabel *Label2;
	TEdit *EVelicinaFonta;
	TButton *BSpremi;
	TColorDialog *ColorDialog1;
	TButton *BPromjeniBoju;
	void __fastcall BSpremiClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BPromjeniBojuClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFPostavke(TComponent* Owner);

	std::map<String, std::map<String, String>> translation;
};
//---------------------------------------------------------------------------
extern PACKAGE TFPostavke *FPostavke;
//---------------------------------------------------------------------------
#endif
