#include <bangtal.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace bangtal;

void Swap(int i, ObjectPtr piece[16], ScenePtr scene, int pos_X[16], int pos_Y[16], int piece_state[16]);

class Block {

public:


    int block_X, block_Y, state;

    Block(int x, int y, int num) : block_X(x), block_Y(y), state(num) {};

};




int main()
{

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);


    // 장면생성
    auto scene1 = Scene::create("", "images/시작.png");
    auto scene2 = Scene::create("", "images/background.png");

    //  Scene 1: 시작화면
    auto start_button = Object::create("images/start.png", scene1, 520, 300);

    start_button->setScale(2.0f);

    start_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        scene2->enter();

        return true;
        });


    // Scene 2: 퍼즐맞추기 게임


    auto background = Object::create("images/background.png", scene2, 0, 0);

    const int num_of_blocks = 16; //분할 수


    Block blocks_pos[num_of_blocks] = { //분할 된 곳의 좌표

    {0,0,1},
    {0,180,2},
    {0,360,3},
    {0,540,4},

    {320,0,5},
    {320,180,6},
    {320,360,7},
    {320,540,8},

    {640,0,9},
    {640,180,10},
    {640,360,11},
    {640,540,12},

    {960,0,13},
    {960,180,14},
    {960,360,15},
    {960,540,16},
    };
    

 
    int rand_num[num_of_blocks], i, sub_i;

    srand((int)time(0));

    for (i = 0; i < num_of_blocks; i++) {

        rand_num[i] = rand() % num_of_blocks;

        for (sub_i = 0; sub_i < i; sub_i++) {
        
            if (rand_num[i] == rand_num[sub_i]){

                i--;
                break;
            }
        }

    }

    //랜덤 좌표 생성

    ObjectPtr piece[16];

    piece[0] = Object::create("images/null.png", scene2, blocks_pos[rand_num[0]].block_X, blocks_pos[rand_num[0]].block_Y);
    piece[1] = Object::create("images/piece1.png", scene2, blocks_pos[rand_num[1]].block_X, blocks_pos[rand_num[1]].block_Y);
    piece[2] = Object::create("images/piece2.png", scene2, blocks_pos[rand_num[2]].block_X, blocks_pos[rand_num[2]].block_Y);
    piece[3] = Object::create("images/piece3.png", scene2, blocks_pos[rand_num[3]].block_X, blocks_pos[rand_num[3]].block_Y);
    piece[4] = Object::create("images/piece4.png", scene2, blocks_pos[rand_num[4]].block_X, blocks_pos[rand_num[4]].block_Y);

    piece[5] = Object::create("images/piece5.png", scene2, blocks_pos[rand_num[5]].block_X, blocks_pos[rand_num[5]].block_Y);
    piece[6] = Object::create("images/piece6.png", scene2, blocks_pos[rand_num[6]].block_X, blocks_pos[rand_num[6]].block_Y);
    piece[7] = Object::create("images/piece7.png", scene2, blocks_pos[rand_num[7]].block_X, blocks_pos[rand_num[7]].block_Y);
    piece[8] = Object::create("images/piece8.png", scene2, blocks_pos[rand_num[8]].block_X, blocks_pos[rand_num[8]].block_Y);

    piece[9] = Object::create("images/piece9.png", scene2, blocks_pos[rand_num[9]].block_X, blocks_pos[rand_num[9]].block_Y);
    piece[10] = Object::create("images/piece10.png", scene2, blocks_pos[rand_num[10]].block_X, blocks_pos[rand_num[10]].block_Y);
    piece[11] = Object::create("images/piece11.png", scene2, blocks_pos[rand_num[11]].block_X, blocks_pos[rand_num[11]].block_Y);
    piece[12] = Object::create("images/piece12.png", scene2, blocks_pos[rand_num[12]].block_X, blocks_pos[rand_num[12]].block_Y);

    piece[13] = Object::create("images/piece13.png", scene2, blocks_pos[rand_num[13]].block_X, blocks_pos[rand_num[13]].block_Y);
    piece[14] = Object::create("images/piece14.png", scene2, blocks_pos[rand_num[14]].block_X, blocks_pos[rand_num[14]].block_Y);
    piece[15] = Object::create("images/piece15.png", scene2, blocks_pos[rand_num[15]].block_X, blocks_pos[rand_num[15]].block_Y);


    int pos_X[16], pos_Y[16];

    for (int i = 0; i < 16; i++) {
    
        pos_X[i] = blocks_pos[rand_num[i]].block_X;
        pos_Y[i] = blocks_pos[rand_num[i]].block_Y;

    }

    for (int i = 0; i < 16; i++) {

        piece[i]->setScale(0.67f);

    }
    
    // 퍼즐 조각이 맞춰졌는지 유무 확인을 위한 배열 선언 

    int piece_state[16] = {

        blocks_pos[rand_num[0]].state, 
        blocks_pos[rand_num[1]].state,
        blocks_pos[rand_num[2]].state,
        blocks_pos[rand_num[3]].state,
        blocks_pos[rand_num[4]].state,
        blocks_pos[rand_num[5]].state,
        blocks_pos[rand_num[6]].state,
        blocks_pos[rand_num[7]].state,
        blocks_pos[rand_num[8]].state,
        blocks_pos[rand_num[9]].state,
        blocks_pos[rand_num[10]].state,
        blocks_pos[rand_num[11]].state,
        blocks_pos[rand_num[12]].state,
        blocks_pos[rand_num[13]].state,
        blocks_pos[rand_num[14]].state,
        blocks_pos[rand_num[15]].state,
    
    };


    while (true) {
    
        piece[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[1] - 320 == pos_X[0]) && (pos_Y[1] == pos_Y[0])) || ((pos_X[1] + 320 == pos_X[0]) && (pos_Y[1] == pos_Y[0])) || ((pos_X[1] == pos_X[0]) && (pos_Y[1] + 180 == pos_Y[0])) || ((pos_X[1] == pos_X[0]) && (pos_Y[1] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[1]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[1], pos_Y[1]);

                pos_X[0] = pos_X[1];
                pos_Y[0] = pos_Y[1];
                pos_X[1] = temp_X;
                pos_Y[1] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[1];
                piece_state[1] = temp;

            }
            return true;

            });


        piece[2]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[2] - 320 == pos_X[0]) && (pos_Y[2] == pos_Y[0])) || ((pos_X[2] + 320 == pos_X[0]) && (pos_Y[2] == pos_Y[0])) || ((pos_X[2] == pos_X[0]) && (pos_Y[2] + 180 == pos_Y[0])) || ((pos_X[2] == pos_X[0]) && (pos_Y[2] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[2]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[2], pos_Y[2]);

                pos_X[0] = pos_X[2];
                pos_Y[0] = pos_Y[2];
                pos_X[2] = temp_X;
                pos_Y[2] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[2];
                piece_state[2] = temp;

            }
            return true;

            });


        piece[3]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[3] - 320 == pos_X[0]) && (pos_Y[3] == pos_Y[0])) || ((pos_X[3] + 320 == pos_X[0]) && (pos_Y[3] == pos_Y[0])) || ((pos_X[3] == pos_X[0]) && (pos_Y[3] + 180 == pos_Y[0])) || ((pos_X[3] == pos_X[0]) && (pos_Y[3] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[3]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[3], pos_Y[3]);

                pos_X[0] = pos_X[3];
                pos_Y[0] = pos_Y[3];
                pos_X[3] = temp_X;
                pos_Y[3] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[3];
                piece_state[3] = temp;

            }
            return true;

            });


        piece[4]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[4] - 320 == pos_X[0]) && (pos_Y[4] == pos_Y[0])) || ((pos_X[4] + 320 == pos_X[0]) && (pos_Y[4] == pos_Y[0])) || ((pos_X[4] == pos_X[0]) && (pos_Y[4] + 180 == pos_Y[0])) || ((pos_X[4] == pos_X[0]) && (pos_Y[4] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[4]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[4], pos_Y[4]);

                pos_X[0] = pos_X[4];
                pos_Y[0] = pos_Y[4];
                pos_X[4] = temp_X;
                pos_Y[4] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[4];
                piece_state[4] = temp;

            }
            return true;

            });


        piece[5]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[5] - 320 == pos_X[0]) && (pos_Y[5] == pos_Y[0])) || ((pos_X[5] + 320 == pos_X[0]) && (pos_Y[5] == pos_Y[0])) || ((pos_X[5] == pos_X[0]) && (pos_Y[5] + 180 == pos_Y[0])) || ((pos_X[5] == pos_X[0]) && (pos_Y[5] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[5]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[5], pos_Y[5]);

                pos_X[0] = pos_X[5];
                pos_Y[0] = pos_Y[5];
                pos_X[5] = temp_X;
                pos_Y[5] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[5];
                piece_state[5] = temp;

            }
            return true;

            });


        piece[6]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[6] - 320 == pos_X[0]) && (pos_Y[6] == pos_Y[0])) || ((pos_X[6] + 320 == pos_X[0]) && (pos_Y[6] == pos_Y[0])) || ((pos_X[6] == pos_X[0]) && (pos_Y[6] + 180 == pos_Y[0])) || ((pos_X[6] == pos_X[0]) && (pos_Y[6] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[6]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[6], pos_Y[6]);

                pos_X[0] = pos_X[6];
                pos_Y[0] = pos_Y[6];
                pos_X[6] = temp_X;
                pos_Y[6] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[6];
                piece_state[6] = temp;

            }
            return true;

            });


        piece[7]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[7] - 320 == pos_X[0]) && (pos_Y[7] == pos_Y[0])) || ((pos_X[7] + 320 == pos_X[0]) && (pos_Y[7] == pos_Y[0])) || ((pos_X[7] == pos_X[0]) && (pos_Y[7] + 180 == pos_Y[0])) || ((pos_X[7] == pos_X[0]) && (pos_Y[7] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[7]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[7], pos_Y[7]);

                pos_X[0] = pos_X[7];
                pos_Y[0] = pos_Y[7];
                pos_X[7] = temp_X;
                pos_Y[7] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[7];
                piece_state[7] = temp;

            }
            return true;

            });


        piece[8]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[8] - 320 == pos_X[0]) && (pos_Y[8] == pos_Y[0])) || ((pos_X[8] + 320 == pos_X[0]) && (pos_Y[8] == pos_Y[0])) || ((pos_X[8] == pos_X[0]) && (pos_Y[8] + 180 == pos_Y[0])) || ((pos_X[8] == pos_X[0]) && (pos_Y[8] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[8]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[8], pos_Y[8]);

                pos_X[0] = pos_X[8];
                pos_Y[0] = pos_Y[8];
                pos_X[8] = temp_X;
                pos_Y[8] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[8];
                piece_state[8] = temp;

            }
            return true;

            });


        piece[9]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[9] - 320 == pos_X[0]) && (pos_Y[9] == pos_Y[0])) || ((pos_X[9] + 320 == pos_X[0]) && (pos_Y[9] == pos_Y[0])) || ((pos_X[9] == pos_X[0]) && (pos_Y[9] + 180 == pos_Y[0])) || ((pos_X[9] == pos_X[0]) && (pos_Y[9] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[9]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[9], pos_Y[9]);

                pos_X[0] = pos_X[9];
                pos_Y[0] = pos_Y[9];
                pos_X[9] = temp_X;
                pos_Y[9] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[9];
                piece_state[9] = temp;

            }
            return true;

            });


        piece[10]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[10] - 320 == pos_X[0]) && (pos_Y[10] == pos_Y[0])) || ((pos_X[10] + 320 == pos_X[0]) && (pos_Y[10] == pos_Y[0])) || ((pos_X[10] == pos_X[0]) && (pos_Y[10] + 180 == pos_Y[0])) || ((pos_X[10] == pos_X[0]) && (pos_Y[10] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[10]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[10], pos_Y[10]);

                pos_X[0] = pos_X[10];
                pos_Y[0] = pos_Y[10];
                pos_X[10] = temp_X;
                pos_Y[10] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[10];
                piece_state[10] = temp;

            }
            return true;

            });


        piece[11]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[11] - 320 == pos_X[0]) && (pos_Y[11] == pos_Y[0])) || ((pos_X[11] + 320 == pos_X[0]) && (pos_Y[11] == pos_Y[0])) || ((pos_X[11] == pos_X[0]) && (pos_Y[11] + 180 == pos_Y[0])) || ((pos_X[11] == pos_X[0]) && (pos_Y[11] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[11]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[11], pos_Y[11]);

                pos_X[0] = pos_X[11];
                pos_Y[0] = pos_Y[11];
                pos_X[11] = temp_X;
                pos_Y[11] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[11];
                piece_state[11] = temp;

            }
            return true;

            });


        piece[12]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[12] - 320 == pos_X[0]) && (pos_Y[12] == pos_Y[0])) || ((pos_X[12] + 320 == pos_X[0]) && (pos_Y[12] == pos_Y[0])) || ((pos_X[12] == pos_X[0]) && (pos_Y[12] + 180 == pos_Y[0])) || ((pos_X[12] == pos_X[0]) && (pos_Y[12] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[12]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[12], pos_Y[12]);

                pos_X[0] = pos_X[12];
                pos_Y[0] = pos_Y[12];
                pos_X[12] = temp_X;
                pos_Y[12] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[12];
                piece_state[12] = temp;

            }
            return true;

            });


        piece[13]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[13] - 320 == pos_X[0]) && (pos_Y[13] == pos_Y[0])) || ((pos_X[13] + 320 == pos_X[0]) && (pos_Y[13] == pos_Y[0])) || ((pos_X[13] == pos_X[0]) && (pos_Y[13] + 180 == pos_Y[0])) || ((pos_X[13] == pos_X[0]) && (pos_Y[13] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[13]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[13], pos_Y[13]);

                pos_X[0] = pos_X[13];
                pos_Y[0] = pos_Y[13];
                pos_X[13] = temp_X;
                pos_Y[13] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[13];
                piece_state[13] = temp;

            }
            return true;

            });


        piece[14]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[14] - 320 == pos_X[0]) && (pos_Y[14] == pos_Y[0])) || ((pos_X[14] + 320 == pos_X[0]) && (pos_Y[14] == pos_Y[0])) || ((pos_X[14] == pos_X[0]) && (pos_Y[14] + 180 == pos_Y[0])) || ((pos_X[14] == pos_X[0]) && (pos_Y[14] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[14]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[14], pos_Y[14]);

                pos_X[0] = pos_X[14];
                pos_Y[0] = pos_Y[14];
                pos_X[14] = temp_X;
                pos_Y[14] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[14];
                piece_state[14] = temp;

            }
            return true;

            });


        piece[15]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

            int temp;

            int temp_X, temp_Y;

            if (((pos_X[15] - 320 == pos_X[0]) && (pos_Y[15] == pos_Y[0])) || ((pos_X[15] + 320 == pos_X[0]) && (pos_Y[15] == pos_Y[0])) || ((pos_X[15] == pos_X[0]) && (pos_Y[15] + 180 == pos_Y[0])) || ((pos_X[15] == pos_X[0]) && (pos_Y[15] - 180 == pos_Y[0]))) {

                temp_X = pos_X[0];
                temp_Y = pos_Y[0];


                piece[15]->locate(scene2, pos_X[0], pos_Y[0]);
                piece[0]->locate(scene2, pos_X[15], pos_Y[15]);

                pos_X[0] = pos_X[15];
                pos_Y[0] = pos_Y[15];
                pos_X[15] = temp_X;
                pos_Y[15] = temp_Y;

                temp = piece_state[0];
                piece_state[0] = piece_state[15];
                piece_state[15] = temp;

            }
            return true;

            });







        if (piece_state[0] == 16 && piece_state[1] == 1 && piece_state[2] == 2 && piece_state[3] == 3 && piece_state[4] == 4 && piece_state[5] == 5 && piece_state[6] == 6 && piece_state[7] == 7 && piece_state[8] == 8 && piece_state[9] == 9 && piece_state[10] == 10 && piece_state[11] == 11 && piece_state[12] == 12 && piece_state[13] == 13 &&
            piece_state[14] == 14 && piece_state[15] == 15) {
        
            break;
        }
        startGame(scene1);
        return 0;
    }


}

void Swap(int i, ObjectPtr piece[16], ScenePtr scene, int pos_X[16], int pos_Y[16], int piece_state[16]) {

    piece[i]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

        int temp;

        int temp_X, temp_Y;

        if (((pos_X[i] - 320 == pos_X[0]) && (pos_Y[i] == pos_Y[0])) || ((pos_X[i] + 320 == pos_X[0]) && (pos_Y[i] == pos_Y[0])) || ((pos_X[i] == pos_X[0]) && (pos_Y[i] + 180 == pos_Y[0])) || ((pos_X[i] == pos_X[0]) && (pos_Y[i] - 180 == pos_Y[0]))) {

            temp_X = pos_X[0];
            temp_Y = pos_Y[0];


            piece[i]->locate(scene, pos_X[0], pos_Y[0]);
            piece[0]->locate(scene, pos_X[i], pos_Y[i]);

            pos_X[0] = pos_X[i];
            pos_Y[0] = pos_Y[i];
            pos_X[i] = temp_X;
            pos_Y[i] = temp_Y;

            temp = piece_state[0];
            piece_state[0] = piece_state[i];
            piece_state[i] = temp;

        }
        return true;

        });
}

