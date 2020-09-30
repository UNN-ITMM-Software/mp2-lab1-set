#include <conio.h>
#include "tbitfield.h"
#include "tset.h"
#include <conio.h>
#include <clocale>



int main(int argc, char* argv[])
{
    int n, m, k, count;
    cout << "Тестирование программ поддержки понятия множества" << endl;
    cout << "Решето Эратосфена" << endl;
    cout << "Ведите верхнюю границу целых значений ";
    cin >> n;
    TSet s(n + 1);
    for (m = 2; m <= n; m++) s.InsElem(m);
    for (m = 2; m * m < n; m++)
        if (s.IsMember(m))
            for (k = 2 * m; k <= n; k += m)
                if (s.IsMember(k)) s.DelElem(k);
    cout << "Печать простых чисел" << endl;
    count = 0; k = 1;
    for (m = 2; m <= n; m++)
        if (s.IsMember(m)) {
            count++;
            cout << m << " ";
            if (k++ % 10 == 0) cout << endl;
        }
    cout << endl;
    cout << "В первых" << n << "числах" << count << "простых" << endl;
    return 0;
}
