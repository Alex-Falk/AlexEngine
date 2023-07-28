//#pragma once
//#include <GL/glew.h>
//
//namespace ae
//{
//	namespace graphics
//	{
//		enum class MeshBuffer : size_t
//		{
//			Vertex = 0,
//			Colour = 1,
//			Texture = 2,
//			Normal = 3,
//			Tangent = 4,
//			Index = 5,
//
//			Max = 6
//		}; 
//
//		class Mesh
//		{
//		public:
//			Mesh();
//			Mesh(const Mesh& rhs);
//			virtual ~Mesh();
//
//			virtual void DrawMesh();
//
//		protected:
//
//			void BufferToMemory();
//
//			GLuint m_array;
//			GLuint m_buffer[static_cast<int>(MeshBuffer::Max)];
//			GLuint m_numVertices;
//			GLuint m_meshType;
//			GLuint m_textureName;
//		};
//	}
//}
