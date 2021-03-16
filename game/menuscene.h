#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <mvz/scene.h>
#include <mvz/button.h>
#include <mvz/entityempty.h>
#include <mvz/color.h>

class MenuScene : public Scene {

public:
	MenuScene();
	virtual ~MenuScene();
	virtual void update();

private:
	Button* startButton;
	EntityEmpty* rgba;

	void start();
};

#endif 

