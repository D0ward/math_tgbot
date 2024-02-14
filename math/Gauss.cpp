#include <iostream>
#include <fstream>
#include <vector>

using namespace std; // ����� ������ ������� ������ 1.0.0 by ������� from School Slon

void zero(vector<vector<double> >& a, int start)
{
    int n = a.size();
    int m = a[0].size();
    vector<double>b = a[start];
    for (int i = start+1; i < n; ++i)
    {
        vector<double>c = a[i];
        for (int j = start; j < m; ++j)
        {
            a[i][j] -= b[j];
        }
        b = c;
    }
}

void one(vector<vector<double> >& a, int start)
{
    int n = a.size();
    int m = a[0].size();
    for (int i = start; i < n; ++i)
    {
        if (a[i][start] != 0)
        {
            double k = a[i][start];
            for (int j = start; j < m; ++j)
            {
                a[i][j] /= k;
            }
        }
    }
}

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


int main()
{
    ifstream file_in("/home/alexey/programms/python/telegram_bot/math/matrix.txt");
    ofstream out("/home/alexey/programms/python/telegram_bot/math/result.txt");
    int n, m; file_in >> n;
    cout << "n = " << n << ' ';
    m = n + 1;
    cout << "m = " << m << '\n';
    vector<vector<double> >a(n,vector<double>(n+1, 0));
    
    for(int i = 0;i < n;++i)
        for(int j = 0; j < m;++j)
            file_in >> a[i][j];
    vivod(a);
    for(int u = 0; u < n-1;++u)
    {
        one(a, u);
        vivod(a);

        zero(a, u);
        vivod(a);
    }

    //out << "Answer\n";

    vector<double> answer(n, 0);
    answer[n-1] = a[n-1][m-1] / a[n-1][m-2];
    for(int i = n - 2; i >= 0;--i)
    {
        double k = 0;
        for(int j = i + 1; j < n;++j)
        {
            k += answer[j] * a[i][j];
        }
        answer[i] = (a[i][m-1] - k) / a[i][i];
    }
    for(int i = 0; i < n;++i)
        out <<"x" << i+1 << " = " <<  answer[i] << ' ';
    return 0;
}
