# Um Breve tutorial sobre Raylib

## Disclaimer

Esse tutorial abrange a parte mais básica do funcionamento da biblioteca Raylib. Para fins didáticos, muitas explicações técnicas estão simplificadas e podem não estar totalmente corretas, mas são úteis para quem está aprendendo a utilizar a biblioteca. Para ter mais detalhes, acesse o site da Raylib e leia a "documentação oficial".

Esse tutorial foi criado tendo em mente auxiliar alunos que estejam cursando a disciplina de Algoritmos e Programação na UFRGS, considerando os requisitos para implementar o trabalho final, mas pode ser consultado por qualquer um que deseje aprender a utilizar a biblioteca.

Muito do que está neste documento pode ser encontrado no [cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html) e em [exemplos](https://www.raylib.com/examples.html) no website oficial da biblioteca.

**Consulte a cheatsheet**. É a maneira mais fácil de encontrar a função que você está procurando.

## Funcionamento de um jogo

Antes de conhecer as funcionalidades da Raylib, é importante ter uma noção básica do funcionamento de um jogo.

Mesmo quando se utiliza uma engine sofisticada para o desenvolvimento, por mais que ela deixe um nível maior de abstrações e ferramentas à disposição do programador, a "lógica" de funcionamento do game continua a mesma: Tudo ocorre dentro de um loop. A Raylib também funciona dessa maneira.

Em qualquer [exemplo](programa_basico.cpp) de jogo que utilize a Raylib, você poderá ver a seguinte linha de código: `while(!WindowShouldClose())`, que define o loop principal do programa. Toda atualização de variável e desenho na tela é feito dentro deste laço, frame a frame.

Repare que o número de vezes que esse loop for executado por segundo **corresponde à quantidade de quadros por segundo do jogo.** Isso cria alguns problemas, pois a velocidade com a qual os eventos do programa acontecem irá estar diretamente relacionado com o FPS, que irá variar, não apenas entre computadores diferentes, mas também entre estágios diferentes do jogo. Esse é o motivo pelo qual cada fase do jogo [space invaders](https://www.youtube.com/watch?v=MU4psw3ccUI) fica progressivamente mais rápida, ao longo que o número de elementos gráficos na tela diminuem. Também é o motivo da existência do [botão turbo](https://canaltech.com.br/desktop/para-que-servia-o-botao-turbo-nos-computadores-antigos-153655/), encontrado em muitos PCs antigos.

Existem duas maneiras de evitar esse problema na Raylib. Uma possibilidade **fortemente recomendada se você não tem experiência com a biblioteca** é simplesmente limitar a quantidade de FPS com a função ``SetTargetFPS()`` (preferencialmente a 60 quadros por segundo). Outra possibilidade, que permite um desempenho muito melhor, é utilizar a função `GetFrameTime()`, e "padronizar" o movimento e as atualizações de variáveis independentemente do FPS. Exemplos de como fazer isso são encontrados na sessão de exemplos do site da Raylib e podem ser difíceis de implementar.

Enfim, vamos ao que interessa.

## Funções básicas

Estas são as funções que você precisa conhecer para desenvolver qualquer programa utilizando Raylib. Veja um exemplo da implementação delas no arquivo [programa_basico.cpp](programa_basico.cpp).

* ```InitWindow(int width, int height, char[n] name);```

  * <i>width</i>  - Largura da tela.
  * <i>height</i> - Altura da tela.
  * <i>name</i> - Nome da janela.

  Essa função é responsável por inicializar (e criar) a tela do seu jogo. Tudo que for relacionado a carregamento e geração de texturas e frames deve ficar depois da chamada dela. **Ela deve ser chamada apenas uma vez no seu programa**.

* ```SetTargetFPS(int frameRate);```
  * <i>frameRate</i> - Quantidade de quadros por segundo (fps) do jogo.

  Essa função determina quantas vezes o loop principal do seu programa (ver [programa_basico.cpp]) será executado por segundo. É comum limitar a quantidade de FPS em 60, mas teoricamente qualquer valor é possível.
  Repare que tudo que estiver dentro do seu loop principal será executado <i>frameRate</i> vezes por segundo, **inclusive suas atualizações de variáveis.** Pense em como isso afetará o funcionamento do seu jogo.

* ` int WindowShouldClose(void); `

    Essa função retorna um booleano (0 ou 1), indicando quando a janela do seu jogo deve ficar aberta. Utilize-a como parâmetro do loop principal do seu jogo:

    ```c
    While(!WindowShouldClose()){
        //execução do jogo.
    }
    ```

    Veja um exemplo concreto em [programa_basico.cpp](programa_basico.cpp).

* `BeginDrawing(void);`

    Essa função indica onde o frame começa a ser gerado. Tudo que gera desenhos na tela deve ficar entre ela e a chamada da função `EndDrawing` (ver abaixo).

* `ClearBackground(Color color);`

  * color - cor do <i> frame buffer </i>

  Essa função é normalmente chamada logo após a `BeginDrawing()`. Ela cria a "base" do novo frame, cobrindo o anterior com a cor color. Normalmente utiliza-se a cor `RAYWHITE`. **Se a tela do seu jogo está piscando, ou apresentando algum tipo de artefato, é provável que você tenha esquecido de chamar esta função.**
    <sub> *A Struct Color abordada mais à frente no tutorial.<sub>

* `EndDrawing(void);`

    Essa função indica onde o frame termina de ser gerado. Tudo que gera desenhos na tela deve ficar acima dela e abaixo da chamada da função ```BeginDrawing()``` (ver acima).

## Principais structs da Raylib

A biblioteca Raylib tem algumas structs muito úteis, que quase sempre serão utilizadas na criação do seu jogo. Aqui estão listadas algumas.

* `(Color) {int R, int G, int B, int alpha};`

     Essa estrutura é utilizada para representar cores na Raylib. Os valores R, G, B significam, respectivamente, a quantidade de vermelho, verde, e azul da cor. O valor alpha determina a transparência da cor. Todos esses valores variam de **0 a 255**.

  * A biblioteca vem por padrão com alguns <i>defines</i> de cores. Consultar [cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html).

* `(Vector2) {double x, double y};`

    Essa é uma das structs mais úteis da biblioteca. É uma tupla de 2 valores double e é geralmente utilizada para representar coordenadas e dimensões de formas geométricas.

* `(Rectangle) {float x, float y, fload width, float height};`

    Essa struct é utilizada para representar... retângulos. Os valores x e y são suas coordenadas, width é a sua largura e height a sua altura. Repare que as coordenadas indicam o **canto superior esquerdo** do retângulo. Essa struct serve para para detecção de colisões e para desenhar formas retangulares na tela.

* `(Camera2D){ Vector2 offset, Vector2 target, float rotation, float zoom};`

    Essa struct é utilizada para modificar o espaço da tela que será mostrado a cada frame.
  * <i>target</i> - Ponto onde a câmera estará.
  * <i>offset</i> - Deslocamento da câmera em relação ao alvo.
  * <i>rotation</i> - Rotação da câmera.
  * <i>zoom</i> - Zoom da câmera.

    Repare que, caso você deseje que a câmera siga um objeto que se move, como um jogador, é necessário atualizar o target a cada frame.

* `Texture2D`

    Essa estrutura é utilizada para representar texturas dentro do jogo. (Ver adiante)

## Desenhando na tela

Há várias funções que que podem ser utilizadas para gerar imagens na tela, mas, antes, é necessário entender como funciona a janela do seu jogo.

Em primeiro lugar, repare que cada ponto da tela pode ser representado por uma `struct Vector2`, definida por `(Vector2) {float x, float y}`

Algo que pode gerar uma certa confusão é o comportamento das coordenadas da tela. Repare que **as coordenadas representam a distância horizontais e verticais de um ponto até a origem da tela, respectivamente**.

Sendo assim, **a coordenada x cresce para a direita e a coordenada y cresce para baixo**. Além disso, o canto superior esquerdo da tela (origem) tem coordenadas que correspondem a `(Vector2) {0, 0}`. O canto inferior direito da tela pode ser representado por `(Vector2) {GetScreenWidth(), GetScreenHeight()}`.

Pense em como isso afetará suas implementações. Por exemplo, para fazer o jogador pular para cima, é intuitivo pensar que deve-se aumentar sua coordenada y, mas o correto é diminuí-la, já que, ao pular para cima, ele estará se aproximando da origem, ou seja, à coordenada cujo valor de y é 0.

## Funções de desenho

* `DrawRectangle(float x, float y, float width, float height, Color color);`

    Essa função desenha um retângulo de dimensão  <i> width x height </i>, nas coordenadas <i> x, y</i>, de cor <i> color </i>. Ela tem diversas variações, como:

  * `DrawRectangleV(Vector2 position, Vector2 size, Color color);`

  * `DrawRectangleRec(Rectangle rec, Color color);`

  * `DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);`

    Esta versão permite rotacionar o retângulo <i> rec </i> em torno das coordenadas <i> origin</i>. Se <i> origin </i> for o centro do retangulo, por exemplo, é possível fazer ele girar em torno de si.

* `Texture2D textura = LoadTexture(char path[n]);`

    Essa função não serve propriamente para desenhar na tela, mas ela é utilizada para carregar as texturas do seu jogo na memória de vídeo do computador. Repare que ela retorna um valor Texture2D, que deve ser armazenado em uma variável para que possa ser utilizada. <i>path</i> é o caminho relativo no seu computador do executável de seu programa até o arquivo da textura.  Não esqueça de remover as texturas da memória com `UnloadTexture(Texture2D texture);` no final do programa!

    <sub> Repare que para projetos mais complexos existem formas mais apropriadas de realizar o carregamento de texturas. </sub>

* `DrawTexture(Texture2D texture, int x, int y, Color tint);`

    Desenha uma texture <i>texture</i> nas coordenadas <i>x, y</i> com cor <i>tint</i> (utiliza-se a cor `RAYWHITE` para manter as cores da imagem, as demais cores podem ser utilizadas para colorir texturas que estão em escala de cinza). Existem algumas variações:

  * `DrawTextureV(Texture2D texture, Vector2 position, Color tint);`

  * `DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);`

    Esta função é similar à função `DrawRectanglePro`, mas para texturas. <i>source</i> é o "recorte" utilizado do arquivo de textura (se não souber do que se trata utilize um retângulo com origem {0, 0} e dimensões iguais ao tamanho da imagem ), <i>origin</i> determina à partir de que coordenadas a texutra será desenhada **em relação ao retângulo <i>dest</i>**. Pode ser complexo entender seu funcionamento.

    É possível visualizar o funcionamento da função [neste link](https://tradam.itch.io/raylib-drawtexturepro-interactive-demo).

* `DrawRectangleLines(int posX, int posY, int width, int height, Color color);`

    Essa função desenha contornos de retângulos.

* `DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);`

    Essa função desenha triângulos, utilizando as coordenadas de seus vértices.

* `DrawText(const char *text, int posX, int posY, int fontSize, Color color);`

    Desenha o texto correspondente ao array de chars <i> text</i>, utilizando a fonte padrão do raylib no tamanho <i>fontSize</i>. Você também pode utilizar:

  * `int MeasureText(char text[n], int fontSize)`;

    Essa função retorna o tamanho, em pixels, do texto <i>text</i>, com tamanho de fonte <i>fontSize</i>. **Essa função é muito útil para centralizar textos**.

    Obs.: Repare que a altura do texto é igual ao tamanho da fonte <i>fontSize</i>.

<br/>

Há diversas outras funções de desenho de formas de fácil de utilização. Consulte o [cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html). (procure por funções que comecem com "Draw").

## Detecção de colisões

As funções de detecção de colisões têm um funcionamento simples. Elas apenas testam se há uma interseção entre a área de dois objetos. No Raylib, esses objetos podem ser retângulos (`Rectangle`), pontos (`Vector2`), entre outros.

Em seus primeiros projetos, a detecção e tratamento de colisões costuma ser a parte mais dfícil de implementar. A biblioteca Raylib tem diversas funções para deteção de colisões entre formas diferentes, mas todas seguem o mesmo formato:

* `bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);`

    Essa função serve para detectar uma colisão entre dois retângulos, ou seja, se há uma interseção entre a área ocupada pelos dois objetos.

* `bool CheckCollisionPointRec(Vector2 point, Rectangle rec);`

    Essa função faz a mesma coisa, mas para um ponto e um retângulo.

Repare que se há mais de um objeto com colisões no cenário do seu jogo, você terá que chamar essa função para cada um deles, passando-os como argumento, por exemplo:

```pseudo
para cada obstaculo, faça:
    se (CheckCollisionRecs(obstaculo, jogador)){
        .
        .
        .
    }
```

Consulte o [cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html). A biblioteca possui diversas funções para detecção de colisões entre outras formas (círculos, linhas, triângulos, etc.).

## Exemplos de programas

* [programa_basico.cpp](programa_basico.cpp) é um programa que demonstra como utilizar as funções básicas da biblioteca. Você pode usá-lo como base para iniciar seu projeto.

* [menu.cpp](menu.cpp) é um exemplo de criação de um menu para o seu jogo.

* [pulo.c](pulo.c) demonstra uma maneira de implementar a movimentação lateral e os pulos do jogador.

* Muitos outros exemplos podem ser encontrados no [site de exemplos](https://www.raylib.com/examples.html).
