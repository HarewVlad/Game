struct Effect {
  void Initialize(float duration, float frequency);
  bool IsExecuting() const;
  void Start();
  void Stop();

  float m_time;
  float m_total_time;
  float m_frequency;
  int m_duration;
};