#pragma once
#include "Mesh.h"
class IndexMesh :
	public Mesh
{
public:
	IndexMesh();
	~IndexMesh();
	virtual void draw();

protected:
	GLuint* indices; 
	GLuint numIndices = 0;
	virtual void enable();
	virtual void disable();
	static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv);

public :
	static IndexMesh* generateTerrain();
};

