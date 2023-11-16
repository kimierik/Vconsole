#include "console.h"
#include <cstddef>
#include <cstdio>
#include <raylib.h>
#include <utility>
#include <map>
#include <string.h>
#include <stdlib.h>

#include <vector>


VConsole * VConsole::instance=nullptr;



//expects this to be int
int parseInt(const char* str){
    
    int number=0;
    int current_mul=1;
    for (int i=strlen(str)-1; i>=0; i--) {
        number +=  (str[i]-0x30)*current_mul;
        current_mul*=10;
    }
    return number;
}


//turn a string with spaces to a list of words
//this vector needs to be cleaned
std::vector<char*> tokenizeString(const char* str){
    std::vector<char*> a;

    char buffer[1024];
    int bufferLen=0;

    //loop all characters
    for(size_t i =0;i<strlen(str);i++){
        if(str[i]!=' '){
            buffer[bufferLen++]=str[i];
        }else{
            buffer[bufferLen]=0;
            char* s=(char*)MemAlloc(sizeof(char)*bufferLen);
            strcpy(s, buffer);
            a.push_back(s);//i need to strcpy & malloc here
            //printf("added %s\n",buffer);
                                
            bufferLen=0;
            buffer[bufferLen]=0;
        }

    }

    buffer[bufferLen]=0;
    char* s=(char*)MemAlloc(sizeof(char)*bufferLen);
    strcpy(s, buffer);
    a.push_back(s);//i need to strcpy & malloc here
    //printf("added %s\n",buffer);
    //printf("bfule %i\n",bufferLen);

    return a;
}



VConsole* VConsole::getConsole(){
    if (instance==nullptr) {
        instance=new VConsole;
        return instance;
    }
    return instance;
}





//print variable from the exposedvariables thing
void tell(char*varnam){
    ExposedVariable* v=VConsole::getConsole()->getVar(varnam);
    if (v==nullptr) {
        printf("%s is null\n",varnam);
    }else{
        switch (v->type) {
            case intiger:
                printf("%i\n",*(int*)v->value);
                break;
            case string:
                //untested
                printf("%s\n",(char*)v->value);
                break;
            case floatingpoint:
                printf("%f\n",*(float*)v->value);
                break;
        }
    }
}


//only changes existing variables does not create if it does not exist
void mod(char*params){
    //first token is var name
    std::vector<char*> tokenlist=tokenizeString(params);
    //second is the value to set it to
    ExposedVariable* v=VConsole::getConsole()->getVar(tokenlist[0]);


    //printf("tokens 0:%s\n1:%s\n",tokenlist[0],tokenlist[1]);
    if (v==nullptr) {
        printf("%s is null\n",tokenlist[0]);
    }else{
        switch (v->type) {
            case intiger:
                //printf("set int to %i\n",parseInt(tokenlist[1]));
                // v.value is int pointer. deref it and assign it to the int of the sting tokenlist[1]
                (*(int*)v->value=parseInt(tokenlist[1]));
                break;
            case string:
                break;
            case floatingpoint:
                break;
        }
    }
    
    //loop all tokens in vec and free them
    for(size_t i=0; i<tokenlist.size();i++){
        free(tokenlist[i]);
    }

}


void VConsole::parseCommand(const char*text, int len){
    //printAllExposedvars();

    //loop all functions in function map
    for(std::map<const char*, void(*)(char*)>::iterator i=functionMap.begin();i!=functionMap.end();i++){
        //is thing
        if (strncmp(i->first, text, strlen(i->first))==0){
            i->second( (char*)text+ strlen(i->first)+1 );
        }

    }
    
}




ExposedVariable* VConsole::getVar(const char *name){

    if (exposedVariables.find(name)!=exposedVariables.end()){
        return &exposedVariables[name];
    }

    //printf("could not find %s.\n",name);
    return nullptr;
}




//default functionality
void VConsole::addDefaultFunctions(){
    functionMap.insert(std::pair<const char*,void(*)(char*)>("TELL",&tell));
    functionMap.insert(std::pair<const char*,void(*)(char*)>("MOD",&mod));
}
