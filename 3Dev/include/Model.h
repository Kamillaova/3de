#pragma once
#include "Texture.h"
#include "Material.h"

class Model
{
public:
	int numVerts;
	float* vertexArray;
		
	Model(std::string filename, std::string texture, std::string ID, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float sizeX, float sizeY, float sizeZ);
	Model(std::string filename, GLuint texture, std::string ID, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float sizeX, float sizeY, float sizeZ);
	Model(std::string filename, GLuint texture, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float sizeX, float sizeY, float sizeZ);
	Model(std::string filename, std::string texture, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float sizeX, float sizeY, float sizeZ);
	Model(std::string filename, std::string texture, float x, float y, float z);
	Model(std::string filename, GLuint texture, float x, float y, float z);
	Model(std::string filename, float x, float y, float z);
	
	Model();
	~Model();

	bool Load(std::string filename, std::string texture = "");

	void Draw();
	void Draw(GLuint texture);
	
	void SetPosition(float x, float y, float z);
	void SetSize(float sizeX, float sizeY, float sizeZ);
	void SetRotation(float rotationX, float rotationY, float rotationZ);
	void SetID(std::string ID);
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
	
	Material GetMaterial();
private:
	Material mat;
	
	std::string ID, filename, texture;

	sf::Vector3f position, rotation, size;

	float* normalArray;
	float* uvArray;

	GLuint ModelTexture = 0;
	
	aiMesh* mesh;
};

