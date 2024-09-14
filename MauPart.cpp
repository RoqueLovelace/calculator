#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <deque>
//PEDMAS (Parentesis, Exponentes, Division, Multiplicacion, Adicion, Sustraccion)
struct sOperator
{
	uint8_t precedence = 0; // la prioridad de la operacion
	uint8_t arguments = 0; // los argumentos que toma el operado. p.e: + toma 2 (4+7), ! toma 1 (5!) 
};

struct sSymbol { // almacena el valor en formato texto y se clasifica en un tipo y detalla sus argumentos y precedencias
	std::string symbol = "";

	enum class Type : uint8_t {
		Unknown,
		Literal_Numeric,
		Operator,
		Parenthesis_Open,
		Parenthesis_Close
	} type = Type::Unknown;

	sOperator op;
};

double SolveExpression(std::string& sExpression) {
  double res = 0.0;
	std::deque<sSymbol> superSExpresion; // se inicializa la variable que contendra la expresion que toma mas de un digito
	std::unordered_map<char, sOperator> mapOps; // un unordered_map contiene key-value y los datos no se ordenan de alguna forma particular
	mapOps['^'] = { 5,2 };
	mapOps['/'] = { 4,2 };
	mapOps['*'] = { 3,2 };
	mapOps['+'] = { 2,2 };
	mapOps['-'] = { 2,2 };
  std::string functionsSymbol = "sctzyxrle!";


    /*region TODO TOMAR NUMEROS DE MAS DE UN DIGITO*/
	{

		std::deque<sSymbol> stackAuxiliar; //para almacenar los operadores traidos de identificar numeros de más de 2 digitos
		std::string variableAuxiliar = ""; //Para los numeros

		bool esNumero = false;
		sSymbol simbolo;

		for (char caracter : sExpression) {
			if (std::isdigit(caracter)) {
				esNumero = true;
				variableAuxiliar += caracter;
			}
			else if (!(std::isdigit(caracter))) {
				esNumero = false;
				variableAuxiliar += ","; //Cada una de estas comas representan un operador en específico.

				if (caracter == '(') {
					simbolo.symbol = caracter;
					simbolo.type = sSymbol::Type::Parenthesis_Open;
					stackAuxiliar.push_back({ simbolo.symbol, simbolo.type });
				}
				else if (caracter == ')') {
					simbolo.symbol = caracter;
					simbolo.type = sSymbol::Type::Parenthesis_Close;
					stackAuxiliar.push_back({ simbolo.symbol, simbolo.type });
				}
				else if (caracter == '*' || caracter == '/' || caracter == '+' || caracter == '-') {
					simbolo.symbol = caracter;
					simbolo.type = sSymbol::Type::Operator;
					simbolo.op = mapOps[caracter];
					stackAuxiliar.push_back({ simbolo.symbol, simbolo.type, simbolo.op });
				}
				else {
					simbolo.symbol = caracter;
					simbolo.type = sSymbol::Type::Unknown;
					std::cout << "Invalid character found in expression: " << simbolo.symbol << "\n";
				}
			}
		}


		int lastIndex = 0;
		std::string numeroIdentificado = "";
		sSymbol sym;
		int longitud = 0, aux = 0;
		for (size_t i = 0; i < variableAuxiliar.length(); i++) {

			//Si estamos en la ultima posicion, pero como no hay coma no agarraría el ultimo numero, por tanto la siguiente condicional
			//Hace dicha labor.
			if (variableAuxiliar[i] == variableAuxiliar.length() - 1) {
				if (variableAuxiliar[i] != ',') // si la cadena no termina en una coma, entonces agarrar como punto fijo su longitud
				{
					aux = lastIndex;
					longitud = (variableAuxiliar.length() - 1) - (aux + 1);
					numeroIdentificado = variableAuxiliar.substr(aux, longitud);
					superSExpresion.push_back({ numeroIdentificado, sSymbol::Type::Literal_Numeric }); // Se asigna el numero dentro de SuperEsxpresion
				}
				//No habría condicion por si termina en coma, porque eso está contemplado en el codicional de abajo
				//Lo cual lo trata en terminos generales, en ese caso si se encuentra con una coma pues hacer lo mismo de ir descomponiendo
				//Y al final agregar el operador correspondiente al que representa la coma.
			}
			if (variableAuxiliar[i] == ',') {
				aux = lastIndex; //guarda copia de lastIndex -> 0
				lastIndex = i; // -> 0
				longitud = lastIndex - (aux + 1); //Toma exactamente la longitud partiendo del primer dígito hasta el ultimo digito
				/*
				*
				* RECORDAR QUE ',' representan operadores encontrados en el proceso de clasificacion de números con digitos mayores.
					por ejemplo ",123,"

					1. la primera ',' -> {0}, representa aux
					2. La segunda ',' -> {4}, representa lastIndex
					3. La longitud de 123 -> 4 - (0+1) = 4 - 1 = 3


					por ejemplo ",123,456789,101112": enfocandose en "456"

					1. La primera ',' -> {4}
					2. La segunda ',' -> {11}
					3. La logintud de 456789 -> {11} - {4+1} = 6

					entonces longitud 6 => 456789 son 6 digitos


				*/
				if (longitud == 0) continue;
				else if (longitud > 0) {
					numeroIdentificado = variableAuxiliar.substr(aux, longitud);
					superSExpresion.push_back({ numeroIdentificado, sSymbol::Type::Literal_Numeric }); // Se asigna el numero dentro de SuperEsxpresion	
				}
				superSExpresion.push_back({ stackAuxiliar.front().symbol }); //Asignamos el operador en el orden de la coma
				stackAuxiliar.pop_front(); //Elimina el primer item de la pila
			}
		}

		for (sSymbol& symbol : superSExpresion) {
			std::cout <<  symbol.symbol;
		}

		// region TOMAR NUMEROS DE MAS DE UN DIGITO
		// stackAuxiliar superEntrada
		// FOR >> recorre todos los numeros
		//     >>>> variable auxiliar: esNumero;;; variable numeroString
		//	   >>>> si es un numero, se concatena con el numero anterior	
		//     >>>>>>si esNumero es true, y el siguiente caracter no es un numero, se agrega numeroString y el caracter a la entradaParseada
		//	   >>>> si no es un numero, se agrega el caracter a la entradaParseada
		// endregion

		// IMPORTANTE TODO: se validan los caracteres de la expresion, se eliminan los espacios y se convierten los caracteres a minusculas 

		// if (caracter es espacio) continue;
		// if (caracter es invalido) { 
		//std::cout << "Invalid character found in expression: " << std::string(1, c) << "\n";
		//return 0;
		// }

		// hallar numeros de mas de un digito

		// hallar funciones y entonces llamar a SolveFunction
		// Ejemplo de posible aplicacion
		/*

		int resultado de funcion;

		if (se halla una funcion) {
			resultado de la funcion = SolveFunction(auxiliarExpression, index);

			se crea un objeto sSymbol con el resultado de la funcion

			se inserta el sSymbol del resultado de la funcion en la superSExpresion
		}
		*/
		return 0.0;
	}// endregion     

}

double SolveFunction(std::string& sExpression, int& index)
{
	int lastDigitIndex = 11;
	double res = 0.0;



	// CAMBIAMOS EL CONTENIDO DE LA sExpression CORTANDO EL CONTENIDO DE LA CADENA
	// Obtener la parte de la cadena antes del rango a eliminar
	std::string before = sExpression.substr(0, index+1);

	// Obtener la parte de la cadena después del rango a eliminar
	std::string after = sExpression.substr(lastDigitIndex + 1, sExpression.length() - lastDigitIndex + 1);
	
	sExpression = before+after;
	
	return res + 3;
}

int Factorial(int number) 
{     
    //if(number == 1) return 1;        
    //return number * Factorial(number - 1);
    return (number == 0 || number == 1) ? 1 : number * Factorial(number - 1);
}

int main() {
    
    
    //std::string expression = "1+2*3s(43+3)-23";
    //int index = 5;
    //std::cout << SolveFunction(expression, index) << "\n";
    //std::cout << expression;
    
    //std::unordered_map<char, sOperator> mapOps; // un unordered_map contiene key-value y los datos no se ordenan de alguna forma particular
    //mapOps['/'] = { 4,2 };
    //mapOps['*'] = { 3,2 };
    //mapOps['+'] = { 2,2 };
    //mapOps['-'] = { 2,2 };
    
    //std::deque<sSymbol> dq;
    
    //dq.push_front({ std::string("12"), sSymbol::Type::Literal_Numeric });
    //dq.push_front({ std::string("/"), sSymbol::Type::Operator, mapOps['/'] });
    
    //for (sSymbol sym : dq) {
        //std::cout << sym.symbol << "\n"; // Accede al miembro 'value' de cada sSymbol
    //}
    
    //std::cout << Factorial(10);
    
    std::string expression = "(1+2*3/4)";
    
    std::cout << SolveExpression(expression) << "\n";
}