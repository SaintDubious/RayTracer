#include "Camera.h"
#include "Bitmap.h"
#include "Scene.h"
#include "SceneReader.h"

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Starting\n";
	try {
		Scene MainScene = SceneReader::ReadScene( "./Busy.txt" );
		Camera MainCamera;
		Bitmap OuputBmp( 600, 600 );
		MainCamera.CapturePhoto( MainScene, OuputBmp );
		OuputBmp.DumpToFile( "Output.bmp" );
		std::cout << "All Done\n";
		return 0;
	}
	catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << "\n";
	}
	catch (...) {
		std::cout << "Caught exception\n";
	}
	return 1;
}