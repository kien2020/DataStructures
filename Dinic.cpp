// zero-based graph flow processing using Dinic algorithm

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
    vector<int> lvl, ptr;

    inline void Init(int new_n)
    {
        n = new_n;
        g.resize(n);
        lvl.resize(n);
        ptr.resize(n);
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
        fill_n(lvl.begin(), n, -1);
        lvl[s] = 0;
        while (!dq.empty())
        {
            s = dq.front();
            dq.pop_front();
            for (auto &i : g[s])
            {
                if (e[i].cap > e[i].val && lvl[e[i].b] == -1)
                {
                    lvl[e[i].b] = lvl[s] + 1;
                    dq.push_back(e[i].b);
                }
            }
        }
        return lvl[t] != -1;
    }
    inline long long Process(int s, int t, long long v)
    {
        long long cur;
        if (v == 0 || s == t)
        {
            return v;
        }
        for (int &i = ptr[s], id; i < g[s].size(); ++i)
        {
            id = g[s][i];
            if (lvl[e[id].b] == lvl[s] + 1 && e[id].cap > e[id].val)
            {
                cur = Process(e[id].b, t, min(v, e[id].cap - e[id].val));
                if (cur > 0)
                {
                    e[id].val += cur;
                    e[id ^ 1].val -= cur;
                    return cur;
                }
            }
        }
        return 0;
    }
    inline long long MaxFlow(int s, int t)
    {
        long long cost = 0, change;
        while (Check(s, t))
        {
            fill_n(ptr.begin(), n, 0);
            while (change = Process(s, t, 2e9))
            {
                cost += change;
            }   
        }
        return cost;
    }
};
