#pragma once


#include <map>
#include <raylib.h>
#include <utility>
#include <vector>
#include <stdio.h>


#include <string.h>




enum vartype{
    intiger,
    floatingpoint,
    string,
};



// this is because cpp does not know how to compare c strings in map
struct cstrcomp{
    bool operator()(char const *a,char const *b)const {
        return strcmp(a, b)!=0;
    }
};



struct ExposedVariable{
    vartype type;
    void* value;
};


//do we make this into a singelton
class VConsole{

    private:
        char input_text[1024]; //c string for simplicity
        int string_len;        //len of c string
                               
        std::map<const char*, void(*)(char*)> functionMap;   //this will have all of the commands that we have
                                                       
        //change void* to a struct that has enum that tells the type of the variable
        std::map<const char*, ExposedVariable ,cstrcomp> exposedVariables;   //this will have all of the variables we have access to

        std::vector<char[1024]> history; //history for the things that we have




    //begin singelton logic
    private:
    static VConsole*instance;
    VConsole(){
        string_len=0;
        //set input_text to be full of 0
        for(int i=0;i<1024;i++){ input_text[i]=0; }
        addDefaultFunctions();
    }
    public:
    VConsole(const VConsole&ob)=delete;
    static VConsole* getConsole();
    //end of singelton




    private:


    
    //parses the command 
    //the dude conpares the first (strlen of function name in func map) chars to the string that is given
    void parseCommand(const char* text, int len);


    void addDefaultFunctions();

    //append char to input text
    void addCharToInput(char character){
        input_text[string_len++]=character;
        input_text[string_len]=0;
    }

    void backspace(){
        if (string_len>0) {
            input_text[--string_len]=0;
        }
    }



    void enter(){
        //parse text
        //printf("%s\n",input_text);
        parseCommand(input_text, string_len);
        //add to history

        //clear text
        string_len=0;
        input_text[string_len]=0;
    }




    public:

    void printAllExposedvars(){
        for(std::map<const char*, ExposedVariable>::iterator i=exposedVariables.begin();i!=exposedVariables.end();i++){
            printf("exposed var %s,\n",i->first);
        }
    }

    ExposedVariable* getVar(const char*name);

    void addFunciton(const char* name, void(*funcion)(char*));

    void exposeVariable(const char* name, void* variable, vartype type){
        ExposedVariable v={type,variable};
        exposedVariables.insert(std::pair<const char*, ExposedVariable>(name,v));
    }


    void update(){
        int key=GetKeyPressed();
        if(key!=0){
            //printf("current key is  %c\n",key);
            if(key==KEY_ENTER){enter();}

            if(key==KEY_BACKSPACE){backspace();}

            if ((key>=KEY_A && key <=KEY_Z) || (key>= KEY_ZERO && key <= KEY_NINE)) {
                addCharToInput(key);
            }

            if(key==KEY_SPACE){addCharToInput(key);}

        }

    }



    void drawinput(){
        //hardcoded things
        DrawText(input_text,400,400,12,BLACK);
    }

        


};

