class DSU_stack
{
    private:
    vector<int> par, sz;
    vector<array<int, 4>> operations;
    public:
    inline DSU_stack(int new_size)
    {
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
            operations.push_back({ina, inb, sz[ina], sz[inb]});
            sz[ina] += sz[inb];
            par[inb] = ina;
            return 1;
        }
        return 0;
    }
    inline void Redo()
    {
        sz[operations.back()[0]] = operations.back()[2];
        sz[operations.back()[1]] = operations.back()[3];
        par[operations.back()[0]] = operations.back()[0];
        par[operations.back()[1]] = operations.back()[1];
    }
};
