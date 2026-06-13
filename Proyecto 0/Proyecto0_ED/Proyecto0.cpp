#include <iostream>
#include <String>
#include "Area.h"
#include "Ventanilla.h"	
#include "Sistema.h"
#include <ctime>
#include <iomanip>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::time_t;


int main() {
    Sistema* sistema = new Sistema();
    sistema->programa();
    return 0;
}