#include "mbed.h"
#include "FastAnalogIn.h"
// ADICIONAR UMA FITA NAS VIRADAS GRANDES PARA O CARRINHO MUDAR BSTT DE VELOCIDADE!

// LED1 = mbed
// LED3 = LPC1
// > 0.03 e branco

PwmOut servod(p22), servoe(p21);// pinos setados para saída em PWM para controle do Servo.
FastAnalogIn sensor_e(p19), sensor_d(p18);// pinos setados para conversão interna do ADC.
DigitalOut L1(LED1),L2(LED2),L3(LED3),L4(LED4);// leds apenas para indicar movimento.

// Colors representam as cores da linha: branco ou preto
enum colors {BLACK, WHITE} SE, SD;
// Direçao representa as possiveis movimentacoes do carrinho
enum direcao {ESQUERDA, DIREITA, FRENTE};
// Essa funçao gera a velocidade proporcinal
void velocidade( float &ValorE, float &ValorD, direcao dir);
// Essa foi usada para ja enviar os valores absolutos
void velocidade(float ValorE, float ValorD);
// Funçao para ligar os leds
void led( int l1, int l2, int l3, int l4);
// Funcao que faz a tomada de decisao da curva
void fazer_curva(int &contador);
// Funçao que mante o carro fazendo curva
void fazendo_curva(float ValorE , float ValorD); //, int time = 300);

//Serial pc(*USBTX, USBRX, 9600); // tx, rx
// Usar: pc.printf( " SE : %f | SD: %f \n", ValorE, ValorD);

int main(){
    float ValorE = 0, ValorD = 0;
    int contador = 0;

    servod.period(0.030);
    servoe.period(0.030);

    while(1) {

        SE = sensor_e.read() >= 0.030 ? WHITE : BLACK ;
        SD = sensor_d.read() >= 0.030 ? WHITE : BLACK ;

        if( SE == WHITE && SD == WHITE) {
            led(1,0,0,0);
            velocidade( ValorE, ValorD, FRENTE);
        }
        else if( SE == WHITE && SD == BLACK) {
            led(0,1,0,0);
            velocidade( ValorE, ValorD, DIREITA);
        }
        else if( SE == BLACK && SD == WHITE) {
            led(0,0,1,0);
            velocidade( ValorE, ValorD, ESQUERDA);
        }
        else if( SE == BLACK && SD == BLACK){
            led(1,1,1,1);
            fazer_curva(contador);

            contador ++;
        }
    }
}


void velocidade(float ValorE, float ValorD){
     // Testando os valores teto da velocidade
        if(ValorD > 90.0) {ValorD = 90.0;}
        if(ValorE > 90.0) {ValorE = 90.0;}
        if(ValorD < 0.0) {ValorD = 0.0;}
        if(ValorE < 0.0) {ValorE = 0.0;}
    // Envia o sinal
        servod.pulsewidth(-ValorD/100.0 * 0.0005 + 0.00138);
        servoe.pulsewidth( ValorE/100.0 * 0.0005 + 0.00144);
        // 0.00194 esquerda RAPIDO
        // 0.00144 esquerda PARA
        // 0.00094 direita RAPIDO
        // 0.00138 direita PARA
}

void velocidade( float &ValorE, float &ValorD, direcao dir){
    float inc = 10;
    switch(dir){
        // D:70 / E:30 ficou bom
        case(FRENTE):
            ValorD = 60;
            ValorE = 90;
            break;

        case(DIREITA):
            ValorD = ValorD - inc * 5.0 ;
            ValorE = ValorE + inc;
            break;
        case(ESQUERDA):
            ValorD = ValorD + inc;
            ValorE = ValorE - inc * 5.0;
            break;
    }
    velocidade(ValorE, ValorD);
}

void led( int l1, int l2, int l3, int l4){
    L1 = l1;
    L2 = l2;
    L3 = l3;
    L4 = l4;
}

void fazendo_curva(float ValorE , float ValorD){ //, int time){
    colors SD,SE;
    SD = SE = BLACK;
    velocidade( ValorE, ValorD);
    wait_us(100000);
    while( SD == BLACK && SE == BLACK){
        wait_ms(5);
        SE = sensor_e.read() >= 0.030 ? WHITE : BLACK ;
        SD = sensor_d.read() >= 0.030 ? WHITE : BLACK ;
    }
}


void fazer_curva( int &contador){
      switch(contador){
        case 0:
                fazendo_curva(0, 100);
                break;
        case 1:
                fazendo_curva(40,62);
                break;
        case 2:
                fazendo_curva(70, 50);
                break;
        case 12:
                fazendo_curva(0,100);
                break;
        case 3:
                fazendo_curva(30,40);
                break;
        case 4:
                fazendo_curva(23,2);
                break;
        case 5:
                fazendo_curva(33,0);
                break;
        case 6:
                fazendo_curva(23,10);
                break;
        case 7:
                fazendo_curva(10,25);
                break;
        case 8:
                fazendo_curva(10,13);
                break;
        case 9:
                fazendo_curva(0,81);
                break;
        case 10:
                fazendo_curva(0,100);
                break;
        case 11:
                fazendo_curva(10,13);
                break;
    }

}
