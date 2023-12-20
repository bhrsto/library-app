
// *************************************************************************************** //
//                                                                                       
//                                   XML Data Binding                                    
//                                                                                       
//         Generated on: 18.8.2023. 15:58:10                                             
//       Generated from: C:\Users\Hrsto\OneDrive\Radna površina\Projekt ntp\nadzor.xml   
//   Settings stored in: C:\Users\Hrsto\OneDrive\Radna površina\Projekt ntp\nadzor.xdb   
//                                                                                       
// *************************************************************************************** //

#ifndef   nadzorH
#define   nadzorH

#include <System.hpp>
#include <Xml.Xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <XMLNodeImp.h>
#include <Xml.xmlutil.hpp>


// Forward Decls 

__interface IXMLnadzorType;
typedef System::DelphiInterface<IXMLnadzorType> _di_IXMLnadzorType;
__interface IXMLkorsinikType;
typedef System::DelphiInterface<IXMLkorsinikType> _di_IXMLkorsinikType;

// IXMLnadzorType 

__interface INTERFACE_UUID("{1168613F-755D-4C44-986F-CE8D9B51D46A}") IXMLnadzorType : public Xml::Xmlintf::IXMLNodeCollection
{
public:
public:
  // Property Accessors 
  virtual _di_IXMLkorsinikType __fastcall Get_korsinik(int Index) = 0;
  // Methods & Properties 
  virtual _di_IXMLkorsinikType __fastcall Add() = 0;
  virtual _di_IXMLkorsinikType __fastcall Insert(const int Index) = 0;
  __property _di_IXMLkorsinikType korsinik[int Index] = { read=Get_korsinik };/* default */
};

// IXMLkorsinikType 

__interface INTERFACE_UUID("{A49C7490-1437-49ED-8E21-1D96B3D898D1}") IXMLkorsinikType : public Xml::Xmlintf::IXMLNode
{
public:
  // Property Accessors 
  virtual System::UnicodeString __fastcall Get_ime() = 0;
  virtual System::UnicodeString __fastcall Get_prezime() = 0;
  virtual System::UnicodeString __fastcall Get_vrijeme() = 0;
  virtual void __fastcall Set_ime(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_prezime(System::UnicodeString Value) = 0;
  virtual void __fastcall Set_vrijeme(System::UnicodeString Value) = 0;
  // Methods & Properties 
  __property System::UnicodeString ime = { read=Get_ime, write=Set_ime };
  __property System::UnicodeString prezime = { read=Get_prezime, write=Set_prezime };
  __property System::UnicodeString vrijeme = { read=Get_vrijeme, write=Set_vrijeme };
};

// Forward Decls 

class TXMLnadzorType;
class TXMLkorsinikType;

// TXMLnadzorType 

class TXMLnadzorType : public Xml::Xmldoc::TXMLNodeCollection, public IXMLnadzorType
{
  __IXMLNODECOLLECTION_IMPL__
protected:
  // IXMLnadzorType 
  virtual _di_IXMLkorsinikType __fastcall Get_korsinik(int Index);
  virtual _di_IXMLkorsinikType __fastcall Add();
  virtual _di_IXMLkorsinikType __fastcall Insert(const int Index);
public:
  virtual void __fastcall AfterConstruction(void);
};

// TXMLkorsinikType 

class TXMLkorsinikType : public Xml::Xmldoc::TXMLNode, public IXMLkorsinikType
{
  __IXMLNODE_IMPL__
protected:
  // IXMLkorsinikType 
  virtual System::UnicodeString __fastcall Get_ime();
  virtual System::UnicodeString __fastcall Get_prezime();
  virtual System::UnicodeString __fastcall Get_vrijeme();
  virtual void __fastcall Set_ime(System::UnicodeString Value);
  virtual void __fastcall Set_prezime(System::UnicodeString Value);
  virtual void __fastcall Set_vrijeme(System::UnicodeString Value);
};

// Global Functions 

_di_IXMLnadzorType __fastcall Getnadzor(Xml::Xmlintf::_di_IXMLDocument Doc);
_di_IXMLnadzorType __fastcall Getnadzor(Xml::Xmldoc::TXMLDocument *Doc);
_di_IXMLnadzorType __fastcall Loadnadzor(const System::UnicodeString& FileName);
_di_IXMLnadzorType __fastcall  Newnadzor();

#define TargetNamespace ""

#endif