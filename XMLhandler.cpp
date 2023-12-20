//---------------------------------------------------------------------------

#pragma hdrstop

#include "XMLhandler.h"
#include "nadzor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

xml::xml(TXMLDocument *xmlDoc, String ime, String prezime, String vrijeme) : xmlDoc(xmlDoc), imeN(ime), prezimeN(prezime), vrijemeN(vrijeme){}

xml::xml(TXMLDocument *xmlDoc, int indeks) : xmlDoc(xmlDoc), indeks(indeks){}


void  xml::dodajNadzor(){
	_di_IXMLnadzorType nadzor = Getnadzor(this->xmlDoc);
	_di_IXMLkorsinikType korsinik = nadzor->Add();

	korsinik->ime = this->imeN;
	korsinik->prezime = this->prezimeN;
	korsinik->vrijeme = this->vrijemeN;
	this->xmlDoc->SaveToFile(this->xmlDoc->FileName);
}

void xml::urediNadzor(int OdabraniIndeks){
	_di_IXMLnadzorType nadzor = Getnadzor(this->xmlDoc);
	nadzor->korsinik[OdabraniIndeks]->ime = this->imeN;
	nadzor->korsinik[OdabraniIndeks]->prezime = this->prezimeN;
	nadzor->korsinik[OdabraniIndeks]->vrijeme = this->vrijemeN;
	this->xmlDoc->SaveToFile(this->xmlDoc->FileName);
}

void xml::izbrisiNadzor(){
	_di_IXMLnadzorType nadzor = Getnadzor(this->xmlDoc);

	nadzor->Delete(indeks);
	this->xmlDoc->SaveToFile(this->xmlDoc->FileName);
}

void xml::zapisiNadzor(){
	_di_IXMLnadzorType nadzor = Getnadzor(this->xmlDoc);
	_di_IXMLkorsinikType korsinik = nadzor->Add();

	/*TDateTime sadasnjeVrijeme = Now();
	String formatirani = FormatDateTime("yyyy-mm-dd hh:nn", sadasnjeVrijeme);*/

	korsinik->ime = this->imeN;;
	korsinik->prezime = this->prezimeN;
	korsinik->vrijeme = this->vrijemeN;

	this->xmlDoc->SaveToFile(this->xmlDoc->FileName);
}


