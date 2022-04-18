void CollisionSystem::Initialize() {
}

void CollisionSystem::Update(int id_a, int id_b, Body *body_a, Body *body_b, Movement *movement_a, Movement *movement_b, float dt) {
  if (TestAABBAABB(body_a, body_b)) {
    if (movement_a) movement_a->m_velocity = {};
    if (movement_b) movement_a->m_velocity = {};

    if (m_on_collide) {
      m_on_collide(id_a, id_b);
    }
  }
}

void CollisionSystem::SetOnCollision(const std::function<void(int, int)> on_collide) {
  m_on_collide = on_collide;
}

bool CollisionSystem::TestAABBAABB(Body *a, Body *b) {
  if (a->m_max.x < b->m_min.x || a->m_min.x > b->m_max.x) return false;
  if (a->m_max.y < b->m_min.y || a->m_min.y > b->m_max.y) return false;
  return true;
}