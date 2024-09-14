// MathFunctions.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <array>
#include <deque>
#include <unordered_map>

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

int Factorial(int number)
{
	return (number == 0 || number == 1) ? 1 : number * Factorial(number - 1);
}

/**
 * Resuelve una función dentro de una expresión dada.
 *
 * @param sExpression La expresión que contiene la función.
 * @param index El índice del primer dígito de la función dentro de la expresión.
 * @return El resultado de la función resuelta.
 */
double SolveExpression(const std::string sExpression)
{
	double res = 0.0;
	std::deque<sSymbol> superSExpresion; // se inicializa la variable que contendra la expresion que toma mas de un digito
	std::unordered_map<char, sOperator> mapOps; // un unordered_map contiene key-value y los datos no se ordenan de alguna forma particular
	mapOps['^'] = { 5,2 };
	mapOps['/'] = { 4,2 };
	mapOps['*'] = { 3,2 };
	mapOps['+'] = { 2,2 };
	mapOps['-'] = { 2,2 };
	
	/*region TODO TOMAR NUMEROS DE MAS DE UN DIGITO*/ {


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
	}// endregion 

	// NOTA... para este punto superSExpression contiene solo numeros y operadores en formato sSymbol

	// DE MOMENTO SE QUEMA UNA EXPRESION PARA PROBAR EL CODIGO
	{

		/*superSExpresion.push_back({ "-", sSymbol::Type::Operator, mapOps['-'] });
		superSExpresion.push_back({ "(", sSymbol::Type::Parenthesis_Open });
		superSExpresion.push_back({ "(", sSymbol::Type::Parenthesis_Open });
		superSExpresion.push_back({ "1", sSymbol::Type::Literal_Numeric });
		superSExpresion.push_back({ "+", sSymbol::Type::Operator, mapOps['+'] });
		superSExpresion.push_back({ "2", sSymbol::Type::Literal_Numeric });
		superSExpresion.push_back({ ")", sSymbol::Type::Parenthesis_Close });
		superSExpresion.push_back({ "/", sSymbol::Type::Operator, mapOps['/'] });
		superSExpresion.push_back({ "(", sSymbol::Type::Parenthesis_Open });
		superSExpresion.push_back({ "6", sSymbol::Type::Literal_Numeric });
		superSExpresion.push_back({ "*", sSymbol::Type::Operator, mapOps['*'] });
		superSExpresion.push_back({ "-7", sSymbol::Type::Literal_Numeric });
		superSExpresion.push_back({ ")", sSymbol::Type::Parenthesis_Close });
		superSExpresion.push_back({ "+", sSymbol::Type::Operator, mapOps['+'] });
		superSExpresion.push_back({ "(", sSymbol::Type::Parenthesis_Open });
		superSExpresion.push_back({ "7", sSymbol::Type::Literal_Numeric });
		superSExpresion.push_back({ "*", sSymbol::Type::Operator, mapOps['*'] });
		superSExpresion.push_back({ "-4", sSymbol::Type::Literal_Numeric });
		superSExpresion.push_back({ ")", sSymbol::Type::Parenthesis_Close });
		superSExpresion.push_back({ "/", sSymbol::Type::Operator, mapOps['/'] });
		superSExpresion.push_back({ "2", sSymbol::Type::Literal_Numeric });
		superSExpresion.push_back({ "-", sSymbol::Type::Operator, mapOps['-'] });
		superSExpresion.push_back({ "3", sSymbol::Type::Literal_Numeric });
		superSExpresion.push_back({ ")", sSymbol::Type::Parenthesis_Close });*/
		
		//superSExpresion.push_back({ "(", sSymbol::Type::Parenthesis_Open });
		//superSExpresion.push_back({ "4", sSymbol::Type::Literal_Numeric });
		//superSExpresion.push_back({ "+", sSymbol::Type::Operator, mapOps['+'] });
		//superSExpresion.push_back({ "4", sSymbol::Type::Literal_Numeric });
		//superSExpresion.push_back({ ")", sSymbol::Type::Parenthesis_Close });
		//superSExpresion.push_back({ "^", sSymbol::Type::Operator, mapOps['^'] });
		//superSExpresion.push_back({ "(", sSymbol::Type::Parenthesis_Open });
		//superSExpresion.push_back({ "4", sSymbol::Type::Literal_Numeric });
		//superSExpresion.push_back({ "-", sSymbol::Type::Operator, mapOps['-'] });
		//superSExpresion.push_back({ "2", sSymbol::Type::Literal_Numeric });
		//superSExpresion.push_back({ ")", sSymbol::Type::Parenthesis_Close });


		for ( sSymbol sym: superSExpresion )
		{
			std::cout << sym.symbol;
		}
		std::cout << "\n";
	}

	/*region RESOLVER LA superSExpression */ {

		//std::string sExpression = "-((1+2)/((6*-7)+(7*-4)/2)-3)";

		std::deque<sSymbol> stkHolding; // se colocaran los operadores y parentesis
		std::deque<sSymbol> stkOutput; // se colocaran los literales numericos y los operadores en formato RPN

		sSymbol symPrevious = { "0", sSymbol::Type::Literal_Numeric, 0, 0 }; // se inicializa con un valor arbitrario. NOTA: {0,0} son los valores que toma el sOperator en el struct sSymbol

		int pass = 0; // para poder aceptar un - o + al inicio de la expresion

		for (const sSymbol& sym : superSExpresion) {
			if (sym.type == sSymbol::Type::Literal_Numeric) // verifica si es un numero
			{
				// se empuja el literal_numeric directamente al output, pues estan en orden
				stkOutput.push_back(sym); // push_back lo coloca de ultimo en la pila
				symPrevious = stkOutput.back(); // se guarda el valor en la variable symPrevious, que es un auxiliar para saber el valor anterior
			}
			else if (sym.symbol == "(")
			{
				// para el parentesis abierto, se agrega a la output stack de una vez porque no es necesario conocer precedencia de nada.
				// Se agrega tambien para saber donde parar a la hora de buscar todo lo que se operara dentro del parentesis
				stkHolding.push_front(sym);
				symPrevious = stkHolding.front(); // se guarda el valor en la variable symPrevious, que es un auxiliar para saber el valor anterior
			}
			else if (sym.symbol == ")")
			{
				// en este caso lo que queremos es sacar todo lo que esta dentro del parentesis y agregarlo a la output stack
				// luego operar todo lo que esta dentro del parentesis

				while (!stkHolding.empty() && stkHolding.front().type != sSymbol::Type::Parenthesis_Open)
				{
					stkOutput.push_back(stkHolding.front());
					stkHolding.pop_front();
				}

				// en facto, nunca deberia de estar vacia la holding stack porque siempre deberia de haber un parentesis abierto
				// por lo que si esta vacia, hay un error en la expresion
				if (stkHolding.empty())
				{
					std::cout << "!!! ERROR! Bad Expression: Parenthesis mismatch\n";
					return 0;
				}

				// se elimina el parentesis abierto de la holding stack
				if (!stkHolding.empty() && stkHolding.front().type == sSymbol::Type::Parenthesis_Open)
				{
					stkHolding.pop_front();
				}

				symPrevious = sym; // se guarda el valor en la variable symPrevious, que es un auxiliar para saber el valor anterior
			}
			else // linea original else if (mapOps.find(C) != mapOps.end()). Se asume que aqui ya se ha verificado que no hay valores invalidos
			{
				// if symbol is an operator
				//const auto& new_op = mapOps[c]; // se utiliza una referencia constante para no modificar el valor original
				// se utiliza & para obtener la direccion de memoria de la variable y no una copia
				sOperator new_op = mapOps[sym.symbol[0]]; // se cambia para poder modificar el valor de arguments y precedence

				if (sym.symbol[0] == '-' || sym.symbol[0] == '+')
				{
					if ((symPrevious.type != sSymbol::Type::Literal_Numeric
						&& symPrevious.type != sSymbol::Type::Parenthesis_Close) || pass == 0)
					{
						new_op.arguments = 1;
						new_op.precedence = 100;
					}
				}


				// para poder agregar el operador a las estructuras de datos, necesitamos conocer la precedencia del operador en la parte superior de la pila

				// si el del tope de la pila es un operador y la precedencia es mayor, se debe sacar el operador de la pila y agregarlo al output 
				// se debe repetir hasta que el operador en el tope de la pila tenga menor precedencia o este vacia (cambiara en el futuro)

				while (!stkHolding.empty() && stkHolding.front().type != sSymbol::Type::Parenthesis_Open)
				{
					// se asegura que el tope de la holding stack es un operator (puede no serlo en el futuro)
					if (stkHolding.front().type == sSymbol::Type::Operator)
					{
						const auto& holding_stack_op = stkHolding.front().op; // se obtiene la precedencia del operador en la holding stack

						if (holding_stack_op.precedence >= new_op.precedence)
						{
							// si la precedencia del operador en la holding stack es mayor o igual al nuevo operador, se debe mover el operador a la output stack
							stkOutput.push_back(stkHolding.front());
							stkHolding.pop_front(); // se elimina el operador de la holding stack
						}
						else
						{
							// si la precedencia del operador en la holding stack es menor al nuevo operador, se debe detener el loop y agregar el nuevo operador a la holding stack
							break;
						}
					}
				}

				// se agrega el nuevo operador a la holding stack
				stkHolding.push_front({ std::string(1,sym.symbol[0]), sSymbol::Type::Operator, new_op });
				symPrevious = stkHolding.front(); // se guarda el valor en la variable symPrevious, que es un auxiliar para saber el valor anterior
			}
			pass++; // se incrementa el contador de pasos
		}

		while (!stkHolding.empty()) // se vacia la holding stack y se agrega todo a la output stack
		{
			stkOutput.push_back(stkHolding.front());
			stkHolding.pop_front();
		}

		//std::cout << "Expression: " << sExpression << "\n";
		//std::cout << "RPN:";
		//for (const auto& symbol : stkOutput)
		//{
		//	std::cout << symbol.symbol;
		//}
		//std::cout << "\n";

		// Solver
		std::deque<double> stkSolve;

		for (const auto& inst : stkOutput) // recorremos todos los valores de la pila Output
		{
			// tenemos que clasificar como operadores o literales numericos
			switch (inst.type)
			{
			case sSymbol::Type::Literal_Numeric:
			{
				stkSolve.push_front(std::stod(inst.symbol)); // se convierte el string a double y se agrega al inicio de la pila
			}
			break;

			case sSymbol::Type::Operator:
			{
				// en este caso, se debe de considerar cuantos argumentos toma el operador
				std::vector<double> mem(inst.op.arguments); // se crea un vector de doubles con el numero de argumentos que toma el operador
				// los argumentos son los valores que se encuentran en el tope de la pila

				for (uint8_t a = 0; a < inst.op.arguments; a++)
				{
					if (stkSolve.empty())
					{
						std::cout << "!!! ERROR! Bad Expression: Some operator has no enough arguments\n";
					}
					else
					{
						mem[a] = stkSolve[0]; // se copia el valor del tope de la pila en el vector
						stkSolve.pop_front(); // se elimina el valor del tope de la pila
					}
				}

				double result = 0.0;
				if (inst.op.arguments == 2) // si el operador toma 2 argumentos
				{
					if (inst.symbol[0] == '^') result = pow(mem[1],mem[0]);
					if (inst.symbol[0] == '/') result = mem[1] / mem[0];
					if (inst.symbol[0] == '*') result = mem[1] * mem[0];
					if (inst.symbol[0] == '+') result = mem[1] + mem[0];
					if (inst.symbol[0] == '-') result = mem[1] - mem[0];
				}

				if (inst.op.arguments == 1)
				{
					if (inst.symbol[0] == '+') result = +mem[0];
					if (inst.symbol[0] == '-') result = -mem[0];
				}

				stkSolve.push_front(result); // se empuja el resultado al inicio de la pila
			}
			default:
				break;
			}
		}

		res = stkSolve[0]; // el resultado final se encuentra en el tope de la pila

	}// endregion 

	return res;
}

/// <summary>
/// Esta función recibe una expresión ingresada por el usuario y el índice donde comienza una función dentro de la expresión.
/// Si la expresión es "1+2+s(32*c(43))-32", el índice indicaría la posición de la función "s", es decir, index = 4.
/// La función llama a SolveExpression para resolver el contenido dentro de los paréntesis, sin importar si contiene funciones anidadas.
/// 
/// Si la expresión es válida, la función devuelve el resultado como un valor double.
/// 
/// Antes de devolver el resultado, la función modifica sExpression eliminando la función evaluada. 
/// En el ejemplo, sExpression se transformaría de "1+2+s(32*c(43))-32" a "1+2+s-32", para que en la siguiente iteración se procese el resto.
/// </summary>
/// <param name="sExpression">La expresión completa ingresada por el usuario</param>
/// <param name="index">Índice que señala el inicio de una función dentro de sExpression</param>
/// <returns>El valor calculado de la subexpresión o función</returns>
double SolveFunction(std::string& sExpression, int& index)
{
	std::string currentExpression = "";
	char functionAbr = sExpression[index];
	int lastDigitIndex;
	double res = 0.0;

	//Primero separamos sExpression en tres partes: antes de la funcion, la funcion y despues de la funcion
	// antes de la funcion y despues de la funcion se uniran para darle un nuevo valor a la sExpression que se nos paso como parametro
	// la funcion se resolvera y se devolvera el valor

	/*region OBTENER LA FUNCION*/ {
		// verificamos que la funcion tenga parentesis
		index++; // nos pasamos al siguiente caracter despues de la funcion
		if (!(sExpression[index] == '(')) // primero verificamos que el parentesis de apertura sea el siguiente caracter despues de la funcion
		{
			std::cout << "!!! ERROR! Bad Expression: Parenthesis mismatch\n";
			return 0;
		}

		int parnthsMissMatched = 0; // contador para saber cuantos parentesis de apertura hay
		// esta parentesis sera util para saber cuantos parentesis de cierre tenemos que encontrar; Porque si hallamos 
		// un parentesis abierto mas adelante, tendremos que encontrar su respectivo parentesis de cierre

		for (size_t i = index; i < sExpression.length(); i++) // empezamos desde el parentesis de apertura
		{
			if (sExpression[i] == '(') parnthsMissMatched++; // si encontramos un parentesis de apertura, incrementamos el contador
			if (sExpression[i] == ')') parnthsMissMatched--; // si encontramos un parentesis de cierre, decrementamos el contador

			currentExpression += sExpression[i]; // guardamos el caracter en la variable currentExpression

			if (parnthsMissMatched == 0) // si el contador llega a 0, significa que encontramos el parentesis de cierre
			{
				lastDigitIndex = i; // guardamos el indice del parentesis de cierre
				break;
			}
		}

		// casos:
		// parnthMissMatched = 0; significa que hay la misma cantidad de parentesis de apertura y cierre, por lo tanto es correcto
		// parnthMissMatched > 0; significa que hay mas parentesis de apertura que de cierre, por lo tanto es incorrecto
		// parnthMissMatched < 0; significa que hay mas parentesis de cierre que de apertura, por lo tanto es incorrecto
		if (parnthsMissMatched != 0) // si el contador no llega a 0, significa que hay algun parentesis sin su contraparte
		{
			std::cout << "!!! ERROR! Bad Expression: Parenthesis mismatch\n";
			return 0;
		}
	}// endregion

	/*region RESOLVER LA FUNCION*/ {
		double argumentRes = SolveExpression(currentExpression); // se resuelve el contenido dentro de la funcion

		if (functionAbr == 's') {
			res = sin(argumentRes);
		}; // seno
		if (functionAbr == 'c') {
			res = cos(argumentRes);
		}; // coseno
		if (functionAbr == 't') {
			res = tan(argumentRes);
		}; // tangente
		if (functionAbr == 'z') {
			res = atan(argumentRes);
		}; // arcotangente
		if (functionAbr == 'y') {
			res = acos(argumentRes);
		}; // arcocoseno
		if (functionAbr == 'x') {
			res = asin(argumentRes);
		}; // arcoseno
		if (functionAbr == 'r') {
			res = sqrt(argumentRes);
		}; // raiz cuadrada
		if (functionAbr == 'l') {
			res = log(argumentRes);
		}; // logaritmo
		if (functionAbr == 'e') {
			res = exp(argumentRes);
		}; // exponencial
		if (functionAbr == '!') {
			if (argumentRes < 0 || static_cast<int>(argumentRes) % 2 != 0) {
			}
			res = Factorial(argumentRes);
		}; // factorial

	}// endregion

	/*region REVINCULAR sExpression*/ {
		std::string before = sExpression.substr(0, index + 1); // Obtener la parte de la cadena antes del rango a eliminar
		std::string after = sExpression.substr(lastDigitIndex + 1, sExpression.length() - lastDigitIndex - 1); // Obtener la parte de la cadena después del rango a eliminar
		sExpression = before + after;
	}// endregion


	return res;
}



int main()
{
	std::cout << SolveExpression(std::string("1+2"));
}
