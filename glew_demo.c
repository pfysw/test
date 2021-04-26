#include <glib.h>
#include <gtk/gtk.h>

#include "GL/glew.h"
#include <stdio.h>

static GtkWidget *window;

FILE *fp;

// Shaders 以定义字符串的方式给出
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


//main函数调用，定义成全局形式
GLuint VAO, VBO;/*声明VAO,VBO*/
GLuint vertexShader, fragmentShader, shaderProgram;/*声明着色器对象和着色器程序对象*/

void slog_init()
{
    fp = fopen("log.txt", "a+");
    if(NULL == fp){
        printf("log_init failed.");
    }
}

void slog(char * fmt,...)
{
    va_list  ap;

    if( NULL != fp){
        va_start(ap, fmt);
        vfprintf(fp, fmt, ap);
        va_end(ap);
        fprintf(fp, "\n");
        fflush(fp);
    }
}

//VBO,VAO初始化
void vertexObjectInit()
{
    GLfloat vertices[] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f  };

    //生成顶点数组对象VAO
    glGenVertexArrays(1, &VAO);
    //生成顶点缓冲对象VBO
    glGenBuffers(1, &VBO);
    //绑定VAO
    glBindVertexArray(VAO);
    //绑定VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //复制顶点数据到VB0
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //解释顶点数据链接方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat),(GLvoid *) 0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);/*两个顶点属性之间无间隙，第五个参数可设置为0*/
    glEnableVertexAttribArray(0);/*开启顶点属性，参数是顶点属性location*/

    //解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //解绑VAO
    glBindVertexArray(0);
}

void shaderInit()
{
    //生成顶点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);/*着色器源码附加到着色器对象上*/
    glCompileShader(vertexShader);/*编译顶点着色器*/

    //检查顶点着色器是否编译成功，不成功输出错误信息
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        slog("---shaderinit-----GetShaderiv error=[%d]", success);
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        glDeleteShader(vertexShader);
    }

    //生成片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //检查片段着色器是否编译成功，不成功输出错误信息
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        slog("---shaderinit-----GetShaderiv error=[%d]", success);
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        glDeleteShader(fragmentShader);
    }

    //生成着色器程序对象，并连接着色器
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);/*把编译好的着色器附加到着色器程序对象上*/
    glAttachShader(shaderProgram, fragmentShader);

    //尝试链接
    glLinkProgram(shaderProgram);
    //检查链接着色器程序是否成功，不成功输出错误信息
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        slog("---shaderinit-----GetShaderiv error=[%d]", success);
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        glDeleteProgram(shaderProgram);
    }

    //删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

gboolean
render(GtkGLArea *area, gpointer user_data)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);/* clear the window*/
    glClear(GL_COLOR_BUFFER_BIT);

    //绘制过程
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glFlush();

    return TRUE;
}

void
realize(GtkWidget *area, gpointer user_data)
{
    gtk_gl_area_make_current(GTK_GL_AREA(area));
    if (gtk_gl_area_get_error(GTK_GL_AREA(area)) != NULL)
            return;

    glewExperimental = GL_TRUE;
    gboolean ret = glewInit();
    if(ret != GLEW_OK)
    {
        slog("<%s>--------glew init error [%s]", __func__, glewGetErrorString(ret));
    }

    //VBO,VAO初始化
    vertexObjectInit();
    shaderInit();
}

gboolean windowinit()
{
    GError *error = NULL;

    GtkWidget *area = gtk_gl_area_new();
    gtk_gl_area_set_required_version(GTK_GL_AREA(area), 3, 2);

    g_object_connect(area,
            "signal::render", render, NULL,
            "signal::realize", realize, NULL,
            NULL);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(area));

    gtk_widget_show_all(window);

    return TRUE;
}

static void create_window(void)
{
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window),"First GTK Window");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_widget_set_size_request(window, 800,800);

    windowinit();
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    create_window();

    gtk_main();
}
