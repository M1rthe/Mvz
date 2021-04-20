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
	SceneManager(std::map<std::string, Scene*> scenesP, std::string current);
	virtual ~SceneManager();

	void run(Renderer renderer);

	static void switchScene(std::string scene);
	static std::string currentScene;
	static std::map<std::string, Scene*> scenes;

private:
};

#endif