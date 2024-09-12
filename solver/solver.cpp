// solver.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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

	std::string sExpression = "1+2*4-3 "; // se asume que la expresion no contiene espacios y que no contiene caracteres invalidos

	// necesitamos 2 containers para el algoritmo

	struct sSymbol { // almacena el valor en formato texto y se clasifica en un tipo y detalla sus argumentos y precedencias
		std::string symbol = "";

		enum class Type : uint8_t {
			Unknown,
			Literal_Numeric,
			Operator
		} type = Type::Unknown;

		sOperator op;
	};

	std::deque<sSymbol> stkHolding;
	std::deque<sSymbol> stkOutput;

	for (const char c : sExpression)
	{
		if (std::isdigit(c)) // verifica si es un digito [0,9]
		{
			// se empuja el literal_numeric directamente al output, pues estan en orden
			stkOutput.push_back({ std::string(1,c), sSymbol::Type::Literal_Numeric }); // push_back lo coloca de ultimo
		}
		else if (mapOps.find(c) != mapOps.end())
		{
			// if symbol is an operator
			const auto& new_op = mapOps[c]; // se utiliza una referencia constante para no modificar el valor original
			// se utiliza & para obtener la direccion de memoria de la variable y no una copia

			// para poder agregar el operador a las estructuras de datos, necesitamos conocer la precedencia del operador en la parte superior de la pila

			// si el del tope de la pila es un operador y la precedencia es mayor, se debe sacar el operador de la pila y agregarlo al output 
			// se debe repetir hasta que el operador en el tope de la pila tenga menor precedencia o este vacia (cambiara en el futuro)

			while (!stkHolding.empty())
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
		}
		else
		{
			// si el caracter no es un digito o un operador, es un caracter invalido
			std::cout << "Invalid character found in expression: " << std::string(1, c) << "\n";
			return 0;
		}
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
	std::deque<int> stkSolve;

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

			for (uint8_t a = 0; a < inst.op.arguments; ++a)
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
			if (inst.op.arguments == 2)
			{
				switch (inst.symbol[0])
				{
					break;
				case '+':
				{
					result = mem[1] + mem[0];
					stkSolve.push_front(result);
				}
				break;
				case '-':
				{
					result = mem[1] - mem[0];
					stkSolve.push_front(result);
				}
				break;
				case '*':
				{
					result = mem[1] * mem[0];
					stkSolve.push_front(result);
				}
				break;
				case '/':
				{
					result = mem[1] / mem[0];
					stkSolve.push_front(result);
				}
				break;
				}
			}
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
