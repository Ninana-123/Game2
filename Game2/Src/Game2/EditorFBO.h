#ifndef EDITOR_FBO_H
#define EDITOR_FBO_H

#include <GL/glew.h>

class EditorFBO {
public:
    EditorFBO();
    ~EditorFBO();

    void Initialize(int width, int height);
    void Bind();
    void Unbind();
    GLuint GetTexID() const;
    void Resize(int newWidth, int newHeight);
   

private:
    GLuint fbo;
    GLuint texture;
    int width, height;

    void SetupFBO();
    void SetupTexture();
};

#endif // EDITOR_FBO_H
