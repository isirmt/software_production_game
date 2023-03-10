#pragma once
#include <GL/glut.h>

#include "PositionVector.hpp"

namespace Scene {
class Camera {
 public:
  Camera() {}
  ~Camera() {}

  inline static void SetActive(bool _isActive = true) { isActive = _isActive; }

  inline static void SetAsPerspective(float _wph, float _fov, float _near, float _far,
                               PosVec _pos = PosVec(),
                               PosVec _lookAt = PosVec(),
                               PosVec _vec = PosVec()) {
    wph = _wph;
    fov = _fov;
    near = _near;
    far = _far;
    r = _pos;
    lookAt = _lookAt;
    vec = _vec;
    isPerspective = true;
    UpdateCamera();
  }
  inline static void SetAsOrtho(PosVec _from, PosVec _to) {
    from = _from;
    to = _to;
    isPerspective = false;
  }
  // for perspective
  inline static void SetCameraPos(PosVec _pos) {
    r = _pos;
    UpdateCamera();
  }
  // for perspective
  inline static void SetCameraLookAt(PosVec _lookAt) {
    lookAt = _lookAt;
    UpdateCamera();
  }
  // for perspective
  inline static void SetCameraVec(PosVec _vec) {
    vec = _vec;
    UpdateCamera();
  }

  inline static void SetPerspectiveMode(bool _isPerspective) {
    isPerspective = _isPerspective;
  }

  inline static void UpdateCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (isPerspective) {
      gluPerspective(fov, wph, near, far);
      gluLookAt(r.x, r.y, r.z, lookAt.x, lookAt.y, lookAt.z, vec.x, vec.y,
                vec.z);
    } else {
      glOrtho(from.x, to.x, from.y, to.y, from.z, to.z);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

 private:
  static bool isActive;

  static bool isPerspective;
  // perspective
  static float fov;
  static float wph;
  static float near, far;
  static PosVec r;
  static PosVec lookAt;
  static PosVec vec;
  // ortho
  static PosVec from, to;
};

}  // namespace Scene