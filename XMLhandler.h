//---------------------------------------------------------------------------

#ifndef XMLhandlerH
#define XMLhandlerH
//---------------------------------------------------------------------------
#endif

#include "nadzor.h"


class xml{
	private:
	   String imeN, prezimeN, vrijemeN;
	   TXMLDocument *xmlDoc;
	   int indeks;
	public:
	 xml(TXMLDocument *xmlDoc, String ime, String prezime, String vrijeme);
	 xml(TXMLDocument *xmlDoc, int indeks);

	void  zapisiNadzor();
	void  dodajNadzor();
	void  urediNadzor(int OdabraniIndeks);
	void  izbrisiNadzor();



		/*static void DodajNadzor(TXMLDocument *xmlDoc, String imeN, String prezimeN, String vrijemeN);
		static void UrediNadzor(TXMLDocument *xmlDoc, int indeks, String imeN, String prezimeN, String vrijemeN);  */
};