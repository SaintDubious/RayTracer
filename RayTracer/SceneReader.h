#ifndef INCLUDE_SCENE_READER
#define INCLUDE_SCENE_READER

#include <string>

class Scene;

class SceneReader
{
public:
	static Scene ReadScene( const std::string& FileName );

private:
};

#endif