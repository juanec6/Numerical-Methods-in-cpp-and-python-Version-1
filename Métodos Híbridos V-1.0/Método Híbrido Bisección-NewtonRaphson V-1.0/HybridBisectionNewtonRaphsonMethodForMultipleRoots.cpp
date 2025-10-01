#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>  // This makes the programe not portable It will only run on windows. 

using namespace std;

string funcion_str(int option) {
    switch(option) {
        case 1: return "f(x) = sin(x) + 0.5*sin(3x) + 0.25*sin(5x)";
        case 2: return "f(x) = sin(50x)*exp(-x^2/100)";
        case 3: return "f(x) = sin(x) + sin(3x)";
        case 4: return "f(x) = sin(x)*cos(x)";
        case 5: return "f(x) = sin(x)*(x-2)*(x+3)";
        case 6: return "f(x) = cos(x) - exp(-x/10)";
        case 7: return "f(x) = cos(x)";
        default: return "Function not defined";
    }
}


// This are the functions to evaluate the method. You can change it if you want
double f(double x, int option){
	switch(option){
		case 1: return sin(x) + 0.5*sin(3.0*x) + 0.25*sin(5.0*x);
		case 2: return sin(50.0*x)*exp(-(pow(x, 2))/100.00);
		case 3: return sin(x)+ sin(3.0*x);
		case 4: return sin(x)*cos(x);
		case 5: return sin(x)*(x-2.0)*(x+3.0);
		case 6: return cos(x) - exp(-x/10.0);
		case 7: return cos(x);
		default: return 0; 
	}
}


// This will be the first derivate of f(x) 
double df(double x, int option){
	switch(option){
		case 1: return cos(x) + 1.5*cos(3.0*x) + 1.25*cos(5.0*x);
		case 2: return exp(-(x*x)/100.0)*(50.0*cos(x*50.0)- 0.02*x*sin(50.0*x));
		case 3: return cos(x) + 3.0*cos(3.0*x);
		case 4: return pow(cos(x), 2) - pow(sin(x), 2);
		case 5: return (-6.0 + x + pow(x, 2))*cos(x) + (1.0 + 2.0*x)*sin(x);
		case 6: return exp(-x/10.0)/10.0 - sin(x);
		case 7: return -sin(x);
		default: return 0;
	}
}

// Now we need the second derivate to check convergence of NewtonRapshon's method

double ddf(double x, int option){
	switch(option){
		case 1: return -sin(x) - 4.5*sin(3.0*x) - 6.25*sin(5.0*x);
		case 2: return ( exp(-pow(x, 2) / 100.0) * 
              ( (pow(x, 2) - 6250050.0) * sin(50.0 * x) - 5000.0 * x * cos(50.0 * x) ) 
             ) / 2500.0;
        case 3: return -9.0*sin(3.0*x) - sin(x);
        case 4: return -4.0*cos(x)*sin(x);
        case 5: return((-pow(x, 2) - x + 8.0) * sin(x)) + ((4.0 * x + 2.0) * cos(x));
        case 6: return -cos(x) - (exp(-x / 10.0) / 100.0);
        case 7: return -cos(x);
		default: return 0;
	}
}

int main() {
	system("chcp 65001 > nul");
    int repeat;
    
    do {
        system("cls"); 
        int option;

        cout << "----- HYBRID BISECTION AND NEWTON-RAPHSON FOR FINDING MULTIPLE ROOTS -----" << endl;
        cout <<endl;
        cout<<endl;
        cout<<"List of functions: "<<endl;
        cout<<endl; 
        cout << "1. f(x) = sin(x) + 0.5*sin(3.0*x) + 0.25*sin(5.0*x)" << endl;
        cout << "2. f(x) = sin(50.0*x)*exp(-(pow(x, 2))/100)" << endl;
        cout << "3. f(x) = sin(x)+ sin(3.0*x)" << endl;
        cout << "4. f(x) = sin(x)*cos(x)" << endl;
        cout << "5. f(x) = sin(x)*(x-2)*(x+3)" << endl;
        cout << "6. f(x) = cos(x) - exp(-x/10.0)" << endl;
        cout << "7. f(x) = cos(x)" << endl;
        cout << endl;
        cout << "Please select a function to test:" << endl;
        cin >> option;
		
        cout << "Selected function: " << funcion_str(option) << endl;

        cout << "Want to try a different function? (1 = yes, 0 = no): ";
        cin >> repeat;

    } while (repeat == 1);

    return 0;
}
