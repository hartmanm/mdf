#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iterator>
using namespace std;

int main(int argv, char *argc[]){

//std::string rd = "#!/bin/bash\n mkdir -p /media/rd; mount -t ramfs -o size=256M ramfs /media/rd";
const char* cmd;
std::string rd = "mkdir -p /media/rd; mount -t ramfs -o size=256M ramfs /media/rd";



ofstream to_file;
to_file.open ("generate_ramdisk");
to_file << rd;
to_file.close();

//cmd = rd.c_str();
system("pwd");
system("bash generate_ramdisk");


ifstream the_file("generate_ramdisk");
string file_string(istreambuf_iterator<char>{the_file}, {});





cout << file_string ;



cmd = file_string.c_str();
system(cmd);



to_file.open ("regen");
to_file << file_string;
to_file.close();

system("cat regen");


return 0;
}
// clang++-7 -pthread -std=c++17 -o mo mo.cpp
