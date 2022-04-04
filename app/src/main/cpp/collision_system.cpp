bool CollisionSystem::Initialize() {
  return true;
}

void CollisionSystem::Update(AABB *a, AABB *b, float dt) {
  if (TestAABBAABB(a, b)) {
    std::cout << "Collide!";
  }
}

bool CollisionSystem::TestAABBAABB(AABB *a, AABB *b) {
  if (a->m_max.x < b->m_min.x || a->m_min.x > b->m_max.x) return false;
  if (a->m_max.y < b->m_min.y || a->m_min.y > b->m_max.y) return false;
  return true;
}