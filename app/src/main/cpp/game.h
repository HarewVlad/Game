// NOTE(Vlad): Your game should have this methods at least =)
struct Game {
  virtual void Shutdown() = 0;
  virtual void Render() = 0;
  virtual void Update(float dt) = 0;
};