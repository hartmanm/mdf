// Copyright (c) 2020 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm
// cpp api for add/get/set line based maps with tab ifs key:values for text based datafiles

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
const string output_file="result";
// META
const string version="003"; 
const string author="Michael N. Hartman"; 
const string modification_date="Sun_Jan__3_20_12_41_2021"; 

// TODO add testing //

// TODO ensure to remove spaces when re-setting

// TODO manage likely errors in datafile 

// TODO make process launchable / persistent / keep injested in memory

// TODO manage reserved char : \t \n when entered as a key/value

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
string _token="";
string _processed="";
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
to_file.open (output_file);
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
to_file.open (output_file);
to_file << _processed;
to_file.close();
}
return _processed;
}
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
if(processing_key_value == false && search_string[_iterator] == '\n'){

// for adding new key
// generate modified stream 
// TODO can be improved
int iterator=0;
while(iterator < mod_line_start){_processed+=search_string[iterator];iterator++;}
line+=nodash;
line+=':';
line+=value;
_processed+=line;
while(_iterator < search_string.length()){_processed+=search_string[_iterator];_iterator++;}

if(output_to_file){
// write result to file
ofstream to_file;
to_file.open (output_file);
to_file << _processed;
to_file.close();
}
// for adding new key

return line;
} // if(processing_key_value == false && search_string[_iterator] == '\n'){
} // if(on_token_line){
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
// TODO can be improved
_iterator=0;
while(_iterator < mod_line_start){_processed+=search_string[_iterator];_iterator++;}
_processed+=line;
while(kv_iterator < search_string.length()){_processed+=search_string[kv_iterator];kv_iterator++;}
if(output_to_file){
// write result to file
ofstream to_file;
to_file.open (output_file);
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
} // string set_or_add_key_value_pair(string target_token,string search_string, string key, string value){


// add a map to a given search_string / datafile
string add_map(string search_string, string map_name, string map){
// search for map in search_string
// add if not present
// return error string otherwise

// ensure map is tab IFS
string processed_map="";
int _iterator=0;
string token;
while(_iterator <= search_string.length()){
if(search_string[_iterator] != '\t' && search_string[_iterator] != '\n' && search_string[_iterator] != ' '){
token+=search_string[_iterator];
} // if(search_string[_iterator] != '\t' && search_string[_iterator] != '\n' && search_string[_iterator] != ' '){
if(search_string[_iterator] == '\t' || search_string[_iterator] == '\n' || _iterator == search_string.length()){
int extra_char_check=0;
string processed_token="";
while(extra_char_check < map_name.length()){processed_token+=token[extra_char_check]; extra_char_check++;}
if(map_name == processed_token){
// map already exists key / value changes should be made with set_or_add_key_value_pair()
return "map already present; key / value changes should be made with set_or_add_key_value_pair()";
} // if(map_name == processed_token){
token="";
} // if(search_string[_iterator] == '\t' || search_string[_iterator] == '\n' || _iterator == search_string.length()){
_iterator++;
} // while(_iterator <= search_string.length()){

// map is not present append it
processed_map+='\n';
processed_map+=map_name;
processed_map+='\t';
processed_map+=map;
processed_map+='\n';
search_string+=processed_map;

if(output_to_file){
// write result to file
ofstream to_file;
to_file.open (output_file);
to_file << search_string;
to_file.close();
}

return search_string;
} // string add_map(string map, string search_string){


int main(int argv, char *argc[]){
if(!argc[1]){cout << "missing target map!" << endl; return 0;}
if(!argc[2]){cout << "missing target datafile!" << endl; return 0;}
string target_token=argc[1];
ifstream target_file(argc[2]);
string search_string(istreambuf_iterator<char>{target_file}, {});
search_string+='\n';
string key="";
string mode="";
string value="None";
bool is_key=false;
int number_tokens=2;
int i;
int j;
int jj;

bool is_tab=false;
int length_of_args;
string token="";
string last_key="";
if(!argc[3]){mode="get_map_or_key_value";}

if(argc[3]){

if(argc[3][0] == '-'){key=argc[3];mode="set_or_add_key_value_pair";}
if(argc[3][0] != '-' && argc[3][1] != '-'){mode="get_map_or_key_value";key=argc[3];}
if(argc[3][1] == '-'){
key="";
mode="add_map"; 
i=0; 
length_of_args=0;
// caculate the length of the map to add
while(number_tokens < argv){
length_of_args+=int(string(argc[number_tokens]).length());
number_tokens++;
} // while(number_tokens < argv){
// process spaces and tabs to ensure tab IFS and key values with spaces are processed as such
i=3;
while(i < argv){
j=0;
token="";
is_tab=false;
while(j < int(string(argc[i]).length())){
value="";
is_key=false;
token+=argc[i][j];
// look ahead to the next token and flag the end of the key if it is a new key
jj=0;
if(i+1 < argv){
while(jj < int(string(argc[i+1]).length()) && ! is_tab){
if(argc[i+1][jj] == ':'){
is_tab=true;
jj=int(string(argc[i+1]).length());
} // if(argc[i+1][jj] == ':'){
jj++;
} // while(jj < int(string(argc[i+1]).length()) && ! is_tab){
} // if(i+1 < argv){
j++;
} // while(j < int(string(argc[i]).length())){
key+=token;
if(! is_tab){key+=' ';}
if(is_tab){key+='\t';}
is_tab=false;
i++;
} // while(i < argv){
// remove leading --
i=2;
string final_key;
while(i < key.length()){
final_key+=key[i];
i++;
} // while(i < key.length()){
key=final_key;
} // if(argc[3][1] == '-'){
} // if(argc[3]){

// process full value with spaces
int args=4;
if(argc[args]){value="";}
while(argc[args]){value+=argc[args];value+=" ";args++;}
cout << endl;
cout << "target_token:              " << target_token << endl;
cout << "target_file:               " << argc[2] << endl;
cout << "mode" << ": " << mode << endl;
if(mode == "get_map_or_key_value"){cout << "key:                    " << key << endl;}
if(mode == "set_or_add_key_value_pair"){cout << "key_value_pair:            " << key << endl;}
if(mode == "add_map"){cout << "map:            " << key << endl;}

if(mode == "get_map_or_key_value"){
string search_result;
search_result=get_map_or_key_value(target_token,search_string,key);
//search_result=alt_find(target_token,search_string,key);
cout << search_result << endl;
if(output_to_file){cout << "result also written to the file: result" << endl;}
} // if(mode == "get_map_or_key_value"){

string current_dtg=get_dtg();
cout << current_dtg << endl;

if(mode == "set_or_add_key_value_pair"){
string modify;
modify=set_or_add_key_value_pair(target_token,search_string,key,value);
cout << modify << endl;
//cout << "!" << modify << "!" << endl;
if(output_to_file){cout << "result also written to the file: result" << endl;}
} // if(mode == "set_or_add_key_value_pair"){

if(mode == "add_map"){
string add;
add=add_map(search_string, argc[1], key);
cout << add << endl;
//cout << "!" << add << "!" << endl;
if(output_to_file){cout << "result also written to the file: result" << endl;}
} // if(mode == "add_map"){






return 0;
}

// test get kv
// time ./mdf VERSION_CONTROL datafile 
// time grep  VERSION_CONTROL datafile 

// time grep  VERSION_CONTROL datafile  > result; cat result

// time grep VERSION_CONTROL datafile | tr ' ' '\n' | grep VERSION | tail -1 | tr ':' ' ' | awk {'print $2'} > result; cat result
// time ./mdf VERSION_CONTROL datafile VERSION

// test set_kv
// time ./mdf VERSION_CONTROL datafile -VERSION 002

// test add kv no value
// time ./mdf VERSION_CONTROL datafile -NEW_VERSION

// test add kv with value
// time ./mdf VERSION_CONTROL datafile -NEW_VERSION_2 the 2 

// test add_map
// // time ./mdf NEW_MAP datafile --this:test is  the:6799 full map:edout 99:contents

// time ./mdf NEW_MAP datafile --this:test is  the:6799 full map:edout 99:contents

/*
 clang++ -pthread -std=c++17 -o mdf mdf.cpp
 ./mdf NEW_MAP datafile --this:test is  the:6799 full map:edout 99:contents
*/


// see aggregate below


// run tests

/*
exec "`head -432 mdf.cpp | tail -1`""

clang++ -pthread -std=c++17 -o mdf mdf.cpp ; time ./mdf VERSION_CONTROL datafile; time ./mdf VERSION_CONTROL datafile VERSION; time ./mdf VERSION_CONTROL datafile -VERSION 003; time ./mdf VERSION_CONTROL datafile -NEW_VERSION; time ./mdf VERSION_CONTROL datafile -NEW_VERSION_2 the 2; time ./mdf NEW_MAP datafile --this:test is  the:6799 full map:edout 99:contents; time ./mdf NEW_MAP result --this:test is  the:6799 full map:edout 99:contents; 

g++ -pthread -std=c++17 -o mdf mdf.cpp ; time ./mdf VERSION_CONTROL datafile; time  ./mdf VERSION_CONTROL datafile VERSION; time  ./mdf VERSION_CONTROL datafile -VERSION 003; time  ./mdf VERSION_CONTROL datafile -NEW_VERSION; time  ./mdf VERSION_CONTROL datafile -NEW_VERSION_2 the 2; time  ./mdf NEW_MAP datafile --this:test is  the:6799 full map:edout 99:contents; time ./mdf NEW_MAP result --this:test is  the:6799 full map:edout 99:contents; 

*/

// this one // c++20 pure

// compile
// test returning a map
// test returning a key from a given map
// test setting a kv 
// test adding a key with no value
// test adding a key with multiple tokens via space based ifs
// test adding a new map 
// test attempting to overwrite an existing map with a newmap

/*
clang++ -std=c++2a -o mdf mdf.cpp; time ./mdf VERSION_CONTROL datafile; time ./mdf VERSION_CONTROL datafile VERSION; time ./mdf VERSION_CONTROL datafile -VERSION 003; time ./mdf VERSION_CONTROL datafile -NEW_VERSION; time ./mdf VERSION_CONTROL datafile -NEW_VERSION_2 the 2; time ./mdf NEW_MAP datafile --this:test is  the:6799 full map:edout 99:contents; time ./mdf NEW_MAP result --this:test is  the:6799 full map:edout 99:contents;
*/








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

/*
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
to_file.open (output_file);
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
to_file.open (output_file);
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

if(search_string[_iterator] != ' ' && search_string[_iterator] != '\n'){
//if(search_string[_iterator] != '@' ){_token+=search_string[_iterator];}
//if(search_string[_iterator] == '@' ){_token+=' ';}
_token+=search_string[_iterator];
}
*/

// time ./mdf VERSION_CONTROL datafile 
// time grep  VERSION_CONTROL datafile

// time grep VERSION_CONTROL datafile | tr ' ' '\n' | grep VERSION | tail -1 | tr ':' ' ' | awk {'print $2'}
// time ./mdf VERSION_CONTROL datafile VERSION



// clang++-7 -pthread -std=c++17 -o mdf mdf.cpp

/*
string alt_find(string target_token,string search_string, string key){

//str.replace(str.find(key),str2.length(),"preposition");

//if(output_to_file){
// write result to file
//ofstream to_file;
//to_file.open (output_file);
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
to_file.open (output_file);
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

*/

// generic_lambda
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0428r2.pdf
/*
auto f = [](auto&& ...args) {
return foo(std::forward<decltype(args)>(args)...);
};

*/
