//---------------------------------------------------------------------------

#ifndef LoginH
#define LoginH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include "uTPLb_BaseNonVisualComponent.hpp"
#include "uTPLb_Hash.hpp"
#include "uTPLb_CryptographicLibrary.hpp"
#include <map>

//---------------------------------------------------------------------------
class TLoginForm : public TForm
{
__published:	// IDE-managed Components
	TButton *BLogin;
	TEdit *Eime;
	TEdit *Eprezime;
	TLabel *Lime;
	TLabel *Lprezime;
	TEdit *Esifra;
	TLabel *Lsifra;
	TXMLDocument *XMLDocument1;
	THash *HashLog;
	TCryptographicLibrary *CryptographicLibrary1;
	TComboBox *ComboBox1;
	void __fastcall BLoginClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ComboBox1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TLoginForm(TComponent* Owner);
	 bool LoggedIn;
	 std::map<String, std::map<String, String>> translation;
};
//---------------------------------------------------------------------------/
//-----------------------------------------------------------------------------
extern PACKAGE TLoginForm *LoginForm;
extern int globalID;
extern String jezik;
//---------------------------------------------------------------------------
#endif
