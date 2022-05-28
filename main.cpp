#include <bits/stdc++.h>
using namespace std;

const string templateString = "abcdefghijklmnopqrstuvwxyz012345";

vector<string> table;
string ciphertext;

// Hàm biến chữ thành số thập phân
int getCharNumber(char c)
{
  if (c >= 'a' & c <= 'z')
    return c - 'a';
  else
    return c - '0' + 1 + 'z' - 'a';
}

// Hàm biến số thập phân thành chữ
char getNumberChar(int x)
{
  if (x <= 25)
    return char(x + 'a');
  else
    return char(x - 26 + '0');
}

// Hàm chuyển chuỗi thành nhị phân
long long text2Bi(const string &s)
{
  long long ans = 0;
  string A = "";
  for (auto x : s)
  {
    int number = getCharNumber(x);
    string Bit = "";
    while (number)
    {
      Bit += char((number % 2) + '0');
      number /= 2;
    }
    reverse(Bit.begin(), Bit.end());
    while (Bit.size() < 5)
      Bit = "0" + Bit;
    A += Bit;
  }
  /* cout << A << "\n"; */
  for (auto x : A)
  {
    ans = ans * 2 + (x - '0');
  }
  return ans;
}

// Hàm chuyển nhị phân thành chuỗi
string bi2Text(long long Number)
{
  string ans = "";
  string bina = "";
  while (Number)
  {
    bina += char((Number % 2) + '0');
    Number /= 2;
  }
  reverse(bina.begin(), bina.end());
  while (bina.size() < ciphertext.size() * 5)
    bina = "0" + bina;
  for (int i = 0; i < bina.size(); i += 5)
  {
    int Num = 0;
    for (int j = i; j <= i + 4; j++)
    {
      Num = Num * 2 + bina[j] - '0';
    }
    ans += getNumberChar(Num);
  }
  return ans;
}

// Hàm giải mã
void decode(const string &s, const vector<string> &table)
{
  int N = table.size();
  for (long long mask = 0; mask < (1LL << table.size()); mask++)
  {
    long long sum = 0;
    for (int i = 0; i < table.size(); i++)
    {
      if (mask >> i & 1)
      {
        sum += text2Bi(table[N - i - 1]);
      }
    }
    sum = sum % (1LL << table.size());
    if (sum == text2Bi(s))
    {
      cout << bi2Text(mask) << "\n";
    }
  }
}

int main()
{
  // freopen("1.txt", "r", stdin);
  cin >> ciphertext;
  for (int i = 0; i < 5 * ciphertext.size(); i++)
  {
    string s;
    cin >> s;
    table.push_back(s);
  }
  decode(ciphertext, table);
  return 0;
}
