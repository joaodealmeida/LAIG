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
#include "SocketClient.h"
#include "LeBloq.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();


	//Podes desbloquear isto para veres como ele guarda os blocks no vector. Tens no demoscene na funcao displayBlocks() la o vetor com as pe�as.
	LeBloq::getInstance().newGame(12,12);
	LeBloq::getInstance().setGameType(LeBloqGameTypePlayerVsAI_Hard);
	//LeBloq::getInstance().setMaxTurnTime(5);
		



	try {
		app.init(&argc, argv);
		DemoScene * scene = new DemoScene("scene.anf");
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