
// *************************************************************************************** //
//                                                                                       
//                                   XML Data Binding                                    
//                                                                                       
//         Generated on: 18.8.2023. 15:58:10                                             
//       Generated from: C:\Users\Hrsto\OneDrive\Radna površina\Projekt ntp\nadzor.xml   
//   Settings stored in: C:\Users\Hrsto\OneDrive\Radna površina\Projekt ntp\nadzor.xdb   
//                                                                                       
// *************************************************************************************** //

#include <System.hpp>
#pragma hdrstop

#include "nadzor.h"


// Global Functions 

_di_IXMLnadzorType __fastcall Getnadzor(Xml::Xmlintf::_di_IXMLDocument Doc)
{
  return (_di_IXMLnadzorType) Doc->GetDocBinding("nadzor", __classid(TXMLnadzorType), TargetNamespace);
};

_di_IXMLnadzorType __fastcall Getnadzor(Xml::Xmldoc::TXMLDocument *Doc)
{
  Xml::Xmlintf::_di_IXMLDocument DocIntf;
  Doc->GetInterface(DocIntf);
  return Getnadzor(DocIntf);
};

_di_IXMLnadzorType __fastcall Loadnadzor(const System::UnicodeString& FileName)
{
  return (_di_IXMLnadzorType) Xml::Xmldoc::LoadXMLDocument(FileName)->GetDocBinding("nadzor", __classid(TXMLnadzorType), TargetNamespace);
};

_di_IXMLnadzorType __fastcall  Newnadzor()
{
  return (_di_IXMLnadzorType) Xml::Xmldoc::NewXMLDocument()->GetDocBinding("nadzor", __classid(TXMLnadzorType), TargetNamespace);
};

// TXMLnadzorType 

void __fastcall TXMLnadzorType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("korsinik"), __classid(TXMLkorsinikType));
  ItemTag = "korsinik";
  ItemInterface = __uuidof(IXMLkorsinikType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

_di_IXMLkorsinikType __fastcall TXMLnadzorType::Get_korsinik(int Index)
{
  return (_di_IXMLkorsinikType) List->Nodes[Index];
};

_di_IXMLkorsinikType __fastcall TXMLnadzorType::Add()
{
  return (_di_IXMLkorsinikType) AddItem(-1);
};

_di_IXMLkorsinikType __fastcall TXMLnadzorType::Insert(const int Index)
{
  return (_di_IXMLkorsinikType) AddItem(Index);
};

// TXMLkorsinikType 

System::UnicodeString __fastcall TXMLkorsinikType::Get_ime()
{
  return GetChildNodes()->Nodes[System::UnicodeString("ime")]->Text;
};

void __fastcall TXMLkorsinikType::Set_ime(System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("ime")]->NodeValue = Value;
};

System::UnicodeString __fastcall TXMLkorsinikType::Get_prezime()
{
  return GetChildNodes()->Nodes[System::UnicodeString("prezime")]->Text;
};

void __fastcall TXMLkorsinikType::Set_prezime(System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("prezime")]->NodeValue = Value;
};

System::UnicodeString __fastcall TXMLkorsinikType::Get_vrijeme()
{
  return GetChildNodes()->Nodes[System::UnicodeString("vrijeme")]->Text;
};

void __fastcall TXMLkorsinikType::Set_vrijeme(System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("vrijeme")]->NodeValue = Value;
};
