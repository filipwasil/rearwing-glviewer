#include <GLPreview.hpp>

#include <Camera.hpp>
#include <RenderItemFactory.hpp>
#include <Strings.hpp>
#include <Math.hpp>
#include <nodes/TextNode.hpp>
#include <Logger.hpp>
#include <GLFW/glfw3.h>

constexpr rwc::vec4f COLOR_WHITE{1.0, 1.0, 1.0};
constexpr rwc::vec4f COLOR_RED{0.992, 0.486, 0.431};

namespace rwc
{

GLPreview* ptr;

GLPreview::GLPreview()
  : GLContext{}
  , mRenderer{}
  , mCameraViewProjectionMatrix{Camera(glm::vec3(0.0f, 0.0f, 1.0f), getResolution()).getViewProjection()}
{
  ptr = this;
  glfwSetMouseButtonCallback(getWindow(), [](GLFWwindow* window, int button, int action, int /*mods*/) {
    if (!glfwWindowShouldClose(window)) {
      if (GLFW_MOUSE_BUTTON_LEFT == button && GLFW_RELEASE == action)
      {
        double x{0.0};
        double y{0.0};
        glfwGetCursorPos(window, &x, &y);
//        const auto normalizedXPosition = x / static_cast<double>(ptr->getResolution()[0]);
//        const auto normalizedYPosition = y / static_cast<double>(ptr->getResolution()[1]);
      }
    }});

  mNodesCreationInfo.push_back( NodeCreationInfo {
    "shaders/BasicNoNormalsDepth.vert"
    , "shaders/TextureColoredFadeOut.frag"
    , ""
    , ""
    , ""
    , ""
    , std::vector<std::string>( { "models/button.png" } )
    , "" }
  );

  mTextsCreationInfo.push_back( TextCreationInfo {
                                  NodeCreationInfo {
                                    "shaders/BasicNoNormalsDepth.vert"
                                    , "shaders/TextFadeOut.frag"
                                    , ""
                                    , ""
                                    , ""
                                    , ""
                                    , std::vector<std::string>( { "models/button.png" } )
                                    , "" }
                                  , Text::Format{
                                    {0.0, 0.12, 0.0}
                                    , 170.0f
                                    , "fonts/FreeSerifBold.meta"
                                    , "fonts/FreeSerifBold.png"
                                    , {Text::AlignmentHorizontal::center, Text::AlignmentVertical::bottom}}
                                }
  );
  reload();
}

GLPreview::~GLPreview()
{
  ptr = nullptr;
}

void GLPreview::reload()
{
  for (const auto& node : mNodesCreationInfo)
  {
    auto vp = mCameraViewProjectionMatrix;

    mNodes.push_back(
      std::make_unique<Plane3D>(
        mCameraViewProjectionMatrix
        , glm::scale(glm::mat4(1.0), glm::vec3(0.3, 0.1, 0.1))
        , node.pathVertexShader.c_str()
        , node.pathFragmentShader.c_str()
        , node.textures.empty() ? "0_0_0.color" : node.textures[0].c_str()));

    mNodes.back()->getRenderItem().useProgramObject().pushUniform("uColor", COLOR_WHITE);

    mRenderer.addToRenderingPipeline<RenderPassDefault>(mNodes.back()->getRenderItem());

    mNodes.back()->onChildrenCallback([vp](Node3D& n)
                                      {
                                        n.getRenderItem().useProgramObject().pushUniform("uMVP", vp * n.getCurrentTransformation());
                                      });
  }

  for (const auto& text : mTextsCreationInfo)
  {
    mTexts.push_back(std::make_unique<TextNode>(
      mCameraViewProjectionMatrix
      , "Test"
      , text.format
      , text.nodeCreationInfo.pathVertexShader.c_str()
      , text.nodeCreationInfo.pathFragmentShader.c_str()
    ) );
    mRenderer.addToRenderingPipeline<RenderPassText>(mTexts.back()->getRenderItem());
  }
}

void GLPreview::onRenderFrame(float timePassedMs)
{
  auto vp = mCameraViewProjectionMatrix;

  for (const auto& entry : mTexts)
  {
    entry->onTimePassed(timePassedMs);
    entry->updateTransformations();
    entry->onChildrenCallback([vp](Node3D& node)
                              {
                                node.getRenderItem().useProgramObject().pushUniform("uMVP", vp * node.getCurrentTransformation());
                              });
  }

  for (const auto& entry : mNodes)
  {
    entry->onTimePassed(timePassedMs);
    entry->updateTransformations();
    entry->onChildrenCallback([vp](Node3D& node)
                              {
                                node.getRenderItem().useProgramObject().pushUniform("uMVP", vp * node.getCurrentTransformation());
                              });
  }

  mRenderer.render();
}

} // namespace rwc
