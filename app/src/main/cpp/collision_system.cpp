bool CollisionSystem::Initialize() {
  return true;
}

void CollisionSystem::Update(Body *a, Body *b, Movement *c, Movement *d, float dt) {
  if (TestAABBAABB(a, b)) {
    if (c) c->m_velocity = {};
    if (d) d->m_velocity = {};
  }
}

bool CollisionSystem::TestAABBAABB(Body *a, Body *b) {
  if (a->m_max.x < b->m_min.x || a->m_min.x > b->m_max.x) return false;
  if (a->m_max.y < b->m_min.y || a->m_min.y > b->m_max.y) return false;
  return true;
}