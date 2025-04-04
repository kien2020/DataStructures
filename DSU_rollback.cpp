class DSU_stack
{
private:
    vector<int> par, sz;
    vector<pair<int, int>> operations;

public:
    inline void Init(int new_size)
    {
        operations.clear();
        par.clear();
        par.resize(new_size);
        sz.clear();
        sz.resize(new_size, 1);
        for (int i = 0; i < new_size; ++i)
        {
            par[i] = i;
        }
    }
    inline int GetPar(int inp)
    {
        return (inp == par[inp] ? inp : GetPar(par[inp]));
    }
    inline bool Unity(int ina, int inb)
    {
        ina = GetPar(ina);
        inb = GetPar(inb);
        if (ina != inb)
        {
            if (sz[ina] < sz[inb])
            {
                swap(ina, inb);
            }
            operations.push_back({ina, inb});
            sz[ina] += sz[inb];
            par[inb] = ina;
            return 1;
        }
        return 0;
    }
    inline void Redo()
    {
        par[operations.back().second] = operations.back().second;
        sz[operations.back().first] -= sz[operations.back().second];
        operations.pop_back();
    }
};

class SEGMENT_TREE
{
private:
    int tree_size;
    vector<vector<pair<int, int>>> tree;
    DSU_stack dsu_stack;

    inline void Add(int ind, int l, int r, int x, int y, int a, int b)
    {
        if (r < x || y < l)
        {
            return;
        }
        if (x <= l && r <= y)
        {
            tree[ind].push_back({a, b});
            return;
        }
        int m = (l + r) >> 1;
        Add(ind << 1, l, m, x, y, a, b);
        Add(ind << 1 | 1, m + 1, r, x, y, a, b);
    }
    inline void Traverse(int ind, int l, int r)
    {
        if (l == r)
        {
            return;
        }
        int m = (l + r) >> 1;
        for (auto & i : tree[ind])
        {
            dsu_stack.Unity(i.first, i.second);
        }
        Traverse(ind << 1, l, m);
        Traverse(ind << 1 | 1, m + 1, r);
        for (int i = 0; i < tree[ind].size(); ++i)
        {
            dsu_stack.Redo();
        }
    }

public:
    inline SEGMENT_TREE(int new_time_size, int new_graph_size)
    {
        tree_size = new_time_size;
        dsu_stack.Init(new_graph_size);
        tree.clear();
        tree.resize(tree_size << 2);
    }
    inline void Add(int x, int y, int a, int b)
    {
        Add(1, 1, tree_size, x, y, a, b);
    }
    inline void Traverse()
    {
        Traverse(1, 1, tree_size);
    }
};
