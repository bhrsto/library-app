//---------------------------------------------------------------------------

#pragma hdrstop

#include "EncryptorAsymmetric.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


EncryptorAsymmetric::EncryptorAsymmetric(TCodec* codec, TCryptographicLibrary *CryptographicLibrary1, TSignatory *Signatory1) {
	this->codec = codec;
	this->CryptographicLibrary1 = CryptographicLibrary1;
	this->javniKljucStream = nullptr;
	this->privatniKljucStream = nullptr;
	this->Signatory = Signatory1;
}


EncryptorAsymmetric::~EncryptorAsymmetric() {
	delete this->javniKljucStream;
	delete this->privatniKljucStream;
}

String EncryptorAsymmetric::EncryptAsymmetric(String& tekst) {

	try {
		Signatory->LoadKeysFromStream(javniKljucStream, TKeyStoragePartSet() << partPublic);
	} catch (Exception &e) {
		ShowMessage("Gre�ka pri u�itavanju javnog klju�a: " + e.Message);
	}

	String sifriranaPoruka;

	try {
		codec->EncryptString(tekst, sifriranaPoruka, TEncoding::UTF8);
	} catch (Exception &e) {
		ShowMessage("Gre�ka pri �ifrovanju poruke: " + e.Message);
	}

	return sifriranaPoruka;
}



String EncryptorAsymmetric::DecryptAsymmetric(String& kriptiraniTekst) {

	String dekriptiranaPoruka;


	if (privatniKljucStream != nullptr) {
		// U�itaj privatni klju� iz streama
		Signatory->LoadKeysFromStream(privatniKljucStream, TKeyStoragePartSet() << partPrivate);
		try {
			codec->DecryptString(dekriptiranaPoruka, kriptiraniTekst, TEncoding::UTF8);
			}
		catch (Exception &e) {
			dekriptiranaPoruka = "Gre�ka pri de�ifriranju poruke: " + e.Message;
			}
	}
	else {
		dekriptiranaPoruka = "Nema privatnog klju�a za de�ifriranje.";
	}


	return dekriptiranaPoruka;
}


bool EncryptorAsymmetric::LoadPublicKey(const String& javniKljucIme) {
	javniKljucStream = new TMemoryStream();
	try{
		javniKljucStream->LoadFromFile(javniKljucIme);
	}catch (Exception &e) {
		return false;
	}


	return true;
}

bool EncryptorAsymmetric::LoadPrivateKey(const String& privatniKljucIme) {
		privatniKljucStream = new TMemoryStream();
		try{
			privatniKljucStream->LoadFromFile(privatniKljucIme);
		}catch(Exception &e){
			return false;
		}


		return true;
}