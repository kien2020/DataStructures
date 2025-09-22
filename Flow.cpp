// This is a flow code using edmonds - karp algorithm
// NOTICE: the graph in the struct use zero base index

struct FLOW
{
    struct EDGE
    {
        int a, b;
        long long cap, val;
    };

    int n;
    vector<EDGE> e;
    vector<vector<int>> g;
    vector<int> par;

    inline void Init(int new_n)
    {
        n = new_n;
        g.resize(n);
        par.resize(n);
    }
    inline void AddEdge(int a, int b, int c)
    {
        g[a].push_back(e.size());
        e.push_back({a, b, c, 0});
        g[b].push_back(e.size());
        e.push_back({b, a, 0, 0});
    }
    inline bool Check(int s, int t)
    {
        deque<int> dq = {s};
        fill_n(par.begin(), n, -1);
        par[s] = -2;
        while (!dq.empty())
        {
            s = dq.front();
            dq.pop_front();
            if (s == t)
            {
                break;
            }
            for (auto &i : g[s])
            {
                if (e[i].cap > e[i].val && par[e[i].b] == -1)
                {
                    par[e[i].b] = i;
                    dq.push_back(e[i].b);
                }
            }
        }
        return par[t] != -1;
    }
    inline long long Process(int s, int t)
    {
        long long change = 1e18;
        for (int i = t; i != s; i = e[par[i]].a)
        {
            change = min(change, e[par[i]].cap - e[par[i]].val);
        }
        for (int i = t; i != s; i = e[par[i]].a)
        {
            e[par[i]].val += change;
            e[par[i] ^ 1].val -= change;
        }
        return change;
    }
    inline long long MaxFlow(int s, int t)
    {
        long long cost = 0;
        while (Check(s, t))
        {
            cost += Process(s, t);
        }
        return cost;
    }
} flow;
