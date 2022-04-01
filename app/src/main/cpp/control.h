struct Control {
  bool Initialize(Input *input);
  void Update(Box *box, float dt);
  
  Input *m_input;
};