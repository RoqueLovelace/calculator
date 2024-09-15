// negative_numbers_handler.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <array>
#include <deque>
#include <unordered_map>

int main()
{
	//PEDMAS (Parentesis, Exponentes, Division, Multiplicacion, Adicion, Sustraccion)
	struct sOperator
	{
		uint8_t precedence = 0; // la prioridad de la operacion
		uint8_t arguments = 0; // los argumentos que toma el operado. p.e: + toma 2 (4+7), ! toma 1 (5!) 
	};

	std::unordered_map<char, sOperator> mapOps; // un unordered_map contiene key-value y los datos no se ordenan de alguna forma particular
	mapOps['/'] = { 4,2 };
	mapOps['*'] = { 3,2 };
	mapOps['+'] = { 2,2 };
	mapOps['-'] = { 2,2 };

	std::string sExpression = "-((1+2)/((6*-7)+(7*-4)/2)-3)";

	// necesitamos 2 containers para el algoritmo

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

	// region TOMAR NUMEROS DE MAS DE UN DIGITO
	// stackAuxiliar superEntrada
	// FOR >> recorre todos los numeros
	//     >>>> variable auxiliar: esNumero;;; variable numeroString
	//	   >>>> si es un numero, se concatena con el numero anterior	
	//     >>>>>>si esNumero es true, y el siguiente caracter no es un numero, se agrega numeroString y el caracter a la entradaParseada
	//	   >>>> si no es un numero, se agrega el caracter a la entradaParseada
	// endregion

	// s(3923) c(3443) 

	std::deque<sSymbol> stkHolding;
	std::deque<sSymbol> stkOutput;

	sSymbol symPrevious = { "0", sSymbol::Type::Literal_Numeric, 0, 0 }; // se inicializa con un valor arbitrario. NOTA: {0,0} son los valores que toma el sOperator en el struct sSymbol
	int pass = 0; // para poder aceptar un - o + al inicio de la expresion


	for (const char c : sExpression)
	{
		if (std::isdigit(c)) // verifica si es un digito [0,9]
		{
			// se empuja el literal_numeric directamente al output, pues estan en orden
			stkOutput.push_back({ std::string(1,c), sSymbol::Type::Literal_Numeric }); // push_back lo coloca de ultimo
			symPrevious = stkOutput.back(); // se guarda el valor en la variable symPrevious, que es un auxiliar para saber el valor anterior
		}
		else if (c == '(')
		{
			// para el parentesis abierto, se agrega a la output stack de una vez porque no es necesario conocer precedencia de nada.
			// Se agrega tambien para saber donde parar a la hora de buscar todo lo que se operara dentro del parentesis
			stkHolding.push_front({ std::string(1, c), sSymbol::Type::Parenthesis_Open });
			symPrevious = stkHolding.front(); // se guarda el valor en la variable symPrevious, que es un auxiliar para saber el valor anterior
		}
		else if (c == ')')
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

			symPrevious = { ")", sSymbol::Type::Parenthesis_Close }; // se guarda el valor en la variable symPrevious, que es un auxiliar para saber el valor anterior

		}
		else if (mapOps.find(c) != mapOps.end())
		{
			// if symbol is an operator
			//const auto& new_op = mapOps[c]; // se utiliza una referencia constante para no modificar el valor original
			// se utiliza & para obtener la direccion de memoria de la variable y no una copia
			sOperator new_op = mapOps[c]; // se cambia para poder modificar el valor de arguments y precedence

			if (c == '-' || c == '+') 
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
			stkHolding.push_front({ std::string(1,c), sSymbol::Type::Operator, new_op });
			symPrevious = stkHolding.front(); // se guarda el valor en la variable symPrevious, que es un auxiliar para saber el valor anterior
		}
		else
		{
			// si el caracter no es un digito o un operador, es un caracter invalido
			std::cout << "Invalid character found in expression: " << std::string(1, c) << "\n";
			return 0;
		}

		pass++;
	}

	while (!stkHolding.empty())
	{
		stkOutput.push_back(stkHolding.front());
		stkHolding.pop_front();
	}

	std::cout << "Expression: " << sExpression << "\n";
	std::cout << "RPN:";
	// se imprime la expresion en formato postfix
	for (const auto& symbol : stkOutput)
	{
		std::cout << symbol.symbol;
	}

	std::cout << "\n";

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

	std::cout << "Result: " << stkSolve[0] << "\n";
	system("pause");
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln


//double SolveExpression2(std::string& sExpression) {
//	double res = 0.0;
//	std::deque<sSymbol> superSExpresion; // se inicializa la variable que contendra la expresion que toma mas de un digito
//	std::unordered_map<char, sOperator> mapOps; // un unordered_map contiene key-value y los datos no se ordenan de alguna forma particular
//	mapOps['^'] = { 5,2 };
//	mapOps['/'] = { 4,2 };
//	mapOps['*'] = { 3,2 };
//	mapOps['+'] = { 2,2 };
//	mapOps['-'] = { 2,2 };
//	std::string functionsSymbol = "sctzyxrle!";
//
//	/*region TODO TOMAR NUMEROS DE MAS DE UN DIGITO*/
//	{
//
//		std::deque<sSymbol> stackAuxiliar; //para almacenar los operadores traidos de identificar numeros de más de 2 digitos
//		std::string variableAuxiliar = ""; //Para los numeros
//
//		bool esNumero = false;
//		sSymbol simbolo;
//
//		for (char caracter : sExpression) {
//			if (std::isdigit(caracter)) {
//				esNumero = true;
//				variableAuxiliar += caracter;
//			}
//			else if (!(std::isdigit(caracter))) {
//				esNumero = false;
//				variableAuxiliar += ","; //Cada una de estas comas representan un operador en específico.
//
//				if (caracter == '(') {
//					simbolo.symbol = caracter;
//					simbolo.type = sSymbol::Type::Parenthesis_Open;
//					stackAuxiliar.push_back({ simbolo.symbol, simbolo.type });
//				}
//				else if (caracter == ')') {
//					simbolo.symbol = caracter;
//					simbolo.type = sSymbol::Type::Parenthesis_Close;
//					stackAuxiliar.push_back({ simbolo.symbol, simbolo.type });
//				}
//				else if (caracter == '*' || caracter == '/' || caracter == '+' || caracter == '-') {
//					simbolo.symbol = caracter;
//					simbolo.type = sSymbol::Type::Operator;
//					simbolo.op = mapOps[caracter];
//					stackAuxiliar.push_back({ simbolo.symbol, simbolo.type, simbolo.op });
//				}
//				else {
//					simbolo.symbol = caracter;
//					simbolo.type = sSymbol::Type::Unknown;
//					std::cout << "Invalid character found in expression: " << simbolo.symbol << "\n";
//				}
//			}
//		}
//
//
//		int lastIndex = 0;
//		std::string numeroIdentificado = "";
//		sSymbol sym;
//		int longitud = 0, aux = 0;
//		for (size_t i = 0; i < variableAuxiliar.length(); i++) {
//
//			//Si estamos en la ultima posicion, pero como no hay coma no agarraría el ultimo numero, por tanto la siguiente condicional
//			//Hace dicha labor.
//			if (variableAuxiliar[i] == variableAuxiliar.length() - 1) {
//				if (variableAuxiliar[i] != ',') // si la cadena no termina en una coma, entonces agarrar como punto fijo su longitud
//				{
//					aux = lastIndex;
//					longitud = (variableAuxiliar.length() - 1) - (aux + 1);
//					numeroIdentificado = variableAuxiliar.substr(aux, longitud);
//					superSExpresion.push_back({ numeroIdentificado, sSymbol::Type::Literal_Numeric }); // Se asigna el numero dentro de SuperEsxpresion
//				}
//				//No habría condicion por si termina en coma, porque eso está contemplado en el codicional de abajo
//				//Lo cual lo trata en terminos generales, en ese caso si se encuentra con una coma pues hacer lo mismo de ir descomponiendo
//				//Y al final agregar el operador correspondiente al que representa la coma.
//			}
//			if (variableAuxiliar[i] == ',') {
//				aux = lastIndex; //guarda copia de lastIndex -> 0
//				lastIndex = i; // -> 0
//				longitud = lastIndex - (aux + 1); //Toma exactamente la longitud partiendo del primer dígito hasta el ultimo digito
//				/*
//				*
//				* RECORDAR QUE ',' representan operadores encontrados en el proceso de clasificacion de números con digitos mayores.
//					por ejemplo ",123,"
//
//					1. la primera ',' -> {0}, representa aux
//					2. La segunda ',' -> {4}, representa lastIndex
//					3. La longitud de 123 -> 4 - (0+1) = 4 - 1 = 3
//
//
//					por ejemplo ",123,456789,101112": enfocandose en "456"
//
//					1. La primera ',' -> {4}
//					2. La segunda ',' -> {11}
//					3. La logintud de 456789 -> {11} - {4+1} = 6
//
//					entonces longitud 6 => 456789 son 6 digitos
//
//
//				*/
//				if (longitud == 0) continue;
//				else if (longitud > 0) {
//					numeroIdentificado = variableAuxiliar.substr(aux, longitud);
//					superSExpresion.push_back({ numeroIdentificado, sSymbol::Type::Literal_Numeric }); // Se asigna el numero dentro de SuperEsxpresion	
//				}
//				superSExpresion.push_back({ stackAuxiliar.front().symbol }); //Asignamos el operador en el orden de la coma
//				stackAuxiliar.pop_front(); //Elimina el primer item de la pila
//			}
//		}
//
//		for (sSymbol& symbol : superSExpresion) {
//			std::cout << symbol.symbol;
//		}
//
//		// region TOMAR NUMEROS DE MAS DE UN DIGITO
//		// stackAuxiliar superEntrada
//		// FOR >> recorre todos los numeros
//		//     >>>> variable auxiliar: esNumero;;; variable numeroString
//		//	   >>>> si es un numero, se concatena con el numero anterior	
//		//     >>>>>>si esNumero es true, y el siguiente caracter no es un numero, se agrega numeroString y el caracter a la entradaParseada
//		//	   >>>> si no es un numero, se agrega el caracter a la entradaParseada
//		// endregion
//
//		// IMPORTANTE TODO: se validan los caracteres de la expresion, se eliminan los espacios y se convierten los caracteres a minusculas 
//
//		// if (caracter es espacio) continue;
//		// if (caracter es invalido) { 
//		//std::cout << "Invalid character found in expression: " << std::string(1, c) << "\n";
//		//return 0;
//		// }
//
//		// hallar numeros de mas de un digito
//
//		// hallar funciones y entonces llamar a SolveFunction
//		// Ejemplo de posible aplicacion
//		/*
//
//		int resultado de funcion;
//
//		if (se halla una funcion) {
//			resultado de la funcion = SolveFunction(auxiliarExpression, index);
//
//			se crea un objeto sSymbol con el resultado de la funcion
//
//			se inserta el sSymbol del resultado de la funcion en la superSExpresion
//		}
//		*/
//		return 0.0;
//	}// endregion     
//
//}
//
//
//double SolveFunction2(std::string& sExpression, int& index)
//{
//	int lastDigitIndex = 12;
//	double res = 0.0;
//
//
//
//	// CAMBIAMOS EL CONTENIDO DE LA sExpression CORTANDO EL CONTENIDO DE LA CADENA
//	// Obtener la parte de la cadena antes del rango a eliminar
//	std::string before = sExpression.substr(0, index + 1);
//
//	// Obtener la parte de la cadena después del rango a eliminar
//	std::string after = sExpression.substr(lastDigitIndex + 1, sExpression.length() - lastDigitIndex + 1);
//
//	sExpression = before + after;
//
//	// TODO HACER PROCESO DE ROUND
//	return res + 3;
//}


double SolveNumber(std::string& sExpression, int& index) {
	std::string currentExpression = "";
	int lastDigitIndex;
	double res = 0.0;
	bool dotFound = false;

	/*region OBTENER LA FUNCION*/ {
		for (size_t i = index; i < sExpression.length(); i++) // empezamos desde el parentesis de apertura
		{
			if (sExpression[i] == '.') {
				if (dotFound) {
					std::cout << "ERROR: BAD NUMBER";
					return 0;
				}
				dotFound = true;
			}

			if (!(std::isdigit(sExpression[i])) && sExpression[i] != '.') // si el contador llega a 0, significa que encontramos el parentesis de cierre
			{
				lastDigitIndex = i; // guardamos el indice del parentesis de cierre
				currentExpression += sExpression[i]; // guardamos el caracter en la variable currentExpression
				break;
			}

			currentExpression += sExpression[i]; // guardamos el caracter en la variable currentExpression
		}

		/*region REVINCULAR sExpression*/ {
			std::string before = sExpression.substr(0, index + 1); // Obtener la parte de la cadena antes del rango a eliminar
			std::string after = sExpression.substr(lastDigitIndex + 1, sExpression.length() - lastDigitIndex - 1); // Obtener la parte de la cadena después del rango a eliminar
			sExpression = before + after;
		}// endregion


		return res;
	}// endregion
}