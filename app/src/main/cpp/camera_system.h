struct CameraSystem {
  void Initialize(Position *position);
  glm::mat4 GetView() const;

  glm::mat4 m_view;
  Position *m_position;
};