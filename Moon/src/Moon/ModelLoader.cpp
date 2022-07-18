#include "ModelLoader.hpp"

namespace Moon
{
	Model* ModelLoader::LoadModel(const String& name, Shader* shader, Material* material, const String& file)
	{
		VertexData Data = LoadOBJ(file);

		Buffer* pbo = new Buffer(&Data.Positions[0], (Uint)Data.Positions.size());
		Buffer* tbo = new Buffer(&Data.TextureCoordinates[0], (Uint)Data.TextureCoordinates.size());
		Buffer* nbo = new Buffer(&Data.Normals[0], (Uint)Data.Normals.size());
		IndexBuffer* ibo = new IndexBuffer(&Data.Indices[0], (Uint)Data.Indices.size());

		VertexBuffer* pvbo = new VertexBuffer(0, 3, 0, 0, pbo);
		VertexBuffer* tvbo = new VertexBuffer(1, 2, 0, 0, tbo);
		VertexBuffer* nvbo = new VertexBuffer(2, 3, 0, 0, nbo);

		VertexArray* vao = new VertexArray();
		vao->SetIBO(ibo);
		vao->AddVBO(pvbo);
		vao->AddVBO(tvbo);
		vao->AddVBO(nvbo);

		return new Model(name, shader, vao, material);
	}

	List<String> ModelLoader::SplitString(const String& string, Char delimeter)
	{
		List<String> res;
		String curr;
		for (Char c : string)
		{
			if (c == delimeter)
			{
				res.push_back(curr);
				curr = "";
			}
			else curr += c;
		}
		if (curr.size() != 0) res.push_back(curr);
		return res;
	}

	VertexData ModelLoader::LoadOBJ(const String& path)
	{
		std::ifstream objfile("./src/models/" + path);

		String line;

		List<Vec2> t;
		List<Vec3> n;

		List<Float> positions;
		List<Float> textureCoords;
		List<Float> normals;
		List<Uint> indices;

		while (std::getline(objfile, line))
		{
			List<String> split = SplitString(line, ' ');

			if (line.rfind("v ", 0) == 0)
			{
				positions.push_back(std::stof(split[1]));
				positions.push_back(std::stof(split[2]));
				positions.push_back(std::stof(split[3]));
			}
			
			if (line.rfind("vt ", 0) == 0)
			{
				t.push_back(Vec2(std::stof(split[1]), std::stof(split[2])));
			}

			if (line.rfind("vn ", 0) == 0)
			{
				n.push_back(Vec3(std::stof(split[1]), std::stof(split[2]), std::stof(split[3])));
			}

			if (line.rfind("f ", 0) == 0)
			{
				for (Uint i = 1; i < split.size(); i++)
				{
					List<String> vertex = SplitString(split[i], '/');
					indices.push_back(std::stoi(vertex[0]) - 1);
					Int64 tci = std::stoi(vertex[1]);
					Vec2 tc = t[tci - 1];
					textureCoords.push_back(tc.x);
					textureCoords.push_back(tc.y);
					Int64 noi = std::stoi(vertex[2]);
					Vec3 no = n[noi - 1];
					normals.push_back(no.x);
					normals.push_back(no.y);
					normals.push_back(no.z);
				}
			}
		}

		objfile.close();
	
		return VertexData { positions, textureCoords, normals, indices };
	}
}