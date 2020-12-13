#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <ctime>
//#include <cstring>
//#include <map>
//#include <algorithm>
using namespace std;
// MAGIC BOOLS
const bool output_to_file=true;
// META
const string version="002"; 
const string author="Michael N. Hartman"; 
const string modification_date="Sun_Dec_13_17_08_43_UTC_2020"; 

// TODO ensure to remove spaces when setting

// c++ equalivent to:  DTG=$(date | tr ': ' '_')
string get_dtg(){
time_t now = time(0);
char* cdate = ctime(&now);
char _no_spaces_date[24];
string date=string(cdate);
string no_spaces_date;
int _iterator=0;
while(_iterator < sizeof(date)){
if(date[_iterator] != ' ' && date[_iterator] != ':'){_no_spaces_date[_iterator]=date[_iterator];}
if(date[_iterator] == ' ' || date[_iterator] == ':'){_no_spaces_date[_iterator]='_';}
_iterator++;
}
no_spaces_date=string(_no_spaces_date);
return no_spaces_date;
} //string get_dtg(){


// searches a string datafile in the format:
// map_name key:value key:value
// map_name key:value key:value
// where the ifs is \t
string get_map_or_key_value(string target_token,string search_string, string key){
int _iterator=0;
const char* _char_iterator;
string _token;
string _processed;
bool on_token_line=false;
bool processing_key_value=false;
while(_iterator < search_string.length()){
if(search_string[_iterator] == '\t' || search_string[_iterator] == '\n'){
if(target_token == _token || on_token_line || processing_key_value){
if(key != "" && processing_key_value){
_processed+=_token;
if(output_to_file){
// write result to file
ofstream to_file;
to_file.open ("result");
to_file << _processed;
to_file.close();
}
return _processed;
} // if(key != "" && processing_key_value){
if(key == ""){_processed+=_token;_processed+='\t';}
on_token_line=true;
} // if(target_token == _token || on_token_line || processing_key_value){
if(on_token_line){
if(search_string[_iterator] == '\n'){
if(output_to_file){
// write result to file
ofstream to_file;
to_file.open ("result");
to_file << _processed;
to_file.close();
}
return _processed;}
}
_token="";
}
if(search_string[_iterator] != '\t' && search_string[_iterator] != '\n'){
_token+=search_string[_iterator];
if(key != ""){
if(on_token_line){
if(_token == key && search_string[_iterator+1] == ':'){processing_key_value=true;_token="";}
if(search_string[_iterator] == ':'){_token="";}
} // if(on_token_line){
} // if(key != ""){
} // if(search_string[_iterator] != '\t' && search_string[_iterator] != '\n'){
_iterator++;
} // while(iterator < search_string.length()){
return _processed;
} // string get_map_or_key_value(string target_token,string search_string, string key){


// sets a keys value or adds a key value pair to a given map
// TODO add a key value pair to a given map if key not present
// searches a string datafile in the format:
// map_name key:value key:value
// map_name key:value key:value
// where the ifs is \t
string set_or_add_key_value_pair(string target_token,string search_string, string key, string value){
int _iterator=0;
const char* _char_iterator;
string _token;
string _processed;
bool on_token_line=false;
bool processing_key_value=false;
bool processing_value=false;
bool processing_end_cap=false;
bool added_value=false;
string nodash=key.substr(1); 
string line="";
string old_value="";
int mod_line_start;
while(_iterator < search_string.length()){
if(search_string[_iterator] == '\t' || search_string[_iterator] == '\n'){
if(target_token == _token){
mod_line_start=_iterator - _token.length();
on_token_line=true;
} // if(target_token == _token){
if(on_token_line){
line+=_token;
line+='\t';
}
_token="";
} // if(search_string[_iterator] == '\t' || search_string[_iterator] == '\n'){
if(search_string[_iterator] != '\t' && search_string[_iterator] != '\n'){
_token+=search_string[_iterator];}
if(on_token_line){
if(_token == nodash && search_string[_iterator+1] == ':'){processing_key_value=true;}
if(processing_key_value){
if(key != ""){
if(search_string[_iterator] == ':'){
line+=nodash;
line+=':';
_token="";
int kv_iterator=_iterator;
while(kv_iterator < search_string.length()){
if(search_string[kv_iterator] != '\t' && search_string[kv_iterator] != ':'){
_token+=search_string[kv_iterator];
}
kv_iterator++;
if(search_string[kv_iterator] == '\t' || search_string[kv_iterator] == '\n'){
added_value=true;
}
if(added_value){
if(search_string[kv_iterator] == '\t' || search_string[kv_iterator] == '\n'){
line+=value;
processing_end_cap=true;
old_value=_token;
_token="";
line+='\t';
}
if(processing_end_cap){
_token="";
while(kv_iterator < search_string.length() && search_string[kv_iterator] != '\n'){
_token+=search_string[kv_iterator];
kv_iterator++;
} // while(kv_iterator < search_string.length() && search_string[kv_iterator] != '\n'){ inner
line+=_token;
if(search_string[kv_iterator] != '\n'){line+='\n';}
// generate modified stream
// TODO can be inmproved
_iterator=0;
while(_iterator < mod_line_start){_processed+=search_string[_iterator];_iterator++;}
_processed+=line;
while(kv_iterator < search_string.length()){_processed+=search_string[kv_iterator];kv_iterator++;}
if(output_to_file){
// write result to file
ofstream to_file;
to_file.open ("result");
to_file << _processed;
to_file.close();
}

return line;
} // if(processing_end_cap){
} // if(added_value){
} // while(kv_iterator < search_string.length()){
} // if(search_string[_iterator] == ':'){
} // if(key != ""){
} // if(processing_key_value){
} // if(on_token_line){
_iterator++;
} // while(iterator < search_string.length()){

return "-1";
} // string set_or_add_key_value_pair(string target_token,string search_string, string key_value_pair){


int main(int argv, char *argc[]){
if(!argc[1]){cout << "missing target map!" << endl; return 0;}
if(!argc[2]){cout << "missing target datafile!" << endl; return 0;}
string target_token=argc[1];
ifstream target_file(argc[2]);
string search_string(istreambuf_iterator<char>{target_file}, {});
string key="";
string mode="";
string value="None";
if(!argc[3]){mode="get_map_or_key_value";}
if(argc[3]){
if(argc[3][0] != '-'){key=argc[3];mode="get_map_or_key_value";}
if(argc[3][0] == '-'){key=argc[3];mode="set_or_add_key_value_pair";}
}
if(argc[4]){value=argc[4];}
cout << endl;
cout << "target_token:              " << target_token << endl;
cout << "target_file:               " << argc[2] << endl;
cout << mode << ": " << mode << endl;
if(mode == "get_map_or_key_value"){cout << "key:                    " << key << endl;}
if(mode == "set_or_add_key_value_pair"){cout << "key_value_pair:            " << key << endl;}

if(mode == "get_map_or_key_value"){
string search_result;
search_result=get_map_or_key_value(target_token,search_string,key);
//search_result=alt_find(target_token,search_string,key);
cout << search_result << endl;
if(output_to_file){cout << "result also written to the file: result" << endl;}
} // if(mode == "get_map_or_key_value"){

string current_dtg=get_dtg();
cout << current_dtg;

if(mode == "set_or_add_key_value_pair"){
string modify;
modify=set_or_add_key_value_pair(target_token,search_string,key,value);
cout << modify << endl;
//cout << "!" << modify << "!" << endl;
if(output_to_file){cout << "result also written to the file: result" << endl;}
} // if(mode == "set_or_add_key_value_pair"){
return 0;


// time ./mdb VERSION_CONTROL datafile 
// time grep  VERSION_CONTROL datafile 

// time grep  VERSION_CONTROL datafile  > result; cat result

// time grep VERSION_CONTROL datafile | tr ' ' '\n' | grep VERSION | tail -1 | tr ':' ' ' | awk {'print $2'} > result; cat result
// time ./mdb VERSION_CONTROL datafile VERSION

// time ./mdb VERSION_CONTROL datafile -VERSION 002

// clang++-7 -pthread -std=c++17 -o mdb mdb.cpp




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

//if(!argc[2]){cout << "missing target datafile!" << endl; return 0;}

//ifstream target_file(argc[2]);

//string search_string(istreambuf_iterator<char>{target_file}, {});


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


string alt_find(string target_token,string search_string, string key){

//str.replace(str.find(key),str2.length(),"preposition");

//if(output_to_file){
// write result to file
//ofstream to_file;
//to_file.open ("result");
//to_file << _processed;
//to_file.close();
//}
//return _processed;
//} // if(key != "" && processing_key_value){

std::size_t found = 0;
found = target_token.find(search_string);
cout << found << endl;
int iterator=found;
if(found==0){return "-1";}
string _processed;
bool append=false;
while(iterator < search_string.length()){
if(append==true){ 
if(search_string[iterator] == '\t' || search_string[iterator] == '\n')
{
// write result to file
ofstream to_file;
to_file.open ("result");
to_file << _processed;
to_file.close();
return _processed;  
} // if(search_string[iterator] == '\t' || search_string[iterator] == '\n')
if(search_string[iterator] != '\t'){_processed+=search_string[iterator];}
} // if(append==true){ 
if(search_string[iterator] == ':'){append=true;}
iterator++;
} // while(iterator < search_string.length()){
return "-2";
} // string alt_find(string target_token,string search_string, string key){


