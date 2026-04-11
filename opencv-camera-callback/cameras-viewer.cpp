#include "window.h"

#include <QApplication>

// Main program
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// Create camera1
	Camera camera1;
	// Create camera2
	Camera camera2;

	// Create the window
	Window window;

	// Show the window
	window.show();

	// Connect the camera1 to the window
	camera1.registerFrameCallback([&](const cv::Mat &m)
								  { window.updateImage1(m); });
	// Connect the camera2 to the window
	camera2.registerFrameCallback([&](const cv::Mat &m)
								  { window.updateImage2(m); });

	// Call the window timerEvent function every 20 ms to refresh the image
	window.startTimer(20);

	OpenCVparameters openCVparameters1;
	openCVparameters1.deviceID = 23;
	openCVparameters1.framerate = 10;
	openCVparameters1.fourcc = cv::VideoWriter::fourcc('G', 'R', 'E', 'Y');
	// 1st camera sensor is v4l-subdev2
	camera1.start(openCVparameters1,
				  {{"/dev/v4l-subdev2", V4L2_CID_GAIN, 0.5},
				   {"/dev/v4l-subdev2", V4L2_CID_HFLIP, 1},
				   {"/dev/v4l-subdev2", V4L2_CID_VFLIP, 1}});

	OpenCVparameters openCVparameters2;
	openCVparameters2.deviceID = 32;
	openCVparameters2.framerate = 10;
	openCVparameters2.fourcc = cv::VideoWriter::fourcc('G', 'R', 'E', 'Y');
	// 2nd camera sensor is v4l-subdev7
	camera2.start(openCVparameters2,
				  {{"/dev/v4l-subdev7", V4L2_CID_GAIN, 0.5},
				   {"/dev/v4l-subdev7", V4L2_CID_HFLIP, 1},
				   {"/dev/v4l-subdev7", V4L2_CID_VFLIP, 1}});

	// Execute the application. This is blocking till the user closes it.
	app.exec();

	camera1.stop();
	camera2.stop();
}
