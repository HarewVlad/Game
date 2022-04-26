void CollisionSystem::Initialize() {
}

inline void CollisionSystem::Update(int ida, int idb, Body *ba, Body *bb, Position *pa, Position *pb, float dt) {
  if (ba->m_type == BodyType::NORMAL) { // NOTE(Vlad): If it is collision between normal AABBs
    if (TestAABBAABB(ba, bb, pa, pb)) { // TODO: If physics applied - resolve, based on box2d-lite physics engine code
      if (m_on_collide_normal) {
        m_on_collide_normal(ida, idb);
      }
    }
  } 
  else if (ba->m_type == BodyType::BOUNDING) {
    if (TestAABBInsideAABB(ba, bb, pa, pb)) {
      if (m_on_collide_bounding) {
        m_on_collide_bounding(idb);
      }
    }
  }
}

void CollisionSystem::SetOnNormalCollision(const std::function<void(int, int)> on_collide) {
  m_on_collide_normal = on_collide;
}

void CollisionSystem::SetOnBoundingCollision(const std::function<void(int)> on_collide) {
  m_on_collide_bounding = on_collide;
}

inline bool CollisionSystem::TestAABBAABB(Body *ba, Body *bb, Position *pa, Position *pb) {
  int max_ax = pa->m_position.x + ba->m_size.x;
  int max_ay = pa->m_position.y + ba->m_size.y;
  int max_bx = pb->m_position.x + bb->m_size.x;
  int max_by = pb->m_position.y + bb->m_size.y;

  if (max_ax < pb->m_position.x || pa->m_position.x > max_bx) return false;
  if (max_ay < pb->m_position.y || pa->m_position.y > max_by) return false;
  return true;
}

inline bool CollisionSystem::TestAABBInsideAABB(Body *bounding, Body *inner, Position *bounding_position, Position *inner_position) {
  int max_boundingx = bounding_position->m_position.x + bounding->m_size.x;
  int max_boundingy = bounding_position->m_position.y + bounding->m_size.y;
  int max_innerx = inner_position->m_position.x + inner->m_size.x;
  int max_innery = inner_position->m_position.y + inner->m_size.y;

  if (bounding_position->m_position.x > inner_position->m_position.x || max_boundingx < max_innerx) return true;
  if (bounding_position->m_position.y > inner_position->m_position.y || max_boundingy < max_innery) return true;
  return false;
}