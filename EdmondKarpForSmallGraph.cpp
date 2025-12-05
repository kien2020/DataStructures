struct FLOW
{
    int n;
    int val[200][200], cap[200][200], par[200];
    vector<int> g[200];

    inline void Init(int new_n)
    {
        n = new_n;
        fill_n(g, n, vector<int>());
    }
    inline void AddEdge(int a, int b, int w)
    {
        g[a].push_back(b);
        g[b].push_back(a);
        val[a][b] = val[b][a] = 0;
        cap[a][b] = w;
        cap[b][a] = 0;
    }
    inline bool Check(int s, int t)
    {
        deque<int> dq = {s};
        fill_n(par, n, -1);
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
                if (cap[s][i] > val[s][i] && par[i] == -1)
                {
                    par[i] = s;
                    dq.push_back(i);
                }
            }
        }
        return par[t] != -1;
    }
    inline int Trace(int s, int t)
    {
        int change = 2e9;
        for (int i = t; i != s; i = par[i])
        {
            change = min(change, cap[par[i]][i] - val[par[i]][i]);
        }
        for (int i = t; i != s; i = par[i])
        {
            val[par[i]][i] += change;
            val[i][par[i]] -= change;
        }
        return change;
    }
    inline int MaxFlow(int s, int t)
    {
        int cost = 0;
        while (Check(s, t))
        {
            cost += Trace(s, t);
        }
        return cost;
    }
} flow;
