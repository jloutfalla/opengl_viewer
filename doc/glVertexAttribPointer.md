/*
first arg '0':
layout(location=0) in vertex shader, tell to opengl that the GL_ARRAY_BUFFER currently bound
should go to location 0 in the shader program

'3':
nomber of element in the vertex, this time 3, see vertices

'GL_FLOAT':
type on a single element of the vertex

'GL_FALSE':
If that should be normalized to float, [-1, 1] if signed [0, 1] otherwise

'0':
tricky part, if the vertices passed to the currently bound GL_ARRAY_BUFFER are
tighlty packed then '0' let opengl compute the stride, or step between each vertex.
otherwise we have to manually specify it, in this case: sizeof(float)*3

'(void*) 0':
weird cast, position data begins in the buffer.
*/
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
// enable the vertex attribute giving the vertex attribute location : vertex attributes are disabled by default
glEnableVertexAttribArray(0);