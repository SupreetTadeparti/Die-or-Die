#include "Models.hpp"

namespace Moon
{
	Model* Models::Rect(const String& name, Float width, Float height)
	{
		Float data[] = {
			// Positions
		   -width / 2, -height / 2,
			width / 2, -height / 2,
			width / 2,  height / 2,
		   -width / 2,  height / 2,

		    // Texture Coordinates
		    0, 0,
		    1, 0,
		    1, 1,
		    0, 1
		};

		Uint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		Buffer* buffer = new Buffer(data, 16);

		IndexBuffer* ibo = new IndexBuffer(indices, 6);

		VertexBuffer* vbo = new VertexBuffer(0, 2, 0, 0, buffer);
		VertexBuffer* tvbo = new VertexBuffer(1, 2, 0, 8 * sizeof(Float), buffer);

		VertexArray* vao = new VertexArray();

		vao->AddVBO(vbo);
		vao->AddVBO(tvbo);

		vao->SetIBO(ibo);

		return new Model(name, vao);
	}

	Model* Models::Rect(const String& name, Material* material, Float width, Float height)
	{
		Model* model = Rect(name, width, height);
		model->SetMaterial(material);
		return model;
	}

	Model* Models::Rect(const String& name, Shader* shader, Float width, Float height)
	{
		Model* model = Rect(name, width, height);
		model->SetShader(shader);
		return model;
	}

	Model* Models::Rect(const String& name, Shader* shader, Material* material, Float width, Float height)
	{
		Model* model = Rect(name, shader, width, height);
		model->SetMaterial(material);
		return model;
	}

	Model* Models::Box(const String& name, Float width, Float length, Float height)
	{
		Float data[] = {
			// Back
			-width / 2,  height / 2, -length / 2,
			-width / 2, -height / 2, -length / 2,
			 width / 2, -height / 2, -length / 2,
			 width / 2,  height / 2, -length / 2,

			// Front
			-width / 2,  height / 2,  length / 2,
			-width / 2, -height / 2,  length / 2,
			 width / 2, -height / 2,  length / 2,
			 width / 2,  height / 2,  length / 2,

			// Right
			 width / 2,  height / 2, -length / 2,
			 width / 2, -height / 2, -length / 2,
			 width / 2, -height / 2,  length / 2,
			 width / 2,  height / 2,  length / 2,

			// Left
			-width / 2,  height / 2, -length / 2,
			-width / 2, -height / 2, -length / 2,
			-width / 2, -height / 2,  length / 2,
			-width / 2,  height / 2,  length / 2,

		    // Top
			-width / 2, height / 2,   length / 2,
			-width / 2, height / 2,  -length / 2,
			 width / 2, height / 2,  -length / 2,
			 width / 2, height / 2,   length / 2,

			// Bottom
			-width / 2, -height / 2,  length / 2,
			-width / 2, -height / 2, -length / 2,
			 width / 2, -height / 2, -length / 2,
			 width / 2, -height / 2,  length / 2,

			0, 1, 0, 0, 1, 0, 1, 1,
			1, 1, 1, 0, 0, 0, 0, 1,
			0, 1, 0, 0, 1, 0, 1, 1,
			1, 1, 1, 0, 0, 0, 0, 1,
			1, 0, 1, 1, 0, 1, 0, 0,
			1, 1, 1, 0, 0, 0, 0, 1,
		};

		Uint indices[] = {
			0,  1,  3,
			3,  1,  2,
			4,  5,  7,
			7,  5,  6,
			8,  9,  11,
			11, 9,  10,
			12, 13, 15,
			15, 13, 14,
			16, 17, 19,
			19, 17, 18,
			20, 21, 23,
			23, 21, 22
		};

		Buffer* buffer = new Buffer(data, 120);

		IndexBuffer* ibo = new IndexBuffer(indices, 36);

		VertexBuffer* vbo = new VertexBuffer(0, 3, 0, 0, buffer);
		VertexBuffer* tvbo = new VertexBuffer(1, 2, 0, 72 * sizeof(Float), buffer);

		VertexArray* vao = new VertexArray();

		vao->AddVBO(vbo);
		vao->AddVBO(tvbo);

		vao->SetIBO(ibo);

		return new Model(name, vao);
	}

	Model* Models::Box(const String& name, Material* material, Float width, Float length, Float height)
	{
		Model* model = Box(name, width, length, height);
		model->SetMaterial(material);
		return model;
	}
	
	Model* Models::Box(const String& name, Shader* shader, Float width, Float length, Float height)
	{
		Model* model = Box(name, width, length, height);
		model->SetShader(shader);
		return model;
	}

	Model* Models::Box(const String& name, Shader* shader, Material* material, Float width, Float length, Float height)
	{
		Model* model = Box(name, shader, width, length, height);
		model->SetMaterial(material);
		return model;
	}
}