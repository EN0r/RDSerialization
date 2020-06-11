#include <iostream>
#include "RDSerialisation.h"
#include "SerializedClass.h"
Serialisor* serial;
int main()
{
    Serialisor* serial = Serialisor::getInstance();
    
    
    if (!serial->openFile("Test.RDV"))
        return -1;
    
    Player Player1;
    Player Player2;

    

    //std::string s = serial->findInFile<std::string>("ID");
    serial->SerialiseClass<Player>(Player1);

    return 1;
}