#include "virtualMachine.hpp"
/*
<Hypnosis> Coco/r учёные делали
<Francezgy> Ну блятьыа
<Hypnosis> это передний край науки
<Hypnosis> а все остальные делали наколенщики

NameVar=Number
+ - * /
*/
type VirtualMachine::type_letters(const char ch)
{
if(FindWhere(VirtualMachine::numbers,(const char*)ch)) return (type)number;
if(FindWhere(VirtualMachine::varsnameletters,(const char*)ch)) return (type)letter;
if(FindWhere(VirtualMachine::math_letters,(const char*)ch)) return (type)math_letter;
return (type)undefined;
}

const char * VirtualMachine::AnalyseString(const char * string)
{
 while(*string && *string !=end_string)
 {
   switch(VirtualMachine::type_letters(*string))
   {
     case number:
     break;
     case letter:
     break;
     case math_letter:
     break;
     default:
     return 0;
     break;
   }
   *string++;
 }
}
