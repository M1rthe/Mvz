#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

//#include <mvz/scene.h>
#include <vector>
#include <map>
#include <mvz/renderer.h>
#include <mvz/shittycamera.h>
#include <mvz/globals.h>

class SceneManager {

public:
	SceneManager(std::map<std::string, Scene*> scenesP);
	virtual ~SceneManager();

	void run(Renderer renderer);

private:
	std::map<std::string, Scene*> scenes;
};

#endif