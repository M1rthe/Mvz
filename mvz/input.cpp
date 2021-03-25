#include <mvz/input.h>
#include <iostream>

Input::Input() {

	window = nullptr;

	windowWidth = 0;
	windowHeight = 0;

	mouseX = 0;
	mouseY = 0;

	for (unsigned int i = 0; i < GLFW_KEY_LAST; i++) {
		keys[i] = false;
		keysDown[i] = false;
		keysUp[i] = false;
	}

	for (unsigned int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
		mouse[i] = false;
		mouseDown[i] = false;
		mouseUp[i] = false;
	}
}

Input::~Input() {

}

void Input::updateInput(GLFWwindow* w) {
	
	window = w;

	glfwPollEvents();

	for (unsigned int i = 32; i < 97; i++) {
		handleKey(i);
	}

	for (unsigned int i = 255; i < GLFW_KEY_LAST; i++) {
		handleKey(i);
	}

	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glfwGetCursorPos(window, &mouseX, &mouseY);

	mouseX = ((float)globals.windowWidth / windowWidth) * mouseX;
	mouseY = ((float)globals.windowHeight / windowHeight) * mouseY;

	for (unsigned int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
		handleMouse(i);
	}
}

void Input::handleMouse(unsigned int button) {

	if (glfwGetMouseButton(window, button) == GLFW_PRESS) {
		if (mouse[button] == false) {
			mouse[button] = true;
			mouseDown[button] = true;
			mouseUp[button] = false;
		}
		else {
			mouseDown[button] = false;
		}
	}
	if (glfwGetMouseButton(window, button) == GLFW_RELEASE) {
		if (mouse[button] == true) {
			mouse[button] = false;
			mouseUp[button] = true;
			mouseDown[button] = false;
		}
		else {
			mouseUp[button] = false;
		}
	}
}

void Input::handleKey(unsigned int key) {
	
	if (glfwGetKey(window, key) == GLFW_PRESS) {
		if (keys[key] == false) {
			keys[key] = true;
			keysDown[key] = true;
		}
		else {
			keysDown[key] = false;
		}
	}
	if (glfwGetKey(window, key) == GLFW_RELEASE) {
		if (keys[key] == true) {
			keys[key] = false;
			keysUp[key] = true;
		}
		else {
			keysUp[key] = false;
		}
	}
}