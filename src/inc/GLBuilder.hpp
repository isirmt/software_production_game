#pragma once
#include <GL/gl.h>
#include <GL/glut.h>

namespace GLSYS {
class GLBuilder {
 public:
  static void GLSetup();
  static void LightSetup();
};
}  // namespace GLSYS