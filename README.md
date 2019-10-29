# Rearwing - GL viewer

Rearwing meant to be an OpenSource API agnostic (OpenGL/Vulkan) data oriented rendering engine with shallow framework layer.

-- Features
- binary shader loading and generation
- fonts shaders and generation
- Vulkan/OpenGL abstraction for resources loading and management
- OpenGL ES backends
- Simple and efficient, based on static polymorphism 
- Unique pointer based (one node can only have one owner - its parent) scenegraph abstraction (Camera/Scene/Node/Text)

-- Backends
- OpenGL - ready
- OpenGl ES - ready
- Vulkan - todo

-- External tools and libraries:
- TinyObjLoader
- Catch
- Trompeloeil
- Cxxopts
- Spimpl
- Freetype
- FontLoader (Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.)

-- This project code is under MIT License, however please mind the dependencies above, because they affect the
 effective license of the code as a whole.

Have fun playing with *Rearwing*
