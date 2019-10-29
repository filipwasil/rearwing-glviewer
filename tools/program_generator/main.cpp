#include "OffscreenContext.hpp"
#include "../Paths.hpp"

int main(int /*argc*/, char* /*argv*/[])
{

  rwc::OffscreenContext context;

  const std::string path = createGeneratedDirectory("programs/");

  const char* prefix = "../../../app/assets/shaders/";

  context.generateProgramBinary("Textured.frag", "Basic.vert", "Textured.bin", prefix, path.c_str());
  context.generateProgramBinary("NonTextured.frag", "Basic.vert", "NonTextured.bin", prefix, path.c_str());
  context.generateProgramBinary("Text.frag", "Text.vert", "Text.bin", prefix, path.c_str());
  context.generateProgramBinary("Background.frag", "Background.vert", "Background.bin", prefix, path.c_str());
  context.generateProgramBinary("BackgroundGrass.frag", "Background.vert", "BackgroundGrass.bin", prefix, path.c_str());
  context.generateProgramBinary("BackgroundGround.frag", "Background.vert", "BackgroundGround.bin", prefix, path.c_str());
  context.generateProgramBinary("BackgroundGlow.frag", "Background.vert", "BackgroundGlow.bin", prefix, path.c_str());
  context.generateProgramBinary("Textured.frag", "Basic.vert", "Digits.bin", prefix, path.c_str());
  context.generateProgramBinary("TextureColored.frag", "BasicNoNormals.vert", "Plane.bin", prefix, path.c_str());
  context.generateProgramBinary("TextureColoredFadeOut.frag", "BasicNoNormalsDepth.vert", "PlaneFadeOut.bin", prefix,path.c_str());
  return 0;
}
