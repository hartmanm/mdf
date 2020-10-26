#include <iostream>
#include <cstring>
int main(int argv, char *argc[]){
int i=0;int v=0;
char *str = (char *)malloc(v);
for(i = 1;i<=(argv-1);i++){
str=(char*)realloc(str,(v+strlen(argc[i])));
strcat(str,argc[i]);strcat(str," ");
}
system(str);return 0;
}
// clang++-7 -pthread -std=c++17 -o sc sc.cpp
