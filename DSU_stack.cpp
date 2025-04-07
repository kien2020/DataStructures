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
