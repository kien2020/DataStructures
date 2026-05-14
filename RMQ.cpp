//problem: https://oj.uz/submission/1370150

template <class comp>
struct RMQ
{
    int n;
    int sp[20][200000];
    comp compare;
    inline int *operator[](int ind)
    {
        return sp[ind];
    }
    inline void Init(int new_n)
    {
        n = new_n;
    }
    inline void Build()
    {
        for (int i = 1; i <= __lg(n); ++i)
        {
            for (int j = 0; j + (1 << i) <= n; ++j)
            {
                if (compare(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]))
                {
                    sp[i][j] = sp[i - 1][j];
                }
                else
                {
                    sp[i][j] = sp[i - 1][j + (1 << (i - 1))];
                }
            }
        }
    }
};
