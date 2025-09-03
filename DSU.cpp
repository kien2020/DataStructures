struct DSU
{
    int par[100000], sz[100000];
    inline DSU()
    {
        for (int i = 0; i < 1e5; ++i)
        {
            par[i] = i;
            sz[i] = 1;
        }
    }
    inline int Get(int inp)
    {
        return (inp == par[inp] ? inp : par[inp] = Get(par[inp]));
    } 
    inline void Combine(int ina, int inb)
    {
        ina = Get(ina);
        inb = Get(inb);
        if (ina != inb)
        {
            if (sz[ina] < sz[inb])
            {
                swap(ina, inb);
            }
            sz[ina] += sz[inb];
            par[inb] = ina;
        }
    }
} dsu;
