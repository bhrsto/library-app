//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.ComCtrls.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include "uTPLb_BaseNonVisualComponent.hpp"
#include "uTPLb_Codec.hpp"
#include "uTPLb_CryptographicLibrary.hpp"
#include <System.SysUtils.hpp>
#include "uTPLb_Signatory.hpp"

#include <map>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TIdTCPClient *TCP_klijent;
	TMemo *Memo1;
	TIdUDPClient *UDP_klijent;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Eime;
	TEdit *Eprezime;
	TEdit *Esifra;
	TButton *Button1;
	TLabel *Label4;
	TGroupBox *GroupBox2;
	TButton *Button2;
	TEdit *Eautor;
	TMemo *Memo2;
	TCodec *Codec1;
	TCryptographicLibrary *CryptographicLibrary1;
	TCodec *ACodec;
	TSignatory *Signatory1;
	TButton *BgeneriranjeKljuceva;
	TButton *BposaljiKljuceve;
	TComboBox *ComboBox1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall BgeneriranjeKljucevaClick(TObject *Sender);
	void __fastcall BposaljiKljuceveClick(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    std::map<String, std::map<String, String>> translation;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
