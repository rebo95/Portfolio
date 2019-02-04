#include "IndexMesh.h"
#include <fstream>





IndexMesh::IndexMesh() : Mesh()
{
	numIndices = 0;
	indices = nullptr;
	type = GL_TRIANGLES;
}


IndexMesh::~IndexMesh()
{
	delete[] indices; 
}

void IndexMesh::enable() {
	Mesh::enable();
	if (indices != nullptr) {
		glEnableClientState(GL_INDEX_ARRAY);
		glIndexPointer(GL_UNSIGNED_INT, 0 , indices);
	}
}

void IndexMesh::disable() {
	Mesh::disable();
	glDisableClientState(GL_INDEX_ARRAY);
}

void IndexMesh:: draw() {
	enable();
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, indices);
	disable();
}

IndexMesh* IndexMesh::generateGrid(GLdouble lado, GLuint numDiv) {
	// grid cuadrado de lado*lado, centrado en el plano Y=0,
	// dividido en numDiv*numDiv celdas

	IndexMesh* m = new IndexMesh();
	GLdouble incr = lado / numDiv;
	GLuint numVer = numDiv + 1;

	int c;
	int f;
	GLdouble y = 0; //cuadrícula en plano y = 0;
	GLdouble z = -lado/2;//la cuadríclua situa su vertice 0 en el punto (-lado/2, -lado/2) estando de esta manera centrado en el plano y = 0
	GLdouble x = -lado/2;

	//generador de vértices , aquí es donde realmente generamos la malla que queremos imprimir en pantalla
	m->numVertices = numVer*numVer;
	m->vertices = new glm::dvec3[m->numVertices];

	for (f = 0; f < numVer; f++) { // número de columnas, tantas como vértices hay en una dimensión
		for (c = 0; c < numVer; c++) {
			m->vertices[f * numVer + c] = glm::dvec3(x, y , z);
			x += incr;
		}
		x = -lado / 2;//cada vez que nos movemos en las filas debemos situarnos de nuevo en x = -lado/medios, es decir, situarnos en la primera columna 
		z += incr; // aumentamos en uno el valor que corresponde a nuestras columnas para el vértice y hacemos lo mismo en el bucle que las va recorriendo 
	}

	//generador de índices
	m->numIndices = numDiv*numDiv * 6;
	m->indices = new GLuint[m->numIndices];



	int i = 0;// es el índice que le corresponde a los vertices, su posición y orden correspondiente para crear los triángulos siguiendo el algoritmo de triangle
	int iv = 0; //indice del vertice, vértice iésimo
	int numFilsCels = numDiv; //tantas filas de celdas como divisiones hay por cada dimensión
	int numColsCels = numDiv;

	for (f = 0; f < numFilsCels; f++) {
		for (c = 0; c < numColsCels; c++) {

			iv = f* numVer + c;
			//primer triángulo
			//i se corresponde con el número del índice que le corresponde a cada vértice en el orden de posicionamiento para el pintado de la malla
			//que no corresponde con el índice propiamente dicho de cada uno de los vérices 
			m->indices[i++] = iv;
			m->indices[i++] = iv + numVer;
			m->indices[i++] = iv + 1;

			//segundo triángulo
			m->indices[i++] = iv + 1; 
			m->indices[i++] = iv + numVer;
			m->indices[i++] = iv + numVer + 1;

		}
	}

	return m; //devolvemos la malla	
}
IndexMesh* IndexMesh::generateTerrain(){
	std::ifstream file("..\\Bmps\\terrain.raw",std::ios::binary);
	if (!file.is_open()) return nullptr;
	GLuint nDiv = 256;
	GLdouble lado = nDiv * 8;
	IndexMesh* m = generateGrid(lado, nDiv);
	unsigned char * data = new unsigned char[m->numVertices];
	file.read((char *)data, m->numVertices * sizeof(char));
	file.close();

	for (GLuint i = 0; i < m->numVertices; i++)
	{
		m->vertices[i].y = data[i] * 0.5;
	}

	m->texCoords = new glm::dvec2[m->numVertices];
	int z = 0;
	for (GLfloat i = 0; i < nDiv + 1; i++) {
		for (GLfloat j = 0; j < nDiv + 1; j++) {
			m->texCoords[z++] = glm::dvec2(j/nDiv, i/nDiv);
		}
	}

	delete data;

	glm::dvec3 n;
	GLuint a;
	GLuint b;
	GLuint c;

	m->normals = new glm::dvec3[m->numVertices];

	for (GLuint i = 0; i < m->numVertices; i++)
	{
		m->normals[i].x = 0;
		m->normals[i].y = 0;
		m->normals[i].z = 0;
	}

	for (GLuint i = 0; i < m->numIndices; i+=3) {

		a = m->indices[i];
		b = m->indices[i+1];
		c = m->indices[i+2]; //a, b , c se corresponden con los índices de cada uno de los vértices que componen cada triángulo 

		n = glm::cross(m->vertices[b] - m->vertices[a], m->vertices[c] - m->vertices[a]); // calculamos la normal a cada triángulo

		m->normals[m->indices[i]] += n;
		m->normals[m->indices[i+1]] += n;
		m->normals[m->indices[i+2]] += n; // sumamos a cada normal de los vértices cada normal de tri
	}

	for (GLuint i = 0; i < m->numVertices; i++)
	{
		m->normals[i] = glm::normalize(m->normals[i]); // normalizamos cada una de las normales del vector de normales 
	}

	return m;
}