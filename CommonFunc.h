#include <iostream>
#include <algorithm>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cmath>

#ifndef COMMONFUNCTION_H_

const float BOSS_SPEED = 0.085;
const int boss_animation_speed = 70;
const int animtion_speed = 300;
int const speed = 10;
const int timming = 500;
static bool is_hitting = false;
static bool main_is_hitting = false;
static bool is_skilling = false;
static bool boss_is_hitted = false;
static bool is_fight = false;
static bool main_boss_hit = false;
const float bullet_speed = 0.78;
const int time_last_skill = 500;
static bool skill_pos_set = false;
static bool kame_pos_set = false;
static bool is_kame_ = false;
static bool is_hitted = false;
static bool stop_game = false;
static bool boss_dead_facing_right = true;
static bool boss_dead_direction_locked = false;

extern bool is_fighting;

struct input_type
{
    int right_;
    int left_;
};

struct Player
{
    float x, y;

    Player(float px, float py);
};

void Boss_hitted(SDL_Rect& boss_dsrect, SDL_Rect& dsrect_, SDL_Texture*& tex_boss_main,
                 SDL_Texture* boss_hitted_left, SDL_Texture* boss_hitted_right, bool& is_hitting, int& status_);

SDL_Texture* LoadTex(SDL_Renderer* screen, const char* file);


class Bullet
{
public:
    float x, y;
    float v_x_, v_y_;
    int width_bullet, height_bullet;
    bool isActive;
    SDL_Texture* bul_tex;
    SDL_Texture* bullet_right;
    SDL_Texture* bullet_left;

    Bullet(float& startX, float& startY, float vantocX, float vantocY, SDL_Texture* bul_tex);

    void update();

    void render(SDL_Renderer* screen);
};

class BulletofPlane
{
public:
    float x, y;
    float v_x, v_y;
    int width, height;
    bool isActive_plane;
    SDL_Texture* bul_tex_plane;

    BulletofPlane(float& startX, float& startY, float vantocX, float vantocY, SDL_Texture* bul_tex);

    void update();

    void render(SDL_Renderer* screen);
};

class Plane
{
public:
    float x, y;
    int width, height;
    int shoottimer;
    int shootinterval;

    Plane(float bx, float by);

    void PlaneMove(SDL_Texture*& plane_tex, SDL_Texture* plane_right, SDL_Texture* plane_left);

    void update(Uint32 deltaTime, std::vector<BulletofPlane>& bul_plane, float& startX, float& startY,
                  SDL_Texture* bul_tex_plane, SDL_Rect& player_srect);

    void shoot(std::vector<BulletofPlane>& bul_plane, float& startX, float& startY, const float bullet_speed,
               SDL_Texture* bul_tex_plane);
};

struct Boss
{
    float x, y;
    int width, height;
    int shoottimer;
    int shootinterval;

    //vi tri cua boss
    Boss(float bx, float by);

    void BossMove(Player& player, SDL_Texture*& tex_main, SDL_Renderer* screen,
                  SDL_Texture* tex_boss1_right,
                  SDL_Texture* tex_boss1_left, bool& boss_is_hitted );
    void BossSkill(SDL_Rect& boss_skill_srect_, SDL_Texture* kinang,
                     Uint32& LastTime, int& frame_, bool& is_skilling,
                     const SDL_Rect& player_drect, SDL_Rect& skill_dest_rect,
                     bool& skill_pos_set, SDL_Texture*& tex_main,
                     SDL_Texture* bidanhphai, SDL_Texture* bidanhtrai, SDL_Rect& boss_dsrect,
                     SDL_Texture* tex_main_left, SDL_Texture* tex_main_right, float& playerHealth);

    void update(Uint32 deltaTime, std::vector<Bullet>& bullets, float& startX, float& startY,
                  SDL_Texture* bullet_right, SDL_Texture* bullet_left, int& countt);
    void shoot(std::vector<Bullet>& bullets, float& startX, float& startY, const float bullet_speed,
               SDL_Texture* bullet_right, SDL_Texture* bullet_left);

    void render(SDL_Renderer* screen);

    void BossMovement(SDL_Rect& boss_srect_, SDL_Texture*& tex_boss_main,
                      Uint32& LastTime, int& frame_ );

};

void updateBullets(std::vector<Bullet>& bullets);
void updateBullets_plane(std::vector<BulletofPlane>& bul_plane);

void renderBullets(SDL_Renderer* screen, std::vector<Bullet>& bullets);
void renderBullets_plane(SDL_Renderer* screen, std::vector<BulletofPlane>& bul_plane);

void checkBullet(std::vector<Bullet>& bullets, const SDL_Rect& srect_,
                 SDL_Texture*& tex_main, SDL_Texture*& bidanhphai, SDL_Texture*& bidanhtrai,
                 Uint32& boss_hit_time, bool& main_is_hitting, SDL_Rect& chuong_dsrect,
                 float& playerHealth);

void checkBulletofPlane(std::vector<BulletofPlane>& bul_plane, const SDL_Rect& srect_,
                 SDL_Texture*& tex_main, SDL_Texture*& bidanhphai, SDL_Texture*& bidanhtrai,
                 Uint32& boss_hit_time, bool& main_is_hitting, int status_,
                 float& playerHealth, float& bossHealth);

void Kamehameha(SDL_Rect& kame_rect_, bool& is_kame_,
                Uint32& kame_time, int& kame_frame,
                bool& kame_pos_set, const SDL_Rect& player_rect, SDL_Rect& kame_dsrect,
                SDL_Rect& chuong_srect_, SDL_Rect& chuong_dsrect_, int& chuong_frame,
                SDL_Renderer* screen, SDL_Texture* kameha_right, SDL_Texture* kameha_left,
                int& status_, SDL_Texture*& tex_boss_main, SDL_Rect& boss_srect, SDL_Rect& boss_dsrect,
                SDL_Texture* boss_hitted_left, SDL_Texture* boss_hitted_right, bool& boss_is_hitted,
                float& bossHealth, Mix_Chunk* kameha_sound);

void renderHealthBar(SDL_Renderer* screen, int x, int y, int width, int height, float& currentHealth, int maxHealth);

void renderKi(SDL_Renderer* screen, int x, int y, int width, int height, float& currentKi, int maxKi);


#endif // COMMONFUNCTION_H_
