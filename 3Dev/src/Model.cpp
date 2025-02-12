#include "Model.h"

Model::Model(std::string filename, std::string texture, std::string ID, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float sizeX, float sizeY, float sizeZ) : ID(ID), filename(filename), texture(texture)
{
	SetPosition(x, y, z);
	SetRotation(rotationX, rotationY, rotationZ);
	SetSize(sizeX, sizeY, sizeZ);
	Load(filename, texture);
}

Model::Model(std::string filename, GLuint texture, std::string ID, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float sizeX, float sizeY, float sizeZ) : ID(ID), filename(filename), ModelTexture(texture)
{
	SetPosition(x, y, z);
	SetRotation(rotationX, rotationY, rotationZ);
	SetSize(sizeX, sizeY, sizeZ);
	Load(filename);
}

Model::Model(std::string filename, GLuint texture, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float sizeX, float sizeY, float sizeZ) : filename(filename), ModelTexture(texture)
{
	SetPosition(x, y, z);
	SetRotation(rotationX, rotationY, rotationZ);
	SetSize(sizeX, sizeY, sizeZ);
	Load(filename);
}

Model::Model(std::string filename, std::string texture, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float sizeX, float sizeY, float sizeZ) : filename(filename), texture(texture)
{
	SetPosition(x, y, z);
	SetRotation(rotationX, rotationY, rotationZ);
	SetSize(sizeX, sizeY, sizeZ);
	Load(filename, texture);
}

Model::Model(std::string filename, std::string texture, float x, float y, float z) : filename(filename), texture(texture)
{
	SetPosition(x, y, z);
	SetSize(1, 1, 1);
	Load(filename, texture);
}

Model::Model(std::string filename, GLuint texture, float x, float y, float z) : filename(filename), ModelTexture(texture)
{
	SetPosition(x, y, z);
	SetSize(1, 1, 1);
	Load(filename);
}

Model::Model(std::string filename, float x, float y, float z) : filename(filename)
{
	SetPosition(x, y, z);
	SetSize(1, 1, 1);
	Load(filename);
}

Model::Model() {}

Model::~Model()
{
	delete[] vertexArray;
	delete[] normalArray;
	delete[] uvArray;
}

bool Model::Load(std::string filename, std::string texture)
{
	if(ModelTexture == 0) ModelTexture = (texture == "") ? 0 : LoadTexture(texture);
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return false;
	}
	mesh = scene->mMeshes[0];
	numVerts = mesh->mNumFaces * 3;
	vertexArray = new float[mesh->mNumFaces * 3 * 3];
	normalArray = new float[mesh->mNumFaces * 3 * 3];
	uvArray = new float[mesh->mNumFaces * 3 * 2];
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace& face = mesh->mFaces[i];

		for (int j = 0; j < 3; j++)
		{
			aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
			memcpy(uvArray, &uv, sizeof(float) * 2);
			uvArray += 2;

			aiVector3D normal = mesh->mNormals[face.mIndices[j]];
			memcpy(normalArray, &normal, sizeof(float) * 3);
			normalArray += 3;

			aiVector3D pos = mesh->mVertices[face.mIndices[j]];
			memcpy(vertexArray, &pos, sizeof(float) * 3);
			vertexArray += 3;
		}
	}

	uvArray -= mesh->mNumFaces * 3 * 2;
	normalArray -= mesh->mNumFaces * 3 * 3;
	vertexArray -= mesh->mNumFaces * 3 * 3;
	return true;
}

void Model::Draw()
{
	glPushMatrix();
	
	mat.Activate();
	
	glTranslatef(position.x, position.y, position.z);
	glScalef(size.x, size.y, size.z);
	
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glRotatef(rotation.x, 1, 0, 0);
		
	glBindTexture(GL_TEXTURE_2D, ModelTexture);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertexArray);
	glNormalPointer(GL_FLOAT, 0, normalArray);

	glTexCoordPointer(2, GL_FLOAT, 0, uvArray);

	glDrawArrays(GL_TRIANGLES, 0, numVerts);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();
}

void Model::Draw(GLuint texture)
{
	glPushMatrix();
	
	mat.Activate();
	
	glTranslatef(position.x, position.y, position.z);
	glScalef(size.x, size.y, size.z);
	
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glRotatef(rotation.x, 1, 0, 0);
		
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertexArray);
	glNormalPointer(GL_FLOAT, 0, normalArray);

	glTexCoordPointer(2, GL_FLOAT, 0, uvArray);

	glDrawArrays(GL_TRIANGLES, 0, numVerts);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();
}

void Model::SetPosition(float x, float y, float z)
{
	position = sf::Vector3f(x, y, z);
}

void Model::SetSize(float sizeX, float sizeY, float sizeZ)
{
	size = sf::Vector3f(sizeX, sizeY, sizeZ);
}

void Model::SetRotation(float rotationX, float rotationY, float rotationZ)
{
	rotation = sf::Vector3f(rotationX, rotationY, rotationZ);
}

void Model::SetID(std::string ID)
{
	this->ID = ID;
}

void Model::SetTexture(GLuint texture)
{
	ModelTexture = texture;
}

void Model::SetMaterial(Material mat)
{
	this->mat = mat;
}

void Model::AddPosition(float x, float y, float z) 
{
	position += sf::Vector3f(x, y, z);
}

void Model::AddRotation(float rotationX, float rotationY, float rotationZ) 
{
	rotation += sf::Vector3f(rotationX, rotationY, rotationZ);
}

void Model::AddSize(float sizeX, float sizeY, float sizeZ) 
{
	size += sf::Vector3f(sizeX, sizeY, sizeZ);
}

sf::Vector3f Model::GetPosition() 
{
	return position;
}

sf::Vector3f Model::GetRotation() 
{
	return rotation;
}

sf::Vector3f Model::GetSize() 
{
	return size;
}

std::string Model::GetID() 
{
	return ID;
}

std::string Model::GetFilename() 
{
	return filename;
}

std::string Model::GetTextureFilename() 
{
	return texture;
}

Material Model::GetMaterial()
{
	return mat;
}
