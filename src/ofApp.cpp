#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  // load in sounds:
  carl.load("sounds/carl_stone.mp3");
  carl.play();

  ofSetBackgroundAuto(false);
  ofEnableAlphaBlending();
  ofBackground(10, 10, 20);
}
float t = 0.0;

//--------------------------------------------------------------
void ofApp::update() {

  // update the sound playing system:
  ofSoundUpdate();

  carl.setVolume(0.0);

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
  // t += fftSmoothed[2] * 2.0 / 30.0;
  t += 0.002;
}

void drawNoisySquare(ofRectangle bounds, ofColor color, float i) {
  float radius = 10.0;
  ofColor secondColor = ofColor::fromHex(color.getHex());
  secondColor.setHue(int(color.getHue() + 50) % 255);
  if (bounds.getWidth() < radius || bounds.getHeight() < radius) {
    return;
  }
  ofRectangle inset = ofRectangle(ofRandomWidth(), ofRandomHeight(),
                                  ofRandomWidth(), ofRandomHeight());
  //  ofNoise(i)
  for (float x = bounds.getLeft(); x <= bounds.getRight(); x += radius) {
    for (float y = bounds.getTop(); y <= bounds.getBottom(); y += radius) {

      float xOffset = ofSignedNoise(x * 0.1, y * 0.1, t * 0.5);
      float yOffset = ofSignedNoise(x * 0.1 + 16.3, y * 0.1 + 16.3, t * 0.5);
      ofVec2f point = ofVec2f(x + xOffset * radius, y + yOffset * radius);
      if (inset.inside(point)) {
        ofSetColor(secondColor);
      } else {
        ofSetColor(color);
      }
      ofDrawCircle(point, radius * 0.3);
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofEnableBlendMode(OF_BLENDMODE_ALPHA);
  ofSetColor(0, 0, 0, 50);
  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

  // draw the fft resutls:
  ofSetColor(255, 255, 255, 255);
  ofSeedRandom(0);
  // float width = (float)(5 * 128) / nBandsToGet;
  // for (int i = 0; i < nBandsToGet; i++) {
  // ofDrawRectangle(10 + i * width, ofGetHeight() - 10, width,
  // -(fftSmoothed[i] * 200));
  // }

  // finally draw the playing circle:

  // ofEnableAlphaBlending();
  // ofSetColor(255, 255, 255, 20);
  // ofDisableAlphaBlending();

  ofSetColor(255, 255, 255, 100);

  ofEnableBlendMode(OF_BLENDMODE_SCREEN);

  // float t = ofGetElapsedTimef();
  // fl
  float n = 0.8 + (sin(t) + 1.0) * 2.0;

  for (int i = 0; i < 5; i++) {

    float sizeclamp = 1.0;
    if (n < i) {
      sizeclamp = max(1.0 - (float(i) - n) * 5.0, 0.);
    }

    ofPoint r_size =
        ofPoint(50) + ofPoint(ofNoise(t, 6.6 * i), ofNoise(t + 9.2, 9.5 * i)) *
                          ofGetWindowSize() * 0.3;

    if (i % 2 == 0) {
      r_size.x *= sizeclamp;

    } else {
      r_size.y *= sizeclamp;
    }

    ofPoint r_start = ofPoint(10, 10) +
                      ofPoint(ofNoise(t, i * 0.5), ofNoise(t + 0.8, i * 1.2)) *
                          (ofGetWindowSize() - (ofPoint(20, 20) + r_size));

    ofColor rectcolor = ofColor::fromHsb(ofRandom(255), 140 + ofRandom(30),
                                         20 + ofRandom(90), 10);

    // if (ofNoise(t * 0.5 + ofRandomf(), 603.0) > 0.7) {
    if (sizeclamp < 1.0 || ofNoise(t * 0.5 + ofRandomf(), 603.0) > 0.7

    ) {
      ofSetColor(rectcolor);

      ofDrawRectangle(r_start.x, r_start.y, r_size.x, r_size.y);

    } else {

      drawNoisySquare(ofRectangle(r_start.x, r_start.y, r_size.x, r_size.y),
                      rectcolor, float(i));
    }
  }

  // ofDrawCircle(x, y, 2);

  // line.addVertex(x, y);
  // if (line.size() > 200) {
  //   line.getVertices().erase(line.getVertices().begin());
  // }
  // line.draw();
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
