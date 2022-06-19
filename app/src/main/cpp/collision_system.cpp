void CollisionSystem::Update(EntityManager *entity_manager, float dt) {
  for (int i = 0; i < arrlen(m_entities); ++i) {
    for (int j = i + 1; j < arrlen(m_entities); ++j) {
      int cga = m_collision_groups[i];
      int cgb = m_collision_groups[j];

      if (cga == cgb)
        continue;

      Entity a = m_entities[i];
      Entity b = m_entities[j];

      Body *ba = entity_manager->GetComponent<Body>(a);
      Body *bb = entity_manager->GetComponent<Body>(b);

      Position *pa = entity_manager->GetComponent<Position>(a);
      Position *pb = entity_manager->GetComponent<Position>(b);

      bool is_collision = false;
      if (cga != CollisionGroup_Arena && cgb != CollisionGroup_Arena) {
        is_collision = TestAABBAABB(ba, bb, pa, pb);
      } else {
        if (cga != CollisionGroup_Arena) {
          is_collision = TestAABBInsideAABB(bb, ba, pb, pa);
        } else {
          is_collision = TestAABBInsideAABB(ba, bb, pa, pb);
        }
      }

      int collision_type = cga | cgb;
      if (is_collision) {
        switch (collision_type) {
          case CollisionType_PlayerEnemy: {
            Health *health;
            Effect *effect;
            if (cga != CollisionGroup_Player) {
              health = entity_manager->GetComponent<Health>(b);
              effect = entity_manager->GetComponent<Effect>(b);
            } else {
              health = entity_manager->GetComponent<Health>(a);
              effect = entity_manager->GetComponent<Effect>(a);
            }

            if (!effect->IsExecuting()) {
              --health->m_value;

              effect->Start();
            }
            
            if (health->m_value < 0) {
              Global_GameState |= GameState_Reset;
            }
          }
          break;
          case CollisionType_PlayerArena: {
            // TODO: Refactor
            Position *position;
            float width;
            if (cga != CollisionGroup_Player) {
              position = entity_manager->GetComponent<Position>(b);
              width = ba->m_size.x;
            } else {
              position = entity_manager->GetComponent<Position>(a);
              width = bb->m_size.x;
            }

            if (position->m_xy.x < 0)
              position->m_xy.x = width * 0.95f;
            else
              position->m_xy.x = 0;
          }
          break;
          case CollisionType_EnemyArena: {
            // TODO: Refactor this
            Position *enemy_position;
            glm::vec2 arena_size;

            if (cga != CollisionGroup_Enemy) {
              enemy_position = entity_manager->GetComponent<Position>(b);
              arena_size = ba->m_size;
            } else {
              enemy_position = entity_manager->GetComponent<Position>(a);
              arena_size = bb->m_size;
            }

            enemy_position->m_xy = Game::GetEnemyPosition(arena_size);
          }
          break;
        }
      }
    }
  }
}

bool CollisionSystem::TestAABBAABB(Body *ba, Body *bb, Position *pa,
                                   Position *pb) {
  int max_ax = pa->m_xy.x + ba->m_size.x;
  int max_ay = pa->m_xy.y + ba->m_size.y;
  int max_bx = pb->m_xy.x + bb->m_size.x;
  int max_by = pb->m_xy.y + bb->m_size.y;

  if (max_ax < pb->m_xy.x || pa->m_xy.x > max_bx)
    return false;
  if (max_ay < pb->m_xy.y || pa->m_xy.y > max_by)
    return false;
  return true;
}

bool CollisionSystem::TestAABBInsideAABB(Body *bounding, Body *inner,
                                         Position *bounding_position,
                                         Position *inner_position) {
  int max_boundingx = bounding_position->m_xy.x + bounding->m_size.x;
  int max_boundingy = bounding_position->m_xy.y + bounding->m_size.y;
  int max_innerx = inner_position->m_xy.x + inner->m_size.x;
  int max_innery = inner_position->m_xy.y + inner->m_size.y;

  if (bounding_position->m_xy.x > inner_position->m_xy.x ||
      max_boundingx < max_innerx)
    return true;
  if (bounding_position->m_xy.y > inner_position->m_xy.y ||
      max_boundingy < max_innery)
    return true;
  return false;
}

void CollisionSystem::AddEntity(Entity entity, int group) {
  ISystem::AddEntity(entity);
  arrput(m_collision_groups, group);
}