#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iterator>
#include <ctime>
#include <map>
using namespace std;


string get_date(){
// c++ equalivent to:  DTG=$(date | tr ': ' '_')
time_t now = time(0);
char* cdate = ctime(&now);
char _no_spaces_date[20];
string date=string(cdate);
string no_spaces_date;
int _iterator=0;
while(_iterator < sizeof(date)){
if(date[_iterator] != ' ' && date[_iterator] != ':'){_no_spaces_date[_iterator]=date[_iterator];}
if(date[_iterator] == ' ' || date[_iterator] == ':'){_no_spaces_date[_iterator]='_';}
//cout << endl;
//cout << date[_iterator];
//cout << endl;
//cout << _no_spaces_date;
_iterator++;
}
no_spaces_date=string(_no_spaces_date);
return no_spaces_date;
}

int main(int argv, char *argc[]){


string current_dtg=get_date();
cout << current_dtg;

return 0;




//std::string rd = "#!/bin/bash\n mkdir -p /media/rd; mount -t ramfs -o size=256M ramfs /media/rd";
const char* cmd;
std::string rd = "mkdir -p /media/rd; mount -t ramfs -o size=256M ramfs /media/rd";




// make file 
ofstream to_file;
to_file.open ("generate_ramdisk");
to_file << rd;
to_file.close();

//cmd = rd.c_str();
system("pwd");
system("bash generate_ramdisk");


// make in memory string from file
ifstream the_file("generate_ramdisk");
string file_string(istreambuf_iterator<char>{the_file}, {});


cout << file_string ;



cmd = file_string.c_str();
system(cmd);


// write in memory string to file
to_file.open ("regen");
to_file << file_string;
to_file.close();

system("cat regen");


const char* cstring_file = file_string.c_str();
const char* ifs = ",";
const char* line_separator = "\n";
int iterator=0;
const char* char_iterator;
char* line;
char* token;
string processed;




/*
map reference
std::map<std::string, string> kvstore;

// Inserting data in std::map
kvstore.insert(std::make_pair("earth", "world"));
kvstore.insert(std::make_pair("moon", 2));
kvstore["sun"] = 3;
// Will replace the value of already added key i.e. earth
kvstore["earth"] = 4;
// Iterate through all elements in std::map
std::map<std::string, int>::iterator it = kvstore.begin();
while(it != kvstore.end())
{
std::cout<<it->first<<" :: "<<it->second<<std::endl;
it++;
}
// Check if insertion is successful or not
if(kvstore.insert(std::make_pair("earth", 1)).second == false)
{
std::cout<<"Element with key 'earth' not inserted because already existed"<<std::endl;
}
// Searching element in std::map by key.
if(kvstore.find("sun") != kvstore.end())
std::cout<<"word 'sun' found"<<std::endl;
if(kvstore.find("mars") == kvstore.end())
std::cout<<"word 'mars' not found"<<std::endl;
*/



bool in_token=true;
bool column_header_mode=false;
//bool on_header=true;

map<string, string> kvstore;

while(cstring_file[iterator] != EOF){
char_iterator=&cstring_file[iterator];
if(char_iterator == line_separator){

line=0;
}


if(char_iterator == ifs){
if(column_header_mode){kvstore.insert(make_pair("earth",token));}

kvstore.insert(make_pair("earth",token));


in_token=false;
}


if(char_iterator != ifs && char_iterator != line_separator){
if(in_token){


}

}

//if(){}
//if(){}

iterator++;
}





return 0;
}
// clang++-7 -pthread -std=c++17 -o mo mo.cpp
