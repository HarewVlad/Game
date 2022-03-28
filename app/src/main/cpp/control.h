struct Control {
  bool Initialize(Box *box, Input *input);
  void Update(float dt);

  Box *m_box;
  Input *m_input;
};