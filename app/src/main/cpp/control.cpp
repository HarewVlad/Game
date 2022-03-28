bool Control::Initialize(Box *box, Input *input) {
  m_box = box;
  m_input = input;

  return true;
}

void Control::Update(float dt) {
  if (m_input->GetKeyState('A')) {
    m_box->m_position.x -= 1;
  } else if (m_input->GetKeyState('D')) {
    m_box->m_position.x += 1;
  }
}
