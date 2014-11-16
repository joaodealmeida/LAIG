/* 
 * G0_Base: projeto inicial de CGra
 * 
 */

#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "DemoScene.h"
#include "XMLScene.h"
#include "TPinterface.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();
	std::string get="";
	std::cout << "Enter the name of .anf file \n" << std::endl;
	std::cin >> get;
	get.append(".anf");

	try {
		app.init(&argc, argv);
		DemoScene * scene = new DemoScene(get);
		app.setScene(scene);
		app.setInterface(new TPinterface(scene));
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}
	

	return 0;
}