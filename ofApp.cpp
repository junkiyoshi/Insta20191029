#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	this->mesh.setMode(OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();
	
	for (auto x = 180; x < 720; x += 360) {

		for (auto y = 180; y < 720; y += 360) {

			for (auto i = 0; i < 3; i++) {

				float noise_seed = ofRandom(1000);
				for (auto deg = 0; deg < 360; deg += 5) {

					auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
					auto noise_radius = ofMap(ofNoise(noise_seed, noise_location.x, noise_location.y, ofGetFrameNum() * 0.005), 0, 1, 60, 150);

					auto location = glm::vec3(x, y, 0) + glm::vec3(noise_radius * cos(deg * DEG_TO_RAD), noise_radius * sin(deg * DEG_TO_RAD), 0);
					this->mesh.addVertex(location);

					this->mesh.addColor(i == 0 ? ofColor(255, 64, 64) : i == 1 ? ofColor(64, 255, 64) : ofColor(64, 64, 255));
				}
			}

			for (int i = 0; i < this->mesh.getVertices().size(); i++) {

				auto location = this->mesh.getVertex(i);
				vector<int> near_index_list;
				for (int k = i + 1; k < this->mesh.getVertices().size(); k++) {

					auto other = this->mesh.getVertex(k);
					auto distance = glm::distance(location, other);
					if (distance < 13) {

						this->mesh.addIndex(i);
						this->mesh.addIndex(k);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();

	for (int i = 0; i < this->mesh.getVertices().size(); i++) {

		auto location = this->mesh.getVertex(i);
		auto color = this->mesh.getColor(i);

		ofSetColor(color);
		ofDrawCircle(location, 2);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}