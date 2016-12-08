#ifndef CARRO_H_
#define CARRO_H_

#include "BlackLib/BlackLib.h"
#include <iostream>


enum colors {BLACK, WHITE};
enum direcao {ESQUERDA, DIREITA, FRENTE};

/// Valores maiores que estes são considerados WHITE ( Há um para cada sensor )
const float LIMITE_DIREITO = 800;
const float LIMITE_ESQUERDO = 550;

// Envia os valores numéricos dos sensores -- deixar true apenas enquanto debugg
const bool ECHO_SENSOR = false;

class carro {
public:
    // Construtor: inicializa os motores
    carro( BlackLib::BlackPWM *left_PWM, BlackLib::BlackPWM *rigth_PWM, BlackLib::BlackADC *left_sensor, BlackLib::BlackADC *rigth_sensor);

    // Função para leitura numérica dos sensores: retorna valores entre 0 e 1800
    void ler_sensor( float &ValorE, float &ValorD);

    // Função que simplifica a leitura dos sensores, depende das variáveis LIMITE_DIREITO e LIMITE_ESQUERDO
    void ler_sensor(colors &ValorE, colors &ValorD);

    // Função que comanda as velocidades nos motores diretamente. Os valores são límitados dentro da função
    void velocidade( float VelE, float VelD);

    // Função que utiliza a velocidade proporcional, deve ser escolhida uma direção (FRENTE,DIREITA,ESQUERDA)
    void velocidade( float &VelE, float &VelD, direcao dir);

    // Função feita para passar em interseções
    void fazer_curva(float VelE , float VelD, int time_wait_ms = 500);

private:
    // Um para cada motor
    BlackLib::BlackPWM *l_PWM, *r_PWM;
    // Um para cada sensor
    BlackLib::BlackADC *l_sensor, *r_sensor;
};

#endif /* BLACKCORE_H_ */
