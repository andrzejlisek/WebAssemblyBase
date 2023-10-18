#include <cstdio>
#include <emscripten.h>
#include <string>


char * ReturnString;
int ReturnStringSize = 256;


EMSCRIPTEN_KEEPALIVE
const char * StrTest1()
{
    return "Hello World";
}

EMSCRIPTEN_KEEPALIVE
char * StrTest2(char * Str)
{
    int I = 0;
    while ((Str[I] != 0) && (I < ReturnStringSize))
    {
        ReturnString[I] = Str[I];
        if ((Str[I] >= 'A') && (Str[I] <= 'Z')) { ReturnString[I] = (Str[I] + 32); }
        if ((Str[I] >= 'a') && (Str[I] <= 'z')) { ReturnString[I] = (Str[I] - 32); }
        I++;
    }
    ReturnString[I] = 0;
    return ReturnString;
}



EMSCRIPTEN_KEEPALIVE
void myFunction(int argc, char ** argv)
{
    printf("MyFunction Called\n");
}

EMSCRIPTEN_KEEPALIVE
int fib(int x)
{
  if (x < 1)
    return 0;
  if (x == 1)
    return 1;
  return fib(x-1)+fib(x-2);
}






EM_JS(int, Alert_, (const char * s), {
  console.log('Komunikaty: ' + s);
  return 1256;
});


void Alert(std::string s)
{
    s = "alert('" + s + "');";
    emscripten_run_script(s.c_str());
}

void Info(std::string s)
{
    s = "Info('" + s + "');";
    emscripten_run_script(s.c_str());
}

int CbTest11(int n)
{
    std::string s = "CallbackTestNum('" + std::to_string(n) + "');";
    return emscripten_run_script_int(s.c_str());
}

EM_JS(int, CbTest12, (int x), {
  return CallbackTestNum(x);
});

std::string CbTest21(std::string n)
{
    std::string s = "CallbackTestStr('" + n + "');";
    std::string str = "";
    str.append(emscripten_run_script_string(s.c_str()));
    return str;
}

EM_JS(const char *, CbTest22_, (const char * x), {
  let x_ = UTF8ToString(x);
  let x__ = CallbackTestStr(x_);
  return stringToUTF8OnStack(x__);
});

std::string CbTest22(std::string n)
{
    std::string str = "";
    str.append(CbTest22_(n.c_str()));
    return str;
}


EMSCRIPTEN_KEEPALIVE
int CallbackTest(int n)
{
    switch (n)
    {
        case 0:
            Info("Info from callback function");
            return 0;
        case 1:
            return CbTest11(64);
        case 2:
            return CbTest12(64);
        case 3:
            Info("Returned from callback: " + CbTest21("Hello"));
            return 777;
        case 4:
            Info("Returned from callback: " + CbTest22("Hello"));
            return 777;
        default:
            return 0;
    }
}




int main()
{
    ReturnString = (char*)malloc(ReturnStringSize);

    printf("Main function\n");
    int N = fib(6);
    printf("fib(6)=%d\n", N);
    return 0;
}

