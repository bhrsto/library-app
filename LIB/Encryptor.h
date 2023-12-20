#include <System.hpp>
#ifndef EncryptorH
#define EncryptorH
//---------------------------------------------------------------------------
#endif

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "uTPLb_BaseNonVisualComponent.hpp"
#include "uTPLb_Codec.hpp"
#include "uTPLb_CryptographicLibrary.hpp"
#include <System.SysUtils.hpp>
#include <Vcl.Dialogs.hpp>
#include "uTPLb_Signatory.hpp"


class Encryptor {
	private:
		TCodec* codec;
		TSignatory *Signatory;
		TCryptographicLibrary *CryptographicLibrary1;

	public:
		Encryptor( TCodec* codec, TCryptographicLibrary *CryptographicLibrary1);

		~Encryptor();

		// Metoda za simetrièno kriptiranje poruke
		String EncryptSymmetric(String& tekst);
		String DecryptSymmetric(String& kriptiraniTekst);

		String EncryptAsymmetric(String& tekst);
		String DecryptAsymmetric(String& kriptiraniTekst);
};

