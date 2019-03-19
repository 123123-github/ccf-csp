// !!! SUBSTR (pos, len) !!!
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int len;
string line;

string deal_line(const string& str)
{
	string result = str;
	
	// deal EM
	string temp = str, s = "";
	bool first = 1;
	for (int i=0; temp[i]; i++) {
		if (temp[i] == '_') {
			first? s.append("<em>"): s.append("</em>");
			first = !first;
		}
		else s += temp[i];
	}
	result = s;
	
	// deal LINK
	temp.clear();
	int a, b, c, k = 0, len = s.length();
	while (s.find('[', k) != string::npos) {
		for (int i=k; i<len; i++) {
			if (s[i] == '[') a = i;
			else if (s[i] == ']') b = i;
			else if (s[i] == ')') { c = i; break; }
		}
		const string& href = s.substr(b+2, c - b - 2);
		const string& name = s.substr(a+1, b - a - 1);
		temp += s.substr(k, a - k) + "<a href=\"" + href + "\">" + name + "</a>";
		k = c + 1;
	}
	if (!temp.empty()) result = temp + s.substr(k, len - k);
	
	return result;
}

void deal_head(int h, const string& s)
{
	cout << "<h" << h << ">" << deal_line(s) << "</h" << h << ">";
}

void deal_list()
{
	cout << "<ul>\n";
	
	int k = 2; while (line[k] == ' ') k++;
	cout << "<li>" << deal_line(line.substr(k, len-k)) << "</li>\n";
	
	while (getline(cin, line)) {
		len = line.length();
		if (len == 0) break;
		k = 2; while (line[k] == ' ') k++;
		cout << "<li>" << deal_line(line.substr(k, len-k)) << "</li>\n";
	}
	cout << "</ul>";
}

void deal_par()
{
	cout << "<p>" << deal_line(line);
	while (getline(cin, line)) {
		if (line.length() == 0) break;
		cout <<  '\n' << deal_line(line);
	}
	cout << "</p>";
}

int main()
{	
	while (getline(cin, line)) {
		int len = line.length();
		if (len == 0) continue;
		
		if (line[0] == '#') {				// HEAD
			int h, k;
			for (h=0; h<len && line[h]=='#'; h++);		// '#' num
			k = h; while (line[k] == ' ') k++;			// jump BLANK
			deal_head(h, line.substr(k, len - k));
		} else if (line[0] == '*') {		// LIST
			deal_list();
		} else {							// PARA
			deal_par();
		}
		
		cout << '\n';
	}
	
	return 0;
}
