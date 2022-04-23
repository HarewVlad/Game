struct ControlSystem {
  void SetOnInputPlayer(const std::function<void(int, float)> on_input_player); // NOTE(Vlad): Only for player
  void SetOnInputGlobal(const std::function<void(float)> on_input_global); // NOTE(Vlad): For game state

  std::function<void(int, float)> m_on_input_player;
  std::function<void(float)> m_on_input_global;
};