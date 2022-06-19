enum AnimationType {
  AnimationType_PlayerIdle,
  AnimationType_PlayerRun,
  AnimationType_Bear,
  AnimationType_Bandit,
  AnimationType_Ent,
  AnimationType_Golem,
};

enum PlayerAnimation {
  PlayerAnimation_Idle = 4,
  PlayerAnimation_Run = 7,
};

struct AnimationInfo {
  int m_type;
  int m_size;
  char *m_fmt;
};

const AnimationInfo Global_AnimationInfo[] = {
  {AnimationType_PlayerIdle, 4, "player/idle/%d.png"},
  {AnimationType_PlayerRun, 8, "player/run/%d.png"},
  {AnimationType_Bear, 4, "bear/%d.png"},
  {AnimationType_Bandit, 4, "bandit/%d.png"},
  {AnimationType_Ent, 4, "ent/%d.png"},
  {AnimationType_Golem, 6, "golem/%d.png"},
};