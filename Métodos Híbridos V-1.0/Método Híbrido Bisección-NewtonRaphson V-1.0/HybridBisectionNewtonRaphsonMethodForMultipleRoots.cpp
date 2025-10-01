#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>  // This makes the programe not portable It will only run on windows. 

using namespace std;

// This are the functions to evaluate the method. You can change it if you want
double f(double x, int opcion){
	switch(opcion){
		case 1: return sin(x) + 0.5*sin(3.0*x) + 0.25*sin(5.0*x);
		case 2: return sin(50.0*x)*exp(-(pow(x, 2))/100);
		case 3: return sin(x)+ sin(3.0*x);
		case 4: return sin(x)*cos(x);
		case 5: return sin(x)*(x-2)*(x+3);
		case 6: return cos(x) - exp(-x/10.0);
		case 7: return cos(x);
		default: return 0; 
	}
}


// This will be the first derivate of f(x) 
double df(double, opcion){
	switch(opcion){
		case 1: cos(x) + 1.5*cos(3*x) + 1.25*cos(5*x);
		case 2: exp(-(x*x)/100)*(50*cos(x*50)- 0.02*x*sin(50*x));
		case 3: cos(x) + 3*cos(3*x);
		case 4: pow(cos(x), 2) - pow(sin(x), 2);
		case 5: (-6 + x + pow(x, 2))*cos(x) + (1 + 2 x)*sin(x);
		case 6: exp(-x/10)/10 - sin(x);
		case 7: 
		default: return 0;
	}
}