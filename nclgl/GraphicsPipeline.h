#pragma once
#include <nclgl/OGLRenderer.h>
#include <nclgl/TSingleton.h>
#include <nclgl/Camera.h>
#include <nclgl/RenderNode.h>
#include <functional>


#define SHADOWMAP_NUM 4
#define SHADOWMAP_SIZE 4096

#define PROJ_FAR      50.0f			//Can see for 50m - setting this too far really hurts shadow quality as they attempt to cover the entirety of the view frustum

#define PROJ_NEAR     0.1f			//Nearest object @ 10cm
#define PROJ_FOV      45.0f			//45 degree field of view

using TransparentPair = std::pair<RenderNode*, float>;


class GraphicsPipeline : public TSingleton<GraphicsPipeline>, OGLRenderer
{
	friend class TSingleton<GraphicsPipeline>;

public:
	//Set all defaults
	// - Called each time a scene is swapped in/reset, so should reset camera position etc
	void InitializeDefaults();

	//Add/Remove Render objects to renderable object lists
	void AddRenderNode(RenderNode* node);
	void RemoveRenderNode(RenderNode* node);


	//Called by main game loop
	// - Naming convention from oglrenderer
	void UpdateScene(float dt) override;
	void RenderScene() override;


	//Utils
	Camera* GetCamera() { return camera; }
	bool GetVsyncEnabled() const { return isVsyncEnabled; }

	void SetVsyncEnabled(bool enabled)
	{
		wglSwapIntervalEXT((isVsyncEnabled = enabled) ? 1 : 0);
	}

	Maths::Matrix4& GetProjMtx() { return projMatrix; }
	Maths::Matrix4& GetViewMtx() { return viewMatrix; }

	Maths::Matrix4& GetShadowViewMtx() { return shadowViewMtx; }
	Maths::Matrix4* GetShadowProjMatrices() { return shadowProj; }
	Maths::Matrix4* GetShadowProjViewMatrices() { return shadowProjView; }

	Vector3& GetAmbientColor() { return ambientColor; }
	Vector3& GetLightDirection() { return lightDirection; }
	float& GetSpecularFactor() { return specularFactor; }
	GLuint& GetShadowTex() { return shadowTex; }

protected:
	GraphicsPipeline();
	~GraphicsPipeline() override;

	void Resize(int x, int y) override; //Called by window when it is resized

	void LoadShaders();
	void UpdateAssets(int width, int height);
	void BuildAndSortRenderLists();
	void RecursiveAddToRenderLists(RenderNode* node);
	void RenderAllObjects(bool isShadowPass, std::function<void(RenderNode*)> perObjectFunc = nullptr);
	void BuildShadowTransforms(); //Builds the shadow projView matrices

protected:
	Maths::Matrix4 projViewMatrix;

	//Render FBO
	GLuint screenTexWidth, screenTexHeight;
	GLuint screenFBO;
	GLuint screenTexColor;
	GLuint screenTexDepth;

	//Shaders
	Shader* shaderPresentToWindow;
	Shader* shaderShadow;
	Shader* shaderForwardLighting;

	//Render Params
	Vector3 ambientColor;
	float gammaCorrection;
	//Monitor Default: 1.0 / 2.2 (Where 2.2 here is the gamma of the monitor which we need to invert before doing lighting calculations)		
	Vector3 lightDirection;
	Vector3 backgroundColor;
	float specularFactor;
	uint16_t numSuperSamples;


	//Shadowmaps
	float sceneBoundingRadius; ///Approx based on scene contents
	GLuint shadowFBO;
	GLuint shadowTex;
	Maths::Matrix4 shadowProj[SHADOWMAP_NUM];
	Maths::Matrix4 shadowViewMtx;
	Maths::Matrix4 shadowProjView[SHADOWMAP_NUM];
	float normalizedFarPlanes[SHADOWMAP_NUM - 1];

	//Common
	Mesh* fullscreenQuad;
	Camera* camera;
	bool isVsyncEnabled;
	std::vector<RenderNode*> allNodes;

	std::vector<RenderNode*> renderlistOpaque;
	std::vector<TransparentPair> renderlistTransparent;
	//Also stores cameraDist in the second argument for sorting purposes
};
