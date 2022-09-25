#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void calcResizeFactor(int w, int h);
		void generateMesh();

	private:
		ofImage				m_image;
		float				m_xFactor;
		float				m_yFactor;
		ofVec2f				m_ulImage;
		ofMesh				m_mesh;
		ofEasyCam			m_easyCam;
		ofShader			m_shader;
		
};
