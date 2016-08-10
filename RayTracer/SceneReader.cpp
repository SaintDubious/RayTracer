#include "SceneReader.h"
#include "Scene.h"

#include <fstream>
#include <iostream>

Scene SceneReader::ReadScene( const std::string& FileName )
{
	Scene RetVal;
	std::ifstream str( FileName.c_str() );
	while (!str.eof()) {
		std::string Token;
		float Radius;
		float X, Y, Z;
		str >> Token;
		if (Token == "SPHERE") {
			str >> Radius >> X >> Y >> Z;
			std::cout << Token << " " << Radius << " " << X << "," << Y << "," << Z << "\n";
			RetVal.AddSphere( Sphere( Point( X, Y, Z ), Radius ) );
		}
		else if (Token == "LIGHT") {
			str >> X >> Y >> Z;
			std::cout << Token << " " << X << "," << Y << "," << Z << "\n";
			RetVal.AddLight( Light( Point( X, Y, Z ) ) );
		}
		else {
			throw std::runtime_error( "read unknown token in the scene file" );
		}
	}

	return RetVal;
}
