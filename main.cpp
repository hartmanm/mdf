#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sstream>
//#include <curl/curl.h>
// init a

void help();

std::string question(std::string the_ask);

void make_stream_call(std::string the_stream);

int main(int argv, char *argc[]){

bool exit=false;
std::string i;
std::string r;
std::string user_cmd;
char cmd[100];
int cycle=4;
while(exit==false)
{
make_stream_call("ls -pla");
std::cout << "input your cmd:" << std::endl;
std::cin >> user_cmd;

make_stream_call(""+user_cmd+"");

  std::cout << "input: help or exit" << std::endl;
std::cin >> r;
cycle=4;
while(cycle>1){cycle--;std::cout << "cycle:" + std::to_string(cycle) << std::endl;}

  char str[6000];
  memset (str,'-',6000);
  puts (str);
std::cout << "memset complete" << std::endl;

//help();
if(r=="exit"){return 0;}
if(r=="help"){help();}
//r=r+"; sleep 4";
//std::cout << "r"+r << std::endl;
//cmd=r.c_str()
//i=system();
//std::cout << "The value returned was:" + i << std::endl;
//printf ("The value returned was: %c.\n",i);
question("hy");
question("why");

}

}

void help(){
std::cout << std::endl;
std::cout << "help:" << std::endl;
std::cout << "-a" << std::endl;
std::cout << "-r" << std::endl;
std::cout << "-c" << std::endl;
std::cout << "-b" << std::endl;
};

std::string question(std::string the_ask){

if(the_ask == "why"){
  std::cout << "beit" << std::endl;
  return "beit";}

else {
    std::cout << "idk" << std::endl;
    return "idk";}
}


void make_stream_call(std::string the_stream){
std::stringstream stream;

stream << the_stream;
system(stream.str().c_str());




}