#include "CommonFunc.h"

int status_;
int boss_status_;
int width_left, width_right, height_left, height_right;

//boss

enum Boss_emotion
{
    BOSS_MOVE_ = 1,
    BOSS_FIGHT_ = 0,
};

enum movement
{
    WALK_RIGHT,
    WALK_LEFT,
    BOSS_LEFT,
    BOSS_RIGHT,
};

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(IMG_INIT_PNG);
    SDL_Init(IMG_INIT_JPG);
    TTF_Init();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Mix Error";
    }

    Mix_Chunk* kameha_sound = Mix_LoadWAV("kameha.wav");
    Mix_Chunk* boss_skill_sound = Mix_LoadWAV("boss_skill.wav");
    Mix_Chunk* afterPlayerDie = Mix_LoadWAV("afterPlayerDie.wav");
    Mix_Chunk* winning = Mix_LoadWAV("winning.wav");

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return -1;

    SDL_Window* window = NULL;
    SDL_Renderer* g_screen = NULL;

    input_type input_type_;

    window = SDL_CreateWindow("GAME C++",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              1200,
                              911,
                              SDL_WINDOW_SHOWN);
    g_screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (g_screen == NULL) return -1;

    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load("img//map.png");

    texture = SDL_CreateTextureFromSurface(g_screen, surface);

    SDL_FreeSurface(surface);

    TTF_Font* font = TTF_OpenFont("arial.ttf", 24);

    SDL_Color textColor = {255, 255, 255};

    //Victory
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "VICTORY", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g_screen, textSurface);

    //Defeated
    SDL_Surface* textSurface_lose = TTF_RenderText_Solid(font, "DEFEATED", textColor);
    SDL_Texture* textTexture_lose = SDL_CreateTextureFromSurface(g_screen, textSurface_lose);

    SDL_Rect textRect = {600, 300, textSurface->w, textSurface->h};

    //Menu
    SDL_Texture* Menu = LoadTex(g_screen, "img//Menu.png");

    SDL_Rect Menu_dsrect = {200, 300, 800, 494};

    //tao hinh anh nhan vat o trang thai ban dau

    //tao surface
    //mac dinh la dung qua phai

    int countt = 0;
    //bullet va maybay

    SDL_Texture* bullet_right = LoadTex(g_screen, "img//bullet_left.png");
    SDL_Texture* bullet_left = LoadTex(g_screen, "img//bullet_right.png");
    SDL_Texture* plane1_right = LoadTex(g_screen, "img//plane1_right.png");
    SDL_Texture* plane1_left = LoadTex(g_screen, "img//plane1_left.png");
    SDL_Texture* bullet_jack = LoadTex(g_screen, "img//jack.png");
    SDL_Texture* plane1_tex = plane1_left;
    SDL_Texture* plane2_right = LoadTex(g_screen, "img//plane2_right.png");
    SDL_Texture* plane2_left = LoadTex(g_screen, "img//plane2_left.png");
    SDL_Texture* bullet_virus = LoadTex(g_screen, "img//virus.png");
    SDL_Texture* plane2_tex = plane2_right;

    //tao hieu ung tele

    SDL_Texture* tex_boss_main_ = NULL;
    SDL_Texture* tex_boss1_right = LoadTex(g_screen, "img//boss1_quaphai.png");
    SDL_Texture* tex_boss1_left = LoadTex(g_screen, "img//boss1_quatrai.png");
    SDL_Texture* frame_boss_right_ = LoadTex(g_screen, "img//boss1danhquaphai.png");
    SDL_Texture* frame_boss_left_ = LoadTex(g_screen, "img//boss1danhquatrai.png");
    SDL_Texture* boss_hitted_left = LoadTex(g_screen, "img//bossbidanhtrungtrai.png");
    SDL_Texture* boss_hitted_right = LoadTex(g_screen, "img//bossbidanhtrungphai.png");
    SDL_Texture* chieucuoi = LoadTex(g_screen, "img//kinang.png");
    SDL_Texture* thuchienskill_boss_left = LoadTex(g_screen, "img//boss_skill_left.png");
    SDL_Texture* thuchienskill_boss_right = LoadTex(g_screen, "img//boss_skill_right.png");

    //nhan vat

    SDL_Texture* tex_tele = LoadTex(g_screen, "img//teleport.png");
    SDL_Texture* tex_main_left = LoadTex(g_screen, "img//dungquatrai.png");
    SDL_Texture* tex_main_right = LoadTex(g_screen, "img//dungquaphai.png");
    SDL_Texture* tex_main = tex_main_right;
    SDL_Texture* tex_move_left = LoadTex(g_screen, "img//quatrai.png");
    SDL_Texture* tex_move_right = LoadTex(g_screen, "img//quaphai.png");
    SDL_Texture* tex_ssj_right = LoadTex(g_screen, "img//ssjright.png");
    SDL_Texture* tex_ssj_left = LoadTex(g_screen, "img//ssjleft.png");
    SDL_Texture* bidanhphai = LoadTex(g_screen, "img//bidanhphai.png");
    SDL_Texture* bidanhtrai = LoadTex(g_screen, "img//bidanhtrai.png");
    SDL_Texture* thedungchuong_right = LoadTex(g_screen, "img//thedungchuong_right.png");
    SDL_Texture* thedungchuong_left = LoadTex(g_screen, "img//thedungchuong_left.png");
    SDL_Texture* kameha_right = LoadTex(g_screen, "img//kameha_right.png");
    SDL_Texture* kameha_left = LoadTex(g_screen, "img//kameha_left.png");

    //tao animation

    SDL_Texture* frame_sheet_right_ = LoadTex(g_screen, "img//danhquaphai.png");

    SDL_Texture* frame_sheet_left_ = LoadTex(g_screen, "img//danhquatrai.png");

    int dem = 0;

    int frame_right = 0;
    int frame_left = 0;

    int boss_frame_ = 0;
    int boss_frame_fight = 0;

    int skill_frame_ = 0; //frame ki nang

    int kame_frame = 0;
    int chuong_frame = 0;

    float playerHealth = 1000;
    int playerMaxHealth = 1000;
    float bossHealth = 3000;
    int bossMaxHealth = 3000;

    SDL_Rect srect_ = {0, 0, 88, 92};

    SDL_Rect dsrect_ = {0, 411, 120, 120};

    //kamehameha
    SDL_Rect kame_srect_ = {0, 0, 57, 90};

    SDL_Rect kame_dsrect_ = {0, 0, 150, 150};

    SDL_Rect chuong_srect_ = {0, 0, 180, 66};

    SDL_Rect chuong_dsrect_ = {0, 0, 200, 80};

    if (texture == NULL) return -1;

    bool inMenu = true;
    bool is_quit = false;
    bool holding = false;

    //boss1
    Player player(0, 300);
    Boss boss1(1050, 350);
    std::vector<Bullet> bullets;
    std::vector<BulletofPlane> plane1_bullet;
    std::vector<BulletofPlane> plane2_bullet;
    //khoi tao gia tri
    Plane plane1(500, 0);
    Plane plane2(700,0);

    SDL_Rect plane1_dsrect = {500, 0, 100, 100};
    SDL_Rect plane2_dsrect = {700, 0, 150, 100};

    SDL_Rect boss_srect_ = {0, 0, 180, 200};
    SDL_Rect boss_dsrect_ = {1050, 350, 180, 219};

    //cho ki nang cua boss
    SDL_Rect boss_skill_rect = {0, 0, 96, 119};
    SDL_Rect boss_skill_dsrect = {0, 0, 100, 120};

    SDL_Event event;

    //time
    Uint32 kame_time = SDL_GetTicks();
    Uint32 LastTime = SDL_GetTicks();
    Uint32 LastTime_plane = SDL_GetTicks();
    Uint32 LastTimem = SDL_GetTicks();
    Uint32 boss_time = SDL_GetTicks();
    Uint32 boss1_lasttime = SDL_GetTicks();
    Uint32 boss_hit_time = SDL_GetTicks();
    Uint32 main_hit_time = SDL_GetTicks();
    Uint32 boss_time_skill = SDL_GetTicks();

    // bo dem thoi gian
    Uint32 startTime = SDL_GetTicks();
    int Timecount = 300;

    //end game
    //player
    SDL_Texture* player_end_game_right = LoadTex(g_screen, "img//player_end_game_right.png");
    SDL_Texture* player_end_game_left = LoadTex(g_screen, "img//player_end_game_left.png");
    SDL_Rect player_srect_end = {0, 0, 86, 92};

    int player_end_game = 0;
    Uint32 main_end_game = SDL_GetTicks();

    //boss
    SDL_Texture* boss_end_game_right = LoadTex(g_screen, "img//boss_end_game_right.png");
    SDL_Texture* boss_end_game_left = LoadTex(g_screen, "img//boss_end_game_left.png");
    SDL_Rect boss_srect_end = {0, 0, 150, 219};

    int boss_end_game = 0;

    //xu ly tele



    // vong lap quan trong
    while (!is_quit)
    {
        while ((SDL_PollEvent(&event)))
        {
            if (event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            else if ((event.type == SDL_KEYDOWN) && (!is_skilling) && (!is_kame_))
            {

                if (event.key.keysym.sym == SDLK_SPACE)

                    stop_game = true;

                if (event.key.keysym.sym == SDLK_RETURN)

                    stop_game = false;

                if (event.key.keysym.sym == SDLK_ESCAPE)
                    is_quit = true;

                    if ( playerHealth != 0)
                    {
                        const Uint8* state = SDL_GetKeyboardState(NULL);

                        bool only_w_pressed = state[SDL_SCANCODE_W] &&
                      !state[SDL_SCANCODE_A] &&
                      !state[SDL_SCANCODE_S] &&
                      !state[SDL_SCANCODE_D];

                      bool only_s_pressed = !state[SDL_SCANCODE_W] &&
                      !state[SDL_SCANCODE_A] &&
                      state[SDL_SCANCODE_S] &&
                      !state[SDL_SCANCODE_D];

if (state[SDL_SCANCODE_D]) {
    status_ = WALK_RIGHT;
    input_type_.right_ = 1;
    tex_main = tex_move_right;
    dsrect_.x += speed;
    if (dsrect_.x > 1200 - 150) dsrect_.x = 1200 - 150;
}

if (state[SDL_SCANCODE_A]) {
    status_ = WALK_LEFT;
    input_type_.left_ = 1;
    tex_main = tex_move_left;
    dsrect_.x -= speed;
    if (dsrect_.x < 0) dsrect_.x = 0;
}

if (state[SDL_SCANCODE_W]) {
    if (tex_main == tex_move_left) tex_main = tex_main_left;
    else if (tex_main == tex_move_right) tex_main = tex_main_right;
    dsrect_.y -= speed;
    if (dsrect_.y < 411) dsrect_.y = 411;
}

if (state[SDL_SCANCODE_S]) {
    if (tex_main == tex_move_left) tex_main = tex_main_left;
    else if (tex_main == tex_move_right) tex_main = tex_main_right;
    dsrect_.y += speed;
    if (dsrect_.y > 911 - 150) dsrect_.y = 911 - 150;
}
switch(event.key.keysym.sym)
{
                    case SDLK_j:
                        is_fight = true;

                        if ((is_fight) && (event.key.repeat == 0))
                        {
                            if (status_ == WALK_RIGHT)
                        {
                            tex_main = frame_sheet_right_;

                            if (LastTime == 0)
                            {
                                LastTime = SDL_GetTicks();
                            }

                            Uint32 currentTime = SDL_GetTicks();

                            srect_.x = frame_right * 88;
                            if (currentTime > LastTime + animtion_speed)
                            {
                                frame_right++;
                                if (frame_right >= 3) frame_right = 0;

                                LastTime = currentTime;
                            } // nhan vat danh

                            std::cout << "frame_right" << frame_right ;

                            if (bossHealth != 0)
                            {
                                Boss_hitted(boss_dsrect_, dsrect_,tex_boss_main_, boss_hitted_left, boss_hitted_right,
                                        is_hitting, status_);
                            }

                            if (is_hitting)
                            {
                                boss_hit_time = SDL_GetTicks();
                                bossHealth -= 20;

                                std::cout << "chuan";
                            }
                        }
                        else
                        {
                            tex_main = frame_sheet_left_;

                            if (LastTime == 0)
                            {
                                LastTime = SDL_GetTicks();
                            }

                            Uint32 currentTime = SDL_GetTicks();

                            srect_.x = frame_left * 88;
                            if (currentTime > LastTime + animtion_speed)
                            {
                                frame_left++;
                                if (frame_left >= 3) frame_left = 0;

                                LastTime = currentTime;
                            }

                            std::cout << "frame_left" << frame_right ;


                            if (bossHealth != 0)
                            {
                                Boss_hitted(boss_dsrect_, dsrect_,tex_boss_main_, boss_hitted_left, boss_hitted_right,
                                        is_hitting, status_);
                            }

                            if (is_hitting)
                            {
                                boss_hit_time = SDL_GetTicks();
                                bossHealth -= 20;

                                std::cout << "chuan";
                            }
                        }
                        }
                        break;
                    case SDLK_l:
                        {
                            if (!holding)
                            {
                                tex_main = tex_tele;
                                if (status_ == WALK_RIGHT)  dsrect_.x += 12 * speed;
                                else dsrect_.x -= 12 * speed;
                            }

                            if (dsrect_.x < 0) dsrect_.x = 0;

                            if (dsrect_.x > 1200 - 150) dsrect_.x = 1200 - 150;

                            holding = true;


                        }
                        break;
                    case SDLK_o:
                        if (status_ == WALK_LEFT) tex_main = tex_ssj_left;
                        else tex_main = tex_ssj_right;
                        break;

                    case SDLK_i:
                        is_kame_ = true;

                        kame_time = SDL_GetTicks();

                        is_fight = false;
                        is_hitted = false;
                        break;

                    }
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                if(event.key.keysym.sym == SDLK_d)
                {
                    input_type_.right_ = 0;
                    tex_main = tex_main_right;
                    dsrect_.x += 0;
                }
                if(event.key.keysym.sym == SDLK_a)
                {
                    input_type_.left_ = 0;
                    tex_main = tex_main_left;
                    dsrect_.x += 0;
                }
                if(event.key.keysym.sym == SDLK_s)
                {
                    dsrect_.y += 0;
                }
                if(event.key.keysym.sym == SDLK_w)
                {
                    dsrect_.y += 0;
                }
                if(event.key.keysym.sym == SDLK_j)
                {
                    is_fight = false;

            if (status_ == WALK_RIGHT) {
                tex_main = tex_main_right;
            } else {
                tex_main = tex_main_left;
            }
            srect_.x = 0;
                }
                if(event.key.keysym.sym == SDLK_o)
                {
                    if (status_ == WALK_LEFT) tex_main = tex_main_left;
                    else tex_main = tex_main_right;
                }
                if(event.key.keysym.sym == SDLK_l)
                {
                    if (status_ == WALK_RIGHT)  tex_main = tex_main_right;
                    else tex_main = tex_main_left;

                    holding = false;
                }
            }
            player.x = dsrect_.x;
            player.y = dsrect_.y;
            }

        if (stop_game)
        {

            SDL_RenderCopy(g_screen, Menu, NULL, &Menu_dsrect);

            SDL_RenderPresent(g_screen);

            continue;
        }

        plane1.PlaneMove(plane1_tex, plane1_right, plane1_left);
        plane1_dsrect.x = plane1.x;

        plane2.PlaneMove(plane2_tex, plane2_right, plane2_left);
        plane2_dsrect.x = plane2.x;

        Uint32 currentTime_Plane = SDL_GetTicks();
        Uint32 bul_deltaTime = currentTime_Plane - LastTime_plane;
        LastTime_plane = currentTime_Plane;


if ((!is_hitting) && (bossHealth != 0)){
        boss1.BossMove(player, tex_boss_main_, g_screen, tex_boss1_right, tex_boss1_left, boss_is_hitted);
        boss1.BossMovement(boss_srect_, tex_boss_main_, boss1_lasttime, boss_frame_);

// cap nhat vi tri cua quai

        if (!is_skilling)
        {
            boss_dsrect_.x = boss1.x;
            boss_dsrect_.y = boss1.y;
        }
// kiem tra va cham

        if (SDL_HasIntersection(&boss_dsrect_, &dsrect_))
            {
                boss_status_ = BOSS_FIGHT_;
            }
        else
        {
            boss_status_ = BOSS_MOVE_;
        }

        if ((boss_status_ == BOSS_FIGHT_) && (!is_skilling) && (!is_kame_) && (bossHealth != 0))
        {

            if (boss_dsrect_.x > dsrect_.x)
            {
                tex_boss_main_ = frame_boss_left_;
            }

            else{
                tex_boss_main_ = frame_boss_right_;
            }

            if (boss_time == 0)
            {
                boss_time = SDL_GetTicks();
            }

            Uint32 boss_currenttime = SDL_GetTicks();
                 boss_srect_.x = (boss_frame_fight) * 180;
            if (boss_currenttime > boss_time + 250)
                {
                    boss_frame_fight = (boss_frame_fight + 1) % 3 ;
                   // boss_srect_.x = boss_frame_fight * 53;
                    boss_time = boss_currenttime;

                    if (SDL_HasIntersection(&boss_dsrect_, &dsrect_) && (boss_frame_fight == 2) && (!is_hitted))
        {

            is_hitted = true;

            playerHealth -= 20;

            if (dsrect_.x > boss_dsrect_.x)
                {
                    tex_main = bidanhphai;
                    SDL_RenderCopy(g_screen, tex_main, NULL, &dsrect_);

                    //status_ = WALK_LEFT;

                    std::cout << "lan 2" ;
                }

            if (dsrect_.x < boss_dsrect_.x)
                {
                    tex_main = bidanhtrai;
                    SDL_RenderCopy(g_screen, tex_main, NULL, &dsrect_);

                    //status_ = WALK_RIGHT;

                    std::cout << "lan 1" ;
                }
        }
        else
        {
            is_hitted = false;
        }
                }
        }
}

        Uint32 currentTime_ = SDL_GetTicks();
        Uint32 deltaTime = currentTime_ - LastTime;
        LastTime = currentTime_;

        if (bossHealth != 0)
        {
            float startX = boss1.x + 146 / 2;
            float startY = boss1.y + 200 / 2;

            checkBullet(bullets, dsrect_, tex_main, bidanhphai, bidanhtrai, main_hit_time,
                        main_is_hitting, chuong_dsrect_, playerHealth);
            boss1.update(deltaTime, bullets, startX, startY, bullet_right, bullet_left, countt);
            updateBullets(bullets);
        }

        float startX1 = plane1.x;
        float startY1 = plane1.y + 169;

        checkBulletofPlane(plane1_bullet, dsrect_, tex_main, bidanhphai, bidanhtrai, main_hit_time,
                           main_is_hitting, status_, playerHealth, bossHealth);
        plane1.update(deltaTime, plane1_bullet, startX1, startY1, bullet_virus, srect_);
        updateBullets_plane(plane1_bullet);

        float startX2 = plane2.x;
        float startY2 = plane2.y + 98;

        checkBulletofPlane(plane2_bullet, dsrect_, tex_main, bidanhphai, bidanhtrai, main_hit_time,
                           main_is_hitting, status_, playerHealth, bossHealth);
        plane2.update(bul_deltaTime, plane1_bullet, startX2, startY2, bullet_jack, srect_);
        updateBullets_plane(plane2_bullet);

        if (countt == 10)
        {
            is_skilling = true;

            boss_time_skill = SDL_GetTicks();
            playerHealth -= 50;

            std::cout << "capnhat";

            countt = 0;

        }

        SDL_SetRenderDrawColor(g_screen, 167, 175, 180, 255);

        SDL_RenderClear(g_screen);
        SDL_RenderCopy(g_screen, texture, NULL, NULL);

        if ((playerHealth != 0))
        {
            if (is_fight)
    SDL_RenderCopy(g_screen, tex_main, &srect_, &dsrect_);

    else if (is_hitted)
    {
        SDL_RenderCopy(g_screen, tex_main, NULL, &dsrect_);
    }
    else if ((!is_skilling) && (!is_kame_) && (!is_fight)) SDL_RenderCopy(g_screen, tex_main, NULL, &dsrect_);

    else if ((is_kame_ ))
    {
        Kamehameha(kame_srect_, is_kame_, kame_time, kame_frame, kame_pos_set,
                   dsrect_, kame_dsrect_, chuong_srect_, chuong_dsrect_, chuong_frame,
                   g_screen, kameha_right, kameha_left, status_, tex_boss_main_, boss_srect_, boss_dsrect_,
                   boss_hitted_left, boss_hitted_right, boss_is_hitted, bossHealth, kameha_sound);
        if (status_ == WALK_RIGHT)
        {
            SDL_RenderCopy(g_screen, thedungchuong_right, &kame_srect_, &kame_dsrect_);
        }
        else SDL_RenderCopy(g_screen, thedungchuong_left, &kame_srect_, &kame_dsrect_);
    }

else {
    // Vẽ sprite bị đánh
    if (boss_dsrect_.x < dsrect_.x)
    {
        SDL_RenderCopy(g_screen, bidanhtrai, NULL, &dsrect_);
    }

    if (boss_dsrect_.x > dsrect_.x)
    {
        SDL_RenderCopy(g_screen, bidanhphai, NULL, &dsrect_);
    }

    Uint32 boss_currentTime = SDL_GetTicks();
    if (boss_currentTime > boss_hit_time + timming)
        main_is_hitting = false; // Khôi phục trạng thái ban đầu
}
        }

//boss dung ultimate
if ((is_skilling) && (bossHealth != 0))
        {
            boss1.BossSkill(boss_skill_rect, chieucuoi, boss_time_skill , skill_frame_, is_skilling,
                            dsrect_, boss_skill_dsrect, skill_pos_set, tex_main, bidanhphai, bidanhtrai,
                            boss_dsrect_, tex_main_left, tex_main_right, playerHealth);

            std::cout << "frame_: " << skill_frame_ << " | is_skilling: " << is_skilling << std::endl;

            SDL_RenderCopy(g_screen, chieucuoi, &boss_skill_rect, &boss_skill_dsrect);

            if (boss_dsrect_.x > dsrect_.x)
            {
                tex_boss_main_ = thuchienskill_boss_left;
            }

            else{
                tex_boss_main_ = thuchienskill_boss_right;
            }

            SDL_RenderCopy(g_screen, tex_boss_main_, NULL, &boss_dsrect_);

            Mix_PlayChannel(-1, boss_skill_sound, 0);
        }
        //

        renderBullets_plane(g_screen, plane1_bullet);
        renderBullets_plane(g_screen, plane2_bullet);
        renderBullets(g_screen, bullets);


//de cho boss di chuyen den nhan vat
if (bossHealth != 0)
{
    if ((!is_hitting) && (!is_skilling))
        {
            SDL_RenderCopy(g_screen, tex_boss_main_, &boss_srect_, &boss_dsrect_);
        }
        else
        {
            SDL_RenderCopy(g_screen, tex_boss_main_, NULL, &boss_dsrect_);

            Uint32 boss_currentTime = SDL_GetTicks();
        if (boss_currentTime > boss_hit_time + timming)
            {
                is_hitting = false;
            }
        }
}

        if (playerHealth < 0)
        {
            playerHealth = 0;
        }
        if (bossHealth < 0)
        {
            bossHealth = 0;
        }
        renderHealthBar(g_screen, dsrect_.x + 20, dsrect_.y - 10, 90, 5, playerHealth, playerMaxHealth);
        renderHealthBar(g_screen, boss_dsrect_.x + 20, boss_dsrect_.y - 10, 120, 5, bossHealth, bossMaxHealth);

        //cho phan end game

        if (playerHealth == 0)
        {
            if (boss_dsrect_.x < dsrect_.x)
            {
                tex_main = player_end_game_right;
            }
            else {
                tex_main = player_end_game_left;
            }

            Uint32 TakeTime = SDL_GetTicks();

            player_srect_end.x = player_end_game * 86;
            if (TakeTime > main_end_game + 350)
            {
                player_end_game++;

                if (player_end_game >= 5)   player_end_game = 4;

                main_end_game = TakeTime;
            }

            SDL_RenderCopy(g_screen, tex_main, &player_srect_end, &dsrect_);
        }

        if (bossHealth == 0)
        {
            if (!boss_dead_direction_locked)
            {
                boss_dead_facing_right = boss_dsrect_.x < dsrect_.x;
                boss_dead_direction_locked = true;
            }

            tex_boss_main_ = boss_dead_facing_right ? boss_end_game_right : boss_end_game_left;

            Uint32 TakeTime = SDL_GetTicks();

            boss_srect_end.x = boss_end_game * 150;
            if (TakeTime > main_end_game + 700)
            {
                boss_end_game++;

                if (boss_end_game >= 4)   boss_end_game = 3;

                main_end_game = TakeTime;
            }

            SDL_RenderCopy(g_screen, tex_boss_main_, &boss_srect_end, &boss_dsrect_);
        }

        SDL_RenderCopy(g_screen, plane1_tex, NULL, &plane1_dsrect);
        SDL_RenderCopy(g_screen, plane2_tex, NULL, &plane2_dsrect);

            Uint32 now = SDL_GetTicks();

            int elapsed = (now - startTime) / 1000;
            int remaining = Timecount - elapsed;

            if (remaining < 0) remaining = 0;

            std::string Timetext = std::to_string(remaining);
            SDL_Surface* Timesurface = TTF_RenderText_Solid(font, Timetext.c_str(), textColor);
            SDL_Texture* Timetexture = SDL_CreateTextureFromSurface(g_screen, Timesurface);

            SDL_Rect Time_dsrect = {0, 911 - Timesurface->h, Timesurface->w, Timesurface->h};

        SDL_RenderCopy(g_screen, Timetexture, NULL, &Time_dsrect);

        if ((remaining != 0) && (bossHealth == 0))
        {
            SDL_RenderCopy(g_screen, textTexture, NULL, &textRect);

            Mix_PlayChannel(-1, winning, 0);
        }
        else if ((remaining == 0) && (bossHealth != 0))
        {
            SDL_RenderCopy(g_screen, textTexture_lose, NULL, &textRect);

            Mix_PlayChannel(-1, afterPlayerDie, 0);
        }
        else if (playerHealth == 0)
        {
            SDL_RenderCopy(g_screen, textTexture_lose, NULL, &textRect);

            Mix_PlayChannel(-1, afterPlayerDie, 0);
        }

        SDL_RenderPresent(g_screen);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(g_screen);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
