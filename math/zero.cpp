#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std; // ������� ������� by ������� �������� from School Slon

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

double bin_search(double l, double r) // ����� ���� ������� ������� ������� �� 2
{
    double mid = (r + l) / 2;
    if(abs(r - l) < eps || abs(f(mid)) <= eps)
        return mid;
    else
        if(f(mid) * f(l) < 0)
            return bin_search(l, mid);
        else
            return bin_search(mid, r);
}

double hord(double a, double b, double eps) // ����� ���� ������� ������� ����
{
    double x = b - f(b) / ((f(b) - f(a)) / (b - a));
    if(abs(b - a) < eps || abs(f(x)) <= eps)
        return x;
    if(f(x) * f(a) < 0)
        return hord(a, x, eps);
    else
        return hord(x, b, eps);
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

pair<double, double>grad(double x, double y)
{

    pair<double, double> G = {(f(x + eps, y) - f(x, y)) / eps, (f(x, y + eps) - f(x, y)) / eps};

    G.first *= h;
    G.second *= h;

    pair<double, double> x_new = {x - G.first, y - G.second};
    pair<double, double> usl1 = {x_new.first - x, x_new.second - y};
    pair<double, double> G_new = {(f(x_new.first + eps, x_new.second) - f(x_new.first, x_new.second)) / eps, (f(x_new.first, x_new.second + eps) - f(x_new.first, x_new.second)) / eps};

    double len = pow(usl1.first * usl1.first + usl1.second* usl1.second, 0.5);
    double G_new_len = pow(G_new.first*G_new.first + G_new.second*G_new.second, 0.5);
    if((abs(len) > eps) || (abs(f(x_new.first, x_new.second) - f(x, y)) > eps) || (abs(G_new_len) > eps))
        return grad(x_new.first, x_new.second);
    else return x_new;
}

int main()
{
    
    ifstream file_in("input_func.txt");
    double a, b; file_in >> a >> b >> eps;

    cout << "bin_search = " << bin_search(a, b) << '\n';
    cout << "hord = " << hord(a, b, eps) << '\n';

}
