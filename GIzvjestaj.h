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
		TMemo *MemoIspis;

	public:
		Izvjestaj(String naslov);
		Izvjestaj(TMemo *MemoIspis);


		void GenerirajIzvjestaj();
		void PrikaziIzvjestaj();
};
