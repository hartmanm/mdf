#include <iostream>
#include <string>
//#include <cstring>
#include <fstream>
#include <iterator>
//#include <ctime>
//#include <map>
//#include <algorithm>
using namespace std;

/*

string get_dtg(){
// c++ equalivent to:  DTG=$(date | tr ': ' '_')
time_t now = time(0);
char* cdate = ctime(&now);
char _no_spaces_date[24];
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
} //string get_dtg(){

*/

int main(int argv, char *argc[]){

/*
string current_dtg=get_dtg();
cout << current_dtg;

//return 0;




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



file_string="";

*/

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

//for_each(_file_string.begin(), _file_string.end(), fn);

/*

// iterate thru string and recreate it
ifstream _the_file("datafile");
string _file_string(istreambuf_iterator<char>{_the_file}, {});
int iterator=0;
const char* char_iterator;
string token;
string processed;
string cstring_file = _file_string;
//cout << endl << cstring_file;
while(iterator < cstring_file.length()){
//cout << endl;
//cout << cstring_file[iterator];
if(cstring_file[iterator] == '\n' && token == ""){processed+='\n';}

if(cstring_file[iterator] == ' ' || (cstring_file[iterator] == '\n' && token != "")){
//cout << "processed space";
processed+=token;
if(cstring_file[iterator] == '\n' && token != ""){processed+='\n';}
if(cstring_file[iterator] == ' '){processed+=' ';}
//cout << "processed" << processed << endl;
//cout << "token" << token << endl;
token="";
}
if(cstring_file[iterator] != ' ' && cstring_file[iterator] != '\n'){
token+=cstring_file[iterator];
}
iterator++;
} // while(iterator < cstring_file.length()){


cout << endl << processed;

// write in memory string to file
to_file.open ("processed");
to_file << processed;
to_file.close();
system("cat processed");



cout << endl << "----------------------------------------" << endl;
*/


// return map (line)
// search for first token in string from file
//string target_token="VERSION_CONTROL";
//ifstream target_file("datafile");
if(!argc[1]){cout << "missing target map!" << endl; return 0;}
if(!argc[2]){cout << "missing target datafile!" << endl; return 0;}
string target_token=argc[1];
ifstream target_file(argc[2]);
string key="";
if(argc[3]){key=argc[3];}
string search_string(istreambuf_iterator<char>{target_file}, {});

cout << "target_token: " << target_token << endl;
cout << "target_file:  " << argc[2] << endl;
cout << "target_key:   " << key << endl;

int _iterator=0;
const char* _char_iterator;
string _token;
string _processed;
bool on_token_line=false;
bool processing_key_value=false;
//bool on_first_token=true;
while(_iterator < search_string.length()){
//cout << endl;
//cout << search_string[iterator];
//if(search_string[_iterator] == '\n' && _token == ""){_processed+='\n';}

if(search_string[_iterator] == ' ' || search_string[_iterator] == '\n'){
//cout << "_processed space";
//_processed+=_token;

if(target_token == _token || on_token_line || processing_key_value){
if(key != "" && processing_key_value){
_processed+=_token;
ofstream to_file;
to_file.open ("result");
to_file << _processed;
to_file.close();
cout << _processed << endl;
return 0;
} // if(key != "" && processing_key_value){
if(key == ""){_processed+=_token;_processed+=' ';}
on_token_line=true;
} // if(target_token == _token || on_token_line || processing_key_value){

if(on_token_line){
if(search_string[_iterator] == '\n'){


// write result to file
ofstream to_file;
to_file.open ("result");
to_file << _processed;
to_file.close();
cout << _processed << endl;

return 0;}
}
//cout << "_processed" << _processed << endl;
//cout << "_token" << _token << endl;
_token="";
}
if(search_string[_iterator] != ' ' && search_string[_iterator] != '\n'){
//if(search_string[_iterator] != '@' ){_token+=search_string[_iterator];}
//if(search_string[_iterator] == '@' ){_token+=' ';}
_token+=search_string[_iterator];

if(key != ""){
if(on_token_line){
//int token_length = _token.length();
//int target_token_length = target_token.length();
//if(_token == key && token_length != target_token_length)

if(_token == key && search_string[_iterator+1] == ':'){processing_key_value=true;_token="";}
if(search_string[_iterator] == ':'){_token="";}
//if(search_string[_iterator] != ':' && processing_key_value){_token+=search_string[_iterator];}
} // if(on_token_line){
} // if(key != ""){


} // if(search_string[_iterator] != ' ' && search_string[_iterator] != '\n'){
_iterator++;
} // while(iterator < search_string.length()){


//cout << endl << _processed << endl;

// for converting @ to ' '
/*
if(search_string[_iterator] != ' ' && search_string[_iterator] != '\n'){
//if(search_string[_iterator] != '@' ){_token+=search_string[_iterator];}
//if(search_string[_iterator] == '@' ){_token+=' ';}
_token+=search_string[_iterator];
}
*/

// time ./mdb VERSION_CONTROL datafile
// time grep  VERSION_CONTROL datafile

// time grep VERSION_CONTROL datafile | tr ' ' '\n' | grep VERSION | tail -1 | tr ':' ' ' | awk {'print $2'}
// time ./mdb VERSION_CONTROL datafile VERSION

return 0;
}
// clang++-7 -pthread -std=c++17 -o mdb mdb.cpp