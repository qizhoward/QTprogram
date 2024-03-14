#include "OpenGLWidget.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <QtOpenGL>
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置清空颜色为黑色
}
void OpenGLWidget::resizeGL(int w, int h)
{
    // 设置视口
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint VAO;

    // 使用顶点缓冲对象
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,  // 左下角
        0.5f, -0.5f, 0.0f,   // 右下角
        0.0f,  0.5f, 0.0f    // 顶部
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // 绘制三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
/*protected:
    void initializeGL() override {
        initializeOpenGLFunctions();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST); // 启用深度测试

        shaderProgram = new QOpenGLShaderProgram;
        shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                               "#version 330 core\n"
                                               "layout(location = 0) in vec2 position;\n"
                                               "void main() {\n"
                                               "    gl_Position = vec4(position, 0.0, 1.0);\n"
                                               "}\n");
        shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                               "#version 330 core\n"
                                               "out vec4 fragColor;\n"
                                               "void main() {\n"
                                               "    fragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
                                               "}\n");
        shaderProgram->link();
    }

    void resizeGL(int w, int h) override {
        glViewport(0, 0, w, h);
    }

    void paintGL() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram->bind();



        // 绘制坐标轴
        GLfloat vertices[] = {
            // x轴
            -1.0f, 0.0f,
            1.0f, 0.0f,
            // y轴
            0.0f, -1.0f,
            0.0f, 1.0f
        };

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        // 绘制线段
        glDrawArrays(GL_LINES, 0, 4);

        shaderProgram->release();
    }
private:
    QOpenGLShaderProgram *shaderProgram;
};
*/
