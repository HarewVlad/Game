void CollisionSystem::Initialize() {
}

void CollisionSystem::Update(int ida, int idb, Body *ba, Body *bb, Movement *ma, Movement *mb, float dt) {
  if (ba->m_type == BodyType::NORMAL) { // NOTE(Vlad): If it is collision between normal AABBs
    if (TestAABBAABB(ba, bb)) { // TODO: If physics applied - resolve, based on box2d-lite physics engine code
      if (m_on_collide_normal) {
        m_on_collide_normal(ida, idb);
      }
    }
  } 
  else if (ba->m_type == BodyType::BOUNDING) {
    if (TestAABBInsideAABB(ba, bb)) {
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

bool CollisionSystem::TestAABBAABB(Body *a, Body *b) {
  if (a->m_max.x < b->m_min.x || a->m_min.x > b->m_max.x) return false;
  if (a->m_max.y < b->m_min.y || a->m_min.y > b->m_max.y) return false;
  return true;
}

bool CollisionSystem::TestAABBInsideAABB(Body *bounding, Body *inner) {
  if (bounding->m_min.x > inner->m_min.x || bounding->m_max.x < inner->m_max.x) return true;
  if (bounding->m_min.y > inner->m_min.y || bounding->m_max.y < inner->m_max.y) return true;
  return false;
}