#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Define some of the global variables we're using for this sample
GLuint program;
GLuint vao;

// This is the callback we'll be registering with GLFW for errors.
// It'll just print out the error to the STDERR stream.
void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main() {
  // Initialize GLFW, and if it fails to initialize for any reason, print it out to STDERR.
  if (!glfwInit()) {
    fprintf(stderr, "Failed initialize GLFW.");
    exit(EXIT_FAILURE);
  }

  // Set the error callback, as mentioned above.
  glfwSetErrorCallback(error_callback);

  // Set up OpenGL options.
  // Use OpenGL verion 4.1,
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Indicate we only want the newest core profile, rather than using backwards compatible and deprecated features.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Make the window resize-able.
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a window to put our stuff in.
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

  // If the window fails to be created, print out the error, clean up GLFW and exit the program.
  if(!window) {
    fprintf(stderr, "Failed to create GLFW window.");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Use the window as the current context (everything that's drawn will be place in this window).
  glfwMakeContextCurrent(window);

  // Set the keyboard callback so that when we press ESC, it knows what to do.
  glfwSetKeyCallback(window, key_callback);

  printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

  // Makes sure all extensions will be exposed in GLEW and initialize GLEW.
  glewExperimental = GL_TRUE;
  glewInit();

  // Shaders is the next part of our program. Notice that we use version 410 core. This has to match our version of OpenGL we are using, which is the core profile in version 4.1, thus 410 core.

  // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
  // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
  static const char * vs_source[] =
  {
      "#version 410 core                                                 \n"
      "                                                                  \n"
      "void main(void)                                                   \n"
      "{                                                                 \n"
      "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
      "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
      "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
      "                                                                  \n"
      "    gl_Position = vertices[gl_VertexID];                          \n"
      "}                                                                 \n"
  };

  // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
  static const char * fs_source[] =
  {
      "#version 410 core                                                 \n"
      "                                                                  \n"
      "out vec4 color;                                                   \n"
      "                                                                  \n"
      "void main(void)                                                   \n"
      "{                                                                 \n"
      "    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
      "}                                                                 \n"
  };

  // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
  program = glCreateProgram();

  // We create a shader with our fragment shader source code and compile it.
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, fs_source, NULL);
  glCompileShader(fs);

  // We create a shader with our vertex shader source code and compile it.
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, vs_source, NULL);
  glCompileShader(vs);

  // We'll attach our two compiled shaders to the OpenGL program.
  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);

  // Generate vertex arrays for our program. More explanation on this will come in the future.
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // We'll specify that we want to use this program that we've attached the shaders to.
  glUseProgram(program);

  // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
  while(!glfwWindowShouldClose(window))
  {
    // Set up our green background color
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    // Clear the entire buffer with our green color (sets the background to be green).
    glClearBufferfv(GL_COLOR, 0, green);

    // Draw our triangles
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap the buffers so that what we drew will appear on the screen.
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Program clean up when the window gets closed.
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
}