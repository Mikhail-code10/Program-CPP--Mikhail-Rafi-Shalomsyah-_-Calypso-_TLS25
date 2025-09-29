#include <iostream>
#include <vector>
using namespace std;

string lampu(int t) {
    int start = 45;           // detik awal (kuning)
    int cycle = 103;          // total panjang siklus
    int offset = (t - start) % cycle;
    if (offset < 0) offset += cycle; // jaga-jaga kalau negatif

    if (offset < 3) return "Kuning";        // 0-2
    else if (offset < 83) return "Merah";   // 3-82
    else return "Hijau";                    // 83-102
}

int main() {
    int arr[] = {80, 135, 150, 212};
    int n = 4;
    for (int i = 0; i < n; i++) {
        int t = arr[i];
        cout << "Detik " << t << " -> " << lampu(t) << endl;
    }
    return 0;
}

