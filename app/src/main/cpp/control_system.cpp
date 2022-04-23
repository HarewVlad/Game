void ControlSystem::SetOnInputPlayer(const std::function<void(int, float)> on_input_player) {
  m_on_input_player = on_input_player;
}

void ControlSystem::SetOnInputGlobal(const std::function<void(float)> on_input_global) {
  m_on_input_global = on_input_global;
}