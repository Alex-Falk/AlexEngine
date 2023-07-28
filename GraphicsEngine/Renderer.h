//#pragma once
//#include <vector>
//
//#include "Engine/Interfaces/IUpdatable.h"
//#include "Utils/ISingleton.h"
//#include "Utils/Matrix4.h"
//
//class RenderNode;
//
//namespace ae
//{
//	namespace graphics
//	{
//		class Renderer : public ISingleton<Renderer>, IUpdatable
//		{
//		public:
//			void OnUpdate(float dt) override;
//			void Render();
//
//		protected:
//			Renderer();
//			~Renderer() override;
//
//			void LoadShaders();
//
//
//			Maths::Matrix4 m_projectionMatrix;
//			Maths::Matrix4 m_modelMatrix;
//			Maths::Matrix4 m_viewMatrix;
//			Maths::Matrix4 m_textureMatrix;
//
//			std::vector<RenderNode*> m_renderNodes;
//
//
//
//		};
//	}
//}
