#include <cheerp/client.h>
#include <cheerp/clientlib.h>
#include <cheerpfs.h>
// client is a regular C++ namespace, so we can reduce verbosity by using it
using namespace client;

extern "C" {
        void init();
        char * myFunction();
		int myIntFunc();
		char * getLine(int x);
		char * exchangeStr(const char* str);
    };
	
class Foo {
    int var1;
    int var2;
};

template<class T>
T* myalloc(size_t size)
{
    return (T*)malloc(size);
}

template<class T>
void myfree(T* t)
{
	free(t);
}

void preloadCallback()
{
    // Files are ready
    //int fd = open("data1.xml");
	//client::console.log("Hello, World Wide Web!");
	//client::console.log(fd);
}

//cheerp::FilePreloader files(preloadCallback, "data1.xml", "images/asset1.png");

[[cheerp::genericjs]]
void webMain()
{
	init();
	
	//int fd = open("data.txt");
	//Foo* foo = myalloc<Foo>(6480000*2);
	
	//char *tst = (char *)malloc(2147483648);
    Element* titleElement=document.getElementById("pagetitle");
	//char s[50];
	//sprintf(s, "fd = %d", fd);
	//titleElement->set_textContent(s);
    // Save the old text, it is a JavaScript String
    String* oldText=titleElement->get_textContent();
	char* c_str = myFunction();
	String* str = new String(c_str);
	titleElement->set_textContent(str);
	c_str = myFunction();
	str = new String(c_str);
    //titleElement->set_textContent(L"Exciting dynamic title, with non-Latin letters ΩЯÅ");
    // setTimeout is included in the client namespace like other browser APIs
    // cheerp::Callback is bridge function to invoke C++ lambdas and functions as
    // JavaScript callbaks. We use C++11 lambda in this case.
    setTimeout(cheerp::Callback([titleElement,str](client::Event* e)
        {
				titleElement->set_textContent(str);
        }), 3000);
	
	//myfree<Foo>(foo);
}

[[cheerp::jsexport]]
int MyIntFuncJS()
{
	return myIntFunc();
}

[[cheerp::jsexport]][[cheerp::genericjs]]
String* GetLineJS(int x)
{
	char* c_str = getLine(x);
	String* str = new String(c_str);
	return str;
}

[[cheerp::wasm]]
std::string* exchangeStrWASM(std::string s)
{
	printf("exchangeStrWASM called.\n");
	char* rc = exchangeStr(s.c_str());
	std::string* str = new std::string(rc);
	return str;
}

[[cheerp::jsexport]][[cheerp::genericjs]]
String* ExchangeStrJS(String* s)
{
	console.log("ExchangeStrJS called.\n");
	console.log(s);
	std::string ss = (std::string)*s;
	console.log("ExchangeStrJS string cast.\n");
	std::string* sstr = exchangeStrWASM(ss);
	console.log("ExchangeStrJS back from calling exchangeStrWASM.\n");
	String* ret = new String(sstr->c_str());
	console.log("ExchangeStrJS new String*.\n");
	
	return new String("response");
}


