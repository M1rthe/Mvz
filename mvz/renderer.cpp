#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

//#include <mvz/shittycamera.h>
#include <mvz/renderer.h>

Renderer::Renderer(unsigned int w, unsigned int h) {

	window_width = w;
	window_height = h;

	this->init();
}

Renderer::~Renderer() {

	//Cleanup VBO and shader
	glDeleteProgram(programID);
}

int Renderer::init() {

	//Initialise GLFW
	if(!glfwInit()) {
		fprintf (stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//Open a window and create its OpenGL context
	_window = glfwCreateWindow(window_width, window_height, "Game", NULL, NULL);
	if (_window == NULL) {
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);

	//Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	//Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	//White background
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	//Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	//Create and compile our GLSL program from the shaders
	programID = this->loadShaders("shaders/sprite.vert", "shaders/sprite.frag");

	// Use our shader
	glUseProgram(programID);

	return 0;
}

float Renderer::updateDeltaTime() {

	// lastTime is initialised only the first time this function is called
	static double lastTime = glfwGetTime();

	// get the current time
	double currentTime = glfwGetTime();

	// Compute time difference between current and last time
	float deltaTime = float(currentTime - lastTime);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	return deltaTime;
}

void Renderer::renderSprite(glm::mat4 modelMatrix, Sprite * sprite) {

	//Send our transformation to the currently bound shader,
	//In the "MVP" uniform
	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	GLuint matrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	//Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->texture());
	//Set our "textureSampler" sampler to user Texture Unit 0
	GLuint textureID  = glGetUniformLocation(programID, "textureSampler");
	glUniform1i(textureID, 0);

	//1st attribute buffer: vertices
	GLuint vertexPositionID = glGetAttribLocation(programID, "vertexPosition");
	glEnableVertexAttribArray(vertexPositionID);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->vertexbuffer());
	glVertexAttribPointer(
		vertexPositionID,	//The attribute we want to configure
		3,					//Size: x+y+z => 3
		GL_FLOAT,			//Type
		GL_FALSE,			//Normalized?
		0,					//Stride
		(void*)0			//Array buffer offset
	);

	//2nd attribute buffer: UVs
	GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->uvbuffer());
	glVertexAttribPointer(
		vertexUVID, // The attribute we want to configure
		2,          // size : U+V => 2
		GL_FLOAT,   // type
		GL_FALSE,   // normalized?
		0,          // stride
		(void*)0    // array buffer offset
	);

	// Draw the triangles
	glDrawArrays(GL_TRIANGLES, 0, 2*3); //2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(vertexPositionID);
	glDisableVertexAttribArray(vertexUVID);
}

void Renderer::renderScene(Scene * scene) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->viewMatrix = scene->camera->viewMatrix;
	this->projectionMatrix = scene->camera->projectionMatrix;

	renderEntity(glm::mat4(1.0f), scene);

	glfwSwapBuffers(_window);
}

void Renderer::renderEntity(glm::mat4 modelMatrix, Entity * entity) {

	//Build the Model matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(entity->position.x, entity->position.y, entity->position.z));
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(entity->rotation.x, entity->rotation.y, entity->rotation.z);
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(entity->scale.x, entity->scale.y, entity->scale.z));

	glm::mat4 mm = translationMatrix * rotationMatrix * scalingMatrix;

	modelMatrix *= mm;

	//Check for Sprites to see if we need to render anything
	Sprite* sprite = entity->sprite;
	if (sprite != nullptr) {
		//Render the Sprite. Just use the model matrix for the entity since this is a single sprite.
		renderSprite(modelMatrix, sprite); 
	}

	//Render all Children (recursively)
	std::vector<Entity*> children = entity->children;
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->renderEntity(modelMatrix, *child);
	}
}

GLuint Renderer::loadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path) {

	//Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertex_file_path.c_str(), std::ios::in);
	if (vertexShaderStream.is_open()){
		std::string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	} else {
		printf("Can't to open %s.\n", vertex_file_path.c_str());
		//getchar();
		return 0;
	}

	//Read the Fragment Shader code from the file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragment_file_path.c_str(), std::ios::in);
	if (fragmentShaderStream.is_open()) {
		std::string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	} else {
		printf("Can't to open %s.\n", fragment_file_path.c_str());
		//getchar();
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	//Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path.c_str());
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer , NULL);
	glCompileShader(vertexShaderID);

	//Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ) {
		std::vector<char> vertexShaderErrorMessage(infoLogLength+1.0);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	//Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path.c_str());
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderID);

	//Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> fragmentShaderErrorMessage(infoLogLength+1.0);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	//Link the program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	//Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ) {
		std::vector<char> programErrorMessage(infoLogLength+1.0);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}
