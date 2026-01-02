#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "NNYNNYnyNYYY";
    int cl = 7;
    int pen = 0;

    for (int i = 0; i < s.size(); i++) {
        char c = toupper(s[i]);
        if (i < cl) {
            if (c == 'N') pen++;
        } else {
            if (c == 'Y') pen++;
        }
    }

    cout << pen;
    return 0;
}


#include <bits/stdc++.h>
using namespace std;

int main() {
    string c = "YYNY";
    vector<int> l;
    int p = count(c.begin(), c.end(), 'Y');

    l.push_back(p);

    for (char ch : c) {
        if (ch == 'Y') p--;
        else p++;
        l.push_back(p);
    }

    cout << min_element(l.begin(), l.end()) - l.begin();
    return 0;
}


#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "BEGIN BEGIN BEGIN Y Y N Y END N N N N N END Y Y Y Y END";
    stringstream ss(s);
    vector<string> tokens;
    string word;

    while (ss >> word) tokens.push_back(word);

    vector<string> stackData, logs;

    for (string &t : tokens) {
        if (t != "END") {
            stackData.push_back(t);
        } else {
            string temp = "";
            while (!stackData.empty() && stackData.back() != "BEGIN") {
                temp += stackData.back();
                stackData.pop_back();
            }
            if (!stackData.empty()) stackData.pop_back();
            reverse(temp.begin(), temp.end());
            logs.push_back(temp);
        }
    }

    vector<int> ans;

    for (string &a : logs) {
        vector<int> l;
        int p = count(a.begin(), a.end(), 'Y');
        l.push_back(p);

        for (char ch : a) {
            if (ch == 'Y') p--;
            else p++;
            l.push_back(p);
        }

        ans.push_back(min_element(l.begin(), l.end()) - l.begin());
    }

    for (int x : ans) cout << x << " ";
    return 0;
}


#include <bits/stdc++.h>
using namespace std;

unordered_map<string, unordered_map<string, double>> d;

double dfs(string a, string b, unordered_set<string> &vis) {
    if (a == b) return 1.0;
    vis.insert(a);

    for (auto &x : d[a]) {
        if (!vis.count(x.first)) {
            double val = dfs(x.first, b, vis);
            if (val != -1) return x.second * val;
        }
    }
    return -1;
}

int main() {
    vector<pair<string,string>> eq = {{"a","b"},{"b","c"}};
    vector<double> val = {2.0,3.0};
    vector<pair<string,string>> queries = {{"a","c"},{"b","a"},{"a","e"}};

    for (int i = 0; i < eq.size(); i++) {
        d[eq[i].first][eq[i].second] = val[i];
        d[eq[i].second][eq[i].first] = 1.0 / val[i];
    }

    vector<double> res;

    for (auto &q : queries) {
        if (!d.count(q.first) || !d.count(q.second)) {
            res.push_back(-1);
        } else {
            unordered_set<string> vis;
            res.push_back(dfs(q.first, q.second, vis));
        }
    }

    for (double x : res) cout << x << " ";
    return 0;
}


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void solve(string ex, set<string> &res) {
        int cb = ex.find('}');
        if (cb == string::npos) {
            res.insert(ex);
            return;
        }

        int ob = ex.rfind('{', cb);
        string first = ex.substr(0, ob);
        string mid = ex.substr(ob + 1, cb - ob - 1);
        string last = ex.substr(cb + 1);

        stringstream ss(mid);
        string token;

        while (getline(ss, token, ',')) {
            solve(first + token + last, res);
        }
    }

    vector<string> braceExpansionII(string ex) {
        set<string> res;
        solve(ex, res);
        return vector<string>(res.begin(), res.end());
    }
};


#include <bits/stdc++.h>
using namespace std;

unordered_map<string, unordered_map<string, int>> d2;

int dfs2(string x, string y, unordered_set<string> &vis) {
    if (x == y) return 0;
    vis.insert(x);

    int mini = INT_MAX;

    for (auto &n : d2[x]) {
        if (!vis.count(n.first)) {
            int cost = dfs2(n.first, y, vis);
            if (cost != -1) {
                mini = min(mini, n.second + cost);
            }
        }
    }

    vis.erase(x);
    return mini == INT_MAX ? -1 : mini;
}

int main() {
    string s = "US,UK,UPS,5:US,CA,FedEx,3:CA,UK,DHL,7";
    stringstream ss(s);
    string part;

    while (getline(ss, part, ':')) {
        stringstream ps(part);
        vector<string> v;
        string x;
        while (getline(ps, x, ',')) v.push_back(x);
        d2[v[0]][v[1]] = stoi(v[3]);
    }

    cout << dfs2("US", "UK", unordered_set<string>());
    return 0;
}


#include <bits/stdc++.h>
using namespace std;

class Solution2 {
public:
    vector<string> res;
    vector<vector<char>> groups;

    vector<string> expand(string s) {
        int i = 0, n = s.size();

        while (i < n) {
            if (s[i] == '{') {
                i++;
                vector<char> temp;
                while (s[i] != '}') {
                    if (s[i] != ',') temp.push_back(s[i]);
                    i++;
                }
                sort(temp.begin(), temp.end());
                groups.push_back(temp);
                i++;
            } else {
                groups.push_back({s[i]});
                i++;
            }
        }

        string cur;
        dfs(0, cur);
        sort(res.begin(), res.end());
        return res;
    }

    void dfs(int idx, string &cur) {
        if (idx == groups.size()) {
            res.push_back(cur);
            return;
        }

        for (char c : groups[idx]) {
            cur.push_back(c);
            dfs(idx + 1, cur);
            cur.pop_back();
        }
    }
};


#include <bits/stdc++.h>
using namespace std;

class TransactionValidator {
public:
    static constexpr double MIN_AMOUNT = 1;
    static constexpr double MAX_AMOUNT = 10000;

    static inline const unordered_set<string> BLOCKED_METHODS = {
        "CRYPTO", "GIFT_CARD"
    };

    static inline const vector<string> ERROR_PRIORITY = {
        "ERR_MISSING_FIELD",
        "ERR_BLOCKED_PAYMENT_METHOD",
        "ERR_AMOUNT_OUT_OF_RANGE",
        "ERR_BEHAVIOR_MISMATCH"
    };

    struct Transaction {
        string id, userId, currency, country, paymentMethod;
        double amount;
        string timeBucket;
    };

    struct UserProfile {
        unordered_set<string> countries;
        unordered_set<string> timeBuckets;
        unordered_set<string> amountBuckets;
    };

    static vector<string> validate(Transaction &tx, UserProfile &profile) {
        unordered_set<string> errors;

        if (tx.id.empty() || tx.userId.empty() || tx.currency.empty() ||
            tx.country.empty() || tx.paymentMethod.empty()) {
            errors.insert("ERR_MISSING_FIELD");
        }

        if (tx.amount < MIN_AMOUNT || tx.amount > MAX_AMOUNT) {
            errors.insert("ERR_AMOUNT_OUT_OF_RANGE");
        }

        if (BLOCKED_METHODS.count(tx.paymentMethod)) {
            errors.insert("ERR_BLOCKED_PAYMENT_METHOD");
        }

        int matches = 0;

        if (profile.countries.count(tx.country)) matches++;
        if (profile.timeBuckets.count(tx.timeBucket)) matches++;
        if (profile.amountBuckets.count(amountBucket(tx.amount))) matches++;

        double matchRatio = matches / 3.0;
        if (matchRatio < 0.5) {
            errors.insert("ERR_BEHAVIOR_MISMATCH");
        }

        vector<string> result;
        for (const string &e : ERROR_PRIORITY) {
            if (errors.count(e)) result.push_back(e);
            if (result.size() == 2) break;
        }

        if (result.empty()) result.push_back("OK");
        return result;
    }

    static string amountBucket(double amt) {
        if (amt < 100) return "LOW";
        if (amt <= 1000) return "MEDIUM";
        return "HIGH";
    }
};


#include <bits/stdc++.h>
using namespace std;

class Solution3 {
public:
    int minTransfers(vector<vector<int>> &transactions) {
        unordered_map<int, int> balance;

        for (auto &t : transactions) {
            balance[t[0]] -= t[2];
            balance[t[1]] += t[2];
        }

        vector<int> debt;
        for (auto &p : balance) {
            if (p.second != 0) debt.push_back(p.second);
        }

        return dfs(debt, 0);
    }

    int dfs(vector<int> &d, int i) {
        while (i < d.size() && d[i] == 0) i++;
        if (i == d.size()) return 0;

        int ans = INT_MAX;
        for (int j = i + 1; j < d.size(); j++) {
            if (d[i] * d[j] < 0) {
                d[j] += d[i];
                ans = min(ans, 1 + dfs(d, i + 1));
                d[j] -= d[i];
            }
        }
        return ans;
    }
};


#include <bits/stdc++.h>
using namespace std;

class Solution4 {
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        vector<int> cost(n, INT_MAX);
        cost[src] = 0;

        for (int i = 0; i <= k; i++) {
            vector<int> tmp = cost;
            for (auto &f : flights) {
                if (cost[f[0]] != INT_MAX) {
                    tmp[f[1]] = min(tmp[f[1]], cost[f[0]] + f[2]);
                }
            }
            cost = tmp;
        }

        return cost[dst] == INT_MAX ? -1 : cost[dst];
    }
};


#include <bits/stdc++.h>
using namespace std;

class Solution5 {
public:
    int minimumTime(int n, vector<vector<int>> &relations, vector<int> &time) {
        vector<vector<int>> g(n);
        vector<int> indeg(n, 0);

        for (auto &r : relations) {
            g[r[0] - 1].push_back(r[1] - 1);
            indeg[r[1] - 1]++;
        }

        queue<int> q;
        vector<int> dp(n);

        for (int i = 0; i < n; i++) {
            dp[i] = time[i];
            if (indeg[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                dp[v] = max(dp[v], dp[u] + time[v]);
                if (--indeg[v] == 0) q.push(v);
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};
