//---------------------------------------------------------------------------
#include <System.hpp>
#ifndef EncryptorH
#define EncryptorH
//---------------------------------------------------------------------------
#endif

#include "Main.h"


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