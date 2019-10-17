#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  // load in sounds:
  carl.load("sounds/carl_stone.mp3");
  carl.play();
}

//--------------------------------------------------------------
void ofApp::update() {

  ofBackground(10, 10, 20);

  // update the sound playing system:
  ofSoundUpdate();

  //   carl.setVolume(0.1);

  // (5) grab the fft, and put in into a "smoothed" array,
  //		by taking maximums, as peaks and then smoothing downward
  float *val = ofSoundGetSpectrum(nBandsToGet); // request 128 values for fft
  for (int i = 0; i < nBandsToGet; i++) {

    // let the smoothed value sink to zero:

    // take the max, either the smoothed or the incoming:
    if (fftSmoothed[i] < val[i]) {
      fftSmoothed[i] += 0.01;

    } else {
      fftSmoothed[i] -= 0.01f;
    }
    //   if (fftSmoothed[i] < 0.01) {
    // fftSmoothed[i] = 0.01;
    //   }
    //    val[i];
  }
}

//--------------------------------------------------------------
void ofApp::draw() {

  ofEnableAlphaBlending();
  ofSetColor(255, 255, 255, 100);
  ofDrawRectangle(10, ofGetHeight() - 210, 5 * 128, 200);
  ofDisableAlphaBlending();

  // draw the fft resutls:
  ofSetColor(255, 255, 255, 255);

  float width = (float)(5 * 128) / nBandsToGet;
  for (int i = 0; i < nBandsToGet; i++) {
    // (we use negative height here, because we want to flip them
    // because the top corner is 0,0)
    ofDrawRectangle(10 + i * width, ofGetHeight() - 10, width,
                    -(fftSmoothed[i] * 200));
  }

  // finally draw the playing circle:

  ofEnableAlphaBlending();
  ofSetColor(255, 255, 255, 20);
  ofDisableAlphaBlending();

  ofSetColor(255, 255, 255, 100);

  //   ofSetColor()

  float xOrig = ofGetWidth() / 2;
  float yOrig = ofGetHeight() / 2;
  float radius = fftSmoothed[3] * 400;
  float angle = ofGetElapsedTimef();

  float x = xOrig + radius * cos(angle * 10);
  float y = yOrig + radius * sin(angle * 1.7);
  ofDrawCircle(x, y, 2);

  line.addVertex(x, y);
  if (line.size() > 2000) {
    line.getVertices().erase(line.getVertices().begin());
  }
  line.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
  //   float speed = (mouseX * 2.) / ofGetWidth();
  //   cout << speed << endl;
  //   carl.setSpeed(speed);

  //   float pan = ((mouseX * 2.0) / ofGetWidth()) - 1.0;
  //   cout << pan << endl;
  //   carl.setPan(pan);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
