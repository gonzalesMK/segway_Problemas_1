BL=BlackLib
SOURCE= $(BL)/BlackADC/BlackADC.cpp $(BL)/BlackMutex/BlackMutex.cpp $(BL)/BlackPWM/BlackPWM.cpp carrinho.cpp $(BL)/BlackCore.cpp $(BL)/BlackDirectory/BlackDirectory.cpp

make:
	g++ -IBlackLib -o seguidor_linha seguidor_linha.cpp $(SOURCE) -pthread -std=c++0x
