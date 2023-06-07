#ifndef SPRITES
#define SPRITES

#include <stdint.h>

typedef uint8_t sprite[3];

void copiar_sprite(sprite * s_out, const sprite * s_in){
  for(uint8_t k = 0; k < 3; k++){
    (*s_out)[k] = (*s_in)[k];
  }
}

const uint8_t PANTALLA_INICIO[32] = {
    //Dibujo inicial 8x32
    0b01111110,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00000000,
    0b00111100,
    0b00100000,
    0b00111100,

    0b00100000,
    0b00111100,
    0b00000000,
    0b01111110,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00000000,

    0b00111100,
    0b00100100,
    0b00111100,
    0b00111000,
    0b00101000,
    0b00000000,
    0b00111100,
    0b00011000,

    0b00011000,
    0b00111100,
    0b00000000,
    0b00111000,
    0b01000100,
    0b00010000,
    0b01000100,
    0b00111000,
};
// const uint8_t PANTALLA_INICIO[32] = {
//     //Dibujo inicial 8x32
//     0b01111110,
//     0b00011000,
//     0b00011000,
//     0b00011000,
//     0b00000000,
//     0b01111110,
//     0b01100000,
//     0b01111110,

//     0b01100000,
//     0b01111110,
//     0b00000000,
//     0b01111110,
//     0b00011000,
//     0b00011000,
//     0b00011000,
//     0b00000000,

//     0b01111110,
//     0b01100110,
//     0b01111110,
//     0b01111000,
//     0b01101100,
//     0b00000000,
//     0b01111110,
//     0b00011000,

//     0b00011000,
//     0b01111110,
//     0b00000000,
//     0b01111100,
//     0b00110010,
//     0b00011000,
//     0b01001100,
//     0b00111110,
// };


const uint8_t CUADRADO_JUEGO[8] = {
    0b11111111,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b11111111,
};

const sprite PIEZAS[4][7] = {
    { // orientacion 0
        { // I 
            0b00001000,
            0b00001000,
            0b00001000,
        },
        { // J
            0b00001000,
            0b00001000,
            0b00011000,
        },
        { // L
            0b00010000,
            0b00010000,
            0b00011000,
        },
        { // O
            0b00011000,
            0b00011000,
            0b00000000,
        },
        { // T
            0b00000000,
            0b00011100,
            0b00001000,
        },
        { // S
            0b00010000,
            0b00011000,
            0b00001000,
        },
        { // Z 
            0b00001000,
            0b00011000,
            0b00010000,
        }
    },
    { // orientacion 1
        { // I 
            0b00000000,
            0b00011100,
            0b00000000,
        },
        { // J
            0b00010000,
            0b00011100,
            0b00000000,
        },
        { // L
            0b00000000,
            0b00111000,
            0b00100000,
        },
        { // O
            0b00011000,
            0b00011000,
            0b00000000,
        },
        { // T
            0b00001000,
            0b00011000,
            0b00001000,
        },
        { // S
            0b00001100,
            0b00011000,
            0b00000000,
        },
        { // Z 
            0b00011000,
            0b00001100,
            0b00000000,
        }
    },
    { // orientacion 2
        { // I 
            0b00001000,
            0b00001000,
            0b00001000,
        },
        { // J
            0b00001100,
            0b00001000,
            0b00001000,
        },
        { // L
            0b00110000,
            0b00010000,
            0b00010000,
        },
        { // O
            0b00011000,
            0b00011000,
            0b00000000,
        },
        { // T
            0b00001000,
            0b00011100,
            0b00000000,
        },
        { // S
            0b00001000,
            0b00001100,
            0b00000100,
        },
        { // Z 
            0b00000100,
            0b00001100,
            0b00001000,
        }
    },
    { // orientacion 3
        { // I 
            0b00000000,
            0b00011100,
            0b00000000,
        },
        { // J
            0b00000000,
            0b00011100,
            0b00000100,
        },
        { // L
            0b00001000,
            0b00111000,
            0b00000000,
        },
        { // O
            0b00011000,
            0b00011000,
            0b00000000,
        },
        { // T
            0b00001000,
            0b00001100,
            0b00001000,
        },
        { // S
            0b00000000,
            0b00001100,
            0b00011000,
        },
        { // Z 
            0b00000000,
            0b00011000,
            0b00001100,
        }
    }
};

#endif