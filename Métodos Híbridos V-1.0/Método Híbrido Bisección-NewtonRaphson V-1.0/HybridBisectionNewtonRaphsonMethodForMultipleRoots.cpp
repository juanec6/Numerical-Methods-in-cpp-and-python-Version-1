// Validar las entradas del usuario (intervalos correctos, pasos >0, opciones válidas) 
// Validar que xi < xf 

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


// This will be the first derivate of f(x) which will need to be updated if updated f(x, opcion)
// Wich means that you need to calculate the first derivate of the functions updated in the previous functions 
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
// if f(x, opcion) you will ned find the second derivates for this function ddf as well

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
        int option, option2, option3, maxIter = 2000;
		double xi, xf, tolBi = 1e-3, tolUser, absErr = 1e-8 , relErr = absErr*100.00, relErrUser, step;
		/* I choose this tolBi to be the deffect tolerance for the bisection method to stop,
		since the purpose of this hybrid method is to use less computational power and get a faster result with newton method. 
		tolUser is in case the the user knows or requires an specific tolerance and understand that it will take more computational power.
		Now, */ 
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
        cout << "Please select a function to test (select one number from 1 to 7): ";
        cin >> option;
        cout << "\nSelected function: " << funcion_str(option) << endl;
        cout << endl;
        cout << "Please select the interval [xi, xf] you want to evaluate:"<<endl;
        cout << "xi = ";
        cin >> xi;
        cout << "xf = ";
        cin >> xi;
        cout << "Please select the step for each iteration e.g (1, 0.5, .., 0.1): ";
        cin >> step;
        cout << endl;
        
        cout << "¡¡TOLERANCE DISCLAIMER FOR BISECTION METHOD!!"<<endl;
        // let's talk about tolerance
        cout << "In metrology, tolerance is the margin of error or variation allowed\n"
     		 << "in the manufacturing of a part with respect to its dimension or\n"
     		 << "characteristic specified in the drawing, guaranteeing its functionality."
     		 << endl;
    	cout << endl;
    	cout << "In numerical methods, tolerance is the allowed error limit\n"
     		 << "used to stop iterative algorithms when the solution is close enough,\n"
     		 << "balancing accuracy with computational cost." 
			 << endl;
			 
		cout << endl;
		cout << "If you need an specific tolerance for the bisection method press 1, otherwise, press 2: ";
		cin >> option2;
		cout << endl;
		
		// In case the user needs an specific tolerance for the bisection method to stop, he/him will be able to do it, otherwise, a default tolerance will be used
		if(option2 == 1){
			cout << "Please enter the tolerance needed to stop iterations for bisection method: ";
			cin >> tolUser;
			cout << endl;
		} else {
			cout <<"Default tolerance to stop bisection method iterations is: "<< tolBi << endl;
		}
		
		cout<<endl;
		cout << "This program calculates the stopping criteria for the newton-rapshon method using a relative error.\n"
			 << "If you need an specific relative error to stop the the iterations, press 1, otherwise, press 2: ";
		cin >> option3;
		cout << endl;
		
		//In case the user needs an specific relative error
		if(option3 == 1){
			cout << "Please enter the relative error required to stop iterations (Enter a percentage number, e.g 10%, 56%,..100% without the % symbol): ";
			cin >> relErrUser;
			cout << endl;
		} else {
			cout << "The default relative error for stopping newton-rapshon iterations is: " << relErr << "%" << endl;
		}
		cout << endl;
		cout << "This program will stop at 2000 iterations if has not reached the paremeters entered" << endl;
		cout << "Iterating..."<<endl;
		cout << endl;
        

        cout << "Want to try a different function? (1 = yes, 0 = no): ";
        cin >> repeat;

    } while (repeat == 1);

    return 0;
}

    return 0;
}

