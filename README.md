
# virtual console testing 
testing a virtual console thing.  
something that could be used to modify variables in a game using a debug menu etc  

## currently implemented things
mod - modify exposed variable  
tell - print exposed variable  


### exposing variables and using functions

expose variable. give the variable a name(as of now must be all capitals), the variable itself, and the type of the variable
```c++
    console->exposeVariable("TEST", &testvaruable, intiger);
```
  
add function. give it name and the pointer to the functiona
```cpp
    functionMap.insert(std::pair<const char*,void(*)(char*)>("TELL",&tell));
```

