#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	m_image.load("images/dresden.jpg");
	//calcResizeFactor(2048, 1536);
	float scale = 0.09f;
	m_image.resize(m_image.getWidth() * scale, m_image.getHeight() *scale);
	generateMesh();
	//ofGetCurrentWindow()->setWindowShape(m_image.getWidth(), m_image.getHeight());

	m_shader.load("vertexShader.vert","fragmentShader.frag");
	m_shader.setUniformTexture("texture", m_image.getTexture(), 0);

	ofLog() <<"Is loaded " << m_shader.isLoaded() << std::endl;
}

//--------------------------------------------------------------
void ofApp::update(){
	auto pixelData = m_image.getPixels().getData();

}

//--------------------------------------------------------------
void ofApp::draw(){
//	m_image.draw(m_ulImage.x, m_ulImage.y, m_image.getWidth() * m_xFactor, m_image.getHeight() * m_yFactor);
	//ofBackground(238, 123, 48);
//	ofColor centerColor = ofColor(238, 123, 48);
//	ofColor edgeColor = ofColor(85, 214, 190);
//	ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
 

	m_easyCam.begin();
		ofPushMatrix();
			ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
			m_shader.begin();

				m_mesh.draw();
			m_shader.end();
		ofPopMatrix();
	m_easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}
void ofApp::generateMesh() {
	m_mesh.setMode(OF_PRIMITIVE_LINES);
	m_mesh.enableIndices();

	float intensityThreshold = 150.0;
	int w = m_image.getWidth();
	int h = m_image.getHeight();
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			ofColor c = m_image.getColor(x, y);
			float intensity = (ofRandomf() + 1.0f) * 100.0f;//c.getLightness()*;
			if (intensity >= intensityThreshold) {
				float saturation = c.getSaturation();
				float z = ofMap(saturation, 0, 255, -100, 100);
				ofVec3f pos(x * 4, y * 4, z);
				m_mesh.addVertex(pos);
				m_mesh.addColor(c);
			}
		}
	}
	ofLogNotice() << "verts: " << m_mesh.getNumVertices();


	// Let's add some lines!
	float connectionDistance = 30;
	int numVerts = m_mesh.getNumVertices();
	for (int a = 0; a < numVerts; ++a) {
		ofVec3f verta = m_mesh.getVertex(a);
		for (int b = a + 1; b < numVerts; ++b) {
			ofVec3f vertb = m_mesh.getVertex(b);
			float distance = verta.distance(vertb);
			if (distance <= connectionDistance) {
				// In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
				// connected to form a line
				m_mesh.addIndex(a);
				m_mesh.addIndex(b);
			}
		}
	}
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	calcResizeFactor(w,h);
	//ofVec2f center = ofVec2f(ofGetCurrentWindow()->getWidth() / 2, ofGetCurrentWindow()->getHeight() / 2);
	//m_ulImage = ofVec2f(center.x - ((m_image.getWidth() * m_xFactor) / 2), center.y - ((m_image.getHeight()*m_yFactor) / 2));


}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::calcResizeFactor(int w, int h) {
	if(m_image.isAllocated()){

		float resizeX =  (float)w / (float)m_image.getWidth();
		float resizeY = (float)h / (float)m_image.getHeight();
	

		if (resizeX < resizeY) {
			m_xFactor = resizeX;
			m_yFactor = resizeX;
		}else{
			m_xFactor = resizeY;
			m_yFactor = resizeY;
		}
	}
}

