#include "raylib.h"

#define GRAVIDADE 20

const int alturaTela = 900;
const int larguraTela = 1200;
const int frameRate = 60;

// Definicao do jogador
typedef struct{
    Vector2 pos;             //posicao
    Vector2 velocidade;
    Vector2 aceleracao;
    Vector2 tamanho;
    bool podePular;
}Jogador;

bool jogadorColidiu(Jogador jogador, Rectangle chao){
    //retangulo na mesma posicao do jogador
    Rectangle jogadorRec = {
        jogador.pos.x,
        jogador.pos.y,
        jogador.tamanho.x,
        jogador.tamanho.y};

    bool colidiu = CheckCollisionRecs(jogadorRec, chao);

    // repare que, caso seu jogo possua mais de um objeto com colisao,
    // e necessario checar se o jogador colidiu com todos eles.

    return colidiu;
}


void andaJogador(Jogador* jogador){

    // e possivel utilizar a aceleracao para tornar
    // o movimento lateral do jogador mais suave

    //atualiza a velocidade do jogador
    if(IsKeyDown(KEY_A))
        jogador->velocidade.x = -5;

    //atualiza a velocidade do jogador
    else if(IsKeyDown(KEY_D))
        jogador->velocidade.x = 5;

    //diminui a velocidade do jogador, faz ele
    //parar de se mover caso nenhuma tecla esteja sendo apertada
    jogador->velocidade.x /=1.2;

    //atualiza a posicao do jogador
    jogador->pos.x += jogador->velocidade.x;
}

void desenhaJogador(Jogador jogador){

    //desenha um retangulo amarelo na posicao e com o tamanho do jogador
    DrawRectangleV(
       jogador.pos,
       jogador.tamanho,
       YELLOW
       );
}

void pulaJogador(Jogador* jogador, Rectangle chao){

    //atualiza a velocidade vertical do jogador
    jogador->velocidade.y += GRAVIDADE * GetFrameTime();

    //checa se o jogador colidiu com o chao.
    //se o seu jogo tiver mais de um obstaculo,
    //sera necessario checar se o jogador colidiu
    //com cada um deles

    if(jogadorColidiu(*jogador, chao)){
        jogador->pos.y = chao.y - jogador->tamanho.y; //retorna o jogador para acima do chao
        jogador->velocidade.y = 0;                    //zera a velociade vertical do jogador
        jogador->podePular = true;                    //pode pular novamente
    }

    if(IsKeyPressed(KEY_SPACE) && jogador->podePular){
        //faz o jogador pular simplesmente alteranto sua velocidade vertical.
        //jogador nao pode pular enquanto nao colidir com o chao
        jogador->velocidade.y = -10;
        jogador->podePular = false;
    }

    //atualiza a posicao do jogador
    jogador->pos.y += jogador->velocidade.y;

}

void inicializaJogador(Jogador* jogador){

    //inicializa as variaveis do jogador
    jogador->velocidade = (Vector2){1, 1};
    jogador->tamanho = (Vector2) {50, 50};
    jogador->pos = (Vector2) {50, 550};
    jogador->aceleracao = (Vector2) {0, 0};
    jogador->podePular = true;
}

int main(void)
{

    //ativa o vsync (recomendavel)
    SetConfigFlags(FLAG_VSYNC_HINT);

    Jogador jogador1;

    inicializaJogador(&jogador1);

    Rectangle chao = (Rectangle){0, 600, larguraTela, alturaTela - 300};

    InitWindow(larguraTela, alturaTela, "Jump");
    SetTargetFPS(frameRate);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKBLUE);        //desenha o fundo
        DrawRectangleRec(chao, BLUE);       //desenha o chao

        desenhaJogador(jogador1);
        andaJogador(&jogador1);             //faz o jogador se movimentar lateralmente
        pulaJogador(&jogador1, chao);       //faz o jogador pular

        EndDrawing();
    }

    return 0;
}
