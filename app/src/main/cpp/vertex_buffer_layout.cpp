void VertexBufferLayout::Initialize() {
  m_elements = NULL;
  m_stride = 0;
}

void VertexBufferLayout::Push(unsigned int type, unsigned int count, unsigned char normilized) {
  VertexBufferElement vbe = {type, count, normilized};
  arrput(m_elements, vbe);
  
  m_stride += Utility::OpenGL::GetTypeSize(type) * count;
}