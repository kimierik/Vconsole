#include "console.h"
#include <cstdio>
#include <utility>
#include <map>
#include <string.h>

#include <vector>


VConsole * VConsole::instance=nullptr;



//turn a string with spaces to a list of words
std::vector<char*> tokenizeString(const char* str){
    std::vector<char*> a;

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
                break;
            case floatingpoint:
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

    if (v==nullptr) {
        printf("%s is null\n",tokenlist[0]);
    }else{
        switch (v->type) {
            case intiger:
                printf("%i\n",*(int*)v->value);
                break;
            case string:
                break;
            case floatingpoint:
                break;
        }
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
}
