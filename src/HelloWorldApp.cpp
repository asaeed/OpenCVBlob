/**
 * OpenCV Blob
 *
 *
 * Ahmad Saeed
 * http://niltoid.com
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "gl.h"

#include "cinder/Capture.h"
#include "CinderOpenCV.h"

class HelloWorldApp : public ci::app::AppBasic {
public:
	void setup();
	void update();
	void draw();

	ci::Capture mCap;
	ci::gl::Texture mTexture;
};

void HelloWorldApp::setup() {
	try {
		mCap = ci::Capture( 640, 480 );
		mCap.start();
	}
	catch( ... ) {
		console() << "Failed to initialize capture" << std::endl;
	}
}

void HelloWorldApp::update() {
	if( mCap && mCap.checkNewFrame() ) {
		cv::Mat input( toOcv( mCap.getSurface() ) ), output;

	//	cv::threshold( input, output, 128, 255, CV_8U );

		cv::Sobel( input, output, CV_8U, 1, 0 );

	//	cv::Laplacian( input, output, CV_8U );

	//	cv::circle( output, toOcv( Vec2f(200, 200) ), 300, toOcv( Color( 0, 0.5f, 1 ) ), -1 );

	//	cv::line( output, cv::Point( 1, 1 ), cv::Point( 30, 30 ), toOcv( Color( 1, 0.5f, 0 ) ) );

		mTexture = ci::gl::Texture( ci::fromOcv( output ) );
	}
}
void HelloWorldApp::draw() {
	ci::gl::clear();
	if( mTexture )
		ci::gl::draw( mTexture );
}

CINDER_APP_BASIC( HelloWorldApp, ci::app::RendererGl )
