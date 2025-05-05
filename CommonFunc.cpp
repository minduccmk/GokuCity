#include "CommonFunc.h"

bool is_fighting = false;

void Boss_hitted(SDL_Rect& boss_rect, SDL_Rect& player_rect, SDL_Texture*& tex_boss_main,
                 SDL_Texture* hitted_left, SDL_Texture* hitted_right, bool& is_hitting,int& status_,
                 float& playerKi)
{
    // Kiểm tra va chạm (giả sử va chạm xảy ra khi hai hình chữ nhật giao nhau)
    if (SDL_HasIntersection(&boss_rect, &player_rect))
    {
        // Chọn texture dựa trên vị trí tương đối
        if ((boss_rect.x < player_rect.x) && (status_ == 1))
        {
            tex_boss_main = hitted_left;  // Boss ở bên phải, đối mặt trái
            is_hitting = true;
        }
        else if ((boss_rect.x > player_rect.x) && (status_ == 0))
        {
            tex_boss_main = hitted_right; // Boss ở bên trái, đối mặt phải
            is_hitting = true;
        }

        playerKi += 10;
    }
    else
    {
        is_hitting = false;
    }
}


Player::Player(float px, float py) : x(px), y(py) {}

Boss::Boss(float bx, float by) : x(bx), y(by), width(53), height(72)
, shoottimer(0), shootinterval(5000) {}

Plane::Plane(float bx, float by) : x(bx), y(by), width(100), height(100),
shoottimer(0), shootinterval(5000) {}

void Boss::shoot(std::vector<Bullet>& bullets, float& startX, float& startY, const float bullet_speed,
                  SDL_Texture* bullet_right, SDL_Texture* bullet_left)
{
    bullets.push_back(Bullet(startX, startY, (-1)*bullet_speed, 0, bullet_right));
    bullets.push_back(Bullet(startX, startY, bullet_speed, 0, bullet_left));
}

void Plane::shoot(std::vector<BulletofPlane>& bul_plane, float& startX, float& startY, const float bullet_speed,
                  SDL_Texture* bul_tex_plane)
{
    bul_plane.push_back(BulletofPlane(startX, startY, bullet_speed, 0, bul_tex_plane));
}

void Boss::update(Uint32 deltaTime, std::vector<Bullet>& bullets, float& startX, float& startY,
                  SDL_Texture* bullet_right, SDL_Texture* bullet_left, int& countt)
{
    shoottimer += deltaTime;

    if (shoottimer >= shootinterval)
    {
        shoottimer = 0;

        countt++;

        shoot(bullets, startX, startY, bullet_speed, bullet_right, bullet_left);
    }

}

void Plane::update(Uint32 deltaTime_plane, std::vector<BulletofPlane>& bul_plane, float& startX, float& startY,
                   SDL_Texture* bul_tex_plane, SDL_Rect& player_srect)
{
    shoottimer += deltaTime_plane;

    if (startX == player_srect.x)
    {
        shoot(bul_plane, startX, startY, bullet_speed, bul_tex_plane);
    }

    if (shoottimer >= shootinterval)
    {
        shoottimer = 0;

        shoot(bul_plane, startX, startY, bullet_speed, bul_tex_plane);
    }
}

void Boss::BossMove(Player& player, SDL_Texture*& tex_main, SDL_Renderer* screen,
                  SDL_Texture* tex_boss1_right,
                  SDL_Texture* tex_boss1_left, bool& boss_is_hitted)
    {
        float dx = player.x - x;
        float dy;
        if (dy != 75)   dy = player.y - y;

        float between;
        between = sqrt(dx * dx + dy * dy);

        if (!boss_is_hitted)
        {

            if (abs(dx) > 88)
            {
                x += (dx / between) * BOSS_SPEED;
                y += (dy / between) * BOSS_SPEED;
            }
            else
            {
                //x += (dx / between) * BOSS_SPEED;
                y = player.y + 120 - 200;
            }

        if (dx > 0) tex_main = tex_boss1_right;
        if (dx < 0) tex_main = tex_boss1_left;
        }
    }

void Plane::PlaneMove(SDL_Texture*& plane_tex, SDL_Texture* plane_right, SDL_Texture* plane_left)
{
    float v_x = (plane_tex == plane_right) ? 0.15 : -0.15;
    x += v_x;

    // Nếu chạm rìa thì đổi hướng và chỉnh vị trí lại cho hợp lệ
    if (x > 1100) {
        x = 1100;
        plane_tex = plane_left;
    }
    else if (x < 0) {
        x = 0;
        plane_tex = plane_right;
    }
}

void Boss::BossMovement(SDL_Rect& boss_srect_, SDL_Texture*& tex_boss_main,
                      Uint32& LastTime, int& frame_)
    {
        if (LastTime == 0)
            {
                LastTime = SDL_GetTicks();
            }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime > LastTime + boss_animation_speed)
            {
                frame_ = (frame_ + 1) % 7;
                boss_srect_.x = frame_ * 80;
                LastTime = currentTime;
            }
    }

// Hàm BossSkill nhận thêm tham số: vị trí của nhân vật và biến lưu vị trí render của chiêu cuối.
void Boss::BossSkill(SDL_Rect& boss_skill_srect_, SDL_Texture* kinang,
                     Uint32& LastTime, int& frame_, bool& is_skilling,
                     const SDL_Rect& player_drect, SDL_Rect& skill_dest_rect,
                     bool& skill_pos_set, SDL_Texture*& tex_main, SDL_Texture* bidanhphai,
                     SDL_Texture* bidanhtrai, SDL_Rect& boss_dsrect, SDL_Texture* tex_main_left, SDL_Texture* tex_main_right,
                     float& playerHealth)
{
    // Nếu đây là lần đầu kích hoạt chiêu cuối, lưu lại vị trí của nhân vật
    if (!skill_pos_set)
    {
        // Lưu vị trí của nhân vật tại thời điểm kích hoạt chiêu cuối
        skill_dest_rect.x = player_drect.x + 20;
        skill_dest_rect.y = player_drect.y + 20;
        // Giả sử kích thước render của chiêu cuối bằng kích thước frame của sprite
        skill_dest_rect.w = 70;
        skill_dest_rect.h = 90;
        skill_pos_set = true;
    }

    // Nếu LastTime chưa được khởi tạo, khởi tạo lần đầu tiên
        Uint32 currentTime = SDL_GetTicks();
    if (currentTime > LastTime + 100) // 100ms mỗi frame
    {
            frame_++; // Tăng frame mỗi 100ms

        if (frame_ >= 8) // Khi đến frame cuối cùng
        {
            if (tex_main == bidanhphai)
            {
                tex_main = tex_main_left;
            }
            else tex_main = tex_main_right;

            frame_ = 0; // Reset frame
            boss_skill_srect_.x = 0;
            is_skilling = false; // Kết thúc animation
            skill_pos_set = false; // Cho phép chiêu cuối được kích hoạt lại
        }

        boss_skill_srect_.x = frame_ * 96;

        if (player_drect.x > boss_dsrect.x)
        {
            tex_main = bidanhphai;
        }
        else tex_main = bidanhtrai;

        LastTime = currentTime; // Cập nhật thời gian frame
    }

    playerHealth -= 0.5;
}


void Boss::render(SDL_Renderer* renderer) {
        SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), width, height };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Màu đỏ cho boss
        SDL_RenderFillRect(renderer, &rect);
    }

SDL_Texture* LoadTex(SDL_Renderer* screen, const char* file)
{
    SDL_Surface* surface = IMG_Load(file);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 167, 175, 180));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(screen, surface);

    SDL_FreeSurface(surface);

    return texture;
}

Bullet::Bullet(float& startX, float& startY, float vantocX, float vantocY, SDL_Texture* bul_tex)
: x(startX), y(startY), v_x_(vantocX), v_y_(0),
    width_bullet(50), height_bullet(33), isActive(true), bul_tex(bul_tex) {}

BulletofPlane::BulletofPlane(float& startX, float& startY, float vantocX, float vantocY, SDL_Texture* bul_tex_plane)
: x(startX), y(startY), v_x(0), v_y(0.2),
    width(90), height(90), isActive_plane(true), bul_tex_plane(bul_tex_plane) {}

void Bullet::update()
{
    if (!isActive) return;

    x += v_x_;

    if (x <0 || x > 1200)
    {
        isActive = false;
    }
}

void BulletofPlane::update()
{
    if (!isActive_plane) return ;

    y += v_y;

    if (y <0 || y > 911)
    {
        isActive_plane = false;
    }
}

void Bullet::render(SDL_Renderer* screen)
{
    if (!isActive) return;

    SDL_Rect rect = {static_cast<int> (x), static_cast<int> (y), 50, 33};

    SDL_RenderCopy(screen, bul_tex, nullptr, &rect);
}


void BulletofPlane::render(SDL_Renderer* screen)
{
    if (!isActive_plane) return;

    SDL_Rect rect = {static_cast<int> (x), static_cast<int> (y), 90, 90};

    SDL_RenderCopy(screen, bul_tex_plane, nullptr, &rect);
}

void updateBullets(std::vector<Bullet>& bullets)
{
    for (auto& bullet : bullets)
    {
        bullet.update();
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const Bullet& b) { return !b.isActive; }),
                                 bullets.end());
}

void updateBullets_plane(std::vector<BulletofPlane>& bul_plane)
{
    for (auto& bul_planec : bul_plane)
    {
        bul_planec.update();
    }

    bul_plane.erase(std::remove_if(bul_plane.begin(), bul_plane.end(),
                                   [](const BulletofPlane& b) {return !b.isActive_plane;}),
                                   bul_plane.end());
}

void renderBullets(SDL_Renderer* screen, std::vector<Bullet>& bullets)
{
    for (auto& bullet : bullets)
    {
        bullet.render(screen);
    }
}

void renderBullets_plane(SDL_Renderer* screen, std::vector<BulletofPlane>& bul_plane)
{
    for (auto& bul_planec : bul_plane)
    {
        bul_planec.render(screen);
    }
}

void checkBullet(std::vector<Bullet>& bullets, const SDL_Rect& srect_,
                 SDL_Texture*& tex_main, SDL_Texture*& bidanhphai, SDL_Texture*& bidanhtrai,
                 Uint32& boss_hit_time, bool& main_is_hitting, SDL_Rect& chuong_dsrect,
                 float& playerHealth)
{
    for (auto& bullet : bullets)
    {

        SDL_Rect bulletRect = {static_cast<int> (bullet.x), static_cast<int> (bullet.y), 50, 33};

        if (SDL_HasIntersection(&bulletRect, &srect_))
            {
                    bullet.isActive = false;

                    main_is_hitting = true;
                    boss_hit_time = SDL_GetTicks();

                    SDL_Log("srect_.x = %d, bulletRect.x = %d", srect_.x, bulletRect.x);

                    if (srect_.x < bulletRect.x)
                    {
                        tex_main = bidanhtrai;
                        SDL_Log("Chọn bidanhtrai");
                    }
                    else
                    {
                        tex_main = bidanhphai;
                        SDL_Log("Chọn bidanhphai");
                        //std::cout << "danh";
                    }

                playerHealth -= 30;
            }

        if (SDL_HasIntersection(&bulletRect, &chuong_dsrect))
        {
            bullet.isActive = false;
        }
    }
}

void checkBulletofPlane(std::vector<BulletofPlane>& bul_plane, const SDL_Rect& srect_,
                 SDL_Texture*& tex_main, SDL_Texture*& bidanhphai, SDL_Texture*& bidanhtrai,
                 Uint32& boss_hit_time, bool& main_is_hitting, int status_,
                 float& playerHealth, float&bossHealth)
{
    for (auto& bul_planec : bul_plane)
    {

        SDL_Rect bullet_planeRect = {static_cast<int> (bul_planec.x), static_cast<int> (bul_planec.y), 90, 90};

        if (SDL_HasIntersection(&bullet_planeRect, &srect_))
            {
                    bul_planec.isActive_plane = false;

                    main_is_hitting = true;
                    boss_hit_time = SDL_GetTicks();

                    SDL_Log("srect_.x = %d, bullet_planeRect.x = %d", srect_.x, bullet_planeRect.x);

                    if (status_ == 0)
                    {
                        tex_main = bidanhtrai;
                        SDL_Log("Chọn bidanhtrai");
                    }
                    else if (status_ == 1)
                    {
                        tex_main = bidanhphai;
                        SDL_Log("Chọn bidanhphai");
                        //std::cout << "danh";
                    }

                if (bossHealth != 0)
                {
                    playerHealth -= 50;
                }
            }
    }
}

void Kamehameha(SDL_Rect& kame_rect_, bool& is_kame_,
                Uint32& kame_time, int& kame_frame,
                bool& kame_pos_set, const SDL_Rect& player_rect, SDL_Rect& kame_dsrect,
                SDL_Rect& chuong_srect_, SDL_Rect& chuong_dsrect_, int& chuong_frame,
                SDL_Renderer* screen, SDL_Texture* kameha_right, SDL_Texture* kameha_left,
                int& status_, SDL_Texture*& tex_boss_main, SDL_Rect& boss_srect, SDL_Rect& boss_dsrect,
                SDL_Texture* boss_hitted_left, SDL_Texture* boss_hitted_right, bool& boss_is_hitted,
                float& bossHealth, Mix_Chunk* kameha_sound, float& playerKi,
                float& boss2_2_Health, float& boss2_3_Health, SDL_Rect boss2_2_dsrect, SDL_Rect boss2_3_dsrect)
    {
        if (!kame_pos_set)
        {
            kame_dsrect.x = player_rect.x;
            kame_dsrect.y = player_rect.y;

            kame_dsrect.w = 57;
            kame_dsrect.h = 90;

            if (status_ == 0)
            {
                chuong_dsrect_.x = 57 + player_rect.x;
                chuong_dsrect_.y = player_rect.y + 10;
            }
            else
            {
                chuong_dsrect_.x = player_rect.x - 200;
                chuong_dsrect_.y = player_rect.y + 10;
            }

            chuong_dsrect_.w = 200;
            chuong_dsrect_.h = 80;

            kame_pos_set = true;
        }

        if (kame_frame == 6)
        {
            kame_frame = 6;
            kame_rect_.x = kame_frame * 57;

            Uint32 currentTime_kame = SDL_GetTicks();

            if (currentTime_kame > kame_time + 300)
            {
                chuong_frame += 1;
                chuong_srect_.x = chuong_frame * 180;
                kame_time = currentTime_kame;
            }

            if (SDL_HasIntersection(&boss_dsrect, &chuong_dsrect_))
                {
                    if (boss_dsrect.x > player_rect.x)
                    {
                        tex_boss_main = boss_hitted_right;
                    }
                    else tex_boss_main = boss_hitted_left;

                    boss_is_hitted = true;

                    bossHealth -= 2;

                    if (bossHealth > 0)
                    {
                        SDL_RenderCopy(screen, tex_boss_main, NULL, &boss_dsrect);
                    }

                }

            if (SDL_HasIntersection(&boss2_2_dsrect, &chuong_dsrect_))
            {
                boss2_2_Health -= 2.5;
            }

            if (SDL_HasIntersection(&boss2_3_dsrect, &chuong_dsrect_))
            {
                boss2_3_Health -= 2.5;
            }

            if (status_ == 0)
            {
                SDL_RenderCopy(screen, kameha_right, &chuong_srect_, &chuong_dsrect_);
            }
            else SDL_RenderCopy(screen, kameha_left, &chuong_srect_, &chuong_dsrect_);
        }

        Uint32 currentTime = SDL_GetTicks();

        if ((currentTime > kame_time + 300) && (kame_frame < 6))
        {
            kame_frame += 1;
            kame_rect_.x = kame_frame * 57;
            kame_time = currentTime;
        }

        if (chuong_frame >= 3)
        {
            kame_frame = 0;
            kame_rect_.x = 0;

            chuong_frame = 0;
            chuong_srect_.x = 0;

            kame_pos_set = false;
            is_kame_ = false;
            boss_is_hitted = false;

        }

        playerKi = 0;

        Mix_PlayChannel(-1, kameha_sound, 0);
    }

void renderHealthBar(SDL_Renderer* screen, int x, int y, int width, int height, float& currentHealth, int maxHealth)
{
    float HealthPercent = (float)currentHealth / maxHealth;
    int healthWidth = (int)(width * HealthPercent);

    SDL_Rect boder = {x, y, width, height};
    SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
    SDL_RenderDrawRect(screen, &boder);

    SDL_Rect heathRect = {x + 1,
        y + 1,
        (int)((width - 2) * HealthPercent),
        height - 2};
    SDL_SetRenderDrawColor(screen, 255, 0, 0, 255);
    SDL_RenderFillRect(screen, &heathRect);
}

void renderKi(SDL_Renderer* screen, int x, int y, int width, int height, float& currentKi, int maxKi)
{
    float KiPercent = (float)currentKi / maxKi;
    int KiWidth = (int)(width * KiPercent) ;

    SDL_Rect boder = {x, y, width, height};
    SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
    SDL_RenderDrawRect(screen, &boder);

    SDL_Rect KiRect = { x + 1,
                        y + 1,
                        (int)((width - 2) * KiPercent),
                        height - 2};

    SDL_SetRenderDrawColor(screen, 0, 255, 255, 255);
    SDL_RenderFillRect(screen, &KiRect);
}


