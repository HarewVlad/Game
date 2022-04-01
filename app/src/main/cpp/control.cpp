bool Control::Initialize(Input *input) {
  m_input = input;

  return true;
}

void Control::Update(Box *box, float dt) {
  if (m_input->GetKeyState('A')) {
    box->m_position.x -= 1;
  } else if (m_input->GetKeyState('D')) {
    box->m_position.x += 1;
  }
}
