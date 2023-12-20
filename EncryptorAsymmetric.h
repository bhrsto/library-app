//---------------------------------------------------------------------------
#include <System.hpp>
#ifndef EncryptorAsymmetricH
#define EncryptorAsymmetricH
//---------------------------------------------------------------------------

#include "Main.h"
#endif
   class EncryptorAsymmetric {
	private:
		TCodec* codec;
		TSignatory* Signatory;
		TCryptographicLibrary* CryptographicLibrary1;
		TMemoryStream* javniKljucStream;
		TMemoryStream* privatniKljucStream;

	public:
		EncryptorAsymmetric(TCodec* codec, TCryptographicLibrary* CryptographicLibrary1, TSignatory* Signatory1);

		~EncryptorAsymmetric();

		String EncryptAsymmetric(String& tekst);
		String DecryptAsymmetric(String& kriptiraniTekst);


		bool LoadPublicKey(const String& publicKeyFileName);
		bool LoadPrivateKey(const String& privateKeyFileName);
};

