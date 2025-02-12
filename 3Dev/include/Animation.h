#pragma once
#include <Model.h>

class Animation
{
public:
	enum State
	{
		Playing,
		Paused,
		Stopped
	};
	
	Animation(std::string filename, std::string texture, int frames, float speed, std::string ID, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
	Animation(std::string filename, GLuint texture, int frames, float speed, std::string ID, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
	Animation(std::string filename, std::string texture, int frames, float speed);
	Animation(std::string filename, GLuint texture, int frames, float speed);
	Animation();
	~Animation();
	
	void Load(std::string filename, std::string texture, int frames);
	void Load(std::string filename, int frames);
	
	void DrawAnimation(float time);
	void DrawFrame(int frame);
	
	void Restart();
	void Stop();
	void Pause();
	void Play();
	
	void SetPosition(float x, float y, float z);
	void SetSize(float sizeX, float sizeY, float sizeZ);
	void SetRotation(float rotationX, float rotationY, float rotationZ);
	void SetID(std::string ID);
	void SetLoop(bool loop);
	void SetSpeed(float speed);
	void SetTexture(GLuint texture);
	void SetMaterial(Material mat);
	
	void AddPosition(float x, float y, float z);
	void AddSize(float sizeX, float sizeY, float sizeZ);
	void AddRotation(float rotationX, float rotationY, float rotationZ);
	
	sf::Vector3f GetPosition();
	sf::Vector3f GetRotation();
	sf::Vector3f GetSize();
	
	std::string GetID();
	std::string GetFilename();
	std::string GetTextureFilename();
	
	int GetFrames();
	int GetCurrentFrame();

	float GetSpeed();
	
	State GetState();
	
	Material GetMaterial();
private:
	Material mat;
	
	sf::Vector3f position, rotation, size;

	int frames;

	std::string ID, filename, texture;

	Model* m;
	
	float current_frame = 1;
	float speed;
	
	GLuint animationTexture = 0;
	
	State state = Playing;
	
	bool loop = true;
};

