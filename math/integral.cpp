#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;// Методы прямоугольников и трапеции рабочая версия 1.0.0 by Алексей from School Slon

double f(double x)
{
    return sin(x);
}

double left_rect(double a, double b, double delta)
{
    int n = (b-a)/delta;
    double answer = 0;
    for(int i = 0;i < n;++i)
    {
        answer += f(a+i * delta) * delta;
    }
    return answer;
}

double right_rect(double a, double b, double delta)
{
    int n = (b-a)/delta;
    double answer = 0;
    for(int i = 1;i <= n;++i)
    {
        answer += f(a+i * delta) * delta;
    }
    return answer;
}

double trap(double a, double b, double delta)
{
    int n = (b-a)/delta;
    double answer = 0;
    for(int i = 0; i < n;++i)
    {
        answer += 2 * f(a + i * delta);
    }
    return answer *(delta / 2);
}

int main()
{
    ifstream file_in("input_int.txt");
    double a, b, delta;int n; file_in >> a >> b >> n;
    delta = (b-a) / n;

    cout << "method left " << left_rect(a, b, delta) << '\n';
    cout << "method right " << right_rect(a, b, delta) << '\n';
    cout << "method trapeze " << trap(a, b, delta) << '\n';
}
