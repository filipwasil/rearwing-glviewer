#pragma once

#include <Config.hpp>
#include <ContextConfig.hpp>
#include <Math.hpp>

#include <type_traits>

class GLFWwindow;
class GLFWmonitor;

namespace rwc
{

/*!
 * @class Context
 *
 * @brief This class encapsulates OS dependent window creation process
 *        More specialized Context should inherit from this class and implment the interface
 *
 * @param[in] cfg configuration which keeps the window creation parameters
 *
 */
class Context
{
 public:
  enum class Type
  {
    Offscreen
    , Render
    , Custom
  };

  explicit Context(const ContextConfig& cfg);
  virtual ~Context();

/*!
 * @brief This method runs the render loop. It's supposed to be called in a separate thread, because it runs forever.
 *
 */
  void runRenderLoop();

/*!
 * @brief Change context type. To be used when calling OpenGL based functinalities from non-main thread.
 *
 */
  void setupThreadContext(Type contextType);

/*!
 * @brief Bring focus to selected window context.
 *
 */
  void focusOnContext(Type contextType);

  /*!
* @brief This method stops the render loop. May be called from any thread.
*
*/
  void stopRenderLoop();

/*!
 * @brief This method suppose to be called before entering the rendering loop to preload
 *        the resources consuming large amounts of HW resources could run in separate thread before
 *        rendering the first frame
 *
 */
  void preload();

/*!
 * @brief This method will perform all the draw commands of the current scene graph
 *
 * @param[in] timePassedMs Time passed since last frame rendered
 *
 */
  virtual void onRenderFrame(float timePassedMs) = 0;

/*!
 * @brief This method suppose to be called when there is an event coming to the renderer.
 *
 */
  virtual void onPreloadResources() = 0;

/*!
 * @brief This method suppose to be called when there is an event coming to the renderer.
 *
 */
  virtual void onPreloadSceneGraph() = 0;

/*!
 * @brief Prints out the details of created context
 *
 */
  void log();

/*!
 * @brief Prints out the details of created context
 *
 */
  vec2f getResolution();

/*!
 * @brief Return current GLFW drawing context
 *
 */
  GLFWwindow* getWindow();

 private:
  using OpenGLCallPtr = std::add_pointer_t<void(void)>;
  using OpenGLCallGetProcAddrPtr = std::add_pointer_t<OpenGLCallPtr(const char*)>;

 protected:
  OpenGLCallGetProcAddrPtr mGetProcAddress;

 private:
  void initWindow(GLFWmonitor**, const ContextConfig&);
  void initCallbacks();

  GLFWwindow* mWindow{nullptr};
  GLFWwindow* mBackgroundContext{nullptr};
  vec2f mResolution;
};

} // namespace rwc
