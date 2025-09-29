#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

string custom_reverse(const string &s) {
    string r;
    r.reserve(s.size());
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        r.push_back(s[i]);
    }
    return r;
}

bool is_vowel(char c) {
    char u = tolower(c);
    return (u=='a' || u=='e' || u=='i' || u=='o' || u=='u');
}

string int_to_string(int x) {
    stringstream ss;
    ss << x;
    return ss.str();
}

int string_to_int(const string &s) {
    stringstream ss(s);
    int x=0;
    ss >> x;
    return x;
}

string encode_machine(const string &word) {
    if (word.empty()) return "";

    //hapus vokal
    string consonants;
    for (size_t i=0; i<word.size(); ++i) {
        if (!is_vowel(word[i])) consonants.push_back(word[i]);
    }

    //reverse konsonan
    string rev = custom_reverse(consonants);

    //ASCII dari huruf pertama
    int ascii_val = (int)word[0];
    string ascii_str = int_to_string(ascii_val);

    //sisipkan di tengah
    size_t mid = rev.size()/2;
    string result = rev.substr(0, mid) + ascii_str + rev.substr(mid);

    return result;
}


pair<char,string> decode_machine(const string &password) {
    int n = (int)password.size();
    int start=-1, end=-1;
    for (int i=0; i<n; ++i) {
        if (isdigit((unsigned char)password[i])) {
            if (start==-1) start=i;
            end=i;
        } else {
            if (start!=-1 && end!=-1) break;
        }
    }
    if (start==-1) return make_pair('\0',"");

    string digits = password.substr(start, end-start+1);
    int ascii_val = string_to_int(digits);
    char first_char = (char)ascii_val;

    string revCons = password.substr(0,start) + password.substr(end+1);
    string consonants_original = custom_reverse(revCons);

    return make_pair(first_char, consonants_original);
}


int main() {
    cout << "=== Mesin Dua Arah ===\n";
    cout << "1. Encode kata\n";
    cout << "2. Decode sandi\n";
    cout << "Pilih mode: ";
    int mode; cin >> mode;
    cin.ignore();

    if (mode==1) {
        string word;
        cout << "Masukkan kata asli: ";
        getline(cin, word);
        cout << "Sandi hasil mesin: " << encode_machine(word) << endl;
    } 
    else if (mode==2) {
        string code;
        cout << "Masukkan sandi: ";
        getline(cin, code);
        pair<char,string> res = decode_machine(code);
        if (res.first=='\0') {
            cout << "Gagal decode: tidak ada blok digit.\n";
        } else {
            cout << "Huruf pertama: " << res.first 
                 << " (ASCII=" << (int)res.first << ")\n";
            cout << "Urutan konsonan (asli): " << res.second << endl;
            cout << ">> Sisipkan vokal sendiri untuk menebak kata aslinya.\n";
        }
    }
    else {
        cout << "Mode tidak valid.\n";
    }

    return 0;
}

