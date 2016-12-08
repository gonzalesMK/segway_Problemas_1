#include "carrinho.h"

carro::carro( BlackLib::BlackPWM *left_PWM, BlackLib::BlackPWM *rigth_PWM, BlackLib::BlackADC *left_sensor, BlackLib::BlackADC *rigth_sensor){
    l_PWM = left_PWM;
    r_PWM = rigth_PWM;

    l_sensor = left_sensor;
    r_sensor = rigth_sensor;

    /// Inicialização dos motores


    bool flag_l = l_PWM->setPeriodTime(100000);
    bool flag_r = r_PWM->setPeriodTime(100000);
    if(!flag_l) std::cout << "erro no motor Esquerdo" << std::endl;
    if(!flag_r) std::cout << "erro no motor Direito" << std::endl;

    flag_l = l_PWM->setDutyPercent(0.0);
    flag_r = r_PWM->setDutyPercent(0.0);
    if(!flag_l) std::cout << "erro no motor Esquerdo" << std::endl;
    if(!flag_r) std::cout << "erro no motor Direito" << std::endl;

    sleep(1);
    //////////////////////////////
    l_PWM->setPeriodTime(30000, BlackLib::microsecond);
    r_PWM->setPeriodTime(30000, BlackLib::microsecond);

    l_PWM->setRunState(BlackLib::run);
    l_PWM->setPolarity(BlackLib::reverse);

    r_PWM->setRunState(BlackLib::run);
    r_PWM->setPolarity(BlackLib::reverse);
}


void carro::velocidade( float VelE, float VelD){
  // Testando os valores teto da velocidade
   if(VelD > 100.0){
//	std::cout << "Velocidade Direita Acima do limite!" << std::endl;	
	VelD = 100.0;
   }
   if(VelE > 100.0) {
//	std::cout << "Velocidade Esquerda Acima do limite!" << std::endl;	
	VelE = 100.0;
    }
   if(VelD < -10.0) {VelD = -10.0;}
   if(VelE < -10.0) {VelE = -10.0;}
	
   bool flag_r,flag_l;

   flag_l = l_PWM->setLoadRatioTime( VelE/100*200 + 1400, BlackLib::microsecond); 
   flag_r = r_PWM->setLoadRatioTime(-VelD/100*200 + 1440 , BlackLib::microsecond); 

   if(!flag_l) std::cout << "erro no motor Esquerdo" << std::endl;
   if(!flag_r) std::cout << "erro no motor Direito" << std::endl;
}

void carro::velocidade( float &VelE, float &VelD, direcao dir){
    float inc = 5;
    switch(dir){
        case(FRENTE):
            VelD = 50;
            VelE = 50;
            break;
        case(DIREITA):
            VelD = VelD - inc * 5.0 ;
            VelE = VelE + inc;
            break;
        case(ESQUERDA):
            VelD = VelD + inc;
            VelE = VelE - inc * 5.0;
            break;
    }
    velocidade(VelE, VelD);
}

void carro::ler_sensor(float &ValorE, float &ValorD){
    // Os valores dos sensores variam de 0 a 1800
    ValorE = l_sensor->getNumericValue();
    ValorD = r_sensor->getNumericValue();
    if(ECHO_SENSOR){
	    std::cout << "ValorE: " << ValorE << "\t";
	    std::cout << "ValorD: " << ValorD << std::endl;
    }
}

void carro::ler_sensor(colors &ValorE, colors &ValorD){
    ValorE =  l_sensor->getNumericValue() >= LIMITE_ESQUERDO ? WHITE : BLACK ;
    ValorD =  r_sensor->getNumericValue() >= LIMITE_DIREITO  ? WHITE : BLACK ;
}

void carro::fazer_curva(float VelE , float VelD, int time_wait_ms){
    colors SD,SE;
    SD = SE = BLACK;
    velocidade( VelE, VelD);
    usleep(time_wait_ms*1000);
    while( SD == BLACK && SE == BLACK){
        usleep(5*1000);
        ler_sensor( SD, SE);
    }
}

