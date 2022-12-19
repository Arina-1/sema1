#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <math.h>

//1) перебираем нашу строчку

//2) проверка на знак + или -

//3) обрезаем наш член уравнения 

//4) проверка есть ли там x

//5) нет x - просто число

//6) есть x- надо искать индексы * и ^

//* нет такого символа - значит либо +x,x,-x

//индекс ^ = индекс '*'+2 позиции

// следовательно степень будет +3 позиции

// дальше просто преобразуем 



char * strcopy(const char* str,int from,int to)//копируем строку // обрезка строки

{
	int len = to-from;
	
    char *result = (char*)malloc(len);//выделение памяти(буфер)
	
    strncpy(result,str + from,len);//копируем строку с ограничением длины
	
    return result;
	
}

int getIndex(char *element, char chr) // получение индекса элемента

{

    char *x;//применить оператор приведения к операнду x
	
    int index;
	
    x = strchr(element,chr);//вхождение символа в строку(первое)
	
    if(x == NULL) // символа нет
	
    {
	
        return -1;    
		
    }
	
    index = (int)(x-element);
	
    return index;
	
	
}

double polynomial(const char* equation, double x)

{

    int len = strlen(equation); // длинна нашего выражения
	
    double y = 0;
	
    int startIndex = 0; // стартовый для обрезки
	
    for(int i = 1; i <= len; i++)
	
    {
	
        if(i == len||equation[i] == '+' || (equation[i] == '-' && equation [i-1] != '^')) // член многочлена
		
        {
		
            char *element = strcopy(equation,startIndex,i); // получаем член
			
            int index = getIndex(element,'x');
			
            if(index == -1) // не содержит x
			
            {
			
                y += atoi(element); // просто переводим в число
				
            }
			
            else // содержит x
			
            {
			
                int indexInc = getIndex(element,'*');
				
                int a;
				
                if(indexInc == -1) // нет коэфа
				
                {
				
                    if(element[0] == '+')// +x
					
                    {
					
                        a = 1;
						
                        indexInc = 0;
						
                    }
					
                    else if(element[0] == 'x')// x
					
                    {
					
                        a = 1;
						
                    }
					
                    else // -x
					
                    {
					
                        a = -1;
						
                        indexInc = 0; // сдвиг тк - перед x
						
                    }
					
                }
				
                else // коэф есть
				
                { 
				
                    a = atoi(strcopy(element,0,indexInc));// получаем коф перед иксом
					
                }
				
                int p = 1; // дефолт степень 1
				
                int indexPow = indexInc + 3; // индекс нашего ^
				
                int lenEl = strlen(element);
				
                if(indexPow < lenEl) // получаем степень, если та есть.
				
                {
				
                    p = atoi(strcopy(element,indexPow,lenEl));
					
                }
				
                y += a * pow(x,p); // считаем пример
				
            }
			
            startIndex = i; // наш новый многочлен начнётся с этого индекса
			
        }
		
    }
	
    return y;
	
}

int main()

{

    const char *expr = "x^3-50+2*x+5*x^2";
	
    double x = 3;
	
    printf("y = %s by x = %f\nresult = %f",expr,x,polynomial(expr, x));
	
    return 0;
	
}
