#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <string>
//#include <vector>
//#include <bits/stdc++.h> 
//#include <curl/curl.h>
// init a

void help();
std::string question(std::string the_ask);
int make_stream_call(std::stringstream stream);

int main(int argv, char *argc[]){



    int i, v = 0, size = argv - 1;

    char *str = (char *)malloc(v);

    for(i = 1; i <= size; i++) {
        str = (char *)realloc(str, (v + strlen(argc[i])));
        strcat(str, argc[i]);
        strcat(str, " ");
    }
//std::string empath="export PATH=\"$PATH:`pwd`\"";
// export PATH="$PATH:`pwd`"
//system(empath.c_str());
system(str);
//memset(user_cmd2,'-',6000);
return 0;

char user_cmd3[6000];
char user_cmd2[100];
//user_cmd2=argc[argv];
//int i=argv;
std::cout << std::to_string(i) << std::endl;

//while(i>1){strcat(user_cmd2, argc[i]);strncat(user_cmd3, user_cmd2,100);i--;};


while(i>1){
  strcat(user_cmd2, argc[i]);
  strncat(user_cmd3, argc[i],sizeof(argc[i]));i--;
  };

//memcpy ( &person_copy, &person, sizeof(person) );
//strcpy(user_cmd2, argc[1]);
//strcpy(user_cmd2, argc[2]);
std::cout << user_cmd3 << std::endl;
system(user_cmd3);
//memset(user_cmd2,'-',6000);
return 0;







bool exit=false;
//std::string i;
//std::string r;
std::string user_cmd;
//char cmd[100];
//int cycle=4;
while(exit==false)
{
  //std::vector <std::string> tokens; 
  //tokens.push_back("ls -pla");
//make_stream_call(tokens);
//i="";
//int done=0;
//std::stringstream user_cmd;
//std::string cmd;

std::cout << "input your cmd:" << std::endl;
char user_cmd[6000];
std::cin.getline(user_cmd,6000);
system(user_cmd);
memset(user_cmd,'-',6000);
//puts(user_cmd);
//while(done==0){std::cin >> cmd; done=make_stream_call(user_cmd);}
//cycle=2;
//while(cycle>1){cycle--;getline(cmd, i, ' '){};user_cmd << cmd;}

 // std::cout << "Please, enter your name: ";
  
//std::cout << i << std::endl;
//i=user_cmd.str().c_str();

//done=make_stream_call(user_cmd);
 //std::stringstream ww(user_cmd); 

 //std::vector <std::string> tokens; 
 //std::string intermediate;      
     // while(getline(user_cmd, intermediate, ' ')){ 
   //           while(getline(ww, intermediate, ' ')){ 
     //   tokens.push_back(intermediate); 
    //}; 
      
//std::string s;
//for (const auto &piece : v) s += piece;
//return s;
 // std::vector <std::string> tokens2; 
 // tokens2.push_back(user_cmd);

 // user_cmd=tokens;
//make_stream_call(tokens2);



 // std::cout << "input: help or exit" << std::endl;
//std::cin >> r;
//cycle=4;
//while(cycle>1){cycle--;std::cout << "cycle:" + //std::to_string(cycle) << std::endl;}

  //char str[6000];
  //memset (str,'-',6000);
  //puts (str);
//std::cout << "memset complete" << std::endl;

//help();
//if(r=="exit"){return 0;}
//if(r=="help"){help();}
//r=r+"; sleep 4";
//std::cout << "r"+r << std::endl;
//cmd=r.c_str()
//i=system();
//std::cout << "The value returned was:" + i << std::endl;
//printf ("The value returned was: %c.\n",i);
//question("hy");
//question("why");

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


int make_stream_call(std::stringstream stream){
//std::vector <std::string> tokens; 
//std::string s;
//std::stringstream s;
/*
std::string const_iterator; 
for (std::vector<std::string>::const_iterator i = tokens.begin(); i != tokens.end(); ++i)
    {s += *i;};
*/
//for (auto const& sr : the_stream) { s << sr;  }
//for (const auto &piece : the_stream) {s += piece;}
//cycle=4;
//while(cycle>1){cycle--;std::cout << "cycle:" + //std::to_string(cycle) << std::endl;}
 
//system(the_stream.str().c_str());
//std::stringstream stream;
//s << stream;
system(stream.str().c_str());
return 1;
}
