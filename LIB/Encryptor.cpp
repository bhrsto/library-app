 #pragma hdrstop

#include "Encryptor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Encryptor::Encryptor(TCodec* codec, TCryptographicLibrary *CryptographicLibrary1) {
	this->codec = codec;
	this->CryptographicLibrary1 = CryptographicLibrary1;
	/*this->javniKljucStream = nullptr;
	this->privatniKljucStream = nullptr;*/

	codec->Password = "Kljuc_koji_je_jako_dugacak";
}



Encryptor::~Encryptor() {
	delete codec;
	delete CryptographicLibrary1;
}


String Encryptor::EncryptSymmetric(String& tekst) {

   String kriptiranaPoruka;

	try {
		codec->EncryptString(tekst, kriptiranaPoruka, TEncoding::UTF8);
	} catch (Exception &e) {
		ShowMessage("Greška pri šifriranju: " + e.Message);
		kriptiranaPoruka = "";
	}

	return kriptiranaPoruka;
}

//---------------------------------------------------------------------


String Encryptor::DecryptSymmetric(String& kriptiraniTekst) {
	String dekriptiranaPoruka;

	try {
		// Provjerite jesu li postavke `codec` ispravno konfigurirane za dekripciju
		if (codec->CryptoLibrary == nullptr || codec->Password.IsEmpty() || codec->BlockCipherId.IsEmpty() || codec->ChainModeId.IsEmpty()) {
			ShowMessage("Nisu ispravno postavljene enkripcijske postavke.");
			return "";
		}

		// Dekriptirajte poruku
		codec->DecryptString(dekriptiranaPoruka, kriptiraniTekst, TEncoding::UTF8);
	} catch (Exception &e) {
		ShowMessage("Greška pri dešifriranju: " + e.Message);
		dekriptiranaPoruka = "";
	}

	return dekriptiranaPoruka;
}
