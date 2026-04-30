// This is Capacity Scaling in Flow Network
// NOTICE: the graph in the struct use zero base index

struct FLOW
{
    struct EDGE
    {
        int a, b; // a -> b
        long long cap, val;
    };

    int n;
    long long cur;
    vector<EDGE> edge;
    vector<vector<int>> graph;
    vector<int> par;

    inline void Init(int new_n)
    {
        n = new_n;
        cur = 0;
        edge.clear();
        graph.clear();
        par.clear();
        edge.resize(n);
        graph.resize(n);
        par.resize(n);
    }
    inline void AddEdge(int a, int b, long long c)
    {
        graph[a].push_back(edge.size());
        edge.push_back({a, b, c, 0LL});
        graph[b].push_back(edge.size());
        edge.push_back({b, a, 0LL, 0LL});
        cur = max(cur, c);
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
            for (auto & i : graph[s])
            {
                if (par[edge[i].b] == -1 && edge[i].cap - edge[i].val >= cur)
                {
                    par[edge[i].b] = i;
                    dq.push_back(edge[i].b);
                }
            }
        }
        return par[t] != -1;
    }
    inline long long Process(int s, int t, long long val = 1e18)
    {
        int ind = par[t];
        if (s == t)
        {
            return val;
        }
        val = min(val, Process(s, edge[ind].a, val));
        edge[ind].val += val;
        edge[ind ^ 1].val -= val;
        return val;
    }
    inline long long MaxFlow(int s, int t)
    {
        long long cost = 0;
        cur = 1LL << __lg(cur);
        for (cur = 1LL << __lg(cur); cur > 0; cur >>= 1)
        {
            while (Check(s, t))
            {
                cost += Process(s, t);
            }
        }
        return cost;
    }
};
