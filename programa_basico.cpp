#include "raylib.h"

const int screen_width = 1200; // Largura da tela
const int screen_height = 900; // Altura da tela
const int frame_rate = 60;     // FPS

int main(void){

    SetTargetFPS(frame_rate);                           // Determina o FPS
    InitWindow(screen_width, screen_height, "Name");    // Inicializa a tela, tudo que envolver gráficos deve ser feito após essa função.

    //------------------------------------------
    // CARREGUE SEUS GRÁFICOS AQUI (LoadTexture)
    //------------------------------------------

    while(!WindowShouldClose()){    // Executa enquanto a janela não for fechada

        //-----------------------------
        // ATUALIZE SUAS VARIÁVEIS AQUI
        //-----------------------------

        BeginDrawing();             // Comando que indica o início de geração de um quadro.
        ClearBackground(RAYWHITE);  // Cria um "buffer", serve para não deixar resquícios do frame anterior na tela. SEMPRE que for desenhar algo na tela utilize esta função logo após o BeginDrawing

        //-----------------------------
        // DESENHE SEU JOGO AQUI
        //-----------------------------

        EndDrawing(); // Indica o fim de geração do frame.

    }

    return 0;
}