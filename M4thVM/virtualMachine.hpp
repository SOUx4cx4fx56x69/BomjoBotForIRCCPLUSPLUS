#include "../util.hpp"
#ifndef VIRTUAL_MATH_MACHINE
#define VIRTUAL_MATH_MACHINE
#define DEFAULVARSALLOCATE 10
union value
{
long double signedvalue;
unsigned long unsignedvalue;
};

typedef struct Machine_Vars
{
char * name;
union value val;
Machine_Vars * before_var;
}Machine_Vars;

typedef enum
{
undefined,number,letter,math_letter
}type;

class VirtualMachine
{
private:
volatile float sum=0;
Machine_Vars * vars;
char * last_error;
const char * numbers = "1234567890";
const char * varsnameletters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char * math_letters = "+-*/%^";
const char end_string = '\n';
const char end_some_math_operation = ';'; // shit name, i know
const char set_char = '=';
type type_letters(char ch);
public:
VirtualMachine(void);
VirtualMachine(const char * string);
unsigned const char * ParseString(const char * string);
float GetResult(void);
protected:
unsigned const char * AnalyseString(const char * string);
}
;
#endif
