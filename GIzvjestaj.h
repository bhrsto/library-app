//---------------------------------------------------------------------------

#ifndef GIzvjestajH
#define GIzvjestajH
//---------------------------------------------------------------------------
#endif

#include <vcl.h> // za osnovne VCL tipove i klase
#include <System.Classes.hpp> // za TFileStream


class Izvjestaj {
	private:
		String naslov;
		//String sadrzaj;
		TMemo *MemoIspis;

	public:
	   /*	wchar_t ime[20], prezime[20], nazivKnjige[40];
		int id;
		String ulaz;
		int zeljenaDuljina; */

		Izvjestaj(String naslov);
		Izvjestaj(TMemo *MemoIspis);


		void GenerirajIzvjestaj();
		void PrikaziIzvjestaj();
};