struct EffectBlink {
  void Initialize(float duration, float frequency);
  bool IsExecuting() const;
  void Update(int *blink, float dt);
  void Start();
  void Stop();

  float m_time;
  float m_total_time;
  float m_frequency;
  int m_duration;
};