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
#include <vector>

#include "cinder/Capture.h"
#include "CinderOpenCV.h"

using namespace std;

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
		cv::Mat input( toOcv( mCap.getSurface() ) ), flipped, grayscale, blurred, thresholded, output;

		cv::flip(input, flipped, 1);
		cv::flip(input, output, 1);
		cv::cvtColor(flipped, grayscale, CV_RGB2GRAY);
		cv::blur(grayscale, blurred, cv::Size(10,10));
		cv::threshold( blurred, thresholded, 75.0f, 255, CV_THRESH_BINARY);

		// findContours requires grayscale image.  also it modifies input image so it won't be usable
		std::vector<std::vector<cv::Point> > contours;
		cv::findContours(thresholded, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		for (vector<vector<cv::Point> >::iterator it=contours.begin() ; it < contours.end(); it++ ){
			cv::Point2f center;
			float radius;
			vector<cv::Point> pts = *it;
			cv::Mat pointsMatrix = cv::Mat(pts);
			cv::minEnclosingCircle(pointsMatrix, center, radius);
			cv::Scalar color( 0, 255, 0 );
			cv::circle(output, center, radius, color);
		}


	//	cv::threshold( input, output, 128, 255, CV_8U );

	//	cv::Sobel( input, output, CV_8U, 1, 0 );

	//	cv::Laplacian( input, output, CV_8U );

	//	cv::circle( output, toOcv( ci::Vec2f(200, 200) ), 300, toOcv( ci::Color( 0, 0.5f, 1 ) ), -1 );

	//	cv::line( output, cv::Point( 1, 1 ), cv::Point( 30, 30 ), toOcv( ci::Color( 1, 0.5f, 0 ) ) );

		mTexture = ci::gl::Texture( ci::fromOcv( output ) );
	}
}
void HelloWorldApp::draw() {
	ci::gl::clear();
	if( mTexture )
		ci::gl::draw( mTexture );
}

CINDER_APP_BASIC( HelloWorldApp, ci::app::RendererGl )
