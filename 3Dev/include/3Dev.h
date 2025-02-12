#pragma once
#define NOMINMAX

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <assimp/BaseImporter.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/ai_assert.h>
#include <assimp/texture.h>
#include <assimp/Vertex.h>
#include <assimp/Bitmap.h>

#include <GL/glew.h>

#define NDEBUG
#define GL_CLAMP_TO_EDGE 0x812F

const double pi = 3.141592653;
