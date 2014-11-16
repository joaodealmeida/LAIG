#include "TPinterface.h"
#include "DemoScene.h"

TPinterface::TPinterface(DemoScene *scene)
{
	testVar=0;
	this->scene=scene;

}



void TPinterface::initGUI(){
	GLUI_Panel *drawingPanel = addPanel(const_cast<char *>(std::string("Drawing Style").c_str()), 1);
    
    int id = 0;
    
    addButtonToPanel(drawingPanel, const_cast<char *>(std::string("Line").c_str()), 1);
    
    addButtonToPanel(drawingPanel, const_cast<char *>(std::string("Point").c_str()), 2);
    
    addButtonToPanel(drawingPanel, const_cast<char *>(std::string("Fill").c_str()), 3);
    
    addColumn();
    
    GLUI_Panel *lightsPanel = addPanel(const_cast<char *>(std::string("Lights").c_str()), 1);
    
    id = 10;
    
    for (int i=0; i<scene->getParserResults()->omniLightVec.size(); i++) {
		OmniLight * l= scene->getParserResults()->omniLightVec[i];
        GLUI_Checkbox *checkbox = addCheckboxToPanel(lightsPanel, const_cast<char *>(l->getID().c_str()), nullptr, id);
        
        checkbox->set_int_val(l->getEnabled() ? 1 : 0);
        
        id++;
    }
	for (int i=0; i<scene->getParserResults()->spotLightVec.size(); i++) {
		SpotLight * l= scene->getParserResults()->spotLightVec[i];
        GLUI_Checkbox *checkbox = addCheckboxToPanel(lightsPanel, const_cast<char *>(l->getID().c_str()), nullptr, id);
        
        checkbox->set_int_val(l->getEnabled() ? 1 : 0);
        
        id++;
    }

    
    addColumn();
    
    GLUI_Panel *camerasPanel = addPanel(const_cast<char *>(std::string("Camera").c_str()), 1);
    
    id = 100;
    
    for (int i=0; i<scene->getParserResults()->OrthocamVec.size(); i++) {
		OrthoCamera *o = scene->getParserResults()->OrthocamVec[i];
        addButtonToPanel(camerasPanel, const_cast<char *>(o->getIdentifier().c_str()), id);
        
        id++;
    }
	for (int i=0; i<scene->getParserResults()->PerscamVec.size(); i++) {
		PerspectiveCamera * p = scene->getParserResults()->PerscamVec[i];
        addButtonToPanel(camerasPanel, const_cast<char *>(p->getID().c_str()), id);
        
        id++;
    }
}

void TPinterface::processGUI(GLUI_Control *ctrl)
{
	if (ctrl->user_id < 10) {
		switch (ctrl->user_id)
		{
		case 1:
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			for(int i=0; i<scene->getParserResults()->sceneGraph->getGraphNodes().size(); i++){
				Node * n =  scene->getParserResults()->sceneGraph->getGraphNodes()[i];
				for(int j=0; j<n->getPrimitives().size(); j++)
					n->getPrimitives()[j]->setDrawStyle(GLU_LINE);
			}
			break;

		case 2:
			glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
			for(int i=0; i<scene->getParserResults()->sceneGraph->getGraphNodes().size(); i++){
				Node * n =  scene->getParserResults()->sceneGraph->getGraphNodes()[i];
				for(int j=0; j<n->getPrimitives().size(); j++)
					n->getPrimitives()[j]->setDrawStyle(GLU_POINT);
			}
			break;

		case 3:
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			for(int i=0; i<scene->getParserResults()->sceneGraph->getGraphNodes().size(); i++){
				Node * n =  scene->getParserResults()->sceneGraph->getGraphNodes()[i];
				for(int j=0; j<n->getPrimitives().size(); j++)
					n->getPrimitives()[j]->setDrawStyle(GLU_FILL);
			}
			break;
		
		default:
			break;
		}
    }else if (ctrl->user_id < 100) {
        int pos=ctrl->user_id - 10;
        int spotlimit,omnilimit;
		vector<OmniLight *> omni = scene->getParserResults()->omniLightVec;
		vector<SpotLight *> spot = scene->getParserResults()->spotLightVec;

		omnilimit = omni.size();
		spotlimit = spot.size();
		

		if(pos > spotlimit+omnilimit){
			std::cout << " Light not found \n" << std::endl;
			exit(1);

		}else{
			CGFlight *l1 = scene->sceneLights[pos];
			if(l1->getEnabled())
				l1->disable();
			else
				l1->enable();
		}
	} else {
        
        int camPos = (int)(ctrl->user_id - 100);
		int ortholimit,perslimit;
		ortholimit = scene->getParserResults()->OrthocamVec.size();
		perslimit = scene->getParserResults()->PerscamVec.size();
		vector<CGFcamera *> cams = scene->sceneCameras; 
        
        if (cams.size() < camPos)
            std::cout << "Camera not found \n" << std::endl;

		//Make sure all cameras are disabled
		for(int i=0; i<scene->getParserResults()->OrthocamVec.size(); i++)
			scene->getParserResults()->OrthocamVec[i]->setEnabled(false);

		for(int i=0; i<scene->getParserResults()->PerscamVec.size(); i++)
			scene->getParserResults()->PerscamVec[i]->setEnabled(false);
		
		if(camPos < ortholimit)
			scene->getParserResults()->OrthocamVec[camPos]->setEnabled(true);
		
		if(camPos >  ortholimit-1)
			scene->getParserResults()->PerscamVec[camPos-ortholimit]->setEnabled(true);

    }
}
