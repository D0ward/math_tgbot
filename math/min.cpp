#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std; 

double eps, fi = 1.6180339, h = 1.0;


double f(double x)
{
    return x*x;
}

double f(double x, double y)
{
    return sin(x*x/2 - y*y/4 + 3) * cos(2*x + 1 - exp(y));
}

double prois(double x)
{
   return (f(x + eps) - f(x)) / eps;
}

double bin_min(double l, double r) // ����� �������� ������� ������� ������� �� 2
{
    double mid = (r+l) / 2;
    double x = prois(l);
    //cout << l << ' ' << mid << ' ' << r << '\n';
    if(abs(x) <= eps)
        return l;
    else{
        if(prois(mid) * x > 0)
            return bin_min(mid, r);
        else
            return bin_min(l, mid);
    }
}

double gold_min(double a, double b,double x1, double x2, double y1, double y2) // ����� �������� ������� ������� �������� �������
{
    if(abs(b-a) < eps)
        return (a+b)/2;

    if(y1 >= y2)
        {
            a = x1;
            x1 = x2;
            y1 = y2;
            x2 = a+ (b-a)/fi;
            y2 = f(x2);
        }
    else
        {
            b = x2;
            x2 = x1;
            y2 = y1;
            x1 = b - (b-a)/fi;
            y1 = f(x1);
        }
    return gold_min(a, b, x1, x2, y1, y2);
}

int main()
{
    ifstream file_in("/home/alexey/programms/python/telegram_bot/math/input_func.txt");
    ofstream out("/home/alexey/programms/python/telegram_bot/math/result.txt");
    double a, b; file_in >> a >> b >> eps;

    //pair<double, double> ans = grad(a, b);
    //cout << ans.first << ' ' << ans.second << '\n';
    double x1 = b - (b-a)/fi;
    double x2 = a + (b-a)/fi;
    double y1 = f(x1);
    double y2 = f(x2);
    out << "min_bin = " << bin_min(a, b) << '\n';
    out << "min_gold = " << gold_min(a, b, x1, x2, y1, y2) << '\n';
    //cout << "bin_search = " << bin_search(a, b) << '\n';
    //cout << "hord = " << hord(a, b, eps) << '\n';

}
