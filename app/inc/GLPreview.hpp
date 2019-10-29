#pragma once

#include <Camera.hpp>
#include "../components/backend/Renderer.hpp"
#include "../components/backend/RenderItem.hpp"
#include <rendering/RenderPassStart.hpp>
#include <rendering/RenderPassDefault.hpp>
#include <rendering/RenderPassText.hpp>
#include <GLContext.hpp>
#include <nodes/Icon.hpp>
#include <stack>
#include <Text.hpp>

namespace rwc
{

class Node3D;

class GLPreview : public GLContext
{
 public:
  GLPreview();

  ~GLPreview() override;

  void onRenderFrame(float timePassedMs) override;

  void reload();

 private:
  struct NodeCreationInfo {
    std::string pathVertexShader;
    std::string pathFragmentShader;
    std::string pathGeometryShader;
    std::string pathTesselationControlShader;
    std::string pathTesselationEvaluationShader;
    std::string pathComputeShader;
    std::vector<std::string> textures;
    std::string model;
  };

  struct TextCreationInfo {
    NodeCreationInfo nodeCreationInfo;
    Text::Format format;
  };
  void onEvent(std::string event);

  Renderer<RenderItem, RenderPassStart, RenderPassDefault, RenderPassText> mRenderer{};

  std::vector<NodeCreationInfo> mNodesCreationInfo;
  std::vector<TextCreationInfo> mTextsCreationInfo;

  std::vector<std::unique_ptr<Node3D>> mNodes;
  std::vector<std::unique_ptr<Node3D>> mTexts;

  glm::mat4 mCameraViewProjectionMatrix;
};

} // namespace rwc
