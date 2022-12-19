#include <iostream>
#include <sstream>
#include <stack>
#include <cmath> 
using namespace std;

const double p = acos(-1);
const double e = exp(1); 
/**
*Класс для элементов математического выражения, где у
*чисел поле value, а у оаераций и функций - type.
*/
class lexeme { 
	public:
		double value; //!< Для операций и функций - 0, для чисел value = число.
		char type; //!< Для чисел - '0', для операций или функций type = символ.
};
/** 
*\brief Функция, устанавливающая приоритет операций.
*
*Функция устанавливает приоритет на какую-либо операцию, которая передаётся ей через параметр.
*\param operation операция, на которую устанавливается приоритет.
*\return значения от 0 до 4, где 0 - несуществующая операция, 4 - операция с наивысшим приоритетом.
*/
int priority (char operation) { 
	if (operation == '+' or operation == '-') return 1;
	if (operation == '*' or operation == '/') return 2;
	if (operation == '^') return 3;
	if (operation == 'u') return 4;
	if (operation == 's' or operation == 'c' or operation == 't' or operation == 'o') return 4;
	if (operation == 'v' or operation == 'b' or operation == 'g' or operation == 'm') return 4;
	if (operation == 'h' or operation == 'j' or operation == 'k' or operation == 'l') return 4;
	if (operation == 'q' or operation == 'w' or operation == 'y' or operation == 'r') return 4;
	if (operation == 'n' or operation == 'd' or operation == 'e' or operation == 'f') return 4;
	return 0;
}
/*! 
*\brief Факториал.
*
*Вычисляет рекурсивно факториал целого положительного числа.
*\param x число, от которого берётся факториал.
*\return 0 - x отрицательный, иначе x!.
*/
double fact (int x) {
	if (x < 0) return 0;
	if (x == 0) return 1;
	else return x*fact(x-1);
}
/*! 
*\brief Перевод из двоичной СС в десятичную.
*
*Функция поразрядно умножает цифры числа на два в степени номера
*разряда. Получившиеся числа суммируются и возвращаюся.
*\param num число, которое необходимо перевести.
*\return bin2dec - значение переведённого числа.
*/
long long bin2dec(int num) {
	long long bin2dec = 0, i = 0;
	while (num) {
		bin2dec += (num % 10)*(1 << i);
		++i;
		num /= 10; 
	}
	return bin2dec;
}
/*! 
*\brief Перевод из восьмеричной СС в десятичную.
*
*Функция поразрядно умножает цифры числа на восемь в степени номера
*разряда. Получившиеся числа суммируются и возвращаюся.
*\param num число, которое необходимо перевести.
*\return oct2dec - значение переведённого числа.
*/
long long oct2dec(int num) {
	long long oct2dec = 0, i = 0;
	while (num) {
		oct2dec += (num % 10)*pow(8, i);
		++i;
		num /= 10; 
	}
	return oct2dec;
}
/*! 
*\brief Перевод из десятичной СС в двоичную.
*
*Остаток от деления на 2 умножается на десять в степени номера
*разряда. Получившиеся числа суммируются и возвращаюся.
*\param num число, которое необходимо перевести.
*\return bin - значение переведённого числа.
*/
long long bin(double num) { //dec to bin
	long long bin = 0, k = 1;
	while (num) {
		bin += ((int) num % 2)*k;
		k *= 10;
		num /= 2;
	}
	return bin;
}
/*! 
*\brief Перевод из десятичной СС в восьмеричную.
*
*Остаток от деления на 8 умножается на десять в степени номера
*разряда. Получившиеся числа суммируются и возвращаюся.
*\param num число, которое необходимо перевести.
*\return oct - значение переведённого числа.
*/
long long oct(double num) { //dec to oct
	long long oct = 0, k = 1;
	while (num) {
		oct += ((int) num % 8)*k;
		k *= 10;
		num /= 8;
	}
	return oct;
}
/*! 
*\brief Функция для вычислений.
*
*Функция вычисляет результат бинарной операции или математической функции.
*Функция имеет тип bool, так как необходимо знать состояние выполнения операции.
*\param StackNums ссылка на стек с числами.
*\param StackOpers ссылка на стек с операциями.
*\param obj результат вычислений.
*\return false - вычисление невозможно, true - вычисление выполнено успешно.
*/
bool Calculate(stack <lexeme> &StackNums, stack <lexeme> &StackOpers, lexeme &obj) {
	
	double x, y, z;
	x = StackNums.top().value; StackNums.pop(); 
	
	switch (StackOpers.top().type) { 
		
		case '+':
			y = StackNums.top().value;
			StackNums.pop();
			StackOpers.pop(); 
			z = x + y;
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case '-': 
			y = StackNums.top().value;
			StackNums.pop();
			StackOpers.pop();
			z = y - x; 
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case '*': 
			y = StackNums.top().value;
			StackNums.pop();
			StackOpers.pop();
			z = x*y;
			obj.value = z;
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case '/': 
			if (x == 0) { 
				cout << "   ������: ������� �� ����!" << endl;
				return false;
			}
			else {
				y = StackNums.top().value;
				StackNums.pop();
				StackOpers.pop();
				z = y/x; 
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
			
		case '^':
			y = StackNums.top().value;
			if ((double) ((int) x) != x) {
				if (y < 0) {
					cout << "  ������: ���������� � ������� ������� �������������� �����!" << endl;
					return false;
				}
			}
			StackNums.pop();
			StackOpers.pop();
			z = pow(y, x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case 'u':
			if(x < 0) {
				cout << "  ������: ������ �� �������������� �����!" << endl;
				return false;
			}
			StackOpers.pop();
			z = sqrt(x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case 's': //sinr
			StackOpers.pop();
			z = round(sin(x)*100000000)/100000000;
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj);
			break;
		
		case 'c': //cosr
			StackOpers.pop();
			z = round(cos(x)*100000000)/100000000;
			obj.value = z;
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case 't': //tanr
			if (round(cos(x)*100000000)/100000000 == 0) { 
				cout << "  ������: ������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = round(tan(x)*100000000)/100000000;
				obj.value = z;
				obj.type = '0';
				StackNums.push(obj);
				break;
			}
			
		
		case 'o': //cotr
			if (round(sin(x)*100000000)/100000000 == 0) { 
				cout << "  ������: ��������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = round(1/tan(x)*100000000)/100000000;
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj);
				break;
			}
		
		case 'v': //sind
			StackOpers.pop();
			z = round(sin(x*2*p/360)*100000000)/100000000;
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj);
			break;
		
		case 'b': //cosd
			StackOpers.pop();
			z = round(cos(x*2*p/360)*100000000)/100000000;
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case 'g': //tand
			if (round(cos(x*2*p/360)*100000000)/100000000 == 0) {
				cout << "  ������: ������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = round(tan(x*2*p/360)*100000000)/100000000;
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
			
		
		case 'm': //cotd
			if (round(sin(x*2*p/360)*100000000)/100000000 == 0) { 
				cout << "  ������: ��������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = round(1/tan(x*2*p/360)*100000000)/100000000;
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
		
		case 'e': //exp
			StackOpers.pop();
			z = exp(x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj);
			break;
		
		case 'n': //ln
			if (x <= 0) { 
				cout << "  ������: �������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = log(x);
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
		
		case 'd': //lg
				if (x <= 0) { 
				cout << "  ������: �������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = log(x)/log(10);
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
		
		case 'q': //asin
			if (x < (-1) or x > 1) { 
				cout << "  ������: �������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = asin(x);
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
			
		case 'w': //acos
			if (x < (-1) or x > 1) { 
				cout << "  ������: ���������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = acos(x);
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
		
		case 'y': //atan
			StackOpers.pop();
			z = atan(x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj);
			break;
		
		case 'r': //acot
			StackOpers.pop();
			z = p/2 - atan(x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case 'f': //n!
			if (x < 0) { 
				cout << "  ������: ��������� �� ��������!" << endl;
				return false;
			}
			if ((double)((int) x) != x) { 
				cout << "  ������: ��������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = fact(x);
				obj.value = z; 
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
		
		case 'h': //sinh
			StackOpers.pop();
			z = sinh(x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case 'j': //cosh
			StackOpers.pop();
			z = cosh(x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case 'k': //tanh
			if (cosh(x) == 0) {
				cout << "  ������: ��������������� ������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = tanh(x);
				obj.value = z;
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
			
		case 'l': //coth
			if (sinh(x) == 0) {
				cout << "  ������: ��������������� ��������� �� ��������!" << endl;
				return false;
			}
			else {
				StackOpers.pop();
				z = 1/tanh(x);
				obj.value = z;
				obj.type = '0';
				StackNums.push(obj); 
				break;
			}
		
		case '2': //bin
			StackOpers.pop();
			z = bin(x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		case '8': //oct
			StackOpers.pop();
			z = oct(x);
			obj.value = z; 
			obj.type = '0';
			StackNums.push(obj); 
			break;
		
		default: //else
			cout << "  ������: ������������� ��������!" << endl;
			return false;
	}
	return true;
}
/**
 * @brief Обработка введённой строки и возвращение ответа
 * 
 * Функция просматривает строку, помещая в стеки с операциями и числами
 * соответствующие им объекты. После просмотра всего выражения происходит
 * вычисление и возвращение ответа.
 * @return 0 - функция выполнена успешно.
 */
int main() {
	
	setlocale(LC_ALL, "rus");
	cout << "  �����������\n";
	char CalcType, scale;
	
	do {
		cout << "  ������� ��� ������������ (S - ����������, P - ���������������): ";
		cin >> CalcType;
	}
	while ((CalcType != 'S') and (CalcType != 'P'));
	cin.ignore();
	bool negative = true; 
	char character; double number; lexeme obj;
	stack <lexeme> StackNums; 
	stack <lexeme> StackOpers; 
	
	if(CalcType == 'P') { //programmer calculator
		do {
			cout << "  ������� ������� ��������� (b - ��������, o - ������������, d - ����������): ";
			cin >> scale;
		}
		while ((scale != 'b') and (scale != 'o') and (scale != 'd'));
		cin.ignore();
		
		cout << "  ������� ���������: ";
		string str;
		getline(cin, str);
		stringstream sstr(str);
		
		if (scale == 'b') { //binary calculator
		while(true) {
			character = sstr.peek();
			
			if (character == ' ') { 
				sstr.ignore();
				continue;
			}
			
			if (character == '\377') break; 
			
			if (character == '-' and negative == true) { 
				obj.value = -1; obj.type = '0';
				StackNums.push(obj); 
				obj.value = 0; obj.type = '*';
				StackOpers.push(obj); 
				negative = false; 
				sstr.ignore();
				continue;
			}
			
			if (character == '(') { 
				negative = true; 
				obj.value = 0;
				obj.type = character; 
				StackOpers.push(obj); 
				sstr.ignore(); 
				//cout << StackOpers.top().type << endl;
				continue;
			}
			
			if (character == ')') { 
				while (StackOpers.top().type != '('){
					if (Calculate(StackNums, StackOpers, obj) == false) return 0; 
					else continue;
				}
				StackOpers.pop(); 
				sstr.ignore(); 
				continue;
			}
			
			if ((character >= '0' and character <= '1') ) { 
				sstr >> number; 
				obj.value = bin2dec(number);
				obj.type = '0';
				StackNums.push(obj);
				negative = false;
				//cout << StackNums.top().value << endl;
				continue;
			}
			
			if (character == '+' or (character == '-' and negative == false) or character == '*' or character == '/') {
				if (StackOpers.empty()) { 
					obj.value = 0;
					obj.type = character; 
					StackOpers.push(obj);
					sstr.ignore(); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				if (not(StackOpers.empty()) and priority(character) > priority(StackOpers.top().type)) { 
					obj.value = 0;
					obj.type = character; 
					StackOpers.push(obj); 
					sstr.ignore();
					//cout << StackOpers.top().type << endl;
					continue;
				}
				if (not(StackOpers.empty()) and priority(character) <= priority(StackOpers.top().type)) {
					if (Calculate(StackNums, StackOpers, obj) == false) return 0; 
				}
				continue;
			}
			
			else { 
				cout << "  ������ ����� � ���������!" << endl;
				return 0;
			}
		}
		
		while (not(StackOpers.empty())) {
			if (Calculate(StackNums, StackOpers, obj) == false) return 0;
			else continue;
		}
		cout << "  �����: " << bin(StackNums.top().value) << endl;
	}
	
	if (scale == 'o') { //octal calculator
		while(true) {
			character = sstr.peek();
			
			if (character == ' ') { 
				sstr.ignore(); 
				continue;
			}
			
			if (character == '\377') break; 
			
			if (character == '-' and negative == true) { 
				obj.value = -1; obj.type = '0';
				StackNums.push(obj); 
				obj.value = 0; obj.type = '*';
				StackOpers.push(obj); 
				negative = false;
				sstr.ignore(); 
				continue;
			}
			
			if (character == '(') {
				negative = true; 
				obj.value = 0;
				obj.type = character; 
				StackOpers.push(obj);
				sstr.ignore(); 
				//cout << StackOpers.top().type << endl;
				continue;
			}
			
			if (character == ')') {
				while (StackOpers.top().type != '('){ 
					if (Calculate(StackNums, StackOpers, obj) == false) return 0; 
					else continue;
				}
				StackOpers.pop(); 
				sstr.ignore(); 
				continue;
			}
			
			if ((character >= '0' and character <= '7') ) {
				sstr >> number; 
				obj.value = oct2dec(number);
				obj.type = '0';
				StackNums.push(obj); 
				negative = false; 
				//cout << StackNums.top().value << endl;
				continue;
			}
			
			if (character == '+' or (character == '-' and negative == false) or character == '*' or character == '/') {
				if (StackOpers.empty()) { 
					obj.value = 0;
					obj.type = character;
					StackOpers.push(obj);
					sstr.ignore(); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				if (not(StackOpers.empty()) and priority(character) > priority(StackOpers.top().type)) {
					obj.value = 0;
					obj.type = character; 
					StackOpers.push(obj); 
					sstr.ignore(); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				if (not(StackOpers.empty()) and priority(character) <= priority(StackOpers.top().type)) { 
					if (Calculate(StackNums, StackOpers, obj) == false) return 0; 
				}
				continue;
			}
			
			else {
				cout << "  ������ ����� � ���������!" << endl;
				return 0;
			}
		}
		
		while (not(StackOpers.empty())) {
			if (Calculate(StackNums, StackOpers, obj) == false) return 0;
			else continue;
		}
		cout << "  �����: " << oct(StackNums.top().value) << endl;
	}
	
	if (scale == 'd') { //decimal calculator
		while(true) {
			character = sstr.peek();
			
			if (character == ' ') {
				sstr.ignore();
				continue;
			}
			
			if (character == '\377') break;
			
			if (character == '-' and negative == true) {
				obj.value = -1; obj.type = '0';
				StackNums.push(obj);
				obj.value = 0; obj.type = '*';
				StackOpers.push(obj);
				negative = false; 
				sstr.ignore(); 
				continue;
			}
			
			if (character == '(') { 
				negative = true;
				obj.value = 0;
				obj.type = character;
				StackOpers.push(obj);
				sstr.ignore(); 
				//cout << StackOpers.top().type << endl;
				continue;
			}
			
			if (character == ')') { 
				while (StackOpers.top().type != '('){ 
					if (Calculate(StackNums, StackOpers, obj) == false) return 0; 
					else continue;
				}
				StackOpers.pop();
				sstr.ignore();
				continue;
			}
			
			if ((character >= '0' and character <= '9') ) { 
				sstr >> number; 
				obj.value = number; 
				obj.type = '0';
				StackNums.push(obj);
				negative = false; 
				//cout << StackNums.top().value << endl;
				continue;
			}
			
			if (character == '+' or (character == '-' and negative == false) or character == '*' or character == '/') {
				if (StackOpers.empty()) { 
					obj.value = 0;
					obj.type = character; 
					StackOpers.push(obj);
					sstr.ignore(); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				if (not(StackOpers.empty()) and priority(character) > priority(StackOpers.top().type)) { 
					obj.value = 0;
					obj.type = character; 
					StackOpers.push(obj); 
					sstr.ignore(); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				if (not(StackOpers.empty()) and priority(character) <= priority(StackOpers.top().type)) { 
					if (Calculate(StackNums, StackOpers, obj) == false) return 0; 
				}
				continue;
			}
			
			else {
				cout << "  ������ ����� � ���������!" << endl;
				return 0;
			}
		}
		
		while (not(StackOpers.empty())) {
			if (Calculate(StackNums, StackOpers, obj) == false) return 0;
			else continue;
		}
		cout << "  �����: " << StackNums.top().value << endl;
	}
	
	}
	
	if (CalcType == 'S') { //scientific calculator
		
		cout << "  ������� ���������: ";
		string str;
		getline(cin, str);
		stringstream sstr(str);
		
		while (true) {
			character = sstr.peek();
			//cout << character;
			
			if (character == ' ') {
				sstr.ignore();
				continue;
			}
			
			if (character == '\377') break;
			
			if (character == 'p') { //pi
				obj.value = p;
				obj.type = '0';
				StackNums.push(obj);
				negative = false; 
				//cout << StackNums.top().value << endl;
				sstr.ignore();
				continue;
			}
			
			if (character == '-' and negative == true) { //-n
				obj.value = -1; obj.type = '0';
				StackNums.push(obj);
				obj.value = 0; obj.type = '*';
				StackOpers.push(obj);
				negative = false; 
				sstr.ignore();
				continue;
			}
			
			if (character == '(') { // (
				negative = true;
				obj.value = 0;
				obj.type = character; 
				StackOpers.push(obj); 
				sstr.ignore();
				//cout << StackOpers.top().type << endl;
				continue;
			}
			
			if (character == ')') { // )
				while (StackOpers.top().type != '('){ 
					if (Calculate(StackNums, StackOpers, obj) == false) return 0; 
					else continue;
				}
				StackOpers.pop(); 
				sstr.ignore(); 
				continue;
			}
			
			if ((character >= '0' and character <= '9') ) { //some number
				sstr >> number; 
				obj.value = number; 
				obj.type = '0';
				StackNums.push(obj);
				negative = false;
				//cout << StackNums.top().value << endl;
				continue;
			}
			
			if (character == '+' or (character == '-' and negative == false) or character == '*' or character == '/' or character == '^') { //+, -, *, /, ^
				if (StackOpers.empty()) { 
					obj.value = 0;
					obj.type = character; 
					StackOpers.push(obj); 
					sstr.ignore(); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				if (not(StackOpers.empty()) and priority(character) > priority(StackOpers.top().type)) {
					obj.value = 0;
					obj.type = character; 
					StackOpers.push(obj); 
					sstr.ignore(); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				if (not(StackOpers.empty()) and priority(character) <= priority(StackOpers.top().type)) { 
					if (Calculate(StackNums, StackOpers, obj) == false) return 0; 
				}
				continue;
			}
			
			if (character == 'e') { //exp
				char func[3];
				for (int i = 0; i < 3; i++) {
					character = sstr.peek();
					func[i] = character;
					sstr.ignore();
				}
				
				if (func[0] == 'e' and func[1] == 'x' and func[2] == 'p') { 
					obj.value = 0;
					obj.type = 'e'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
			}
			
			if (character == 's' or character == 'c' or character == 't') { //sqrt, sin, cos, tan, cot, sinh, cosh, tanh, coth
				char func[4];
				for (int i = 0; i < 4; i++) {
					character = sstr.peek();
					func[i] = character;
					sstr.ignore();
				}
				
				if (func[0] == 's' and func[1] == 'q' and func[2] == 'r' and func[3] == 't') {
					obj.value = 0;
					obj.type = 'u'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 's' and func[1] == 'i' and func[2] == 'n' and func[3] == 'r') {
					obj.value = 0;
					obj.type = 's'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'c' and func[1] == 'o' and func[2] == 's' and func[3] == 'r') { 
					obj.value = 0;
					obj.type = 'c';
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 't' and func[1] == 'a' and func[2] == 'n' and func[3] == 'r') {
					obj.value = 0;
					obj.type = 't'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'c' and func[1] == 'o' and func[2] == 't' and func[3] == 'r') { 
					obj.value = 0;
					obj.type = 'o';
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 's' and func[1] == 'i' and func[2] == 'n' and func[3] == 'd') { 
					obj.value = 0;
					obj.type = 'v'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'c' and func[1] == 'o' and func[2] == 's' and func[3] == 'd') { 
					obj.value = 0;
					obj.type = 'b';
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 't' and func[1] == 'a' and func[2] == 'n' and func[3] == 'd') {
					obj.value = 0;
					obj.type = 'g';
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'c' and func[1] == 'o' and func[2] == 't' and func[3] == 'd') {
					obj.value = 0;
					obj.type = 'm';
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 's' and func[1] == 'i' and func[2] == 'n' and func[3] == 'h') { 
					obj.value = 0;
					obj.type = 'h'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'c' and func[1] == 'o' and func[2] == 's' and func[3] == 'h') { 
					obj.value = 0;
					obj.type = 'j'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 't' and func[1] == 'a' and func[2] == 'n' and func[3] == 'h') { 
					obj.value = 0;
					obj.type = 'k'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'c' and func[1] == 'o' and func[2] == 't' and func[3] == 'h') { 
					obj.value = 0;
					obj.type = 'l'; 
					StackOpers.push(obj);
					//cout << StackOpers.top().type << endl;
					continue;
				}
			}
			
			if (character == 'l') { //ln, lg
				char func[2];
				for (int i = 0; i < 2; i++) {
					character = sstr.peek();
					func[i] = character;
					sstr.ignore();
				}
				
				if (func[0] == 'l' and func[1] == 'n') {
					obj.value = 0;
					obj.type = 'n';
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'l' and func[1] == 'g') { 
					obj.value = 0;
					obj.type = 'd'; 
					StackOpers.push(obj);
					//cout << StackOpers.top().type << endl;
					continue;
				}
			}
			
			if (character == 'a') { //acos, asin, atan, acot
				char func[4];
				for (int i = 0; i < 4; i++) {
					character = sstr.peek();
					func[i] = character;
					sstr.ignore();
				}
				
				if (func[0] == 'a' and func[1] == 's' and func[2] == 'i' and func[3] == 'n') {
					obj.value = 0;
					obj.type = 'q'; 
					StackOpers.push(obj);
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'a' and func[1] == 'c' and func[2] == 'o' and func[3] == 's') {
					obj.value = 0;
					obj.type = 'w'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'a' and func[1] == 't' and func[2] == 'a' and func[3] == 'n') {
					obj.value = 0;
					obj.type = 'y'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'a' and func[1] == 'c' and func[2] == 'o' and func[3] == 't') { 
					obj.value = 0;
					obj.type = 'r';
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
			}
			
			if (character == 'f') { //n!
				char func[4];
				for (int i = 0; i < 4; i++) {
					character = sstr.peek();
					func[i] = character;
					sstr.ignore();
				}
				if (func[0] == 'f' and func[1] == 'a' and func[2] == 'c' and func[3] == 't') {
					obj.value = 0;
					obj.type = 'f'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
			}
			
			if (character == 'b' or character == 'o') { //bin, oct
				char func[3];
				for (int i = 0; i < 3; i++) {
					character = sstr.peek();
					func[i] = character;
					sstr.ignore();
				}
				
				if (func[0] == 'b' and func[1] == 'i' and func[2] == 'n') {
					obj.value = 0;
					obj.type = '2'; 
					StackOpers.push(obj); 
					//cout << StackOpers.top().type << endl;
					continue;
				}
				
				if (func[0] == 'o' and func[1] == 'c' and func[2] == 't') { //�������� ��
					obj.value = 0;
					obj.type = '8';
					StackOpers.push(obj);
					//cout << StackOpers.top().type << endl;
					continue;
				}
			}
			
			else { 
				cout << "  ������ ����� � ���������!" << endl;
				return 0;
			}
		}
		//cout << StackNums.top().value << ' '; cout << StackOpers.top().type << endl;
		while (not(StackOpers.empty())) {
			if (Calculate(StackNums, StackOpers, obj) == false) {
				system ("pause");
				return 0;
			}
			else {
				continue;
			}
		}
		cout << "  �����: " << StackNums.top().value << endl;
	}
	system ("pause");
	return 0;
}
