//---------------------------------------------------------------------------

#ifndef translateFormH
#define translateFormH
//---------------------------------------------------------------------------
#endif
#include <map>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//#include "Login.h"


void translateForm(TForm* Form, String Language, const std::map<String, std::map<String, String>>& translation);
