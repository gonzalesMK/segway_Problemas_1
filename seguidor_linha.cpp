#include <iostream>
#include "carrinho.h"

int main(){
    float VelE = 0, VelD = 0;
    int contador = 0;

    BlackLib::BlackPWM l_PWM(BlackLib::P9_14);
    BlackLib::BlackPWM r_PWM(BlackLib::P8_13);

    BlackLib::BlackADC l_sensor(BlackLib::AIN2); // ESQUERDA
    BlackLib::BlackADC r_sensor(BlackLib::AIN3); // DIREITA

    carro bbb( &l_PWM, &r_PWM, &l_sensor, &r_sensor);
    colors SE,SD;

    while(1) {

        bbb.ler_sensor(SE,SD);

        if( SE == WHITE && SD == WHITE) {
            bbb.velocidade( VelE, VelD, FRENTE);
        }
        else if( SE == WHITE && SD == BLACK) {
            bbb.velocidade( VelE, VelD, DIREITA);
        }
        else if( SE == BLACK && SD == WHITE) {
            bbb.velocidade( VelE, VelD, ESQUERDA);
        }
        else if( SE == BLACK && SD == BLACK){
            contador ++;
            system( "clear" );
            std::cout << "CONTADOR: " << contador << std::endl;
      switch(contador){
        case 1:
                bbb.fazer_curva(0, 100,800);
                break;
        case 2:
                bbb.fazer_curva(20,80);
                break;
        case 3:
                bbb.fazer_curva(70, 70);  // 50 -> 70
                break;
        case 4:
                bbb.fazer_curva(-10,100);
                break;
        case 5:
                bbb.fazer_curva(80,30);  // 40 -> 30
                break;
        case 6:
                bbb.fazer_curva(80,80,800);
                break;
        case 7:
                bbb.fazer_curva(100,0,900);
                break;
        case 8:
                bbb.fazer_curva(70,30);
                break;
        case 9:
                bbb.fazer_curva(70,90);
                break;
        case 10:
                bbb.fazer_curva(70,70);
                break;
        case 11:
                bbb.fazer_curva(50,90);
                break;
        default:
                contador = 0;
//                bbb.velocidade(0,0);
            }
        }
    }
}
