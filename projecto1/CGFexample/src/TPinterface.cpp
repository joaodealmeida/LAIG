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
    
    for (OmniLight *l : scene->getParserResults()->omniLightVec) {
        GLUI_Checkbox *checkbox = addCheckboxToPanel(lightsPanel, const_cast<char *>(l->getID().c_str()), nullptr, id);
        
        checkbox->set_int_val(l->getEnabled() ? 1 : 0);
        
        id++;
    }
	for (SpotLight *l : scene->getParserResults()->spotLightVec) {
        GLUI_Checkbox *checkbox = addCheckboxToPanel(lightsPanel, const_cast<char *>(l->getID().c_str()), nullptr, id);
        
        checkbox->set_int_val(l->getEnabled() ? 1 : 0);
        
        id++;
    }

    
    addColumn();
    
    GLUI_Panel *camerasPanel = addPanel(const_cast<char *>(std::string("Camera").c_str()), 1);
    
    id = 100;
    
    for (OrthoCamera *o : scene->getParserResults()->OrthocamVec) {
        addButtonToPanel(camerasPanel, const_cast<char *>(o->getIdentifier().c_str()), id);
        
        id++;
    }
	for (PerspectiveCamera *p : scene->getParserResults()->PerscamVec) {
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
			glPolygonMode(GL_FRONT_AND_BACK,GLU_LINE);
			for(Node *n : scene->getParserResults()->sceneGraph->getGraphNodes())
				for(Primitives *p : n->getPrimitives())
					p->setDrawStyle(GLU_LINE);
			break;

		case 2:
			glPolygonMode(GL_FRONT_AND_BACK,GLU_POINT);
			for(Node *n : scene->getParserResults()->sceneGraph->getGraphNodes())
				for(Primitives *p : n->getPrimitives())
					p->setDrawStyle(GLU_POINT);
			break;

		case 3:
			glPolygonMode(GL_FRONT_AND_BACK,GLU_FILL);
			for(Node *n : scene->getParserResults()->sceneGraph->getGraphNodes())
				for(Primitives *p : n->getPrimitives())
					p->setDrawStyle(GLU_FILL);
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
		for(OrthoCamera *o : scene->getParserResults()->OrthocamVec)
			o->setEnabled(false);

		for(PerspectiveCamera *p : scene->getParserResults()->PerscamVec)
			p->setEnabled(false);
		
		if(camPos < ortholimit)
			scene->getParserResults()->OrthocamVec[camPos]->setEnabled(true);
		
		if(camPos >  ortholimit-1)
			scene->getParserResults()->PerscamVec[camPos-ortholimit]->setEnabled(true);

    }
}

