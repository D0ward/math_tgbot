#include <iostream>
#include <vector>
#include <fstream>

using namespace std; // ����� �������  ������� ������ 1.0.0 by ������� from School Slon

void vivod(vector<vector<double> >a)
{
    int n = a.size(), m = a[0].size();
    for(int i = 0;i < n;++i)
    {
        for(int j = 0; j < m;++j)
            cout << a[i][j] << ' ';
        cout << '\n';
    }
    cout << "#######################\n";
}

double det(vector<vector<double> > a)
{
    int n = a.size();

    if (n == 2)
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    double result = 0;
    for(int j = 0; j < n;++j)
    {
        vector<vector<double> >b;
        for(int st = 1; st < n;++st)
        {
            vector<double>c;
            bool flag = false;
            for(int str = 0; str < n;++str)
            {
                if(str == j)
                    flag = true;
                if(flag && str < n - 1)
                    c.push_back(a[st][str+1]);
                else if(flag && str == n - 1)
                    continue;
                else
                    c.push_back(a[st][str]);
            }
            b.push_back(c);
        }
        if(j % 2 == 0)
            result += a[0][j] * det(b);
        else
            result -= a[0][j] * det(b);
    }
    return result;
}

vector<vector<double> > swap_sl(vector<vector<double> > a, int num)
{
    int n = a.size();
    int m = a[0].size();
    for(int i = 0; i < n;++i)
        a[i][num] = a[i][m-1];

    return a;
}

int main()
{
    ifstream file_in("/home/alexey/programms/python/telegram_bot/math/matrix.txt");
    ofstream out("/home/alexey/programms/python/telegram_bot/math/result.txt");
    int n; file_in >> n;
    cout << "N = " << n << '\n';
    vector<vector<double> >matrix(n,vector<double>(n+1, 0));
    for(int i = 0;i < n;++i)
        for(int j = 0; j <= n;++j)
            file_in >> matrix[i][j];
    for(int i = 0;i < n;++i){
        for(int j = 0; j <= n;++j)
            cout << matrix[i][j] << ' ';
        cout << '\n';
    }
    //vivod(matrix);
    //cout << det(matrix) << '\n';

    vector<vector<double> >a(n, vector<double>(n, 0));
    for(int i = 0;i < n;++i)
        for(int j = 0; j < n;++j)
            a[i][j] = matrix[i][j];
    double detA = det(a);
    cout << detA << '\n';
    if(detA == 0)
    {
        out << "No answer" << '\n';
        return 0;
    }
    vector<double>det_x(n);
    for(int i = 0; i <n;++i)
    {
        det_x[i] = det(swap_sl(matrix, i));
        //out << "det_x = " << det_x[i] << '\n';
       // vivod(swap_sl(matrix, i));
    }
    //out << "Answer" << '\n';
    for(int i = 0;i < n;++i)
    {
        out << "x" << i+1 << " = " << det_x[i]/detA << ' ';
    }
    return 0;

}
